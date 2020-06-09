/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
** Modified by : M. Bonaventure (Mar 2010)
**=======================================================================*/
/*==============================================================================
 *   File        : MoMeshElement.h
 *   Classes     : MoMeshElement
 *   Author(s)   : Pascal Doux
 *   Date        : 16 2 2009
 *==============================================================================
 *
 * Description : Element that stores a Tessellator.
 *
 *============================================================================*/

#ifndef  _MoTessellatorElement_
#define  _MoTessellatorElement_

#include <Inventor/elements/SoReplacedElement.h>
#include <MeshVizInterface/mapping/MoMeshVizDataMapping.h>

class MiTessellator;

/**
* @DTEXT Stores the current tessellator.
* 
* @ingroup MeshIViz_Mapping_Elements
*
* @DESCRIPTION
*   This element stores a tesselator in the traversal state list.
* @SEE_ALSO
*   MoTesselator
*/
class MESHIVIZDM_API MoTessellatorElement : public SoReplacedElement 
{

  SO_ELEMENT_HEADER(MoTessellatorElement);

public:

  /** Sets the current tessellator */
  static void set(SoState *state, SoNode *node, MiTessellator *tess , size_t nodeTimeStamp);

  /** Returns the current tessellator from the state */
  static MiTessellator *getTessellator(SoState *state, size_t& eltTimeStamp);

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

  /**
  *  Return the timestamp of the associated node
  */
  size_t getTimeStamp() const;

protected:
  MiTessellator *m_tessellator;
  size_t         m_tessTimeStamp;
  size_t         m_nodeTimeStamp;
  
  virtual ~MoTessellatorElement();
  
};
/*----------------------------------------------------------------------------*/

#endif // _MoTessellatorElement_
