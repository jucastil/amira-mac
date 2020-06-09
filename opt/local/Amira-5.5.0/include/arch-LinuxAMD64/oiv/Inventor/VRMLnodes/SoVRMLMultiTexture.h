/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : John Rohlf (MMM yyyy)
** Modified by : Thad Beier (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_VRMLMULTI_TEXTURE_
#define  _SO_VRMLMULTI_TEXTURE_

#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoMFNode.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLMultiTexture
//
//  MultiTexture node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT MultiTexture node.\ @NO_ACTION
 * 
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
 *   MultiTexture enables the application of several individual textures
 *   to a 3D object to achieve a more complex visual effect. MultiTexture 
 *   can be used as a value for the #texture field in an Appearance node.
 *   
 *   The #texture field contains a list of texture nodes (e.g., ImageTexture, 
 *   PixelTexture, MovieTexture, and MultiTexture). The texture field may 
 *   not contain another MultiTexture node.
 *
 *   The #color and #alpha fields define base RGB and alpha values for 
 *   SELECT mode operations.
 *   
 *   The #mode field controls the type of blending operation.
 *   
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLMultiTexture {
 *    @TABLE_FILE_FORMAT
 *       @TR alpha      @TD 1
 *       @TR color      @TD 1 1 1
 *       @TR function   @TD []
 *       @TR mode       @TD []
 *       @TR source     @TD []
 *       @TR texture    @TD []
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
 *       @TR SoSFFloat   @TD   set_alpha
 *       @TR SoSFColor   @TD   set_color
 *       @TR SoMFString  @TD   set_function
 *       @TR SoMFString  @TD   set_mode
 *       @TR SoMFString  @TD   set_source
 *       @TR SoMFNode    @TD   set_texture
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR SoSFFloat   @TD   alpha_changed
 *       @TR SoSFColor   @TD   color_changed
 *       @TR SoMFString  @TD   function_changed
 *       @TR SoMFString  @TD   mode_changed
 *       @TR SoMFString  @TD   source_changed
 *       @TR SoMFNode    @TD   texture_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLMultiTexture : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLMultiTexture);

 public:

  /**
   * The alpha value for SELECT mode operations.
   * 
   */
  SoSFFloat           alpha;
  /**
   * The color value for SELECT mode operations.
   * 
   */
  SoSFColor           color;
  /**
   * The optional function to be applied after the mode has been evaluated.
   * 
   */
  SoMFString           function;
  /**
   * The type of blending operation.
   * 
   */
  SoMFString           mode;
  /**
   * Determines the color source.
   * 
   */
  SoMFString         source;
  /**
   * The texture node.
   * 
   */
  SoSFNode           texture;
  /**
   * Constructor.
   */
  SoVRMLMultiTexture();
    
 SoEXTENDER public:

  virtual void        doAction(SoAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        callback(SoCallbackAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();
 protected:
  virtual ~SoVRMLMultiTexture();

 private:
};

#endif /* _SO_VRMLMULTI_TEXTURE_ */

