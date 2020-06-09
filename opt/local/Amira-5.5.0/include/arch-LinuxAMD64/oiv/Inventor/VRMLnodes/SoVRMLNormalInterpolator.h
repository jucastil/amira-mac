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


#ifndef  _SO_VRMLNORMALINTERPOLATOR_
#define  _SO_VRMLNORMALINTERPOLATOR_

#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/VRMLnodes/SoVRMLInterpolator.h>
#include <Inventor/VRMLnodes/SoVRMLSubInterpolator.h>
//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLNormalInterpolator
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Interpolates among a set of normals.
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
 *   This node interpolates among a set of multi-valued Vec3f values, suitable for
 *   transforming normal vectors. All output vectors will have been normalized by the
 *   interpolator. 
 *   
 *   The number of normals in the #keyValue field must be an integer multiple of
 *   the number of keyframes in the #key field; that integer multiple defines
 *   how many normals will be contained in the @B value_changed @b events. 
 *   
 *   Normal interpolation is to be performed on the surface of the unit sphere. That
 *   is, the output values for a linear interpolation from a point P on the unit
 *   sphere to a point Q also on unit sphere should lie along the shortest arc (on
 *   the unit sphere) connecting points P and Q. Also, equally spaced input fractions
 *   will result in arcs of equal length. Cases where P and Q are diagonally opposing
 *   allow an infinite number of arcs. The interpolation for this case can be along
 *   any one of these arcs.
 *   
 *   Refer to "Concepts - Interpolators" for a more detailed discussion of
 *   interpolators.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLNormalInterpolator {
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
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoMFVec3f   @TD   value_changed      
 *       @TR   SoMFFloat   @TD   key_changed      
 *       @TR   SoMFVec3f   @TD   keyValue_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLNormalInterpolator : public SoVRMLInterpolator {

  SO_INTERPOLATOR_HEADER(SoVRMLNormalInterpolator);

 public:
  // Fields
  SoMFFloat           key;
  SoMFVec3f           keyValue;       

  // Events

  /**
   * Constructor.
   */
  SoVRMLNormalInterpolator();

 SoINTERNAL public:
  SoSFFloat               set_fraction;
  SoVRMLInterpOutput      value_changed;
  static void             initClass();
  static void             exitClass();

  // Propagates modification notification through an instance.
  virtual void        notify(SoNotList *list);

 protected:
  virtual ~SoVRMLNormalInterpolator();
  virtual void        evaluate(SoVRMLInterpOutput *interp);
  
 private:
  SbBool              needsEvaluation;        // Dirty bit
  SbVec3f             *p3;
  int                 m_numMult;

};

#endif /* _SO_VRMLNORMALINTERPOLATOR_ */

