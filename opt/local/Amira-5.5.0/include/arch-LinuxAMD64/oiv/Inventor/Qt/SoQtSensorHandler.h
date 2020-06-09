/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#include <Inventor/Qt/OivQtCompat.h>
#include <Inventor/SbBasic.h>
#include <Inventor/SbTime.h>

#include <QtCore/QObject>
#include <QtCore/QPointer>

class QTimer;
class SoTimerThread;
class QCustomEvent;
/**
 * This class ties Inventor sensors into the Qt event queue.
 */
class INVENTORQT_API SoQtSensorHandler : public QObject
{
  Q_OBJECT

  public:
  SoQtSensorHandler();
  ~SoQtSensorHandler();

  protected Q_SLOTS:
  void processNextTimerSensor();
  void processNextDelaySensor();
  void processNextDelaySensorTimeout();

  protected:

  // Callback for changes to the sensor manager
  static void sensorManagerChangedCallback(void *data);

  void setUpPendingTimers();
  void setUpTimerSensor();
  void setUpDelaySensor();
  void setUpDelaySensorTimeout();

  // Allows timer thread to post timeout events
  void customEvent( QCustomEvent * );

  QPointer<QTimer> timedSensorTimer;
  QPointer<QTimer> delaySensorTimer;
  QPointer<QTimer> delaySensorTimeout;

  // Internal class for managing timer in separate thread
  SoTimerThread *m_timerThread;

  // Internal deadline to decide if we have to reschedule or not the sensor
  SbTime currentDeadLine;
};
