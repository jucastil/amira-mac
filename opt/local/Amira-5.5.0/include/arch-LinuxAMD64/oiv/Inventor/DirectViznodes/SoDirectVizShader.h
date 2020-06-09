/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : G.TALLEC (Oct 2006)
**=======================================================================*/



#ifndef  _SoDirectVizShader_
#define  _SoDirectVizShader_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFString.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoDirectVizShader
//
//  DirectViz general shader node.
//
//////////////////////////////////////////////////////////////////////////////

class SoTexture2;

/**
* @DVEXT DirectViz shader node base class.
*
* @ingroup DirectViz
* 
* @DESCRIPTION
* 
* Base class for specifying shader and associated options for DirectViz ray-traced rendering. 
* It provides a generic interface to OpenRTRT(tm) shaders. 
* @B Note: use the appropriate derived class depending on the shader type@b
* (i.e., SoDirectVizGeneralShader for surface shaders, or SoDirectVizEnvironmentShader).
* See the Open Inventor by VSG User's Guide for descriptions of  
* the shaders supported by DirectViz and reference information about available shader options.
*
* @SEE_ALSO 
*
* SoDirectVizManager
* 
* 
*/ 

class INVENTOR_API SoDirectVizShader : public SoNode {

  SO_NODE_HEADER(SoDirectVizShader);

public:
  // Fields

  /**
  * Name of OpenRTRT dynamic library containing the shader code. 
  * Always use ".so" extensions for UNIX compatibility 
  * (automatically transformed into ".dll" on Windows platforms).
  * For instance use "libRTX.so" for RTX shaders; use "libDTX.so" for DTX shaders. 
  * If this field is not set (null string), DirectViz will try to guess the 
  * appropriate library depending on the current shader package, 
  * as defined by environment variable DIRECTVIZ_RENDERING_OBJECT. See SoPreferences.
  */
  SoSFString          file; 

  /**
  * Name of the shader to use.
  *
  */
  SoSFString          name; 

  /**
  * These strings specify parameters to the shader.
  * 
  * The syntax is:@BR
  * \<parameter type> \<parameter name> \<parameter value>
  *
  * Allowed types are:
  *
  * @TABLE_1B
  * @TR 1i @TD One integer
  * @TR 2i @TD Two integers
  * @TR 3i @TD Three integers
  * @TR 1f @TD One float
  * @TR 2f @TD Two floats
  * @TR 3f @TD Three floats
  * @TR color @TD Same as 3f
  * @TR bool @TD Same as 1i
  * @TR texture @TD File path
  * @TABLE_END
  *
  * Example: 
  * <PRE>
  *  options [ "bool isVisible true" , "1i upDirection 1" , "3f intensity 0.65 0.5899 0.5899  "]
  * </PRE>
  *
  * Any trailing part of the string that does not correspond to a parameter is ignored.
  *
  * When specifying a shader, it may not be necessary to specify values for all available parameters. 
  * If a parameter is not specified by the user, the default value will be used. 
  * See version 6.1 of the Open Inventor by VSG User's Guide for more information.
  *
  */
  SoMFString          options;

  /**
  * Constructor.
  */
  SoDirectVizShader();

  SoEXTENDER public:
  // Implements actions
  virtual void GLRender(SoGLRenderAction *action);

  virtual void doAction(SoAction *action);

  virtual void callback(SoCallbackAction *action);

  SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  SoTexture2 *_texture;

  SbString _texUrl;

  virtual void checkTexture();

protected:

  static void textureChangedCB(void *data, SoSensor *sensor);

  virtual ~SoDirectVizShader();

  SoINTERNAL public:

  static void addDirectories();

  static void removeDirectories();

  static SbStringList *_dirList;
};

#endif /* _SoDirectVizShader_ */
