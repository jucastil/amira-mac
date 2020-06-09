/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Aug 2003)
**=======================================================================*/
#ifndef  _SO_TEXTURE_COORDINATE_OBJECT_
#define  _SO_TEXTURE_COORDINATE_OBJECT_

#include <Inventor/nodes/SoTextureCoordinateFunction.h>
#include <Inventor/fields/SoSFVec4f.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTextureCoordinateObject
//
//////////////////////////////////////////////////////////////////////////////

/**
 * 
 * @VSGEXT Node that specifies texture coordinates which are a linear combination of
 * the object coordinates of the vertex.
 * 
 * @ingroup TextureNodes
 * 
 * @DESCRIPTION
 *   This node creates texture coordinates which are a linear combination of
 *   the object coordinates of the vertex (xo, yo, zo, wo).
 *   A factor can be defined for each component of the texture coordinate (S, T, R, and Q).
 *   The generated texture coordinate (S, R, T) at each vertex is:
 *
 *   S = factorS[0] * xo + factorS[1]* yo + factorS[2] * zo + factorS[3] * wo @BR
 *   R = factorR[0] * xo + factorR[1]* yo + factorR[2] * zo + factorR[3] * wo @BR
 *   T = factorT[0] * xo + factorT[1]* yo + factorT[2] * zo + factorT[3] * wo @BR
 *  
 *   wo usually equals 1.
 * 
 * @FILE_FORMAT_DEFAULT
 *    TextureCoordinateObject {
 *      @TABLE_FILE_FORMAT
 *        @TR factorS @TD 1 0 0 0
 *        @TR factorT @TD 0 1 0 0
 *        @TR factorR @TD 0 0 1 0
 *        @TR factorQ @TD 0 0 0 1
 *      @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoRayPickAction @BR
 *    Sets the current texture function in the state.
 * 
 * 
 * @SEE_ALSO
 *    SoTexture2,
 *    SoTexture2Transform,
 *    SoTextureCoordinateDefault,
 *    SoTextureCoordinatePlane,
 *    SoTextureCoordinateEnvironment.
 * 
 * 
 */ 

class INVENTOR_API SoTextureCoordinateObject : public SoTextureCoordinateFunction {

  SO_NODE_HEADER(SoTextureCoordinateObject);

 public:
  /**
   * Factor applied to generate the coordinate S
   */
   SoSFVec4f factorS ;

  /**
   * Factor applied to generate the coordinate T
   */
   SoSFVec4f factorT ;

  /**
   * Factor applied to generate the coordinate R
   */
   SoSFVec4f factorR ;

  /**
   * Factor applied to generate the coordinate Q
   */
   SoSFVec4f factorQ ;

  /**
   * Creates a texture function node with default settings.
   */
  SoTextureCoordinateObject();

 SoEXTENDER public:
  void                GLRender(SoGLRenderAction *action);
  void                pick(SoPickAction *action);
  void                callback(SoCallbackAction *action);
    
  void                doAction(SoAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoTextureCoordinateObject();

 private:
  // Callback used internally to project a point:
  static const SbVec4f &valueCallback(void *instance,
                                      const SbVec3f &point, const SbVec3f &normal);

  // Callback used internally to send GL texgen commands:
  static void doTexgen(void *);
};

#endif /* _SO_TEXTURE_COORDINATE_OBJECT_ */

