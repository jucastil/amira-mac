/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MILINEMESHREGULAR_H
#define _MILINEMESHREGULAR_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/MiMesh.h>
#include <MeshVizInterface/mesh/MiMeshRegular.h>

class MiGeometryRegular;
class MiTopologyI;


/**
* @DTEXT Regular line mesh abstract interface.
* 
* @ingroup MeshIViz_Mesh
* 
* @DESCRIPTION
*   This interface defines a regular line mesh. 
*   This is a straight line subdivided into getNumCells() segment cells of equal size.
*   The number of cells is given by getNumCells(), in the MiTopologyI interface.
*   The bounds of this line are given by getMin() and getMax() 
*   inherited from MiMeshRegular::getGeometry(). 
*
*/
class MiLineMeshRegular : virtual public MiMeshRegular
{
public:
  /**
  * Returns the topology of this mesh.
  */
  virtual const MiTopologyI& getTopology() const = 0;

  /**
  * @copydoc MiVolumeMeshUnstructured::getNewClone() const
  */
  virtual const MiLineMeshRegular* getNewClone() const
  {
    throw MiAbstractMethodError("MiLineMeshRegular::getNewClone()");
  }

protected: //PROTECTED_TO_DOCUMENT
  /**
  * @copydoc MiMesh::toStream(std::ostream& s) const
  */
  virtual std::ostream& toStream(std::ostream& s) const { return s;}

};

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif
