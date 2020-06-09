/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Feb 1997)
**=======================================================================*/

#ifndef  _SO_ENVIRONMENT_ELEMENT_
#define  _SO_ENVIRONMENT_ELEMENT_
/* include files */
#include <Inventor/elements/SoReplacedElement.h>
#include <Inventor/SbColor.h>

/*----------------------------------------------------------------------------*/
/**
* @VSGEXT Stores the current environment.
*
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the current environment.
*   @SEE_ALSO
*   SoEnvironment
*/

SoEXTENDER_Documented class INVENTOR_API SoEnvironmentElement : public SoReplacedElement {
  SO_ELEMENT_HEADER(SoEnvironmentElement) ;

 public:

   /** Fog type */
  enum FogType {
    /** None */
    NONE,
    /** Haze */
    HAZE,
    /** Fog */
    FOG,
    /** Smoke */
    SMOKE
  } ;

   /**
   *  Sets the current environment in the state.
   */
  static void set(SoState *state, SoNode *node,
                  float ambientIntensity, const SbColor &ambientColor,
                  const SbVec3f attenuation, FogType fogType, const
                  SbColor fogColor, float fogVisibility) ;
   /**
   *  Gets the current environment in the state.
   */
  static void get(SoState *state, float &ambientIntensity, 
                  SbColor &ambientColor, SbVec3f &attenuation, 
                  FogType &fogType, SbColor &fogColor, float &fogVisibility) ;

  /**
  *  Gets the ambient intensity.
  */
  static float          getAmbientIntensity(SoState *state) ;
  /**
  *  Gets the ambient color.
  */
  static const SbColor& getAmbientColor(SoState *state) ;
  /**
  *  Gets the light attenuation.
  */
  static const SbVec3f& getLightAttenuation(SoState *state) ;

  /**
  *  Returns the default value.
  */
  static void getDefault(float &ambientIntensity, SbColor &ambientColor,
                         SbVec3f &attenuation, FogType &fogType,
                         SbColor &fogColor, float &fogVisibility) ;
  
  // Push copies the values from the previous element
  virtual void  push(SoState *state) ;

  // Returns TRUE if the attributes of environment  match in both elements
  virtual SbBool matches(const SoElement *elt) const ;

 SoINTERNAL public:
  
  // Initializes the SoEnvironmentElement class
  static void initClass() ;
  static void exitClass() ;
  
  // Initializes element.
  virtual void init(SoState *state);

protected:
  float     m_ambientIntensity ;
  SbColor   m_ambientColor ;
  SbVec3f   m_attenuation ;
  FogType   m_fogType ;
  SbColor   m_fogColor ;
  float     m_fogVisibility ;

  virtual void setElt( float ambientIntensity, const SbColor &ambientColor,
                  const SbVec3f attenuation, FogType fogType, const
                  SbColor fogColor, float fogVisibility) ;

  virtual ~SoEnvironmentElement() ;

} ;

/*----------------------------------------------------------------------------*/

#endif // _SO_ENVIRONMENT_ELEMENT_
