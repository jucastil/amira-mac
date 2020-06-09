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


#ifndef  _SO_VRMLINTEGERTRIGGER_
#define  _SO_VRMLINTEGERTRIGGER_

#include <Inventor/VRMLnodes/SoVRMLInterpolator.h>
#include <Inventor/VRMLnodes/SoVRMLSubInterpolator.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoMFInt32.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLIntegerTrigger
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Sets an integer value for the output event.
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
 *   This node handles single field boolean events to set an integer value for
 *   the output event. This is useful for connecting environmental events to the
 *   VRMLSwitch node's #whichChoice field.
 *
 *   Upon receiving a set_boolean event, the IntegerTrigger node will generate a 
 *   #triggerValue event with the current value of #integerKey.
 *   
 *   Refer to "Event Utilities Component" for a more detailed discussion.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLIntegerTrigger {
 *    @TABLE_FILE_FORMAT
 *       @TR integerKey @TD -1
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFFloat   @TD   set_boolean      
 *       @TR   SoSFInt32   @TD   set_integerKey
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT 
 *       @TR   SoSFInt32   @TD   triggerValue      
 *       @TR   SoSFInt32   @TD   value_changed      
 *       @TR   SoSFInt32   @TD   integerKey_changed
 *       @TR   SoSFNode   @TD   metadata_changed      
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLIntegerTrigger : public SoVRMLInterpolator {

  SO_INTERPOLATOR_HEADER(SoVRMLIntegerTrigger);

 public:
  // Fields
  /**
   * Current trigger value to output.
   */
  SoSFInt32            integerKey;

  /**
   * Constructor.
   */
  SoVRMLIntegerTrigger();

 SoINTERNAL public:
  SoSFBool                set_boolean;
  SoVRMLInterpOutput      triggerValue;
  static void             initClass();
  static void             exitClass();

 protected:
  virtual ~SoVRMLIntegerTrigger();
  virtual void        evaluate(SoVRMLInterpOutput *interp);
  
 private:
  SbBool              needsEvaluation;        // Dirty bit

};

#endif /* _SO_VRMLINTEGERTRIGGER_ */

