/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
** Modified by : M. Bonaventure (Mar 2010)
**=======================================================================*/
/*==============================================================================
 *   File        : MoColorMappingElement.h
 *   Classes     : MoColorMappingElement
 *   Author(s)   : Pascal Doux
 *   Date        : 6 6 2008
 *==============================================================================
 *
 * Description : Element that stores a color mapping interface.
 *
 *============================================================================*/

#ifndef  _MO_COLORMAPPING_ELEMENT_
#define  _MO_COLORMAPPING_ELEMENT_

#include <Inventor/elements/SoReplacedElement.h>
#include <Inventor/SbColorRGBA.h>
#include <MeshVizInterface/mapping/interfaces/MiColorMapping.h>

/**
* @DTEXT Stores the current color mapping.
* 
* @ingroup MeshIViz_Mapping_Elements
*
* @DESCRIPTION
*   This element stores the current color mapping.
*
* @SEE_ALSO
*   MoCustomColorMapping, MoLevelColorMapping, MoLinearColorMapping, MoPredefinedColorMapping
*
*/
class MESHIVIZDM_API MoColorMappingElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(MoColorMappingElement);
  
 public:

  /** Sets the current color mapping */
  static void set(SoState *state, SoNode *node, const MiColorMapping<double,SbColorRGBA> *colorMapping);
  
  /** Returns the current color mapping from the state */
  static const MiColorMapping<double,SbColorRGBA> *getColorMapping(SoState *state);

  /**
  *  Returns TRUE if the geoOrigins match in both elements.
  */
  virtual SbBool matches(const SoElement *elt) const;

  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;
  
 SoINTERNAL public:
  // Initializes the class
  static void initClass();
  static void exitClass() ;

  /** Initializes element */
  virtual void init(SoState *state);

  /**
  *  Create and return a copy of this element.
  */
  virtual SoElement *copyMatchInfo() const;
  
 protected:
  
  virtual ~MoColorMappingElement();

  const MiColorMapping<double,SbColorRGBA>* m_colorMapping;
  size_t m_colorMapTimeStamp;
};
/*----------------------------------------------------------------------------*/

#endif // _MO_COLORMAPPING_ELEMENT_
