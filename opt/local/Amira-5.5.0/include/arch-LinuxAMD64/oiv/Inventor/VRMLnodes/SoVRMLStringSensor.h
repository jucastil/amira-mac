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



#ifndef  _SO_VRMLSTRINGSENSOR_
#define  _SO_VRMLSTRINGSENSOR_

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>
//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLStringSensor
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
 *   A StringSensor node generates events as the user presses keys 
 *   on the keyboard. A StringSensor node can be enabled or disabled 
 *   by sending it an #enabled event with a value of TRUE or FALSE. 
 *   If the StringSensor node is disabled, it does not track 
 *   keyboard input or send events.
 *   
 *   #enteredText events are generated as keys which produce characters 
 *   are pressed on the keyboard. The value of this event is the 
 *   UTF-8 string entered including the latest character struck. 
 *   The set of UTF-8 characters that can be generated will vary 
 *   between different keyboards and different implementations. 
 *   
 *   If a #deletionAllowed has value TRUE, the previously entered 
 *   character in the #enteredText is removed when the browser-recognized 
 *   value for deleting the preceding character of a string is entered. 
 *   Typically, this value is defined by the local operating system. 
 *   If #deletionAllowed has value FALSE, characters may only be added 
 *   to the string; deletion of characters will not be allowed. 
 *   Should the browser-recognized value for deleting the preceding 
 *   character is entered, it will be ignored.
 *   
 *   The #finalText event is generated whenever the browser-recognized 
 *   value for terminating a string is entered. Typically, this value 
 *   is defined by the local operating system. When this recognition 
 *   occurs, the #finalText field generates an event with value equal 
 *   to that of #enteredText. After the #finalText field event has been 
 *   generated, the #enteredText field is set to the empty string but
 *   no event is generated.
 *   
 *   When the user begins typing, the StringSensor sends an #isActive 
 *   event with value TRUE. When the string is terminated, the 
 *   StringSensor sends an #isActive event with value FALSE.
 *   
 *   The StringSensor is not affected by its position in the 
 *   transformation hierarchy.
 *
 *   See "Key device sensor component" for more details.
 *   
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLStringSensor {
 *    @TABLE_FILE_FORMAT
 *       @TR deletionAllowed    @TD TRUE
 *       @TR enabled            @TD TRUE
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFBool   @TD   set_deletionAllowed      
 *       @TR   SoSFBool   @TD   set_enabled
 *       @TR   SoSFNode   @TD   set_metadata      
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT
 *       @TR   SoSFString @TD   enteredText
 *       @TR   SoSFString @TD   finalText
 *       @TR   SoSFBool   @TD   isActive
 *       @TR   SoSFBool   @TD   deletionAllowed_changed      
 *       @TR   SoSFBool   @TD   enabled_changed
 *       @TR   SoSFNode   @TD   metadata_changed      
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLStringSensor : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLStringSensor);

 public:
  // Fields
  /** 
   * Enables (TRUE) or disables (FALSE) the deletion of text
   * in the enteredText eventOut
   * 
   */
  SoSFBool            deletionAllowed;
  /**
   * Enables (TRUE) or disables (FALSE) the sensor.
   * 
   */
  SoSFBool            enabled;
  /**
   * Constructor.
   */
  SoVRMLStringSensor();

  // Overrides default method on SoNode
  virtual SbBool      affectsState() const;

  /**
   * Enables/disables events for @I all @i SoVRMLStringSensor objects. If you have
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
  SoSFString          enteredText;          // eventOut
  SoSFString          finalText;            // eventOut

 protected:
  virtual ~SoVRMLStringSensor();
 
  static SbBool enableEventsFlag;

 private:
};

#endif /* _SO_VRMLSTRINGSENSOR_ */

