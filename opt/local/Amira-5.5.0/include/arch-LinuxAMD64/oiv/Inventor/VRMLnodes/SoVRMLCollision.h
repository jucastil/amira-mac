/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_VRMLCOLLISION_
#define  _SO_VRMLCOLLISION_

#include <Inventor/fields/SoSFTime.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/VRMLnodes/SoVRMLGroup.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLCollision
//
//  VRMLGroup group node: state is saved before traversing children
//  and restored afterwards.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Grouping node that controls collision detection.\ @PARTIAL_ACTION
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   See the VRML97 Specification, below.
 *   
 *   Note: This node is partially implemented. It functions correctly as a grouping
 *   node, but does not currently implement the collision detection feature.
 *   
 *   IV_SEPARATOR_MAX_CACHES specifies the maximum number of render caches. To disable
 *   caching entirely, set it to 0. (This can reduce memory requirements at the cost
 *   of degraded performance.) See SoSeparator for additional information on caching
 *   in general, and SoVRMLGroup for information on the @B CacheEnabled @b enum
 *   values.
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
 *   By default, @B all @b @B objects @b @B in @b @B the @b @B scene @b
 *   @B are @b @B collidable @b. The browser must detect geometric collisions between
 *   the user's avatar (see SoVRMLNavigationInfo) and the scene's geometry, and
 *   prevent the avatar from 'entering' the geometry. The SoVRMLCollision node is a
 *   grouping node that may turn off collision detection for its descendants, specify
 *   alternative objects to use for collision detection, and send events signalling
 *   that a collision has occurred between the user's avatar and the SoVRMLCollision
 *   group's geometry or alternate. If there are no SoVRMLCollision nodes specified
 *   in a scene, browsers must detect collision with all objects during
 *   navigation.
 *   
 *   See the "Concepts - Grouping and Children Nodes" section for a description the
 *   @B children @b, @B addChildren @b, and @B removeChildren @b fields and
 *   eventIns.
 *   
 *   The SoVRMLCollision node's #collide field enables and disables collision
 *   detection. If #collide is set to FALSE, the children and all descendants
 *   of the SoVRMLCollision node will not be checked for collision, even though they
 *   are drawn. This includes any descendant SoVRMLCollision nodes that have
 *   #collide set to TRUE - (i.e., setting #collide to FALSE turns it off
 *   for every node below it).
 *   
 *   SoVRMLCollision nodes with the #collide field set to TRUE detect the
 *   nearest collision with their descendant geometry (or proxies). Note that not all
 *   geometry is collidable - see each geometry node's sections for details. When the
 *   nearest collision is detected, the collided SoVRMLCollision node sends the time
 *   of the collision through its #collideTime eventOut. This behavior is
 *   recursive - if an SoVRMLCollision node contains a child, descendant, or proxy
 *   (see below) that is an SoVRMLCollision node, and both SoVRMLCollisions detect
 *   that a collision has occurred, then both send a #collideTime event out at
 *   the same time, and so on.
 *   
 *   The @B bboxCenter @b and @B bboxSize @b fields specify a bounding box that
 *   encloses the SoVRMLCollision's children. This is a hint that may be used for
 *   optimization purposes. If the specified bounding box is smaller than the actual
 *   bounding box of the children at any time, then the results are undefined. A
 *   default @B bboxSize @b value, (-1 -1 -1), implies that the bounding box is not
 *   specified and if needed must be calculated by the browser. See "Concepts -
 *   Bounding Boxes" for a description of the @B bboxCenter @b and @B bboxSize @b
 *   fields.
 *   
 *   The collision proxy, defined in the #proxy field, is a legal child node,
 *   (see "Concepts - Grouping and Children Nodes"), that is used as a substitute for
 *   the SoVRMLCollision's children during collision detection. The proxy is used
 *   strictly for collision detection - it is not drawn.
 *   
 *   If the value of the #collide field is FALSE, then collision detection is
 *   not performed with the children or proxy descendant nodes. If the root node of a
 *   scene is an SoVRMLCollision node with the #collide field set to FALSE,
 *   then collision detection is disabled for the entire scene, regardless of whether
 *   descendant SoVRMLCollision nodes have set #collide TRUE.
 *   
 *   If the value of the #collide field is TRUE and the #proxy field is
 *   non-NULL, then the #proxy field defines the scene which collision
 *   detection is performed. If the #proxy value is NULL, the @B children @b
 *   of the collision node are collided against.
 *   
 *   If #proxy is specified, then any descendant children of the SoVRMLCollision
 *   node are ignored during collision detection. If @B children @b is empty,
 *   #collide is TRUE and #proxy is specified, then collision detection
 *   is done against the proxy but nothing is displayed (i.e., invisible collision
 *   objects). 
 *   
 *   The #collideTime eventOut generates an event specifying the time when the
 *   user's avatar (see SoVRMLNavigationInfo) intersects the collidable children or
 *   proxy of the SoVRMLCollision node. An ideal implementation computes the exact
 *   time of intersection. Implementations may approximate the ideal by sampling the
 *   positions of collidable objects and the user. Refer to the SoVRMLNavigationInfo
 *   node for parameters that control the user's size.
 *   
 *   Browsers are responsible for defining the navigation behavior when collisions
 *   occur. For example, when the user comes sufficiently close to an object to
 *   trigger a collision, the browser may have the user bounce off the object, come
 *   to a stop, or glide along the surface.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLCollision {
 *    @TABLE_FILE_FORMAT
 *       @TR children     @TD []
 *       @TR collide      @TD TRUE // VRML97 only
 *       @TR enabled      @TD TRUE // X3D only
 *       @TR bboxCenter   @TD 0 0 0
 *       @TR bboxSize     @TD -1 -1 -1
 *       @TR proxy        @TD NULL @NI 
 *       @TR metadata     @TD NULL
 *       @TR renderCaching        @TD AUTO
 *       @TR boundingBoxCaching   @TD AUTO
 *       @TR renderCulling        @TD AUTO
 *       @TR pickCulling          @TD AUTO
 *    @TABLE_END
 *    }
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoMFNode   @TD   addChildren      
 *       @TR   SoMFNode   @TD   removeChildren      
 *       @TR   SoMFNode   @TD   set_children      
 *       @TR   SoSFBool   @TD   set_collide // VRML97 only @NI 
 *       @TR   SoSFBool   @TD   set_enabled // X3D only @NI 
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFTime   @TD   collideTime @NI      
 *       @TR   SoMFNode   @TD   children_changed      
 *       @TR   SoSFBool   @TD   collide_changed // VRML97 only @NI 
 *       @TR   SoSFBool   @TD   enabled_changed // X3D only @NI 
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * @ACTION_BEHAVIOR
 *    Sets: SoCacheElement
 * 
 * 
 */ 

class INVENTOR_API SoVRMLCollision : public SoVRMLGroup {

  SO_NODE_HEADER(SoVRMLCollision);

 public:

  // Fields

  /**
   *  @NI Enables (TRUE) or disables (FALSE) collision detection.
   * (VRML97 only)
   * 
   */
  SoSFBool       collide;
  /**
   *  @NI Enables (TRUE) or disables (FALSE) collision detection.
   * (X3D only)
   *
   * @FIELD_SINCE_OIV 5.0
   *
   * @B NOTE 2:@b This field is not compatible with VRML97.
   * If you specify a non-default value for this field, when 
   * this node is written to a VRML file, the file will contain
   * this incompatible field and standard VRML97 file readers 
   * will not be able to read it.
   */
  SoSFBool       enabled;
  /**
   *  @NI Child node that is used as a substitute for the SoVRMLCollision's children
   * during collision detection.
   * 
   */
  SoSFNode       proxy;

  /**
   * Constructor.
   */
  SoVRMLCollision();

  /**
   * Constructor that takes approximate number of children
   */
  SoVRMLCollision(int nChildren);

 SoEXTENDER public:
  // Implement actions
  virtual void        GLRender(SoGLRenderAction *action);

 SoINTERNAL public:

  SoSFTime      collideTime; // eventOut
  SoSFBool      isActive;    // eventOut

  static void         initClass();
  static void         exitClass();

  virtual void        notify(SoNotList *list);

 protected:

  virtual ~SoVRMLCollision();

  ///////////////////////EXCEPTION METHODS/////////////////////////////////////
  //
  // #unfound bboxCenter
  // #unfound bboxSize
  //
  /////////////////////////////////////////////////////////////////////////////

};

#endif /* _SO_VRMLCOLLISION_ */

