/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Martial Bonaventure (Dec 2010)
**=======================================================================*/


#ifndef _MO_LINEMESHDETAIL_
#define _MO_LINEMESHDETAIL_

#include <MeshVizInterface/mapping/details/MoMeshRepresentationDetail.h>

#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: MoLineMeshDetail
//
//  Detail information about a mesh representation defined by a line.
//
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Stores detail information about a mesh representation defined by a line.
 * 
 * @ingroup MeshIViz_Mapping_Details
 * 
 * @DESCRIPTION
 *   This class contains detail information about a mesh representation defined by a
 *   line. It includes the extracted line. 
 * 
 * @SEE_ALSO
 *    SoDetail,
 *    MoMeshRepresentationDetail
 *    MoLineDetail,
 *    MeXLineMeshUnstructured,
 * 
 */ 

class MeXLineMeshUnstructured;

class MESHIVIZDM_API MoLineMeshDetail : public MoMeshRepresentationDetail {

 SO_DETAIL_HEADER(MoLineMeshDetail);

 public:
  /**
   * Constructor.
   */
  MoLineMeshDetail();
  /**
   * Destructor.
   */
  virtual ~MoLineMeshDetail();

  /*
  * Returns the extracted line
  */
  const MeXLineMeshUnstructured* getExtractedMesh() const   { return m_extractedMesh; }

  // Returns an instance that is a copy of this instance. The caller
  // is responsible for deleting the copy when done.
  virtual MoLineMeshDetail *  copy() const;

 SoEXTENDER public:
  MoLineMeshDetail(const MeXLineMeshUnstructured* mesh, const MeXScalardSetI* scalarset);

 SoINTERNAL public:
  static void                 initClass();
  static void                 exitClass();

private:
  const MeXLineMeshUnstructured*   m_extractedMesh;

};

#endif /* _MO_LINEMESHDETAIL_ */

