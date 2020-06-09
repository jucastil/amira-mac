/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Beilloin (Aug 2006)
**=======================================================================*/


#ifndef SO_TILE_COMPOSER_H
#define SO_TILE_COMPOSER_H

#include <ScaleViz/nodes/SoBaseScreen.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFVec4f.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFFloat.h>

/**
 * @SCVEXT Defines a simple tile composer in a ScaleViz configuration file.
 * 
 * @ingroup ScaleVizNodes
 * 
 * @DESCRIPTION
 * 
 * The SoTileComposer node is used in a ScaleViz configuration file. 
 * SoTileComposer nodes provide a simple way of defining a sub-viewport area
 * that will be rendered by a render node. SoTileComposer fields
 * describe the portion of the view volume that will be rendered.
 *
 * This class is used in Cluster mode Only (no MultiPipe support).
 *
 * In Cluster mode, use #tileOrigin and #tileSize to set the portion
 * of the view volume to render, and use #channelOrigin and #channelSize
 * to specify where it will be rendered on the physical screen.
 * 
 * @FILE_FORMAT_DEFAULT
 *    TileComposer {
 *    @TABLE_FILE_FORMAT
 *       @TR channelOrigin     @TD 0.0 0.0
 *       @TR channelSize       @TD 1.0 1.0
 *       @TR tileOrigin        @TD 0.0 0.0
 *       @TR tileSize          @TD 1.0 1.0
 *       @TR display           @TD ":0"
 *       @TR name              @TD "screen"
 *       @TR hostname          @TD "localhost"
 *    @TABLE_END
 *    }
 *
 * 
 */ 

class SCALEVIZ_API SoTileComposer : public SoBaseScreen {

  SO_NODE_HEADER(SoTileComposer);
        
public :

  /** 
   * This field specifies the origin of the rectangular part of the view volume
   * to be rendered on this screen. The origin can be any point
   * between (0,0) and (1,1). Here (0,0) denotes the lower left corner of
   * the view volume.
   *
   */
  SoSFVec2f tileOrigin;

  /**
   * This field specifies the size of the rectangular part of the view volume
   * to be rendered on this screen. The size can be a value
   * between (0,0) and (1,1).
   *
   */
  SoSFVec2f tileSize;

  /** 
   * Constructor.
   */
  SoTileComposer();

SoINTERNAL public:
  static void initClass();
  static void exitClass();

  void setOverlapFix(SbVec2f);

protected:
  virtual ~SoTileComposer();
};

#endif // SO_TILE_COMPOSER_H

/**/
