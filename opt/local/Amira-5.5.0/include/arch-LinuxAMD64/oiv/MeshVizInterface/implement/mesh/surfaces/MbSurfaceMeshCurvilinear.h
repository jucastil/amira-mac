/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _MBSURFACEMESHCURVILINEAR_H
#define _MBSURFACEMESHCURVILINEAR_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#  pragma warning(disable:4251)
#endif

#include <MeshVizInterface/mesh/MiSurfaceMeshCurvilinear.h>
#include <MeshVizInterface/implement/mesh/MbMeshIj.h>

#include <MeshVizInterface/implement/geometry/MbGeometryIj.h>

/**
 * @DTEXT class defining a Curvilinear volume mesh.
 * 
 * @ingroup MeshIViz_Implement_Mesh
 * 
 * @DESCRIPTION

 * 
 */

template <typename _CoordT=MbVec3d, typename _ScalarT=double, typename _Vec3T=MbVec3d>
class MbSurfaceMeshCurvilinear : virtual public MiSurfaceMeshCurvilinear, public MbMeshIj<_ScalarT,_Vec3T>
{
public:

  /** Constructor */
  MbSurfaceMeshCurvilinear(size_t numCellI, size_t numCellJ) 
    : MbMeshIj<_ScalarT,_Vec3T>(numCellI,numCellJ), m_geometry(numCellI+1,numCellJ+1)
  {
  }

  /**
  * Set coordinate (i,j)
  */
  virtual void setCoord(size_t i, size_t j, const _CoordT& val )
  {
    m_geometry.setCoord(i,j,val);
  }
  
  /**
  * Get the geometry interface
  */
  virtual const MiGeometryIj& getGeometry() const
  {
    return m_geometry;
  }

protected:
  virtual std::ostream& toStream(std::ostream& s) const;

  MbGeometryIj<_CoordT> m_geometry;

};

//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
inline std::ostream& 
MbSurfaceMeshCurvilinear<_CoordT,_ScalarT,_Vec3T>::toStream(std::ostream& s) const
{
  MiSurfaceMeshCurvilinear::toStream(s);
  MbMeshIj<_ScalarT,_Vec3T>::toStream(s);
  return s;
}

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif
