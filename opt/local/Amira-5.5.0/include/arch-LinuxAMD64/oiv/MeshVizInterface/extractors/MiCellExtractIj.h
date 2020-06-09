/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MICELLEXTRACTIJ_H
#define  _MICELLEXTRACTIJ_H

#include <MeshVizInterface/mesh/data/MiDataSetI.h>
#include <MeshVizInterface/mesh/data/MiDataSetIj.h>
#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>

#include <MeshVizInterface/mesh/MiSurfaceMeshRegular.h>
#include <MeshVizInterface/mesh/MiSurfaceMeshRectilinear.h>
#include <MeshVizInterface/mesh/MiSurfaceMeshCurvilinear.h>
#include <MeshVizInterface/extrmesh/MeXSurfaceMeshUnstructured.h>
#include <MeshVizInterface/tessellator/MiTessellator.h>

#include <Inventor/STL/vector>

class MiCellFilterIj;

/**
 * @DTEXT Cell extractor for structured surface meshes
 * 
 * @ingroup MeshIViz_Extract_Cell
 * 
 * @DESCRIPTION Extracts a list of cells from the input structured mesh and builds a surface mesh representing the extracted cells.
 * 
 * 
 * 
 */

class MESHIVIZ_API MiCellExtractIj : virtual public MiBaseExtractor
{
public:
    
  virtual ~MiCellExtractIj() {}

  //@{
  /**
  * @copydoc MiCellExtractIjk::getNewInstance()
  */ 
  static MiCellExtractIj* getNewInstance(const MiSurfaceMeshRegular& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  static MiCellExtractIj* getNewInstance(const MiSurfaceMeshRectilinear& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  static MiCellExtractIj* getNewInstance(const MiSurfaceMeshCurvilinear& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  //@}

  /**
  * A pair of indices used to define the cells to be extracted
  */ 
  class couple 
  {
  public:
    couple():i(0),j(0) {} /**< constructor */
    couple(size_t x, size_t y):i(x),j(y) {} /**< constructor */
    couple(size_t v):i(v),j(v) {} /**< constructor */
    size_t i; /**< I index*/
    size_t j; /**< J index */
    /** == operator */
    friend bool operator ==(const couple &t1, const couple &t2) 
    { return (t1.i==t2.i && t1.j==t2.j);}
    /** < operator */
    friend bool operator <(const couple &t1, const couple &t2) 
    { return (t1.i<t2.i || (t1.i==t2.i && t1.j<t2.j)); }
  };

  /**
  * Creates an unstructured surface mesh from the cells faces corresponding to the
  * given indices in the original volume mesh. Cells are scaled depending on the given
  * factor.@n 
  * Shrinking: factor < 1@n 
  * Expanding: factor > 1
  */
  virtual const MeXSurfaceMeshUnstructured&
  extractCell(const std::vector<couple>& cellIndexes, double factor, const MiCellFilterIj* cellFilter=NULL) = 0;

  /**
  * Creates an unstructured surface mesh from the faces of the cells corresponding to the
  * given indices in the original volume mesh. Cells are resized according to the given
  * factor.@n 
  * Shrinking: factor < 1@n 
  * Expanding: factor > 1
  */
  virtual const MeXSurfaceMeshUnstructured&
  extractCell(double factor, const MiCellFilterIj* cellFilter=NULL) = 0;
 
  /**
  * Extracts a scalar set from the surface mesh. The scalars are mapped onto the 
  * current extracted mesh. 
  *
  * @param inputSet The input scalar set defined on the surface mesh.
  * @return The output scalar set defined on the extracted mesh.
  */
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetIj& inputSet) = 0;

  /**
  * Extracts a vector set from the surface mesh. The vectors are mapped onto the 
  * current extracted mesh. 
  *
  * @param inputSet The input vector set defined on the surface mesh.
  * @return The output scalar set defined on the extracted mesh.
  */
  virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetIj& inputSet) = 0;

  /**
  * @copydoc MiCellExtractIjk::getExtract()
  */
  virtual const MeXSurfaceMeshUnstructured& getExtract() const = 0;

};

#endif /* _MICELLEXTRACTIJ_H */


