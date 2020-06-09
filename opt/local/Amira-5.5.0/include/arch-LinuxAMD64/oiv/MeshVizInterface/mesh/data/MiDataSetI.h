/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MIDATASETI_H
#define _MIDATASETI_H

#include <MeshVizInterface/MxMeshIViz.h>
#include <MeshVizInterface/mesh/data/MiBoundedDataSet.h>
#include <MeshVizInterface/MbVec3.h>

/**
* @DTEXT Generic data set interface for unstructured meshes.
* 
* @ingroup MeshIViz_Mesh_DataSets
* 
* @DESCRIPTION
*    A generic abstract template interface for a data set usable in any extract of an unstructured mesh.
* 
*/
template <typename _T>
class MiDataSetI : virtual public MiBoundedDataSet<_T>
{
public:

  /**
  * Returns the i-th value of this set.
  */
  virtual _T get(size_t i) const = 0;

};

/**
* @ingroup MeshIViz_Mesh_DataSets
* Specialization for unstructured scalar sets containing double
*/
typedef MiDataSetI<double>  MiScalardSetI;
/**
* @ingroup MeshIViz_Mesh_DataSets
* Specialization for unstructured vector sets containing MbVec3d
*/
typedef MiDataSetI<MbVec3d> MiVec3dSetI;

#endif
