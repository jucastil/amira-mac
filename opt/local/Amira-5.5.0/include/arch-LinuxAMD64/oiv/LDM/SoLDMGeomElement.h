/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _GEOM_ELEM_
#define _GEOM_ELEM_

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

#include <LDM/SoLDMLargeDataManagement.h>
#include <Inventor/SbBox.h>
#include <Inventor/SbViewVolume.h>
#include <Inventor/STL/map>
#include <Inventor/helpers/SbGlContextHelper.h>
#include <Inventor/misc/SoRef.h>
#include <Inventor/nodes/SoShape.h>
#include <LDM/SoLDMTileID.h>

class SoAction;
class SoShape;
class SoROI;
class SoTimeHints;
class SoState;
class SoNodeSensor;

/**
 *
 *
 * @LDMEXT Geometry element
 *
 * @ingroup LDMKernel
 *
 * @DESCRIPTION
 *
 * The SoLDMGeomElement is a helper class defining a LDM node and its properties.
 *
 * @SEE_ALSO
 * SoLDMGeometry,
 */
SoEXTENDER_Documented class LDM_API SoLDMGeomElement {

 public:

  /**
   * Constructor.
   */
  SoLDMGeomElement(SoLDMGeometry*);

  /**
   * Destructor.
   */
  virtual ~SoLDMGeomElement();

SoEXTENDER public:
  /**
   * Sets node member and returns information about whether
   * any properties of the node have changed (change of ROI, bounding box...).
   * @B view@b indicates if the viewpoint should be taken into account.
   * @B roiChanged@b indicates if there was any ROI change.
   * @B userInteracts@b indicates if the user is interacting with the scene
   * at the time of the valuation.
   * [OIVJAVA-WRAPPER-ARG IN,IN,NO_WRAP]
   */
  virtual SbBool setGeometry( SoAction *action, SoNode *node, SbBool& userInteracts) = 0;

  /**
   * Returns the signed distance from the geometry to a tile in data/geometric coordinnate.
   * (depending on the geometry type).
   * < 0 means the tile is behind the geometry.
   * > 0 means the tile is in front of the geometry.
   * = 0 means the tile intersects the geometry.
   */
  virtual float getGeomToTileDist(SbBox3i32& tileBox, SbBox3f &tileGeomPos, SbVec3f &tileGeomCenter) = 0;

  /**
   * Returns the LDM node.
   */
  inline SoNode*   getNode();
  /**
   * Returns the weight associated with the geometry.
   */

  inline float     getWeight();
  /**
   * Returns the matrix associated with the geometry.
   */
  inline SbMatrix& getMatrix();
  /**
   * Returns the bounding box associated with the geometry.
   */
  inline SbBox3f   getBBox();
  /**
   * Returns the ROI associated with the geometry.
   */
  inline SoROI*    getROI();

  virtual bool isSkin(){return false;};
  virtual bool isFullyTransparent(double min, double max);

  /**
   * Returns the signed distance from the geometry ROI to a tile in data coordinnate.
   * < 0 means the tile is outside the ROI.
   * > 0 means the tile is inside the ROI.
   * = 0 means the tile intersects the ROI.
   */
  int getROIToTileDist(SbBox3i32& tileBox);


  virtual bool isVolume(){return false;};

SoINTERNAL public:
  void setNumTiles(int numTiles){m_numTiles=numTiles;};
  int getNumTiles(){return m_numTiles;};

  inline void setCurrentTileId(const SoLDMTileID& tile);

  //for fixed resolution
  SbBox3i32 dataBox;
  SbBox3i32 dataDimension;
  bool m_toUpdate;

 protected:
  static const float s_tolerance;

  SbBool setCommonGeometry( SoAction *action, SoShape *node, SbBool& userInteracts);
  bool hasTimeHintsChanged(SoState *state);

  typedef std::map<SbGlContextHelper::GLContext, SbBox3i32> CtxBBoxMap;
  typedef std::map<SbGlContextHelper::GLContext, SoShape*> CtxShapeMap;
  typedef std::map<SbGlContextHelper::GLContext, SbViewVolume> CtxViewVolumeMap;
  typedef std::map<SbGlContextHelper::GLContext, SbMatrix> CtxMatrixMap;
  CtxShapeMap m_ctxShape;
  CtxBBoxMap m_ctxBBox;
  CtxViewVolumeMap m_ctxViewVolume;
  CtxMatrixMap m_ctxModelMatrix;

  float               m_weight;
  SbMatrix            m_matrix;

  SbMatrix            m_modelMatrix;
  SbViewVolume        m_viewVolume;

  SbBox3f             m_bbox;
  SbBox3i32           m_dataBox;
  int                 m_ROIflag;

  SbBox3i32           m_ROISubVolume;
  SbBox3i32           m_ROIBox;
  SoLDMGeometry*      m_vvizGeom;
  int                 m_numTiles;

  short m_curTimeStep;
  short m_stepIncrement;

  /** Tile being traversed */
  SoLDMTileID m_curTileId;

private:
  // sensor responsible to catch mRoiNode changes (including delete)
  // it will be attached to the m_roiNode when it changed
  SoROI* m_ROINode;
  SoNodeSensor* m_roiNodeSensor;
  static void roiChangedSensorCB(void* data, SoSensor *sensor);
  static void roiRemovedSensorCB(void* data, SoSensor *sensor);

  // sensor responsible to catch m_shape changes (including delete)
  // it will be attached to the m_shape when it changed
  SoShape* m_shape;
  SoNodeSensor* m_shapeNodeSensor;
  static void shapeRemovedSensorCB(void* data, SoSensor *sensor);
};


/*******************************************************************************/
inline float
SoLDMGeomElement::getWeight()
{
#if defined(_DEBUG)
  if(m_weight == 0)
    SoError::post("SoLDMGeomElement returns a null weight");
#endif
  return m_weight;
}

/*******************************************************************************/
inline bool
SoLDMGeomElement::isFullyTransparent(double , double )
{
  return false;
}

/*******************************************************************************/
inline void
SoLDMGeomElement::setCurrentTileId(const SoLDMTileID& tile)
{
  m_curTileId = tile;
}

/*******************************************************************************/
SoROI*
SoLDMGeomElement::getROI()
{
  return m_ROINode;//.ptr();
}

/*******************************************************************************/
SoNode*
SoLDMGeomElement::getNode()
{
  return m_shape;
}

/*******************************************************************************/
SbMatrix&
SoLDMGeomElement::getMatrix()
{
  return m_matrix;
}

/*******************************************************************************/
SbBox3f
SoLDMGeomElement::getBBox()
{
  return m_bbox;
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif
