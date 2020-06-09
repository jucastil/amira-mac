/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Martial Bonaventure (Nov 2010)
**=======================================================================*/


#ifndef _MO_LINEDETAIL_
#define _MO_LINEDETAIL_

#include <Inventor/details/SoLineDetail.h>
#include <MeshVizInterface/MbVec3.h>
#include <MeshVizInterface/mapping/MoMeshVizDataMapping.h>

#include <MeshVizInterface/mapping/details/MoMeshDetail.h>
#include <MeshVizInterface/mapping/details/MoLineMeshDetail.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: MoLineDetail
//
//  Detail information about vertex-based shapes made of line
//  segments. It adds indices of various items that vary among lines, vertices
//  and cell id 
//
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Stores detail information about vertex-based shapes made of line segments.
 * 
 * @ingroup MeshIViz_Mapping_Details
 * 
 * @DESCRIPTION
 *   This class contains detail information about a line segment in a
 *   vertex-based shape made of line segments (extends SoLineDetail).  Additional
 *   information includes the input mesh and the mesh representation details. 
 *   It also allows computing the value of the mapped scalarset used for coloring 
 *   at any points along the line segment.
 *
 *   Detail objects are returned by the SoPickedPoint class after picking.
 * 
 * @SEE_ALSO
 *    SoDetail,
 *    SoPickedPoint,
 *    SoLineDetail,
 *    MoMeshDetail,
 *    MoLineMeshDetail,
 *    SoPickedPoint,
 *    SoPrimitiveVertex,
 *    SoVertexShape
 * 
 */ 

class MeXTopologyI;

class MESHIVIZDM_API MoLineDetail : public SoLineDetail {

  SO_DETAIL_HEADER(MoLineDetail);

 public:
  /**
   * Constructor.
   */
  MoLineDetail();
  /**
   * Destructor.
   */
  virtual ~MoLineDetail();

  /**
  * Computes and returns the value of the mapped scalarset at the given point. 
  * Returns DBL_MAX if point not along the line or no mapped scalarset available.
  */
  double                      getValue(const SbVec3f& point) const;

  /**
  * Returns information about the input mesh containing the cell that the line belongs to,
  * represented as a MoMeshDetail.
  */
  const MoMeshDetail*         getMeshDetail() const   { return &m_meshDetail; }

  /**
  * Returns information about the mesh representation (outline, clipline, ...) containing the line,
  * represented as an MoLineMeshDetail, if available, returns NULL otherwise.
  */
  const MoLineMeshDetail*     getMeshRepresentationDetail() const { return m_repDetail; }

  // Returns an instance that is a copy of this instance. The caller
  // is responsible for deleting the copy when done.
  virtual MoLineDetail *      copy() const;

 SoEXTENDER public:
  // Copies the given details
  MoLineDetail(const SoLineDetail* lineDetail, const MoLineMeshDetail* lineMeshDetail, const std::vector<size_t>* lineMapping = NULL);
  // Copy constructore
  MoLineDetail(const MoLineDetail& lineDetail);
  // Assignment operator
  MoLineDetail& operator=(const MoLineDetail& lineDetail);
  
 SoINTERNAL public:
  static void                 initClass();
  static void                 exitClass();

 protected:
  MoMeshDetail                m_meshDetail;
  MoLineMeshDetail*           m_repDetail;

  size_t getExtractedCellIndex() const { return m_extractedCellIndex; }

 private:
  size_t                      m_extractedCellIndex;

};

#endif /* _MO_LINEDETAIL_ */

