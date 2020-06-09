/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _MBSURFACEMESHREGULAR_H
#define _MBSURFACEMESHREGULAR_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#  pragma warning(disable:4251)
#endif

#include <MeshVizInterface/mesh/MiSurfaceMeshRegular.h>
#include <MeshVizInterface/implement/mesh/MbMeshIj.h>

#include <MeshVizInterface/implement/geometry/MbGeometryRegular.h>

/**
 * @DTEXT class defining a regular volume mesh.
 * 
 * @ingroup MeshIViz_Implement_Mesh
 * 
 * @DESCRIPTION

 * 
 */

template <typename _CoordT=double, typename _ScalarT=double, typename _Vec3T=MbVec3d>
class MbSurfaceMeshRegular : virtual public MiSurfaceMeshRegular, public MbMeshIj<_ScalarT,_Vec3T>
{
public:

  /** Constructor */
  MbSurfaceMeshRegular(size_t numCellI, size_t numCellJ,
                      _CoordT xmin, _CoordT ymin, _CoordT zmin, 
                      _CoordT xmax, _CoordT ymax, _CoordT zmax) 
    : MbMeshIj<_ScalarT,_Vec3T>(numCellI,numCellJ), m_geometry(xmin,ymin,zmin, xmax,ymax,zmax)  
  {
  }

  /**
  * Get the geometry interface
  */
  virtual const MiGeometryRegular& getGeometry() const 
  {
    return m_geometry;
  }

protected:
  virtual std::ostream& toStream(std::ostream& s) const;

  MbGeometryRegular<_CoordT> m_geometry;

};

//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
inline std::ostream& 
MbSurfaceMeshRegular<_CoordT,_ScalarT,_Vec3T>::toStream(std::ostream& s) const
{
  MiSurfaceMeshRegular::toStream(s);
  MbMeshIj<_ScalarT,_Vec3T>::toStream(s);
  return s;
}

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif
