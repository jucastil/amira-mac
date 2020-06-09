/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul Isaacs (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_TEXTURE_COORDINATE_FUNCTION
#define  _SO_TEXTURE_COORDINATE_FUNCTION

#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTextureCoordinateFunction
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Abstract base class for texture coordinate function nodes.
 * 
 * @ingroup TextureNodes
 * 
 * @DESCRIPTION
 *   This is an abstract base class for texture coordinate functions. 
 *   The subclasses of this node enable texture coordinates
 *   to be created by mapping object-space points on the surfaces
 *   of shapes into texture space, according to some function. 
 *   If you are using multiple textures,
 *   these texture coordinates are the texture coordinates of the current
 *   texture unit (SoTextureUnit).
 *
 * 
 * @FILE_FORMAT_DEFAULT
 *    TextureCoordinateFunction {
 *    @TABLE_FILE_FORMAT
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoTexture2,
 *    SoTexture2Transform,
 *    SoTextureCoordinate2,
 *    SoTextureCoordinateBinding,
 *    SoTextureCoordinateDefault,
 *    SoTextureCoordinateEnvironment,
 *    SoTextureCoordinatePlane,
 *    SoTextureUnit
 * 
 * 
 */ 

class INVENTOR_API SoTextureCoordinateFunction : public SoNode {

  SO_NODE_HEADER(SoTextureCoordinateFunction);

 public:
  // No fields.

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  /**
   * Constructor.
   */
  SoTextureCoordinateFunction();
  virtual ~SoTextureCoordinateFunction();
};

#endif /* _SO_TEXTURE_COORDINATE_FUNCTION */

