/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _MBVOLUMEMESHRECTILINEAR_H
#define _MBVOLUMEMESHRECTILINEAR_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#  pragma warning(disable:4251)
#endif

#include <MeshVizInterface/mesh/MiVolumeMeshRectilinear.h>
#include <MeshVizInterface/implement/mesh/volumes/MbMeshStructuredIjk.h>

#include <MeshVizInterface/implement/geometry/MbVolumeGeometryRectilinear.h>

/**
 * @DTEXT class defining a Rectilinear volume mesh.
 * 
 * @ingroup MeshIViz_Implement_Mesh
 * 
 * @DESCRIPTION

 * 
 */

template <typename _CoordT=double, typename _ScalarT=double, typename _Vec3T=MbVec3d>
class MbVolumeMeshRectilinear : virtual public MiVolumeMeshRectilinear, public MbMeshStructuredIjk<_ScalarT,_Vec3T>
{
public:
  /** Constructor */
  template <typename _NodeIdIter>
  MbVolumeMeshRectilinear(size_t numCellI, size_t numCellJ, size_t numCellK, 
    _NodeIdIter xBegin,_NodeIdIter xEnd, 
    _NodeIdIter yBegin,_NodeIdIter yEnd,
    _NodeIdIter zBegin,_NodeIdIter zEnd) 
    : MbMeshStructuredIjk<_ScalarT,_Vec3T>(numCellI,numCellJ,numCellK),
      m_geometry(xBegin,xEnd,yBegin,yEnd,zBegin,zEnd)
  {
  }

  /** Gets the geometry interface */
  virtual const MiVolumeGeometryRectilinear& getGeometry() const
  {
    return m_geometry;
  }

protected:
  virtual std::ostream& toStream(std::ostream& s) const;

  MbVolumeGeometryRectilinear<_CoordT> m_geometry;

};

//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
inline std::ostream& 
MbVolumeMeshRectilinear<_CoordT,_ScalarT,_Vec3T>::toStream(std::ostream& s) const
{
  MiVolumeMeshRectilinear::toStream(s);
  MbMeshStructuredIjk<_ScalarT,_Vec3T>::toStream(s);
  return s;
}


#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif
