/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MeXVolumeCell_H
#define _MeXVolumeCell_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/cell/MiVolumeCell.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/utility>

/**
* @DTEXT  Defines an abstract cell of an extracted volume mesh.
* 
* @ingroup MeshIViz_ExtractedMesh_Cell
* 
* @DESCRIPTION
*    A volume cell is a polyhedron element that connects adjacent nodes of a volume mesh.
* 
*/

class MESHIVIZ_API MeXVolumeCell : public MiVolumeCell
{
public:
  /**
  * Gets the normal to the given facet of the cell.
  * This method is not pure virtual because it is not used by 
  * extraction classes. However using this method will generate an exception. 
  * An application does not need to override this method if not used.
  * 
  * @param[in] facet The index of the facet (where 0 <= facet < getNumFacets()).
  * @param[in] meshGeometry The geometry of the mesh. Used to retrieve the node coordinates
  * of this cell.
  * @return a vector.
  */
  virtual MbVec3d getFacetNormal(size_t UNREF_PARAM(facet), const MiGeometryI* UNREF_PARAM(meshGeometry)) const 
  {
    throw MiAbstractMethodError("MeXVolumeCell::getFacetNormal(size_t facet, const MiGeometryI* meshGeometry)");
  }

  /**
  * Gets the volume of the cell.
  * This method is not pure virtual because it is not used by 
  * extraction classes. However using this method will generate an exception. 
  * An application does not need to override this method if not used.
  * 
  * @param[in] meshGeometry The geometry of the mesh. Used to retrieve the node coordinates
  * of this cell.
  */
  virtual double getVolume(const MiGeometryI* UNREF_PARAM(meshGeometry)) const 
  {
    throw MiAbstractMethodError("MeXVolumeCell::getVolume(const MiGeometryI* meshGeometry)");
  }

};


#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif
