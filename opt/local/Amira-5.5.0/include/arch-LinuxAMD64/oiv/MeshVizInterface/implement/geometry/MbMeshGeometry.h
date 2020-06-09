/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MBMESHGEOMETRY_H
#define  _MBMESHGEOMETRY_H

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4250)
#pragma warning(disable:4251)
#endif

#include <MeshVizInterface/mesh/geometry/MiGeometryI.h>
#include <MeshVizInterface/implement/geometry/MbGeometry.h>
#include <MeshVizInterface/MbVec3.h>

#include <Inventor/STL/vector>

/**
 * @DTEXT  Defines a set of 3D coordinates.
 * 
 * @ingroup MeshIViz_Implement_Geometry
 * 
 * @DESCRIPTION
 * 
 */
template <typename _Vec3T=MbVec3d>
class MbMeshGeometry : public MiGeometryI, public MbGeometry
{
public:
  MbMeshGeometry() {}

  /** Constructor */
  template <typename _Vec3Iter>
  MbMeshGeometry(_Vec3Iter begin, _Vec3Iter end)
#ifndef MBMESH_DONT_USE_STL
    : m_coords(begin,end)
#endif
  {
#ifdef MBMESH_DONT_USE_STL
    m_coordsSize = end-begin;
    m_coords = new _Vec3T[m_coordsSize];
    _Vec3Iter it = begin;
    size_t i;
    for (it=begin, i=0; it!=end; ++it,++i)
      m_coords[i] = *it;
#endif
  }

#ifdef MBMESH_DONT_USE_STL
  ~MbMeshGeometry();
#endif

  /**
  * Change the content of this dataset. Clears the current content and copy the 
  * data from the interval [begin,end[.
  * The timestamp of this dataset is incremented.
  */
  template <typename _Vec3Iter>
  void assign(_Vec3Iter begin, _Vec3Iter end)
  {
#ifndef MBMESH_DONT_USE_STL
    m_coords.assign(begin,end);
#else
    delete [] m_coords;
    m_coordsSize = end-begin;
    m_coords = new _Vec3T[m_coordsSize];
    _Vec3Iter it = begin;
    size_t i;
    for (it=begin, i=0; it!=end; ++it,++i)
      m_coords[i] = *it;
#endif
    m_timeStamp = MxTimeStamp::getTimeStamp();
  }

  /**
  * Return the min point of this parallelepiped.
  */
  virtual MbVec3d getMin() const;
  /**
  * Return the max point of this parallelepiped.
  */
  virtual MbVec3d getMax() const;

  /**
  * Returns the coordinate (i) of this geometry.
  */
  virtual MbVec3d getCoord(size_t i) const 
  {
    return (MbVec3d)m_coords[i];
  }

  MbVec3d getCenter() const
  {
    return (getMin() + getMax())/2.0f;
  }

  size_t getSize() const;

  void rotate(double angle, size_t rotaxis);

  template <typename _FunctorT>
  void transform(const _FunctorT& func);

private:
#ifndef MBMESH_DONT_USE_STL
  std::vector<_Vec3T> m_coords;
#else
  _Vec3T* m_coords;
  size_t m_coordsSize;
#endif
};

#ifdef MBMESH_DONT_USE_STL
//-----------------------------------------------------------------------------
template <typename _Vec3T>
MbMeshGeometry<_Vec3T>::~MbMeshGeometry() 
{
  delete [] m_coords;
}
#endif

template <typename _Vec3T>
inline size_t
MbMeshGeometry<_Vec3T>::getSize() const
{
#ifndef MBMESH_DONT_USE_STL
  return m_coords.size();
#else
  return m_coordsSize;
#endif
}

//-----------------------------------------------------------------------------
template <typename _Vec3T>
inline MbVec3d
MbMeshGeometry<_Vec3T>::getMin() const
{
  double xm = m_coords[0][0];
  double ym = m_coords[0][1];
  double zm = m_coords[0][2];
  double cx,cy,cz;

#ifndef MBMESH_DONT_USE_STL
  for (size_t i=1; i<m_coords.size(); ++i)
#else
  for (size_t i=1; i<m_coordsSize; ++i)
#endif
  {
    cx = m_coords[i][0];
    cy = m_coords[i][1];
    cz = m_coords[i][2];
    if (cx < xm) 
      xm = cx;
    if (cy < ym) 
      ym = cy;
    if (cz < zm) 
      zm = cz;
  }
  return MbVec3d(xm,ym,zm);
}


//-----------------------------------------------------------------------------
template <typename _Vec3T>
inline MbVec3d
MbMeshGeometry<_Vec3T>::getMax() const
{
  double xm = m_coords[0][0];
  double ym = m_coords[0][1];
  double zm = m_coords[0][2];
  double cx,cy,cz;

#ifndef MBMESH_DONT_USE_STL
  for (size_t i=1; i<m_coords.size(); ++i)
#else
  for (size_t i=1; i<m_coordsSize; ++i)
#endif
  {
    cx = m_coords[i][0];
    cy = m_coords[i][1];
    cz = m_coords[i][2];
    if (cx > xm) 
      xm = cx;
    if (cy > ym) 
      ym = cy;
    if (cz > zm) 
      zm = cz;
  }
  return MbVec3d(xm,ym,zm);
}

//-----------------------------------------------------------------------------
template < typename _Vec3T>
void 
MbMeshGeometry<_Vec3T>::rotate(double angle, size_t rotaxis)
{
  const MbVec3d center = this->getCenter();
  if (angle != 0.0)
  {
    double cosa = cos(angle);
    double sina = sin(angle);
    _Vec3T shift((rotaxis!=1 ? center[0]:0), (rotaxis!=1?center[1]:0), (rotaxis!=1?center[2]:0));
    _Vec3T tcoord;
    _Vec3T* it = &m_coords[0];
    size_t numCoord = this->getSize();
    switch(rotaxis)
    {
    case 0:
      for (size_t i = 0; i < numCoord; ++i, ++it)
      {
        tcoord = *it - shift;
        it->setValue( tcoord[0],
          tcoord[1]*cosa - tcoord[2]*sina,
          tcoord[1]*sina + tcoord[2]*cosa);
        *it += shift;
      }
      break;
    case 1:
      for (size_t i = 0; i < numCoord; ++i, ++it)
      {
        tcoord = *it - shift;
        it->setValue( tcoord[0]*cosa - tcoord[2]*sina,
          tcoord[1],
          tcoord[0]*sina + tcoord[2]*cosa);
        *it += shift;
      }
      break;
    case 2:
      for (size_t i = 0; i < numCoord; ++i, ++it)
      {
        tcoord = *it - shift;
        it->setValue( tcoord[0]*cosa - tcoord[1]*sina,
                            tcoord[0]*sina + tcoord[1]*cosa,
                            tcoord[2]);
        *it += shift;
      }
      break;
    }
    this->touch();
  }
}

//-----------------------------------------------------------------------------
template < typename _Vec3T>
template < typename _FunctorT>
void 
MbMeshGeometry<_Vec3T>::transform(const _FunctorT& func)
{
  size_t numCoord = this->getSize();
  for (size_t i = 0; i < numCoord; ++i)
    m_coords[i] = func(m_coords[i]); 
  this->touch();
}

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif







