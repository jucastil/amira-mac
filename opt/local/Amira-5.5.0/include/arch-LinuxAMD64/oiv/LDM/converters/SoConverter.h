/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (Apr 2003)
**=======================================================================*/

#ifndef _SO_BASE_CONVERTER_
#define _SO_BASE_CONVERTER_

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif


#include <LDM/nodes/SoDataSet.h>
#include <Inventor/STL/vector>
#include <Inventor/SbBox.h>
#include <Inventor/SbPList.h>

#include <Inventor/threads/SbThreadMutex.h>

#include <LDM/readers/SoLDMReader.h>
#include <LDM/compressors/SoDataCompressor.h>

class SoLDMTopoOctree;
class ScJobManagerServer;
class ScJobManagerClient;
class ScJob;
class SoVolumeHistogram;
class SiBitFile;
class SoDataCompressInfo;
class SoPerfCounterManager;
class SoConverterParameters;

/**
 * @LDMEXT Abstract base class for converting data sets into LDM format.
 *
 * @ingroup LDMConverters
 *
 * @DESCRIPTION
 *
 * This is the abstract base class for classes that convert existing data sets
 * into the LDM (Large Data Management) format.
 *
 * SoConverter provides powerful features including:
 * - Command line parsing for easy creation of stand-alone converter programs.
 * - Checkpoint and restart for interrupted conversions.
 * - Distributed conversion (to accelerate conversion using a cluster).
 * - Multiple subsampling algorithms for creating low resolution tiles.
 * - Automatic loading of any supported data format (see SoVolumeData).
 * - Conversion of any data format by providing a custom reader (see SoVolumeReader).
 * - Special handling to minimize disk space for "thin volumes" where one dimension
 *   is smaller than the tile size. (Currently only implemented for Z dimension.)
 * - Optional data compression to reduce disk space.
 * - Optional data type conversion, e.g. float to byte.
 *
 * Information common to all converter classes is included here including
 * command line, incomplete conversion, distributed conversion, compression
 * and subsampling.  Normally you will use, for example, the derived class
 * SoVolumeConverter to convert volume data.  You can also subclass from
 * SoVolumeConverter to use a custom volume reader, provide a custom
 * subsampling method, etc.
 *
 * Command Line
 *
 * This class can be used to easily build a stand-alone command line program
 * for converting volume data sets. The #convert method takes the "argc" and
 * "argv" parameters from the application's "main" function directly.  See
 * $OIVHOME/src/VolumeViz/Converters/convert.cxx.
 *
 * See the complete list of command line options listed under the #convert method.
 *
 * You can also invoke the converter from an application by synthesizing a
 * command line as shown below. Each "token" from the command should be a
 * separate string in the argv array. The first token string is effectively
 * ignored (it would be the application name in a real command line). For example,
 * the command line "convert filename.sgy -b -t 128" would be synthesized like
 * this:
 * <PRE>
 *   char *my_argv[] = {
 *     "Converter",
 *     "filename.sgy",
 *     "-b",
 *     "-t",
 *     "128"
 *   };
 *   int   my_argc = sizeof(my_argv)/sizeof(char*);
 *   myConverter.convert( my_argc, my_argv );
 * </PRE>
 *
 * Incomplete Conversion
 *
 * The converter saves the progress of the conversion in case the user wishes to
 * abort or start visualizing the converted data or if the program crashes for any reason.
 * In this case, the LDM files (header and data) are coupled with a completion file
 * (name of the header file with an extension of .fcp).
 * When restarting the converter, if the header file points to a .fcp file
 * (XML tag \<completionFilename\>), the conversion will restart where it previously ended.
 * When visualizing an incompletely converted file, it is possible to know where
 * data actually exists by turning on the topology outlines (see SoVolumeRendering). Red
 * outlines indicate actual data.
 *
 * In order to restart an incomplete conversion, the header file must be in synch with
 * the completion file.
 * For this reason when writing the pair of header/completion files,
 * the converter first backs up the pair of files before overwriting them (.ldm and .fcp with .bck extension).
 * If the header file is lost or its size is less than the size of the backed up header file,
 * then you can rename the backed up completion and header files to restart the conversion.
 *
 * Distributed Conversion
 *
 * The LDM converter can be run in a distributed mode on a cluster.
 * Conversion speed can be greatly increased in this mode because
 * different regions of the volume are converted in parallel.  You run
 * a "server" converter on the master node and a "client" converter on
 * each of the cluster nodes.
 *
 * A client converter program passes TRUE to the constructor when it
 * creates the SoConverter object. Then it calls the #listenToServer
 * method (instead of the convert method), passing argc and argv. Argv
 * should contain three strings: the executable name, server host name
 * and port number.  See the example program:
 * $OIVHOME/src/VolumeViz/Converters/distributed/clientConvert.cxx.
 * Depending on the communication tools available (e.g. ssh) a script
 * can be used to launch the clients once the server has been launched.
 * See $OIVHOME/src/VolumeViz/Converters/distributed/launch.sh for an
 * example.
 *
 * Start the server converter with the usual arguments (input filename
 * and options) plus "-D". The port number can be specified using the
 * -P option or can be chosen dynamically by passing a null port (-P 0).
 * In this case, the server will output the port number it is using.
 * If unspecified the server converter will open the communication on
 * port 7654.
 *
 * @SEE_ALSO
 *    SoVolumeConverterParameters,
 *    SoVolumeConverter,
 *    SoVolumeReader,
 *    SoDataCompressor,
 *    SoJpegDataCompressor,
 *    SoGzipDataCompressor
 *
 *
 */
class LDM_API SoConverter {

public:

  /**
   * Destructor.
   */
  virtual ~SoConverter();

  /**
   * Converter errors.
   */
  enum ConverterError{
    /** No error */
    CVT_NO_ERROR                =  0,
    /** Input params problems */
    CVT_INPUT_PARAMS_PROBLEM    = -1,
    /** Unknown file extension */
    CVT_FILE_EXT_UNKNOWN        = -2,
    /** Unable to open file */
    CVT_CANT_OPEN_INPUT_FILE    = -3,
    /** Unable to create data file */
    CVT_CANT_CREATE_DATA_FILE   = -4,
    /** Unable to create header file */
    CVT_CANT_CREATE_HEADER_FILE = -5,
    /** No enough disk space */
    CVT_NOT_ENOUGH_DISK_SPACE   = -6,
    /** Unable to read input file */
    CVT_CANT_READ_INPUT_FILE    = -7,
    /** Conversion aborted */
    CVT_ABORTED                 = -9,
    /** Uninitialized converter */
    CVT_NOT_INITIALIZED         = -10,
    /** No node */
    CVT_NO_NODE                 = -998,
    /** No LDM license */
    CVT_NO_LDM_LICENSE          = -999
  };

  /**
  * Converts an input file into the LDM (Large Data Management) format.
  * The string should be of the following form:
  *
  * inputFilename [-t tiledim] [-b [bordersize]] [-o filename] [-O [filename]] [-m memsize] [-h] [-w B|L]
  *               [-f u8|u16|u32|s8|s16|s32|f [-r min max]] [-q] [-D] [-P portnum] [-c type] [-l level]
  *               [-C] [-s [0..N]] [-u value]
  *
  * where:
  *
  *  @TABLE_1B
  * @TR-t tiledim @TD Dimension of tiles. Must be a power of two. Default is 64, meaning 64x64x64.
  *
  * @TR-b bordersize @TD Build tiles so that they overlap each other in order to avoid artifacts
  *               during rendering.
  *               If specified, the size of the output file is larger.
  *               If no argument is specified, the border size is 1. In order to avoid discontinuity artifacts
  *               with lighted volume rendering or with bump mapped slices, a border size of 3 should be specified.
  *               This will increase the size of the output file even further.
  *
  * @TR-o filename @TD Name of created XML header ldm file. Default is inputFilename with extension .ldm.
  *
  * @TR-O filename   @TD Name of the file containing the data.
  *               If filename is omitted, the default filename is the same
  *               as the output filename specified by the -o option, with extension .dat instead.
  *
  * @TR-m memsize    @TD Maximum size of memory to use in MB. Default is 512 MB.
  *
  * @TR-h            @TD Output the header only.
  *
  * @TR-w wordfmt    @TD Indicates the target machine word format is Big Endian (B) or Little Endian (L).
  *               Default is the current machine word format.
  *
  * @TR-f datafmt    @TD Indicates the output data format with * = 8,16,32. u*:unsigned integer, s*:signed integer, f:float.
  *               If the output data format is float, the values are mapped to the range [0-1].
  *               Default is the input data format.
  * @TR-r min max    @TD Indicates the input data range to map to the new data format specified by the -f option.
  *               If not specified, and input type is float and ouput type is integer, the values are simply cast into the output data type.
  * @TR-q            @TD Quiet mode.
  *
  * @TR-D            @TD Distributed mode. The application specifying this option becomes the server converter,
  *               and, by default opens port number 7654.
  *
  * @TR-P portnum    @TD Port number. Default is 7654. If 0 is specified, the port number is dynamically assigned.
  *
  * @TR-c type @TD Type of compression used. By default the following compression types are available: gzip and jpeg.
  *                Jpeg is a lossy compression format and should not be used if data degradation is unacceptable.
  * @TR-l level @TD Level of compression used. The meaning of this parameter depends on the type of compression used:
  *
  *                 -For gzip, it must be between 0 and 9: 0 gives no compression, 9 gives best compression but slower speed.
  *                  Default is 3.
  *
  *                 -For jpeg, it must be between 0 and 100: 0 gives best compression but most loss of data,
  *                 100 gives minimum compression and minimum data alteration. Default is 85.
  *
  * @TR-C @TD Data integrity check. When compression is enabled using -c, adds a data integrity check value
  *                 to all compressed tiles.
  *                         If the environment variable LDM_COMPRESS_CHECK_CRC32 is set, data values will be checked
  *                         each time they are read from disk.
  * @TR-s 0..n @TD Specifies the algorithm used to build low resolution tiles. Available options are :
  *                 - 0 to use decimation algorithm (one voxel out of two).
  *                 - n to use weighted average algorithm : voxels of tile of resolution N+1 are
  *                   built from the average of the 6 neighbors from resolution N and the current
  *                   voxel value weighted by n.
  *                 If not specified, by default the decimation algorithm is used (n=0).
  * @TR-u value @TD Undefined value. The given value will marked as undefined in the LDM file.
  *                 This is currently used by SoHeightFieldRender (vertices with undefined values
  *                 are not rendered).
  *
  * @TR-rgba @TD Specifies that output will be unsigned int32 RGBA values.
  *
  * @TR-noHistogram @TD Disable histogram computation (conversion will be faster).
  *
  * @TR-B value @TD      Define threshold value to generate a bitset dataset. @BR
  *               Any value in the dataset less than or equal to the threshold will generate a zero bit.
  *               Values greater than threshold will generate a one bit.
  *
  *    @TABLE_END
  *
  * The return value may be one of the following:@BR
  *
  *    @TABLE_1B
  *       @TR CVT_NO_ERROR                 @TD No problem, task complete
  *       @TR CVT_INPUT_PARAMS_PROBLEM     @TD Input parameters problem: input filename missing, bad parameter
  * value, or invalid option
  *       @TR CVT_FILE_EXT_UNKNOWN         @TD Unknown file type (file extension)
  *       @TR CVT_CANT_OPEN_INPUT_FILE     @TD Could not open input file (does not exist)
  *       @TR CVT_CANT_CREATE_DATA_FILE    @TD Could not create data file
  *       @TR CVT_CANT_CREATE_HEADER_FILE  @TD Could not create header file
  *       @TR CVT_NOT_ENOUGH_DISK_SPACE    @TD Could not allocate disk space for the data file
  *       @TR CVT_ABORTED                  @TD Conversion has been aborted by the application, task not complete
  *       @TR CVT_NO_NODE                  @TD Distributed converter cannot be used as the license does not allow any client node
  *       @TR CVT_NO_LDM_LICENSE           @TD No LDM license
  *    @TABLE_END
  *
  *
  * If in a distributed scheme only the server calls this function
  * [OIV-WRAPPER-ARG NO_WRAP{((argv != NULL? argv->Length: 0))},IN]
  * [OIVJAVA-WRAPPER-RETURN-TYPE WRAP_AS{SoConverter::ConverterError}]
  */

  /**
   * Deprecated method, please use the new main api
   * int convert( SoConverterParameters* parameters = NULL);
   */
  SoDEPRECATED int convert( int argc, char ** argv);
  SoDEPRECATED int convert( const SbStringList& arguments );

  /**
   * Main converter function. @BR
   * Call this method to launch the converter. Conversion parameters may be
   * specified using an instance of SoConverterParameters. Returns
   * 0 if conversion was successful, else returns one of the CVT_ error codes
   * above.
   */
  int convert( SoConverterParameters* parameters = NULL);

  /**
   * Specifies the callback that will be called when the LDM file header is generated.
   * This allows the application to add custom XML tags.
   * The custom tags can be read back using the method SoVRLdmFileReader::getXmlTag().
   */
  void setXmlCallback( void (*xmlCB)( FILE*, void * userData ), void * userData );

  /**
   * Used by a client converter if in distributed mode.
   * argv must contain the executable name, server host name, and port number.
   * [OIV-WRAPPER-ARG NO_WRAP{((argv != NULL? argv->Length: 0))},IN]
   */
  void listenToServer(int argc, char** argv);

SoINTERNAL public:

  enum MessageType{
    INIT = 1,
    BUILD_SLAB,
    BUILD_LEVEL,
    CLEAR
  };

  //used by clients:
  ScJobManagerClient* m_client;

  char*     m_slabBuffer;
  SbVec3i32 m_slabBufferDim;
  int64_t   m_subSliceSize;
  bool      m_stopClient;

  //statistics
  SoVolumeHistogram* m_stat;
  double             m_min, m_max;
  std::vector<int64_t>    m_numValues;
  std::vector<double>     m_values;

  int                m_numTilesGenerated;
  float              m_progress;

  struct Stat{
    double  value;
    int64_t numValues;
  };

  void checkProgress();


  //data information
  int                    m_dataSize;
  int                    m_shrunkTileSize;

  //routines
  ConverterError init();

  char* allocateSlabBuffer(int& _numTilesOnYAxis, SbVec3i32& _slabBufferDim, int64_t& _subSliceSize);
  int   buildSlab2Level(SbBox3i32& slabBox, char*& slabBufferPtr, void* parentTile, void** octantTile,SbVec3i32& slabBufferDim, int64_t subSliceSize, std::vector<int>& fileIDsBuilt);
  void  buildLevel(std::vector<int>&, int, int fromFileID = -1, int toFileID = -1);
  int   initializeFiles( int argc, char ** argv );

  int   writeSubVolume( const SbBox3i32 & subVolume, const void * data, SbBool doLowerResolution = TRUE, SbBool doOverlappingTiles = TRUE );
  int   writeTile( const SoLDMTileID & tileID, void * data );

  int   writeSubVolume( const SbBox3i32 & subVolume, SoBufferObject* data, SbBool doLowerResolution = TRUE, SbBool doOverlappingTiles = TRUE );
  int   writeTile( const SoLDMTileID & tileID, SoBufferObject* data );

  const SoLDMTopoOctree* getTopo() { return m_LDMTopo; };
  int   finalizeFiles( int retCode = 0 );
  int   buildLevels( int fromLevel, int numLevels );
  virtual bool isTileShrinkable() { return true; }      // Return the status of the last tile in reservoirviz
  virtual bool isTileShrinkable(int ) {return true;} ;  // Return the status of the tile tileId in reservoirviz
  virtual bool isTileShrinkable(int, SbVec3i32, void *) {return true;}  // Virtual method used by ReservoirViz converter.
                                                                        // return true by default
  virtual void setUncompressedSize(int , int64_t ) {return; };  // Virtual method used by ReservoirViz converter.
                                                                // return true by default

  virtual int64_t getUncompressedSize(int ) {return 0;}; // Virtual method used by ReservoirViz converter.
                                                               // return true by default

  virtual void toiTileToRaw(int &neededSize, char* dataPtr = NULL) { neededSize = 0; dataPtr = NULL; } // Virtual method used by ReservoirViz converter.


  void * m_fout;
  SoConverterParameters* getParameters();
  void updateFileCompletion(std::vector<int>& fileIDs);

  std::vector<SoDataSet::DatumElement> m_datum;
  bool                   m_isDataFloat;
  bool                   m_isDataSigned;
  size_t                  m_tileSize;
  int                    m_numSigBits;

protected: //PROTECTED_TO_DOCUMENT

  /**
   * Constructor.
   */
  SoConverter(SbBool isClient = FALSE);

  virtual void setCurrentTimeStep( int curTimeStep );
  //// TO REDEFINE WHEN A CLIENT MODULE INHERITS FROM THE CONVERTER://///
  virtual void getSubSlice( const SbBox2i32& subSlice, int sliceNumber, void * data ) = 0;

  //error returned : 0 = ok, 1 = pb = return
  virtual SbBox3f getSize(int& error) = 0;
  virtual std::vector<SoDataSet::DatumElement> getDatum(int& error) = 0;
  virtual SbVec3i32 getDimension(int& error) = 0;
  virtual int getRange( double & rangeMin, double & rangeMax) = 0;
  virtual SoVolumeHistogram* getHistogram();
  virtual std::vector<SbVec2d>& getTileMinMax(int numTiles);
  virtual void closeInputFileHandles();

  /**
   * Method used to downsample a tile. The input are the eight higher resolution tiles used to create the
   * one lower resolution tile (parent).
   * By default, the converter simply takes one voxel out of two in the higher resolution tile to create the
   * parent tile. This method can be overriden by a custom converter to use a different approach.
   * Inputs are:
   * tileDim is the size of the tile to create in number of voxels.
   * dataType is the type of the data (the value corresponds to the SoDataSet::DataType enum).
   * border takes a 0 or 1 value to let the user know whether border between tiles should be handled.
   * octantTile are the values of the 8 higher resolution tiles.
   * octantExists let the user know if a given octant is free of data (the data is an asymmetric volume).
   * Output is the parentTile buffer.
   */
  virtual void  sampleTile ( const SbVec3i32& tileDim, int border, const void* const octantTile[8], const int octantExists[8], void* parentTile ) = 0;
  virtual void  buildTile  ( SbBox3i32& slabBox, SbVec3i32& slabBufferDim, void* slabBuffer, SbVec3i32& tileOrigin, void* tileBuffer );
          void  buildTile  ( const SbBox3i32& subVolume, const void* subVolumeBuffer, const SbBox3i32& tilePos, void* tileData, const SbBox3i32& intersection );
  virtual void  outputHeader( FILE* ) {};
  virtual void  outputTileBefore( int fileTileIndex, int dataSize, void *data, bool dataInverted );
  virtual void  startConversion(){};
  virtual void  endConversion(){};

  virtual bool updateDataFile() { return true; }
  virtual int getSpecificOffset(bool aligned = true ) { return !aligned; }      // dummy return to avoid compilation warning

  //// END LIST OF FUNC TO REDEFINE WHEN A CLIENT MODULE INHERITS FROM THE CONVERTER://///

  /** Abort */
  enum Abort {
    /** */
    CVT_CONTINUE,
    /** */
    CVT_ABORT
  };

  /**
  * Define available algorithm available for downsampling process
  */
  enum SampleType
  {
    /**
     * Decimation : Only one voxel out of two
     */
    DECIMATION,
    /**
     * Average : Voxel value in parent tile is an average of Neighbor voxel in child tile
     */
    AVERAGE
  };

  /**
   * This method is called each time a tile of data is generated.
   * numTilesGenerated represents the number of tiles already generated and numTilesToGenerate is
   * the total number of tiles to generate. So the quotient of these two numbers represents the progress
   * of the task.
   * If this method returns ABORT, the task is stopped. By default it returns CONTINUE.
   */
  virtual Abort progress( int numTilesGenerated, int numTilesToGenerate );

  ConverterError  buildHeader( const SbString&, bool conversionDone = false);

  virtual void outputDataType(FILE* fout);

  SbBox3f          m_volumeSize;

  void inputTile( int fileTileIndex, int dataSize, void *data, bool i = false );
  void printTime();
  int buildLevelMax();
  void outputTile( int fileTileIndex, int dataSize, void*, bool i = false );
  virtual size_t shrinkTile(int dataSize, void *data);

  void printCompressionInfos();

  void (*m_xmlCB)( FILE*, void* );
  void  *m_xmlCBUserData;
  SoLDMTopoOctree *m_LDMTopo;

  //files info
  int64_t   m_filesize;//final data file size
  int64_t   m_compressedFilesize;//final compressed file size
  SbString  m_fileCompletion; //file completion
  SbString  m_fileCompletionName;
  SbString m_fileExt;

  //prog argument
  SbString  m_serverName;

  //data info
  int              m_pid;
  int              m_levelMax;
  bool             m_thinDataSet;
  SbVec3i32        m_volumeDimension;


  int              m_numTimeSteps;
  int              m_curTimeStep;

  // progress
  int              m_numTilesToGenerate;
  bool             m_abort;
  int  getNumTileToGenerate(SbBox3i32& slabBox);
  SiBitFile* m_bitFile;

  //Compression
  SoDataCompressor *m_ldmCompressor;
  int64_t m_sizeOfTileIndex;
  char m_compressionType[256];
  SoDataCompressInfo* m_lastWrittenCompressInfo;


  bool       m_fromInitializeFiles;

  ScJobManagerServer*    m_server;
  //orders sent to clients by server:
  ScJob* getInitJob( const SbStringList& arguments );//---> init job sent to all clients at connection time
  void sendSlabJobs(std::vector<SbBox3i32>&);
  void sendLevelJobs(std::vector<SbVec3i32>&);
  void sendClearJob();

  bool m_isServer;
  SbString m_hostName;

  //file completion
  void writeTileComplete(int fileID, bool writeHeader = false);

  //abort function
  void abortConversion();

  void readSlab(SbBox3i32& slabBox, char*& slabBufferPtr,int64_t subSliceSize);

  //number of client converter allowed to be connected to the server converter
  int m_numClientAllowed;

  // Define the algorithm used for downsampling
  SampleType m_sampleType;


  // type dependent vars/macros
  static const char *m_dataTypeStr[];
  static const char *m_dataTypeXml[];
  int              m_currentWordFormat;

  // Performance counter manager
  SoPerfCounterManager *m_perfManager;

  SoConverterParameters* m_parameters;

  virtual void adjustParameters() {};

    /** One minMax for each file ids */
  std::vector<SbVec2d> m_tileMinMax;

private:
  bool m_userDefinedParameters;
  int64_t getCrc32(void* data, int dataSize, const SoDataCompressor::TileInfo& ti);
  void usage();
  template <typename T> void fillTile(void* ptrDst, int size, void* value );

  template <typename T> void fillTileWithSingleValue(void* ptrDst, int size, T value );

  /** Write min max infos into the ldm file */
  SoConverter::ConverterError outputMinMaxInfos(FILE* fout);

  /** Compute minMax of low res by combining min max of children*/
  void computeLowResMinMax(const SoLDMTileID& tileId, int timeStep);

  bool m_bComplFileAlreadyExists;

  static SbThreadMutex s_classMutex;
};

inline void
SoConverter::setCurrentTimeStep( int )
{
}

inline void
SoConverter::outputTileBefore( int , int , void *, bool )
{
}

inline SoConverterParameters*
SoConverter::getParameters()
{
  return m_parameters;
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif //_SO_BASE_CONVERTER_
