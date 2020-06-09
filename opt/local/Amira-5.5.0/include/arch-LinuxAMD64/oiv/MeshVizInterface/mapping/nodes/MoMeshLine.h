/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MO_MESHLINE_
#define  _MO_MESHLINE_

#include <MeshVizInterface/mapping/nodes/MoMeshRepresentation.h>

class MiTessellatedLineExtract;

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif


/**
 * @DTEXT  Rendering node that displays a line mesh.
 * 
 * @ingroup MeshIViz_Mapping_Representation
 * 
 * @DESCRIPTION
 *    This class just gets the MoMesh node from the scene graph and creates an MoLineMesh node to display it.
 *    The MoMesh stored in the scene graph must be a line mesh.
 *
 *  @note It only performs an extraction for quadratic meshes and in this case, a MoTessellator must be set 
 *        in the scenegraph for proper rendering.
 *
 *    The line mesh can be colored using a scalar set defined in the colorScalarSetId inherited field.
 *    This is an index into the list of scalar sets existing in the traversal state
 *    (see the MoScalarSetxxx nodes). To disable coloring set this field to -1.
 *
 * @FILE_FORMAT_DEFAULT
 *    MeshLine {
 *    @TABLE_FILE_FORMAT
 *       @TR colorScalarSetId           @TD 0
 *       @TR parallel                   @TD TRUE
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *  MoMesh, MoTessellator,
 *  MoLineMesh
 *
 */

class MESHIVIZDM_API MoMeshLine : public MoMeshRepresentation {

  SO_NODE_HEADER(MoMeshLine) ;

 public:

  /**
   * Constructor.
   */
  MoMeshLine() ;

  /**
   * No extraction in this node so always returns NULL.
   */
  virtual const MiMesh* getExtractedMesh(MeshType& UNREF_PARAM(meshType)) { return NULL; };

  /*----------------------------------------------------------------------------*/
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 SoEXTENDER public:
  virtual void doExtract(SoAction *action);

 protected:
  virtual ~MoMeshLine() ;  

  void clear();

  template<typename _MeshInterface>
  void doExtract(SoState * state,const _MeshInterface* mesh);

  MiTessellatedLineExtract* m_tessellatorExtract;

  template<typename _MeshInterface, typename _ScalarSet>
  void display(const _MeshInterface* mesh, const _ScalarSet* colorSet);
  
} ;

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /* _MO_MESHLINE_ */



