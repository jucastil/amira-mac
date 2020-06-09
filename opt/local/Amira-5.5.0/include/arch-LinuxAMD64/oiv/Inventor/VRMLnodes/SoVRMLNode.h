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



#ifndef  _SO_VRMLNODE_
#define  _SO_VRMLNODE_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/nodes/SoNode.h>
//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLNode
//
//  Abstract classs to derive all VRML nodes from to get the field
//  metadata 
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Abstract base class for all VRML nodes.
 * 
 * 
 * @DESCRIPTION
 *   Most X3D nodes are derived from SoVRMLNode. The field metadata is common
 *   to all X3D nodes. The nodes that can not be derived from SoVRMLNode
 *   have a metadata field. It is included in the VRML97 nodes but will not
 *   be written out unless it is set.
 * 
 * @FILE_FORMAT_DEFAULT
 *    This is an abstract class. See the reference page of a derived class for the
 *   format and default values.
 *
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

class INVENTOR_API SoVRMLNode : public SoNode {

  SO_NODE_ABSTRACT_HEADER(SoVRMLNode);

 public:
  /**
   * Specifies the metadata node
   * 
   */
  SoSFNode            metadata;

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);

 protected:
  SoVRMLNode();                              // Makes this abstract

  virtual ~SoVRMLNode();
};

#endif /* _SO_VRMLNODE_ */

