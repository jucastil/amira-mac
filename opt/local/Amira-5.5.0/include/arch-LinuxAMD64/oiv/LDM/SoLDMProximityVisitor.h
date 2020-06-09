/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : J.HUMMEL (Dec 2004)
**=======================================================================*/
#ifndef  _SO_LDM_PROXIMITY_VISITOR_
#define  _SO_LDM_PROXIMITY_VISITOR_

#include <LDM/SoLDMTileVisitor.h>

/**
 *
 * @LDMEXT Proximity Visitor
 * @ingroup LDMKernel
 * 
 * @DESCRIPTION
 *
 * This class is only needed for advanced users who intend to extend or replace
 * internal LDM algorithms.
 *
 * This visitor assigns weight to a tile based on the tile's distance to the geometry
 * and the tile's distance to the ROI associated to the geometry.
 * The tiles are loaded first on the geometry and second by forming a hull around it.
 *
 *
 * @SEE_ALSO
 * SoLDMTileVisitor
 * 
 * 
 */ 
SoEXTENDER_Documented class LDM_API SoLDMProximityVisitor : public SoLDMTileVisitor {
 public:
  /**
   * Constructor.
   */
   SoLDMProximityVisitor();

  /**
   * Destructor.
   */
  ~SoLDMProximityVisitor();
 
  /**
   * Assigns a weight based on distance to the center of the screen.
   * May be overridden by the application.
   * distToScreen is the signed distance from the tile considered to the
   * center of the screen in normalized screen coordinate.
   * This functions is called only if the tile is culled.
   * The returned weight must be between 0 and 1.
   * Default returns 0 always.
   */
  virtual float getCullWeight(float distToScreen);

  /**
   * Assigns a weight based on distance to a surface geometry.
   * May be overridden by the application.
   * distToGeom is the signed distance from the surface to the considered
   * tile in data coordinates.
   * < 0 means the tile is behind or outside the geometry.
   * > 0 means the tile is in front of or inside the geometry.
   * = 0 means the tile intersects the geometry.
   * (the normal of a geometry plane is oriented towards increasing data (from voxel 0 to 1))
   * The geometryPriority argument is the weight of the geometry considered.
   * The returned weight must be between 0 and 1.
   * Default returns geometryPriority if the distance is null, else 0.
   */
  virtual float getSurfaceGeomWeight(float distToGeom, float geometryPriority);

  /**
   * Assigns a weight based on distance to a data set geometry.
   * May be overridden by the application.
   * distToGeom is the signed distance from the data set to the considered
   * tile in data coordinates.
   * < 0 means the tile is outside the data set.
   * > 0 means the tile is inside the data set.
   * = 0 means the tile intersects the data set.
   * (the normal of a geometry plane is oriented towards increasing data (from voxel 0 to 1))
   * The geometryPriority argument is the weight of the geometry considered.
   * The returned weight must be between 0 and 1.
   * Default returns geometryPriority if the distance is null, else 0.
   */
  virtual float getVolumeGeomWeight(float distToGeom, float geometryPriority);

  /**
   * Assigns a weight based on distance to ROI.
   * May be overridden by the application.
   * distToROI is the signed distance from the geometry ROI to a tile in data coordinates.
   * < 0 means the tile is outside the ROI.
   * > 0 means the tile is inside the ROI.
   * = 0 means the tile intersects the ROI.
   * The geometryPriority argument is the weight of the geometry considered.
   * The returned weight must be between 0 and 1.
   * Default returns 1 if the distance is >= 0, else 0.
   */
  virtual float getROIWeight(int distToROI, float geometryPriority);

};


#endif //_SO_LDM_PROXIMITY_VISITOR_

