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


#ifndef  _SO_SHUTTLE_
#define  _SO_SHUTTLE_

#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>

#include <Inventor/engines/SoElapsedTime.h>
#include <Inventor/engines/SoCalculator.h>
#include <Inventor/engines/SoInterpolate.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/sensors/SoOneShotSensor.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoShuttle
//
//  SoTranslation node oscillates between two translations
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Animated oscillating translation node.
 * 
 * @ingroup TransformNodes
 * 
 * @DESCRIPTION
 *   The SoShuttle class is derived from SoTranslation, so it applies a translation
 *   to the current transformation. Using engines connected to the @B realTime @b
 *   global field, the translation value is animated over time between two fixed
 *   translations, achieving a shuttling effect. The period of the motion can be
 *   adjusted by changing the #speed field. The current translation at any time
 *   is available in the @B translation @b field, inherited from SoTranslation
 * 
 * @FILE_FORMAT_DEFAULT
 *    Shuttle {
 *    @TABLE_FILE_FORMAT
 *       @TR translation    @TD 0 0 0
 *       @TR translation0   @TD 0 0 0
 *       @TR translation1   @TD 0 0 0
 *       @TR speed          @TD 1
 *       @TR on             @TD TRUE
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoRayPickAction @BR
 *        Concatenates interpolated translation value with the current transformation
 *        matrix.
 * 
 *    SoGetMatrixAction @BR
 *        Returns transformation matrix specified by the interpolated translation.
 * 
 * 
 * @SEE_ALSO
 *    SoPendulum,
 *    SoRotor
 * 
 * 
 */ 

class INVENTOR_API SoShuttle : public SoTranslation {

  SO_NODE_HEADER(SoShuttle);

 public:
  // Fields
  SoSFVec3f           translation0;
  /**
   * These define the two fixed translations that are interpolated to create the
   * shuttling motion.
   * 
   */
  SoSFVec3f           translation1;
  /**
   * Defines the speed of the shuttle, in cycles per second.
   * 
   */
  SoSFFloat           speed;
  /**
   * Allows applications to enable or disable the motion easily.
   * 
   */
  SoSFBool            on;

  /**
   * Creates a shuttle node with default settings.
   */
  SoShuttle();

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoShuttle();

 private:
  // internal engines to compute the translation
  class SoElapsedTime         *time;
  class SoCalculator          *calc;
  class SoInterpolateVec3f    *interp;

  // overload write method not to write internal engines
  virtual void        write(class SoWriteAction *action);

  // keep track of internal connection
  class SoEngineOutput        *internalConnection;

  // overload notify method to check for field updates
  virtual void notify(SoNotList *list);

  class SoOneShotSensor       *translationSensor;
  class SoFieldSensor         *translation0Sensor;
  class SoFieldSensor         *translation1Sensor;
  class SoFieldSensor         *onSensor;

  static void translationSensorCB(void *data, class SoSensor *sensor);
  static void onSensorCB(void *data, class SoSensor *sensor);
};

#endif /* _SO_SHUTTLE_ */

