/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MIDATASETIJ_H
#define _MIDATASETIJ_H

#include <MeshVizInterface/MxMeshIViz.h>
#include <MeshVizInterface/mesh/data/MiBoundedDataSet.h>
#include <MeshVizInterface/MbVec3.h>

//-----------------------------------------------------------------------------
/**
* @DTEXT Generic data set interface for structured surface meshes.
* 
* @ingroup MeshIViz_Mesh_DataSets
* 
* @DESCRIPTION
*    A generic abstract template interface for a data set usable in any extract of a structured surface mesh.
* 
*/
template <typename _T>
class MiDataSetIj : virtual public MiBoundedDataSet<_T>
{
public:
  /**
  * Returns the ij-th value of this set.
  */
  virtual _T get(size_t i, size_t j) const = 0;
};

/**
* @ingroup MeshIViz_Mesh_DataSets
* Specialization for structured scalar sets containing double
*/
typedef MiDataSetIj<double>  MiScalardSetIj;
/**
* @ingroup MeshIViz_Mesh_DataSets
* Specialization for structured vector sets containing MbVec3d
*/
typedef MiDataSetIj<MbVec3d> MiVec3dSetIj;

#endif

