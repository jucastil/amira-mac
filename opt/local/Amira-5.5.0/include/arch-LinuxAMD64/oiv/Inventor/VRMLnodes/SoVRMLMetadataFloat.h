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


#ifndef  _SO_VRMLMETADATA_FLOAT_
#define  _SO_VRMLMETADATA_FLOAT_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/VRMLnodes/SoVRMLMetadataObject.h>
//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLMetadataFloat
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Provides Metadata in single precision.
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
 *   SoVRMLMetadataFloat provides Metadata in single precision values.
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction  @BR
 *
 * @FILE_FORMAT_DEFAULT
 *    VRMLMetadataFloat {
 *    @TABLE_FILE_FORMAT
 *       @TR reference      @TD ""
 *       @TR name           @TD ""
 *       @TR value          @TD []
 *       @TR metadata       @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN       
 *       @TR   SoMFFloat    @TD   set_value
 *       @TR   SoSFNode     @TD   set_metadata      
 *       @TR   SoSFString   @TD   set_name      
 *       @TR   SoSFString   @TD   set_reference     
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoMFFloat    @TD   value_changed 
 *       @TR   SoSFNode     @TD   metadata_changed
 *       @TR   SoSFString   @TD   name_changed      
 *       @TR   SoSFString   @TD   reference _changed     
 *    @TABLE_END
 * 
 * 
 */ 

class INVENTOR_API SoVRMLMetadataFloat : public SoVRMLMetadataObject {

  SO_NODE_HEADER(SoVRMLMetadataFloat);

 public:
  /**
   * The metadata provided by this node is contained in the 
   * single-precision floating point numbers of the value field. 
   */
  SoMFFloat             value;
  /**
   * Constructor
   */
  SoVRMLMetadataFloat(); 

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);

 protected:

  virtual ~SoVRMLMetadataFloat();
};

#endif /* _SO_VRMLMETADATA_FLOAT_ */


