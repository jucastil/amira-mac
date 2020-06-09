/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : G.TALLEC (Oct 2006)
**=======================================================================*/



#ifndef  _SO_DIRECTVIZ_RENDERINGOBJECT_
#define  _SO_DIRECTVIZ_RENDERINGOBJECT_

#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/nodes/SoNode.h>

#include <Inventor/DirectViznodes/SoDirectVizShader.h>


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoDirectVizRenderingObject
//
//
//
//////////////////////////////////////////////////////////////////////////////

/**
* DirectViz Rendering Object.
* 
* 
* @DESCRIPTION
*   
* 
*/ 

class INVENTOR_API SoDirectVizRenderingObject : public SoDirectVizShader {

  SO_NODE_HEADER(SoDirectVizRenderingObject);

 public:

  /**
   * Constructor.
   */
  SoDirectVizRenderingObject();

  SoINTERNAL public:
    // Implements actions
    static void         initClass();
  static void           exitClass();

 protected:

  virtual ~SoDirectVizRenderingObject();
};

#endif /* _SO_DIRECTVIZ_RENDERINGOBJECT_ */

