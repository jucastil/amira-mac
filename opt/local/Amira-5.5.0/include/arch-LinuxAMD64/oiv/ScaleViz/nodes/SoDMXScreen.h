/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Jul 2007)
**=======================================================================*/


#ifndef SO_DMX_SCREEN_H
#define SO_DMX_SCREEN_H

#ifndef HIDDEN_FROM_DOC
#include <Inventor/nodes/SoNode.h>

/**
 * @SCVEXT Defines a simple DMX screen configuration in a ScaleViz configuration file.
 * 
 * @ingroup ScaleVizNodes
 * 
 * @DESCRIPTION
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    DMXScreen {
 *    }
 *
 * 
 */ 

SoINTERNAL class SCALEVIZ_API SoDMXScreen : public SoNode
{

  SO_NODE_HEADER(SoDMXScreen);
        
public :

  /** 
   * Constructor.
   */
  SoDMXScreen();

SoINTERNAL public:
  static void initClass();
  static void exitClass();

protected:
  virtual ~SoDMXScreen();
};

#endif
#endif // SO_DMX_SCREEN_H

/**/

