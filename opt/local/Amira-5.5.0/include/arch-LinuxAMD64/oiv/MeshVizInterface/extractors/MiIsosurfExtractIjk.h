/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MIISOSURFEXTRACTREGULAR_H
#define  _MIISOSURFEXTRACTREGULAR_H

#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>
#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/extrmesh/MeXSurfaceMeshUnstructured.h>

class MiCellFilterIjk;
class MiVolumeMeshRegular;
class MiVolumeMeshCurvilinear;
class MiVolumeMeshRectilinear;
class MiTessellator;

/**
* @DTEXT Isosurface extractor for structured volume meshes
* 
* @ingroup MeshIViz_Extract_Isosurf
* 
* @DESCRIPTION Builds the isosurface of the given isovalue in the given dataset.
* 
* 
*/
class MESHIVIZ_API MiIsosurfExtractIjk : virtual public MiBaseExtractor
{
public:
  virtual ~MiIsosurfExtractIjk() {}

  //@{
  /**
  * @copydoc MiCellExtractIjk::getNewInstance()
  */ 
  static MiIsosurfExtractIjk* getNewInstance(const MiVolumeMeshRegular& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  static MiIsosurfExtractIjk* getNewInstance(const MiVolumeMeshCurvilinear& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  static MiIsosurfExtractIjk* getNewInstance(const MiVolumeMeshRectilinear& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  //@}

  /**
  * Builds the isosurface of the given isovalue in the given dataset. 
  * @note In case of dataset bound PER_CELL, it will be converted into 
  * a new internal dataset bound PER_NODE and cached in the extractor.
  * @param isovalue Value for which an isosurface must be computed
  * @param dataSet The input data set used to compute the isovalue from
  * @param cellFilter The cell filter
  * @return The extracted isosurface
  */
  virtual const MeXSurfaceMeshUnstructured& extractIsovalue(double isovalue, const MiScalardSetIjk& dataSet, const MiCellFilterIjk* cellFilter=NULL) = 0;

  /**
  * Computes a scalar set on the extracted isosurface.
  * @param inputSet the input scalar set defined on the volume mesh
  * @return the output scalar set defined on the resulting isosurface mesh
  */
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetIjk& inputSet) = 0;

  /**
  * Computes a vector set on the extracted isosurface.
  * @param inputSet the input vec3 set defined on the volume mesh
  * @return the output scalar set defined on the resulting isosurface mesh
  */
  virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetIjk& inputSet) = 0;

  /**
  * @copydoc MiCellExtractIjk::getExtract()
  */
  virtual const MeXSurfaceMeshUnstructured& getExtract() const = 0;


} ;


#endif 


