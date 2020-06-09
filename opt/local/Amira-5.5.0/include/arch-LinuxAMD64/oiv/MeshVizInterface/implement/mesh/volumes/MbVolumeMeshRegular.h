/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _MBVOLUMEMESHREGULAR_H
#define _MBVOLUMEMESHREGULAR_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#  pragma warning(disable:4251)
#endif

#include <MeshVizInterface/mesh/MiVolumeMeshRegular.h>
#include <MeshVizInterface/implement/mesh/volumes/MbMeshStructuredIjk.h>
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
class MbVolumeMeshRegular : virtual public MiVolumeMeshRegular, public MbMeshStructuredIjk<_ScalarT,_Vec3T>
{
public:

  /** Constructor */
  MbVolumeMeshRegular(size_t numCellI, size_t numCellJ, size_t numCellK,
                      _CoordT xmin, _CoordT ymin, _CoordT zmin, 
                      _CoordT xmax, _CoordT ymax, _CoordT zmax) 
    : MbMeshStructuredIjk<_ScalarT,_Vec3T>(numCellI,numCellJ,numCellK), 
      m_geometry(xmin,ymin,zmin, xmax,ymax,zmax)
  {
  }

  /**
  * Returns the geoemtry interface
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
MbVolumeMeshRegular<_CoordT,_ScalarT,_Vec3T>::toStream(std::ostream& s) const
{
  MiVolumeMeshRegular::toStream(s);
  MbMeshStructuredIjk<_ScalarT,_Vec3T>::toStream(s);
  return s;
}


#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif
