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


#ifndef  _SO_VRMLCOORDINATEINTERPOLATOR2D_
#define  _SO_VRMLCOORDINATEINTERPOLATOR2D_

#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/VRMLnodes/SoVRMLInterpolator.h>
#include <Inventor/VRMLnodes/SoVRMLSubInterpolator.h>
//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLCoordinateInterpolator2D
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Interpolates among a set of 2D coordinate values.
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
 *   This node linearly interpolates among a set of MFVec2f values to produce an MFVec2f
 *   value_changed event. 
 *   
 *   The number of coordinates in the #keyValue field must be an integer
 *   multiple of the number of keyframes in the #key field; that integer
 *   multiple defines how many coordinates will be contained in the
 *   @B value_changed @b events. 
 *   
 *   Refer to "Concepts - Interpolators" for a more detailed discussion of
 *   interpolators.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLCoordinateInterpolator {
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
 *       @TR   SoMFVec2f   @TD   set_keyValue
 *       @TR   SoSFNode    @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoMFVec2f   @TD   value_changed      
 *       @TR   SoMFFloat   @TD   key_changed      
 *       @TR   SoMFVec2f   @TD   keyValue_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLCoordinateInterpolator2D : public SoVRMLInterpolator {

  SO_INTERPOLATOR_HEADER(SoVRMLCoordinateInterpolator2D);

 public:
  /**
   * Key array.
   */
  SoMFFloat           key;
  /**
   * KeyValue array.
   */
  SoMFVec2f            keyValue;       
  /**
   * Constructor.
   */
  SoVRMLCoordinateInterpolator2D();

 SoINTERNAL public:
  SoSFFloat               set_fraction;
  SoVRMLInterpOutput      value_changed;
  static void             initClass();
  static void             exitClass();


  // Propagates modification notification through an instance.
  virtual void        notify(SoNotList *list);

 protected:

  virtual ~SoVRMLCoordinateInterpolator2D();

  virtual void        evaluate(SoVRMLInterpOutput *interp);

 private:
  SbBool              needsEvaluation;        // Dirty bit
  SbVec2f             *p3;
  int                 m_numMult;

};

#endif /* _SO_VRMLCOORDINATEINTERPOLATOR_ */

