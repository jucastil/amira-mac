/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : M. Heck (Jul 2003)
**=======================================================================*/
#ifndef  _SO_VR_VOX_FILE_READER_
#define  _SO_VR_VOX_FILE_READER_

#include <LDM/readers/SoVolumeReader.h>
#include <VolumeViz/nodes/SoVolumeData.h>


/**
 * @VREXT VOX file reader.
 * 
 * @ingroup VolumeVizReaders
 * 
 * @DESCRIPTION
 * Reader for TeraRecon ".vox" data files (vox1999 format).
 * 
 *   VOX is a volume interchange format defined by TeraRecon Inc.
 *   (www.terarecon.com). The VolumeViz reader can load "Vox1999a"
 *   files containing 8- or 16-bit voxels (first volume only).
 * 
 * 
 */ 
class VOLUMEVIZ_API SoVRVoxFileReader : public SoVolumeReader 
{
  SO_FIELDCONTAINER_HEADER(SoVRVoxFileReader);

 public:
  /** Constructor. */
  SoVRVoxFileReader();

  /**
  * Specifies the path of the file. Returns 0 for success. Any other return
  * value indicates failure.
  */
  virtual int setFilename( const SbString& filename );

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
   * [OIV-WRAPPER-CUSTOM-CODE]
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
   * This method is optional. It returns the number of significant bits of the volume data.
   *
   * If it is not implemented, the default return value is 0, meaning the number of bits
   * depends on the data type. See the last parameter of SoVolumeData::setVolumeData().
   * This method is called immediately after #getDataChar().
   */
  virtual int getNumSignificantBits() 
  { return m_numSigBits; }

  /**
   * Returns the reader type.
   */
  virtual ReaderType getReaderType ()
  {return VOX;};

 private:
  SbBox3f   m_size;
  SbVec3i32 m_dim;
  SoDataSet::DataType m_type;

  int m_offsetToData;
  int m_bytesPerVoxel;

  // Specific data from vox file
  SbString  m_volumeTitle;
  SbString  m_volumeCopyright;
  int       m_volumeCount;
  SbVec3f   m_volumeScale;
  SbVec3f   m_volumePosition;
  char      m_endian;
  SbMatrix  m_volumeMatrix;

  int       m_numSigBits;

  SbString m_userFilename;
};

#endif // _SO_VR_VOX_FILE_READER_
