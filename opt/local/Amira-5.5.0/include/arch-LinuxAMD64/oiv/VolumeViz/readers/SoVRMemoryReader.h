/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : J.HUMMEL (Oct 2003)
**=======================================================================*/
#ifndef  _SO_VR_MEMORY_READER_
#define  _SO_VR_MEMORY_READER_

#include <LDM/readers/SoVolumeReader.h>

class SoBufferObject;

/**
 * @VREXT Reads data passed in memory.
 *
 * @ingroup VolumeVizReaders
 *
 * @DESCRIPTION
 *
 *
 *
 */
class VOLUMEVIZ_API SoVRMemoryReader : public SoVolumeReader
{

  SO_FIELDCONTAINER_HEADER(SoVRMemoryReader);

public:

  /**
   * Constructor.
   */
  SoVRMemoryReader();

  /**
   * Constructor. @deprecated 
   * Use default constructor and appropriate setProperties method instead.
   * @DEPRECATED_SINCE_OIV 7.0
   * [OIV-WRAPPER-ARG IN,IN,IN,ARRAY,IN]
   */
  SoDEPRECATED SoVRMemoryReader(const SbBox3f& size, SoDataSet::DataType type, const SbVec3i32& dim, void* internalData, int sigBits = 0);

  /**
   * @deprecated Obsolete version kept for compatibility.
   * @DEPRECATED_SINCE_OIV 6.0
   * [OIV-WRAPPER-ARG IN,IN,IN,IN,ARRAY,IN]
   */
  SoDEPRECATED SoVRMemoryReader(const SbBox3f& size, SoDataSet::DataType type, const SbVec3i32& dim, const SbVec2i32& padding,
                   void* internalData, int sigBits = 0);

  /**
   * @deprecated Obsolete version kept for compatibility.
   * @DEPRECATED_SINCE_OIV 6.0
   * [OIV-WRAPPER-ARG IN,IN,IN,ARRAY,IN]
   */
  SoDEPRECATED SoVRMemoryReader( SbBox3f size, SoDataSet::DataType type, SbVec3s smalldim, void* internalData, int sigBits = 0);

  /**
  * Gets the characteristics (file header) of the data volume. See SoVolumeData.
  * @B size@b is the size of the actual volume. @B type@b is the type of the data.
  * @B dim@b is the dimension of the data.
  * [OIV-WRAPPER-CUSTOM-CODE]
  */
  virtual ReadError getDataChar( SbBox3f &size, SoDataSet::DataType &type,  SbVec3i32 &dim );

  /**
  * New method required by VolumeViz 3.0 when using large volume support.
  * Must copy a rectangular part of an XY slice to the memory pointed to by @B data@b.
  * Slices will not always be read sequentially.
  * [OIV-WRAPPER-CUSTOM-CODE]
  */
  virtual void getSubSlice( const SbBox2i32& subSlice, int sliceNumber, void * data );

  /** 
   * Same as getSubSlice( const SbBox2i32& subSlice, int sliceNumber, void * data )
   * but using SoBufferObject as parameter. 
   */
  virtual void getSubSlice(const SbBox2i32& subSlice, int sliceNumber, SoBufferObject * dataBuffer);

  /**
   * @deprecated No longer used. use void setProperties(const SbBox3f&,SoDataSet::DataType,const SbVec3i32&,const SbVec2i32&, SoBufferObject*,int)
   * [OIV-WRAPPER-ARG IN,IN,IN,IN,ARRAY&STRONG_REF{Normal},IN]
   * @DEPRECATED_SINCE_OIV 8.0
   */
  SoDEPRECATED void setProperties ( const SbBox3f& size, SoDataSet::DataType type, const SbVec3i32 &dim,
                                 const SbVec2i32 &padding, void* internalData, int sigBits);

  /**
   * @deprecated No longer used. use setProperties(const SbBox3f&,SoDataSet::DataType,const SbVec3i32, SoBufferObject*, int)
   * [OIV-WRAPPER-ARG IN,IN,IN,ARRAY&STRONG_REF{Normal},IN]
   * @DEPRECATED_SINCE_OIV 8.0
   */
  SoDEPRECATED void setProperties ( const SbBox3f& size, SoDataSet::DataType type, const SbVec3i32 &dim,
                                 void* internalData, int sigBits);

  /**
   * @deprecated No longer used. use setProperties(SbBox3f,SoDataSet::DataType,SbVec3s,SoBufferObject*,int)
   * [OIV-WRAPPER-ARG IN,IN,IN,ARRAY&STRONG_REF{Normal},IN]
   * @DEPRECATED_SINCE_OIV 8.0
   */
  SoDEPRECATED void setProperties ( SbBox3f size, SoDataSet::DataType type, SbVec3s dim,
                                 void* internalData, int sigBits = 0);

  /**
   * Sets properties of the reader.
   */
  void setProperties ( const SbBox3f& size, SoDataSet::DataType type, const SbVec3i32 &dim,
                                 const SbVec2i32 &padding, SoBufferObject* internalData, int sigBits);

  /** 
   * Sets properties of the reader.
   */
  void setProperties ( const SbBox3f& size, SoDataSet::DataType type, const SbVec3i32 &dim,
                                 SoBufferObject* internalData, int sigBits);

  /** 
   * Sets properties of the reader.
   */
  void setProperties ( SbBox3f size, SoDataSet::DataType type, SbVec3s dim,
                                 SoBufferObject* internalData, int sigBits = 0);
  /**
   * Returns the number of significant bits of the volume data.
   */
  virtual int getNumSignificantBits();

  /**
   * Returns the reader type.
   */
  virtual ReaderType getReaderType ()
  {return MEMORY;};

  /**
  * Should return TRUE if the reader is thread safe. @BR
  * This function is called by VolumeViz when using the multiIO mode (LDM only).
  * LDM multi-threaded data loading can only be used if this method returns TRUE.
  */
  virtual SbBool isThreadSafe() const;

private:
  SbBox3f                m_size;
  SbVec3i32              m_dim;
  SbVec2i32              m_padding;
  SoDataSet::DataType m_type;
  int                    m_headerSize;
  int                    m_bytesPerVoxel;
  SoBufferObject*        m_internalBuffer;
  int                    m_sigBits;
};

#endif // _SO_VR_MEMORY_READER_
