/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Martial Bonaventure (Dec 2010)
**=======================================================================*/


#ifndef _MO_LINEDETAILIJ_
#define _MO_LINEDETAILIJ_

#include <MeshVizInterface/mapping/details/MoLineDetail.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: MoLineDetailIj
//
//  Detail information about vertex-based shapes made of line segments. It
//  adds indices of the input cell in a structured surface mesh. 
//
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Stores detail information about vertex-based shapes made of line segments
 * from structured surface meshes.
 * 
 * @ingroup MeshIViz_Mapping_Details
 * 
 * @DESCRIPTION
 *   This class contains detail information about a line segment in a
 *   vertex-based shape made of line segments (extends MoLineDetail).  
 *   Additional information includes the I/J indices of the cell containing the line segment
 *   in the structured surface mesh stored in the associated MoMeshDetail 
 *   (see MoLineDetail::getMeshDetail()).
 *  
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

class MESHIVIZDM_API MoLineDetailIj : public MoLineDetail {

  SO_DETAIL_HEADER(MoLineDetailIj);

 public:
  /**
   * Constructor.
   */
  MoLineDetailIj();
  /**
   * Destructor.
   */
  virtual ~MoLineDetailIj();

  //@{
  /**
  * Returns the index of the cell containing the face within the input mesh.
  */
  size_t                      getCellIndexI() const    { return m_cellIndexI; }
  size_t                      getCellIndexJ() const    { return m_cellIndexJ; }
  //@}

  // Returns an instance that is a copy of this instance. The caller
  // is responsible for deleting the copy when done.
  virtual MoLineDetailIj *      copy() const;

 SoEXTENDER public:
  // Copies the given details
  MoLineDetailIj(const MoLineDetail* lineDetail, const MoMeshDetail* meshDetail);

 SoINTERNAL public:
  static void                 initClass();
  static void                 exitClass();

 private:
  size_t                      m_cellIndexI;
  size_t                      m_cellIndexJ;

};

#endif /* _MO_LINEDETAILIJ_ */

