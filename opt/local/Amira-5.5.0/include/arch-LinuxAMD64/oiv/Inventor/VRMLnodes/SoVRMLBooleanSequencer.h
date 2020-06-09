/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_VRMLBOOLEANSEQUENCER_
#define  _SO_VRMLBOOLEANSEQUENCER_

#include <Inventor/VRMLnodes/SoVRMLInterpolator.h>
#include <Inventor/VRMLnodes/SoVRMLSubInterpolator.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFBool.h>
#include <Inventor/fields/SoSFBool.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLBooleanSequencer
//
//////////////////////////////////////////////////////////////////////////////

/**
 * 
 * @VSGEXT Generates sequential SoSFBool events when driven from a VRMLTimeSensor
 *         clock.
 * 
 * @ingroup X3D
 * 
 * @DESCRIPTION
 *   See the X3D Specification, below.
 * 
 * @VRMLX3D_SPECIFICATION
 *   This section describes the expected behavior of the node in a conforming X3D
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *   This section may reference portions of the X3D specification that are not
 *   present in this help file. The complete X3D spec is available at
 *   @B http://www.web3d.org @b.
 *   
 *   This node generates sequential SoSFBool events when driven from a TimeSensor
 *   clock. Amoung other actions, it can enable/disable lights and sensors.
 *   The #keyValue field must contain exactly as many numbers as there are
 *   keyframes in the #key field.
 *   
 *   The keyValue field is made up of a list of FALSE and TRUE values.
 *   
 *   Refer to "Event Utilities Component" for a more detailed discussion.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLBooleanSequencer {
 *    @TABLE_FILE_FORMAT
 *       @TR key        @TD []
 *       @TR keyValue   @TD []
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFFloat   @TD   set_fraction      
 *       @TR   SoMFFloat   @TD   set_key      
 *       @TR   SoMFBool    @TD   set_keyValue
 *       @TR   SoMFBool    @TD   next
 *       @TR   SoMFBool    @TD   previous
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFBool    @TD   value_changed      
 *       @TR   SoMFFloat   @TD   key_changed      
 *       @TR   SoMFBool    @TD   keyValue_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLBooleanSequencer : public SoVRMLInterpolator {

  SO_INTERPOLATOR_HEADER(SoVRMLBooleanSequencer);

 public:
  // Fields
  /**
   * Key array.
   */
  SoMFFloat           key;
  /**
   * KeyValue array.
   */
  SoMFBool            keyValue;       

  /**
   * Constructor.
   */
  SoVRMLBooleanSequencer();

 SoINTERNAL public:
  SoSFFloat               set_fraction;
  SoSFBool                next;
  SoSFBool                previous;
  SoVRMLInterpOutput      value_changed;
  static void             initClass();
  static void             exitClass();

 protected:
  virtual ~SoVRMLBooleanSequencer();
  virtual void        evaluate(SoVRMLInterpOutput *interp);

 private:
  SbBool              needsEvaluation;        // Dirty bit
  uint32_t            m_last_index;

};

#endif /* _SO_VRMLBOOLEANSEQUENCER_ */

