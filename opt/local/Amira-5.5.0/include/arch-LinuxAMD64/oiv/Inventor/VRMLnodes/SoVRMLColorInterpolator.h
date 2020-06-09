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


#ifndef  _SO_VRMLCOLORINTERPOLATOR_
#define  _SO_VRMLCOLORINTERPOLATOR_

#include <Inventor/fields/SoMFColor.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/VRMLnodes/SoVRMLInterpolator.h>
#include <Inventor/VRMLnodes/SoVRMLSubInterpolator.h>
//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLColorInterpolator
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Interpolates among a set of color values.
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
 *   This node interpolates among a set of SoMFColor key values, to produce an
 *   SoSFColor (RGB) @B value_changed @b event. The number of colors in the
 *   #keyValue field must be equal to the number of keyframes in the #key
 *   field. The #keyValue field and @B value_changed @b events are defined in
 *   RGB color space. A linear interpolation, using the value of @B set_fraction @b
 *   as input, is performed in HSV space.
 *   
 *   Refer to "Concepts - Interpolators" for a more detailed discussion of
 *   interpolators.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLColorInterpolator {
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
 *       @TR   SoMFColor   @TD   set_keyValue
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFColor   @TD   value_changed      
 *       @TR   SoMFFloat   @TD   key_changed      
 *       @TR   SoMFColor   @TD   keyValue_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLColorInterpolator : public SoVRMLInterpolator {

  SO_INTERPOLATOR_HEADER(SoVRMLColorInterpolator);

 public:
  // Fields
  SoMFFloat           key;
  SoMFColor           keyValue;       


  /**
   * Constructor.
   */
  SoVRMLColorInterpolator();

 SoINTERNAL public:
  SoSFFloat               set_fraction;
  SoVRMLInterpOutput      value_changed;
  static void             initClass();
  static void             exitClass();

 protected:
  // Events
  virtual ~SoVRMLColorInterpolator();
  virtual void        evaluate(SoVRMLInterpOutput *interp);

 private:
  static void         convertToRGB(float h, float s, float v, float *r,
                                   float *g, float *b);
  static void         convertToHSV(float r, float g, float b, float *h,
                                   float *s, float *v);

};

#endif /* _SO_VRMLCOLORINTERPOLATOR_ */

