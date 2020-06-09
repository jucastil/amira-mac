/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Beilloin (Aug 2006)
**=======================================================================*/


#ifndef SO_DEPTH_COMPOSER_H
#define SO_DEPTH_COMPOSER_H

#include <ScaleViz/nodes/SoBaseScreen.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFVec4f.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFFloat.h>

/**
 * @SCVEXT Defines a simple depth composer in a ScaleViz configuration file.
 * 
 * @ingroup ScaleVizNodes
 * 
 * @DESCRIPTION
 * 
 * The SoDepthComposer node is used in a ScaleViz configuration file. 
 * SoDepthComposer nodes provide a simple way of specifying
 * which render node will be used to render a sub scene graph.
 *
 * This class is used in Cluster mode Only (no MultiPipe support).
 *
 * See the text in the User's Guide for additional information.
 * 
 * @FILE_FORMAT_DEFAULT
 *    DepthComposer {
 *    @TABLE_FILE_FORMAT
 *       @TR channelOrigin     @TD 0.0 0.0
 *       @TR channelSize       @TD 1.0 1.0
 *       @TR display           @TD ":0"
 *       @TR name              @TD "screen"
 *       @TR hostname          @TD "localhost"
 *    @TABLE_END
 *    }
 *
 * 
 */ 

class SCALEVIZ_API SoDepthComposer : public SoBaseScreen {

  SO_NODE_HEADER(SoDepthComposer);
        
public :

/** 
   * Constructor.
   */

  SoDepthComposer();

SoINTERNAL public:
  static void initClass();
  static void exitClass();

  void setOverlapFix(SbVec2f);

protected:
  virtual ~SoDepthComposer();
};

#endif // SO_DEPTH_COMPOSER_H

/**/
