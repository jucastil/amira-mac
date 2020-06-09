/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Martial Bonaventure (Nov 2010)
**=======================================================================*/


#ifndef _MO_MESHREPRESENTATIONDETAIL_
#define _MO_MESHREPRESENTATIONDETAIL_

#include <Inventor/details/SoSubDetail.h>

#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>
#include <MeshVizInterface/mapping/MoMeshVizDataMapping.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: MoMeshRepresentationDetail
//
//  Detail information about a mesh representation.
//
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Stores detail information about a mesh representation.
 * 
 * @ingroup MeshIViz_Mapping_Details
 * 
 * @DESCRIPTION
 *   This class contains detail information about a mesh representation. 
 *   It includes the mapped scalarset used for coloring.
 * 
 * @SEE_ALSO
 *    SoDetail,
 *    MoFaceDetail,
 *    MoLineDetail
 *    MeXScalardSetI
 * 
 */ 

class MiMeshUnstructuredI;

class MESHIVIZDM_API MoMeshRepresentationDetail : public SoDetail {

 SO_DETAIL_HEADER(MoMeshRepresentationDetail);

 public:
  /**
   * Constructor.
   */
  MoMeshRepresentationDetail();
  /**
   * Destructor.
   */
  virtual ~MoMeshRepresentationDetail();

  /*
  * Returns the mapped scalarset used for coloring the mesh representation
  */
  const MeXScalardSetI* getExtractedColorScalarSet() const   { return m_extractedColorScalarset; }


  // Returns an instance that is a copy of this instance. The caller
  // is responsible for deleting the copy when done.
  virtual MoMeshRepresentationDetail *  copy() const = 0;

 SoEXTENDER public:
  MoMeshRepresentationDetail(const MiMeshUnstructuredI* mesh, const MeXScalardSetI* scalarset);

  // Computes the value of the scalarset in the cell defined by the index at the given point.
  // Returns DBL_MAX if point is not inside the cell.
  double computeValue(const MbVec3d& point, int32_t index) const;

 SoINTERNAL public:
  static void                 initClass();
  static void                 exitClass();

private:
  const MiMeshUnstructuredI*  m_mesh;
  const MeXScalardSetI*       m_extractedColorScalarset;

};

#endif /* _MO_MESHREPRESENTATIONDETAIL_ */

