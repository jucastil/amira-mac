/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.DUFOUR (Jun 2002)
**=======================================================================*/

#ifndef _SO_VOLUME_SKIN_DETAIL_
#define _SO_VOLUME_SKIN_DETAIL_

#include <Inventor/details/SoSubDetail.h>
#include <VolumeViz/details/SoVolumeDetail.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVolumeSkinDetail
//
//  Detail about an SoVolumeSkin node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VREXT Stores detail information about a picked voxel or pick ray in a data volume.
 * 
 * @ingroup VolumeVizDetails
 * 
 * @DESCRIPTION
 *   A successful pick operation returns an SoPickedPoint object. If the picked
 *   geometry is an SoVolumeSkin node, use the @B getDetail @b method and cast
 *   the result to this class to get extra information about the the pick.
 *   
 *   SoVolumeSkinDetail returns information about the first (closest)
 *   non-transparent voxel along the pick ray and/or information about all the voxels
 *   intersected by the pick ray (called a profile). For the first non-transparent
 *   voxel (if any) on the pick ray, it returns XYZ position, IJK location, and data
 *   value. For the profile defined by all the intersected voxels, it returns:
 *   
 *   - Profile position in object space (two XYZ points)
 *   
 *   - Profile location in the data volume (two IJK indices)
 *   
 *   - Number of values along the profile
 *   
 *   - Each voxel value and corresponding IJK location
 * 
 * @SEE_ALSO
 *    SoDetail,
 *    SoVolumeDetail,
 *    SoVolumeSkin
 * 
 * 
 */ 

class VOLUMEVIZ_API SoVolumeSkinDetail : public SoVolumeDetail {

  SO_DETAIL_HEADER(SoVolumeSkinDetail);

 public:
  /**
   * Constructor.
   */
  SoVolumeSkinDetail();
  /**
   * Destructor.
   */
  virtual ~SoVolumeSkinDetail();


  //------------------------------------------------------------------------------

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

};

#endif /* _SO_VOLUME_SKIN_DETAIL_ */
