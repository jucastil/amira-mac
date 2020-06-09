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


#ifndef  _SO_VRMLORIENTINTERPOLATOR_
#define  _SO_VRMLORIENTINTERPOLATOR_

#include <Inventor/fields/SoMFRotation.h>
#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/VRMLnodes/SoVRMLInterpolator.h>
#include <Inventor/VRMLnodes/SoVRMLSubInterpolator.h>
//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLOrientationInterpolator
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Interpolates among a set of rotation values.
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
 *   This node interpolates among a set of SFRotation values. The rotations are
 *   absolute in object space and are, therefore, not cumulative. The #keyValue
 *   field must contain exactly as many rotations as there are keyframes in the
 *   #key field, or an error will be generated and results will be undefined.
 *   
 *   An orientation represents the final position of an object after a rotation has
 *   been applied. An SoVRMLOrientationInterpolator will interpolate between two
 *   orientations by computing the shortest path on the unit sphere between the two
 *   orientations. The interpolation will be linear in arc length along this path.
 *   The path between two diagonally opposed orientations will be any one of the
 *   infinite possible paths with arc length pi. 
 *   
 *   If two consecutive keyValue values exist such that the arc length between them is
 *   greater than pi, then the interpolation will take place on the arc complement.
 *   For example, the interpolation between the orientations:
 *   
 *   <PRE>
 *    0 1 0 0 --> 0 1 0 5.0
 *    </PRE>
 *    is equivalent to the rotation between the two orientations:
 *   
 *   <PRE>
 *    0 1 0 2*PI --> 0 1 0 5.0 
 *    </PRE>
 *    Refer to "Concepts - Interpolators" for a more detailed discussion of
 *   interpolators.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLOrientationInterpolator {
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
 *       @TR   SoMFRotation   @TD   set_keyValue
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFRotation   @TD   value_changed      
 *       @TR   SoMFFloat   @TD   key_changed      
 *       @TR   SoMFRotation   @TD   keyValue_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLOrientationInterpolator : public SoVRMLInterpolator {

  SO_INTERPOLATOR_HEADER(SoVRMLOrientationInterpolator);

 public:
  // Fields
  SoMFFloat           key;
  SoMFRotation        keyValue;       

  // Events

  /**
   * Constructor.
   */
  SoVRMLOrientationInterpolator();

 SoINTERNAL public:
  SoSFFloat               set_fraction;
  SoVRMLInterpOutput      value_changed;
  static void             initClass();
  static void             exitClass();

 protected:
  virtual ~SoVRMLOrientationInterpolator();
  virtual void        evaluate(SoVRMLInterpOutput *interp);
  
 private:
  SbBool              needsEvaluation;        // Dirty bit

};

#endif /* _SO_VRMLORIENTINTERPOLATOR_ */

