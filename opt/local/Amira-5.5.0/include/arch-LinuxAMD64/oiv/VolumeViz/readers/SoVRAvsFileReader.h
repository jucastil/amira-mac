/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : G. SEGUIN (Oct 2001)
**=======================================================================*/
#ifndef  _SO_VR_AVS_FILE_READER_
#define  _SO_VR_AVS_FILE_READER_

#include <LDM/readers/SoVolumeReader.h>
#include <VolumeViz/nodes/SoVolumeData.h>


/**
 * @VREXT AVS field file reader.
 * 
 * @ingroup VolumeVizReaders
 * 
 * @DESCRIPTION
 * 
 *     AVS field is a general purpose file format that can contain many
 *     different kinds of data. The VolumeViz file reader can load AVS
 *     field files containing 3-dimensional, uniform data of type "byte".
 * 
 *  
 * 
 */ 
class VOLUMEVIZ_API SoVRAvsFileReader : public SoVolumeReader  
{

  SO_FIELDCONTAINER_HEADER(SoVRAvsFileReader);

public:
  /** Constructor. */
  SoVRAvsFileReader();

  /**
   * Gets the characteristics (file header) of the data volume. See SoVolumeData.
   * @B size@b is the size of the actual volume. @B type@b is the type of the data.
   * @B dim@b is the dimension of the data.
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  ReadError getDataChar( SbBox3f &size, SoDataSet::DataType &type,  SbVec3i32 &dim );

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
  void getSubSlice( const SbBox2i32& subSlice, int sliceNumber, void * data );

  /**
   * Returns the reader type.
   */
  virtual ReaderType getReaderType ()
  {return AVS;};

private:
  SbBox3f   m_size;
  SbVec3i32 m_dim;
  SoDataSet::DataType m_type;

  int m_headerSize;
  int m_bytesPerVoxel;
};

#endif // _SO_VR_AVS_FILE_READER_
