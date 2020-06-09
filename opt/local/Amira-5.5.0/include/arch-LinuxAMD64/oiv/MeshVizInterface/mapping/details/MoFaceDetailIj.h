/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Martial Bonaventure (Dec 2010)
**=======================================================================*/


#ifndef _MO_FACEDETAILIJ_
#define _MO_FACEDETAILIJ_

#include <MeshVizInterface/mapping/details/MoFaceDetail.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: MoFaceDetailIj
//
//  Detail information about vertex-based shapes made of faces. It
//  adds indices of the input cell in a structured surface mesh. 
//
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Stores detail information about vertex-based shapes made of faces from a 
 * structured surface mesh.
 * 
 * @ingroup MeshIViz_Mapping_Details
 * 
 * @DESCRIPTION
 *   This class contains detail information about a face in a vertex-based
 *   shape made of faces (extends MoFaceDetail). Additional information includes 
 *   the I/J indices of the cell that contains this face in the structured surface
 *   mesh stored in the associated MoMeshDetail (see MoFaceDetail::getMeshDetail()).
 *  
 * 
 * @SEE_ALSO
 *    SoDetail,
 *    MoFaceDetail,
 *    MoMeshDetail,
 *    MoSurfaceMeshDetail,
 *    SoPickedPoint,
 *    SoPrimitiveVertex,
 *    SoVertexShape
 * 
 */ 

class MESHIVIZDM_API MoFaceDetailIj : public MoFaceDetail {

  SO_DETAIL_HEADER(MoFaceDetailIj);

 public:
  /**
   * Constructor.
   */
  MoFaceDetailIj();
  /**
   * Destructor.
   */
  virtual ~MoFaceDetailIj();

  //@{
  /**
  * Returns the indices I/J of the cell containing the face within the input mesh.
  */
  size_t                      getCellIndexI() const    { return m_cellIndexI; }
  size_t                      getCellIndexJ() const    { return m_cellIndexJ; }
  //@}

  // Returns an instance that is a copy of this instance. The caller
  // is responsible for deleting the copy when done.
  virtual MoFaceDetailIj *      copy() const;

 SoEXTENDER public:
  // Copies the given details
  MoFaceDetailIj(const MoFaceDetail* faceDetail, const MoMeshDetail* meshDetail);

 SoINTERNAL public:
  static void                 initClass();
  static void                 exitClass();

 private:
  size_t                      m_cellIndexI;
  size_t                      m_cellIndexJ;

};

#endif /* _MO_FACEDETAILIJ_ */

