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


#ifndef  _SO_VRMLINTEGERSEQUENCER_
#define  _SO_VRMLINTEGERSEQUENCER_

#include <Inventor/VRMLnodes/SoVRMLInterpolator.h>
#include <Inventor/VRMLnodes/SoVRMLSubInterpolator.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoSFBool.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLIntegerSequencer
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Interpolates among a set of float values.
 * 
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
 *   This node generates sequential SoSFInt32 events for a single TimeSensor
 *   clock (e.g., drives a VRMLSwitch via set_whichChoice).
 *   This node is a discrete-value generator.
 *   The #keyValue field must contain exactly as many numbers as there are keyframes
 *   in the #key field.
 *   
 *   Refer to "Event Utilities Component" for a more detailed discussion.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLIntegerSequencer {
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
 *       @TR   SoMFInt32   @TD   set_keyValue
 *       @TR   SoMFBool    @TD   next
 *       @TR   SoMFBool    @TD   previous
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFInt32   @TD   value_changed      
 *       @TR   SoMFFloat   @TD   key_changed      
 *       @TR   SoMFInt32   @TD   keyValue_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLIntegerSequencer : public SoVRMLInterpolator {

  SO_INTERPOLATOR_HEADER(SoVRMLIntegerSequencer);

 public:
  // Fields
  /**
   * Key array.
   */
  SoMFFloat           key;
  /**
   * KeyValue array.
   */
  SoMFInt32           keyValue;       

  // Events

  /**
   * Constructor.
   */
  SoVRMLIntegerSequencer();

 SoINTERNAL public:
  SoSFFloat               set_fraction;
  SoVRMLInterpOutput      value_changed;
  SoSFBool                next;
  SoSFBool                previous;
  static void             initClass();
  static void             exitClass();


 protected:
  virtual ~SoVRMLIntegerSequencer();

  virtual void        evaluate(SoVRMLInterpOutput *interp);

 private:
  SbBool              needsEvaluation;        // Dirty bit
  uint32_t            m_last_index;
};

#endif /* _SO_VRMLIntegerSequencer_ */

