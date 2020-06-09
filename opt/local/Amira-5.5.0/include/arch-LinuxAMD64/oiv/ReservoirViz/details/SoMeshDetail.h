/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SOMESHDETAIL_H
#define _SOMESHDETAIL_H

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

#include <Inventor/STL/vector>
#include <Inventor/details/SoSubDetail.h>
#include <Inventor/SbVec.h>
#include <Inventor/SbViewVolume.h>

class SoDataSet;
class SoAction;

/**
 * @RVEXT Stores detail information about a picked cell in a mesh.
 * 
 * @ingroup ReservoirVizDetails
 * 
 * @DESCRIPTION
 *   A successful pick operation returns an SoPickedPoint object. If the picked
 *   shape corresponds to a representation of a mesh of type SoMeshGeometry, use 
 *   the @B getDetail @b method and cast the result to the appropriate class to 
 *   get extra information about the location of the pick.
 *   
 *   SoMeshDetail returns    
 *     - the i,j,k position of the picked cell (position in data space).
 *     - the value of the picked cell retreived from the current SoMeshProperty
 *     - or the values of the picked cell when multiple SoMeshProperty nodes are 
 *       inherited.
 *     - the data set of the picked mesh, i.e., the current SoMeshProperty node.
 *     - or the data sets of the picked mesh, when multiple SoMeshProperty nodes are
 *       inherited.
 * 
 * @SEE_ALSO
 *    SoDetail,
 *    SoMeshGeometry,
 *    SoMeshShape,
 *    SoMeshProperty
 *
 * @DESCRIPTION
 * 
 * @SEE_ALSO
 *    SoDetail
 * 
 * 
 */ 
class RESERVOIRVIZ_API SoMeshDetail : public SoDetail {

  SO_DETAIL_HEADER(SoMeshDetail);

public:
  /**
  * Constructor.
  */
  SoMeshDetail();
  /**
  * Destructor.
  */
  virtual ~SoMeshDetail();

  /**
  * Returns the value of the picked cell
  * retrieved from the current SoMeshProperty node.
  */
  float getValue() const;

  /**
  * Returns the values of the picked cell
  * when multiple SoMeshProperty nodes are inherited.
  */
  const std::vector<float> &getValues() const { 
    return m_values; 
  }

  /**
  * Returns the first property data set 
  * of the picked mesh, i.e., the current SoMeshProperty node.
  */
  SoDataSet * getPropertyData() const {
    return (m_propData.empty()) ? NULL : m_propData.at(0);
  }

  /**
  * Returns the property data sets of the picked mesh 
  * when multiple SoMeshProperty nodes are inherited.
  */
  const std::vector<SoDataSet *> &getAllPropertyData() const {
     return m_propData;
  }

  /**
  * Returns the position in data space (cell coordinates) of the picked cell.
  */
  SbVec3i32 getPos() { return m_ijkPos; }

  // Returns an instance that is a copy of this instance. The caller
  // is responsible for deleting the copy when done.
  virtual SoDetail * copy() const;

  //------------------------------------------------------------------------------

  SoEXTENDER public:
  void setDetails(const std::vector<float> &values, const SbVec3i32 &ijkPos, 
                  const std::vector<SoDataSet *> &propData, SoAction* action = NULL);
  void setPos(const SbVec3i32 &pos) { m_ijkPos = pos; }

  SoINTERNAL public:
  static void   initClass();
  static void   exitClass();
  SbViewVolume m_vv;

protected:
  std::vector<SoDataSet *> m_propData;
  SbVec3i32 m_ijkPos;  
  std::vector<float> m_values;
};

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /* _SOMESHDETAIL_H */
