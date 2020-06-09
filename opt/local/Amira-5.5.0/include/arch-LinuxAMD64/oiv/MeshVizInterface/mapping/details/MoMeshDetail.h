/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Martial Bonaventure (Nov 2010)
**=======================================================================*/


#ifndef _MO_MESHDETAIL_
#define _MO_MESHDETAIL_

#include <Inventor/details/SoSubDetail.h>

#include <MeshVizInterface/mapping/MoMeshVizDataMapping.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: MoMeshDetail
//
//  Detail information about a mesh.
//
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Stores detail information about a mesh.
 * 
 * @ingroup MeshIViz_Mapping_Details
 * 
 * @DESCRIPTION
 *   This class contains detail information about a mesh, like the mesh type, the mesh
 *   itself as an MiMesh and the associated color scalarset as an MiBoundedDataSet.
 *
 *   Detail objects are returned by the SoPickedPoint class after picking.
 * 
 * @SEE_ALSO
 *    SoDetail,
 *    SoPickedPoint,
 *    MoFaceDetail,
 *    MoLineDetail,
 *    MiMesh,
 *    MiBoundedDataSet,
 * 
 */ 

class MiMesh;
template <typename _T>
class MiBoundedDataSet;

class MoFaceDetail;
class MoLineDetail;

class MESHIVIZDM_API MoMeshDetail : public SoDetail {

 SO_DETAIL_HEADER(MoMeshDetail);

 public:
  /**
   * Constructor.
   */
  MoMeshDetail();
  /**
   * Destructor.
   */
  virtual ~MoMeshDetail();

  /*
  * Returns the type of the mesh
  */
  MeshType getMeshType() const   { return m_meshType; }

  /*
  * Returns the mesh
  */
  const MiMesh* getMesh() const   { return m_mesh; }

  /*
  * Returns the associated color scalarset, NULL if none.
  */
  const MiBoundedDataSet<double>* getColorScalarSet() const   { return m_colorScalarset; }

  // Returns an instance that is a copy of this instance. The caller
  // is responsible for deleting the copy when done.
  virtual MoMeshDetail *  copy() const;

 SoEXTENDER public:
  MoMeshDetail(const MiMesh* mesh, MeshType meshType, const MiBoundedDataSet<double>* colorScalarset = NULL);

  // set the associated scalarset
  void setColorScalarSet(const MiBoundedDataSet<double>* colorScalarset);
  // creates a new specialized face detail from the generic given one.
  // returns either a MoFaceDetailI, MoFaceDetailIj or a MoFaceDetailIjk depending on
  // the mesh type stored in this.
  MoFaceDetail* specilizeFaceDetail(const MoFaceDetail* faceDetail) const;
  // creates a new specialized line detail from the generic given one.
  // returns either a MoLineDetailI, MoLineDetailIj or a MoLineDetailIjk depending on
  // the mesh type stored in this.
  MoLineDetail* specilizeLineDetail(const MoLineDetail* lineDetail) const;

 SoINTERNAL public:
  static void                 initClass();
  static void                 exitClass();

  // temporary methods that convert a flat id into I/J/K indices until 
  // the MeXTopologyI is proprely implementated in all extractors for IJK meshes
  void computeIj(size_t id, size_t& i, size_t &j) const ;
  void computeIjk(size_t id, size_t& i, size_t &j, size_t &k) const;

private:

  MeshType                          m_meshType;
  const MiMesh*                     m_mesh;
  const MiBoundedDataSet<double>*   m_colorScalarset;

};

#endif /* _MO_MESHDETAIL_ */

