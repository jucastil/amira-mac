/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_VRMLTRIANGLE_
#define  _SO_VRMLTRIANGLE_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/SbColor.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/VRMLnodes/SoVRMLGeometry.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLTriangle
//
//
//////////////////////////////////////////////////////////////////////////////

class SoNormalBundle;

/**
 * @VSGEXT Abstract base class for the three VRMLIndexedTriangle
 *  nodes.\ @NO_ACTION
 * 
 * @ingroup X3D
 *  
 * @DESCRIPTION
 *   SoVRMLTriangle is the abstract base class for the three VRMLIndexedTriangle nodes.
 * 
 * @FILE_FORMAT_DEFAULT
 *   This is an abstract base class. See the derived classes for the format and
 *   default values.
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoRayPickAction,  SoGetBoundingBoxAction,  SoCallbackAction  @BR
 * 
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFNode   @TD   set_color      
 *       @TR   SoSFNode   @TD   set_coord      
 *       @TR   SoSFNode   @TD   set_normal      
 *       @TR   SoSFNode   @TD   set_texCoord
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFNode   @TD   color_changed      
 *       @TR   SoSFNode   @TD   coord_changed      
 *       @TR   SoSFNode   @TD   normal_changed      
 *       @TR   SoSFNode   @TD   texCoord_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLTriangle : public SoVRMLGeometry {

  SO_NODE_ABSTRACT_HEADER(SoVRMLTriangle);

 public:
  // Fields
  /**
   * An SoVRMLCoordinate node.
   * 
   */
  SoSFNode            coord;
  /**
   * An SoVRMLTextureCoordinate node.
   * 
   */
  SoSFNode            texCoord;
  /**
   * An SoVRMLNormal node containing the normals. If NULL, the normals will be
   * automatically generated.
   * 
   */
  SoSFNode            normal;
  /**
   * An SoVRMLColor node whose colors are applied to the vertices or faces of the
   * three VRMLIndexedTriangle nodes.
   * 
   */
  SoSFNode            color;
  /**
   * The colorPerVertex field is ignored and always treated as TRUE.
   */
  SoSFBool            colorPerVertex;
  /**
   * If TRUE, normals are applied to the vertices of the three 
   * VRMLIndexedTriangle nodes. If FALSE, the normals are applied 
   * to the faces.
   * 
   */
  SoSFBool            normalPerVertex;
  /**
   * Indicates whether the vertices are ordered in a counterclockwise direction when
   * viewed from the outside (TRUE) or in a clockwise direction (FALSE).
   * 
   */
  SoSFBool            ccw;
  /**
   * If you know that the shape encloses a volume, set this value to TRUE. 
   * Then backface culling will be performed. 
   * 
   */
  SoSFBool            solid;

 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);
 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:

  // Constructor - makes this abstract
  SoVRMLTriangle();


  virtual ~SoVRMLTriangle();

 private:

};
#endif /* _SO_VRMLTRIANGLE_ */

