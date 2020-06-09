/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Thaddeus Beier (MMM yyyy)
** Modified by : Dave Immel (MMM yyyy)
** Modified by : Howard Look (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef _SO_CYLINDER_DETAIL_
#define _SO_CYLINDER_DETAIL_

#include <Inventor/details/SoSubDetail.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoCylinderDetail
//
//  Detail about an SoCylinder node. It contains a bitmask indicating
//  the part of the cylinder.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Stores detail information about the SoCylinder node.
 * 
 * @ingroup details
 * 
 * @DESCRIPTION
 *   This class contains detail information about a point on a cylinder. It contains
 *   the part of the cylinder that was hit (sides, top, or bottom).
 * 
 * @SEE_ALSO
 *    SoCylinder,
 *    SoDetail,
 *    SoPickedPoint,
 *    SoPrimitiveVertex
 * 
 * 
 */ 

class INVENTOR_API SoCylinderDetail : public SoDetail {

  SO_DETAIL_HEADER(SoCylinderDetail);

 public:
  /**
   * Constructor.
   */
  SoCylinderDetail();
  /**
   * Destructor.
   */
  virtual ~SoCylinderDetail();

  /**
   * Returns the part in the detail. The returned value is one of the SoCylinder part
   * flags.
   */
  int                 getPart() const                 { return part; }

  // Returns an instance that is a copy of this instance. The caller
  // is responsible for deleting the copy when done.
  virtual SoDetail *  copy() const;

 SoEXTENDER public:
  // Sets the part of detail for the shape
  void                setPart(int _part)              { part = _part; }

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();
   
 protected:
  int part;

};

#endif /* _SO_CYLINDER_DETAIL_ */

