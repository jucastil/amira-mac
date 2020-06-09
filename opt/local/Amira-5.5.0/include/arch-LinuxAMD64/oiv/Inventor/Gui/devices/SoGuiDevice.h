/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.MEHAMLI (Jun 2007)
**=======================================================================*/

#ifndef  SO_GUI_DEVICE
#define  SO_GUI_DEVICE

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGuiComponent
//
// SoXXDevice implementation class
// 
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/Gui/SoGui.h>
#include <Inventor/SbLinear.h>
#include <Inventor/events/SoEvent.h>

/** [OIV-WRAPPER-NO-WRAP] */
class INVENTORGUI_API SoGuiDevice
{
 SoINTERNAL public:

  /**
   * Sets the size of the window this device is registered for. This allows
   * the device to correctly convert position information from X window coordinates
   * (origin at top left) to Open Inventor window coordinates (origin at bottom
   * left). (SoQtRenderArea will automatically call this method for each device
   * registered on it whenever the window size changes.) Note: Setting the window
   * size only affects the size as perceived by the device and not the actual window
   * size.
   */
  void setWindowSize( const SbVec2s& s ) { m_winSize = s; }

  /**
   * Gets the size of the window this device is registered for. 
   */
  const SbVec2s& getWindowSize() const { return m_winSize; }

  // ----------------------- Extension usage -----------------------------------

  /**
   *  Set the window coordinate from the passed x,y value. This will flip
   *  the y value to convert from X coordinates to So coordinates.
   *  Note : The position is float to handle particular use cases when a desktop is magnified
   *  on a wall of screens thanks to ScaleViz in correlation with a tracker
   *  device calibrated for this wall.
   */
  inline void         setEventPosition(SoEvent *event, float x, float y) const;

  // ----------------------- Private usage -------------------------------------
    
 private:

  SbVec2s m_winSize;    // size of the window this device works in

};

  // ----------------------- inline definitions --------------------------------

// Inline functions
void
SoGuiDevice::setEventPosition(SoEvent *event, float x, float y) const
{
  event->setPosition(SbVec2f(x, (((float)m_winSize[1]) - 1.f) - y));
}

#endif // SO_GUI_DEVICE
