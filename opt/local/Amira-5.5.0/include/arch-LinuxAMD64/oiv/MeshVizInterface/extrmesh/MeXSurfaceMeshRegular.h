/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MeXSurfaceMeshRegular_H
#define _MeXSurfaceMeshRegular_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/extrmesh/MeXMeshIj.h>
#include <MeshVizInterface/mesh/MiSurfaceMeshRegular.h>
#include <MeshVizInterface/extrmesh/geometry/MeXGeometryRegular.h>

#include <Inventor/STL/ostream>
/**
* @DTEXT Extracted regular surface mesh abstract interface.
* 
* @ingroup MeshIViz_ExtractedMesh
* 
* @DESCRIPTION
*   This interface defines an extracted regular surface mesh. 
*   It is a rectangular surface subdivided into rectangular cells.
*   All cells have the same size.
*   The geometry of this rectangle is given by getMin() and getMax() 
*   inherited from MiMeshRegular::getGeometry(). 
*   The number of cells on each axis is given by getNumCellsI(), 
*   and getNumCellsJ() inherited from MiMeshIj::getTopology().
*
*/
class MeXSurfaceMeshRegular : public MiSurfaceMeshRegular, virtual public MeXMeshIj
{
public:
  /**
  * Returns the geometry of this mesh. 
  */
  virtual const MeXGeometryRegular& getGeometry() const = 0;

  /**
  * @copydoc MiVolumeMeshUnstructured::getNewClone() const
  */
  virtual const MeXSurfaceMeshRegular* getNewClone() const
  {
    throw MiAbstractMethodError("MeXSurfaceMeshRegular::getNewClone()");
  }

};

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif
