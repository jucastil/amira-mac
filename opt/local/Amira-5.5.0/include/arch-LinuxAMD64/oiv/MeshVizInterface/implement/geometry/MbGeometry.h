/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MBGEOMETRY_H
#define _MBGEOMETRY_H

#include <MeshVizInterface/mesh/geometry/MiGeometry.h>
#include <MeshVizInterface/MxTimeStamp.h>

/**
* @DTEXT Generic geometry interface.
* 
* @ingroup MeshIViz_Implement_Geometry
* 
* @DESCRIPTION
*    Generic base class of geometry interfaces used by mesh interfaces. 
* 
*/
class MbGeometry : virtual public MiGeometry
{
public:
  MbGeometry() : m_timeStamp(MxTimeStamp::getTimeStamp()) {}

  /** 
  * Returns the time stamp 
  */
  virtual size_t getTimeStamp() const { return m_timeStamp; }

  /**
  * @internal
  * Simulate a modification to this geometry
  */
  void touch()
  {
    m_timeStamp = MxTimeStamp::getTimeStamp();
  }

protected: 
  size_t m_timeStamp;

};

#endif
