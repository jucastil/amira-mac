/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MO_MESHELEVATEDPLANESLICE_
#define  _MO_MESHELEVATEDPLANESLICE_

#include <MeshVizInterface/MbVec3.h>

#include <MeshVizInterface/mapping/nodes/MoMeshPlaneSlice.h>

#include <Inventor/fields/SoSFPlane.h>
#include <Inventor/fields/SoSFDouble.h>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

class MiPlaneSliceExtractUnstructured;
class MiPlaneSliceExtractUnstructuredIjk;
class MiPlaneSliceExtractIjk;
class MiVolumeMeshUnstructured;
class MiVolumeMeshUnstructuredIjk;
class MiVolumeMeshHexahedronIjk;
class MiVolumeMeshRegular;
class MiVolumeMeshRectilinear;
class MiVolumeMeshCurvilinear;
template <typename _T>
class MeSurfaceMeshUnstructured;
class MiTopologyExplicitI;
class MiGeometryI;
class MeXtractedGeometryI;
template <typename _T>
class MiDataSetI;
template <typename _T>
class MeXtractedScalarSetI;

/**
 * @DTEXT  Rendering node that displays an elevated plane slice of a volume mesh.
 * 
 * @ingroup MeshIViz_Mapping_Representation
 * 
 * @DESCRIPTION
 *  An elevated plane slice is based on an unstructured surface mesh defined by the intersection of 
 *  an arbitrary plane with a volume mesh. This surface is extruded with a height depending on
 *  the data extracted from the plane using the elevation scalar set, and a scale factor.
 *  The plane (an SbPlane) is defined by a direction vector and a distance from the origin.
 *
 *  The slice can be colored using a scalar set defined in the colorScalarSetId inherited field.
 *  This is an index into the list of scalar sets existing in the traversal state
 *  (see the MoScalarSetxxx nodes). To disable coloring set this field to -1.
 *  Rendering can be modified using various property nodes (see the SEE ALSO section).
 *
 * @FILE_FORMAT_DEFAULT
 *    MeshElevatedPlaneSlice {
 *    @TABLE_FILE_FORMAT
 *       @TR colorScalarSetId           @TD 0
 *       @TR elevationScalarSetId       @TD 0
 *       @TR scaleFactor                @TD 1.0
 *       @TR parallel                   @TD TRUE
 *       @TR plane                      @TD 0,0,1,0
 *    @TABLE_END
 *    }
 *
 * @SEE_ALSO
 *  MoCellFilter, MoColorMapping, MoDrawStyle, MoMaterial, @BR
 *  MiPlaneSliceExtractIjk,
 *  MiPlaneSliceExtractUnstructured,
 *  MiPlaneSliceExtractUnstructuredIjk
 * 
 */

class MESHIVIZDM_API MoMeshElevatedPlaneSlice : public MoMeshPlaneSlice {

  SO_NODE_HEADER( MoMeshElevatedPlaneSlice ) ;

 public:

  /**
   * Constructor.
   */
  MoMeshElevatedPlaneSlice() ;

  /**
   * The scaleFactor can be set to control the height of extruded cells.
   * By default, this value is set to 1.
   */
  SoSFDouble scaleFactor;

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

 SoEXTENDER public:
  virtual void doExtract( SoAction *action );

 protected:
  virtual ~MoMeshElevatedPlaneSlice() ;  

  template<typename _MeshInterface, typename _Extractor, typename _ScalarSet, typename _MoScalarSet, typename _CellFilter>
  void doExtract( SoState * state, const _MeshInterface* mesh, _Extractor** extractor );

  template<typename _Extractor, typename _ScalarSet, typename _MoScalarSet, typename _CellFilter>
  void extract( SoState * state, _Extractor* extractor, const _CellFilter *cellFilter );
} ;

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /* _MO_MESHELEVATEDPLANESLICE_ */



