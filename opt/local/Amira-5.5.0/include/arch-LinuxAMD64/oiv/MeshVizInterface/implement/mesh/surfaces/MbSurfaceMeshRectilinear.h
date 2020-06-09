/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MBSURFACEMESHRECTILINEAR_H
#define _MBSURFACEMESHRECTILINEAR_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#  pragma warning(disable:4251)
#endif

#include <MeshVizInterface/mesh/MiSurfaceMeshRectilinear.h>
#include <MeshVizInterface/implement/mesh/MbMeshIj.h>

#include <MeshVizInterface/implement/geometry/MbSurfaceGeometryRectilinear.h>

/**
 * @DTEXT class defining a Rectilinear volume mesh.
 * 
 * @ingroup MeshIViz_Implement_Mesh
 * 
 * @DESCRIPTION

 * 
 */

template <typename _CoordT=double, typename _ScalarT=double, typename _Vec3T=MbVec3d>
class MbSurfaceMeshRectilinear : virtual public MiSurfaceMeshRectilinear, public MbMeshIj<_ScalarT,_Vec3T>
{
public:
  /** Constructor */
  template <typename _NodeIdIter>
  MbSurfaceMeshRectilinear( _NodeIdIter xBegin,_NodeIdIter xEnd, 
                            _NodeIdIter yBegin,_NodeIdIter yEnd) :
  MbMeshIj<_ScalarT,_Vec3T>(std::distance(xBegin,xEnd)-1,std::distance(yBegin,yEnd)-1),
  m_geometry(xBegin,xEnd,yBegin,yEnd)
  {
  }

  /**
  * Get the geometry interface
  */
  virtual const MiSurfaceGeometryRectilinear& getGeometry() const
  {
    return m_geometry;
  }

protected:
  virtual std::ostream& toStream(std::ostream& s) const;

  MbSurfaceGeometryRectilinear<_CoordT> m_geometry;

};

//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
inline std::ostream& 
MbSurfaceMeshRectilinear<_CoordT,_ScalarT,_Vec3T>::toStream(std::ostream& s) const
{
  MiSurfaceMeshRectilinear::toStream(s);
  MbMeshIj<_ScalarT,_Vec3T>::toStream(s);
  return s;
}

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif
