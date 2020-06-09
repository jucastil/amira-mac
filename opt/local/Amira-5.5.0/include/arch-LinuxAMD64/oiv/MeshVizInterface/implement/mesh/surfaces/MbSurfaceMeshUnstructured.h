/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MBSURFACEMESHUNSTRUCTURED_H
#define _MBSURFACEMESHUNSTRUCTURED_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/MiSurfaceMeshUnstructured.h>

#include <MeshVizInterface/implement/mesh/MbMesh.h>
//#include <MeshVizInterface/implement/geometry/MbMeshGeometry.h>


#include <MeshVizInterface/MbVec3.h>
#include <Inventor/STL/vector>
#include <Inventor/STL/iostream>

/**
 * @DTEXT Abstract class to define an unstructured surface mesh .
 * 
 * @ingroup MeshIViz_Implement_Mesh
 * 
 * @DESCRIPTION

 * 
 */
template <typename _CoordT=MbVec3d, typename _ScalarT=double, typename _Vec3T=MbVec3d>
class MbSurfaceMeshUnstructured : virtual public MiSurfaceMeshUnstructured, public MbMesh<_CoordT,_ScalarT,_Vec3T>
{

public:
  /**
  * Constructor of an empty mesh. 
  */
  MbSurfaceMeshUnstructured() {}

protected:
  /**
  * Defines a specialized output on stream 
  */
  virtual std::ostream& toStream(std::ostream& s) const;


  template <typename _CoordIter>
  MbSurfaceMeshUnstructured(_CoordIter beginCoord, _CoordIter endCoord);
  
};


//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
template <typename _CoordIter>
inline 
MbSurfaceMeshUnstructured<_CoordT,_ScalarT,_Vec3T>::MbSurfaceMeshUnstructured(
  _CoordIter beginCoord, _CoordIter endCoord
  ) 
  : MbMesh<_CoordT,_ScalarT,_Vec3T>(beginCoord,endCoord)
{
}

//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
inline std::ostream&
MbSurfaceMeshUnstructured<_CoordT,_ScalarT,_Vec3T>::toStream(std::ostream& s) const
{
  MiSurfaceMeshUnstructured::toStream(s);
  MbMesh<_CoordT,_ScalarT,_Vec3T>::toStream(s);
  return s;
}


#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif 







