/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG3D (Jun 2009)
**=======================================================================*/


#ifndef _SO_BASE_CONVERTER_PARAMETERS
#define _SO_BASE_CONVERTER_PARAMETERS

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

#include <Inventor/STL/vector>
#include <Inventor/SbBox.h>
#include <Inventor/SbPList.h>
#include <LDM/compressors/SoDataCompressor.h>
#include <Inventor/helpers/SbFileHelper.h>

/**
 * @LDMEXT Container class for LDM converter parameters
 *
 * @ingroup LDMConverters
 *
 * @DESCRIPTION
 *   This class provides a convenient way to specify parameters for the
 *   LDM converter.
 *
 * @SEE_ALSO
 *    SoConverter
 */
class LDM_API SoConverterParameters {

public:
  
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

  enum ParametersError
  {
    /** No error */
    PARAM_NO_ERROR =  0,
    /** Input params problems */
    PARAM_ERROR    = -1,
  };

  
  /**
   * Default constructor. 
   */
  SoConverterParameters( );

  /**
   * Destructor.
   */
  virtual ~SoConverterParameters();

  /**
  *  Static method to build a parameters container from command line arguments. @BR
  * The method returns NULL if an error is detected in the arguments. 
  * Otherwise, it returns a pointer
  * to an instance of the class, initialized with given parameters.
  * See SoConverter::converter for a list of command line arguments.
  */
  static SoConverterParameters* create( int argc, char** argv );

  /**
  *  Static method to build a parameters container from command line arguments. @BR
  * The method returns NULL if an error is detected in the parameters. 
  * Otherwise, it returns a pointer
  * to an instance of the class, initialized with given parameters
  * See SoConverter::converter for a list of command line arguments.
  */
  static SoConverterParameters* create( const SbStringList& arguments );

  /**
   * Set verbose mode. Default value is Off.
   */    
  void setVerbose( const bool isVerbose );

  /**
   * Returns verbose mode setting.
   */
  bool isVerbose() const;

  /**
   * Set tile dimension. @BR
   * Like the -t command line argument.
   * The default is 64 and the value must be a power of 2. 
   * The same value is used for all dimensions of the tile. 
   */
  void setTileDim( const int tileDim );

  /**
   * Set tile dimension. @BR
   * The default value is 64,64,64 and all values must a power of 2. 
   * This method can be used to set a different 
   * value for each tile dimension, for example for a "thin volume" or
   * height field.
   */
  void setTileDim(const SbVec3i32& tileDim);

  /**
   * Returns tile dimension.
   */
  SbVec3i32 getTileDim() const;
  
  /**
   * Set border (overlap) value in voxels. @BR
   * Like the -b command line argument.
   * Build tiles so they overlap in order to avoid artifacts during rendering. 
   * If specified, the size of the output file is larger. In order to avoid 
   * discontinuity artifacts with lighted volume rendering or with bump mapped 
   * slices, overlap of 3 should be specified.
   *
   * Default value is 0. A call to setBorder with no parameter will set 
   * the border to 1 (like "-b" on the command line).
   * Returns true if parameter is valid, else returns false.
   */
  bool setBorder( const int border = 1 );

  /**
   * Returns border (overlap) value.
   */
  int getBorder() const;

  /**
   * Set header filename (i.e. the .ldm filename). @BR
   * Like the -o command line argument.
   * Default is input filename with extension .ldm.
   */
  void setHeaderFileName( const SbString& headerFileName );

  /**
   * Returns header filename.
   */
  SbString getHeaderFileName() const;

  /**
   * Set data filename (i.e. the .dat filename). @BR
   * Like the -O command line argument.
   * Default is the same as the header file, with .dat extension.
   */
  void setDataFileName( const SbString& dataFileName );

  /**
   * Returns the data filename. 
   */
  SbString getDataSectionFileName() const;

  /**
   * Returns the complete data filename (i.e.: the whole path to .dat file). 
   */
  SbString getDataFileName() const;

  /**
  * Set the input filename.  @BR
  * This is the file containing data to convert.
  * An input file must be specified.
  */
  void setInputFileName( const SbString& inputFileName );

 /**
  * Returns input filename. 
  */
  SbString getInputFileName() const ;

  /**
   * Set maximum memory available for the converter, in MB. @BR
   * Like the -m command line argument. Default value is 512 MB. 
   * Returns true if parameter is valid, else returns false.
   */
  bool setMaxMemory( int maxMemory );

  /**
   * Returns max memory available for converter.
   */
  int getMaxMemory() const;

  /**
   * Set the header only feature. @BR
   * Like the -h command line argument. If set,
   * the converter will only write the header file. No data will
   * be generated. Default value is Off.
   */
  void setOutputHeaderOnly( bool headerOnly );

  /**
  * Returns header only setting.
  */
  bool getOutputHeaderOnly() const;

  /**
   * Set the output data format from a format string. @BR
   * Like the -f command line argument. The format is specified as
   * "u*" for unsigned integer, "s*" for signed integer or "f" for float, where
   * * = 8, 16 or 32. Default is no conversion.
   * Returns true if parameter is valid, else returns false.
   *
   * Note that if the input reader does not support the requested conversion, 
   * the output data format will be the same as the input data format (no conversion).
   */
  bool setOutputDataFormat( const SbString& dataFormat );

  /**
   * Set the output data format with an SoDataSet::DataType. @BR
   * Note that if the input reader does not support the requested conversion, 
   * the output data format will be the same as the input data format (no conversion)
   * Returns true if parameter is valid, else returns false.
   */
  bool setOutputDataFormat( const SoDataSet::DataType& dataType);

  /**
   * Returns the output data format.
   */
  SoDataSet::DataType getOutputDataFormat() const;

  /**
   * Set the target machine word format. @BR
   * Like the -w command line argument. Default is the current machine word format.
   * wordFormat parameter is 0 for Big Endian, and 1 for Little Endian.
   * Returns true if parameter is valid, else returns false.
   */
  bool setTargetWordFormat(int wordFormat);

  /**
  * Returns word format property.
  */
  int getTargetWordFormat() const;
  
  /**
   * Set the input data range to map to the output data format. @BR
   * Like the -r command line argument. If not specified, and input type 
   * is float and output type is integer, the values are simply cast into the output data type. 
   * Returns true if parameter is valid, else returns false.
   */
  bool setInputRangeMinMax( double min, double max );

  /**
   * Returns input data range.
   */
  void getInputRangeMinMax( double& min, double& max ) const;

  /**
   * Set compression name. @BR
   * Like the -c command line argument.
   * The following compression types are currently supported: "gzip" and "jpeg". 
   * Jpeg is a lossy compression format and should not be used if data degradation is unacceptable.
   * Returns true if parameter is valid, else returns false.
   */
  bool setCompressionName( const SbString& compressionName );

  /**
   * Set compression level. @BR
   * Like the -l command line argument.
   * The meaning of this parameter depends on the type of compression used:
   * -For gzip, it must be between 0 and 9: 0 gives no compression, 
   *  9 gives best compression but slower speed. Default is 3.
   * -For jpeg, it must be between 0 and 100: 0 gives best compression but most loss of data, 
   *  100 gives minimum compression and minimum data alteration. Default is 85.
   */
  void setCompressionLevel (int compressionLevel );
  
  /**
   * Set CRC32 check on compression. @BR
   * Like -C command line argument.
   * When compression is enabled using -c, adds a data integrity check value to all compressed 
   * tiles. If the environment variable LDM_COMPRESS_CHECK_CRC32 is set, data values will be 
   * checked each time they are read from disk. Default is false.
   */
  void setCrcCheck (bool addCrcCheck );

  /**
   * Returns compression type.
   */
  SbString getCompressionName() const;

  /*
   * Returns compression level.
   */
  int getCompressionLevel() const;

  /*
   * Returns CRC check setting.
   */
  bool isCrcCheckDone () const;

  /*
   * Returns true if using default compression level.
   */
  bool useDefaultCompLvl() const;

  /**
  * Set the algorithm used to build low resolution tiles. @BR
  * Available options are : 
  * - 0: To use decimation algorithm
  * - n: To use average algorithm and give a ponderation coefficient of n
  *      to the selected voxel.
  * The default is Decimation.
  * Returns true if parameter is valid, else returns false.
  */
  bool setLowResAlgorithm( int lowResAlgorithm );

  /**
  * Returns algorithm used to build low resolution tiles.
  */
  SampleType getLowResAlgorithm() const;

  /**
  * Retrieve the ponderation coefficient for low resolution tiles. @BR
  * Only relevant when low resolution algorithm is set to AVERAGE.
  */
  int getPondCoef() const;

  /**
  * Set the undefined value. @BR
  * Like the -u command line argument.
  * The given value will be stored in the LDM file. Default is NaN (Not a Number).
  * This is currently used by SoHeightFieldRender (vertices with undefined values are not rendered).
  */
  void setUndefinedValue(double undefinedValue);

  /**
  * Returns the undefined value.
  */
  double getUndefinedValue() const;

  /**
  * Set distributed mode. @BR
  * Like the -D command line argument. Default is false.
  * The application becomes the server converter, and, by default opens port number 7654.
  */
  void setDistributed(bool isDistributed);

  /**
  * Returns the distributed mode.
  */
  bool isDistributed() const;

  /**
   * Set the server port for distributed conversion. @BR
   * Like the -p command line argument. If parameter is 0, the port number is
   * chosen dynamically. Default value is 7654.
   * Returns true if parameter is valid, else returns false.
   */
  bool setServerPort(int serverPort);

  /**
   * Returns server port number.
   */
  int getServerPort() const;

  /**
  * Returns the number of arguments set during init
  */
  int getNbArgs() const;

  /**
  * Return whether or not the output data type has been specified
  */
   bool isOutputDataTypeSpecified() const;

  /**
  * Return whether or not the input data range has been specified
  */
  bool isInputDataRangeSpecified() const;

  /**
   * Set RGBA data mode (output will be unsigned int32 RGBA values).
   */
  void setRGBAMode(const bool flag);

  /**
   * Returns true if RGBA mode.
   */
  bool isRGBAMode() const;

  /** 
   * Specify if the histogram must be computed or not. Default is true.
   *
   * Disabling Histogram generation will greatly speedup the conversion process,
   * but some VolumeViz rendering features and optimizations won't be available.
   * 
   * It also implies that the following information won't be computed:
   * - dataset min and max values
   * - per Tile min max values
   *
   * Note also that if RGBA mode is set then no histogram is computed.
   */
  void enableHistogram(const bool flag);

  /**
   * Returns true if histogram will be computed.
   */
  bool isHistogramEnabled() const;

  /** 
   * Returns true if output will be saved as a bitset (ie: 8 values per byte)
   */
  bool isSavedAsBitSet() const;

  /**
   * Specify if dataset should be saved as a bitset (8 values per byte) or values.
   * @param flag Dataset is a bitset (true) or values (false) 
   * @param bitsetThreshold For each value (V) of a dataset, if V > bitsetThreshold
   * the bitset is set to 1 for this bit, or to 0 otherwise. Used only if flag parameter is
   * set to true. Default is 0.
   */
  void saveAsBitSet( bool flag, double  bitsetThreshold = 0);

  /**
  * Returns the bitset generation threshold value.
  */
  double getBitSetThreshold() const;

  /** 
  * Set the bitset threshold value. @BR
  * Whichever was called last, saveAsBitSet or this method, determines the threshold value that will be used.
  * @param bitsetThreshold. For each value (V) of a dataset, if V > threshold
  * the bitset is set to 1 for this bit, or to 0 otherwise. Default is 0.
  */
  void setBitSetThreshold( double bitsetThreshold );

SoINTERNAL public:
  SbStringList* getArgListAsSbString() const;

  /**
  * This method is used internally for DataEditing.
  * Specify the converter will be used to update existing data file.
  */
  bool isForEditing() const;
  void setIsForEditing(bool flag);
  void setDefaultValue(double value);
  double getDefaultValue() const;
  bool isBorderDefault();
  bool isTileDimDefault();
  bool isRGBAModeDefault() const;
  void setIsFromWriter( bool flag );
  bool isFromWriter() const;

  /**
   * Specify if tile min/max must be computed or not. Default is true.
   *
   */
  void enableTileMinMax(const bool flag);

  /**
   * Returns true if tile min/max will be computed.
   */
  bool isTileMinMaxEnabled() const;

private: //PROTECTED_TO_DOCUMENT

  bool      m_verboseMode;
  bool      m_outputDataTypeSpecified;
  bool      m_inputDataRangeSpecified;
  bool      m_headerOnly;
  bool      m_crcCheck;
  bool      m_distributed;
  bool      m_useDefaultCompLevel;
  double    m_defaultValue;
  bool      m_RGBAMode;

  int       m_border;
  int       m_memSize;
  int       m_currentWordFormat;
  int       m_targetWordFormat;
  int       m_compressionLevel;
  int       m_pondCoeff;
  int       m_serverPort;
  int       m_nbArgs;

  double    m_undefValue;
  double    m_dataRangeInMin;
  double    m_dataRangeInMax;

  SbString  m_headerFileName;
  SbString  m_dataSectionFileName;
  SbString  m_dataFileName;

  SbString m_inputFileName; //file to convert 
  SbString m_fileExt;
  SbString m_compressionName;
  
  SampleType             m_sampleType;
  SoDataSet::DataType    m_dataTypeOut;
  SbVec3i32              m_tileDim;

  SbStringList m_argListAsSbString;

  // type dependent vars/macros
  static const char *m_dataTypeStr[];
  static const char *m_dataTypeXml[];

  void buildOutputFileName();
  bool m_isForEditing;
  bool m_isBorderDefaultValue;
  bool m_isTileDimDefaultValue;
  bool m_savedAsBitSet;
  bool m_isRGBAModeDefault;
  bool m_doHistogram;
  bool m_doTileMinMax;
  double m_bitsetThreshold;

  // Who instanciate the converterParameters
  bool m_bFromWriter;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

inline bool
SoConverterParameters::isVerbose() const
{
  return m_verboseMode;
}

inline void
SoConverterParameters::setVerbose(bool flag)
{
   m_verboseMode = flag;
}

inline SbVec3i32
SoConverterParameters::getTileDim() const
{
  return m_tileDim;
}

inline int
SoConverterParameters::getBorder() const 
{
  return m_border;
}

inline void
 SoConverterParameters::setHeaderFileName( const SbString& headerFileName )
 {
    m_headerFileName = headerFileName;
    m_dataFileName.makeEmpty();
    m_dataSectionFileName.makeEmpty();
 }

inline SbString
SoConverterParameters::getHeaderFileName() const
{
  return m_headerFileName;
}

inline SbString
SoConverterParameters::getDataSectionFileName() const 
{
  return m_dataSectionFileName;
}

inline void
SoConverterParameters::setDataFileName(const SbString& dataFileName)
{
  m_dataFileName = dataFileName;
  m_dataSectionFileName = SbFileHelper::getBaseName( m_dataFileName );
}

inline SbString 
SoConverterParameters::getDataFileName() const
{
  return m_dataFileName;
}

inline int
SoConverterParameters::getMaxMemory() const 
{
  return m_memSize;
}

inline bool
SoConverterParameters::getOutputHeaderOnly() const 
{
  return m_headerOnly;
} 

inline void
SoConverterParameters::setOutputHeaderOnly(bool headerOnly)
{
  m_headerOnly = headerOnly;
} 

inline SoDataSet::DataType 
SoConverterParameters::getOutputDataFormat() const
{
  return m_dataTypeOut;
}

inline int
SoConverterParameters::getTargetWordFormat() const
{
  return m_targetWordFormat;
}

inline SbString 
SoConverterParameters::getCompressionName() const
{
  return m_compressionName;
}

inline int 
SoConverterParameters::getCompressionLevel() const 
{
  return m_compressionLevel;
}

inline bool 
SoConverterParameters::isCrcCheckDone() const 
{
  return m_crcCheck;
}

inline void 
SoConverterParameters::setCrcCheck ( bool addCrcCheck )
{
  m_crcCheck = addCrcCheck;
}

inline void
SoConverterParameters::getInputRangeMinMax(double& min, double& max) const 
{
  min = m_dataRangeInMin;
  max = m_dataRangeInMax;
}

inline SoConverterParameters::SampleType
SoConverterParameters::getLowResAlgorithm() const 
{
  return m_sampleType;
}

inline double
SoConverterParameters::getUndefinedValue() const 
{
  return m_undefValue;
}

inline void
SoConverterParameters::setDistributed(bool isDistributed)
{
  m_distributed = isDistributed;
}

inline bool
SoConverterParameters::isDistributed() const 
{
  return m_distributed;
}

inline int
SoConverterParameters::getServerPort() const 
{
  return m_serverPort;
}

inline int
SoConverterParameters::getNbArgs() const 
{
  return m_nbArgs;
}

inline bool
SoConverterParameters::useDefaultCompLvl() const 
{
  return m_useDefaultCompLevel;
}

inline void
SoConverterParameters::setUndefinedValue(double undefinedValue)
{
  m_undefValue = undefinedValue;
}

inline bool 
SoConverterParameters::isOutputDataTypeSpecified() const 
{
  return m_outputDataTypeSpecified;
}

inline void
SoConverterParameters::setInputFileName( const SbString& inputFileName )
{
  m_inputFileName = inputFileName;

  buildOutputFileName();
}

inline SbString
SoConverterParameters::getInputFileName() const 
{
  return m_inputFileName;
}

inline bool
SoConverterParameters::isInputDataRangeSpecified() const 
{
  return m_inputDataRangeSpecified;
}

inline int 
SoConverterParameters::getPondCoef() const 
{
  return m_pondCoeff;
}

inline bool
SoConverterParameters::isForEditing() const 
{
  return m_isForEditing;
}

inline void
SoConverterParameters::setDefaultValue(const double value)
{
    m_defaultValue = value;
}

inline double
SoConverterParameters::getDefaultValue() const
{
    return m_defaultValue;
}

inline bool
SoConverterParameters::isBorderDefault()
{
  return m_isBorderDefaultValue;
}

inline bool
SoConverterParameters::isTileDimDefault()
{
  return m_isTileDimDefaultValue;
}

inline bool
SoConverterParameters::isSavedAsBitSet() const
{
  return m_savedAsBitSet;
}

inline void 
SoConverterParameters::saveAsBitSet( bool flag, double bitsetThreshold )
{
  m_savedAsBitSet = flag;

  if ( flag )
    m_bitsetThreshold = bitsetThreshold;
}

inline void 
SoConverterParameters::setRGBAMode(const bool flag)
{
  m_isRGBAModeDefault = false;
  m_RGBAMode = flag;
}

inline bool 
SoConverterParameters::isRGBAMode() const
{
  return m_RGBAMode;
}

inline void 
SoConverterParameters::enableHistogram(const bool flag)
{
  m_doHistogram = flag;
}

inline bool
SoConverterParameters::isHistogramEnabled() const
{
  return m_doHistogram && !isRGBAMode();
}

inline void
SoConverterParameters::enableTileMinMax(const bool flag)
{
  m_doTileMinMax = flag;
}

inline bool
SoConverterParameters::isTileMinMaxEnabled() const
{
  return m_doTileMinMax;
}

inline bool
SoConverterParameters::isRGBAModeDefault() const 
{
  return m_isRGBAModeDefault;
}

inline double
SoConverterParameters::getBitSetThreshold() const
{
  return m_bitsetThreshold;
}

inline void
SoConverterParameters::setBitSetThreshold( double bitsetThreshold ) 
{
  m_bitsetThreshold = bitsetThreshold;
}

inline bool
SoConverterParameters::isFromWriter() const
{
  return m_bFromWriter;
}

inline void
SoConverterParameters::setIsFromWriter( bool flag )
{
  m_bFromWriter = flag;
}



#endif //_SO_BASE_CONVERTER_
