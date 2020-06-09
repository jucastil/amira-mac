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


#ifndef _SO_CONE_DETAIL_
#define _SO_CONE_DETAIL_

#include <Inventor/details/SoSubDetail.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoConeDetail
//
//  Detail about an SoCone node. It contains a bitmask indicating
//  the part of the cone.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Stores detail information about the SoCone node.
 * 
 * @ingroup details
 * 
 * @DESCRIPTION
 *   This class contains detail information about a point on a cone. It contains the
 *   part of the cone that was hit (sides or bottom).
 * 
 * @SEE_ALSO
 *    SoCone,
 *    SoDetail,
 *    SoPickedPoint,
 *    SoPrimitiveVertex
 * 
 * 
 */ 

class INVENTOR_API SoConeDetail : public SoDetail {

  SO_DETAIL_HEADER(SoConeDetail);

 public:
  /**
   * Constructor.
   */
  SoConeDetail();
  /**
   * Destructor.
   */
  virtual ~SoConeDetail();

  /**
   * Returns the part in the detail. The returned value is one of the SoCone part
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

#endif /* _SO_CONE_DETAIL_ */

