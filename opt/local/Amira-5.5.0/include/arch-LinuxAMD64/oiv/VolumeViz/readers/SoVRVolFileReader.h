/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : G. SEGUIN (Sep 2001)
**=======================================================================*/
#ifndef  _SO_VR_VOL_FILE_READER_
#define  _SO_VR_VOL_FILE_READER_

#include <LDM/readers/SoVolumeReader.h>
#include <VolumeViz/nodes/SoVolumeData.h>


/**
 * @VREXT VOL file reader.
 * 
 * @ingroup VolumeVizReaders
 * 
 * @DESCRIPTION
 * 
 * VOL is a simple volume interchange format (see "Introduction to
 * Volume Rendering", Lichtenbelt, Crane, Naqvi, 1998). The VolumeViz
 * reader can load files containing 8- or 16-bit voxels.
 * 
 * The following is a slightly simplified description of the VOL file format.
 *
 * All values in a VOL file are binary format, stored in "big-endian" order.
 * In other words, values can used directly on most UNIX machines (SPARC,
 * MIPS, PA-RISC, etc), but must be byte swapped on most Windows and Linux
 * (X86) machines.
 *
 * A VOL file consists of a variable length header followed by data values.
 * The VolumeViz reader looks at the first seven or ten header values
 * (depending on the value of magicNumber). All values in the header are 4
 * bytes long and are 32 bit integer or float as listed below.  The header
 * contains the total length of the header in bytes and the data values
 * begin at this offset in the file.  Data values are either 1 or 2 bytes
 * long (8- or 16- bit integers). Data values are stored as a stack of
 * images, in other words Z slices (X increasing fastest, then Y, then Z).
 *
 * The header consists of:
 * - magicNumber  (int) should be 192837465 or 192837466
 * - headerSize   (int) in bytes
 * - width        (int) in voxels
 * - height       (int) in voxels
 * - depth        (int) in voxels
 * - bitsPerVoxel (int) either 8 or 16 are valid
 * - indexBits    (int) not used
 *
 * If "magicNumber" equals 192837466 (decimal) then header also contains
 * three scale factors used to define nonuniform voxel spacing:
 * - scaleX       (float) 
 * - scaleY       (float)
 * - scaleZ       (float)
 * 
 *  
 * 
 */ 
class VOLUMEVIZ_API SoVRVolFileReader : public SoVolumeReader  
{
  SO_FIELDCONTAINER_HEADER(SoVRVolFileReader);

 public:
  /** Constructor. */
  SoVRVolFileReader();

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
   * Returns the reader type.
   */
  virtual ReaderType getReaderType ()
  {return VOL;};

private:
  SbBox3f   m_size;
  SbVec3i32 m_dim;
  SoDataSet::DataType m_type;

  int m_headerSize;
  int m_bytesPerVoxel;
};

#endif // _SO_VR_VOL_FILE_READER_
