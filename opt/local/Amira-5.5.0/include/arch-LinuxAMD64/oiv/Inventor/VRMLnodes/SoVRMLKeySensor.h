/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : SGI (MMM YYYY)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/



#ifndef  _SO_VRMLKEYSENSOR_
#define  _SO_VRMLKEYSENSOR_

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLKeySensor
//
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Maps pointing device motion onto a plane.\ @NO_ACTION
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
 *   The SoVRMLKeySensor node generates events when the user presses keys on the keyboard.
 *   A SoVRMLKeySensor node can be enabled or disabled by sending it an #enabled event with
 *   TRUE or FALSE. If the SoVRMLKeySensor node is disabled, it does not track keyboard
 *   input or send events.
 *
 *   #keyPress and #keyRelease events are generated as keys which produce characters
 *   are pressed or released on the keyboard. The values of these events is a string
 *   of length 1 containing the single UTF-8 character associated with the key pressed.
 *   
 *   #actionKeyPress and #actionKeyRelease events are generated as 'action' keys are
 *   pressed and released on the keyboard.
 *   
 *   Action Key Values
 *   @TABLE_1B
 *   @TR
 *   HOME @BR
 *   PGDN @BR
 *   LEFT @BR
 *   END @BR
 *   UP @BR
 *   RIGHT @BR
 *   PGUP @BR
 *   DOWN @BR
 *   F1-F12 @BR
 *   @TD 
 *   13 @BR
 *   16 @BR
 *   19 @BR
 *   14 @BR
 *   17 @BR
 *   20 @BR
 *   15 @BR
 *   18 @BR
 *   1-12 @BR
 *   @TABLE_END
 *
 *   #shiftKey_depressed, #controlKey_depressed, and #altKey_depressed events are generated
 *   as the shift, control, and alt keys on the keyboard are pressed and released. Their 
 *   value is TRUE when the key is pressed and FALSE when the key is released.
 *
 *   When a key is pressed, the SoVRMLKeySensor sends an #isActive event with the value
 *   TRUE. Once the key is released, the SoVRMLKeySensor sends an #isActive event
 *   with the value FALSE.
 *   
 *   The SoVRMLKeySensor is not affected by its position in the transformation hierarchy.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLKeySensor {
 *    @TABLE_FILE_FORMAT
 *       @TR enabled  @TD TRUE
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFBool   @TD   set_enabled
 *       @TR   SoSFNode   @TD   set_metadata      
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT 
 *       @TR   SoSFBool    @TD   enabled_changed      
 *       @TR   SoSFInt32   @TD   actionKeyPress      
 *       @TR   SoSFInt32   @TD   actionKeyRelease      
 *       @TR   SoSFBool    @TD   altKey      
 *       @TR   SoSFBool    @TD   controlKey 
 *       @TR   SoSFBool    @TD   shiftKey
 *       @TR   SoSFBool    @TD   isActive      
 *       @TR   SoSFString  @TD   keyPress      
 *       @TR   SoSFString  @TD   keyRelease
 *       @TR   SoSFNode   @TD   metadata_changed     
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLKeySensor : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLKeySensor);

 public:
  // Fields
  /**
   * Enables (TRUE) or disables (FALSE) the sensor.
   * 
   */
  SoSFBool            enabled;
  /**
   * Constructor.
   */
  SoVRMLKeySensor();

  // Overrides default method on SoNode
  virtual SbBool      affectsState() const;

  /**
   * Enables/disables events for @I all @i SoVRMLKeySensor objects. If you have
   * created several objects of this class, you can disable/enable events for all of
   * them with a single call to this method. 
   */
  static void enableEvents(SbBool OnOffFlag);

  /**
   * Queries if events are enabled for all objects of this class.
   */
  static SbBool isEventsEnabled();

 SoEXTENDER public:

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();
  SoSFBool            isActive;             // eventOut
  SoSFInt32           actionKeyPress;       // eventOut
  SoSFInt32           actionKeyRelease;     // eventOut
  SoSFBool            altKey;               // eventOut
  SoSFBool            controlKey;           // eventOut
  SoSFString          keyPress;             // eventOut
  SoSFString          keyRelease;           // eventOut
  SoSFBool            shiftKey;             // eventOut

 protected:
  virtual ~SoVRMLKeySensor();
 
  static SbBool enableEventsFlag;

 private:
};

#endif /* _SO_VRMLKEYSENSOR_ */

