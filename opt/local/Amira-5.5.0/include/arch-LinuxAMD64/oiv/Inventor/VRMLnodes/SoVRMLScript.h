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


#ifndef  _SO_VRMLSCRIPT_
#define  _SO_VRMLSCRIPT_

#include <Inventor/SbLinear.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLScript
//
//  VRMLScript source node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Used to program behavior in a scene.\ @NO_ACTION
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   The SoVRMLScript node is used to program behavior in a scene. SoVRMLScript nodes
 *   typically receive events that signify a change or user action, contain a program
 *   module that performs some computation, and effect change somewhere else in the
 *   scene by sending output events.
 * 
 * @VRML2_SPECIFICATION
 *    This section describes the expected behavior of the node in a conforming VRML97
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *   This section may reference portions of the VRML97 specification that are not
 *   present in this help file. The complete VRML97 spec is available at
 *   @B http://www.web3d.org @b.
 *   
 *   The SoVRMLScript node is used to program behavior in a scene. SoVRMLScript nodes
 *   typically receive events that signify a change or user action, contain a program
 *   module that performs some computation, and effect change somewhere else in the
 *   scene by sending output events. Each SoVRMLScript node has associated
 *   programming language code, referenced by the #url field, that is executed
 *   to carry out the SoVRMLScript node's function. That code will be referred to as
 *   "the script" in the rest of this description.
 *   
 *   Browsers are not required to support any specific language. See the section in
 *   "Concepts - Scripting" for detailed information on scripting languages. Browsers
 *   are required to adhere to the language bindings of languages specified in
 *   annexes of the specification. See the section "Concepts - URLS and URNs" for
 *   details on the #url field.
 *   
 *   When the script is created, any language-dependent or user-defined initialization
 *   is performed. The script is able to receive and process events that are sent to
 *   it. Each event that can be received must be declared in the SoVRMLScript node
 *   using the same syntax as is used in a prototype definition: 
 *   
 *   <PRE>
 *    eventIn @I type name @i
 *    @I  @i </PRE>
 *    The type can be any of the standard VRML fields (see "Field
 *   Reference"), and name must be an identifier that is unique for this SoVRMLScript
 *   node. 
 *   
 *   The SoVRMLScript node should be able to generate events in response to the
 *   incoming events. Each event that can be generated must be declared in the
 *   SoVRMLScript node using the following syntax: 
 *   
 *   <PRE>
 *    eventOut type name
 *    </PRE>
 *    SoVRMLScript nodes cannot have exposedFields. The implementation
 *   ramifications of exposedFields is far too complex and thus not allowed. 
 *   
 *   If the SoVRMLScript node's #mustEvaluate field is FALSE, the browser can
 *   delay sending input events to the script until its outputs are needed by the
 *   browser. If the #mustEvaluate field is TRUE, the browser should send input
 *   events to the script as soon as possible, regardless of whether the outputs are
 *   needed. The #mustEvaluate field should be set to TRUE only if the
 *   SoVRMLScript has effects that are not known to the browser (such as sending
 *   information across the network); otherwise, poor performance may result.
 *   
 *   Once the script has access to a VRML node (via an SFNode or MFNode value either
 *   in one of the SoVRMLScript node's fields or passed in as an eventIn), the script
 *   should be able to read the contents of that node's exposed field. If the
 *   SoVRMLScript node's #directOutput field is TRUE, the script may also send
 *   events directly to any node to which it has access, and may dynamically
 *   establish or break routes. If #directOutput is FALSE (the default), then
 *   the script may only affect the rest of the world via events sent through its
 *   eventOuts. 
 *   
 *   A script is able to communicate directly with the VRML browser to get the current
 *   time, the current world URL, and so on. This is strictly defined by the API for
 *   the specific language being used.
 *   
 *   It is expected that all other functionality (such as networking capabilities,
 *   multi-threading capabilities, and so on) will be provided by the scripting
 *   language.
 *   
 *   The location of the SoVRMLScript node in the scene graph has no effect on its
 *   operation. For example, if a parent of an SoVRMLScript node is an SoVRMLSwitch
 *   node with @B whichChoice @b set to -1 (i.e., ignore its children), the
 *   SoVRMLScript continues to operate as specified (receives and sends events).
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLScript {
 *    @TABLE_FILE_FORMAT
 *       @TR metadata         @TD NULL
 *       @TR url              @TD []
 *       @TR directedOutput   @TD FALSE
 *       @TR mustEvaluate     @TD FALSE
 *    @TABLE_END
 *    }
 *
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoMFString   @TD   set_url      
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoMFString   @TD   url _changed     
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END

 * 
 * 
 */ 

class INVENTOR_API SoVRMLScript : public SoNode {

  SO_NODE_HEADER(SoVRMLScript);

public:

  // Fields
  /**
   * Associated programming language code.
   * 
   */
  SoMFString         url;
  /**
   * If TRUE, the script can send events directly to the other nodes. If FALSE, the
   * scripts must use eventOuts to affect the rest of the world. Default is FALSE.
   * 
   */
  SoSFBool           directOutput;
  /**
   * If FALSE, delay sending input events to the script until needed. If TRUE, send
   * as soon as possible. Default is FALSE.
   * 
   */
  SoSFBool           mustEvaluate;
  /**
   * Specifies the metadata node
   * 
   */
  SoSFNode            metadata;

  /**
   * Constructor.
   */
  SoVRMLScript();

 SoEXTENDER public:

  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        pick(SoPickAction *action);
  virtual void        handleEvent(SoHandleEventAction *action);
  virtual void        write(SoWriteAction *writeAction);

 SoINTERNAL public:

  static void         initClass();
  static void         exitClass();

 protected:

  virtual  ~SoVRMLScript();

  virtual void        copyContents(const SoFieldContainer *fromFC,
                                   SbBool copyConnections);

  ///////////////////////EXCEPTION METHODS/////////////////////////////////////
  //
  // #unfound eventTypeName
  // #unfound fieldTypeName
  //
  /////////////////////////////////////////////////////////////////////////////

};

#endif /* _SO_VRMLSCRIPT_ */

