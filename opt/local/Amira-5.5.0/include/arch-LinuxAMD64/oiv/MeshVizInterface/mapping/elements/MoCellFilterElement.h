/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
** Modified by : M. Bonaventure (Mar 2010)
**=======================================================================*/
/*==============================================================================
 *   File        : MoCellFilterElement.h
 *   Classes     : MoCellFilterElement
 *   Author(s)   : Pascal Doux
 *   Date        : 6 6 2008
 *==============================================================================
 *
 * Description : Element that stores a cell filter.
 *
 *============================================================================*/

#ifndef  _MO_CELLFILTER_ELEMENT_
#define  _MO_CELLFILTER_ELEMENT_

#include <Inventor/elements/SoReplacedElement.h>
#include <MeshVizInterface/mapping/MoMeshVizDataMapping.h>

class MiCellFilter;

/**
* @DTEXT Stores the current cell filter.
* 
* @ingroup MeshIViz_Mapping_Elements
*
* @DESCRIPTION
*   This element stores the current cell filter.
* @SEE_ALSO
*   MoCellFilter
*/

class MESHIVIZDM_API MoCellFilterElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(MoCellFilterElement);
  
 public:
  /** Sets the current cell filter */
  static void set(SoState *state, SoNode *node, CellFilterType cellFilterType, const MiCellFilter *cellFilter);
  
  /** Returns the current cellfilter from the state */
  static const MiCellFilter *getCellFilter(SoState *state, CellFilterType &cellFilterType);

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
  static void exitClass();

  /** Initializes element */
  virtual void init(SoState *state);

  /**
  *  Create and return a copy of this element.
  */
  virtual SoElement *copyMatchInfo() const;
  
 protected:
  const MiCellFilter *m_cellFilter;
  size_t              m_cellFilterTimeStamp;
  CellFilterType      m_cellFilterType;
  
  virtual ~MoCellFilterElement();
  
};
/*----------------------------------------------------------------------------*/

#endif // _MO_CELLFILTER_ELEMENT_
