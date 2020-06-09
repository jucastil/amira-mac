/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Martial Bonaventure (Dec 2010)
**=======================================================================*/


#ifndef _MO_SURFACEMESHDETAIL_
#define _MO_SURFACEMESHDETAIL_

#include <MeshVizInterface/mapping/details/MoMeshRepresentationDetail.h>

#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: MoSurfaceMeshDetail
//
//  Detail information about a mesh representation defined by a surface.
//
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Stores detail information about a mesh representation defined by a surface.
 * 
 * @ingroup MeshIViz_Mapping_Details
 * 
 * @DESCRIPTION
 *   This class contains detail information about a mesh representation defined by a
 *   surface. It includes the extracted surface. 
 * 
 * @SEE_ALSO
 *    SoDetail,
 *    MoMeshRepresentationDetail
 *    MoFaceDetail,
 *    MeXSurfaceMeshUnstructured,
 * 
 */ 

class MeXSurfaceMeshUnstructured;

class MESHIVIZDM_API MoSurfaceMeshDetail : public MoMeshRepresentationDetail {

 SO_DETAIL_HEADER(MoSurfaceMeshDetail);

 public:
  /**
   * Constructor.
   */
  MoSurfaceMeshDetail();
  /**
   * Destructor.
   */
  virtual ~MoSurfaceMeshDetail();

  /*
  * Returns the extracted surface
  */
  const MeXSurfaceMeshUnstructured* getExtractedMesh() const   { return m_extractedMesh; }

  // Returns an instance that is a copy of this instance. The caller
  // is responsible for deleting the copy when done.
  virtual MoSurfaceMeshDetail *  copy() const;

 SoEXTENDER public:
  MoSurfaceMeshDetail(const MeXSurfaceMeshUnstructured* mesh, const MeXScalardSetI* scalarset);

 SoINTERNAL public:
  static void                 initClass();
  static void                 exitClass();

private:
  const MeXSurfaceMeshUnstructured*   m_extractedMesh;

};

#endif /* _MO_SURFACEMESHDETAIL_ */

