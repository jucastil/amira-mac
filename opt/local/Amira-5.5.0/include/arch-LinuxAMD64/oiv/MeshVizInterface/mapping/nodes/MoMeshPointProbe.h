/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Martial Bonaventure (October 2009)
**=======================================================================*/
#ifndef  _MoMeshPointProbe_H
#define  _MoMeshPointProbe_H

#include <MeshVizInterface/mapping/nodes/MoActionNode.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>

#include <Inventor/fields/SoMFInt32.h>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

class MiPointProbeUnstructured;
class MiPointProbeUnstructuredIjk;
class MiPointProbeIjk;
class MiPointProbeIj;
class MxNodeSensor;
class MxProbeCallback;
class MxAttributesManager;
class MiMesh;

/**
 * @DTEXT  Action node that probes cells of a mesh
 * 
 * @ingroup MeshIViz_Mapping_Action
 * 
 * @DESCRIPTION
 *  This node retrieves information at a given position in a mesh and
 *  triggers a callback each time the position moves.
 *
 *  The callback is defined by calling the method setProbeCallback().
 *    
 *  The information available in the callback are the cellId, the scalars
 *  and vectors interpolated at the probe location. The scalar and
 *  vector values are computed from the scalar sets and vector sets defined by
 *  the scalarSetIds and vectorSetIds fields.
 *  These are indices into the list of scalar sets and vector sets existing
 *  in the traversal state (see the MoScalarSetxxx and MoVec3Setxxx nodes).
 *
 *  Set these fields to -1 to disable interpolating these data sets.
 *
 *  Probing can be optimized by setting environment variables (see the 
 *  MESHVIZ_OCTREE_ variables in SoPreferences).
 *
 *  Since Open Inventor version 8.5, using the probe tool should be limited to probing 
 *  inside a volume. Probing a mesh representation (skin, slice, etc) should now be done 
 *  using Open Inventor picking (see the getPickedPoint method in classes SoRayPickAction,
 *  SoEventCallback, etc) combined with the MoFaceDetail or MoLineDetail and their derived classes. 
 *
 * @FILE_FORMAT_DEFAULT
 *    MoMeshPointProbe {
 *    @TABLE_FILE_FORMAT
 *       @TR position                   @TD 0,0,0
 *       @TR scalarSetIds               @TD 0
 *       @TR vectorSetIds               @TD 0
 *    @TABLE_END
 *    }
 *
 * @SEE_ALSO
 *   MiPointProbeUnstructured, MiPointProbeUnstructuredIjk,
 *   MiPointProbeIjk, MiPointProbeIj.
 * 
 */

class MESHIVIZDM_API MoMeshPointProbe : public MoActionNode 
{

  SO_NODE_HEADER(MoMeshPointProbe) ;

 public:

  /**
   * Constructor.
   */
  MoMeshPointProbe() ;

  /**
  * Field representing the position of the probe.@n
  */
  SoSFVec3f position;

  /**
  * Field representing the scalar set nodes to use when probing at the current position.
  * During traversal of the scene graph, scalar set nodes are accumulated in a list of scalar sets.
  * scalarSetIds are indices into this list. 
  * Default value is 0 which means that only the first scalar set stored in the scene graph is used.
  * Setting this value to -1 disables the probing on scalar sets.
  */
  SoMFInt32 scalarSetIds;

  /**
  * Field representing the vector set nodes to use when probing at the current position.
  * During traversal of the scene graph, vector set nodes are accumulated in a list of vector sets.
  * vectorSetIds are indices into this list. 
  * Default value is 0 which means that only the first vector set stored in the scene graph is used.
  * Setting this value to -1 disables the probing on vector sets.
  */
  SoMFInt32 vectorSetIds;

  /**
  * This class specifies the interface used by this node to notify the application
  * when the {@link MoMeshPointProbe::position position} of the probe is updated.
  * A derived class must implement at least one of the event method motionCallback depending
  * on the type of mesh.
  */
  class MoProbeCallback
  {
  public:
    //@{
    /**
    * Callback that is triggered each time the field MoMeshPointProbe::position changes.
    * 
    * @param [in] cellId(I/J/K) is the index of cell in which the probe is located.
    * @param [in] scalars is a set of probed scalar values from the selected scalar sets at the current position.
    *             The number of scalar values corresponds to the number of indices in scalarSetIds. The ith value in
    *             scalars is associated with the ith index in scalarSetIds.
    * @param [in] vectors is a set of probed vectors from the selected vector sets at the current position.
    *             The number of vectors corresponds to the number of indices in vectorSetIds. The ith element in
    *             vectors is associated with the ith index in vectorSetIds.
    * @note cellId(I/J/K) is set to -1 when the probe is outside the mesh and the scalar and vector sets are empty.
    */
    virtual void motionCallback(size_t UNREF_PARAM(cellId), const MeXScalardSetI& UNREF_PARAM(scalars), const MeXVec3dSetI& UNREF_PARAM(vectors)) {}
    virtual void motionCallback(size_t UNREF_PARAM(cellIdI), size_t UNREF_PARAM(cellIdJ), 
                                const MeXScalardSetI& UNREF_PARAM(scalars), const MeXVec3dSetI& UNREF_PARAM(vectors)) {}
    virtual void motionCallback(size_t UNREF_PARAM(cellIdI), size_t UNREF_PARAM(cellIdJ), size_t UNREF_PARAM(cellIdK), 
                                const MeXScalardSetI& UNREF_PARAM(scalars), const MeXVec3dSetI& UNREF_PARAM(vectors)) {}
    //@}
  };
  
  /**
  * Set the user defined probe callback which will be called when the motion event occurs.
  * If no callback set, the node is not activated (see also removeProbeCallback()).
  */
  void setProbeCallback(MoProbeCallback& probeCallback);

  /**
  * remove the user defined probe callback (see setProbeCallback()) which will disable 
  * the node.
  */
  void removeProbeCallback();

  //@{
  /** 
  * Get probes for reuse outside this node. 
  * @note The returned pointer may be null if a mesh has not been set in the scene graph 
  * or if no probing action has traversed the scene graph. 
  * Use the method corresponding to the type of mesh stored in the scene graph. 
  * 
  */
  const MiPointProbeUnstructured*     getPointProbeUnstructured();
  const MiPointProbeUnstructuredIjk*  getPointProbeUnstructuredIjk();
  const MiPointProbeIjk*              getPointProbeIjk();
  const MiPointProbeIj*               getPointProbeIj();
  //@}


  /*----------------------------------------------------------------------------*/
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 SoEXTENDER public:
  virtual void doAction(SoAction *action);

protected:
  virtual ~MoMeshPointProbe() ;  

private:
  void clear();

  template<typename _ScalarSet, typename _VectorSet, typename _MeshInterface, typename _Probe>
  void doProbing(SoState * state,const _MeshInterface* mesh, _Probe** probe);

  template<typename _Probe, typename _ScalarSet, typename _VectorSet>
  void probeAtPosition(SoState * state,_Probe* probe, std::vector<const _ScalarSet*>& sSets, 
                       std::vector<const _VectorSet*>& vSets);

  const MiMesh* getMeshFromState(SoState* state, MeshType& meshType);

  // Probes used internally
  MiPointProbeUnstructured*    m_pointProbeU;
  MiPointProbeUnstructuredIjk* m_pointProbeUIjk;
  MiPointProbeIjk*             m_pointProbeIjk;
  MiPointProbeIj*              m_pointProbeIj;

  // Internal mechanism used to detect that the node has changed.
  MxNodeSensor* m_sensor;

  // Internal mechanism to retrieve the attributes for the extraction
  MxAttributesManager* m_attributesManager;

  // call back
  MxProbeCallback* m_probeCallback;

} ;

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /* _MoMeshPointProbe_H */



