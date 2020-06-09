/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : G. SEGUIN (Nov 2001)
**=======================================================================*/
#ifndef  _SO_VR_AM_FILE_READER_
#define  _SO_VR_AM_FILE_READER_

#include <LDM/readers/SoVolumeReader.h>
#include <VolumeViz/nodes/SoVolumeData.h>


/**
 * @VREXT Am file reader.
 * 
 * @ingroup VolumeVizReaders
 * 
 * @DESCRIPTION
 * 
 * AmiraMesh file format. 
 * 
 *   Amira mesh is a general purpose file format that can contain many
 *   different kinds of data. The VolumeViz file reader can load Amira
 *   mesh files containing a 3-dimensional "Lattice" data object with
 *   uniform coordinates and any data type.
 * 
 * 
 */ 
class VOLUMEVIZ_API SoVRAmFileReader : public SoVolumeReader
{

  SO_FIELDCONTAINER_HEADER(SoVRAmFileReader);

 public:
  /** Constructor. */
  SoVRAmFileReader(); 

  /**
   * Gets the characteristics (file header) of the data volume. See SoVolumeData.
   * @B size@b is the size of the actual volume. @B type@b is the type of the data.
   * @B dim@b is the dimension of the data.
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  virtual ReadError getDataChar( SbBox3f &size, SoDataSet::DataType &type,  SbVec3i32 &dim );

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
   * Returns the reader type.
   */
  virtual ReaderType getReaderType ()
  {return AM;};

  int getHeaderSize();

  /**
   * Returns TRUE if the data set contains RGBA color values.
   */
  virtual SbBool isRGBA() const;

 private:
  SbVec3i32 m_dim;
  SbBox3f m_size;
  SoDataSet::DataType m_type;

  int m_headerSize;
  int m_bytesPerVoxel;
  bool m_isLittleEndian;
  bool m_isInitialized;
};

#endif // _SO_VR_AM_FILE_READER_
