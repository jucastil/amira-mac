/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Ronen Barzel (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_BLINKER_
#define  _SO_BLINKER_

#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/sensors/SoOneShotSensor.h>
#include <Inventor/engines/SoTimeCounter.h>
#include <Inventor/sensors/SoFieldSensor.h>


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoBlinker
//
//  SoSwitch node cycles between all its children.
//  with only one child, cycles that child on and off.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Animated cycling switch node.
 * 
 * @ingroup GroupNodes
 * 
 * @DESCRIPTION
 *   The SoBlinker class is derived from SoSwitch, so it selects one of its children
 *   to traverse. Using engines connected to the @B realTime @b global field, the
 *   @B whichChild @b field is animated over time. If the node has only one child,
 *   @B whichChild @b toggles between SO_SWITCH_NONE and 0, causing the child to be
 *   switched on and off repeatedly. If the node has more than one child, they are
 *   cycled through continuously.
 * 
 * @FILE_FORMAT_DEFAULT
 *    Blinker {
 *    @TABLE_FILE_FORMAT
 *       @TR whichChild   @TD -1
 *       @TR speed        @TD 1
 *       @TR on           @TD TRUE
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoGetMatrixAction,  SoHandleEventAction,  SoRayPickAction,  SoSearchAction @BR
 *        Same as for SoSwitch.
 * 
 * 
 * 
 */ 

class INVENTOR_API SoBlinker : public SoSwitch {

  SO_NODE_HEADER(SoBlinker);

 public:
  // Fields
  /**
   * Defines the speed of the blinker, in cycles per second.
   * 
   */
  SoSFFloat           speed;
  /**
   * Allows applications to enable or disable the blinking easily.
   * 
   */
  SoSFBool            on;

  /**
   * Creates a blinker node with default settings.
   */
  SoBlinker();

 SoEXTENDER public:
  // Bounding box computation takes all children into account
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);

  // overload write method not to write internal engines
  virtual void        write(SoWriteAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoBlinker();

  virtual void        notify(SoNotList *);

 private:
  SbBool              wasOn;  // Remembers previous state of "on" field

  // keep track of internal connection
  class SoEngineOutput        *internalConnection;

  class SoTimeCounter *count;
  void                setupCounter();
  int                 nchildren;

  class SoOneShotSensor       *childrenSensor;
  class SoOneShotSensor       *whichChildSensor;
  class SoFieldSensor         *onSensor;

  static void childrenSensorCB(void *data, class SoSensor *sensor);
  static void whichChildSensorCB(void *data, class SoSensor *sensor);
  static void onSensorCB(void *data, class SoSensor *sensor);
};

#endif /* _SO_BLINKER_ */

