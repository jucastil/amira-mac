/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : P. ESTRADE (Dec 2000)
** Modified by : T.DUFOUR (MMM yyyy)
**=======================================================================*/

#ifndef _SO_ORTHO_SLICE_DETAIL_
#define _SO_ORTHO_SLICE_DETAIL_

#include <Inventor/details/SoSubDetail.h>
#include <LDM/nodes/SoTransferFunction.h>
#include <Inventor/SbVec.h>
#include <Inventor/SbLine.h>

class SoVolumeData;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoOrthoSliceDetail
//
//  Detail about an SoOrthoSlice node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VREXT Stores detail information about an ortho slice.
 * 
 * @ingroup VolumeVizDetails
 * 
 * @DESCRIPTION
 *   A successful pick operation returns an SoPickedPoint object. If the picked
 *   geometry is an SoOrthoSlice, use the @B getDetail @b method and cast the result
 *   to this class to get extra information about the pick.
 *   
 *   This class contains detail information about a picked voxel on an ortho slice.
 *   The information includes the position of the picked voxel in object coordinate
 *   space (X, Y, Z) and data coordinate space (I, J, K), as well as the value of the
 *   picked voxel.
 * 
 * @SEE_ALSO
 *    SoDetail,
 *    SoOrthoSlice
 * 
 * 
 */ 

class VOLUMEVIZ_API SoOrthoSliceDetail : public SoDetail {

  SO_DETAIL_HEADER(SoOrthoSliceDetail);

 public:
  /**
   * Constructor.
   */
  SoOrthoSliceDetail();
  /**
   * Destructor.
   */
  virtual ~SoOrthoSliceDetail();

  /**
   * Returns the position of the picked voxel in object coordinate space (X, Y, Z).
   */
  const SbVec3f& getValueObjectPos() const;

  /**
   * Returns the position of the picked voxel in data coordinate space (I, J, K).
   */
  const SbVec3i32& getValueDataPos() const;

  /**
   * Returns the value of the picked voxel as an integer.
   */
  int64_t getValue() const;
  
  /**
   * Returns the value of the picked voxel as a floating point value.
   */
  double getValueD() const;

  /**
   * Returns an instance that is a copy of this instance. The caller
   * is responsible for deleting the copy when done.
   */
  virtual SoDetail * copy() const;

  //------------------------------------------------------------------------------

 SoEXTENDER public:
  void setDetails(int axis, float coord, int slice, SbLine line, SoVolumeData *vd);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  int           Zaxis;
  float         Zcoord;
  int           Zslice;
  SbLine        rayLine;
  SoVolumeData *volData;
  SbBool        valueAvailable;
  SbBool        m_valueAvailableD;
  SbVec3f       valueObjectPos;
  SbVec3i32     valueDataPos;
  int64_t       value;
  double        m_valueD;

 private:
  void computeValue(bool isDataFloat = false);

};

#endif /* _SO_ORTHO_SLICE_DETAIL_ */
