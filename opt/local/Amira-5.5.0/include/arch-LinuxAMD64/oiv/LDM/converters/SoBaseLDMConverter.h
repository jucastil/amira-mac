/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (Apr 2003)
**=======================================================================*/

#ifndef  _SO_LDM_CONVERTER_
#define  _SO_LDM_CONVERTER_

#include <LDM/converters/SoConverter.h>
class SoVolumeReader;

#ifdef _WIN32
#pragma warning( push )
#pragma warning(disable:4251)
#endif

/**
* @LDMEXT Base class for converting data sets into the LDM format.
*
* @ingroup LDMConverters
*
* @DESCRIPTION
*
* This is the base class for converting existing volume data sets into the
* LDM (Large Data Management) format. Normally you will use, for example, the
* derived class SoVolumeConverter to convert volume data.
*
* The LDM converter classes provide many powerful features.  Information common
* to all converter classes is documented in SoConverter, including:
* - Command line parsing for easy creation of stand-alone converter programs.
* - Checkpoint and restart for interrupted conversions.
* - Distributed conversion (to accelerate conversion using a cluster).
* - Multiple subsampling algorithms for creating low resolution tiles.
* - Automatic loading of any supported data format (see SoVolumeData).
* - Conversion of any data format by providing a custom reader (see SoVolumeReader).
* - Optional data compression to reduce disk space.
* - Optional data type conversion, e.g. float to byte.
*
* @SEE_ALSO
*    SoConverter,
*    SoVolumeConverter,
*    SoVolumeReader
*
*
*/
class LDM_API SoBaseLDMConverter : public SoConverter
{

public:
 /**
   * Constructor.
   */
  SoBaseLDMConverter(SbBool isClient = FALSE);

  /**
   * Returns a custom reader according to the given filename and extension. 
   * Returns NULL by default, meaning that SoBaseLDMConverter is configured to run
   * with a predefined reader not a custom one. The method must be overridden in a 
   * derived class to return a user-defined custom reader.
   * @param filename part of the filename without extension.
   * @param fileExt part of the filename after the last '.'
   */
  virtual SoVolumeReader* getReader( const SbString& filename, const SbString& fileExt );

  /**
   * Destructor.
   */
  virtual ~SoBaseLDMConverter();

  
protected:
  SoVolumeReader* m_reader;

/////////////////////// func to define /////////////////
  virtual void instanciateReader(SoConverter::ConverterError& error);
  virtual void setCurrentTimeStep( int curTimeStep ) ;
  virtual void getSubSlice( const SbBox2i32& subSlice, int sliceNumber, void * data ) ;

  //error returned : 0 = ok, 1 = pb = return
  virtual SbBox3f getSize(int& error) ;
  virtual std::vector<SoDataSet::DatumElement> getDatum(int& error) ;
  virtual SbVec3i32 getDimension(int& error) ;
  virtual int getRange( double & rangeMin, double & rangeMax );
  virtual SoVolumeHistogram* getHistogram();
  virtual std::vector<SbVec2d>& getTileMinMax(int numTiles);
  virtual void closeInputFileHandles();

  //if return true output numsigbits in header
  virtual bool getNumSignificantBits(int& numsigbits);

  virtual void  outputHeader( FILE* );
  //////////////////////////////////////////////////////

  /**
   * Called before reading the file. If the return value is NULL, a reader by default will be
   * used according to the extension of the file.
   * If a reader is returned the following methods have to be implemented at least:
   * SoVolumeReader::getDataChar()
   * SoVolumeReader::getSubSlice()
   */
  virtual void sampleTile( const SbVec3i32& tileDim, int border,
                           const void* const octantTile[8],
                           const int octantExists[8],
                           void *parentTile );

  /**
   * Called before reading the file. If the return value is NULL, a reader by default will be
   * used according to the extension of the file.
   * If a reader is returned the following methods have to be implemented at least:
   * SoVolumeReader::getDataChar()
   * SoVolumeReader::getSubSlice()
   */
  virtual void sampleTile( const SbVec3i32& tileDim, int type, int border,
                           const void* const octantTile[8],
                           const int octantExists[8],
                           void *parentTile );

  /**
   * Used to build the low resolution tile using the average algorithm
   * which take one voxel out of two from the child tile, ponderated with
   * the average of the six neighbor voxel
   */
  virtual void sampleAverage( const SbVec3i32& tileDim, int type, int border,
                              const void* const octantTile[8], const int octantExists[8],
                              void *parentTile );

  /**
   * Used to build the low resolution tile using the decimation algorithm
   * which take one voxel out of two from the child tile
   */
  virtual void sampleDecimation(const SbVec3i32& tileDim, int dataType, int border,
                                const void* const octantTile[8],
                                const int octantExists[8],
                                void *parentTile );

  virtual void adjustParameters();

SoINTERNAL public:
  static void sampleAverageS(
    int pondCoef,const SbVec3i32& tileDim, int type,
    const void* const childTile,
    void *parentTile,
    int octant, int border, const int octantExists[8]);

  static void sampleDecimationS(
    const SbVec3i32& tileDim, int type,
    const void* const childTile,
    void *parentTile,
    int octant, int border, const int octantExists[8]);

private:
  template <typename T>
  static void sampleAverage(int pondCoef, const SbVec3i32& tileDim, const void* const childTile,
                     void *parentTile, int octant, int border, const int octantExists[8]);

  static void sampleAverageRGBA(int pondCoef, const SbVec3i32& tileDim, const void* const childTile,
                         void *parentTile, int octant, int border, const int octantExists[8]);
  template <typename T>
  static void sampleDecimation(const SbVec3i32& tileDim, const void* const childTile,
                        void *parentTile, int octant, int border, const int octantExists[8]);

  static void getShiftAndHalfTileDim(SbVec2i32& shiftParentOctant,
                              SbVec3i32& halfTileDim,
                              const SbVec3i32& tileDim,
                              int octant, int border);

  static void getRatio ( SbVec3f &ratio,
                  SbVec3i32 &shiftOctant, 
                  SbVec3i32 tileDim, 
                  SbVec3i32 halfTileDim, 
                  int octant, int border,
                  const int octantExists[8]);

  SoDataSet::DataType    m_dataType; //one data only for this type of conversion
  bool                   m_outputNumSigBits;

};

inline SoVolumeReader* 
SoBaseLDMConverter::getReader( const SbString& , const SbString& )
{
  return NULL;
}

#if defined(_WIN32)
#pragma warning( pop )
#pragma warning(disable:4251)
#endif

#endif // _SO_LDM_CONVERTER_
