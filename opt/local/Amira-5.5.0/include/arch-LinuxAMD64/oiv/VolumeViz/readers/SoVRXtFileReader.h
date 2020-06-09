/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.DUFOUR (Jul 2004)
**=======================================================================*/
#ifndef  _SO_VR_XT_FILE_READER_
#define  _SO_VR_XT_FILE_READER_

#include <LDM/readers/SoVolumeReader.h>
#include <VolumeViz/nodes/SoVolumeData.h>


/**
 * @VREXT XT file reader.
 * 
 * @ingroup VolumeVizReaders
 * 
 * @DESCRIPTION
 * Reader for Total ".xt" data files.
 * 
 *   XT is a volume data format defined by Total
 *   (www.total.com).
 * 
 * 
 */ 
class VOLUMEVIZ_API SoVRXtFileReader : public SoVolumeReader 
{
   SO_FIELDCONTAINER_HEADER(SoVRXtFileReader);

 public:

  SoVRXtFileReader();
  /** [OIV-WRAPPER-CUSTOM-CODE] */
  virtual ReadError getDataChar( SbBox3f &size, SoDataSet::DataType &type,  SbVec3i32 &dim );
  /** [OIV-WRAPPER-CUSTOM-CODE] */
  virtual void getSubSlice( const SbBox2i32& subSlice, int sliceNumber, void * data );

 private:

  SbVec3i32 m_dim;
  int       m_numBytes;
  bool      m_signed;
  int       m_headerSize;

};

#endif // _SO_VR_XT_FILE_READER_
