/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Martial Bonaventure (Dec 2010)
**=======================================================================*/


#ifndef _MO_LINEDETAILI_
#define _MO_LINEDETAILI_

#include <MeshVizInterface/mapping/details/MoLineDetail.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: MoLineDetailI
//
//  Detail information about vertex-based shapes made of line
//  segments. It adds the index of the input cell of unstructured meshes and 
//  structured line meshes 
//
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Stores detail information about vertex-based shapes made of line segments
 * from unstructured meshes and structured line meshes 
 * 
 * @ingroup MeshIViz_Mapping_Details
 * 
 * @DESCRIPTION
 *   This class contains detail information about a line segment in a
 *   vertex-based shape made of line segments (extends MoLineDetail). 
 *   Additional information includes the index of the cell containing the line in the
 *   mesh stored in the associated MoMeshDetail (see MoLineDetail::getMeshDetail()).
 * 
 * @SEE_ALSO
 *    SoDetail,
 *    MoLineDetail,
 *    MoMeshDetail,
 *    MoSurfaceMeshDetail,
 *    SoPickedPoint,
 *    SoPrimitiveVertex,
 *    SoVertexShape
 * 
 */ 

class MESHIVIZDM_API MoLineDetailI : public MoLineDetail {

  SO_DETAIL_HEADER(MoLineDetailI);

 public:
  /**
   * Constructor.
   */
  MoLineDetailI();
  /**
   * Destructor.
   */
  virtual ~MoLineDetailI();

  /**
  * Returns the index of the cell containing the face within the input mesh.
  */
  size_t                      getCellIndex() const    { return m_cellIndex; }

  // Returns an instance that is a copy of this instance. The caller
  // is responsible for deleting the copy when done.
  virtual MoLineDetailI *      copy() const;

 SoEXTENDER public:
  // Copies the given details
  MoLineDetailI(const MoLineDetail* lineDetail, const MoMeshDetail* meshDetail);

 SoINTERNAL public:
  static void                 initClass();
  static void                 exitClass();

 private:
  size_t                      m_cellIndex;

};

#endif /* _MO_LINEDETAILI_ */

