/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MIDATASETIJK_H
#define _MIDATASETIJK_H

#include <MeshVizInterface/MxMeshIViz.h>
#include <MeshVizInterface/mesh/data/MiBoundedDataSet.h>
#include <MeshVizInterface/MbVec3.h>

/**
* @DTEXT Generic data set interface for structured volume meshes.
* 
* @ingroup MeshIViz_Mesh_DataSets
* 
* @DESCRIPTION
*    A generic abstract template interface for a data set usable in any extract of a structured volume mesh.
* 
*/
template <typename _T>
class MiDataSetIjk : virtual public MiBoundedDataSet<_T>
{
public:

  /**
  * Returns the ijk-th value of this set.
  */
  virtual _T get(size_t i, size_t j, size_t k) const = 0;

};

/**
* @ingroup MeshIViz_Mesh_DataSets
* Specialization for structured scalar sets containing double
*/
typedef MiDataSetIjk<double>  MiScalardSetIjk;
/**
* @ingroup MeshIViz_Mesh_DataSets
* Specialization for structured vector sets containing MbVec3d
*/
typedef MiDataSetIjk<MbVec3d> MiVec3dSetIjk;

#endif
