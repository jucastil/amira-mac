/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : John Rohlf (MMM yyyy)
** Modified by : Thad Beier (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_VRMLTEXTURE_COORDINATE_
#define  _SO_VRMLTEXTURE_COORDINATE_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLTextureCoordinate
//
//  VRMLTextureCoordinate point node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Texture coordinate node.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   The SoVRMLTextureCoordinate node specifies a set of 2D texture coordinates used
 *   by vertex-based geometry nodes (e.g. SoVRMLIndexedFaceSet and
 *   SoVRMLElevationGrid) to map from textures to the vertices. Texture map parameter
 *   values range from 0.0 to 1.0 in S and T. The horizontal coordinate, S, is
 *   specified first, followed by the vertical coordinate, T.
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
 *   The SoVRMLTextureCoordinate node specifies a set of 2D texture coordinates used
 *   by vertex-based geometry nodes (e.g. SoVRMLIndexedFaceSet and
 *   SoVRMLElevationGrid) to map from textures to the vertices. Textures are two
 *   dimensional color functions that given an S and T pair return a color value.
 *   Texture maps parameter values range from 0.0 to 1.0 in S and T. However,
 *   SoVRMLTextureCoordinate values, specified by the #point field, can range
 *   from -@I infinity @i to +@I infinity @i. Texture coordinates identify a
 *   location (and thus a color value) in the texture map. The horizontal coordinate,
 *   S, is specified first, followed by the vertical coordinate, T.
 *   
 *   If the texture map is repeated in a given direction (S or T), then a texture
 *   coordinate C is mapped into a texture map that has N pixels in the given
 *   direction as follows:
 *   
 *   <PRE>
 *    Location = (C - floor(C)) * N
 *    </PRE>
 *    If the texture is not repeated:
 *   
 *   <PRE>
 *    Location = (C > 1.0 ? 1.0 : (C < 0.0 ? 0.0 : C)) * N
 *    </PRE>
 *    See texture nodes for details on repeating textures (SoVRMLImageTexture,
 *   SoVRMLMovieTexture, SoVRMLPixelTexture).
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    SoVRMLTextureCoordinate {
 *    @TABLE_FILE_FORMAT
 *       @TR point   @TD []
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoRayPickAction,  SoCallbackAction  @BR
 * 
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoMFVec2f   @TD   set_point
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoMFVec2f   @TD   point_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLTextureCoordinate : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLTextureCoordinate);

 public:
  // Fields
  /**
   * Texture coordinate points.
   * 
   */
  SoMFVec2f           point;

  /**
   * Constructor.
   */
  SoVRMLTextureCoordinate();

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        pick(SoPickAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);
    
 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoVRMLTextureCoordinate();
};

#endif /* _SO_VRMLTEXTURE_COORDINATE_ */

