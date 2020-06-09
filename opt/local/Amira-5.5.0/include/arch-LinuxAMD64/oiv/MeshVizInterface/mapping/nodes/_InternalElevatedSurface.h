#ifndef HIDDEN_FROM_DOC

/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

/*=======================================================================

***********************INTERNAL USE ONLY*********************************

*********************** DO NOT USE **************************************

**=======================================================================*/

#ifndef  _MO_MESHELEVATEDSURFACE_
#define  _MO_MESHELEVATEDSURFACE_

#include <MeshVizInterface/MbVec3.h>

#include <MeshVizInterface/mapping/nodes/MoMeshSurface.h>

#include <Inventor/fields/SoSFDouble.h>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

class MiSurfaceMeshUnstructured;
class MoSurfaceMesh;
class MxElevatedSurfaceExtractUnstructured;

/**
 * @DTEXT  INTERNAL USE ONLY, Rendering node that displays an elevated surface on a surface mesh.
 * 
 * @ingroup MeshIViz_Mapping_Representation
 * 
 * @DESCRIPTION
 *  An elevated surface is based on an unstructured surface mesh . This surface is extruded 
 *  with a height depending on the data from the surface using the elevation scalar set, 
 *  and a scale factor.
 *
 *  The surface can be colored using a scalar set defined in the colorScalarSetId inherited field.
 *  This is an index into the list of scalar sets existing in the traversal state
 *  (see the MoScalarSetxxx nodes). To disable coloring set this field to -1.
 *  Rendering can be modified using various property nodes (see the SEE ALSO section).
 *
 * @FILE_FORMAT_DEFAULT
 *    MeshElevatedPlaneSlice {
 *    @TABLE_FILE_FORMAT
 *       @TR colorScalarSetId           @TD 0
 *       @TR elevationScalarSetId       @TD 0
 *       @TR elevationFactor            @TD 1.0
 *       @TR parallel                   @TD TRUE
 *    @TABLE_END
 *    }
 *
 * @SEE_ALSO
 *  MoCellFilter, MoColorMapping, MoDrawStyle, MoMaterial
 * 
 */

class MESHIVIZDM_API MoMeshElevatedSurface : public MoMeshSurface {

  SO_NODE_HEADER( MoMeshElevatedSurface ) ;

 public:

  /**
   * Constructor.
   */
  MoMeshElevatedSurface() ;

  /**
   * The elevationFactor can be set to control the height of extruded cells.
   * By default, this value is set to 1.
   */
  SoSFDouble elevationFactor;

  /**
   * The scalar set to be used to map elevation onto the representation. @BR
   * During traversal of the scene graph, scalar set nodes are accumulated in a list of scalar sets.
   * elevationScalarSetId is an index into this list.
   * Default value is 0 which means that the first scalar set stored in the scene graph is used.
   * Setting this value to -1 enables the elevation values to be the same as used for color mapping.
   * Setting this value to another id enables the elevation values to be different than the ones used
   * for color mapping.
   */
  SoSFInt32 elevationScalarSetId;

  /*----------------------------------------------------------------------------*/
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  virtual ~MoMeshElevatedSurface();

  virtual void clear();

  virtual void transformSurface( const MiSurfaceMeshUnstructured*& mesh, const MiScalardSetI*& colorSet, 
                                 SoState* state );

  // Elevated surface extractor
  MxElevatedSurfaceExtractUnstructured* m_elevator;

} ;

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /* _MO_MESHELEVATEDSURFACE_ */

#endif //HIDDEN_FROM_DOC



