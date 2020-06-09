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


#ifndef  _SO_VRMLCOLOR_
#define  _SO_VRMLCOLOR_

#include <Inventor/fields/SoMFColor.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>

class SoColorPacker;
//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLColor
//
//  Surface base color (of the material) node. This affects the
//  diffuse color of the current material.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Specifies RGB colors to be used in the fields of another node.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   This node defines a set of RGB colors to be used in the fields of another node.
 * 
 * @VRML2_SPECIFICATION
 *    This section describes the expected behavior of the node in a conforming VRML97
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *   This section may reference portions of the VRML97 specification that are not
 *   present in this help file. The complete VRML97 spec is available at
 *   @B http://www.web3d.org @b.
 *   
 *   This node defines a set of RGB colors to be used in the fields of another node.
 *   
 *   SoVRMLColor nodes are only used to specify multiple colors for a single piece of
 *   geometry, such as a different color for each face or vertex of an
 *   SoVRMLIndexedFaceSet. An SoVRMLMaterial node is used to specify the overall
 *   material parameters of a lighted geometry. If both an SoVRMLMaterial and an
 *   SoVRMLColor node are specified for a geometry, the colors should ideally replace
 *   the diffuse component of the material. 
 *   
 *   Textures take precedence over colors; specifying both an SoVRMLTexture and an
 *   SoVRMLColor node for a geometry will result in the SoVRMLColor node being
 *   ignored. See "Concepts - Lighting Model" for details on lighting equations.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLColor {
 *    @TABLE_FILE_FORMAT
 *       @TR color   @TD []
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoCallbackAction  @BR
 * 
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoMFColor   @TD   set_color
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoMFColor   @TD   color_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLColor : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLColor);

 public:
  // Fields
  /**
   * RGB color values.
   * 
   */
  SoMFColor           color;

  /**
   * Constructor.
   */
  SoVRMLColor();

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        callback(SoCallbackAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoVRMLColor();
  SoColorPacker *colorPacker;
};

#endif /* _SO_VRMLCOLOR_ */

