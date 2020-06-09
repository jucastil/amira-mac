/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_CELLFACET_
#define  _PO_CELLFACET_

#include <MeshViz/3Ddata/PoCellShape.h>

/**
 * @DTEXT  Builds facets of a cell of a mesh.
 * 
 * @ingroup MeshRepresentation
 * 
 * @DESCRIPTION
 *    The cell is defined by its index in the current mesh (see PoCellShape).
 *    The current mesh is either the one defined by PoMesh::setMesh() or (if 
 *    this method is not called) the one defined in a special node inherited 
 *    during the traversal. This node has a type derived from PoMeshProperty.
 * @CATALOG_PARTS_INCLUDE pocellfacets.cat.html
 * 
 * 
 */
class MESHVIZ_API PoCellFacets : public PoCellShape {
  
  SO_KIT_HEADER(PoCellFacets) ;
  
  SO_KIT_CATALOG_ENTRY_HEADER(groupCellFacets) ;
  // Define fields for new parts


 public:

  /**
   * Constructor.
   */
  PoCellFacets() ;

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void   rebuild() ;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  void drawFacets(const PbCell *cell);

 protected:
  virtual ~PoCellFacets() ;  
  // Destructor

  // Methods
  virtual void setDefaultOnNonWritingFields();
  virtual void addElementsAllCaches() ;
  virtual void preRebuild();

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_CELLFACET_ */


