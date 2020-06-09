/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _MBVOLUMEMESHCURVILINEAR_H
#define _MBVOLUMEMESHCURVILINEAR_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#  pragma warning(disable:4251)
#endif

#include <MeshVizInterface/mesh/MiVolumeMeshCurvilinear.h>
#include <MeshVizInterface/implement/mesh/volumes/MbMeshStructuredIjk.h>

#include <MeshVizInterface/implement/geometry/MbGeometryIjk.h>

/**
 * @DTEXT class defining a Curvilinear volume mesh.
 * 
 * @ingroup MeshIViz_Implement_Mesh
 * 
 * @DESCRIPTION

 * 
 */

template <typename _CoordT=MbVec3d, typename _ScalarT=double, typename _Vec3T=MbVec3d>
class MbVolumeMeshCurvilinear : virtual public MiVolumeMeshCurvilinear, public MbMeshStructuredIjk<_ScalarT,_Vec3T>
{
public:

  /** Constructor */
  MbVolumeMeshCurvilinear(size_t numCellI, size_t numCellJ, size_t numCellK) 
    : MbMeshStructuredIjk<_ScalarT,_Vec3T>(numCellI,numCellJ,numCellK),
      m_geometry(numCellI+1,numCellJ+1,numCellK+1)
  {
  }


  /**
  * Set coordinate (i,j,k)
  */
  virtual void setCoord(size_t i, size_t j, size_t k, const _CoordT& val )
  {
    m_geometry.setCoord(i,j,k,val);
  }
  
  /**
  * Get the geometry interface
  */
  virtual const MiGeometryIjk& getGeometry() const
  {
    return m_geometry;
  }


protected:
  virtual std::ostream& toStream(std::ostream& s) const;

  MbGeometryIjk<_CoordT> m_geometry;

};

//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
inline std::ostream& 
MbVolumeMeshCurvilinear<_CoordT,_ScalarT,_Vec3T>::toStream(std::ostream& s) const
{
  MiVolumeMeshCurvilinear::toStream(s);
  MbMeshStructuredIjk<_ScalarT,_Vec3T>::toStream(s);
  return s;
}


#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif
