/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MeXDataSetI_H
#define _MeXDataSetI_H

#include <MeshVizInterface/mesh/data/MiDataSetI.h>
#include <MeshVizInterface/extrmesh/data/MeXBoundedDataSet.h>

/**
* @DTEXT Generic data set interface for extracted unstructured meshes.
* 
* @ingroup MeshIViz_ExtractedMesh_DataSets
* 
* @DESCRIPTION
*    A generic abstract template interface for data sets returned by any extract of unstructured mesh.
* 
*/
template <typename _T>
class MeXDataSetI : virtual public MiDataSetI<_T>, virtual public MeXBoundedDataSet<_T>
{
public:
  /**
  * Returns the number of elements in the data set.
  */
  virtual size_t getSize() const = 0;

};

/**
* @ingroup MeshIViz_ExtractedMesh_DataSets
* Specialization for extracted unstructured scalar sets containing double
*/
typedef MeXDataSetI<double>  MeXScalardSetI;
/**
* @ingroup MeshIViz_Mesh_DataSets
* Specialization for extracted unstructured vector sets containing MbVec3d
*/
typedef MeXDataSetI<MbVec3d> MeXVec3dSetI;

#endif
