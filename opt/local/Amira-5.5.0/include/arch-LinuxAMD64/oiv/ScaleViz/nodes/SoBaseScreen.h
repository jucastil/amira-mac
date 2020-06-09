/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Mar 2005)
**=======================================================================*/


#ifndef SO_BASE_SCREEN_H
#define SO_BASE_SCREEN_H

#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFInt32.h>

#include <Inventor/nodes/SoNode.h>

class SoBaseScreenImpl;

/**
 * @SCVEXT Abstract base class for all screen classes used in a ScaleViz
 *         configuration file.
 * 
 * @ingroup ScaleVizNodes
 * 
 * @DESCRIPTION
 *
 *  SoBaseScreen is the base class for ScaleViz screen descriptions and settings. 
 *
 *  SoBaseScreen cannot be used directly in a configuration file, but its derived
 *  classes (#SoScreen and #SoFlatScreen) are used in a ScaleViz configuration file. 
 *
 *  The SoBaseScreen derived classes are used in Cluster mode and MultiPipe mode.
 *  But note that some fields are only used in Cluster mode (e.g., #hostname) and
 *  some fields are only used in MultiPipe mode (e.g., #position).
 *
 * @FILE_FORMAT_DEFAULT
 *    BaseScreen {
 *    @TABLE_FILE_FORMAT
 *       @TR display       @TD ":0"
 *       @TR name          @TD "screen"
 *       @TR hostname      @TD "localhost"
 *       @TR position      @TD -1.0 -1.0
 *       @TR size          @TD -1.0 -1.0
 *       @TR channelOrigin @TD  0.0 0.0
 *       @TR channelSize   @TD  1.0 1.0
 *    @TABLE_END
 *    }
 * 
 * 
 */ 

class SCALEVIZ_API SoBaseScreen : public SoNode
{

  SO_NODE_HEADER(SoBaseScreen);
 
public :
  
  /**
   * Name of the X Display to connect to (the Display where this screen
   * should be rendered). The default value is ":0". The display 
   * can specify a non-local machine simply by writing the field value in 
   * the form "machine:display", e.g., "node2:0.0". Note that IP addresses 
   * are also supported. This field is not used on Windows.
   */
  SoSFString display;
  
  /**
   * Name of the screen. Does not affect rendering, but can be used
   * to make configuration files more readable.
   */
  SoSFString name;
  
  /** 
   * Hostname for current screen.
   *
   * In a cluster configuration, the hostname specifies which node of
   * the graphics cluster should render this screen.
   * Hostname can either be specified as a name
   * (machine name without or with full domain name information) or as a
   * numeric IP address.
   *
   * Cluster mode only, not used in MultiPipe mode.
   */
  SoSFString hostname;

  /**
   * Position of the graphics window on the physical screen.
   *
   * Specifies the position of the upper left corner of the graphics window.
   * 0,0 is always the upper left corner of the desktop.
   * If the values are in the range [0.0, 1.0], they are interpreted as a
   * fraction of the size of the display, where 1,1 is the lower right corner
   * of the desktop.  If values are greater than 1.0 they are interpreted as
   * pixels and the lower right corner of the desktop depends on the display
   * resolution.
   *
   * MultiPipe mode only, not used in Cluster mode.
   * For Cluster mode, use the SoFlatScreen::channelOrigin field.
   */
  SoSFVec2f position;
  
  /**
   * Size of the graphics window on the physical screen.
   *
   * If the values are in the range [0.0, 1.0], they are interpreted as a
   * fraction of the size of the display, where the size of the whole
   * desktop is 1,1. If the values are greater than 1.0 they are interpreted as
   * pixels and the maximum value depends on the display resolution.
   * 
   * If no size is specified, the window will be set to full screen.
   *
   * MultiPipe mode only, not used in Cluster mode.
   * For Cluster mode, use the SoFlatScreen::channelSize field.
   */
  SoSFVec2f size; 

  /** 
   * Position of the graphics window on the physical screen.
   *
   * Specifies the position of the upper left corner of the graphics window.
   * 0,0 is always the upper left corner of the desktop.
   * If the values are in the range [0.0, 1.0], they are interpreted as a
   * fraction of the size of the display, where 1,1 is the lower right corner
   * of the desktop. If values are greater than 1.0, they are interpreted as
   * pixels and the lower right corner of the desktop depends on the display
   * resolution.
   *
   * Cluster mode only, not used in MultiPipe mode.
   * For MultiPipe mode, see SoBaseScreen::position.
   */
  SoSFVec2f channelOrigin;

  /** 
   * Size of the graphics window on the physical screen.
   *
   * If the values are in the range [0.0, 1.0], they are interpreted as a
   * fraction of the size of the display, where the size of the whole
   * desktop is 1,1. If the values are greater than 1.0 they are interpreted as
   * pixels and the maximum value depends on the display resolution.
   *
   * Cluster mode only, not used in MultiPipe mode.
   * For MultiPipe mode, see SoBaseScreen::size.
   */
  SoSFVec2f channelSize;
    
  /**
   * Constructor.
   */
  SoBaseScreen();

SoINTERNAL public:
  static void initClass();
  static void exitClass();

  SoSFInt32 nodeid;

  SoBaseScreenImpl* m_soBaseScreenImpl;

protected:
  virtual ~SoBaseScreen();
};

#endif // SO_BASE_SCREEN_H

/**/
