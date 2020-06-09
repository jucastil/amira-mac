/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Chris Marrin (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_VRMLLINE_PROPERTIES_
#define  _SO_VRMLLINE_PROPERTIES_

#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>

/**
 * @VSGEXT Specifies additional properties to be applied to all line geometry.
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
 *   The SoVRMLLineProperties node specifies additional properties to be applied
 *   to all line geometry. The linetype and linewidth will only be applied when
 *   the #applied field has value TRUE. When the value of the #applied field is FALSE, 
 *   a solid line of nominal width will be produced. The color of the line is specified 
 *   by the associated Material node.
 *   
 *   The #linewidthScaleFactor is a multiplicative value that scales a 
 *   nominal linewidth by the linewidth scale factor. This resulting value will then 
 *   be mapped to the nearest available line width. A value less than or equal to zero 
 *   refers to the minimum available line width.
 *
 * @FILE_FORMAT_DEFAULT
 *    VRMLLineProperties {
 *    @TABLE_FILE_FORMAT
 *       @TR applied               @TD TRUE
 *       @TR lineType              @TD 1
 *       @TR linewidthScaleFactor  @TD 0
 *       @TR metaData              @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoCallbackAction  @BR
 *
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN       
 *       @TR   SoSFBool    @TD   set_applied      
 *       @TR   SoSFInt32   @TD   set_lineType      
 *       @TR   SoSFFloat   @TD   set_linewidthScaleFactor      
 *       @TR   SoSFNode    @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFBool    @TD   applied_changed      
 *       @TR   SoSFInt32   @TD   lineType_changed      
 *       @TR   SoSFFloat   @TD   linewidthScaleFactor_changed      
 *       @TR   SoSFNode    @TD   metadata_changed
 *    @TABLE_END
 *   
 * 
 */ 

class INVENTOR_API SoVRMLLineProperties : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLLineProperties);

 public:
  /**
   * Constructor.
   */
  SoVRMLLineProperties();

  // Fields 
  /**
   * Specifies if the lineType and lineScaleFactor should
   * be applied. If FALSE, a solid line of nominal width is used.
   * 
   */
  SoSFBool            applied;
  /** 
   * The linetype field selects a line pattern. The following 
   * values of lineType are supported:
   *
 *   @TABLE_1B
 *   @TR
 *   @B lineType@b
 *   @TD @B Line Pattern@b
 *   @TR
 *   1 @BR
 *   2 @BR
 *   3 @BR
 *   4 @BR
 *   5 @BR
 *   @TD 
 *   Solid @BR
 *   Dashed @BR
 *   Dotted @BR
 *   Dashed-dotted @BR
 *   Dash-dot-dot @BR
 *   @TABLE_END
   * 
   */
  SoSFInt32           lineType;
  /**
   * The linewidthScaleFactor is a multiplicative value that scales
   * a nominal linewidth by the linewidth scale factor. 
   * This resulting value will then be mapped to the nearest 
   * available line width. A value less than or equal to zero refers 
   * to the minimum available line width.
   *
   */
  SoSFFloat           linewidthScaleFactor;

  /**
   * Set the state of the override field.
   * see SoNode::setOverride doc.
   */
  inline virtual void setOverride(const SbBool state)
  { override.setValue(state); }

  /**
   * Returns the state of the override field.
   */
  inline virtual SbBool isOverride() const
  { return override.getValue(); }

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
    
 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  SoSFBool override;

 protected:
  virtual ~SoVRMLLineProperties();
    
 private:
  static unsigned short  line[5];      

  // Thread static variables
  struct MTstruct {
    SbBool first;
  };
};

#endif /* _SO_VRMLLINE_PROPERTIES_ */

