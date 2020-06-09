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


#ifndef  _SO_GET_MATRIX_ACTION_
#define  _SO_GET_MATRIX_ACTION_

#include <Inventor/SbLinear.h>
#include <Inventor/actions/SoSubAction.h>
#include <Inventor/SbViewportRegion.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGetMatrixAction
//
//  For computing a cumulative transformation matrix and its inverse,
//  along with a cumulative texture transformation matrix and its inverse.
//
//  This action is unlike most others in that it does not traverse
//  downwards. When called on a node, it computes the matrix for just
//  that node. (This makes sense for transformation nodes, but not for
//  others, really.) When called on a path, it gathers the
//  transformation info for all nodes in the path and those that
//  affect nodes in the path, but it stops when it hits the last node
//  in the path; it does not traverse downwards from it as other
//  actions (such as rendering) do. This behavior makes the most sense
//  for this action.
//
//  EXTENDERS:  The model and texture matrix elements are not enabled
//  for this action.  Your transformation nodes must use the
//  getMatrix/getInverse calls and directly modify the matrices stored
//  in the action.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Computes transformation matrix for a subgraph.
 * 
 * @ingroup actions
 * 
 * @DESCRIPTION
 *   This action computes transformation matrices for a given subgraph. It computes
 *   the cumulative transformation matrix and its inverse, along with a cumulative
 *   texture transformation matrix and its inverse.  The cumulative transformation
 *   matrix transforms the coordinates of a shape from the local object coordinate
 *   system to the global world coordinate system.
 *   
 *   When this action is applied to a node, it computes the matrix for just that node.
 *   This is currently the easiest way to get the transformation matrix for an
 *   SoTransform node.  It's not very useful for most other types of nodes.
 *
 *   The most common scenario is applying this action to a path.  In that case it 
 *   gathers the transformation info for all nodes in the path and those that affect
 *   nodes in the path, but it stops when it hits the last node in the path; it does
 *   @I not @i traverse downwards from it as most other actions (such as rendering) do. 
 *   This behavior makes the most sense for this action.  To get a path to, for
 *   example, a specific geometry in the scene graph see SoSearchAction.
 *
 *   Sets: SoViewportRegionElement
 *
 * @EXAMPLE
 *   \oivnetdoc
 *     \code
 *     // Get cumulative matrix using current viewport on screen
 *     SoGetMatrixAction gma = new SoGetMatrixAction();
 *     gma.Apply( somePath );
 *     SbMatrix matrix = gma.GetMatrix();
 *     \endcode
 *   \else
 *     \code
 *     // Get cumulative matrix using current viewport on screen
 *     SoGetMatrixAction gma( pViewer->getViewportRegion() );
 *     gma.apply( pPath );
 *     SbMatrix &matrix = gma.getMatrix();
 *     \endcode
 *   \endoivnetdoc
 * 
 * @SEE_ALSO
 *    SoGetBoundingBoxAction,
 *    SoSearchAction
 * 
 * 
 */ 

class INVENTOR_API SoGetMatrixAction : public SoAction {

  SO_ACTION_HEADER(SoGetMatrixAction);

 public:
  /**
   * Constructor. @BR
   * Even though the bounding box computation may not involve a window per se, 
   * some nodes need the size of the viewport to determine their size in 3D
   * coordinates.  For example the size of an SoText2 is a fixed value in device
   * coordinates, but the corresponding size in 3D depends on the current camera.
   *
   * Usually it is convenient to get the actual viewport region from the viewer
   * as shown in the example above.  However if the scene graph does not contain
   * any viewport dependent nodes then any values can be used.
   */
  SoGetMatrixAction(const SbViewportRegion &newRegion);

  // Destructor
#ifndef HIDDEN_FROM_DOC
  virtual ~SoGetMatrixAction();
#endif // HIDDEN_FROM_DOC

  /**
   * Sets current viewport region to use for action.
   */
  void                setViewportRegion(const SbViewportRegion &newRegion);

  /**
   * Returns current viewport region to use for action.
   */
  const SbViewportRegion &getViewportRegion() const   { return vpRegion; }

  /**
   * Returns cumulative transformation matrix. Warning: the matrix
   * returned by this routine should not be changed (unless you are implementing
   * your own transformation nodes).
   */
  SbMatrix &          getMatrix()             { return ctm; }
  /**
   * Returns the inverse of the cumulative transformation matrix. Warning: the matrix
   * returned by this routine should not be changed (unless you are implementing
   * your own transformation nodes).
   */
  SbMatrix &          getInverse()            { return inv; }

  /**
   * Returns cumulative texture transformation matrix. Warning: the
   * matrix returned by this routine should not be changed (unless you are
   * implementing your own transformation nodes).
   */
  SbMatrix &          getTextureMatrix()      { return texCtm; }
  /**
   * Returns the inverse of the cumulative texture transformation matrix. Warning: the
   * matrix returned by this routine should not be changed (unless you are
   * implementing your own transformation nodes).
   */
  SbMatrix &          getTextureInverse()     { return texInv; }

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  // Initiates action on graph
  virtual void        beginTraversal(SoNode *node);

 private:
  SbMatrix            ctm;            // Cumulative transformation matrix
  SbMatrix            inv;            // Inverse transformation matrix
  SbMatrix            texCtm;         // Cumulative texture transf matrix
  SbMatrix            texInv;         // Inverse texture transf matrix
  SbViewportRegion    vpRegion;       // Current viewport region

};

#endif /* _SO_GET_MATRIX_ACTION_ */

