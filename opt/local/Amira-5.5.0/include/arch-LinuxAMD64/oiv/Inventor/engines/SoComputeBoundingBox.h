/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_COMPUTE_BOUNDING_BOX_
#define  _SO_COMPUTE_BOUNDING_BOX_

#include <Inventor/SbViewportRegion.h>
#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFPath.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoSFVec3f.h>

class SoGetBoundingBoxAction;

/////////////////////////////////////////////////////////////////////////////
//
// Class: SoComputeBoundingBox
//
//  This engine has two input fields: "node" (SoSFNode) and "path"
//  (SoSFPath). By default, these fields contain NULL pointers. If the
//  "path" field is not NULL, this engine computes the bounding box
//  and center of the graph defined by the path, using an
//  SoGetBoundingBoxAction, and outputs the results. If the "path"
//  field is NULL but the "node" field isn't, it computes the bounding
//  box and center of the graph rooted by the node.
//
//  If both the node and the path are NULL, the outputs are disabled.
//
//  The "boxCenter" output is the center of the computed bounding box,
//  and the "objectCenter" output is the center defined by the objects
//  themselves, as returned by SoGetBoundingBoxAction::getCenter().
//
//  The engine uses a default viewport region when constructing the
//  SoGetBoundingBoxAction, so screen-based objects (such as 2D text)
//  may not be dealt with correctly. If this feature is needed, you
//  can call setViewportRegion() on an engine instance to set up the
//  correct viewport region to use.
//
/////////////////////////////////////////////////////////////////////////////

/**
 * Computes the bounding box and center of a scene graph.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   This engine computes the bounding box and center of a scene graph. The scene
 *   graph can be defined by a path or by a root node.
 *   
 *   If the #path input is not NULL, the bounding box of the graph defined by
 *   the path will be computed. If #path is NULL, but the #node input is
 *   not NULL, the bounding box is computed on the graph rooted by the node. By
 *   default, the two inputs are NULL. If both the inputs are NULL, the outputs are
 *   disabled.
 *   
 *   The engine uses a default viewport region. If the graph includes screen-based
 *   objects (such as SoText2) you can call setViewportRegion() on the engine
 *   instance to set up the correct viewport region to use.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ComputeBoundingBox {
 *    @TABLE_FILE_FORMAT
 *       @TR node   @TD NULL
 *       @TR path   @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoEngineOutput,
 *    SoGetBoundingBoxAction,
 *    SbBox3f
 * 
 * 
 */ 

class INVENTOR_API SoComputeBoundingBox : public SoEngine {

  SO_ENGINE_HEADER(SoComputeBoundingBox);

 public:
  /**
   * Defines the graph for which the bounding box is computed. 
   */
  SoSFNode            node;
  /**
   * Alternatively, defines the graph for which the bounding box is computed. 
   */
  SoSFPath            path;

  /**
   * ( SoSFVec3f )  Minimum point of the computed bounding box.
   */
  SoEngineOutput      min;
  /**
   * ( SoSFVec3f )  Maximum point of the computed bounding box.
   */
  SoEngineOutput      max;
  /**
   * ( SoSFVec3f )  Center of the computed bounding box.
   */
  SoEngineOutput      boxCenter;
  /**
   * ( SoSFVec3f )  Center of the objects in the graph.
   */
  SoEngineOutput      objectCenter;

  /**
   * Constructor
   */
  SoComputeBoundingBox();

  /**
   * Sets the viewport region to use for the bounding box computation.
   */
  void                   setViewportRegion(const SbViewportRegion &vpReg);
  /**
   * Returns the viewport region to use for the bounding box computation.
   */
  const SbViewportRegion &getViewportRegion() const;

 SoINTERNAL public:
  static void                 initClass();
  static void exitClass();

 protected:
  // Indicates that an input has changed - we use this to determine
  // whether to use the node or path, or to disable output entirely
  virtual void                inputChanged(SoField *whichInput);

  // Destructor
  virtual ~SoComputeBoundingBox();
 private:
  // Pointer to SoGetBoundingBoxAction
  SoGetBoundingBoxAction      *bba;

  // Each of these is TRUE if the corresponding input pointer is non-NULL
  SbBool                      gotNode;
  SbBool                      gotPath;

  // Evaluation method
  virtual void        evaluate();
};

#endif  /* _SO_COMPUTE_BOUNDING_BOX_ */

