/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Mar 2005)
**=======================================================================*/


#ifndef SO_FLAT_SCREEN_H
#define SO_FLAT_SCREEN_H

#include <ScaleViz/nodes/SoBaseScreen.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFVec4f.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFEnum.h>

/**
 * @SCVEXT Defines a simple flat screen in a ScaleViz configuration file.
 * 
 * @ingroup ScaleVizNodes
 * 
 * @DESCRIPTION
 * 
 * The SoFlatScreen node is used in a ScaleViz configuration file. 
 * SoFlatScreen nodes provide a simple way of defining a display that is
 * basically a very large desktop. The entire display
 * configuration is treated as a single "logical" viewport, allowing the
 * application's existing 2D interaction techniques to work as usual.
 * 
 * SoFlatScreen fields
 * describe the portion of the view volume that will be rendered and
 * where it will be rendered on the physical screen, as well as which
 * render node will be used (for cluster rendering).
 *
 * This class is used in both Cluster mode and MultiPipe mode, but
 * different fields are used in each mode, as follows:
 *
 * In MultiPipe mode there are two different ways to set the portion of
 * the view volume to render: @B view@b and @B viewport@b values. 
 * Views are convenient keywords (e.g., NONE, LEFT, RIGHT...) 
 * that ScaleViz will interpret to compute the viewport values.
 * Using viewport values is a more general and flexible way to describe
 * the portion of the view volume to render.
 *
 * In Cluster mode, use #tileOrigin and #tileSize to set the portion
 * of the view volume to render, and use #channelOrigin and #channelSize
 * to specify where it will be rendered on the physical screen.
 * 
 * @FILE_FORMAT_DEFAULT
 *    FlatScreen {
 *    @TABLE_FILE_FORMAT
 *       @TR channelOrigin     @TD 0.0 0.0
 *       @TR channelSize       @TD 1.0 1.0
 *       @TR tileOrigin        @TD 0.0 0.0
 *       @TR tileSize          @TD 1.0 1.0
 *       @TR softEdgeOverlap   @TD 0 0 0 0
 *       @TR softEdgeGamma     @TD 0 0 0 0
 *       @TR view              @TD "NONE"
 *       @TR viewport          @TD -1.0 -1.0 -1.0 -1.0
 *       @TR rightOverlap      @TD 0.0
 *       @TR leftOverlap       @TD 0.0
 *       @TR topOverlap        @TD 0.0
 *       @TR bottomOverlap     @TD 0.0
 *       @TR display           @TD ":0"
 *       @TR name              @TD "screen"
 *       @TR hostname          @TD "localhost"
 *       @TR position          @TD -1.0 -1.0
 *       @TR size              @TD -1.0 -1.0
 *       @TR cameraMode        @TD MONOSCOPIC
 *    @TABLE_END
 *    }
 *
 * 
 */ 

class SCALEVIZ_API SoFlatScreen : public SoBaseScreen
{

  SO_NODE_HEADER(SoFlatScreen);
        
public :

  /** 
   * This field specifies lower left corner of the rectangular part of the view volume
   * to be rendered on this screen. The origin can be any point
   * between (0,0) and (1,1). Here (0,0) denotes the lower left corner of
   * the view volume.
   *
   * Cluster mode only, not used in MultiPipe mode.
   * For MultiPipe mode, use the #view or #viewport field.
   */
  SoSFVec2f tileOrigin;

  /**
   * This field specifies the size of the rectangular part of the view volume
   * to be rendered on this screen. The size can be a value
   * between (0,0) and (1,1).
   *
   * Cluster mode only, not used in MultiPipe mode.
   * For MultiPipe mode, use the #view or #viewport field.
   */
  SoSFVec2f tileSize;

  /** 
   * This field specifies the size of the overlap on each side of the graphics
   * window. Values are positive for positive overlap, i.e., for extending the
   * rendering.
   * If values are between 0 and 1.0, they are interpreted as the soft-edge region on the
   * left, right, bottom, and top border of the screen relative to the total
   * width or height of the screen.
   * If values are greater than 1.0 they are interpreted as pixels.
   *
   * Cluster mode only, not used in MultiPipe mode.
   * For MultiPipe mode, use the xxxOverlap fields.
   */
  SoSFVec4f softEdgeOverlap;

  /**
   * Specifies the gamma factor for the soft-edge region. The gamma factor determines
   * how the fading from full intensity to black is done. A gamma factor of one means a
   * linear transition in terms of RGB values. For most projectors, gamma values bigger
   * than 1 are required to achieve good results.
   */
  SoSFVec4f softEdgeGamma;

  /**
   * Specifies the portion of the view volume to be rendered on this screen.
   * Valid choices are LEFT, CENTER, RIGHT, TOP, BOTTOM,
   * TOP_RIGHT, TOP_LEFT, BOTTOM_RIGHT, BOTTOM_LEFT, NONE (default), 
   * STEREO_RIGHT, and STEREO_LEFT.
   * If #view and #viewport are both specified (not recommended), #viewport takes
   * precedence.
   *
   * MultiPipe mode only, not used in Cluster mode.
   * For Cluster mode, use the tileOrigin and tileSize fields.
   */    
  SoSFString view;

  /**
   * Viewport values used to specify the portion of the scene to render
   * within the MultiPipe window. (0,0) is the lower-left corner of the 
   * virtual viewport.
   * The values are minX, minY, maxX, maxY.
   * The viewport values range from 0.0 to 1.0. 
   * If #view and #viewport are both specified (not recommended), #viewport takes
   * precedence.
   *
   * MultiPipe mode only, not used in Cluster mode.
   * For Cluster mode, use the tileOrigin and tileSize fields.
   */    
  SoSFVec4f viewport;
   
  /**
   * #rightOverlap modifies the right side of the MultiPipe window. It modifies the
   * right limit of the viewport of the region of the scene (that is rendered
   * in this MP window). Valid range for values is 0..1.
   *
   * MultiPipe mode only, not used in Cluster mode.
   * For Cluster mode use the #softEdgeOverlap field.
   */    
  SoSFFloat rightOverlap;

  /**
   * #leftOverlap modifies the left side of the MultiPipe window. It modifies the
   * left limit of the viewport of the region of the scene (that is rendered
   * in this MP window). Valid range for values is 0..1.
   *
   * MultiPipe mode only, not used in Cluster mode.
   * For Cluster mode use the #softEdgeOverlap field.
   */    
  SoSFFloat leftOverlap;

  /**
   * #topOverlap modifies the top of the MultiPipe window. It modifies the
   * top limit of the viewport of the region of the scene (that is rendered
   * in this MP window). Valid range for values is 0..1.
   *
   * MultiPipe mode only, not used in Cluster mode.
   * For Cluster mode use the #softEdgeOverlap field.
   */    
  SoSFFloat topOverlap;

  /**
   * #bottomOverlap modifies the bottom of the MultiPipe window. It modifies the
   * bottom of the viewport of the region of the scene (that is rendered
   * in this MP window). Valid range for values is 0..1.
   *
   * MultiPipe mode only, not used in Cluster mode.
   * For Cluster mode use the #softEdgeOverlap field.
   */    
  SoSFFloat bottomOverlap;

  enum CameraMode
  {
    /** 
     * Rendering is done for full view (i.e., with unmodified camera).
     */
    MONOSCOPIC,
    /**
     * Rendering is done for left eye view.
     */
    LEFT_VIEW,
    /**
     * Rendering is done for right eye view.
     */
    RIGHT_VIEW
  };

  /**
   * Specifies the passive stereo rendering mode. 
   * Use enum #CameraMode. Default is MONOSCOPIC.
   * @BR
   * @BR
   * @FIELD_SINCE_OIV 7.0
   */
  SoSFEnum cameraMode;

  /** 
   * Constructor.
   */
  SoFlatScreen();

SoINTERNAL public:
  static void initClass();
  static void exitClass();

protected:
  virtual ~SoFlatScreen();
};

#endif // SO_FLAT_SCREEN_H

/**/
