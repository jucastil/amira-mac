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


#ifndef  _SO_VRMLMETADATA_INTEGER_
#define  _SO_VRMLMETADATA_INTEGER_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/VRMLnodes/SoVRMLMetadataObject.h>
//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLMetadataInteger
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Provides Metadata in 32-bit integer precision.
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
 *   SoVRMLMetadataInteger provides Metadata in integer precision values.
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction  @BR
 *
 * @FILE_FORMAT_DEFAULT
 *    VRMLMetadataInteger {
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
 *       @TR   SoMFInt32    @TD   set_value
 *       @TR   SoSFNode     @TD   set_metadata      
 *       @TR   SoSFString   @TD   set_name      
 *       @TR   SoSFString   @TD   set_reference     
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoMFInt32    @TD   value_changed 
 *       @TR   SoSFNode     @TD   metadata_changed
 *       @TR   SoSFString   @TD   name_changed      
 *       @TR   SoSFString   @TD   reference _changed     
 *    @TABLE_END
 * 
 * 
 */ 

class INVENTOR_API SoVRMLMetadataInteger : public SoVRMLMetadataObject {

  SO_NODE_HEADER(SoVRMLMetadataInteger);

 public:
  /**
   * The metadata provided by this node is contained in the 
   * integers of the value field.
   */
  SoMFInt32             value;
  /**
   * Constructor
   */
  SoVRMLMetadataInteger(); 

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);

 protected:

  virtual ~SoVRMLMetadataInteger();
};

#endif /* _SO_VRMLMETADATA_INTEGER_ */

