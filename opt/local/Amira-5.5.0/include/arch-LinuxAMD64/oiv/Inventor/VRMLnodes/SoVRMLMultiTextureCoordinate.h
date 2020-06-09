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


#ifndef  _SO_VRMLMULTITEXTURE_COORDINATE_
#define  _SO_VRMLMULTITEXTURE_COORDINATE_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoMFNode.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>
//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLMultiTextureCoordinate
//
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT MultiTexture coordinate node.\ @NO_ACTION
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
 *   The SoVRMLMultiTextureCoordinate node supplies multiple texture
 *   coordinates for the different texture channels. 
 *   
 *   Each entry in the #texCoord field may contain a TextureCoordinate or 
 *   TextureCoordinateGenerator node.
 *   
 *   By default, if using MultiTexture with an IndexedFaceSet without 
 *   a MultiTextureCoordinate texCoord node, texture coordinates for channel 
 *   0 are replicated along the other channels. Likewise, if there are 
 *   too few entries in the #texCoord field, the last entry is replicated. 
 *   
 *   Example:
 *
 *  <PRE>
 *   Shape { 
 *     appearance Appearance { 
 *       texture MultiTexture {  
 *         mode [ "MODULATE" "MODULATE" ] 
 *         texture [ 
 *           ImageTexture { url "brick.jpg")  
 *           ImageTexture { repeatS FALSE repeatT FALSE url "light_gray.png"} 
 *         ]
 *       }
 *     }
 *     geometry IndexedFaceSet {  
 *         ... 
 *       texCoord MultiTextureCoord {
 *         texCoord [ 
 *           TextureCoordinate { ... } 
 *           TextureCoordinate { ... } 
 *         ] 
 *       }
 *     }
 *   }
 * </pre>
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLMultiTextureCoordinate {
 *    @TABLE_FILE_FORMAT
 *       @TR texCoord   @TD NULL
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
 *       @TR   SoMFNode   @TD   set_texCoord
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoMFNode   @TD   texCoord_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLMultiTextureCoordinate : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLMultiTextureCoordinate);

 public:
  // Fields
  /**
   * Texture coordinate points.
   * 
   */
  SoMFNode           texCoord;

  /**
   * Constructor.
   */
  SoVRMLMultiTextureCoordinate();

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
  virtual ~SoVRMLMultiTextureCoordinate();
};

#endif /* _SO_VRMLMULTITEXTURE_COORDINATE_ */

