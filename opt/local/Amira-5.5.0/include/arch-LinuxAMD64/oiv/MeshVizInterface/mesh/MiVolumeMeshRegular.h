/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MIVOLUMEMESHREGULAR_H
#define _MIVOLUMEMESHREGULAR_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/MiMeshIjk.h>
#include <MeshVizInterface/mesh/MiMeshRegular.h>

#include <Inventor/STL/ostream>
/**
* @DTEXT Regular volume mesh abstract interface.
* 
* @ingroup MeshIViz_Mesh
* 
* @DESCRIPTION
*   This interface defines a regular volume mesh. 
*   It is a parallelepiped subdivided into parallelepiped cells.
*   All cells have the same size.
*   The geometry of this parallelepiped is given by getMin() and getMax() 
*   inherited from MiMeshRegular::getGeometry(). 
*   The number of cells on each axis is given by getNumCellsI(), 
*   getNumCellsJ() and getNumCellsK() inherited from MiMeshIjk::getTopology().
*
*/
class MiVolumeMeshRegular : virtual public MiMeshIjk, virtual public MiMeshRegular
{
public:
  /**
  * @copydoc MiVolumeMeshUnstructured::getNewClone() const
  */
  virtual const MiVolumeMeshRegular* getNewClone() const
  {
    throw MiAbstractMethodError("MiVolumeMeshRegular::getNewClone()");
  }

protected: //PROTECTED_TO_DOCUMENT
  /**
  * @copydoc MiMesh::toStream(std::ostream& s) const
  */
  virtual std::ostream& toStream(std::ostream& s) const 
  { 
    s << "#MiVolumeMeshRegular" << std::endl;
    s << getTopology() << std::endl;
    s << getGeometry() << std::endl;
    return s;
  }

};

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif
