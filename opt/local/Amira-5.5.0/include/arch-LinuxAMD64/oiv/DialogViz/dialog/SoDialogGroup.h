/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/
#ifndef  _SO_DIALOG_GROUP_
#define  _SO_DIALOG_GROUP_

#include <DialogViz/dialog/SoDialogComponent.h>

class SoDialogAuditor;
class SoDialogGroupAuditor;

/**
 * @VSGEXT Abstract base class for container dialog components.
 * 
 * @ingroup Dialog
 * 
 * @DESCRIPTION
 *   This class defines the properties of the container dialog components. These
 *   containers are SoRowDialog, SoColumnDialog, and SoTabDialog.
 *
 * @SEE_ALSO
 *   SoColumnDialog,
 *   SoRowDialog,
 *   SoTabDialog
 *
 */

class DIALOGVIZ_API SoDialogGroup : public SoDialogComponent
{
  SO_DG_HEADER(SoDialogGroup);

 public:

  enum ScrollVisibility {
    /** Scroll bar never displayed */
    NEVER,
    /** Sscroll bar always visible */
    ALWAYS,
    /** Automatic scroll bar : displayed when needed (Default). */
    AUTO
  };

  /**
   * Control how vertical scrollbar appears. Default value is AUTO.
   */
  SoSFEnum vScrollVisibility;

  /**
   * Control how horizontal scrollbar appears. Default value is AUTO.
   */
  SoSFEnum hScrollVisibility;

  /**
   * Control the window sizing when a child is added or removed. If FALSE, the window is not resized; scrollbars appear if needed. Default is TRUE.
   */
  SoSFBool windowResizedByChildren;

  /**
   * Specifies the margin width. Default is zero.
   */
  SoSFInt32 margin;

  /**
   * Adds a dialogGroupAuditor to the current column component.
   */
  void addAuditor(SoDialogAuditor* auditor);

  /**
   * Removes the specified DialogGroupAuditor from the auditor list.
   */
  void removeAuditor(SoDialogAuditor* auditor);

  /**
  * Applies all DialogGroupAuditors in the auditor list.
  */
  void applyAuditors();

  /**
   * Retrieves the DialogViz object from the specified auditorID field in an SoDialogGroup
   * structure. NULL is returned if auditorID string is not found.
   */
  SoDialogViz* searchForAuditorId(SbString id);

  /**
   * Adds a child as last one in group.
   */
  virtual void addChild(SoDialogComponent *child);

  /**
   * Adds a child so that it becomes the one with the given index.
   */
  virtual void insertChild(SoDialogComponent *child, int newChildIndex);

  /**
   * Returns pointer to child node with the given index.
   */
  virtual SoNode *getChild(int index) const;

  /**
   * Returns number of children.
   */
  virtual int getNumChildren() const;

  /**
   * Finds index of given child within group. Returns -1 if not found.
   */
  virtual int findChild(const SoDialogComponent *child) const;

  /**
   * Removes child with given index from group.
   */
  virtual void removeChild(int index);

  /**
   * Removes first instance of given child from group.
   */
  virtual void removeChild(SoDialogComponent *child);

  /**
   * Removes all children from group.
   */
  virtual void removeAllChildren();

  /**
   * Replaces child with given index with new child.
   */
  virtual void replaceChild(int index, SoDialogComponent *newChild);

  /**
   * Replaces first instance of given child with new child.
   */
  virtual void replaceChild(SoDialogComponent *oldChild, SoDialogComponent *newChild);

/*==============================================================================*/
SoINTERNAL public:
  virtual SoChildList *getChildren() const;

  virtual void   buildWidget(SoWidget parent, SbVec2i32 & rSize, SbVec2i32 & pos, SbBool isActive2d);
  static  void   initClass();
  static  void   exitClass();
  virtual void   updateFromSensor(SoSensor* sensor);
          SbBool isVScrollVisible() {return m_vScrollVisible;};
          void   updateAfterSceneGraphChange();
  virtual void   resetSize();
  virtual void   destroyWidget();

  // Internal child management following inheritance of classes.
  virtual void internalRemoveChild( int index )                          { removeChild(index); }
  virtual void internalRemoveChild( SoNode *child  )                     { removeChild(internalFindChild(child)); }
  virtual void internalRemoveAllChildren()                               { removeAllChildren(); }
  virtual void internalAddChild( SoNode *child );
  virtual int internalFindChild( const SoNode *child ) const;
  virtual void internalInsertChild( SoNode *child, int newChildIndex );
  virtual SoNode *internalGetChild( int index) const                     { return getChild(index); }
  virtual void internalReplaceChild( int index, SoNode *newChild);
  virtual void internalReplaceChild( SoNode *oldChild, SoNode *newChild) { replaceChild(dynamic_cast<SoDialogComponent*>(oldChild),dynamic_cast<SoDialogComponent*>(newChild) ); }

protected:

  // Reads stuff into instance of SoGroup. Returns FALSE on error
  virtual SbBool readInstance(SoInput *in, unsigned short flags);
  
  // Reads just the children into instance of SoGroup. Returns FALSE on error
  virtual SbBool readChildren(SoInput *in);
  
  int        m_arrayNumChildren;
  SbVec2i32* m_childrenMin;
  SbVec2i32* m_childrenMax;
  SbVec2i32* m_childrenSize;
  int        m_cptToResize;
  SbBool     m_hScrollVisible;
  SbBool     m_vScrollVisible;
  SoWidget     m_groupWidget;
  SoWidget     m_horzSBXt;
  SoWidget     m_vertSBXt;
  int m_numberOfChildren;
  SbBool     m_firstBuild;

  SoDialogGroup();
  virtual           ~SoDialogGroup();
  virtual void      fixSizeWithBorder(SbVec2i32 &size, int revert = 1);
  virtual SbVec2i32 getLabelInitSize();
  virtual SbVec2i32 getComponentInitSize();

  virtual void      getSize(SbVec2i32 &size, SbVec2i32 &min, SbVec2i32 &max);
  virtual void      setChildrenComponentSize() {};
  virtual void      setChildrenLabelSize() {};
  virtual void      setComponentSize(SbVec2i32& size);
  virtual void      setLabelSize(SbVec2i32& size);
          void      setScrollProperties();
          void      updateGroupWidgetScrollPosition();
          void      updateChildrenSizeDB();

  virtual void changeEnable();
  virtual void changeWidgetEnable(SbBool state);

          void resetChangedStatus();  // Notified changes

  // Details of change (only valid during notification)
  SoNode*                  changedChild;
  int                      changedIndex;
  SoDataSensor::ChangeType changeType;

private: 

          void createGroupWidget(SbVec2i32 & rSize, SbVec2i32 & pos);
  virtual void applyAuditor(SoDialogViz* dlgCpt);


  SoDialogGroupAuditor* m_defaultAuditor;

///////////////////////////////////////////////////////////////////////////////////////
// 3D methods
SoINTERNAL public:
  virtual void show3D(SbBool show);
  virtual void change3DPosition();
  virtual void change3DEnable();
  virtual void change3DWidgetEnable(SbBool state);

///////////////////////////////////////////////////////////////////////////////////////
SoEXTENDER public:
  virtual void getBoundingBox(SoGetBoundingBoxAction* action);
  virtual void rayPick(SoRayPickAction *action);
  virtual void search(SoSearchAction *action);
  virtual void write(SoWriteAction *action);

///////////////////////////////////////////////////////////////////////////////////////

};

#endif // _SO_DIALOG_GROUP_
