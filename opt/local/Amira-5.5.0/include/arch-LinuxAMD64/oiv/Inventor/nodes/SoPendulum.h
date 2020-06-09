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


#ifndef  _SO_PENDULUM_
#define  _SO_PENDULUM_

#include <Inventor/nodes/SoRotation.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>

#include <Inventor/sensors/SoOneShotSensor.h>
#include <Inventor/engines/SoElapsedTime.h>
#include <Inventor/engines/SoCalculator.h>
#include <Inventor/engines/SoInterpolate.h>
#include <Inventor/sensors/SoFieldSensor.h>


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoPendulum
//
//  SoRotation node oscillates between two rotations
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Animated oscillating rotation node.
 * 
 * @ingroup TransformNodes
 * 
 * @DESCRIPTION
 *   The SoPendulum class is derived from SoRotation, so it applies a rotation to the
 *   current transformation. Using engines connected to the @B realTime @b global
 *   field, the rotation value is animated over time between two fixed rotations,
 *   achieving the effect of a swinging pendulum. The period of the swing can be
 *   adjusted by changing the #speed field. The current rotation at any time is
 *   available in the @B rotation @b field, inherited from SoRotation
 * 
 * @FILE_FORMAT_DEFAULT
 *    Pendulum {
 *    @TABLE_FILE_FORMAT
 *       @TR rotation    @TD 0 0 1 0
 *       @TR rotation0   @TD 0 0 1 0
 *       @TR rotation1   @TD 0 0 1 0
 *       @TR speed       @TD 1
 *       @TR on          @TD TRUE
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoRayPickAction @BR
 *        Concatenates interpolated rotation value with the current transformation
 *        matrix.
 * 
 *    SoGetMatrixAction @BR
 *        Returns transformation matrix specified by the interpolated rotation.
 * 
 * 
 * @SEE_ALSO
 *    SoRotor,
 *    SoShuttle
 * 
 * 
 */ 

class INVENTOR_API SoPendulum : public SoRotation {

  SO_NODE_HEADER(SoPendulum);

 public:
  // Fields
  /**
   * Defines the first of the two fixed rotations that are interpolated to create the
   * pendular motion.
   * 
   */
  SoSFRotation        rotation0;
  /**
   * Defines the second of the two fixed rotations that are interpolated to create the
   * pendular motion.
   * 
   */
  SoSFRotation        rotation1;
  /**
   * Defines the speed of the pendulum, in cycles per second.
   * 
   */
  SoSFFloat           speed;
  /**
   * Allows applications to enable or disable the motion easily.
   * 
   */
  SoSFBool            on;

  /**
   * Creates a pendulum node with default settings.
   */
  SoPendulum();

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoPendulum();

 private:
  // internal engines to compute the rotation
  class SoElapsedTime         *time;
  class SoCalculator          *calc;
  class SoInterpolateRotation *interp;

  // overload write method not to write internal engines
  virtual void        write(class SoWriteAction *action);

  // keep track of internal connection
  class SoEngineOutput        *internalConnection;

  // overload notify method to check for field updates
  virtual void notify(SoNotList *list);

  class SoOneShotSensor       *rotationSensor;
  class SoFieldSensor         *rotation0Sensor;
  class SoFieldSensor         *rotation1Sensor;
  class SoFieldSensor         *onSensor;

  static void rotationSensorCB(void *data, class SoSensor *sensor);
  static void onSensorCB(void *data, class SoSensor *sensor);
};

#endif /* _SO_PENDULUM_ */

