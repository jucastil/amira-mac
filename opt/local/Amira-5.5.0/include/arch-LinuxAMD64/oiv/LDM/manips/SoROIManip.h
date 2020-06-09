/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : P. ESTRADE (Jul 2002)
** Modified by : T.DUFOUR (MMM yyyy)
**=======================================================================*/

/* include files */
#ifndef  _SO_ROI_MANIP_
#define  _SO_ROI_MANIP_

#include <Inventor/draggers/SoDragger.h>
#include <LDM/nodes/SoROI.h>

class SoOneShotSensor;
class SoState;

/*----------------------------------------------------------------------------*/

/**
  * @LDMEXT Manipulator to transform an ROI (Region of Interest).
  * 
  * @ingroup LDMManips
  * 
  * @DESCRIPTION
  *   This class defines a manipulator to transform an ROI. An SoTabBoxDragger
  *   allows the user to move and resize the ROI.
  * 
  * @FILE_FORMAT_DEFAULT
  *    ROIManip {
  *    @TABLE_FILE_FORMAT
  *		    @TR subVolume	  @TD 0 0 0 0 0 0
  *       @TR box         @TD 0 0 0 1 1 1
  *       @TR flags       @TD 7
  *		    @TR relative	  @TD FALSE
  *       @TR boxOn			  @TD TRUE
  *       @TR constrained @TD FALSE
  *    @TABLE_END
  *    }
  * 
  * @SEE_ALSO
  *    SoROI,
  *    SoDragger
  * 
  * 
  */

class LDM_API SoROIManip : public SoROI {
  
  SO_NODE_HEADER(SoROIManip) ;
  
public:
  /**
   * Constructor.
   */
  SoROIManip() ;
  
  // Fields
  /**
   * Chooses between the #box (TRUE) or the #subVolume (FALSE) in the SoROI.
   * Default value is TRUE.
   */
  SoSFBool boxOn;
  
  /**
   * Constrains the dragger to fit in the data volume. Default value is FALSE.
   */
  SoSFBool constrained;

  /**
   * Returns the dragger node being employed by this manip.
   */
  SoDragger *getDragger() ;
  
#ifdef OIV_NET_DOC
  /**
  * Replaces the tail of the path with this manipulator. The tail of the path must
  * be an SoROI node (or subclass thereof). If the path has a nodekit,
  * this will try to use setPart() to insert the manipulator. Otherwise, the
  * manipulator requires that the next-to-last node in the path chain be a group.
  * 
  * The field values from the ROI node will be copied to this
  * manipulator, and the ROI node will be replaced.
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
  * be an SoROI node (or subclass thereof). If the path has a nodekit,
  * this will try to use setPart() to insert the manipulator. Otherwise, the
  * manipulator requires that the next-to-last node in the path chain be a group.
  * 
  * The field values from the ROI node will be copied to this
  * manipulator, and the ROI node will be replaced.
  * 
  * The manipulator will not call ref() on the node it is replacing. The old
  * node will disappear if it has no references other than from the input path p and
  * its parent, since this manipulator will be replacing it in both of those places.
  * Nor will the manipulator make any changes to field connections of the old node.
  * The calling process is thus responsible for keeping track of its own nodes and
  * field connections.
  */

#endif //OIV_NET_DOC
  SbBool replaceNode(SoPath *p) ;
  
#ifdef OIV_NET_DOC
  /**
  * Replaces the tail of the path, which must be this manipulator, with the given
  * SoROI node. If the path has a nodekit, this will try to use
  * setPart() to insert the new node. Otherwise, the manipulator requires
  * that the next-to-last node in the path chain be a group.
  * 
  * The field values from the manipulator will be copied to the ROI
  * node, and the manipulator will be replaced.
  * 
  * It will not make any changes to field connections. The calling
  * process is thus responsible for keeping track of its own nodes and field
  * connections.
  */

#else
  /**
  * Replaces the tail of the path, which must be this manipulator, with the given
  * SoROI node. If the path has a nodekit, this will try to use
  * setPart() to insert the new node. Otherwise, the manipulator requires
  * that the next-to-last node in the path chain be a group.
  * 
  * The field values from the manipulator will be copied to the ROI
  * node, and the manipulator will be replaced.
  * 
  * The manipulator will not call ref() or unref() on the node which is
  * replacing it, nor will it make any changes to field connections. The calling
  * process is thus responsible for keeping track of its own nodes and field
  * connections.
  */

#endif //OIV_NET_DOC
  SbBool replaceManip(SoPath *p, SoROI *newOne) const;
  
SoINTERNAL public:
  // These functions implement all actions for this manip.
  // They first traverse the children, then use the 
  // SoROI version of the actions. They traverse first 
  // so that the SoROI will affect objects which 
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
  
protected:
  // When the dragger moves, this interprets the fields modifications 
  // of the dragger and sets the fields of this SoROI accordingly
  static void valueChangedCB(void *,SoDragger *);
  
  // When one of the field of this node changes, moves the
  // child-dragger to a new location, if necessary.
  SoFieldSensor *m_boxOnSensor;
  SoFieldSensor *m_boxFieldSensor;
  SoFieldSensor *m_subVolumeFieldSensor;
  SoFieldSensor *m_relativeFieldSensor; 
  SoOneShotSensor *m_wasInitSensor; 
  
  static void fieldSensorCB(void *, SoSensor *);
  static void oneShotSensorCB(void *, SoSensor *);
  
  // Establishes the given dragger as the new child-dragger
  void setDragger(SoDragger *newDragger);
  
  // The hidden children.
  SoChildList *m_children;
  virtual SbBool readInstance(SoInput *in, unsigned short flags);
  virtual SbBool readChildren(SoInput *in);
  
  // Destructor
  virtual ~SoROIManip();
  
private:
  SbVec3i32 m_dimension;
  SbBox3f m_size;
  SbBool  m_init;
  SbVec3i32 m_boxmin, m_boxmax;

  
  static void dataToGeometry( const SbVec3i32 &, const SbVec3i32 &, SbVec3f &, SbVec3f &, const SoROIManip * );
  static void geometryToData( const SbVec3f &, const SbVec3f &, SbVec3i32 &, SbVec3i32 &, const SoROIManip *, bool );

  int getNumChildren() const { return (m_children->getLength()); }
  void initBox(SoAction* action);

  bool hasVolumeDataSizeChanged(SoState *state);
} ;
/*----------------------------------------------------------------------------*/

#endif /* _SO_ROI_MANIP_  */
