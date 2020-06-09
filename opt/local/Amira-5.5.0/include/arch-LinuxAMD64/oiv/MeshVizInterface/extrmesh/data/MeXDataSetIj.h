/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MeXDataSetIj_H
#define _MeXDataSetIj_H

#include <MeshVizInterface/mesh/data/MiDataSetIj.h>
#include <MeshVizInterface/extrmesh/data/MeXBoundedDataSet.h>

//-----------------------------------------------------------------------------
/**
* @DTEXT Generic data set interface for extracted structured surface meshes.
* 
* @ingroup MeshIViz_ExtractedMesh_DataSets
* 
* @DESCRIPTION
*    A generic abstract template interface for a data set returned by any extract of a structured surface mesh.
* 
*/
template <typename _T>
class MeXDataSetIj : virtual public MiDataSetIj<_T>, virtual public MeXBoundedDataSet<_T>
{
public:
  /**
  * Returns the size of the dataset along the first logical axis.
  */
  virtual size_t getSizeI() const = 0;
  /**
  * Returns the size of the dataset along the second logical axis.
  */
  virtual size_t getSizeJ() const = 0;

};

/**
* @ingroup MeshIViz_ExtractedMesh_DataSets
* Specialization for extracted structured scalar sets containing double
*/
typedef MeXDataSetIj<double>  MeXScalardSetIj;
/**
* @ingroup MeshIViz_ExtractedMesh_DataSets
* Specialization for extracted structured vector sets containing MbVec3d
*/
typedef MeXDataSetIj<MbVec3d> MeXVec3dSetIj;

#endif

