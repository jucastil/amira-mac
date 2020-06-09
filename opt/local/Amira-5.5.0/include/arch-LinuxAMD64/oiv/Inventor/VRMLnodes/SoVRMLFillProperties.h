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


#ifndef  _SO_VRMLFILL_PROPERTIES_
#define  _SO_VRMLFILL_PROPERTIES_

#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLFillProperties
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Specifies additional properties to be applied to all polygonal areas
 *         on top of whatever appearance is specified.\ @NO_ACTION
 *
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
 *   The FillProperties node specifies additional properties to be applied to 
 *   all polygonal areas on top of whatever appearance is specified by the 
 *   other fields of the respective Appearance node. Thus, hatches are applied 
 *   on top of the already rendered appearance of the node. Hatches are not 
 *   affected by lighting. 
 *   
 *   The #hatchStyle field selects a hatch pattern 
 *   as defined in the International Register of Graphical Items 
 *   (see 2.[REG] <../references.html>). The hatches are rendered using the 
 *   color specified by the #hatchColor field.
 *   The associated geometry must be filled and/or hatched only when the 
 *   respective values of the #filled and/or #hatched fields have value TRUE.
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLFillProperties {
 *    @TABLE_FILE_FORMAT
 *       @TR filled         @TD TRUE
 *       @TR hatchColor     @TD 1 1 1
 *       @TR hatched        @TD TRUE 
 *       @TR hatchStyle     @TD 1
 *       @TR metadata     @TD NULL 
 *    @TABLE_END
 *    }
 *
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR SoSFBool   @TD set_filled      
 *       @TR SoSFColor  @TD set_hatchColor  
 *       @TR SoSFBool   @TD set_hatched    
 *       @TR SoSFInt32  @TD set_hatchStyle
 *       @TR   SoSFNode   @TD   set_metadata   
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR SoSFBool   @TD filled_changed      
 *       @TR SoSFColor  @TD hatchColor_changed  
 *       @TR SoSFBool   @TD hatched_changed    
 *       @TR SoSFInt32  @TD hatchStyle_changed
 *       @TR   SoSFNode   @TD   metadata_changed   
 *    @TABLE_END
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoRayPickAction,  SoGetBoundingBoxAction,  SoCallbackAction  @BR
 * 
 * 
 * 
 */ 

 class INVENTOR_API SoVRMLFillProperties : public SoVRMLNode {
  
   SO_NODE_HEADER(SoVRMLFillProperties);

 public:
  /**
   * Constructor.
   */
  SoVRMLFillProperties();

  // Fields    
  /**
   * Specifies whether the area is filled.
   * 
   */
  SoSFBool            filled;
   /**
   * Specifies whether the area is hatched.
   * 
   */
  SoSFBool            hatched;
 
  /**
   * Specifies the color of the hatch lines.
   *
   */
  SoSFColor           hatchColor;
  /**
   * Defines the hatch style.
   *
   */
  SoSFInt32           hatchStyle;

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
    
 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();


 protected:
  virtual ~SoVRMLFillProperties();
    
 private:
};

#endif /* _SO_VRMLFILL_PROPERTIES_ */

