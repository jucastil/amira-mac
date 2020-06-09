/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Olivier Fedkiw (MMM yyyy)
**=======================================================================*/

#ifndef _SO_STEREO_ELEMENT
#define _SO_STEREO_ELEMENT

#include <Inventor/nodes/SoCamera.h>
#include <Inventor/elements/SoSubElement.h>

/**
*  @VSGEXT Stores the current stereo attributes.
* 
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the current stereo attributes.
* 
*   @SEE_ALSO
*/

SoEXTENDER_Documented class INVENTOR_API SoStereoElement : public SoElement {
  
  SO_ELEMENT_HEADER(SoStereoElement);
  
 public:  
  /**
   * Indicates if the stereo offset and and balance setting should be
   * interpreted as factors or as absolute parameters.
   * If TRUE, the stereo adjustments are absolute.
   */
  static void setStereoAbsoluteAdjustments(SoState * state, SbBool absolute);
  /**
   * Returns TRUE if stereo adjustments are absolute. See #setStereoAbsoluteAdjustments().
   */
  static bool isStereoAbsoluteAdjustments(SoState * state);

  /**
   *  Sets the stereo offset adjustment.
   */
  static void setStereoAdjustment(SoState * state, float stoffset);
 
  /** 
   *  Sets the stereo balance adjustment. When @B stNearFrac @b is set to TRUE,
   *  @B stbalance @b value is considered to be a fraction of the camera near distance.
   */
  static void setBalanceAdjustment(SoState * state, float stbalance, SbBool stNearFrac = false);

  /**
   *  Sets the inter-eye distance (immersive MP only).
   */
  static void setInterEyeDistance(SoState * state, float ied);
    
  /**
   *  Sets the stereo inverted view flag.
   */
  static void setReversedView(SoState * state, bool strev);

  /**
   *  Returns the stereo offset adjustment.
   */
  static float getStereoAdjustment(SoState *state); 
  
  /**
   *  Returns the stereo balance adjustment.
   */
  static float getBalanceAdjustment(SoState *state);

  /** 
   * Returns TRUE when the stereo balance adjustement is defined as a fraction
   * of the camera near distance.  See setBalanceAdjustment.
   */
  static SbBool isBalanceAdjustmentNearFrac(SoState *state);

  /**
   *  Returns the inter-eye distance (immersive MP only).
   */
  static float getInterEyeDistance(SoState *state);
  
  /**
   *  Returns the inverted view flag.
   */
  static bool getReversedView(SoState *state);
  
  /**
   *  Sets the stereo mode, LEFT_VIEW, RIGHT_VIEW, or MONOSCOPIC.
   */
  static void set(SoState *state, const SoCamera::StereoMode mode);
  
  // Returns the boolean that tells the camera to narrow or not the view volume
  //static const SbBool getNarrow(SoState *state);
  
  /**
   *  Returns the stereoMode.
   */
  static SoCamera::StereoMode getStereoMode(SoState *state);
  
  /**
   *  Return the top (current) instance of the element in the state.
   *  Note it does NOT cause cache dependency!
   *  It also casts away the const.
   */
  static SoStereoElement *getInstance(const SoState *state, SbBool &elemIsSet);
  
  /**
   *  Returns TRUE if the passes match in both elements.
   */
  virtual SbBool matches(const SoElement *elt) const;
  
  /**
   *  Create and return a copy of this element.
   */
  virtual SoElement *copyMatchInfo() const;
  
 SoINTERNAL public:
   // Initializes the SoStereoElement class
  static void initClass();
  static void exitClass();
  
  // Initializes element
  virtual void init(SoState *state);
  
protected:
  
  /*  SbBool narrowViewVolume;*/
  SoCamera::StereoMode stereoMode;
  SbBool stereoAbsoluteAdjustments;
  float  stereoOffset;
  bool  stereoNearFrac;
  float  stereoBalance;
  float  interEyeDistance;
  bool   reversed;

  SbBool isSet;
  
  virtual ~SoStereoElement();

private:
  uint64_t nodeId;

};
#endif /* _SO_STEREO_ELEMENT */
