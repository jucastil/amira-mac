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


#ifndef  _SO_VRMLMETADATA_OBJECT_
#define  _SO_VRMLMETADATA_OBJECT_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>
//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLMetadataObject
//
//  Abstract base class for all Metadata Objects
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Abstract base class for all X3D MetadataObject nodes.
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

 *   SoVRMLMetadataObject is the abstract base class for all 
 *   MetadataObjects.
 *
 *   Metadata is information that is associated with the objects 
 *   of the X3D world but is not a direct part of the world 
 *   representation. The SoVRMLMetadataObject defines an abstract 
 *   interface that identifies a node as containing metadata and 
 *   metadata nodes that specify metadata values in various data types.
 * 
 * @FILE_FORMAT_DEFAULT
 *   This is an abstract class. See the reference page of a derived class for the
 *   format and default values.
 *
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction  @BR
 *
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFNode     @TD   set_metadata      
 *       @TR   SoSFString   @TD   set_name      
 *       @TR   SoSFString   @TD   set_reference      
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFNode     @TD   metadata_changed      
 *       @TR   SoSFString   @TD   name_changed      
 *       @TR   SoSFString   @TD   reference _changed     
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLMetadataObject : public SoVRMLNode {

  SO_NODE_ABSTRACT_HEADER(SoVRMLMetadataObject);

 public:
  /**
   * The specification of the reference field is optional. If provided, 
   * it identifies the metadata standard or other specification that defines 
   * the name field. If the reference field is not provided or is empty, 
   * the meaning of the #name field is considered implicit to the 
   * characters in the string.
   * 
   */
  SoSFString           reference;
  /**
   * The specification of the #reference field is optional. If provided, 
   * it identifies the metadata standard or other specification that defines 
   * the name field. If the #reference field is not provided or is empty, 
   * the meaning of the name field is considered implicit to the 
   * characters in the string.
   * 
   */
  SoSFString           name;   

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);

 protected:
  SoVRMLMetadataObject();                              // Makes this abstract

  virtual ~SoVRMLMetadataObject();
};

#endif /* _SO_VRMLMETADATA_OBJECT_ */

