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


#ifndef  _SO_VRMLTEXTURE_
#define  _SO_VRMLTEXTURE_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>
//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLTexture
//
//  Abstract base texture source node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Abstract base class for all VRML texture nodes.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   SoVRMLTexture is the abstract base class for all VRML texture nodes.
 *
 *   If the texture image's width or height is not a power of 2, and the 
 *   Non Power Of Two (NPOT) extension is available on your graphics board, by default Open Inventor
 *   will send the image to OpenGL without modification. See SoTexture2 for a complete
 *   discussion of this feature.
 * 
 * @FILE_FORMAT_DEFAULT
 *   This is an abstract class. See the reference page of a derived class for the
 *   format and default values.
 * 
 * @SEE_ALSO
 *    SoVRMLImageTexture,
 *    SoVRMLMovieTexture,
 *    SoVRMLPixelTexture
 * 
 * 
 */ 

class INVENTOR_API SoVRMLTexture : public SoVRMLNode {

  SO_NODE_ABSTRACT_HEADER(SoVRMLTexture);

 public:
  // Fields common to all subclasses:
  SoSFBool            repeatS;        
  /**
   * The #repeatS and #repeatT fields specify how the texture wraps in
   * the S and T directions. If #repeatS is TRUE (the default), the texture map
   * is repeated outside the 0-to-1 texture coordinate range in the S direction so
   * that it fills the shape. If #repeatS is FALSE, the texture coordinates are
   * clamped in the S direction to lie within the 0-to-1 range. The #repeatT
   * field is analogous to the #repeatS field. 
   * 
   */
  SoSFBool            repeatT;
    

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);

 protected:
  SoVRMLTexture();                            // Makes this abstract

  virtual ~SoVRMLTexture();

  // A mutex to protect the accesses to the renderList :
  // a problem occured when a system can't share display lists.
  SbThreadRWMutex *VRMLTextureMutex;
};

#endif /* _SO_VRMLTEXTURE_ */

