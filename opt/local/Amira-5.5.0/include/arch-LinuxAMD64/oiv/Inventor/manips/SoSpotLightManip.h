/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : SGI (MMM YYYY)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/
////////////////////////////////////////////////////////////////////////
//
// Description:
//      This file defines a manipulator for a spot light nodes.
//      It is subclassed from SoSpotLight.
//
////////////////////////////////////////////////////////////////////////

 
#ifndef  _SO_SPOT_LIGHT_MANIP_
#define  _SO_SPOT_LIGHT_MANIP_

#include <Inventor/SbLinear.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/nodes/SoSpotLight.h>
#include <Inventor/sensors/SoFieldSensor.h>

#ifdef OIV_NET_DOC
/**
* Spotlight node with 3D interface for editing location, direction, and beam
* width.
* 
* @ingroup manips
* 
* @DESCRIPTION
*   SoSpotLightManip is the base class for all SoSpotLight nodes that have a
*   built-in 3D user interface (this is the only such class provided with the Open
*   Inventor toolkit). Since it is derived from SoSpotLight, any changes to its
*   fields result in a change of lighting for nodes that follow it in the scene
*   graph. In this case, the interface edits the @B location @b, @B direction @b,
*   and @B cutOffAngle @b fields. Also, the color of the manipulator's geometry
*   will reflect the color of the light (but you can not edit the color using this
*   manipulator).
*   
*   Typically, you will want to replace a regular SoSpotLight with an
*   SoSpotLightManip (as when the user selects a light to be edited), or vice versa
*   (as when the user is done moving the light and the interface should go away).
*   Use the replaceNode() method to insert a manipulator into a scene graph,
*   and the replaceManip() method to remove it when done.
*   
*   The SoSpotLightManip utilizes an SoSpotLightDragger to provide a 3D interface.
*   However, the manipulator differs from the dragger; it lights other objects in
*   the scene because, as an SoSpotLight, it alters the state. The fields values and
*   movement of the dragger, on the other hand, affect only the dragger itself. To
*   find out more about how the interface works and what each part will do, see the
*   reference page for SoSpotLightDragger. The interfaces of the dragger and the
*   manipulator are identical.
*   
*   The SoSpotLightManip utilizes its dragger by adding it as a hidden child. When an
*   action is applied to the manipulator, such as rendering or handling events, the
*   manipulator first traverses the dragger, and then the manipulator adds its
*   lighting parameters to the state. When you click-drag-release over the
*   manipulator, it passes these events down to the dragger, which moves as a result
*   ("I can't @B help @b it, I'm a dragger!").
*   
*   The manipulator maintains consistency between the fields of the dragger and its
*   own fields. Let's say you use the mouse to widen the cone of the @B dragger @b.
*   Callbacks insure that the @B cutOffAngle @b field of the @B manipulator @b
*   will change by the same amount, thus changing the lighting of nodes which follow
*   in the scene graph. Similarly, if you set the @B cutOffAngle @b field of the
*   SoSpotLightManip, the manipulator will widen the beam of the dragger
*   accordingly.
*   
*   Because the dragger is a @B hidden @b child, you can see the dragger on screen
*   and interact with it, but the dragger does not show up when you write the
*   manipulator to file. Also, any SoPath will end at the manipulator. (See the
*   Actions section of this reference page for a complete description of when the
*   dragger is traversed).
*   
*   If you want to get a reference to the dragger you can get it from the manipulator
*   using the getDragger() method. You will need to do this if you want to
*   change the geometry of a manipulator, since the geometry actually belongs to the
*   dragger.
* 
* @FILE_FORMAT_DEFAULT
*    SpotLightManip {
*    @TABLE_FILE_FORMAT
*       @TR on            @TD true
*       @TR intensity     @TD 1
*       @TR color         @TD 1 1 1
*       @TR location      @TD 0 0 1
*       @TR direction     @TD 0 0 -1
*       @TR dropOffRate   @TD 0
*       @TR cutOffAngle   @TD 0.785398
*    @TABLE_END
*    }
* 
* @ACTION_BEHAVIOR
*    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoGetMatrixAction,  SoHandleEventAction,  SoRayPickAction @BR
*        First, traverses the dragger the way an SoGroup would. All draggers place
*        themselves in space, but leave the current transformation unchanged when
*        finished. Then the SoSpotLightManip adds a spotlight to the state, just like its
*        base class, SoSpotLight.
* 
*    SoSearchAction @BR
*        Searches just like an SoSpotLight. Does not search the dragger, which is a
*        hidden child.
* 
*    SoWriteAction @BR
*        Writes out just like an SoSpotLight. Does not write the dragger, which is a
*        hidden child. If you really need to write valuable information about the
*        dragger, such as customized geometry, you can retrieve the dragger with the
*        getDragger() method and then write it out separately.
* 
* 
* @SEE_ALSO
*    SoDragger,
*    SoSpotLight,
*    SoSpotLightDragger,
*    SoDirectionalLightManip,
*    SoPointLightManip
* 
* 
*/ 
#else
/**
* Spotlight node with 3D interface for editing location, direction, and beam
* width.
* 
* @ingroup manips
* 
* @DESCRIPTION
*   SoSpotLightManip is the base class for all SoSpotLight nodes that have a
*   built-in 3D user interface (this is the only such class provided with the Open
*   Inventor toolkit). Since it is derived from SoSpotLight, any changes to its
*   fields result in a change of lighting for nodes that follow it in the scene
*   graph. In this case, the interface edits the @B location @b, @B direction @b,
*   and @B cutOffAngle @b fields. Also, the color of the manipulator's geometry
*   will reflect the color of the light (but you can not edit the color using this
*   manipulator).
*   
*   Typically, you will want to replace a regular SoSpotLight with an
*   SoSpotLightManip (as when the user selects a light to be edited), or vice versa
*   (as when the user is done moving the light and the interface should go away).
*   Use the replaceNode() method to insert a manipulator into a scene graph,
*   and the replaceManip() method to remove it when done.
*   
*   The SoSpotLightManip utilizes an SoSpotLightDragger to provide a 3D interface.
*   However, the manipulator differs from the dragger; it lights other objects in
*   the scene because, as an SoSpotLight, it alters the state. The fields values and
*   movement of the dragger, on the other hand, affect only the dragger itself. To
*   find out more about how the interface works and what each part will do, see the
*   reference page for SoSpotLightDragger. The interfaces of the dragger and the
*   manipulator are identical.
*   
*   The SoSpotLightManip utilizes its dragger by adding it as a hidden child. When an
*   action is applied to the manipulator, such as rendering or handling events, the
*   manipulator first traverses the dragger, and then the manipulator adds its
*   lighting parameters to the state. When you click-drag-release over the
*   manipulator, it passes these events down to the dragger, which moves as a result
*   ("I can't @B help @b it, I'm a dragger!").
*   
*   The manipulator maintains consistency between the fields of the dragger and its
*   own fields. Let's say you use the mouse to widen the cone of the @B dragger @b.
*   Callbacks insure that the @B cutOffAngle @b field of the @B manipulator @b
*   will change by the same amount, thus changing the lighting of nodes which follow
*   in the scene graph. Similarly, if you set the @B cutOffAngle @b field of the
*   SoSpotLightManip, the manipulator will widen the beam of the dragger
*   accordingly.
*   
*   Because the dragger is a @B hidden @b child, you can see the dragger on screen
*   and interact with it, but the dragger does not show up when you write the
*   manipulator to file. Also, any SoPath will end at the manipulator. (See the
*   Actions section of this reference page for a complete description of when the
*   dragger is traversed).
*   
*   If you want to get a pointer to the dragger you can get it from the manipulator
*   using the getDragger() method. You will need to do this if you want to
*   change the geometry of a manipulator, since the geometry actually belongs to the
*   dragger.
* 
* @FILE_FORMAT_DEFAULT
*    SpotLightManip {
*    @TABLE_FILE_FORMAT
*       @TR on            @TD TRUE
*       @TR intensity     @TD 1
*       @TR color         @TD 1 1 1
*       @TR location      @TD 0 0 1
*       @TR direction     @TD 0 0 -1
*       @TR dropOffRate   @TD 0
*       @TR cutOffAngle   @TD 0.785398
*    @TABLE_END
*    }
* 
* @ACTION_BEHAVIOR
*    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoGetMatrixAction,  SoHandleEventAction,  SoRayPickAction @BR
*        First, traverses the dragger the way an SoGroup would. All draggers place
*        themselves in space, but leave the current transformation unchanged when
*        finished. Then the SoSpotLightManip adds a spotlight to the state, just like its
*        base class, SoSpotLight.
* 
*    SoSearchAction @BR
*        Searches just like an SoSpotLight. Does not search the dragger, which is a
*        hidden child.
* 
*    SoWriteAction @BR
*        Writes out just like an SoSpotLight. Does not write the dragger, which is a
*        hidden child. If you really need to write valuable information about the
*        dragger, such as customized geometry, you can retrieve the dragger with the
*        getDragger() method and then write it out separately.
* 
* 
* @SEE_ALSO
*    SoDragger,
*    SoSpotLight,
*    SoSpotLightDragger,
*    SoDirectionalLightManip,
*    SoPointLightManip
* 
* 
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SoSpotLightManip : public SoSpotLight
{
  SO_NODE_HEADER(SoSpotLightManip);

 public:
  /**
   * Constructor.
   */
  SoSpotLightManip();

#ifdef OIV_NET_DOC
  /**
  * Returns a reference to the dragger being used by this manipulator. Given this
  * reference, you can customize the dragger just like you would any other dragger.
  * You can change geometry using the setPart() method, or add \oivnetdoc delegates \else callbacks \endoivnetdoc
  * using the methods found in the SoDragger reference page.
  */

#else
  /**
  * Returns a pointer to the dragger being used by this manipulator. Given this
  * pointer, you can customize the dragger just like you would any other dragger.
  * You can change geometry using the setPart() method, or add \oivnetdoc delegates \else callbacks \endoivnetdoc
  * using the methods found in the SoDragger reference page.
  */

#endif //OIV_NET_DOC
  SoDragger *getDragger();

#ifdef OIV_NET_DOC
  /**
  * Replaces the tail of the path with this manipulator. The tail of the path must
  * be an SoSpotLight node (or subclass thereof). If the path has a nodekit, this
  * will try to use setPart() to insert the manipulator. Otherwise, the
  * manipulator requires that the next to last node in the path chain be a group.
  * 
  * The field values from the spotlight node will be copied to this manipulator, and
  * the light node will be replaced.
  * 
  * The old
  * node will disappear if it has no references other than from the input path p and
  * its parent, since this manipulator will be replacing it in both of those places.
  * Nor will the manipulator make any changes to field connections of the old node.
  * The calling process is thus responsible for keeping track of its own nodes and
  * field connections.
  */

#else
  /**
  * Replaces the tail of the path with this manipulator. The tail of the path must
  * be an SoSpotLight node (or subclass thereof). If the path has a nodekit, this
  * will try to use setPart() to insert the manipulator. Otherwise, the
  * manipulator requires that the next to last node in the path chain be a group.
  * 
  * The field values from the spotlight node will be copied to this manipulator, and
  * the light node will be replaced.
  * 
  * The manipulator will not call ref() on the node it is replacing. The old
  * node will disappear if it has no references other than from the input path p and
  * its parent, since this manipulator will be replacing it in both of those places.
  * Nor will the manipulator make any changes to field connections of the old node.
  * The calling process is thus responsible for keeping track of its own nodes and
  * field connections.
  */

#endif //OIV_NET_DOC
  SbBool replaceNode( SoPath *p );
#ifdef OIV_NET_DOC
  /**
  * Replaces the tail of the path, which must be this manipulator, with the given
  * SoSpotLight node. If the path has a nodekit, this will try to use
  * setPart() to insert the new node. Otherwise, the manipulator requires
  * that the next to last node in the path chain be a group.
  * 
  * The field values from the manipulator will be copied to the spotlight node, and
  * the manipulator will be replaced.
  * 
  * It will not make any changes to field connections. The calling
  * process is thus responsible for keeping track of its own nodes and field
  * connections.
  */

#else
  /**
  * Replaces the tail of the path, which must be this manipulator, with the given
  * SoSpotLight node. If the path has a nodekit, this will try to use
  * setPart() to insert the new node. Otherwise, the manipulator requires
  * that the next to last node in the path chain be a group.
  * 
  * The field values from the manipulator will be copied to the spotlight node, and
  * the manipulator will be replaced.
  * 
  * The manipulator will not call ref() or unref() on the node which is
  * replacing it, nor will it make any changes to field connections. The calling
  * process is thus responsible for keeping track of its own nodes and field
  * connections.
  */

#endif //OIV_NET_DOC
  SbBool replaceManip(SoPath *p, SoSpotLight *newOne ) const;

 SoEXTENDER public:

  // These functions implement all actions for nodekits.
  // They first traverse the children, then use the SoSpotLight
  // version of the actions. They traverse first so that the light
  // will affect objects which follow it in the tree, but not the
  // dragger-child.
  virtual void doAction( SoAction *action );
  virtual void callback( SoCallbackAction *action );
  virtual void GLRender( SoGLRenderAction *action );
  virtual void getBoundingBox( SoGetBoundingBoxAction *action );
  virtual void getMatrix(SoGetMatrixAction *action );
  virtual void handleEvent( SoHandleEventAction *action );
  virtual void pick( SoPickAction *action );
  virtual void search( SoSearchAction *action );
  virtual void write( SoWriteAction *action );

 SoINTERNAL public:

  static void initClass();
  static void exitClass();

  virtual SoChildList *getChildren() const;
  virtual bool isGroup() { return true; }

  // Internal child management following inheritance of classes.
  virtual void internalRemoveChild( int index );
  virtual void internalRemoveChild( SoNode *child) { internalRemoveChild(internalFindChild(child)); }
  virtual void internalRemoveAllChildren();
  virtual void internalAddChild( SoNode *child );
  virtual int internalFindChild( const SoNode *child ) const;
  virtual void internalInsertChild( SoNode *child, int newChildIndex );
  virtual SoNode *internalGetChild( int index) const { return (*children)[index]; }
  virtual void internalReplaceChild( int index, SoNode *newChild);
  virtual void internalReplaceChild( SoNode *oldChild, SoNode *newChild) { internalReplaceChild(internalFindChild(oldChild),newChild); }

 protected:

  // Redefines this to also copy the dragger
  virtual void        copyContents(const SoFieldContainer *fromFC,
                                   SbBool copyConnections);

  static void transferFieldValues( const SoSpotLight *from, 
                                   SoSpotLight *to);

  SoFieldSensor *locationFieldSensor;
  SoFieldSensor *directionFieldSensor;
  SoFieldSensor *angleFieldSensor;
  SoFieldSensor *colorFieldSensor;
  static void fieldSensorCB(void *, SoSensor *);
  static void valueChangedCB(void *,SoDragger *);

  void setDragger( SoDragger *newDragger );

  SoChildList *children;
  virtual SbBool readInstance(SoInput *in, unsigned short flags);
  virtual SbBool readChildren(SoInput *in);

  virtual ~SoSpotLightManip();

  inline virtual SoNode::SoNotificationInfo * getNotificationInfo() const
  { return (SoNotificationInfo*)(&m_notificationInfo); }

 private:
  int getNumChildren() const { return (children->getLength()); }

  SoNode::SoNotificationInfo m_notificationInfo;

};    

#endif  /* _SO_SPOT_LIGHT_MANIP_ */

