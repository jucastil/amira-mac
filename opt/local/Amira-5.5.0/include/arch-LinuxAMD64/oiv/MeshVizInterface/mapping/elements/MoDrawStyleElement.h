/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
** Modified by : M. Bonaventure (Mar 2010)
**=======================================================================*/
/*==============================================================================
 *   File        : MoDrawStyleElement.h
 *   Classes     : MoDrawStyleElement
 *   Author(s)   : Pascal Doux
 *   Date        : 8 9 2008
 *==============================================================================
 *
 * Description : Element that stores a data binding.
 *
 *============================================================================*/

#ifndef  _MO_DRAWSTYLE_ELEMENT_
#define  _MO_DRAWSTYLE_ELEMENT_

#include <Inventor/elements/SoReplacedElement.h>
#include <MeshVizInterface/mapping/MoMeshVizDataMapping.h>
#include <MeshVizInterface/mapping/nodes/MoDrawStyle.h>

class MoDataBinding;

/**
* @DTEXT Stores the current draw style.
* 
* @ingroup MeshIViz_Mapping_Elements
*
* @DESCRIPTION
*   This element stores the current draw style.
* @SEE_ALSO
*   MoDrawStyle
*/
class MESHIVIZDM_API MoDrawStyleElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(MoDrawStyleElement);
  
 public:
  
  /** Sets the current draw style */
  static void set(SoState *state, SoNode *node, bool displaySolid, bool displayEdges, bool displayPoints);
  
  /** Returns the current DrawStyle from the state */
  static bool getDrawStyle(SoState *state, bool& displaySolid, bool& displayEdges, bool& displayPoints);

  /** Returns the default Drawstyle from the state */
  static bool getDefault(bool& displaySolid, bool& displayEdges, bool& displayPoints);

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
  bool m_displaySolid;
  bool m_displayEdges;
  bool m_displayPoints;
  bool m_isSet;
  
  virtual ~MoDrawStyleElement();
  
};
/*----------------------------------------------------------------------------*/

#endif // _MO_DRAWSTYLE_ELEMENT_
