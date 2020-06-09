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
/*
 * Modifications for VRML 2.0  1997
 */


#ifndef  _SO_VRMLBOOLEANTRIGGER_
#define  _SO_VRMLBOOLEANTRIGGER_

#include <Inventor/VRMLnodes/SoVRMLInterpolator.h>
#include <Inventor/VRMLnodes/SoVRMLSubInterpolator.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFTime.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLBooleanTrigger
//
//////////////////////////////////////////////////////////////////////////////

/**
 * 
 * @VSGEXT Generates boolean events upon receiving time events.
 * 
 * @ingroup X3D
 * 
 * @DESCRIPTION
 *   See the X3D Specification, below.
 * 
 * @VRMLX3D_SPECIFICATION
 *   This section describes the expected behavior of the node in a conforming
 *   X3D browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes
 *   and IVF classes implement some of the application behaviors.
 *   
 *   This section may reference portions of the X3D specification that are not
 *   present in this help file. The complete X3D spec is available at
 *   @B http://www.web3d.org @b.
 *   
 *   This utility event is a trigger node that generates boolean events
 *   upon receiving time events. The triggerTrue event is generated when
 *   the BooleanTrigger receives a set_triggerTime event. The value of 
 *   triggerTrue will always be TRUE.
 *   
 *   Refer to "Event Utilities Component" for a more detailed discussion.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLBooleanTrigger {
 *    @TABLE_FILE_FORMAT
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFTime    @TD   set_triggerTime
 *       @TR   SoSFNode   @TD   set_metadata 
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFBool    @TD   triggerTrue
 *       @TR   SoSFNode   @TD   metadata_changed           
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLBooleanTrigger : public SoVRMLInterpolator {

  SO_INTERPOLATOR_HEADER(SoVRMLBooleanTrigger);

 public:
  // Fields

  // Events

  /**
   * Constructor.
   */
  SoVRMLBooleanTrigger();

 SoINTERNAL public:
  SoSFTime                set_triggerTime;
  SoVRMLInterpOutput      triggerTrue;
  static void             initClass();
  static void             exitClass();


 protected:
  virtual ~SoVRMLBooleanTrigger();
  virtual void        evaluate(SoVRMLInterpOutput *interp);

 private:
  SbBool              needsEvaluation;        // Dirty bit

};

#endif /* _SO_VRMLBOOLEANTRIGGER_ */

