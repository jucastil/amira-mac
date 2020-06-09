/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_PICK_ACTION_
#define  _SO_PICK_ACTION_

#include <Inventor/SbViewportRegion.h>
#include <Inventor/actions/SoSubAction.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoPickAction
//
//  Base class for picking actions.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Abstract base class for picking objects in a scene.
 * 
 * @ingroup actions
 * 
 * @DESCRIPTION
 *   This is an abstract base class for all picking actions. Currently, the only
 *   supported subclass is the SoRayPickAction.
 * 
 * @SEE_ALSO
 *    SoRayPickAction
 * 
 * 
 */ 

class INVENTOR_API SoPickAction : public SoAction {

  SO_ACTION_HEADER(SoPickAction);

 public:
  /**
   * Sets current viewport region to use for action. Even though the picking
   * operation may not involve a window per se, some nodes need this information to
   * determine their size and placement.
   */
  void                setViewportRegion(const SbViewportRegion &newRegion);

  /**
   * Returns current viewport region to use for action. 
   */
  const SbViewportRegion &getViewportRegion() const   { return vpRegion; }

 SoEXTENDER_Documented public:
  // Setting this flag to FALSE disables any pick culling that might
  // take place (as in SoSeparators). This can be used for nodes
  // (such as SoArray and SoMultipleCopy) that traverse their
  // children multiple times in different locations, thereby
  // avoiding computing bounding boxes each time. (This problem is
  // very severe when each bounding box traversal also traverses the
  // children N times.) The default setting is TRUE.
  void                enableCulling(SbBool flag)      { culling = flag; }
  SbBool              isCullingEnabled() const        { return culling; }

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  SbViewportRegion    vpRegion;       // Current viewport region

  // Constructor takes viewport region. See comments for the
  // setViewportRegion() method.
  SoPickAction(const SbViewportRegion &viewportRegion);

  // Destructor
  virtual ~SoPickAction();

  // Initiates action on graph
  virtual void        beginTraversal(SoNode *node);

 private:
  SbBool              culling;        // Pick culling enabled?

};

#endif /* _SO_PICK_ACTION_ */

