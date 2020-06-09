/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MeXCell_H
#define _MeXCell_H

#include <MeshVizInterface/mesh/cell/MiCell.h>
#include <MeshVizInterface/extrmesh/cell/MeXCell.h>

/**
* @DTEXT  Defines an abstract cell of an extracted mesh.
* 
* @ingroup MeshIViz_ExtractedMesh_Cell
* 
* @DESCRIPTION
*    A cell is a basic volume, surface or edge element that 
*    connects adjacent nodes of a mesh. 
*
*  @see MeXLineCell
*  @see MeXSurfaceCell
*  @see MeXVolumeCell
* 
*/
class MESHIVIZ_API MeXCell : virtual public MiCell
{

};


#endif 







