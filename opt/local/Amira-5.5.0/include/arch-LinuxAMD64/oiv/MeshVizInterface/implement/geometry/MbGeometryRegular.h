/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MBGEOMETRYREGULAR_H
#define _MBGEOMETRYREGULAR_H

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4250)
#pragma warning(disable:4251)
#endif

#include <MeshVizInterface/mesh/geometry/MiGeometryRegular.h>
#include <MeshVizInterface/implement/geometry/MbGeometry.h>

/**
* @DTEXT Generic parallelepiped, rectangular or straight line geometry.
* 
* @ingroup MeshIViz_Implement_Geometry
* 
* @DESCRIPTION
*    The geometry is given by 2 points defining 2 extremities.
* 
*/
template <typename _T=double>
class MbGeometryRegular : public MiGeometryRegular, public MbGeometry
{
public:
  /** Constructor */
  MbGeometryRegular(_T xmin, _T ymin, _T zmin, 
                    _T xmax, _T ymax, _T zmax) 
    : m_min(xmin,ymin,zmin), m_max(xmax,ymax,zmax)
  {
  }

  /**
  * Return the min point of this parallelepiped.
  */
  virtual MbVec3d getMin() const { return m_min; }

  /**
  * Return the max point of this parallelepiped.
  */
  virtual MbVec3d getMax() const { return m_max; }

protected:
  MbVec3d m_min;
  MbVec3d m_max;

};

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif
