/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.MEHAMLI (Jun 2007)
**=======================================================================*/

#ifndef  SO_GUI_SPACEBALL
#define  SO_GUI_SPACEBALL

#include <Inventor/Gui/SoGui.h>
#include <Inventor/events/SoMotion3Event.h>
#include <Inventor/events/SoSpaceballButtonEvent.h>

#include <Inventor/Gui/devices/SoGuiDevice.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGuiComponent
//
// SoXXSpaceball implementation class
// 
//
//////////////////////////////////////////////////////////////////////////////

/** [OIV-WRAPPER-NO-WRAP] */
class INVENTORGUI_API SoGuiSpaceball : public SoGuiDevice 
{
SoINTERNAL public:

  enum Mask 
  {
    /**
     *  Spaceball translation and rotation 
     */
    MOTION  = 0x01, 
    /**
     *  Spaceball button press 
     */
    PRESS   = 0x02, 
    /**
     *  Spaceball button release 
     */
    RELEASE = 0x04, 
    /**
     *  All spaceball events 
     */
    ALL     = 0x07
  };
  
  enum DeviceType 
  {
    SPACE_BALL           = 0x01, 
    MAGELLAN_SPACE_MOUSE = 0x02
  };
  
  //
  // valid event mask values:
  //        SoXtSpaceball::MOTION   - spaceball translation and rotation
  //        SoXtSpaceball::PRESS    - spaceball button press
  //        SoXtSpaceball::RELEASE  - spaceball button release
  //        SoXtSpaceball::ALL      - all spaceball events
  // Bitwise OR these to specify whichEvents this device should queue.
  //
  // The second constructor allows the spaceball to be attached
  // to a different display than the one used by SoXt::init().
  
  /**
   * Constructor.
   */
  SoGuiSpaceball( Mask mask = SoGuiSpaceball::ALL );

  /**
   * Destructor.
   */
  ~SoGuiSpaceball();
  
  /**
   * The spaceball reports rotations and translations as integers. These values must
   * be scaled to be useful. This method sets the rotation scale factor. 
   * Default is .006.
   */
  void setRotationScaleFactor( float f );
  
  /**
   * Returns the rotation scale factor.
   */
  float getRotationScaleFactor() const ;
  
  /**
   * The spaceball reports rotations and translations as integers. These values must
   * be scaled to be useful. This method sets the translation scale factor. Default
   * is .006.
   */
  void setTranslationScaleFactor( float f );
  
  /**
   * Returns the translation scale factor.
   */
  float getTranslationScaleFactor() const;

  /**
   * Sets the input focus method used to get events from the space ball.
   * If FALSE: SpaceBall events are received only if the cursor is in the window or
   * when the window has the focus (default). @BR
   * If TRUE: SpaceBall events are received even if cursor is out of the window. 
   */
  void setFocusToWindow(SbBool flag);

  /**
   * Gets the input focus method. See setFocusToWindow() for details.
   */
  SbBool isFocusToWindow() const;

 private:

  SbBool m_focusToWindow;
  Mask m_eventMask;      // X event interest for this device
  
  // scale factors
  float m_rotScale;
  float m_transScale;
};

#endif // SO_GUI_SPACEBALL
