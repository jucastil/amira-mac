/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MISURFACEMESHREGULAR_H
#define _MISURFACEMESHREGULAR_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/MiMeshIj.h>
#include <MeshVizInterface/mesh/MiMeshRegular.h>

#include <Inventor/STL/ostream>
/**
* @DTEXT Regular surface mesh abstract interface.
* 
* @ingroup MeshIViz_Mesh
* 
* @DESCRIPTION
*   This interface defines a regular surface mesh. 
*   It is a rectangular surface subdivided into rectangular cells.
*   All cells have the same size.
*   The geometry of this rectangle is given by getMin() and getMax() 
*   inherited from MiMeshRegular::getGeometry(). 
*   The number of cells on each axis is given by getNumCellsI(), 
*   and getNumCellsJ() inherited from MiMeshIj::getTopology().
*
*/
class MiSurfaceMeshRegular : virtual public MiMeshIj, virtual public MiMeshRegular
{
public:
  /**
  * @copydoc MiVolumeMeshUnstructured::getNewClone() const
  */
  virtual const MiSurfaceMeshRegular* getNewClone() const
  {
    throw MiAbstractMethodError("MiSurfaceMeshRegular::getNewClone()");
  }


protected: //PROTECTED_TO_DOCUMENT
  /**
  * @copydoc MiMesh::toStream(std::ostream& s) const
  */
  virtual std::ostream& toStream(std::ostream& s) const 
  {
    s << "#SurfaceMeshRegular" << std::endl;
    s << getTopology() << std::endl;
    s << getGeometry() << std::endl;
    return s;
  }

};

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif
