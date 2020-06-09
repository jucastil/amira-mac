/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MIMESHUNSTRUCTUREDI_H
#define _MIMESHUNSTRUCTUREDI_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <Inventor/STL/vector>

#include <MeshVizInterface/mesh/MiMeshUnstructured.h>
#include <MeshVizInterface/mesh/topology/MiTopologyExplicitI.h>

/**
* @DTEXT I Unstructured mesh abstract interface.
* 
* @ingroup MeshIViz_Mesh
* 
* @DESCRIPTION
*    This interface defines a generic unstructured mesh containing any type of 
*    cells. An unstructured mesh I can be either a volume, a surface or a line.
*
*    @see MiVolumeMeshUnstructured
*    @see MiSurfaceMeshUnstructured
*    @see MiLineMeshUnstructured
* 
*/
class MiMeshUnstructuredI : virtual public MiMeshUnstructured
{
public:
  /**
  * Returns the generic topology of this mesh. 
  */
  virtual const MiTopologyExplicitI& getTopology() const = 0;
};

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif
