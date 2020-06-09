/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MeWGeometryI_h
#define _MeWGeometryI_h

#include <MeshVizInterface/extrmesh/geometry/MeXGeometryI.h>
#include <Inventor/STL/vector>

class MiCell;
class MiVolumeCell;

/**
* @DTEXT Abstract interface to write unstructured mesh geometry.
* 
* @ingroup MeshIViz_ExtractedMesh_Geometry
* 
* @DESCRIPTION
*    This interface is used by the existing tessellator instances (see MiTessellator)
*    to write into the geometry of the tessellated line, surface and volume meshes.
*    It is designed to allow the application to implement its own tessellator class.
*
*/
class MeWGeometryI : public MeXGeometryI
{
public:

  /** Add a new interpolated node computed by the tessellator and its associated 
  * parametric coordinate to the tessellated geometry. 
  * @param[in] coord  Node coordinate. 
  * @param[in] pcoord Parametric coordinate. 
  */
  virtual void addInterpolatedCoord(const MbVec3d& coord, const MbVec3d& pcoord) = 0;

  /**
  * Add an input node associated with its index in the input geometry.
  * @param[in] coord  Node coordinate. 
  * @param[in] nodeId Node id in the input mesh. 
  */
  virtual void addInputCoord(const MbVec3d& coord, size_t nodeId) = 0;

  /**
  * Add the center of a given cell.
  * @param[in] cell  Given cell. 
  * @param[in] geometry Geometry to used for center computation
  */
  virtual void addCellCenter(const MiCell* cell, const MiGeometryI& geometry) = 0;

  /**
  * Add the center of a facet in the given volume cell.
  * @param[in] cell  Given volume cell. 
  * @param[in] facetId Facet id in the given cell. 
  * @param[in] geometry Geometry used for coordinate computation
  */
  virtual void addFacetCenter(const MiVolumeCell* cell, size_t facetId, const MiGeometryI& geometry) = 0;

SoINTERNAL public:
  /** Add a new coordinate to the tessellated geometry */
  virtual void addCoord(const MbVec3d& coord) = 0;

  /** not yet used */
  virtual void resizeCoord(size_t size) = 0;
  /** not yet used */
  virtual void setCoord(size_t id, const MbVec3d& coord) = 0;


  /** Add a new parametric coordinate to the tessellated geometry */
  virtual void addPCoord(const MbVec3d& pcoord) = 0;

  /** not yet used */
  virtual void resizePCoord(size_t size) = 0;
  /** not yet used */
  virtual void setPCoord(size_t id, const MbVec3d& pcoord) = 0;

  /**
  * Add a new node id associated with the last coordinate 
  * and parametric coordinate added to the geometry.
  * @param[in] nodeId Node id in the input mesh. If nodeId == -1 
  * it means the last coord added is a point computed by the tessellator, so
  * it does not refer to a node of the input mesh.
  */
  virtual void addNodeId(size_t nodeId) = 0;

};

#endif

