/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul Isaacs (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_TRANSFORM_MANIP_
#define  _SO_TRANSFORM_MANIP_

#include <Inventor/SbLinear.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/sensors/SoFieldSensor.h>

class SoGetBoundingBoxAction;

#ifdef OIV_NET_DOC
/**
* Base class for all transform nodes with built-in 3D user interfaces.
* 
* @ingroup manips
* 
* @DESCRIPTION
*   SoTransformManip is the base class for all SoTransform nodes that have a
*   built-in 3D user interface. Since it is derived from SoTransform, any changes to
*   its fields result in the rotation, scaling, and/or translation of nodes that
*   follow it in the scene graph.
*   
*   Typically, you will want to replace a regular SoTransform with an
*   SoTransformManip (as when the user selects an object to be moved), or vice versa
*   (as when the object is deselected, and the motion interface should go away). Use
*   the replaceNode() method to insert a manipulator into a scene graph, and
*   the replaceManip() method to remove it when done.
*   
*   Every subclass of SoTransformManip utilizes a dragger of some sort to provide a
*   3D interface. (This class does not have dragger; but all the subclasses do.)
*   However a manipulator differs from a dragger; it influences other objects in the
*   scene because, as an SoTransform, it alters the state. The fields values and
*   movement of a dragger, on the other hand, affect only the dragger itself.
*   
*   Each SoTransformManip subclass utilizes its dragger by adding it as a hidden
*   child. When an action is applied to the manipulator, such as rendering or
*   handling events, the manipulator first traverses the dragger, and then the
*   manipulator adds its transformation matrix to the state. When you
*   click-drag-release over the manipulator, it passes these events down to the
*   dragger, which moves as a result ("I can't @B help @b it, I'm a dragger!").
*   
*   The manipulator maintains consistency between the fields of the dragger and its
*   own fields. Let's say you use the mouse to rotate the @B dragger @b. \oivnetdoc Delegates \else Callbacks \endoivnetdoc
*   insure that the @B rotation @b field of the @B manipulator @b will change by
*   the same amount, resulting in the rotation of nodes which follow in the scene
*   graph. Similarly, if you set any of the SoTransformManip fields the manipulator
*   will move the dragger accordingly. You can use this feature to impose
*   constraints on a manipulator: If the user moves the manipulator so that a field
*   value becomes too large, you can set the field back to your desired maximum, and
*   the whole thing will move back to where you specified.
*   
*   Since each SoTransformManip uses a dragger to provide its interface, you will
*   generally be told to look at the dragger's reference page for details of how it
*   moves and what the different parts are for. The interface for the dragger and
*   the manipulator will always be exactly the same. Usually, an SoTransformManip
*   will surround the objects that it influences (i.e., those that move along with
*   it). This is because the manipulator turns on the @B surroundScale @b part of
*   its dragger; so the dragger geometry expands to envelope the other objects (see
*   the reference page for SoSurroundScale).
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
*    TransformManip {
*    @TABLE_FILE_FORMAT
*       @TR translation        @TD 0 0 0
*       @TR rotation           @TD 0 0 1 0
*       @TR scaleFactor        @TD 1 1 1
*       @TR scaleOrientation   @TD 0 0 1 0
*       @TR center             @TD 0 0 0
*    @TABLE_END
*    }
* 
* @ACTION_BEHAVIOR
*    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoGetMatrixAction,  SoHandleEventAction,  SoRayPickAction @BR
*        First, traverses the dragger the way an SoGroup would. All draggers place
*        themselves in space, but leave the current transformation unchanged when
*        finished. Then the SoTransformManip accumulates a transformation into the
*        current transformation just like its base class, SoTransform.
* 
*    SoSearchAction @BR
*        Searches just like an SoTransform. Does not search the dragger, which is a
*        hidden child.
* 
*    SoWriteAction @BR
*        Writes out just like an SoTransform. Does not write the dragger, which is a
*        hidden child. If you really need to write valuable information about the
*        dragger, such as customized geometry, you can retrieve the dragger with the
*        getDragger() method and then write it out separately.
* 
* 
* @SEE_ALSO
*    SoDragger,
*    SoTransform,
*    SoCenterballManip,
*    SoHandleBoxManip,
*    SoJackManip,
*    SoSurroundScale,
*    SoTabBoxManip,
*    SoTrackballManip,
*    SoTransformBoxManip,
*    SoTransformerManip
* 
* 
*/ 
#else
/**
* Base class for all transform nodes with built-in 3D user interfaces.
* 
* @ingroup manips
* 
* @DESCRIPTION
*   SoTransformManip is the base class for all SoTransform nodes that have a
*   built-in 3D user interface. Since it is derived from SoTransform, any changes to
*   its fields result in the rotation, scaling, and/or translation of nodes that
*   follow it in the scene graph.
*   
*   Typically, you will want to replace a regular SoTransform with an
*   SoTransformManip (as when the user selects an object to be moved), or vice versa
*   (as when the object is deselected, and the motion interface should go away). Use
*   the replaceNode() method to insert a manipulator into a scene graph, and
*   the replaceManip() method to remove it when done.
*   
*   Every subclass of SoTransformManip utilizes a dragger of some sort to provide a
*   3D interface. (This class does not have dragger; but all the subclasses do.)
*   However a manipulator differs from a dragger; it influences other objects in the
*   scene because, as an SoTransform, it alters the state. The fields values and
*   movement of a dragger, on the other hand, affect only the dragger itself.
*   
*   Each SoTransformManip subclass utilizes its dragger by adding it as a hidden
*   child. When an action is applied to the manipulator, such as rendering or
*   handling events, the manipulator first traverses the dragger, and then the
*   manipulator adds its transformation matrix to the state. When you
*   click-drag-release over the manipulator, it passes these events down to the
*   dragger, which moves as a result ("I can't @B help @b it, I'm a dragger!").
*   
*   The manipulator maintains consistency between the fields of the dragger and its
*   own fields. Let's say you use the mouse to rotate the @B dragger @b. Callbacks
*   insure that the @B rotation @b field of the @B manipulator @b will change by
*   the same amount, resulting in the rotation of nodes which follow in the scene
*   graph. Similarly, if you set any of the SoTransformManip fields the manipulator
*   will move the dragger accordingly. You can use this feature to impose
*   constraints on a manipulator: If the user moves the manipulator so that a field
*   value becomes too large, you can set the field back to your desired maximum, and
*   the whole thing will move back to where you specified.
*   
*   Since each SoTransformManip uses a dragger to provide its interface, you will
*   generally be told to look at the dragger's reference page for details of how it
*   moves and what the different parts are for. The interface for the dragger and
*   the manipulator will always be exactly the same. Usually, an SoTransformManip
*   will surround the objects that it influences (i.e., those that move along with
*   it). This is because the manipulator turns on the @B surroundScale @b part of
*   its dragger; so the dragger geometry expands to envelope the other objects (see
*   the reference page for SoSurroundScale).
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
*    TransformManip {
*    @TABLE_FILE_FORMAT
*       @TR translation        @TD 0 0 0
*       @TR rotation           @TD 0 0 1 0
*       @TR scaleFactor        @TD 1 1 1
*       @TR scaleOrientation   @TD 0 0 1 0
*       @TR center             @TD 0 0 0
*    @TABLE_END
*    }
* 
* @ACTION_BEHAVIOR
*    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoGetMatrixAction,  SoHandleEventAction,  SoRayPickAction @BR
*        First, traverses the dragger the way an SoGroup would. All draggers place
*        themselves in space, but leave the current transformation unchanged when
*        finished. Then the SoTransformManip accumulates a transformation into the
*        current transformation just like its base class, SoTransform.
* 
*    SoSearchAction @BR
*        Searches just like an SoTransform. Does not search the dragger, which is a
*        hidden child.
* 
*    SoWriteAction @BR
*        Writes out just like an SoTransform. Does not write the dragger, which is a
*        hidden child. If you really need to write valuable information about the
*        dragger, such as customized geometry, you can retrieve the dragger with the
*        getDragger() method and then write it out separately.
* 
* 
* @SEE_ALSO
*    SoDragger,
*    SoTransform,
*    SoCenterballManip,
*    SoHandleBoxManip,
*    SoJackManip,
*    SoSurroundScale,
*    SoTabBoxManip,
*    SoTrackballManip,
*    SoTransformBoxManip,
*    SoTransformerManip
* 
* 
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SoTransformManip : public SoTransform
{
  SO_NODE_HEADER(SoTransformManip);

 public:

  /**
   * Constructor.
   */
  SoTransformManip();

#ifdef OIV_NET_DOC
  /**
  * Returns a @reference to the dragger being used by this manipulator. Given this
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
  * be an SoTransform node (or subclass thereof). If the path has a nodekit, this
  * will try to use setPart() to insert the manipulator. Otherwise, the
  * manipulator requires that the next to last node in the path chain be a group.
  * 
  * The field values from the transform node will be copied to this manipulator, and
  * the transform will be replaced.
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
  * be an SoTransform node (or subclass thereof). If the path has a nodekit, this
  * will try to use setPart() to insert the manipulator. Otherwise, the
  * manipulator requires that the next to last node in the path chain be a group.
  * 
  * The field values from the transform node will be copied to this manipulator, and
  * the transform will be replaced.
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
  * SoTransform node. If the path has a nodekit, this will try to use
  * setPart() to insert the new node. Otherwise, the manipulator requires
  * that the next to last node in the path chain be a group.
  * 
  * The field values from the manipulator will be copied to the transform node, and
  * the manipulator will be replaced.
  * 
  * It will not make any changes to field connections. The calling
  * process is thus responsible for keeping track of its own nodes and field
  * connections.
  */

#else
  /**
  * Replaces the tail of the path, which must be this manipulator, with the given
  * SoTransform node. If the path has a nodekit, this will try to use
  * setPart() to insert the new node. Otherwise, the manipulator requires
  * that the next to last node in the path chain be a group.
  * 
  * The field values from the manipulator will be copied to the transform node, and
  * the manipulator will be replaced.
  * 
  * The manipulator will not call ref() or unref() on the node which is
  * replacing it, nor will it make any changes to field connections. The calling
  * process is thus responsible for keeping track of its own nodes and field
  * connections.
  */

#endif //OIV_NET_DOC
  SbBool replaceManip(SoPath *p, SoTransform *newOne ) const;

 SoEXTENDER public:

  // These functions implement all actions for nodekits.
  // They first traverse the children, then use the SoTransform
  // version of the actions. They traverse first so that the transform
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
  static void initClass();  // initialize the class
  static void exitClass();

  SB_THREAD_TLS_HEADER();

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
  virtual void copyContents(const SoFieldContainer *fromFC, SbBool copyConnections);

  static void transferFieldValues( const SoTransform *from, SoTransform *to);

  static void valueChangedCB(void *,SoDragger *);

  SoFieldSensor *rotateFieldSensor;
  SoFieldSensor *translFieldSensor;
  SoFieldSensor *scaleFieldSensor;
  SoFieldSensor *centerFieldSensor;
  SoFieldSensor *scaleOrientFieldSensor;
  static void fieldSensorCB(void *, SoSensor *);

  virtual void setDragger( SoDragger *newDragger );

  SoChildList *children;
  virtual SbBool readInstance(SoInput *in, unsigned short flags);
  virtual SbBool readChildren(SoInput *in);

  virtual ~SoTransformManip();

  // Class static thread local storage
  struct MTstruct {
    SoGetBoundingBoxAction *bboxAction;
  };

  inline virtual SoNode::SoNotificationInfo * getNotificationInfo() const
  { return (SoNotificationInfo*)(&m_notificationInfo); }

 private:
  int getNumChildren() const { return (children->getLength()); }

  SoNode::SoNotificationInfo m_notificationInfo;

};    

#endif  /* _SO_TRANSFORM_MANIP_ */

