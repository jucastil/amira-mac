/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
** Modified by : M. Bonaventure (Mar 2010)
**=======================================================================*/
/*==============================================================================
 *   File        : MoMaterialElement.h
 *   Classes     : MoMaterialElement
 *   Author(s)   : Pascal Doux
 *   Date        : 18 11 2008
 *==============================================================================
 *
 * Description : Element that stores a mesh material.
 *
 *============================================================================*/

#ifndef  _MO_MATERIAL_ELEMENT_
#define  _MO_MATERIAL_ELEMENT_

#include <Inventor/elements/SoReplacedElement.h>
#include <MeshVizInterface/mapping/MoMeshVizDataMapping.h>
#include <MeshVizInterface/mapping/nodes/MoMaterial.h>

class MoDataBinding;

/**
* @DTEXT Stores the current material.
* 
* @ingroup MeshIViz_Mapping_Elements
*
* @DESCRIPTION
*   This element stores the current colors and coloring options.
* @SEE_ALSO
*   MoMaterial
*/
class MESHIVIZDM_API MoMaterialElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(MoMaterialElement);

public:

  /** Sets the current material */
  static void set(SoState *state, SoNode *node, MoMaterial::ColoringType coloring,const SbColor& color,
    MoMaterial::ColoringType lineColoring,const SbColor& lineColor, 
    MoMaterial::ColoringType markerColoring, const SbColor& markerColor, 
    float transparency, bool enhancedColoring);

  /** Returns the current Material from the state */
  static bool getMaterial(SoState *state, MoMaterial::ColoringType& coloring, SbColor& color, 
    MoMaterial::ColoringType& lineColoring, SbColor& lineColor, 
    MoMaterial::ColoringType& markerColoring, SbColor& markerColor, 
    float& transparency, bool& enhancedColoring);

  /** Returns the default Material from the state */
  static bool getDefault(MoMaterial::ColoringType& coloring, SbColor& color, 
    MoMaterial::ColoringType& lineColoring, SbColor& lineColor, 
    MoMaterial::ColoringType& markerColoring, SbColor& markerColor, 
    float& transparency, bool& enhancedColoring);

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
   MoMaterial::ColoringType   m_coloring;
   SbColor                    m_color;
   MoMaterial::ColoringType   m_lineColoring;
   SbColor                    m_lineColor;
   MoMaterial::ColoringType   m_markerColoring;
   SbColor                    m_markerColor;
   float                      m_transparency;
   bool                       m_enhancedColoring;
   bool                       m_isSet;

  virtual ~MoMaterialElement();
  
};
/*----------------------------------------------------------------------------*/

#endif // _MO_MATERIAL_ELEMENT_
