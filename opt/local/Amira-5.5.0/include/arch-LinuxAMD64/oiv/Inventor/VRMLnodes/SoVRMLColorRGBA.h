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


#ifndef  _SO_VRMLCOLORRGBA_
#define  _SO_VRMLCOLORRGBA_

#include <Inventor/fields/SoMFColorRGBA.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>

class SoColorPacker;
//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLColorRGBA
//
//  Surface base color (of the material) node. This affects the
//  diffuse color of the current material.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Specifies RGBA colors to be used in the fields of another node.\ @NO_ACTION
 * 
 * @ingroup X3D
 * 
 * @DESCRIPTION
 *   See the X3D Specification, below.
 * 
 * @VRMLX3D_SPECIFICATION
 *   This section describes the expected behavior of the node in a conforming X3D
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *   This section may reference portions of the X3D specification that are not
 *   present in this help file. The complete X3D spec is available at
 *   @B http://www.web3d.org @b.
 *   
 *   This node defines a set of RGBA colors to be used in the fields of another node.
 *   
 *   SoVRMLColorRGBA nodes are only used to specify multiple colors for a single piece of
 *   geometry, such as a different color for each face or vertex of an
 *   SoVRMLIndexedFaceSet. An SoVRMLMaterial node is used to specify the overall
 *   material parameters of a lighted geometry. If both an SoVRMLMaterial and an
 *   SoVRMLColorRGBA node are specified for a geometry, the colors replace
 *   the diffuse component of the material. 
 *   
 *   Textures take precedence over colors; specifying both an SoVRMLTexture and an
 *   SoVRMLColorRGBA node for a geometry will result in the SoVRMLColorRGBA node being
 *   ignored. See the Lighting model chapter of the X3D spec for details on lighting equations.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLColorRGBA {
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
 *       @TR   SoMFColorRGBA   @TD   set_color
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoMFColorRGBA   @TD   color_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLColorRGBA : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLColorRGBA);

 public:
  // Fields
  /**
   * RGBA color values.
   * 
   */
  SoMFColorRGBA           color;

  /**
   * Constructor.
   */
  SoVRMLColorRGBA();

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        callback(SoCallbackAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();


 protected:
  virtual ~SoVRMLColorRGBA();
  SoColorPacker *colorPacker;
};

#endif /* _SO_VRMLCOLOR_ */
