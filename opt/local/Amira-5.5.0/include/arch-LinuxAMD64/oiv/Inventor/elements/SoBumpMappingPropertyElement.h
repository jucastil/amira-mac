/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Oct 2002)
**=======================================================================*/

                                                             /* include files */
#ifndef  _SO_BUMP_MAPPING_PROPERTY_ELEMENT_
#define  _SO_BUMP_MAPPING_PROPERTY_ELEMENT_

#include <Inventor/elements/SoReplacedElement.h>
/**
* @VSGEXT Stores bump mapping properties.
*
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores bump mapping properties.
*   @SEE_ALSO
*   SoBumpMappingProperty
*/

SoEXTENDER_Documented class INVENTOR_API SoBumpMappingPropertyElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(SoBumpMappingPropertyElement) ;

 public:

   /** Normal map space */
  enum NormalMapSpace {
    /** Tangent space */
    TANGENT_SPACE,
    /** Model space */
    MODEL_SPACE
  } ;

  /** Texture format */
  enum TextureFormat {
    /** Height map */
    HEIGHT_MAP,
    /** Normal map */
    NORMAL_MAP
  } ;

  /**
  *  Sets the current attributes in the state.
  */
  static void set(SoState *state, 
                  SoNode *node, 
                  NormalMapSpace normalMapSpace,
                  SbBool isShadowed,
                  SbBool isEyeDistanceAttenuation,
                  SbBool isOnlyClosestLightUsed,
                  TextureFormat textureFormat) ;

  /**
  *  Gets the current attributes in the state.
  */
  static void get(SoState *state, 
                  NormalMapSpace &normalMapSpace,
                  SbBool &isShadowed,
                  SbBool &isEyeDistanceAttenuation,
                  SbBool &isOnlyClosestLightUsed,
                  TextureFormat &textureFormat) ;
  
  /**
  *  Returns default values.
  */
  static void getDefault(NormalMapSpace &normalMapSpace,
                         SbBool &isShadowed,
                         SbBool &isEyeDistanceAttenuation,
                         SbBool &isOnlyClosestLightUsed,
                         TextureFormat &textureFormat) ;

 SoINTERNAL public:
  // Initializes the SoBumpMappingPropertyElement class
  static void initClass() ;
  static void exitClass() ;

    // Initializes element
  virtual void init(SoState *state) ;

 protected:
  NormalMapSpace m_normalMapSpace ;
  SbBool         m_isShadowed ;
  SbBool         m_isEyeDistanceAttenuation ;
  SbBool         m_isOnlyClosestLightUsed ;
  TextureFormat  m_textureFormat ;

  virtual ~SoBumpMappingPropertyElement() ;
} ;

#endif /* _SO_BUMP_MAPPING_PROPERTY_ELEMENT_ */
