/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Martial Bonaventure (Dec 2010)
**=======================================================================*/


#ifndef _MO_FACEDETAILI_
#define _MO_FACEDETAILI_

#include <MeshVizInterface/mapping/details/MoFaceDetail.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: MoFaceDetailI
//
//  Detail information about vertex-based shapes made of faces. It
//  adds the index of the input cell of unstructured meshes and 
//  structured line meshes 
//
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Stores detail information about vertex-based shapes made of faces from 
 * unstructured meshes and structured line meshes.
 * 
 * @ingroup MeshIViz_Mapping_Details
 * 
 * @DESCRIPTION
 *   This class contains detail information about a face in a vertex-based
 *   shape made of faces (extends MoFaceDetail). Additional information includes
 *   the index of the cell that contains this face in the mesh stored in the associated 
 *   MoMeshDetail (see MoFaceDetail::getMeshDetail()).
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

class MESHIVIZDM_API MoFaceDetailI : public MoFaceDetail {

  SO_DETAIL_HEADER(MoFaceDetailI);

 public:
  /**
   * Constructor.
   */
  MoFaceDetailI();
  /**
   * Destructor.
   */
  virtual ~MoFaceDetailI();

  /**
  * Returns the index of the cell containing the face within the input mesh.
  */
  size_t                      getCellIndex() const    { return m_cellIndex; }

  // Returns an instance that is a copy of this instance. The caller
  // is responsible for deleting the copy when done.
  virtual MoFaceDetailI *      copy() const;

 SoEXTENDER public:
  // Copies the given details
  MoFaceDetailI(const MoFaceDetail* faceDetail, const MoMeshDetail* meshDetail);

 SoINTERNAL public:
  static void                 initClass();
  static void                 exitClass();

 private:
  size_t                      m_cellIndex;

};

#endif /* _MO_FACEDETAILI_ */

