/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MO_MESHVECTORS_
#define  _MO_MESHVECTORS_

#include <MeshVizInterface/MbVec3.h>

#include <MeshVizInterface/mapping/nodes/MoMeshRepresentation.h>

#include <Inventor/fields/SoMFFloat.h>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

class MiLineMeshUnstructured;
class MiLineMeshCurvilinear;
class MiLineMeshRegular;
class MiVolumeMeshUnstructured;
class MiVolumeMeshUnstructuredIjk;
class MiVolumeMeshRegular;
class MiVolumeMeshRectilinear;
class MiVolumeMeshCurvilinear;
class MiCellFilter;
class MiCellFilterI;
class SoLineSet;
class SoVertexProperty;
class MiGeometryI;
class MxIndexDataSetI;

/**
 * @DTEXT  Rendering node that displays a vector data set.
 * 
 * @ingroup MeshIViz_Mapping_Representation
 * 
 * @DESCRIPTION
 *  Each value of the vector data set is represented by a line plus an (optional) small arrow.
 *  The lines are located at the cell centers for per cell data sets or at the node positions
 *  for per node data sets. 
 *  The vectorSetId field defines the index of the vector set to display. This is an index 
 *  into the list of vector sets existing in the traversal state (see the MoVec3Setxxx nodes).
 *
 *  The lines can be colored using a scalar set defined in the colorScalarSetId inherited field.
 *  This is an index into the list of scalar sets existing in the traversal state
 *  (see the MoScalarSetxxx nodes). To disable coloring set this field to -1.
 *
 * @FILE_FORMAT_DEFAULT
 *    MeshVector {
 *    @TABLE_FILE_FORMAT
 *       @TR colorScalarSetId           @TD 0
 *       @TR vectorSetId                @TD 0
 *       @TR scaleFactor                @TD 1.0
 *       @TR arrow                      @TD true
 *    @TABLE_END
 *    }
 * 
 */

class MESHIVIZDM_API MoMeshVector : public MoMeshRepresentation {

  SO_NODE_HEADER(MoMeshVector) ;

 public:

  /**
   * Constructor.
   */
  MoMeshVector() ;

  /**
  * Specifies the vector set to display.
  * During traversal of the scene graph, vector sets are accumulated in a list of vector sets.
  * vectorSetId is an index in this list. Default is 0 meaning the first set in the list.
  * @note  This vector set must be defined per node to be valid. 
   */
  SoSFInt32  vectorSetId;

  /**
  * The scale factor to apply to the vector field to resize the representation.  
  * Default is 1.0.
  */
  SoSFFloat  scaleFactor;

  /**
  * Do not draw arrows on vectors if set to false. 
  * Default is true.
  */
  SoSFBool   arrow;

  /*----------------------------------------------------------------------------*/
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 SoEXTENDER public:
  virtual void doExtract(SoAction * action);

  // Does not create any new mesh so return NULL
  virtual const MiMesh* getExtractedMesh(MeshType& UNREF_PARAM(meshType)) { return NULL;}

 protected:
  virtual ~MoMeshVector() ;  

  void clear();
  
  void doExtract(SoState* state, const MiMeshUnstructuredI& realMesh);

  template < typename _adaptorT, typename _MeshIjT>
  void doExtractSurfaceIj(SoState* state, _MeshIjT& realMesh);

  template < typename _adaptorT, typename _MeshIjkT>
  void doExtractVolumeIjk(SoState* state, _MeshIjkT& realMesh);

  void buildVectors(SoState* state, const MiMeshUnstructuredI& uMesh, const MiVec3dSetI& vec3, 
                    const MiScalardSetI* colorSet, const MiCellFilterI* filter=NULL);

  bool initLineSet(size_t numVectors, SoLineSet*& ls, SoVertexProperty*& vp);
  void fillLineSet(SoLineSet*& ls, SoVertexProperty*& vp, MxIndexDataSetI& extract, const MiGeometryI& geom, const MiVec3dSetI& vec3);
  void fillShapeSet(SoLineSet*& ls, SoVertexProperty*& vp, MxIndexDataSetI& extract, const MiGeometryI& geom, const MiVec3dSetI& vec3);
  void fillColors(SoState* state, SoLineSet* fs, SoVertexProperty* vp, MxIndexDataSetI& extract, const MiScalardSetI* colorSet);
  bool haveValuesChanged(size_t topoTimeStamp, size_t geoTimeStamp, size_t vec3TimeStamp, 
                         SoState* state, const MiDataSet* colorSet, const MiCellFilter* filter=NULL);

  size_t m_topoTimeStamp;
  size_t m_geoTimeStamp;
  size_t m_vec3TimeStamp;
  size_t m_colorTimeStamp;
  size_t m_colorMapTimeStamp;
  size_t m_cellFilterTimeStamp;
  float m_scaleFactor;
  bool  m_arrow;

  size_t m_numPointVec;

  MxIndexDataSetI* m_extract;

  bool m_cleared;

} ;

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /* _MO_MESHVECTORS_ */



