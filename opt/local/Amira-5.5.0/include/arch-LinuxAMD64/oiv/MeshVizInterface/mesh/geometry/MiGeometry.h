/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MIGEOMETRY_H
#define _MIGEOMETRY_H

#include <Inventor/STL/string>
#include <Inventor/STL/iostream>

#include <MeshVizInterface/MxMeshIViz.h>
#include <MeshVizInterface/MbVec3.h>
#include <MeshVizInterface/MiAbstractMethodError.h>


/**
* @DTEXT Generic geometry interface.
* 
* @ingroup MeshIViz_Mesh_Geometry
* 
* @DESCRIPTION
*    Generic base class of geometry interfaces used by mesh interfaces. 
* 
*/
class MESHIVIZ_API MiGeometry
{
public:
  virtual ~MiGeometry() {}

  /**
  * Returns the minimum value of this set.
  */
  virtual MbVec3d getMin() const 
  {
    throw MiAbstractMethodError("MiGeometry::getMin()");
  }
  /**
  * Returns the maximum value of this set.
  */
  virtual MbVec3d getMax() const 
  {
    throw MiAbstractMethodError("MiGeometry::getMax()");
  }

  /**
  * Returns a time stamp on this geometry. When the content of the geometry 
  * changes, the time stamp must increase. The time stamp allows MeshViz 
  * to be aware of any change to this geometry.
  */
  virtual size_t getTimeStamp() const = 0;

  /**
  * @copydoc MiMesh::operator <<()
  */
  friend std::ostream& operator << (std::ostream& s, const MiGeometry& dataset)
  {
    return dataset.toStream(s);
  }

protected: //PROTECTED_TO_DOCUMENT
  /**
  * @copydoc MiMesh::toStream(std::ostream& s) const
  */  
  virtual std::ostream& toStream(std::ostream& s) const { return s; }

};

#endif
