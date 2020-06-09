/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : G.TALLEC (Oct 2006)
**=======================================================================*/


#ifndef  _SO_DIRECTVIZ_GENERALSHADER_
#define  _SO_DIRECTVIZ_GENERALSHADER_

#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/DirectViznodes/SoDirectVizShader.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoDirectVizGeneralShader
//
//  DirectViz general shader node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @DVEXT DirectViz general surface shader class.
 * 
 * @ingroup DirectViz
 * 
 * @DESCRIPTION
 * 
 * Node specifying a surface shader for DirectViz ray-traced rendering.
 * See the Open Inventor by VSG User's Guide for descriptions of  
 * the surface shaders supported by DirectViz and reference information about available shader options.
 *
 * @SEE_ALSO 
 * SoDirectVizShader.
 *
 *
*/ 

class INVENTOR_API SoDirectVizGeneralShader : public SoDirectVizShader {

  SO_NODE_HEADER(SoDirectVizGeneralShader);

 public:

  /**
   * Constructor.
   */
  SoDirectVizGeneralShader();

  SoEXTENDER public:
    virtual void doAction(SoAction *action);

  SoINTERNAL public:
    static void         initClass();
  static void           exitClass();

 protected:

  virtual ~SoDirectVizGeneralShader();
};

#endif /* _SO_DIRECTVIZ_GENERALSHADER_ */

