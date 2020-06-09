/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : J.HUMMEL (Dec 2002)
** Modified by : T.DUFOUR (MMM yyyy)
**=======================================================================*/
#ifndef  _SO_LDM_VVIZ_GEOMETRY_
#define  _SO_LDM_VVIZ_GEOMETRY_

#include <LDM/SoLDMLargeDataManagement.h>
#include <LDM/SoLDMTileVisitor.h>
#include <Inventor/SbPList.h>
#include <Inventor/SbElapsedTime.h>

class SoAction;
class SoNode;
class SoROI;

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

/**
 * @LDMEXT VVizGeometry
 *
 * @ingroup LDMKernel
 *
 * @DESCRIPTION
 *
 * This class is only needed for advanced users who intend to extend or replace
 * internal LDM algorithms.
 *
 * The SoLDMGeometry node is in charge of collecting the geometry relevant to the data set
 * being rendered.
 * This geometry collection is used by the SoLDMTileVisitor to evaluate the importance of tiles.
 * Any modification of the geometry collection (geometry is added or removed) results in a new
 * collection done during a render traversal before anything is evaluated and rendered.
 * Once the geometry is collected, SoLDMGeometry notifies SoLDMNodeFrontManager that the texture
 * node front needs reevaluation. Each piece of geometry can have a weight associated with it.
 * The user can then focus on highlighting the part of the data set that is the most interesting for him.
 * The weight can be used by the SoLDMTileVisitor to assign the tiles weight.
 *
 * @SEE_ALSO
 * SoLDMNodeFrontManager,
 * SoLDMTileVisitor
 *
 */

SoEXTENDER_Documented class LDM_API SoLDMGeometry : public SoLDMLargeDataManagement {

 public:
  /**
   * Constructor.
   */
  SoLDMGeometry();

  /**
   * Destructor.
   */
  virtual ~SoLDMGeometry();

  /**
   * Indicates geometry collection is going to begin.
   */
  void beginCollectingGeometry(SoState* state = NULL);

  /**
   * Add geometry. The action is passed to access state and geometry
   * information.
   */
  void addGeometry( SoAction *action, SoNode* node );

  /**
   * Indicates geometry collection is achieved.
   */
  void endCollectingGeometry(SoState* state = NULL);

  /**
   * Returns TRUE if the tile box is inside the geometry ROI.
   */
  bool isTileInROI(SoROI*, const SbBox3i32& ,SoLDMTileVisitor::NodeStatus&, SbBool);

  /**
   * Returns the exhaustive list of geometries
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  int getGeometry(SbPList& geomList);

  /**
   * Based on geometry state, sets the tileID threshold under which tile weights should
   * be reset in memory before a topology evaluation.
   */
  void assignTilePriority();

SoINTERNAL public:
  void setUpdateGeometry(); //mark geomtries as cache invalid
  bool needsUpdate();       //does any geom need update
  bool toUpdate(SoNode*);   //does this node needs cache update?
  void updated(SoNode*);    //this node cache has been updated.

  bool isCollecting(){return m_isCollecting;};

  //distance from a point to a plane in data coordinnate
  static int getPointToPlaneDistance(const SbVec3i32& point, const SbPlane& plane);

  //distance from a point to the nearest plane of a box in data coordinnate
  static int getPointToBoxSkinDistance(const SbVec3i32& point, const SbBox3i32& box);

  bool            m_ROIChanged;
  SbBox3f         getGeomPos(SbBox3i32 subVolume);

  //------------------------------------------------------------------------------
private:
  struct GeometryInfos
  {
    GeometryInfos() : m_firstMove(1),
                         m_userIsInteracting(FALSE),
                         m_changeNotification(FALSE),
                         m_numGeoms(0), m_currentGeomIndex(0) {}
    int               m_firstMove;
    SbBool            m_userIsInteracting;
    SbBool            m_changeNotification;

    SbPList           m_geometryList;
    int               m_numGeoms;
    int               m_currentGeomIndex;
  };
  typedef std::map<int, GeometryInfos> CtxGeometryMap;

  CtxGeometryMap m_geometryInfos;

  static void setUpdateGeometry(CtxGeometryMap::value_type& p);
  static bool needsUpdate(CtxGeometryMap::value_type& p);
  static void deleteLDMGeomElement(CtxGeometryMap::value_type& p);

  /** Remove context no loger used */
  void removeUnusuedContext();

  void              handleInteraction(SoState* state);
  bool              m_rightEye; //stereo?

  bool              m_isCollecting;
  //temp var for no_user_interaction mode:
  SbBool            m_viewCulling;
  int               m_sliceTexLoadRate;
  int               m_texLoadRate;
  LDM_TILE_ID_TYPE  m_maxTileID;

  friend class SoLDMGeometryToUpdate;
  friend class SoLDMGeometryUpdated;
};
//--------------------------------------------------------------------------------

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // _SO_LDM_VVIZ_GEOMETRY_
