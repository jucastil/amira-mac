/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MBGEOMETRYIJ_H
#define _MBGEOMETRYIJ_H

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4250)
#pragma warning(disable:4251)
#endif

#include <MeshVizInterface/mesh/geometry/MiGeometry.h>
#include <MeshVizInterface/mesh/geometry/MiGeometryIj.h>

#include <MeshVizInterface/implement/geometry/MbGeometry.h>
#include <MeshVizInterface/implement/MbIjToI.h>

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
class MbGeometryIj : public MiGeometryIj, public MbGeometry, private MbIjToI
{
public:
  /** Constructor */
  MbGeometryIj(size_t numNodesI, size_t numNodesJ) 
    : MbIjToI(numNodesI),m_numJ(numNodesJ),
    m_max(0), m_min(_Vec3T::numeric_limit_max())
  {
    m_coords.resize(m_numI*m_numJ);
  }

  /**
  * Returns the coordinate (i,j) of this geometry.
  */
  virtual MbVec3d getCoord(size_t i, size_t j) const 
  {
    return (MbVec3d) m_coords[getI(i,j)];
  }


  /**
  * Sets the coordinate (i,j).
  */
 virtual void setCoord(size_t i, size_t j, const _Vec3T& val ) 
  {
    if (i<m_numI && j<m_numJ) 
    {
      m_coords[getI(i,j)] = val;
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
  void getSize(size_t &numNodesI, size_t &numNodesJ)
  {
    numNodesI = m_numI;
    numNodesJ = m_numJ;
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
  size_t m_numJ;
  _Vec3T m_min;
  _Vec3T m_max;

};

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif
