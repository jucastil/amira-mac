/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Dave Immel (MMM yyyy)
** Modified by : Howard Look (MMM yyyy)
** Modified by : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef _SO_DETAIL_
#define _SO_DETAIL_

#include <Inventor/SbBasic.h>
#include <Inventor/SoOutput.h>
#include <Inventor/SoTypedObject.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoDetail
//
//  Base class for all detail classes. A detail represents extra
//  information about a point on a surface, such as an intersection
//  returned from picking along a ray (SoPickedPoint) or as a vertex
//  of a generated primitive (SoPrimitiveVertex).
//
//  The base class does not contain any useful information. It is here
//  only as an abstract class. Subclasses can add useful detail
//  information, such as a part index or nearest vertex.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Base class for describing detail information about a shape node.
 * 
 * @ingroup details
 * 
 * @DESCRIPTION
 *   SoDetail is the abstract base class for all detail classes. A detail contains
 *   shape-specific information about a particular shape during picking and primitive
 *   generation. Subclasses store information based on the particular type of shape.
 * 
 * @SEE_ALSO
 *    SoConeDetail,
 *    SoCubeDetail,
 *    SoCylinderDetail,
 *    SoDetailList,
 *    SoFaceDetail,
 *    SoLineDetail,
 *    SoNodeKitDetail,
 *    SoPickedPoint,
 *    SoPointDetail,
 *    SoPrimitiveVertex,
 *    SoTextDetail
 * 
 * 
 */ 

class INVENTOR_API SoDetail: public SoTypedObject {
 public:
  // Destructor
#ifndef HIDDEN_FROM_DOC
  virtual ~SoDetail();
#endif // HIDDEN_FROM_DOC

  /**
   * Returns type identifier for this class.
   */
  static SoType       getClassTypeId();

  /**
   * Returns an instance that is a copy of this instance. The caller is responsible
   * for deleting the copy when it is no longer needed.
   */
  virtual SoDetail *  copy() const = 0;

  /*
   *  Writes instance to SoOutput. Must be defined by all sub-class
   */
  //virtual void writeInstance(SoOutput *out);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  // Initialize ALL Inventor detail classes
  static void         initClasses();
  static void         exitClasses();

 protected:
  // Constructor is protected since this is an abstract class
  SoDetail();

 private:
  // Type identifier
  static SoType classTypeId;
};

#endif /* _SO_DETAIL_ */


