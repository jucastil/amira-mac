/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MBVOLUMEGEOMETRYRECTILINEAR_H
#define _MBVOLUMEGEOMETRYRECTILINEAR_H

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4250)
#pragma warning(disable:4251)
#endif

#include <MeshVizInterface/mesh/geometry/MiVolumeGeometryRectilinear.h>
#include <MeshVizInterface/implement/geometry/MbGeometry.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/algorithm>

/**
* @DTEXT Generic parallelepiped geometry.
* 
* @ingroup MeshIViz_Implement_Geometry
* 
* @DESCRIPTION
*    A generic abstract interface for a rectilinear geometry. 
* 
*/
template <typename _T=double>
class MbVolumeGeometryRectilinear : public MiVolumeGeometryRectilinear, public MbGeometry
{
public:
  /** Constructor */
  template <typename _NodeIdIter>
  MbVolumeGeometryRectilinear(_NodeIdIter xBegin,_NodeIdIter xEnd, 
    _NodeIdIter yBegin,_NodeIdIter yEnd,_NodeIdIter zBegin,_NodeIdIter zEnd)
  {
    m_x.assign(xBegin,xEnd);
    m_y.assign(yBegin,yEnd);
    m_z.assign(zBegin,zEnd);
    m_min.setValue(*std::min_element(xBegin,xEnd),
                   *std::min_element(yBegin,yEnd),
                   *std::min_element(zBegin,zEnd));
    m_max.setValue(*std::max_element(xBegin,xEnd),
                   *std::max_element(yBegin,yEnd),
                   *std::max_element(zBegin,zEnd));
  }

  /** 
  * Returns the X coordinate at index I 
  */
  virtual double getX(size_t i) const { return m_x[i]; }
  /** 
  * Returns the Y coordinate at index J 
  */
  virtual double getY(size_t j) const { return m_y[j]; }
   /** 
  * Returns the Y coordinate at index K 
  */
  virtual double getZ(size_t k) const { return m_z[k]; }

  /**
  * Return the min point of this parallelepiped.
  */
  MbVec3d getMin() const { return (MbVec3d) m_min;}
  /**
  * Return the max point of this parallelepiped.
  */
  MbVec3d getMax() const { return (MbVec3d) m_max;}

protected:
  std::vector<_T> m_x;
  std::vector<_T> m_y;
  std::vector<_T> m_z;
  MbVec3<_T> m_min;
  MbVec3<_T> m_max;

};

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif
