/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _SO_FILE_SENSOR_H
#define  _SO_FILE_SENSOR_H

#include <Inventor/sensors/SoTimerSensor.h>
#include <Inventor/helpers/SbFileHelper.h>

#include <Inventor/STL/map>
#include <Inventor/STL/vector>

/**
 * Sensor that triggers a \oivnetdoc delegate \else callback \endoivnetdoc each time a file is changed.
 *
 * @ingroup sensors
 *
 * @DESCRIPTION
 *   File sensors trigger their \oivnetdoc delegate \else callback \endoivnetdoc function when a watched file changes.
 *   Files are checked at the interval specified with SoTimerSensor::setInterval.
 *
 *
 * @SEE_ALSO
 *    SoOneShotSensor,
 *    SoAlarmSensor,
 *    SoTimerQueueSensor,
 *    SbTime
 *
 *
 */
class INVENTOR_API SoFileSensor : public SoTimerSensor {

 public:
  /**
   * Default constructor.
   */
  SoFileSensor();

  /**
   * Constructor that takes the callback function and data to be
   * called when the sensor is triggered.
   */
  SoFileSensor(SoSensorCB *func, void *data);

  /**
   * Destroys the sensor, freeing up any memory associated with it after unscheduling
   * it.
   */
  virtual ~SoFileSensor();

  /**
   * Add file to be monitored.  If file does not exist, the method does nothing.
   */
  void addFile(const SbString& filename);

  /**
   * Remove file from monitored list.  If file is not being monitored, the method does nothing.
   */
  void removeFile(const SbString& filename);

  /**
   * Stop monitoring all previously registered files
   */
  void clearFiles();

  /**
   * Return changed file name. @BR
   * Note: Only valid when called from the \oivnetdoc delegate \else callback \endoivnetdoc function.
   */
  inline SbString getFilename() const { return m_currentFile; }

protected:
  /** Check if some files changed */
  virtual void trigger();

private:
  using SoTimerSensor::setBaseTime;
  using SoTimerSensor::getBaseTime;

  typedef std::pair<SbString, SbFileHelper::Stat> FullPathStatPair;
  typedef std::map<SbString, FullPathStatPair> FileStatMap;

  void triggerFile(SbString string);

  std::vector<SbString> m_touchedFiles;

  FileStatMap m_fileStat;

  /** File name for which we have launched a trigger */
  SbString m_currentFile;
};

#endif

