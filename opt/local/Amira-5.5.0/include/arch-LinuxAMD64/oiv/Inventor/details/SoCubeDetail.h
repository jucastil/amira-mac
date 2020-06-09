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


#ifndef _SO_CUBE_DETAIL_
#define _SO_CUBE_DETAIL_

#include <Inventor/details/SoSubDetail.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoCubeDetail
//
//  Detail about an SoCube node. It contains the part index (face) of
//  the cube.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Stores detail information about the SoCube node.
 * 
 * @ingroup details
 * 
 * @DESCRIPTION
 *   This class contains detail information about a point on a cube. It contains the
 *   part of the cube that was hit.
 *   
 *   Part values are as follows:
 *   @TABLE_0B
 *     @TR 0 @TD Front
 *     @TR 1 @TD Back
 *     @TR 2 @TD Left
 *     @TR 3 @TD Right
 *     @TR 4 @TD Top
 *     @TR 5 @TD Bottom
 *   @TABLE_END
 * 
 * @SEE_ALSO
 *    SoCube,
 *    SoDetail,
 *    SoPickedPoint,
 *    SoPrimitiveVertex
 * 
 * 
 */ 

class INVENTOR_API SoCubeDetail : public SoDetail {

  SO_DETAIL_HEADER(SoCubeDetail);

 public:
  /**
   * Constructor.
   */
  SoCubeDetail();
  /**
   * Destructor.
   */
  virtual ~SoCubeDetail();

  /**
   * Returns the part in the detail.
   */
  int                 getPart() const                 { return part; }

  /**
   * Returns an instance that is a copy of this instance. The caller
   * is responsible for deleting the copy when done.
   */
  virtual SoDetail *  copy() const;

 SoEXTENDER public:
  // Sets the part of detail for the shape
  void                setPart(int _part)              { part = _part; }

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();
    
 protected:
  int                 part;

};

#endif /* _SO_CUBE_DETAIL_ */

