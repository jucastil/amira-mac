/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MeXLineCell_H
#define _MeXLineCell_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/extrmesh/cell/MeXCell.h>
#include <MeshVizInterface/mesh/cell/MiLineCell.h>

/**
* @DTEXT  Defines an abstract cell of an extracted line mesh.
* 
* @ingroup MeshIViz_ExtractedMesh_Cell
* 
* @DESCRIPTION
*    A line cell is an edge element that connects adjacent nodes of a line mesh.
* 
*/

class MeXLineCell : public MiLineCell
{
public:
  /**
  * Gets the length of the cell.
  * This method is not pure virtual because it is not used by 
  * extraction classes. However using this method will generate an exception. 
  * An application does not need to override this method if not used.
  * 
  * @param[in] meshGeometry The geometry of the mesh. Used to retrieve the node coordinates
  * of this cell.
  */
  virtual double getLength(const MiGeometryI* UNREF_PARAM(meshGeometry)) const 
  {
    throw MiAbstractMethodError("MeXLineCell::getLength(const MiGeometryI* meshGeometry)");
  }

};

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif

