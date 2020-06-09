/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : G.TALLEC (Oct 2006)
**=======================================================================*/


#ifndef  _SO_DIRECTVIZ_ENVIRONMENTSHADER_
#define  _SO_DIRECTVIZ_ENVIRONMENTSHADER_

#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFInt32.h> 
#include <Inventor/nodes/SoNode.h>
#include <Inventor/DirectViznodes/SoDirectVizShader.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoDirectVizEnvironmentShader
//
//  Environment shading node used for DirectViz rendering
//
//////////////////////////////////////////////////////////////////////////////

class SoTexture2;
class SoFieldSensor;

/**
 * @DVEXT DirectViz Environment shader.
 *
 * @ingroup DirectViz
 * 
 * @DESCRIPTION
 *   Node specifiying an environment shader used for DirectViz rendering.
 * 
 *   @SEE_ALSO
 *   SoDirectVizManager, SoDirectVizShader.
 *
 *
*/ 

class INVENTOR_API SoDirectVizEnvironmentShader : public SoDirectVizShader {

  SO_NODE_HEADER(SoDirectVizEnvironmentShader);

 public:
  // Fields

  /**
   * A list of textures files. The files must be in one of the following formats supported by Open Inventor:
   * BMP, GIF, JPEG2000, JPEG, PGX, PNG, PNM, SGI RGBA, Sun, and TIFF.    
   */
  SoMFString textureURLs;

  /**
   * Index into the list of texture file (textureURLs) indicating which texture 
   * file to use for environment shading.
   */
  SoSFInt32 textureID;

  /**
   * Constructor.
   */
  SoDirectVizEnvironmentShader();

  SoEXTENDER public:

    // Implement actions
    virtual void doAction(SoAction *action);

  SoINTERNAL public:

    static void         initClass();
  static void           exitClass();
    
 protected:

  virtual void checkTexture();

  SoFieldSensor *filenameSensor;

  SoFieldSensor *idSensor;

  virtual ~SoDirectVizEnvironmentShader();
};

#endif /* _SO_DIRECTVIZ_ENVIRONMENTSHADER_ */
