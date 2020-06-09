/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MeXGeometryI_H
#define _MeXGeometryI_H

#include <MeshVizInterface/mesh/geometry/MiGeometryI.h>

/**
* @DTEXT Generic geometry interface for extracted unstructured meshes.
* 
* @ingroup MeshIViz_ExtractedMesh_Geometry
* 
* @DESCRIPTION
*    Generic geometry interface accessible via one index.
*    This type of geometry is typically used by extracted unstructured mesh interfaces. 
* 
*/
class MESHIVIZ_API MeXGeometryI : public MiGeometryI
{
public:
  /**
  * Returns the number of points in the geometry.
  */
  virtual size_t getSize() const = 0; 

};


#endif 
