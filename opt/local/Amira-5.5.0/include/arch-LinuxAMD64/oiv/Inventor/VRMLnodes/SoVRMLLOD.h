/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_VRMLLOD_
#define  _SO_VRMLLOD_

#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoMFNode.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/VRMLnodes/SoVRMLParent.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLLOD
//
//  Level-of-detail group node. The levels of this node typically
//  represent the same object or objects at varying levels of detail,
//  from highest detail to lowest.  The world-space distance of the
//  eye from the transformed center of the VRMLLOD is computed, and one
//  level is drawn, based on the values in the ranges field.
//
//  More precisely, if the distance from the eyepoint to the
//  transformed center is D and the ranges array contains LAST_RANGE+1
//  values (numbered 0...LAST_RANGE), then:
//
//  D < ranges[0]  : Level 0 is drawn
//  ranges[i-1] < D < ranges[i] : Level i is drawn
//  D > ranges[LAST_RANGE] : Level LAST_RANGE+1 is drawn
//
//  So, you should specify N ranges and N+1 levels.  If you specify
//  too few levels, the last level will be used for the extra
//  ranges.  If you specify too few ranges, the extra levels will
//  never be used.
//
//  Add an SoInfo node as a level if you want a level of detail
//  that doesn't draw anything.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Distance-based level-of-detail switching group node.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   The SoVRMLLOD node allows applications to switch between various levels of
 *   detail or complexity for a given object, based on the distance from the user.
 *
 *   @B NOTE:@b  This node contains three fields inherited from 
 *   SoVRMLParent that are new in Open Inventor 5.0. These fields 
 *   are children (replaces the level field for X3D), bboxCenter, 
 *   and bboxSize.
 *   If you specify a non-default value for this field, when this node
 *   is written to an Inventor file, the file will contain this new
 *   field. Older versions of Open Inventor will not be able to read
 *   this file and will generate an Inventor read error (unknown
 *   field).@BR
 *   @B NOTE 2:@b This field is not compatible with VRML97.
 *   If you specify a non-default value for this field, when this node
 *   is written to a VRML file, the file will contain this incompatible
 *   field and standard VRML97 file readers will not be able to read it.
 *
 *   The #level field contains a list of nodes that represent the same object
 *   or objects at varying levels of detail, from highest to the lowest level of
 *   detail, and the #range field specifies the ideal distances at which to
 *   switch between the levels.
 *   
 *   The #center field is a translation offset in the local coordinate system
 *   that specifies the center of the SoVRMLLOD object for distance calculations. In
 *   order to calculate which level to display, first the distance is calculated from
 *   the viewpoint, transformed into the local coordinate space of the SoVRMLLOD
 *   node, (including any scaling transformations), to the #center point of the
 *   SoVRMLLOD. If the distance is less than the first value in the #range
 *   field, then the first level of the SoVRMLLOD is drawn. If between the first and
 *   second values in the #range field, the second level is drawn, and so on.
 *   
 *   If there are N values in the #range field, the SoVRMLLOD must have N+1
 *   nodes in its #level field. Specifying too few levels will result in the
 *   last level being used repeatedly for the lowest levels of detail; if more levels
 *   than ranges are specified, the extra levels will be ignored. The exception to
 *   this rule is to leave the range field empty, which is a hint to the browser that
 *   it should choose a level automatically to maintain a constant display rate. Each
 *   value in the #range field should be greater than the previous value;
 *   otherwise results are undefined.
 *
 *   Note that the selection of which child to render depends on the current
 *   camera settings, so generally this node should not be render cached.
 *   SoVRMLLOD nodes prohibit auto-caching, so that no SoSeparator (or other render
 *   caching node) above an SoVRMLLOD in the scene graph will automatically create a
 *   render cache.  This can significantly affect performance and applications should
 *   try to keep nodes that @I can @i be render cached (especially geometry nodes)
 *   under a different SoSeparator.
 * 
 * @VRML2_SPECIFICATION
 *    This section describes the expected behavior of the node in a conforming VRML97
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *   This section may reference portions of the VRML97 specification that are not
 *   present in this help file. The complete VRML97 spec is available at
 *   @B http://www.web3d.org @b.
 *   
 *   The SoVRMLLOD node specifies various levels of detail or complexity for a given
 *   object, and provides hints for browsers to automatically choose the appropriate
 *   version of the object based on the distance from the user. The #level
 *   field contains a list of nodes that represent the same object or objects at
 *   varying levels of detail, from highest to the lowest level of detail, and the
 *   #range field specifies the ideal distances at which to switch between the
 *   levels. See the "Concepts - Grouping and Children Nodes" section for a details
 *   on the types of nodes that are legal values for level.
 *   
 *   The #center field is a translation offset in the local coordinate system
 *   that specifies the center of the SoVRMLLOD object for distance calculations. In
 *   order to calculate which level to display, first the distance is calculated from
 *   the viewpoint, transformed into the local coordinate space of the SoVRMLLOD
 *   node, (including any scaling transformations), to the #center point of the
 *   SoVRMLLOD. If the distance is less than the first value in the #range
 *   field, then the first level of the SoVRMLLOD is drawn. If between the first and
 *   second values in the #range field, the second level is drawn, and so on.
 *   
 *   If there are N values in the #range field, the SoVRMLLOD must have N+1
 *   nodes in its #level field. Specifying too few levels will result in the
 *   last level being used repeatedly for the lowest levels of detail; if more levels
 *   than ranges are specified, the extra levels will be ignored. The exception to
 *   this rule is to leave the range field empty, which is a hint to the browser that
 *   it should choose a level automatically to maintain a constant display rate. Each
 *   value in the #range field should be greater than the previous value;
 *   otherwise results are undefined.
 *   
 *   Authors should set SoVRMLLOD ranges so that the transitions from one level of
 *   detail to the next are smooth. Browsers may adjust which level of detail is
 *   displayed to maintain interactive frame rates, to display an already-fetched
 *   level of detail while a higher level of detail (contained in an Inline node) is
 *   fetched, or might disregard the author-specified ranges for any other
 *   implementation-dependent reason. For best results, specify ranges only where
 *   necessary, and nest SoVRMLLOD nodes with and without ranges. Browsers should try
 *   to honor the hints given by authors, and authors should try to give browsers as
 *   much freedom as they can to choose levels of detail based on performance.
 *   
 *   SoVRMLLOD nodes are evaluated top-down in the scene graph. Only the descendants
 *   of the currently selected level are rendered and evaluated. Note that all nodes
 *   under an SoVRMLLOD node continue to receive and send events regardless of which
 *   SoVRMLLOD #level is active.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLLOD {
 *    @TABLE_FILE_FORMAT
 *       @TR level        @TD [] // VRML97 only
 *       @TR children     @TD [] // X3D only
 *       @TR center       @TD 0 0 0
 *       @TR range        @TD []
 *       @TR bboxCenter   @TD 0 0 0
 *       @TR bboxSize     @TD -1 -1 -1
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoRayPickAction,  SoSearchAction,  SoWriteAction  @BR
 * 
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoMFNode   @TD   set_level // VRML97 only
 *       @TR   SoMFNode   @TD   set_children // X3D only
 *       @TR   SoSFNode    @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoMFNode   @TD   level_changed // VRML97 only
 *       @TR   SoMFNode   @TD   children_changed // X3D only
 *       @TR   SoSFNode    @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLLOD : public SoVRMLParent {

  SO_NODE_HEADER(SoVRMLLOD);

 public:
  // Fields
  /**
   * Specifies the ideal distances at which to switch between the levels.
   * 
   */
  SoMFFloat           range;
  /**
   * Translation offset in the local coordinate system that specifies the center of
   * the SoVRMLLOD objects.
   * 
   */
  SoSFVec3f           center;
  /**
   * List of nodes that request the same object or objects at varying levels of
   * detail from highest to lowest (VRML97).
   *
   * In X3D, the list of nodes is specified using the children field 
   * (inherited from SoVRMLParent). 
   *
   * @B NOTE:@b The children field is a @B new field in SoVRMLLOD @b added 
   * in Open Inventor 5.0.
   * If you specify a non-default value for this field, when this node
   * is written to an Inventor file, the file will contain this new
   * field. Older versions of Open Inventor will not be able to read
   * this file and will generate an Inventor read error (unknown
   * field).@BR
   * @B NOTE 2:@b This field is not compatible with VRML97.
   * If you specify a non-default value for this field, when this node
   * is written to a VRML file, the file will contain this incompatible
   * field and standard VRML97 file readers will not be able to read it.
   * 
   */
  SoMFNode            level;
  /**
   * Constructor.
   */
  SoVRMLLOD();
  /**
   * Constructor that takes approximate number of levels/children.
   */
  SoVRMLLOD(int nLevels);
  /**
   * Overrides default method on SoNode.
   */
  virtual SbBool     affectsState() const;
  /**
   * Adds a level/child as last one in group.
   */
  void                addLevel(SoNode *level1);

  /**
   * Adds a level/child so that it becomes the one with the given index.
   */
  void                insertLevel(SoNode *level1, int newLevelIndex);

#ifdef OIV_NET_DOC
  /**
  * Returns reference to nth level/child node.
  */

#else
  /**
  * Returns pointer to nth level/child node.
  */

#endif //OIV_NET_DOC
  SoNode *            getLevel(int index) const;

  /**
   * Finds index of given level/child within group.
   */
  int                 findLevel(const SoNode *level1) const;

  /**
   * Returns number of levels/children.
   */
  int                 getNumLevels() const;

  /**
   * Removes level/child with given index from group.
   */
  void                removeLevel(int index);

  /**
   * Removes first instance of given level/child from group.
   */
  void                removeLevel(SoNode *level1)
    { removeLevel(findLevel(level1)); }

  /**
   * Removes all levels/children from group.
   */
  void                removeAllLevels();

  /**
   * Replaces level with given index with new level/child.
   */
  void                replaceLevel(int index, SoNode *newLevel);

  /**
   * Replaces first instance of given level/child with new level/child.
   */
  void                replaceLevel(SoNode *oldLevel, SoNode *newLevel)
    { replaceLevel(findLevel(oldLevel), newLevel); }

 SoEXTENDER public:
  // Implement actions:
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        rayPick(SoRayPickAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        search(SoSearchAction *action);
  virtual void        write(SoWriteAction *writeAction);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

  // These methods make render traversal faster by implementing
  // different rendering paths corresponding to different action
  // path codes.
  virtual void        GLRenderBelowPath(SoGLRenderAction *action);
  virtual void        GLRenderInPath(SoGLRenderAction *action);
  virtual void        GLRenderOffPath(SoGLRenderAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  // Adds a child as last one in group
  void                addChild(SoNode *child);

  // Adds a child so that it becomes the one with the given index
  void                insertChild(SoNode *child, int newChildIndex);

  // Returns pointer to nth child node
  SoNode *            getChild(int index) const;

  // Finds index of given child within group
  int                 findChild(const SoNode *child) const;

  // Returns number of children
  int                 getNumChildren() const;

  // Removes child with given index from group
  void                removeChild(int index);

  // Removes first instance of given child from group
  void                removeChild(SoNode *child)
    { removeChild(findChild(child)); }

  // Removes all children from group
  void                removeAllChildren();

  // Replaces child with given index with new child
  void                replaceChild(int index, SoNode *newChild);

  // Replaces first instance of given child with new child
  void                replaceChild(SoNode *oldChild, SoNode *newChild)
    { replaceChild(findChild(oldChild), newChild); }
  
  // Copies the contents of the given node into this instance. The
  // default implementation copies just field values and the name.
  virtual void copyContents(const SoFieldContainer *fromFC, SbBool copyConnections);

 protected:
  virtual ~SoVRMLLOD();
  virtual void        notify(SoNotList *);
  virtual SbBool      readInstance(SoInput *in, unsigned short flags);
  int internalSetValue;
  SoMFNode  addChildren;     //eventIn
  SoMFNode  removeChildren;  //eventIn
  void      processAddChildren();
  void      processRemoveChildren();


  virtual int         whichToTraverse(SoAction *);
};

#endif /* _SO_VRMLLOD_ */

