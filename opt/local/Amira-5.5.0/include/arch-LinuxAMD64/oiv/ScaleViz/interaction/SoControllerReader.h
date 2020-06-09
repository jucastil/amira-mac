/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Dec 2006)
**=======================================================================*/



#ifndef SO_CONTROLLER_READER_H
#define SO_CONTROLLER_READER_H

#include <Inventor/SbLinear.h>
#include <Inventor/errors/SoDebugError.h>

#include <ScaleViz/SoScaleViz.h>

/**
 * @SCVEXT Interface to trackdAPI (buttons, valuators).
 *
 * @ingroup ScaleVizInteraction
 *
 * @DESCRIPTION
 *  SoControllerReader is a class that interfaces to trackdAPI. It provides
 *  access functions to the states of buttons and valuators of VR input devices, e.g.,
 *  the buttons and joystick of a wand.
 *  SoTrackerReader is instantiated by the SbConfig class, if the configuration file
 *  specifies the use of a tracking system (by providing shared
 *  memory keys). See SbConfig::getControllerReader.
 *
 * NOTE: trackd from VRCO (www.vrco.com) is not included with Open Inventor.
 * If trackd exists on the system, Open Inventor will dynamically load it at
 * run time. See trackd documentation for information about the values returned.
 *
 *
 *
 */

class SCALEVIZ_API SoControllerReader
{
 public:

  /**
   * Constructor. The argument passed to the constructor is the shared memory key
   * used by trackd. The constructor dynamically loads trackdAPI into
   * memory, and gets the necessary function addresses.
   */
  SoControllerReader( int );

  /**
   * Destructor.
   */
  virtual ~SoControllerReader();

  /**
   * Returns the number of valuators the tracker daemon is storing.
   */
  int getNumberOfValuators();

  /**
   * Returns the number of buttons the tracker daemon is storing.
   */
  int getNumberOfButtons();

  /**
   * Returns value of the valuator identified by @B id@b from the tracker daemon.
   */
  float getValuator( int id );

  /**
   * Returns the value of button identified by @B id@b from the tracker daemon.
   */
  int getButton( int id );

  /**
   * Returns information about changes of the state of the button identified by @B id@b.
   * The function returns 0 if the state of the button hasn't changed,
   * returns -1, if the button was released,
   * returns 1, if the button was pressed.
   */
  int buttonChange( int id );

  /**
   * Returns TRUE if libtrackd.so was loaded successfully.
   */
  SbBool isLoadSuccess() { return loadSucceed; }

  /**
   * Returns TRUE if Inventor was able to retrieve all the trackdAPI functions.
   */
  SbBool isInitSuccess() { return initSucceed; }

 protected:
  void* controller;
  void* (*soTrackdInitControllerReader)( int );
  int (*soTrackdGetNumberOfValuators)( void* );
  int (*soTrackdGetNumberOfButtons)( void* );
  float (*soTrackdGetValuator)( void*, int );
  int (*soTrackdGetButton)( void*, int );

 private:

  SbBool loadSucceed;
  SbBool initSucceed;

  SbBool loadTrackdAPI();

  // previous button state
  int* buttonState;
};

#endif // SO_CONTROLLER_READER_H

/**/
