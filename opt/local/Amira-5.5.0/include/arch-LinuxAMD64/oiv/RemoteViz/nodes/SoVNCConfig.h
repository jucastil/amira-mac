/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Apr 2008)
**=======================================================================*/


#ifndef SO_VNCCONFIG_H
#define SO_VNCCONFIG_H

#include <Inventor/fields/SoMFColor.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFVec2i32.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/nodes/SoNode.h>

/**
 * @SCVEXT Defines VNC connection parameters. 
 * 
 * @ingroup ScaleVizNodes
 * 
 * @DESCRIPTION
 *  The SoVncConfig class is used in a ScaleViz configuration file to set various
 *  parameters for a VNC remote configuration, for example which server to connect
 *  to (#server).
 *  #colorMask specifies the color to use as the
 *  mask color during the composition step of the rendering on the display wall.
 *
 * @M_SINCE 7.2
 *
 * @FILE_FORMAT_DEFAULT
 *    VncConfig {
 *    @TABLE_FILE_FORMAT
 *       @TR server     @TD "localhost:0"
 *       @TR password   @TD ""
 *       @TR maskColor @TD 0.0 1.0 0.0
 *    @TABLE_END
 *    }
*
* @SEE_ALSO
*    SoVncTexture2, 
*    SoVnc
 *
 * 
 */ 

SoINTERNAL class SCALEVIZ_API SoVncConfig : public SoNode
{

  SO_NODE_HEADER(SoVncConfig);

public :

  /**
   * Specifies the hostname where the VNC server is running. (Default is "localhost".)
   */
  SoSFString server;

  /**
   * Specifies the password needed to access the VNC server. (Default is empty string.)
   */
  SoSFString password;

  /**
   * Defines the mask color to use into the composition process.
   */
  SoMFColor colorMask;

  /**
   * Constructor.
   */    
  SoVncConfig();

SoINTERNAL public:

  static void initClass();
  static void exitClass();

  void init();

  /**
   * Size of the desktop where application is running.
   * This field is automatically updated by OIV.
   */
  SoSFVec2i32 desktopSize;

  /**
   * Zoom position (normalized coordinates in the whole desktop)
   */
  SoSFVec2f zoomPosition;

  /**
   * Zoom size, normalized radius defining the point around zoomPosition that will be zoomed. 
   */
  SoSFFloat zoomSize;

  /**
   * Zoom factor, 1 means no zoom, >1 means zoom in, <1 means zoom out.
   */
  SoSFFloat zoomFactor;

  virtual void notify( SoNotList* list );

protected:
  virtual ~SoVncConfig();

};

#endif // ! SO_VNCCONFIG_H

/**/
