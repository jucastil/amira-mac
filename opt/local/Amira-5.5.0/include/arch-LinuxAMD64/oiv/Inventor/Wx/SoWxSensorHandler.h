/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.MEHAMLI (Jul 2007)
**=======================================================================*/

#include <wx/event.h>
#include <wx/timer.h>

#include <Inventor/SbBasic.h>
#include <Inventor/SbTime.h>

#define TIMEOUT_EVT_ID 49570

class wxTimer;
class SoTimerThread;

/**
 * This class ties Inventor sensors into the Wx event queue.
 */
class INVENTORWX_API SoWxSensorHandler : public wxEvtHandler
{  
public:
 
  SoWxSensorHandler();
  ~SoWxSensorHandler();
  
protected:

  enum
  {
    Id_TimedSensorTimer,
    Id_DelaySensorTimer,
    Id_DelaySensorTimeout
  };

  void processNextTimerSensor( wxTimerEvent& ev );
  void processNextDelaySensor( wxTimerEvent& ev );
  void processNextDelaySensorTimeout( wxTimerEvent& ev );

  // Callback for changes to the sensor manager
  static void sensorManagerChangedCallback( void* data );

  void setUpPendingTimers();

  // Allows timer thread to post timeout events
  void processTimeoutEvent( wxCommandEvent& timeoutEvent );

  wxTimer* m_timedSensorTimer;
  wxTimer* m_delaySensorTimer;
  wxTimer* m_delaySensorTimeout;

  // Internal class for managing timer in separate thread
  SoTimerThread* m_timerThread;

  // Internal deadline to decide if we have to reschedule or not the sensor
  SbTime m_currentDeadLine;
  SbBool m_useThread;

private:
  DECLARE_EVENT_TABLE() // Macro used by wxWidget to declare a table of events which will connect
                        // the events to the associated functions.
};

#define wxEVT_TIMEOUT (TIMEOUT_EVT_ID)

#define EVT_TIMEOUT(id,func) \
	EVT_CUSTOM(wxEVT_TIMEOUT,id,func)
