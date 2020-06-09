/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MICELLEXTRACTIJK_H
#define  _MICELLEXTRACTIJK_H

#include <MeshVizInterface/mesh/data/MiDataSetI.h>
#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>
#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>

#include <MeshVizInterface/mesh/MiVolumeMeshRegular.h>
#include <MeshVizInterface/mesh/MiVolumeMeshRectilinear.h>
#include <MeshVizInterface/mesh/MiVolumeMeshCurvilinear.h>
#include <MeshVizInterface/extrmesh/MeXSurfaceMeshUnstructured.h>
#include <MeshVizInterface/tessellator/MiTessellator.h>

#include <Inventor/STL/vector>

class MiCellFilterIjk;

/**
 * @DTEXT Cell extractor for structured volume meshes
 * 
 * @ingroup MeshIViz_Extract_Cell
 * 
 * @DESCRIPTION Extracts a list of cells from the input structured mesh and builds a surface mesh representing the extracted cells.
 * 
 * 
 * 
 */

class MESHIVIZ_API MiCellExtractIjk : virtual public MiBaseExtractor
{
public:
    
  virtual ~MiCellExtractIjk() {}

  //@{
  /**
  * Factory method returning a new instance of a class implementing this interface.
  * @param mesh The input mesh 
  * @param parallel When true, tries to create an extract module using a parallel algorithm to speed up the extraction. 
  * @param tessellator The tessellator object used for tessellating non linear cells (quadratic,...). 
  * @note Only some of the extraction algorithms have a parallel implementation.
  */ 
  static MiCellExtractIjk* getNewInstance(const MiVolumeMeshRegular& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  static MiCellExtractIjk* getNewInstance(const MiVolumeMeshRectilinear& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  static MiCellExtractIjk* getNewInstance(const MiVolumeMeshCurvilinear& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  //@}

  /**
  * A triplet of indices used to define the cells to be extracted
  */ 
  class triplet 
  {
  public:
    triplet():i(0),j(0),k(0) {} /**< constructor */
    triplet(size_t x, size_t y, size_t z):i(x),j(y),k(z) {} /**< constructor */
    triplet(size_t v):i(v),j(v),k(v) {} /**< constructor */
    size_t i; /**< I index*/
    size_t j; /**< J index */
    size_t k; /**< K index */
    /** == operator */
    friend bool operator ==(const triplet &t1, const triplet &t2) 
    { return (t1.i==t2.i && t1.j==t2.j && t1.k==t2.k);}
    /** < operator */
    friend bool operator <(const triplet &t1, const triplet &t2) 
    { return (t1.i<t2.i || (t1.i==t2.i && (t1.j<t2.j || (t1.j==t2.j && t1.k<t2.k)))); }
  };

  /**
  * Creates an unstructured surface mesh from the faces of the cells corresponding to the
  * given indices in the original volume mesh. Cells are scaled according to the given
  * factor.@n 
  * Shrinking: factor < 1@n 
  * Expanding: factor > 1
  */
  virtual const MeXSurfaceMeshUnstructured&
  extractCell(const std::vector<triplet>& cellIndexes, double factor, const MiCellFilterIjk* cellFilter=NULL) = 0;

  /**
  * Creates an unstructured surface mesh from the faces of all the cells in the
  * original volume mesh. Cells are scaled according to the given
  * factor.@n 
  * Shrinking: factor < 1@n 
  * Expanding: factor > 1
  */
  virtual const MeXSurfaceMeshUnstructured&
  extractCell(double factor, const MiCellFilterIjk* cellFilter=NULL) = 0;
 
  /**
  * Extracts a scalar set from the original mesh. The scalars are mapped onto the 
  * current extracted mesh. 
  *
  * @param inputSet The input scalar set defined on the original mesh.
  * @return The output scalar set defined on the extracted mesh.
  */
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetIjk& inputSet) = 0;

  /**
  * Extracts a vector set from the original mesh. The vectors are mapped onto the 
  * current extracted mesh. 
  *
  * @param inputSet The input vector set defined on the original mesh.
  * @return The output vector set defined on the extracted mesh.
  */
  virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetIjk& inputSet) = 0;

  /**
  * Returns the result of the extraction as a mesh.
  */
  virtual const MeXSurfaceMeshUnstructured& getExtract() const = 0;

};

#endif /* _MICELLEXTRACT_H */


