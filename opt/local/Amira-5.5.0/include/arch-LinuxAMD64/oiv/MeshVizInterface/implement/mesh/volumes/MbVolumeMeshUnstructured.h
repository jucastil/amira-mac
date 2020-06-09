/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef _MBVOLUMEMESHUNSTRUCTURED_H
#define _MBVOLUMEMESHUNSTRUCTURED_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/MiVolumeMeshUnstructured.h>
#include <MeshVizInterface/mesh/geometry/MiGeometryI.h>

#include <MeshVizInterface/implement/mesh/MbMesh.h>

#include <MeshVizInterface/MbVec3.h>
#include <Inventor/STL/vector>
#include <Inventor/STL/iostream>

/**
 * @DTEXT Abstract class to define an unstructured mesh .
 * 
 * @ingroup MeshIViz_Implement_Mesh
 * 
 * @DESCRIPTION

 * 
 */
template <typename _CoordT=MbVec3d, typename _ScalarT=double, typename _Vec3T=MbVec3d>
class MbVolumeMeshUnstructured : virtual public MiVolumeMeshUnstructured, public MbMesh<_CoordT,_ScalarT,_Vec3T>
{

public:
  /**
  * Constructor of an empty mesh. 
  */
  MbVolumeMeshUnstructured() {}


protected:
  /**
  * Defines a specialized output on stream 
  */
  virtual std::ostream& toStream(std::ostream& s) const;

  template <typename _CoordIter>
  MbVolumeMeshUnstructured(_CoordIter beginCoord, _CoordIter endCoord);
  

};


//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
template <typename _CoordIter>
inline 
MbVolumeMeshUnstructured<_CoordT,_ScalarT,_Vec3T>::MbVolumeMeshUnstructured(
  _CoordIter beginCoord, _CoordIter endCoord
  ) 
   : MbMesh<_CoordT,_ScalarT,_Vec3T>(beginCoord,endCoord)
{
}

//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
inline std::ostream&
MbVolumeMeshUnstructured<_CoordT,_ScalarT,_Vec3T>::toStream(std::ostream& s) const
{
  MiVolumeMeshUnstructured::toStream(s);
  MbMesh<_CoordT,_ScalarT,_Vec3T>::toStream(s);
  return s;
}

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif 







