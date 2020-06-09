/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : J. Hummel (Apr 2003)
**=======================================================================*/
#ifndef  _SO_VR_LDM_FILE_READER_
#define  _SO_VR_LDM_FILE_READER_

#include <Inventor/STL/string>
#include <LDM/readers/SoLDMReader.h>
#include <Inventor/threads/SbThread.h>
#include <Inventor/STL/vector>

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
//Disable Deprecated warnings because call to
//these functions are needed for compatibility
#pragma warning(disable:4996)
#endif

class SbThreadMutex;
class SiBitFile;


/**
 * @LDMEXT LDM file reader.
 *
 * @ingroup LDMReaders
 *
 * @DESCRIPTION
 *
 * LDM is a format for storing hierarchical multi-resolution volume data,
 * defined by VSG. VolumeViz includes a utility program that can
 * convert other formats (supported by VolumeViz) into this format.
 * Preprocessing volume data into this format provides the maximum
 * benefits from the VolumeViz large data management (LDM) features.
 *
 * The default VolumeViz LDM file format is based on an octree topology.
 * The data is stored in tiles of different subsampling resolution.
 *
 * The first tile in the file represents the entire volume at its lowest resolution and
 * corresponds to the root of the octree. The next 8 tiles represent octants
 * of the entire volume at a lower subsample step. There is another set of 8 tiles for
 * each of these tiles, and so on, until reaching tiles
 * of full resolution.
 *
 * The tile index starts at 0 for the root and increments linearly
 * into the octree (1 to 8 for octree children, 9 to 16 for children of tile 1, and so on).
 *
 * The data of a tile is accessed with the #readTile function by passing an index and
 * allocated buffer. This function is called by the SoLDMTileManager
 * when it needs to load a tile in main memory.
 *
 * Note: SoLDMTileManager is declared SoEXTENDER and is intended for advanced users.
 * For details see its header file.
 *
 *
 */
class LDM_API SoVRLdmFileReader : public SoLDMReader  
{
  SO_FIELDCONTAINER_HEADER(SoVRLdmFileReader);

  using SoLDMReader::getDataChar;

public:
  /** Default constructor. */
  SoVRLdmFileReader();

  /**
   * Constructor.
   * @deprecated Provided for compatibility only. Use default constructor.
   * @DEPRECATED_SINCE_OIV 7.0
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  SoDEPRECATED SoVRLdmFileReader(SoDataSet* ds);

  /**
   * Gets the characteristics (file header) of the data volume. See SoVolumeData.
   * @B size@b is the size of the actual volume. @B type@b is the type of the data.
   * @B dim@b is the dimension of the data.
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  virtual ReadError getDataChar( SbBox3f &size, SoDataSet::DataType &type,  SbVec3i32 &dim );


  /**
   * Returns the minimum and maximum data values (obsolete).
   * [OIVJAVA-WRAPPER NAME{getIntMinMax}]
   */
  virtual SbBool getMinMax(int & min, int & max);

  /**
   * Returns the minimum and maximum data values.
   */
   virtual SbBool getMinMax(int64_t & min, int64_t & max);

  /**
   * Returns the minimum and maximum data values (for float values).
   * [OIVJAVA-WRAPPER NAME{getDoubleMinMax}]
   */
  virtual SbBool getMinMax(double & min, double & max);

  /**
   *
   * Returns the distribution of data values, i.e., the number of voxels per data value.
   * numVox(0) is the number of voxels with value 0, numVox(1) is the number of voxels
   * with value 1, and so on.
   */
  virtual SbBool getHistogram(std::vector<int64_t>& numVox);

  /**
   *
   * Returns the number of significant bits.
   */
  virtual int getNumSignificantBits() { return m_numSignificantBits; }

  /** 
   * @deprecated No longer used. use getSubSlice( const SbBox2i32&, int sliceNumber, SoBufferObject* )
   * @DEPRECATED_SINCE_OIV 8.0
   */ 
  SoDEPRECATED void getSubSlice( const SbBox2i32& subSlice, int sliceNumber, void * data );

 SoINTERNAL public:

  //returns histo and values. bool returned whether some values are set or not
  virtual SbBool getHistogramAndValues(std::vector<int64_t>& numVox, std::vector<double>& values);

  /** 
  * Requests that the input data be converted (if necessary) to the specified data type. @BR
  * This allows, for example, conversion of float data to unsigned byte in order to reduce
  * system memory usage.  If doChange is FALSE no type conversion is applied.
  * Always returns TRUE.
  */
  virtual SbBool setOutputDataType( SbBool doChange, SoDataSet::DataType type );

  /**
  * Should return TRUE if the reader is thread safe. @BR
  * This function is called by VolumeViz when using the multiIO mode (LDM only).
  * LDM multi-threaded data loading can only be used if this method returns TRUE.
  */
  virtual SbBool isThreadSafe() const;

 protected:
    bool  m_isDataSigned;
    bool  m_isDataFloat;

    SoDataSet::DataType m_type;

    int m_numSignificantBits;

    //min, max
    int64_t m_dataMin , m_dataMax;
    double  m_dataMinD, m_dataMaxD;

    //histo
    std::vector<int>     m_entries;
    std::vector<int64_t> m_values;
    std::vector<double>  m_valuesD;
    std::vector<int64_t> m_numVoxels;

    virtual int handleHeader(TiXmlElement *);

private:
    void internalInit();
    SoDataSet* m_ds;
    bool m_changeFormat;
    SoDataSet::DataType m_typeOut;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // _SO_VR_LDM_FILE_READER_
