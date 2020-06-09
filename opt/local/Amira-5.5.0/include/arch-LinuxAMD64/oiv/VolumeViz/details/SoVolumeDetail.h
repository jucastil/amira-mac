/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : P. ESTRADE (Dec 2000)
** Modified by : T.DUFOUR (MMM yyyy)
**=======================================================================*/

#ifndef _SO_VOLUME_DETAIL_
#define _SO_VOLUME_DETAIL_

#include <Inventor/details/SoSubDetail.h>
#include <LDM/nodes/SoTransferFunction.h>
#include <Inventor/SbVec.h>
#include <Inventor/SbLine.h>
#include <VolumeViz/nodes/SoVolumeDataDrawStyle.h>
#include <LDM/elements/SoDataRangeElement.h>

class SoVolumeData;
class SoROI;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVolumeDetail
//
//  Abstract class for SoVolumeRenderDetail and SoVolumeSkinDetail nodes.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VREXT Base class for detail information about picking in a data volume.
 *
 * @ingroup VolumeVizDetails
 *
 * @DESCRIPTION
 *   A successful pick operation returns an SoPickedPoint object. If the picked
 *   geometry is an SoVolumeSkin or SoVolumeRender, use the @B getDetail @b method
 *   and cast the result to the appropriate class (SoVolumeSkinDetail or
 *   SoVolumeRenderDetail) to get extra information about the location of the pick.
 *
 *   SoVolumeDetail returns information about the first (closest)
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
 *   This class returns information about the data values in the picked voxels.
 *   SoVolumeRenderDetail also returns information about the mapped RGBA colors
 *   of the picked voxels.
 *
 * @SEE_ALSO
 *    SoDetail,
 *    SoVolumeRenderDetail,
 *    SoVolumeSkinDetail,
 *    SoVolumeRender,
 *    SoVolumeSkin
 *
 *
 */

class VOLUMEVIZ_API SoVolumeDetail : public SoDetail {

  SO_DETAIL_HEADER(SoVolumeDetail);

 public:
  /**
   * Constructor.
   */
  SoVolumeDetail();
  /**
   * Destructor.
   */
  virtual ~SoVolumeDetail();

  /**
   * Returns the profile position in object space (world coordinates).
   *
   * Specifically the @I profile@i parameter contains the XYZ coordinates of the
   * first and last points on the profile.
   */
  void getProfileObjectPos(SbVec3f profile[2]) const;

  /**
   * Returns the number of values along the profile and the profile position in data
   * space (voxel coordinates).
   *
   * Specifically the @I profile@i parameter contains the IJK coordinates of the
   * first and last points on the profile.  The number of values is the number of
   * of voxels intersected by the pick ray.
   * [OIVJAVA-WRAPPER-RETURN-TYPE NO_WRAP]
   * [OIVJAVA-WRAPPER DUPLICATE{getProfileNumValues}]
   * [OIVJAVA-WRAPPER-ARG APPLY_TO{getProfileNumValues} NO_WRAP]
   */
  int  getProfileDataPos(SbVec3i32 profile[2]) const;

  /**
   * Returns the @B index@b'th value (as an integer) and its position in object and data space.
   *
   * The number of values along the profile can be queried using the 
   * #getProfileDataPos() method.  However @B index @b is automatically clamped
   * to the valid range of values.
   *
   * If @B realValue @b is TRUE, VolumeViz will return the actual voxel value from 
   * the full resolution data. Note that this may require a read from disk if full
   * resolution data is not currently in memory. If FALSE, VolumeViz will return the
   * voxel value from the (possibly subsampled) data currently in memory.
   * [OIV-WRAPPER-ARG IN,OUT,OUT,IN]
   * [OIVJAVA-WRAPPER PACK{ProfileValue}]
   * [OIVJAVA-WRAPPER-RETURN-TYPE NAME{voxelValue}]
   */
  int64_t getProfileValue(int index, SbVec3i32 &pos, SbVec3f *objPos = 0, SbBool realValue = FALSE) const;

  /**
   * Returns the @B index@b'th value (as a double) and its position in object and data space.
   *
   * The number of values along the profile can be queried using the 
   * #getProfileDataPos() method.  However @B index @b is automatically clamped
   * to the valid range of values.
   *
   * If @B realValue @b is TRUE, VolumeViz will return the actual voxel value from 
   * the full resolution data. Note that this may require a read from disk if full
   * resolution data is not currently in memory. If FALSE, VolumeViz will return the
   * voxel value from the (possibly subsampled) data currently in memory.
   * [OIV-WRAPPER-ARG IN,OUT,OUT,IN]
   * [OIVJAVA-WRAPPER PACK{ProfileValueD}]
   * [OIVJAVA-WRAPPER-RETURN-TYPE NAME{voxelValue}]
   */
  double  getProfileValueD(int index, SbVec3i32 &pos, SbVec3f *objPos, SbBool realValue = FALSE) const;

  /**
   * Returns the integer value of the first non-transparent voxel along the pick
   * ray (if any) and its position in object and data space. Returns FALSE if not found.
   *
   * If @B realValue @b is TRUE, VolumeViz will return the actual voxel value from 
   * the full resolution data. Note that this may require a read from disk if full
   * resolution data is not currently in memory. If FALSE, VolumeViz will return the
   * voxel value from the (possibly subsampled) data currently in memory.
   * [OIV-WRAPPER-ARG OUT,OUT,OUT,IN]
   * [OIVJAVA-WRAPPER PACK{TransparentLongValue}]
   */
  virtual SbBool getFirstNonTransparentValue(int64_t &value, SbVec3i32 &pos, SbVec3f *objPos = 0, SbBool realValue = FALSE) const;

  /**
   * Returns the floating point value of the first non-transparent voxel along the pick
   * ray (if any) and its position in object and data space. Returns FALSE if not found.
   *
   * If @B realValue @b is TRUE, VolumeViz will return the actual voxel value from 
   * the full resolution data. Note that this may require a read from disk if full
   * resolution data is not currently in memory. If FALSE, VolumeViz will return the
   * voxel value from the (possibly subsampled) data currently in memory.
   * [OIV-WRAPPER-ARG OUT,OUT,OUT,IN]
   * [OIVJAVA-WRAPPER NAME{getFirstNonTransparentDoubleValue},PACK{TransparentDoubleValue}]
   */
  virtual SbBool getFirstNonTransparentValue(double &value, SbVec3i32 &pos, SbVec3f *objPos = 0, SbBool realValue = FALSE) const;

  /**
   * Returns an instance that is a copy of this instance. The caller
   * is responsible for deleting the copy when done.
   */
  virtual SoDetail * copy() const;

  ////////////////////////////////////////////////////////////////////////////////////////////////
  // deprecated methods
  //

  /** @deprecated No longer used. Use getProfileDataPos( SbVec3i32 profile[2] )
   *  @DEPRECATED_SINCE_OIV 6.0
   */
  SoDEPRECATED int getProfileDataPos(SbVec3s profile[2] = 0) const
  {
    SbVec3i32 profileI32[2];
    int rv = getProfileDataPos( profileI32 );
    if (profile) {
      profile[0].setValue( (short)profileI32[0][0], (short)profileI32[0][1], (short)profileI32[0][2] );
      profile[1].setValue( (short)profileI32[1][0], (short)profileI32[1][1], (short)profileI32[1][2] );
    }
    return rv;
  };

  /** @deprecated No longer used. Use getProfileValue(int, SbVec3i32*, SbVec3f*, SbBool)
   *  @DEPRECATED_SINCE_OIV 6.0
   *  [OIV-WRAPPER-NO-WRAP]
   */
  SoDEPRECATED int64_t getProfileValue(int index, SbVec3s *pos = 0, SbVec3f *objPos = 0, SbBool realValue = FALSE) const
  {
    SbVec3i32 posI32;
    int64_t rv = getProfileValue( index, posI32, objPos, realValue );
    if (pos)
      pos->setValue( (short)posI32[0], (short)posI32[1], (short)posI32[2] );
    return rv;
  };

  /** @deprecated No longer used. Use getFirstNonTransparentValue( unsigned int*, SbVec3i32*, SbVec3f*, SbBool )
   *  @DEPRECATED_SINCE_OIV 6.0
   *  [OIV-WRAPPER-NO-WRAP]
   */
  SoDEPRECATED virtual SbBool getFirstNonTransparentValue(unsigned int *value, SbVec3s *pos = 0, SbVec3f *objPos = 0, SbBool flag = FALSE) const
  {
    int64_t   valueI64;
    SbVec3i32 posI32;
    SbBool rc = getFirstNonTransparentValue( valueI64, posI32, objPos, flag );
    *value = (unsigned int)valueI64;
    if (pos)
      pos->setValue( (short)posI32[0], (short)posI32[1], (short)posI32[2] );
    return rc;
  };

  //
  // end deprecated methods
  ////////////////////////////////////////////////////////////////////////////////////////////////

  //------------------------------------------------------------------------------

 SoEXTENDER public:
  void setDetails(SbLine line, SoVolumeData *vd, SoTransferFunction *tf, SoROI *r);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  /** Set pair of dataset/id for this detail */
  inline void setDataSetIdPairList(const SoLDM::DataSetIdPairList& dsPairList) { m_dsPairList = dsPairList; }

  /** Set pair of dataset/id for this detail */
  inline void setDrawStyleMap(const SoVolumeDataDrawStyle::MaskDrawStyleValueMap& styleMap) { m_styleMap = styleMap; }

  /** Set the transfer function list and the id of the tf used for intersections*/
  void setTransferFunctionList(const std::vector<SoTransferFunction*>& tfList, int intersectionTfId);

  /** Set transfer function list */
  inline void setIsovalueMap(const SoVolumeDataDrawStyle::IsovalueMap& isomap) { m_isoMap = isomap; }

  /** Set transfer function list */
  inline void setDataRangeMap(const SoDataRangeElement::DataRangeIdMap& dataRangeMap) { m_dataRangeMap = dataRangeMap; }

  /** Transparency of the volume data */
  inline void setVolumeRenderTransparency(float transparency) { m_volumeRenderAlpha = SbMathHelper::Max(1.0f-transparency, 0.f); }

 protected:

   /** Copy detail into this */
   void copy(const SoVolumeDetail* detail);

   // members that save set<XXX> call parameters.
   // and used by computeProfile() call.
  SbLine              m_rayLine;
  SoVolumeData       *m_volData;
  SoTransferFunction *m_trFunc;
  SoROI              *m_roi;
  SoLDM::DataSetIdPairList m_dsPairList;
  SoVolumeDataDrawStyle::MaskDrawStyleValueMap m_styleMap;
  std::vector<SoTransferFunction*> m_tfList;
  SoVolumeDataDrawStyle::IsovalueMap m_isoMap;
  int m_tfIntersectionId;
  SoDataRangeElement::DataRangeIdMap m_dataRangeMap;
  
  /** Transparency of the material applied on volume render style */
  float m_volumeRenderAlpha;

  // vars setup by setup computeProfile
  // which is called only when a get function is called (this is why it is mutable)
  mutable SbBool              m_valueAvailable;
  mutable SbVec3f             m_profileObjectPos[2];
  mutable SbVec3i32           m_profileDataPos[2];
  mutable int                 m_numValues;
  /** Axis of the profile with the biggest number of values*/
  mutable int                 m_valueAxis;

  void computeProfile() const;

};

#endif /* _SO_VOLUME_DETAIL_ */
