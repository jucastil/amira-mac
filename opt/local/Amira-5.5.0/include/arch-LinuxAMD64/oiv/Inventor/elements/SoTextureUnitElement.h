/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (May 2002)
**=======================================================================*/

#ifndef  _SO_TEXTURE_UNIT_ELEMENT_
#define  _SO_TEXTURE_UNIT_ELEMENT_

#include <Inventor/SbPList.h>
#include <Inventor/elements/SoAccumulatedElement.h>

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

/**
*   @VSGEXT Stores the current texture unit identifier.
*
*   @ingroup elements
*
*   @DESCRIPTION
*   This element stores the the current texture unit identifier.
*
*   @SEE_ALSO
*   SoTextureUnit
*/

SoEXTENDER_Documented class INVENTOR_API SoTextureUnitElement : public SoAccumulatedElement {
  SO_ELEMENT_HEADER(SoTextureUnitElement) ;

 public:
    /** MappingMethod */
  enum MappingMethod {
    /** BUMP_MAPPING */
    BUMP_MAPPING,
    /** IMAGE_MAPPING */
    IMAGE_MAPPING
  } ;

  /**
  *  Sets the current texture unit and mapping method.
  */
  static void set(SoState *state, SoNode *node, int unit, MappingMethod mappingMethod) ;

  /**
  *  Activates the current texture if it exists. Returned value indicates if it is successful.
  */
  static SbBool activateTextureUnit(SoState *state, int unit) ;

  /**
  *  Overrides push() method to copy values from next instance in the stack.
  */
  virtual void push(SoState *state) ;

  /**
  *  Pop method.
  */
  virtual void pop(SoState *, const SoElement *prevTopElement) ;

  /**
  *  Returns the current list texture units.
  */
  static const SbIntList& getTextureUnits(SoState *state) ;

  /**
  *  Returns the mapping method associated with each texture unit.
  * [OIV-WRAPPER-RETURN-TYPE ARRAY{GetMaxTextureUnit()}]
  */
  static const MappingMethod* getMappingMethods(SoState *state) ;

  /**
  *  Returns the current active texture unit (the last texture unit set).
  */
  static int getActiveTextureUnit(SoState *state) ;

  /**
  *  Returns the current active mapping method according to
  *  the current texture unit.
  */
  static MappingMethod getActiveMappingMethod(SoState *state) ;

  /**
  *  Returns the maximum texture units.
  */
  static int getMaxTextureUnit(SoState* state=NULL) ;

  /**
  *  Returns TRUE if the multi-texturing is active: i.e., at least 2 texture units are defined
  *  with a mapping method equal to IMAGE_MAPPING.
  *  Returns also the list of units where the mapping method is equal to IMAGE_MAPPING.
  */
  static SbBool isMultiTexturing(SoState *state, SbIntList &imageTexUnitList) ;

  /**
  *  Indicate according to the current mapping method if GL data must be sent or
  *  not.
  */
  static SbBool shouldSendGLData(SoState *state) ;

  /**
  *  Indicate if one unit among the current unit list corresponds to an IMAGE_MAPPING.
  *  The first corresponding unit found is returned, -1 otherwise.
  */
  static int isImageMapping(SoState *state) ;

  /**
  *  Indicate if one unit among the current unit list corresponds to an BUMP_MAPPING.
  *  The first corresponding unit found is returned, -1 otherwise.
  */
  static int isBumpMapping(SoState *state) ;

 SoINTERNAL public:
  // Initializes element.
  virtual void init(SoState *state);

  // Common Initialization. Directly called by the constructor.
  virtual void commonInit() ;

  // Initializes the SoTextureUnitElement class
  static void initClass() ;
  static void exitClass() ;

  /**
   *  Returns the maximum texture units for the fixed pipeline .
   */
  static uint32_t getFixedPipelineMaxTextureUnit(SoState* state) ;

  /**
   * Returns TRUE if multi-texturing is supported on the current context
   * Note: can be force disabled with OIV_MULTITEXTURING envvar
   */
  static SbBool isMultitexturingAvailable(SoState* state);

 protected:
  // Sets the element
  virtual void setElt(SoState* state, SoNode *node, const int unit, MappingMethod mappingMethod) ;
  virtual void setUnit(SoState*, const int ) {}

  int       m_startIndex ;
  int       m_textureUnit ;

  // List of texture units
  SbIntList m_textureUnits ;

  // Mapping method associated to each texture unit.

  virtual ~SoTextureUnitElement() ;

  MappingMethod& getMapping(const size_t unit) const;

private:
  // List of mapping methods per texture unit
  mutable std::vector<MappingMethod> m_mappingMethods ;

  // used to indicate that multitexturing has been disable through OIV_MULTITEXTURING envvar
  static SbBool s_multiTexturingAllowed;
  static int s_multitexturing_extensionID;
} ;
/*----------------------------------------------------------------------------*/

#ifdef WIN32
#pragma warning( pop )
#endif

#endif // _SO_TEXTURE_UNIT_ELEMENT_
