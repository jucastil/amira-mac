/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
** Modified by : M. Bonaventure (Avr 2010)
**=======================================================================*/
#ifndef  _MO_MESHREPRESENTATION_
#define  _MO_MESHREPRESENTATION_

#include <MeshVizInterface/mapping/nodes/MoMeshBaseRepresentation.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <MeshVizInterface/mesh/data/MiDataSetI.h>
#include <MeshVizInterface/mesh/data/MiDataSetIj.h>
#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>
class MiMesh;
class MiExtractorCallback;
class MiTessellator;

class MoMeshDetail;

class SoRayPickAction;

class MxMeshCache;
class MxAttributesManager;

/**
 * @DTEXT  Abstract base class for all MeshViz Interface representation nodes containing an extractor.
 * 
 * @ingroup MeshIViz_Mapping_Representation
 * 
 * @DESCRIPTION
 *    Abstract base class for all MeshViz Interface representation nodes containing an extractor. 
 *
 *    The basic representations and the meshes they apply to are:
 *    - Volume mesh
 *      - MoMeshCellShape
 *      - MoMeshClipLine
 *      - MoMeshCylinderSlice
 *      - MoMeshGridPlaneSlice
 *      - MoMeshInterpolatedLogicalSlice
 *      - MoMeshIsosurface
 *      - MoMeshLogicalSlice
 *      - MoMeshOutline
 *      - MoMeshPlaneSlice
 *      - MoMeshSkin
 *      - MoMeshSphereSlice
 *      - MoMeshStreamline
 *      - MoMeshVector
 *    - Surface mesh
 *      - MoMeshAnnotatedIsoline
 *      - MoMeshCellShape
 *      - MoMeshIsoline
 *      - MoMeshOutline
 *      - MoMeshVector
 *    - Line mesh
 *      - MoMeshVector
 * 
 *   All surface representations, for instance MoMeshIsosurface and MoMeshSkin, are using an inner SoPolygonOffset node
 *   to allow line representations, such as MoMeshIsoline and MoMeshOutline, on top without artifacts.
 *   However SoPolygonOffset can introduce other artifacts on surfaces when the two-sided lighting mode is active.
 *   Thus, to disable this SoPolygonOffset node, set the MESHVIZ_POLYGON_OFFSET environment variable to false (See SoPreferences).
 */

class MESHIVIZDM_API MoMeshRepresentation : public MoMeshBaseRepresentation {

  SO_NODE_HEADER(MoMeshRepresentation) ;

 public:

  /**
  * Field representing the scalar set node to be used to map colors onto the representation.
  * During traversal of the scene graph, scalar set nodes are accumulated in a list of scalar sets.
  * colorScalarSetId is an index into this list. 
  * Default value is 0 which means that the first scalar set stored in the scene graph is used.
  * Setting this value to -1 disables color mapping 
  */
  SoSFInt32 colorScalarSetId;

  /**
  * If TRUE, the node tries to launch the extraction in parallel if this is supported by the associated extractor.
  * Extractions performed in parallel use multiple cores and/or processors to compute the extraction.
  * Default is TRUE.
  */
  SoSFBool parallel;

  /**
  * Set the extraction callback which will be called each time an extraction is performed
  */
  virtual void setExtractorCallback(MiExtractorCallback& extractorCallback);

  /*----------------------------------------------------------------------------*/
 SoINTERNAL public:
  /**
  * Field representing the scalar set node to be used to map colors onto the representation.
  * When set, overrides the value set into colorScalarSetId  
  */
  SoSFNode colorScalarSet;

  static void initClass() ;
	static void exitClass() ;

  size_t getTimeStamp() const;

  /**
  * Return true if the extractor is currently using a Tessellator
  */
  bool isUsingTessellator() const;

 SoEXTENDER public:
  virtual void rayPick(SoRayPickAction *action);
  virtual void doExtract(SoAction *action) = 0;
  virtual void doAction(SoAction *action);

  // pure virtual method used to return the extracted mesh computed by the representation used by MoMesh::connectFrom()
  virtual const MiMesh* getExtractedMesh(MeshType& meshType) = 0;

  // computes the extract of the data set corresponding to the given index in the state list from the current representation's extractor.
  virtual const MiScalardSetI* extractScalarSetI(SoState * UNREF_PARAM(state),size_t UNREF_PARAM(scalarSetId)) {return NULL;};
  virtual const MiScalardSetIj* extractScalarSetIj(SoState * UNREF_PARAM(state),size_t UNREF_PARAM(scalarSetId)) {return NULL;};

  // computes the extract of the data set corresponding to the given index in the state list from the current representation's extractor.
  virtual const MiVec3dSetI* extractVec3SetI(SoState * UNREF_PARAM(state),size_t UNREF_PARAM(vec3SetId)) {return NULL;};
  virtual const MiVec3dSetIj* extractVec3SetIj(SoState * UNREF_PARAM(state),size_t UNREF_PARAM(vec3SetId)) {return NULL;};

 protected:
  MoMeshRepresentation() ;
  virtual ~MoMeshRepresentation() ;  

  const MiMesh* getMeshFromState(SoState* state, MeshType& meshType);
  MiTessellator* getTessellatorFromState(SoState* state, bool ignoreCache = false);
  template <typename _ScalarSetT>
  const _ScalarSetT* getColorScalarSetFromState(SoState* state);

  virtual void clear();

  MiExtractorCallback* m_extractorCallback;

private:
  // Parallel field sensor
  SoFieldSensor m_parallelFieldSensor;
  static void parallelFieldSensorCB(void* data, SoSensor* sensor);
  // detail storing the current mesh and the color scalarset
  MoMeshDetail* m_meshDetail;
  // Internal mechanism to retrieve the attributes for the extractions
  MxAttributesManager* m_attributesManager;
  // time stamp is updated when creating a new the representation meshcache 
  size_t m_timeStamp;
  // set to true if the extractor is currentlty using a Tessellator
  bool m_usingTessellator;
};

#endif /* _MO_MESHREPRESENTATION_ */



