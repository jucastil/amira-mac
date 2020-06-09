/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : G. SEGUIN (Oct 2001)
**=======================================================================*/
#ifndef  _SO_VR_GENERIC_FILE_READER_
#define  _SO_VR_GENERIC_FILE_READER_

#include <LDM/readers/SoVolumeReader.h>
#include <VolumeViz/nodes/SoVolumeData.h>


/**
 * @VREXT Generic file reader.
 * 
 * @ingroup VolumeVizReaders
 * 
 * @DESCRIPTION
 * 
 * 
 * 
 */ 
class VOLUMEVIZ_API SoVRGenericFileReader : public SoVolumeReader  
{
  SO_FIELDCONTAINER_HEADER(SoVRGenericFileReader);

 public:
  /** Constructor. */
  SoVRGenericFileReader(); 

  /**
   * Gets the characteristics (file header) of the data volume. See SoVolumeData.
   * @B size@b is the size of the actual volume. @B type@b is the type of the data.
   * @B dim@b is the dimension of the data.
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  virtual ReadError getDataChar( SbBox3f &size, SoDataSet::DataType &type,  SbVec3i32 &dim ) {
    size = m_size;
    type = m_type;
    dim = m_dim;
    return RD_NO_ERROR;
  };

  #ifdef OIV_NET_DOC
 /**
   * New method required by VolumeViz 3.0 when using large volume support.
   * Must copy a rectangular part of an XY slice to the memory referenced by @B data@b.
   * Slices will not always be read sequentially.
   */
 #else
  /**
   * New method required by VolumeViz 3.0 when using large volume support.
   * Must copy a rectangular part of an XY slice to the memory pointed to by @B data@b.
   * Slices will not always be read sequentially.
   */
#endif
  virtual void getSubSlice( const SbBox2i32& subSlice, int sliceNumber, void * data );

  /**
   * Since the format is raw data, it is necessary to specify 
   * the dimension and data size of the volume. 
   * You can also specify a header size to add support for your own file format.
   */
  void setDataChar( const SbBox3f &size, const SoDataSet::DataType &type, const SbVec3i32 &dim, int headerSize = 0) {
    m_size = size;
    m_type = type;
    m_dim = dim;
    m_bytesPerVoxel = SoVolumeData::dataSize( type );
    m_headerSize = headerSize;
  }

  /**
   * Since the format is raw data, it is sometime necessary to specify 
   * the number of time steps. 
   */
  void setNumTimeSteps( int numTimeSteps ) {
    m_numTimeSteps = numTimeSteps;
  }

  /**
   * Obsolete version retained for compatibility
   * [OIV-WRAPPER-NOT-WRAP]
   */
  void setDataChar( SbBox3f &size, SoDataSet::DataType &type, SbVec3s &smalldim, int headerSize = 0) {
    SbVec3i32 dim(smalldim[0],smalldim[1],smalldim[2]);
    setDataChar( size, type, dim, headerSize );
  }

  /**
   * Returns the reader type.
   */
  virtual ReaderType getReaderType ()
  {return GENERIC;};

  ////////////////////////////////////////////////////////////////////////////////////////////////
  // deprecated methods
  //

  /** @deprecated No longer used. Use void setDataChar( const SbBox3f&, SoDataSet::DataType&, const SbVec3i32&, int )
   * @DEPRECATED_SINCE_OIV 6.0
   */
  SoDEPRECATED virtual void setDataChar( const SbBox3f &size, const SoDataSet::DataType &type, const SbVec3s &dim, int headerSize = 0)
  {
    SbVec3i32 dimI32( dim[0], dim[1], dim[2] );
    setDataChar( size, type, dimI32, headerSize );
  }

 protected:
  SbBox3f   m_size;
  SbVec3i32 m_dim;
  SoDataSet::DataType m_type;

  int m_headerSize;
  int m_bytesPerVoxel;
};

#endif // _SO_VR_GENERIC_FILE_READER_
