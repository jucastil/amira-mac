/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Feb 1997)
**=======================================================================*/

                                                             /* include files */
#ifndef  _SO_CLIP_PLANE_MANIP_
#define  _SO_CLIP_PLANE_MANIP_

#include <Inventor/draggers/SoDragger.h>
#include <Inventor/nodes/SoClipPlane.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/fields/SoSFVec3f.h>

/*----------------------------------------------------------------------------*/

/**
 * @VSGEXT Manipulator to transform a clipping plane.
 * 
 * @ingroup manips
 * 
 * @DESCRIPTION
 *   This class defines a manipulator to transform a clipping plane. An SoJackDragger
 *   allows the user to rotate and translate the clipping plane.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ClipPlaneManip {
 *    @TABLE_FILE_FORMAT
 *       @TR plane             @TD 1 0 0 0
 *       @TR on                @TD TRUE
 *       @TR draggerPosition   @TD 0 0 0
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoClipPlane,
 *    SoDragger
 * 
 * 
 */ 

class INVENTOR_API SoClipPlaneManip : public SoClipPlane {
  
  SO_NODE_HEADER(SoClipPlaneManip) ;

 public:
  /**
   * Constructor.
   */
  SoClipPlaneManip() ;

  // Fields
  /**
   * Dragger position.
   * 
   */
  SoSFVec3f draggerPosition ;

  /**
   * Returns the dragger node being employed by this manip.
   */
  SoDragger *getDragger() ;

  virtual SoNode *copy(SbBool copyConnections = FALSE) const;

  /**
   * Convenience method to set the clip plane passing through the center of a
   * bounding box (defined by the parameter @B box @b) and oriented by a normal
   * (defined by the parameter @B planeNormal @b). The size of the dragger is the
   * max size of the bounding box multiplied by a factor (defined by the parameter
   * @B draggerScaleFactor @b).
   */
  void setValue(const SbBox3f &box, const SbVec3f &planeNormal, float draggerScaleFactor) ;

  /**
   * Replaces a regular SoClipPlane node with this manipulator.
   */
  SbBool replaceNode(SoPath *p) ;

  /**
   * Replaces this manipulator with a regular SoClipPlane node.
   */
  SbBool replaceManip(SoPath *p, SoClipPlane *newOne) const;

 SoINTERNAL public:
  // These functions implement all actions for this manip.
  // They first traverse the children, then use the 
  // SoClipPlane version of the actions. They traverse first 
  // so that the SoClipPlane will affect objects which 
  // follow it in the tree, but not the dragger-child.
  virtual void doAction(SoAction *action);
  virtual void callback(SoCallbackAction *action);
  virtual void GLRender(SoGLRenderAction *action);
  virtual void getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void getMatrix(SoGetMatrixAction *action);
  virtual void handleEvent(SoHandleEventAction *action);
  virtual void pick(SoPickAction *action);
  virtual void search(SoSearchAction *action);
  virtual void write( SoWriteAction *action );

  // call this after SoInteraction::init();
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
  // When the dragger moves, this interprets the fields modifications 
  // of the dragger and sets the fields of this SoClip plane accordingly
  static void valueChangedCB(void *,SoDragger *);
  
  // When one of the field of this node changes, moves the
  // child-dragger to a new location, if necessary.
  SoFieldSensor *planeFieldSensor ;
  SoFieldSensor *onFieldSensor ;
  SoFieldSensor *draggerPosFieldSensor ;
  static void fieldSensorCB(void *, SoSensor *);
  
  // Establishes the given dragger as the new child-dragger
  void setDragger(SoDragger *newDragger);
  
  // The hidden children.
  SoChildList *children ;
  virtual SbBool readInstance(SoInput *in, unsigned short flags);
  virtual SbBool readChildren(SoInput *in);

  // Destructor
  ~SoClipPlaneManip();

  inline virtual SoNode::SoNotificationInfo * getNotificationInfo() const
  { return (SoNotificationInfo*)(&m_notificationInfo); }

 private:
  SbVec3f projectPointPlane() const ;

  int getNumChildren() const { return (children->getLength()); } 

  SoNode::SoNotificationInfo m_notificationInfo;

} ;
/*----------------------------------------------------------------------------*/

#endif /* _SO_CLIP_PLANE_MANIP_  */

