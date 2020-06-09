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


#ifndef  _SO_VRMLPOSITIONINTERPOLATOR2D_
#define  _SO_VRMLPOSITIONINTERPOLATOR2D_

#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/VRMLnodes/SoVRMLInterpolator.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/VRMLnodes/SoVRMLSubInterpolator.h>
//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLPositionInterpolator2D
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Interpolates among a set of position values.
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
 *   This node linearly interpolates among a set of SFVec3f values. This is
 *   appropriate for interpolating a translation. The vectors are interpreted as
 *   absolute positions in object space. The #keyValue field must contain
 *   exactly as many values as in the #key field.
 *   
 *   Refer to "Concepts - Interpolators" for a more detailed discussion of
 *   interpolators.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLPositionInterpolator {
 *    @TABLE_FILE_FORMAT
 *       @TR key        @TD []
 *       @TR keyValue   @TD []
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFFloat   @TD   set_fraction      
 *       @TR   SoMFFloat   @TD   set_key      
 *       @TR   SoMFVec3f   @TD   set_keyValue
 *       @TR   SoSFNode    @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFVec2f   @TD   value_changed      
 *       @TR   SoMFFloat   @TD   key_changed      
 *       @TR   SoMFVec2f   @TD   keyValue_changed
 *       @TR   SoSFNode    @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLPositionInterpolator2D : public SoVRMLInterpolator {

  SO_INTERPOLATOR_HEADER(SoVRMLPositionInterpolator2D);

 public:
  /**
   * Key array.
   */
  SoMFFloat key;

  /**
   * KeyValue array.
   *
   */
  SoMFVec2f keyValue;

  /**
   * Constructor.
   */
  SoVRMLPositionInterpolator2D();

 SoINTERNAL public:
  SoSFFloat               set_fraction;
  SoVRMLInterpOutput      value_changed;
  static void             initClass();
  static void             exitClass();
 protected:    
  virtual ~SoVRMLPositionInterpolator2D();
  virtual void        evaluate(SoVRMLInterpOutput *interp);
  
 private:
  SbBool              needsEvaluation;        // Dirty bit

};

#endif /* _SO_VRMLPOSITIONINTERPOLATOR2D_ */
