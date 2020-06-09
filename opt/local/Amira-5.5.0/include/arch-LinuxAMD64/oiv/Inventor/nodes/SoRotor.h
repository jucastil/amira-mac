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


#ifndef  _SO_ROTOR_
#define  _SO_ROTOR_

#include <Inventor/nodes/SoRotation.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>

#include <Inventor/engines/SoElapsedTime.h>
#include <Inventor/engines/SoCalculator.h>
#include <Inventor/engines/SoCompose.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/sensors/SoOneShotSensor.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoRotor
//
//  SoRotation node that spins the rotation angle, keeping the axis constant
//
//////////////////////////////////////////////////////////////////////////////

#ifdef OIV_NET_DOC
/**
* Animated rotation node.
* 
* @ingroup TransformNodes
* 
* @DESCRIPTION
*   The SoRotor class is derived from SoRotation, so it applies a rotation to the
*   current transformation. Using engines connected to the @B realTime @b global
*   field, the rotation value is animated over time, achieving a spinning effect.
*   The period of the rotation can be adjusted by changing the #speed field.
*   
*   The current rotation at any time is available in the @B rotation @b field,
*   inherited from SoRotation. This field can also be set to specify the axis of
*   rotation. Note that unless a non-zero rotation is specified for the rotation,
*   the node will not know which axis to use. For example, to set a rotor to spin
*   about the y-axis, use the following:
*   
* @FILE_FORMAT_DEFAULT
*    Rotor {
*    @TABLE_FILE_FORMAT
*       @TR rotation   @TD 0 0 1 0
*       @TR speed      @TD 1
*       @TR on         @TD true
*    @TABLE_END
*    }
* 
* @ACTION_BEHAVIOR
*    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoRayPickAction @BR
*        Concatenates current rotation value with the current transformation matrix.
* 
*    SoGetMatrixAction @BR
*        Returns transformation matrix specified by the rotation.
* 
* 
* @SEE_ALSO
*    SoPendulum,
*    SoShuttle
* 
* 
*/ 
#else
/**
* Animated rotation node.
* 
* @ingroup TransformNodes
* 
* @DESCRIPTION
*   The SoRotor class is derived from SoRotation, so it applies a rotation to the
*   current transformation. Using engines connected to the @B realTime @b global
*   field, the rotation value is animated over time, achieving a spinning effect.
*   The period of the rotation can be adjusted by changing the #speed field.
*   
*   The current rotation at any time is available in the @B rotation @b field,
*   inherited from SoRotation. This field can also be set to specify the axis of
*   rotation. Note that unless a non-zero rotation is specified for the rotation,
*   the node will not know which axis to use. For example, to set a rotor to spin
*   about the y-axis, use the following:
*   
*   <PRE> 
*    rotor->rotation.setValue(axis, 0.1);
*    </PRE>
*    where @B axis @b is a vector containing (0,1,0). Any non-zero angle can
*   be used in this code.
* 
* @FILE_FORMAT_DEFAULT
*    Rotor {
*    @TABLE_FILE_FORMAT
*       @TR rotation   @TD 0 0 1 0
*       @TR speed      @TD 1
*       @TR on         @TD TRUE
*    @TABLE_END
*    }
* 
* @ACTION_BEHAVIOR
*    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoRayPickAction @BR
*        Concatenates current rotation value with the current transformation matrix.
* 
*    SoGetMatrixAction @BR
*        Returns transformation matrix specified by the rotation.
* 
* 
* @SEE_ALSO
*    SoPendulum,
*    SoShuttle
* 
* 
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SoRotor : public SoRotation {

  SO_NODE_HEADER(SoRotor);

 public:
  // Fields
  /**
   * Defines the speed of the rotor, in revolutions per second.
   * 
   */
  SoSFFloat   speed;
  /**
   * Allows applications to enable or disable the motion easily.
   * 
   */
  SoSFBool    on;

  /**
   * Creates a rotor node with default settings.
   */
  SoRotor();

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoRotor();

 private:
  // internal engines to compute the rotation
  class SoElapsedTime         *time;
  class SoCalculator          *calc;
  class SoComposeRotation     *compose;
  class SoDecomposeRotation   *decompose; // COMPAT 2.0 ???

  // overload write method not to write internal engines
  virtual void        write(class SoWriteAction *action);

  // keep track of internal connection
  class SoEngineOutput        *internalConnection;

  // overload notify method to check for field updates
  virtual void notify(SoNotList *list);

  class SoOneShotSensor       *rotationSensor;
  class SoFieldSensor         *onSensor; // COMPAT 2.0 ???

  static void rotationSensorCB(void *data, class SoSensor *sensor);
  static void onSensorCB(void *data, class SoSensor *sensor);
};

#endif /* _SO_ROTOR_ */

