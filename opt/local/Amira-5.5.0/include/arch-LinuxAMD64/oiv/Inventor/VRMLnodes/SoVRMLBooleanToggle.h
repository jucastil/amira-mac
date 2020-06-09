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


#ifndef  _SO_VRMLBOOLEANTOGGLE_
#define  _SO_VRMLBOOLEANTOGGLE_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLBooleanToggle
//
//////////////////////////////////////////////////////////////////////////////

/**
 * 
 * @VSGEXT Stores a boolean value for toggling on/off.
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
 *   This utility event stores a boolean value for toggling on and off.
 *
 *   When a #set_boolean TRUE event is received, the BooleanToggle negates the value
 *   of the toggle field and generates the corresponding toggle field output event.
 *   #set_boolean FALSE events are ignored.
 *   
 *   The BooleanToggle can be reset to a specific state by directly setting the 
 *   value of the inputOutput toggle field. 
 *  
 *   Refer to "Event Utilities Component" for a more detailed discussion.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLBooleanToggle {
 *    @TABLE_FILE_FORMAT
 *       @TR toggle       @TD FALSE
 *       @TR metadata     @TD NULL 
 *    @TABLE_END
 *    }
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFBool    @TD   set_boolean 
 *       @TR   SoSFBool    @TD   set_toggle
 *       @TR   SoSFNode   @TD   set_metadata           
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFBool    @TD   toggle_changed
 *       @TR   SoSFNode   @TD   metadata_changed           
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLBooleanToggle : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLBooleanToggle);

 public:
  // Fields
  /**
   * The boolean value for toggling on/off.
   */
  SoSFBool            toggle;

  /**
   * Constructor.
   */
  SoVRMLBooleanToggle();

 SoINTERNAL public:
  SoSFBool                set_boolean;
  static void             initClass();
  static void             exitClass();
  virtual void        notify(SoNotList *list);

 protected:
  virtual ~SoVRMLBooleanToggle();
  virtual SbBool      readInstance(SoInput *in, unsigned short flags);

 private:

   int internalSetValue;
};

#endif /* _SO_VRMLBOOLEANTOGGLE_ */

