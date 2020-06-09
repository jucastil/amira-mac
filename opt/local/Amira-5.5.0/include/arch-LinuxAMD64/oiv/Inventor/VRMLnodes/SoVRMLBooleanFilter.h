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


#ifndef  _SO_VRMLBOOLEANFILTER_
#define  _SO_VRMLBOOLEANFILTER_

#include <Inventor/VRMLnodes/SoVRMLInterpolator.h>
#include <Inventor/VRMLnodes/SoVRMLSubInterpolator.h>
#include <Inventor/fields/SoSFBool.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLBooleanFilter
//
//////////////////////////////////////////////////////////////////////////////

/**
 * 
 * @VSGEXT Filters boolean events
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
 *   This node filters boolean events, allowing for selective routing of TRUE or FALSE
 *   values and negation.
 *
 *   When the set_boolean event is received, the BooleanFilter node generates two events:
 *   either inputTrue or inputFalse, based on the boolean value received; and inputNegate,
 *   which contains the negation of the value received.
 *
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLBooleanFilter {
 *    @TABLE_FILE_FORMAT
 *       @TR metadata     @TD NULL
 *    @TABLE_END 
 *    }
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFBool    @TD   set_boolean
 *       @TR   SoSFNode   @TD   set_metadata      
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFBool    @TD   inputFalse      
 *       @TR   SoSFBool    @TD   inputNegate      
 *       @TR   SoSFBool    @TD   inputTrue
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLBooleanFilter : public SoVRMLInterpolator {

  SO_INTERPOLATOR_HEADER(SoVRMLBooleanFilter);

 public:

  /**
   * Constructor.
   */
  SoVRMLBooleanFilter();

 SoINTERNAL public:
  SoSFBool                set_boolean;
  SoVRMLInterpOutput      inputFalse;
  SoVRMLInterpOutput      inputNegate;
  SoVRMLInterpOutput      inputTrue;

  static void             initClass();
  static void         exitClass();
 protected:
  virtual ~SoVRMLBooleanFilter();
  virtual void        evaluate(SoVRMLInterpOutput *interp);

 private:
  SbBool              needsEvaluation;        // Dirty bit

};

#endif /* _SO_VRMLBOOLEANFILTER_ */

