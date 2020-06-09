/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Martial Bonaventure (Nov 2010)
**=======================================================================*/


#ifndef _MO_FACEDETAIL_
#define _MO_FACEDETAIL_

#include <Inventor/details/SoFaceDetail.h>
#include <MeshVizInterface/MbVec3.h>
#include <MeshVizInterface/mapping/MoMeshVizDataMapping.h>

#include <MeshVizInterface/mapping/details/MoMeshDetail.h>
#include <MeshVizInterface/mapping/details/MoSurfaceMeshDetail.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: MoFaceDetail
//
//  Detail information about vertex-based shapes made of faces. It
//  adds indices of various items that vary among faces, vertices and input cell 
//
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Stores detail information about vertex-based shapes made of faces.
 * 
 * @ingroup MeshIViz_Mapping_Details
 * 
 * @DESCRIPTION
 *   This class contains detail information about a face in a vertex-based
 *   shape made of faces (extends SoFaceDetail). Additional information includes the input mesh
 *   and mesh representation details. It also allows computing the value of the mapped scalarset
 *   used for coloring at any points in the face.
 *
 *   Detail objects are returned by the SoPickedPoint class after picking.
 * 
 * @SEE_ALSO
 *    SoDetail,
 *    SoFaceDetail,
 *    SoPickedPoint,
 *    MoMeshDetail,
 *    MoSurfaceMeshDetail,
 *    SoPickedPoint,
 *    SoPrimitiveVertex,
 *    SoVertexShape
 * 
 */ 

class MeXTopologyI;

class MESHIVIZDM_API MoFaceDetail : public SoFaceDetail {

  SO_DETAIL_HEADER(MoFaceDetail);

 public:
  /**
   * Constructor.
   */
  MoFaceDetail();
  /**
   * Destructor.
   */
  virtual ~MoFaceDetail();

  /**
  * Computes and returns the value of the mapped scalarset at the given point. 
  * Returns DBL_MAX if point not inside the face or no mapped scalarset available.
  */
  double                      getValue(const SbVec3f& point) const;

  /**
  * Returns information about the input mesh containing the cell that the face belongs to,
  * represented as a MoMeshDetail.
  */
  const MoMeshDetail*         getMeshDetail() const   { return &m_meshDetail; }

  /**
  * Returns information about the mesh representation (skin, isosurface...)
  * containing the face, represented as a MoSurfaceMeshDetail, if available, 
  * returns NULL otherwise.
  */
  const MoSurfaceMeshDetail*  getMeshRepresentationDetail() const   { return m_repDetail; }

  // Returns an instance that is a copy of this instance. The caller
  // is responsible for deleting the copy when done.
  virtual MoFaceDetail *      copy() const;

 SoEXTENDER public:
  // Copies the given details. Optional table to mapp the facet indices to 
  // the extracted surfaceCell which is mandatory when the extracted mesh contains deadcells
  MoFaceDetail(const SoFaceDetail* faceDetail, const MoSurfaceMeshDetail* surfMeshDetail, const std::vector<size_t>* facetMapping = NULL);
  // Copy constructor
  MoFaceDetail(const MoFaceDetail& faceDetail);
  // Assignment operator
  MoFaceDetail& operator=(const MoFaceDetail& faceDetail);

 SoINTERNAL public:
  static void                 initClass();
  static void                 exitClass();

 protected:
  MoMeshDetail                m_meshDetail;
  MoSurfaceMeshDetail*        m_repDetail;

  size_t getExtractedCellIndex() const { return m_extractedCellIndex; }

 private:
  size_t                      m_extractedCellIndex;

};

#endif /* _MO_FACEDETAIL_ */

