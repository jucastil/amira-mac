/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.DUFOUR (Jun 2002)
**=======================================================================*/

#ifndef _SO_VOLUME_RENDER_DETAIL_
#define _SO_VOLUME_RENDER_DETAIL_

#include <Inventor/details/SoSubDetail.h>
#include <VolumeViz/details/SoVolumeDetail.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVolumeRenderDetail
//
//  Detail about an SoVolumeRender node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VREXT Stores detail information about a picked voxel or pick ray in a data volume.
 *
 * @ingroup VolumeVizDetails
 *
 * @DESCRIPTION
 *   A successful pick operation returns an SoPickedPoint object. If the picked
 *   geometry is an SoVolumeRender node, use the @B getDetail @b method and cast
 *   the result to this class to get extra information about the the pick.
 *
 *   SoVolumeRenderDetail returns information about the first (closest)
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
 *   Use the methods in SoVolumeDetail to get information about the data values
 *   of the picked voxels.  Use the getRgba... methods in this class to get information
 *   about the mapped RGBA colors of the picked voxels.  Because these methods
 *   return colors, they always return information based on the (possibly
 *   subsampled) tiles currently in memory.
 *
 * @SEE_ALSO
 *    SoDetail,
 *    SoVolumeDetail,
 *    SoVolumeRender
 *
 *
 */

class VOLUMEVIZ_API SoVolumeRenderDetail : public SoVolumeDetail {

  SO_DETAIL_HEADER(SoVolumeRenderDetail);

 public:
  /**
   * Constructor.
   */
  SoVolumeRenderDetail();
  /**
   * Destructor.
   */
  virtual ~SoVolumeRenderDetail();

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
  virtual SbBool getFirstNonTransparentValue(int64_t &value, SbVec3i32 &pos, SbVec3f *pos3D = 0, SbBool realValue = FALSE) const;

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
  virtual SbBool getFirstNonTransparentValue(double &value, SbVec3i32 &pos, SbVec3f *pos3D = 0, SbBool realValue = FALSE) const;

  /**
   * Returns the number of volume masks applied to the first non-transparent voxel.
   *
   * If @B realValue @b is TRUE, VolumeViz will return the actual value from
   * the full resolution data. Note that this may require a read from disk if full
   * resolution data is not currently in memory. If FALSE, VolumeViz will return the
   * value from the (possibly subsampled) data currently in memory.
   */
  size_t getMaskCount(SbBool realValue = FALSE) const;

  /**
   * Returns the i-th volume mask applied to the first non-transparent voxel.
   *
   * @B index @b must be in the valid range returned by #getMaskCount().
   *
   * If @B realValue @b is TRUE, VolumeViz will return the actual value from
   * the full resolution data. Note that this may require a read from disk if full
   * resolution data is not currently in memory. If FALSE, VolumeViz will return the
   * value from the (possibly subsampled) data currently in memory.
   */
  SoLDM::DataSetIdPair getMask(size_t index, SbBool realValue = FALSE)  const;

  /**
   * Returns the style applied to the first non-transparent voxel (and its isovalue
   * if the style is SoVolumeDataDrawStyle::ISOSURFACE). @BR
   *
   * If @B realValue @b is TRUE, VolumeViz will return the actual value from
   * the full resolution data. Note that this may require a read from disk if full
   * resolution data is not currently in memory. If FALSE, VolumeViz will return the
   * value from the (possibly subsampled) data currently in memory.
   */
  void getVoxelStyleAndIsoValue(SoVolumeDataDrawStyle::DrawStyle& style, double &iso, SbBool realValue = FALSE)  const;

  /**
  * Returns the RGBA value, object space position, data space position
  * and tileId for each voxel intersected by the pick ray.
  * Voxels with a alpha value less or equal to opacityThreshold are ignored.
  * Values returned are based on the (possibly subsampled) tiles currently in memory.
  */
  void getRgbaValues(std::vector<SbVec4ub>& rgbaValues, std::vector<SbVec3f>& objectPos,
                     std::vector<SbVec3i32>& dataPos, std::vector<SoLDMTileID>& tileIds,
                     float opacityThreshold = -1.f) const;

  /**
  * Returns the RGBA value and object space position of each voxel intersected by the pick ray.
  * Plus their object space position.
  * Voxels with a alpha value less or equal to opacityThreshold are ignored.
  * Values returned are based on the (possibly subsampled) tiles currently in memory.
  */
  void getRgbaValues(std::vector<SbVec4ub>& rgbaValues, std::vector<SbVec3f>& objectPos, float opacityThreshold = -1.f) const;

  /**
  * Returns the RGBA value of each voxel intersected by the pick ray.
  * Voxels with a alpha value less or equal to opacityThreshold are ignored.
  * Values returned are based on the (possibly subsampled) tiles currently in memory.
  */
  void getRgbaValues(std::vector<SbVec4ub>& rgbaValues, float opacityThreshold = -1.f) const;

  /**
  * Returns the RGBA value and data space position of each voxel intersected by the pick ray.
  * Voxels with a alpha value less or equal to opacityThreshold are ignored.
  * Values returned are based on the (possibly subsampled) tiles currently in memory.
  */
  void getRgbaValues(std::vector<SbVec4ub>& rgbaValues, std::vector<SbVec3i32>& dataPos, float opacityThreshold = -1.f) const;

  /**
  * Returns the tileID of each voxel intersected by the pick ray.
  * Values returned are based on the (possibly subsampled) tiles currently in memory.
  */
  const std::vector<SoLDMTileID>& getRgbaValuesTileIds() const;

  /**
  * Returns an instance that is a copy of this instance. The caller
  * is responsible for deleting the copy when done.
  */
  virtual SoDetail * copy() const;

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  /** Set rgba values crossing the ray*/
  void setRgbaValues(const std::vector<SbVec4ub>& rgbaValues, const SbVec3f& enterPoint, const SbVec3f& exitPoint);

protected:
  using SoVolumeDetail::copy;

private:
  enum CachedMode
  {
    NOT_CACHED,
    REAL_VALUE,
    IN_MEMORY_VALUE
  };

  /** Map between a dataset id and a bit */
  typedef std::map<int, bool> MaskValueMap;

  /** Return the data position of the given value */
  SbVec3i32 computePosOfProfileValue(int index) const;

  /** Return true if more than one mask has a non zero value */
  bool hasIntersection(const MaskValueMap& maskValueMap) const;

  /**
   * Return true if there is a opaque voxel according to the current mask style and position
   * @param volDataValue is the voxel value of the volume data
   * @param nextVolDataValue is the voxel value of the volume data at the next position along the ray
   * @param curMaskPair is the mask/id pair of the mask currently traversed (S_INTERSECTION_KEY if it is
   * an intersection)
   * @param onVolumeBoundary is true if the voxel is on a volume's boundary
   * @param curPosMaskValue map an dataset id and a mask bit
   * @param curPosMaskValue map an dataset id and a mask bit at the next position along the ray
   */
  template<typename T>
  bool isOpaqueVoxel(T volDataValue, T nextVolDataValue, const SoLDM::DataSetIdPair& curMaskPair,
                     bool onVolumeBoundary, const MaskValueMap& curPosMaskValue,
                     const MaskValueMap& nextPosMaskValue);

  /** Generic implementation of getFirstNonTransparentValue  */
  template<typename T>
  SbBool getFirstNonTransparentValueTemplate(T &value, SbVec3i32 &pos,
                                             SbVec3f *objPos, SbBool realValue);

  /** Return true if picking infos must be recomputed */
  bool needCacheUpdate(bool realValue) const;

  /** Return true if there is a iso value between value and prevValue. The iso value is put in iso */
  template<typename T>
  static bool isCrossingIso(const SoVolumeDataDrawStyle::IsovalueVec& isoValues, T value, T nextValue, float& iso);

  /** Return true if the volume rendered voxel with given value is opaque*/
  template<typename T>
  bool isVolumeRenderedVoxelOpaque(SoTransferFunction* tf, T value) const;

  /** Return true if the ith picked voxel is opaque */
  bool isOpaqueVoxel(size_t index);

  /** Return datarange for given dsIdPair */
  SoDataRange* getDataRange(const SoLDM::DataSetIdPair& dsIdPair) const;

  /** List of masks applied on the first non transparent voxel */
  mutable SoLDM::DataSetIdPairList m_volumeMaskList;

  /** Style of the first non transparent voxel */
  mutable SoVolumeDataDrawStyle::DrawStyle m_voxelStyle;

  /** If style is iso, it is the picked iso value*/
  mutable float m_pickedIso;

  /** Style of the first non transparent mask */
  mutable SoVolumeDataDrawStyle::DrawStyle m_maskStyle;

  int m_cachedComputeMode;
  CachedMode m_firstNonTransparentValueCalled;
  SoDataRange* m_dataRangeVolumeData;

  std::vector<SbVec4ub> m_rgbaValues;
  std::vector<SbVec3f> m_rgbaValuesObjectPos;
  std::vector<SbVec3i32> m_rgbaValuesDataPos;
  std::vector<SoLDMTileID> m_rgbaValuesTileId;
  bool m_gpuPicking;
};

#endif /* _SO_VOLUME_RENDER_DETAIL_ */
