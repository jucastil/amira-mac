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


#ifndef  _SO_VRMLSCALARINTERPOLATOR_
#define  _SO_VRMLSCALARINTERPOLATOR_

#include <Inventor/VRMLnodes/SoVRMLInterpolator.h>
#include <Inventor/VRMLnodes/SoVRMLSubInterpolator.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFFloat.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLScalarInterpolator
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Interpolates among a set of float values.
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
 *   This node linearly interpolates among a set of SFFloat values. This interpolator
 *   is appropriate for any parameter defined using a single floating point value,
 *   e.g., width, radius, intensity, etc. The #keyValue field must contain
 *   exactly as many numbers as there are keyframes in the #key field.
 *   
 *   Refer to "Concepts - Interpolators" for a more detailed discussion of
 *   interpolators.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLScalarInterpolator {
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
 *       @TR   SoMFFloat   @TD   set_keyValue
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFFloat   @TD   value_changed      
 *       @TR   SoMFFloat   @TD   key_changed      
 *       @TR   SoMFFloat   @TD   keyValue_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLScalarInterpolator : public SoVRMLInterpolator {

  SO_INTERPOLATOR_HEADER(SoVRMLScalarInterpolator);

 public:
  // Fields
  SoMFFloat           key;
  SoMFFloat           keyValue;       

  // Events

  /**
   * Constructor.
   */
  SoVRMLScalarInterpolator();

 SoINTERNAL public:
  SoSFFloat               set_fraction;
  SoVRMLInterpOutput      value_changed;
  static void             initClass();
  static void             exitClass();

 protected:
  virtual ~SoVRMLScalarInterpolator();
  virtual void        evaluate(SoVRMLInterpOutput *interp);
  
 private:
  SbBool              needsEvaluation;        // Dirty bit

};

#endif /* _SO_VRMLSCALARINTERPOLATOR_ */

