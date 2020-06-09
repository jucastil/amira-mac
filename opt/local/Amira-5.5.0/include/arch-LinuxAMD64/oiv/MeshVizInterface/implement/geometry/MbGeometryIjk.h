/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MbGeometryIjk_H
#define _MbGeometryIjk_H

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4250)
#pragma warning(disable:4251)
#endif

#include <MeshVizInterface/mesh/geometry/MiGeometry.h>
#include <MeshVizInterface/mesh/geometry/MiGeometryIjk.h>

#include <MeshVizInterface/implement/geometry/MbGeometry.h>
#include <MeshVizInterface/implement/MbIjkToI.h>

#include <Inventor/STL/vector>

/**
* @DTEXT Generic parallelepiped, rectangular or straight line geometry.
* 
* @ingroup MeshIViz_Implement_Geometry
* 
* @DESCRIPTION
*    The geometry is given by 2 points defining 2 extremities.
* 
*/
template <typename _Vec3T=MbVec3d>
class MbGeometryIjk : public MiGeometryIjk, public MbGeometry, private MbIjkToI
{
public:
  /** Constructor */
  MbGeometryIjk(size_t numNodesI, size_t numNodesJ, size_t numNodesK) 
    : MbIjkToI(numNodesI,numNodesJ),m_numJ(numNodesJ),m_numK(numNodesK), 
    m_max(0), m_min(_Vec3T::numeric_limit_max())
  {
    m_coords.resize(m_numIxJ*m_numK);
  }

  /**
  * Returns the coordinate (i,j,k) of this geometry.
  */
  virtual MbVec3d getCoord(size_t i, size_t j, size_t k) const 
  {
    return (MbVec3d) m_coords[getI(i,j,k)];
  }

  /**
  * Sets the coordinate at index (i,j,k).
  */
  virtual void setCoord(size_t i, size_t j, size_t k, const _Vec3T& val ) 
  {
    if (i<m_numI && j<m_numJ && k<m_numK) 
    {
      m_coords[getI(i,j,k)] = val;
      for(size_t d=0; d<3; ++d)
      {
        if(val[d] > m_max[d]) m_max[d] = val[d];
        if(val[d] < m_min[d]) m_min[d] = val[d];
      }
      m_timeStamp = MxTimeStamp::getTimeStamp();
    }
  }

  /**
  * Gets the size of the geometry.
  */
  void getSize(size_t &numNodesI, size_t &numNodesJ, size_t &numNodesK)
  {
    numNodesI = m_numI;
    numNodesJ = m_numJ;
    numNodesK = m_numK;
  }

  //@{
  /**
  * Gets the min and max of the geometry.
  */
  MbVec3d getMin() const { return (MbVec3d) m_min;}
  MbVec3d getMax() const { return (MbVec3d) m_max;}
  //@}

protected:

  std::vector<_Vec3T> m_coords;
  _Vec3T m_min;
  _Vec3T m_max;
  size_t m_numJ;
  size_t m_numK;

};

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif
