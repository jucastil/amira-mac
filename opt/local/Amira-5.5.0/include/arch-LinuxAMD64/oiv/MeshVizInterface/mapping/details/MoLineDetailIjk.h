/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Martial Bonaventure (Dec 2010)
**=======================================================================*/


#ifndef _MO_LINeDETAILIJK_
#define _MO_LINEDETAILIJK_

#include <MeshVizInterface/mapping/details/MoLineDetail.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: MoLineDetailIjk
//
//  Detail information about vertex-based shapes made of line segments. It
//  adds indices of the input cell in a structured volume mesh. 
//
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Stores detail information about vertex-based shapes made of line segments 
 * from structured volume meshes.
 * 
 * @ingroup MeshIViz_Mapping_Details
 * 
 * @DESCRIPTION
 *   This class contains detail information about a line segment in a
 *   vertex-based shape made of line segments (extends MoLineDetail).  
 *   Additional information includes the I/J/K indices of the cell containing the line segment
 *   in the structured volume mesh stored in the associated MoMeshDetail 
 *   (see MoLineDetail::getMeshDetail()).
 *  
 * 
 * @SEE_ALSO
 *    MoLineDetail,
 *    MoMeshDetail,
 *    MoSurfaceMeshDetail,
 *    SoPickedPoint,
 *    SoPrimitiveVertex,
 *    SoVertexShape
 * 
 */ 

class MESHIVIZDM_API MoLineDetailIjk : public MoLineDetail {

  SO_DETAIL_HEADER(MoLineDetailIjk);

 public:
  /**
   * Constructor.
   */
  MoLineDetailIjk();
  /**
   * Destructor.
   */
  virtual ~MoLineDetailIjk();

  //@{
  /**
  * Returns the index I/J/K of the cell containing the face within the input mesh.
  */
  size_t                      getCellIndexI() const    { return m_cellIndexI; }
  size_t                      getCellIndexJ() const    { return m_cellIndexJ; }
  size_t                      getCellIndexK() const    { return m_cellIndexK; }
  //@}

  // Returns an instance that is a copy of this instance. The caller
  // is responsible for deleting the copy when done.
  virtual MoLineDetailIjk *   copy() const;

 SoEXTENDER public:
  // Copies the given details
  MoLineDetailIjk(const MoLineDetail* lineDetail, const MoMeshDetail* meshDetail);

 SoINTERNAL public:
  static void                 initClass();
  static void                 exitClass();

 private:
  size_t                      m_cellIndexI;
  size_t                      m_cellIndexJ;
  size_t                      m_cellIndexK;

};

#endif /* _MO_LINEDETAILIJK_ */

