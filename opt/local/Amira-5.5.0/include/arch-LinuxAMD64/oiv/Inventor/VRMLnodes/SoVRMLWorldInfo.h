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



#ifndef  _SO_VRMLWORLDINFO_
#define  _SO_VRMLWORLDINFO_

#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLWorldInfo
//
//  Node that holds application-specific information as a title and 
//  text strings.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Contains information about the world.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   See the VRML97 Specification, below.
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
 *   The SoVRMLWorldInfo node contains information about the world. This node has no
 *   effect on the visual appearance or behavior of the world - it is strictly for
 *   documentation purposes. The #title field is intended to store the name or
 *   title of the world so that browsers can present this to the user - for instance,
 *   in their window border. Any other information about the world can be stored in
 *   the #info field - for instance, the scene author, copyright information,
 *   and public domain information.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    SoVRMLWorldInfo {
 *    @TABLE_FILE_FORMAT
 *       @TR info    @TD []
 *       @TR title   @TD ""
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 *
 * @EVENTS
 *
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 *
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 *
 * 
 */ 

class INVENTOR_API SoVRMLWorldInfo : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLWorldInfo);

 public:
  // Fields

  /**
   * Title of the world.
   * 
   */
  SoSFString          title;

  /**
   * Any additional information that the author wishes to pass to the user.
   * 
   */
  SoMFString          info;

  /**
   * Constructor.
   */
  SoVRMLWorldInfo();

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoVRMLWorldInfo();

  // NOTE: No actions for this node. It's pretty passive.
};

#endif /* _SO_VRMLWORLDINFO_ */

