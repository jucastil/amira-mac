/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Martial Bonaventure (Dec 2010)
**=======================================================================*/


#ifndef _MO_FACEDETAILIJK_
#define _MO_FACEDETAILIJK_

#include <MeshVizInterface/mapping/details/MoFaceDetail.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: MoFaceDetailIjk
//
//  Detail information about vertex-based shapes made of faces. It
//  adds indices of the input cell in a structured volume mesh. 
//
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Stores detail information about vertex-based shapes made of faces from 
 * a structured volume mesh.
 * 
 * @ingroup MeshIViz_Mapping_Details
 * 
 * @DESCRIPTION
 *   This class contains detail information about a face in a vertex-based
 *   shape made of faces (extends MoFaceDetail). Additional information includes
 *   the I/J/K indices of the cell that contains this face in the structured volume 
 *   mesh stored in the associated MoMeshDetail (see MoFaceDetail::getMeshDetail()).
 *  
 * 
 * @SEE_ALSO
 *    MoFaceDetail,
 *    MoMeshDetail,
 *    MoSurfaceMeshDetail,
 *    SoPickedPoint,
 *    SoPrimitiveVertex,
 *    SoVertexShape
 * 
 */ 

class MESHIVIZDM_API MoFaceDetailIjk : public MoFaceDetail {

  SO_DETAIL_HEADER(MoFaceDetailIjk);

 public:
  /**
   * Constructor.
   */
  MoFaceDetailIjk();
  /**
   * Destructor.
   */
  virtual ~MoFaceDetailIjk();

  //@{
  /**
  * Returns the I/J/K indices of the cell containing the face within the input mesh.
  */
  size_t                      getCellIndexI() const    { return m_cellIndexI; }
  size_t                      getCellIndexJ() const    { return m_cellIndexJ; }
  size_t                      getCellIndexK() const    { return m_cellIndexK; }
  //@}

  // Returns an instance that is a copy of this instance. The caller
  // is responsible for deleting the copy when done.
  virtual MoFaceDetailIjk *   copy() const;

 SoEXTENDER public:
  // Copies the given details
  MoFaceDetailIjk(const MoFaceDetail* faceDetail, const MoMeshDetail* meshDetail);

 SoINTERNAL public:
  static void                 initClass();
  static void                 exitClass();

 private:
  size_t                      m_cellIndexI;
  size_t                      m_cellIndexJ;
  size_t                      m_cellIndexK;

};

#endif /* _MO_FACEDETAILIJK_ */

