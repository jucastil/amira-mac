/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MeXDataSetIjk_H
#define _MeXDataSetIjk_H

#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>
#include <MeshVizInterface/extrmesh/data/MeXBoundedDataSet.h>

/**
* @DTEXT Generic data set interface for extracted structured volume meshes.
* 
* @ingroup MeshIViz_ExtractedMesh_DataSets
* 
* @DESCRIPTION
*    A generic abstract template interface for a data set returned by any extract of a structured volume mesh.
* 
*/
template <typename _T>
class MeXDataSetIjk : virtual public MiDataSetIjk<_T>, virtual public MeXBoundedDataSet<_T>
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
  /**
  * Returns the size of the dataset along the third logical axis.
  */
  virtual size_t getSizeK() const = 0;

};

/**
* @ingroup MeshIViz_ExtractedMesh_DataSets
* Specialization for extracted structured scalar sets containing double
*/
typedef MeXDataSetIjk<double>  MeXScalardSetIjk;
/**
* @ingroup MeshIViz_ExtractedMesh_DataSets
* Specialization for extracted structured vector sets containing MbVec3d
*/
typedef MeXDataSetIjk<MbVec3d> MeXVec3dSetIjk;

#endif
