/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Mar 2005)
**=======================================================================*/


#ifndef SO_SCREEN_H
#define SO_SCREEN_H

#include <ScaleViz/nodes/SoBaseScreen.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFEnum.h>

/** 
 * @SCVEXT Defines a general screen in a ScaleViz configuration file. 
 * 
 * @ingroup ScaleVizNodes
 * 
 * @DESCRIPTION
 * The SoScreen node is used in a ScaleViz configuration file. 
 * SoScreen fields specify three coordinates
 * defining a "projection wall". The three points should define
 * a right angle.
 * 
 * The projection wall coordinates are used by the camera to compute the view and
 * projection matrices.
 *
 * SoScreen is normally only used in an immersive environment.
 *
 * @FILE_FORMAT_DEFAULT
 *    Screen {
 *    @TABLE_FILE_FORMAT
 *       @TR lowerLeft      @TD -1 -1 -1
 *       @TR lowerRight     @TD -1 -1 -1
 *       @TR upperLeft      @TD -1 -1 -1
 *       @TR upperRight     @TD -1 -1 -1
 *       @TR display        @TD ":0"
 *       @TR name           @TD "screen"
 *       @TR position       @TD -1.0 -1.0
 *       @TR size           @TD -1.0 -1.0
 *       @TR cameraMode     @TD MONOSCOPIC
 *    @TABLE_END
 *    }
 * 
 * 
 */ 

class SCALEVIZ_API SoScreen : public SoBaseScreen
{

  SO_NODE_HEADER(SoScreen);
        
  public :

    /**
     * Coordinates of lower left corner of the projection wall.
     */
    SoSFVec3f lowerLeft;
    
    /**
     * Coordinates of lower right corner of the projection wall.
     */
    SoSFVec3f lowerRight;

    /**
     * Coordinates of upper left corner of the projection wall.
     */
    SoSFVec3f upperLeft;

    /**
     * Coordinates of upper right corner of the projection wall.
     *
     * Note: This value of this field is not currently used.
     * @BR
     * @BR
     * @FIELD_SINCE_OIV 6.1
     */
    SoSFVec3f upperRight;

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
  SoScreen();

SoINTERNAL public:
  static void initClass();
  static void exitClass();

protected:
  virtual ~SoScreen();
};

#endif // SO_SCREEN_H

/**/
