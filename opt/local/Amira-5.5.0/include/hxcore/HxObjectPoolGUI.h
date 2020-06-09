/*
Copyright 1999-2013 Visualization Sciences Group, SAS
Copyright 1995-2013, ZIB Berlin
ALL RIGHTS RESERVED.

amira(R) is a registered trademark of ZIB.

amira(R) is being jointly developed by Zuse Institute Berlin and
Visualization Sciences Group, SAS.
Avizo® is a registered trademark of Visualization Sciences Group, SAS
HardCopy, MeshViz, VolumeViz, TerrainViz are marks of Visualization
Sciences Group, SAS 
Visualization Sciences Group, SAS is a source licensee of OpenGL®, Open Inventor® 
from Silicon Graphics, Inc. OpenGL® and Open Inventor® are 
registered trademark of Silicon Graphics, Inc. All other products and 
company names are trademarks or registered trademarks of 
their respective companies. 

FEI Visualization Sciences Group accepts no liability to any 
party for loss or damage caused by errors or omissions or by 
statements of any kind in this publication, whether such errors 
result from accident, negligence or any other cause. FEI Visualization
Sciences Group assumes  no liability for incidental or consequential
damages arising from the use of information in this publication.
FEI Visualization Sciences Group provides no 
warranties regarding the information contained in this 
publication, whether expressed, implied, or statutory, including 
implied warranties of merchantability or fitness for a 
particular purpose. 

FEI Visualization Sciences Group also does not assume any liability
for links from this publication to publications from other companies,
organizations or individuals. FEI Visualization Sciences Group does not
imply endorsement of any specific  company, organization or individual
through offering links to this content.
All information provided within this publication 
is subject to change at any time and is provided for 
informational purposes only by FEI Visualization Sciences Group.
Copyright 1994-2012 by Visualization Sciences Group, SAS Merignac, France.

*/

/// @addtogroup hxcore hxcore
/// @{
#ifndef _HX_OBJECT_POOL_GUI_H
#define _HX_OBJECT_POOL_GUI_H

#include <QFrame>
#include <qpixmap.h>
#include <QScrollArea>
#include <QTimer>
#include <QDialog>

#include <mclib/McDArray.h>
#include <mclib/McVec2i.h>
#include <mclib/McTypedObject.h>
#include <hxcore/HxAmiraWinDLLApi.h>

class HxObjectPool;
class HxObjectPoolGUI;
class HxObject;
class HxConnection;
class QScrollBar;
class QListWidget;
class QHBoxLayout;
class QVBoxLayout;
class QToolButton;
class QPushButton;
class QDialog;
class QCursor;
class QMenu;
class QRubberBand;

class QxButtonContainer : public QFrame 
{
public:
    QxButtonContainer(QWidget* parent) : QFrame(parent){}
protected:
    virtual void contextMenuEvent ( QContextMenuEvent * event );
};

class QxObjectPoolContainer : public QWidget {

  public:
    QxObjectPoolContainer(HxObjectPool* pool, QWidget* parent);

    HxObjectPoolGUI* gui() { return mPool; }
    QWidget* getButtonContainer() { return mButtonContainer; }

    void updateMacroButtons();
    void updateModuleButtons();
	void deleteModuleButtons();

	inline QScrollArea * getButtonContainerScrollView() const {return sv;};
	inline QVBoxLayout * getButtonContainerScrollViewLayout() const {return layout;};

  protected:
    HxObjectPoolGUI* mPool;
    QFrame * mButtonContainer;
    QHBoxLayout* mMacroButtonLayout;
    QHBoxLayout* mModuleButtonLayout;
    McDArray<QPushButton*> mMacroButtons;
    McDArray<QPushButton*> mModuleButtons;
	QScrollArea* sv;
	QVBoxLayout* layout;
};

// Dialog which asks how unsaved objects should be saved.
// Its exec method returns QDialog::Rejected, QDialog::Accepted
// (manual save), and SaveObjectsDialog::AutoSave.
class SaveObjectsDialog : public QDialog
{
    Q_OBJECT
public:
    SaveObjectsDialog(QWidget *parent, McDArray<HxObject*>& autoSaveObjects);
    int exec();
    QListWidget* mListBox;
    QPushButton* mSaveBtn;
    static const int AutoSave = 2;
protected slots:
    void onAutoSaveBtn();
protected:
    int mResult;
};

/// This class holds all Amira data objects and modules
class HXCORE_API HxObjectPoolGUI : public QFrame
{
    Q_OBJECT

  public:
    /// Constructor
    HxObjectPoolGUI( HxObjectPool* pool, QWidget* parent ) ;

    /// Destructor
    virtual ~HxObjectPoolGUI();

    /** This method checks if Amira can be safely terminated. If there are
        unsaved data objects in the pool, a question dialog is popped up.
        If Amira can be quited or should be quited, 1 is returned. Otherwise
        0 is returned. */
    int okToQuit();

    /// Checks if auto save is ok when a network script should be written.
    int autoSaveOk(McDArray<HxObject*>& autoSaveObjects);

    /// Used by HxDynamicFileSeriesCtrl
    void emitObjectRemoved(HxObject* object);

    /** 
     * Used by HxObject.
     */
    void emitObjectRenamed(HxObject* object, const char* oldName);

    /** Used by HxBase. Emits signal polygonOffsetChanged(). This signal
        inidcates that HxBase::polygonOffsetRequired() has changed. */
    void emitPolygonOffsetChanged();

    /** 
     * To get the viewerToggleObject.
     */
    const HxObject* getViewerToggleObject() const;

    /** 
     * To get the activeViewerId flag.
     */
    int getActiveViewerId() const;

    void popup(HxObject* pop, int x,int y);
    void popup2(HxObject* pop, int x,int y);
    
    QMenu* getPoolPopupMenu() const { return poolMenu ;}

  public slots:
    /** 
    * The default popup menu available via a right button click.
    */
    void defaultRightClickPopup(const QPoint& pos);

    void setPanMode();

    void setSelectMode();

    void runMacroButton();

    // Pool menu
    void poolHide();
    void poolRemove();
    void poolDuplicate();
    void poolRename();
    void poolShowOne(QAction*);
    void poolShowAll();
    void poolRemoveAll();
    void poolPickableAll();
    void poolUnpickableAll();
    void poolDuplicateMode();
    void poolAutoAdjustRangeOfColormaps();
    void configurePoolMenu();

  signals:
    void objectAdded(HxObject* object);

    void objectRemoved(HxObject* object);

    void objectRenamed(HxObject* object, const char* old_name);

    void objectConnected(HxConnection* connection, HxObject* oldSrc);

    void objectDisconnected(HxConnection* connection, bool isDisconnectedDuringConnection, HxObject* oldConnectedObject);

    void objectSelected(HxObject* object);

    void objectDeselected(HxObject* object);

    void objectReplaced(HxObject* oldObject, HxObject* newObject);

    void objectFired(HxObject* object);

    void polygonOffsetChanged();

  protected:
    // Pointer to non-GUI object pool
    HxObjectPool* pool;

    // Indicates the object of which the popup menu was requested
    HxObject* popupSource;

    // Points to the primary module currently being dragged
    HxObject* movingObject;

    // Points to the connections currently being dragged
    McDArray<HxConnection*> movingConnections;

    // Current mouse position, set in mouse*Event(), used in redraw().
    int mx,my;

    // Optional scroll bars ...
    QRect virtualRect;
    QScrollBar* verticalScrollBar;
    QScrollBar* horizontalScrollBar;

    // The selction rectangle 
    QRubberBand *mRubberBand;

    // Shows, hides, or adjusts the scroll bars. No redraw is done.
    void adjustScrollBars();

    // Needed for drawing a box when selecting multiple objects
    McVec2i bboxCorner1;
    McVec2i bboxCorner2;
    int drawingBoundingBox;

    // Qt event handlers
    virtual void paintEvent(QPaintEvent* e);
    virtual void mousePressEvent(QMouseEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* e);
    virtual void mouseMoveEvent(QMouseEvent* e);
    virtual void keyPressEvent(QKeyEvent* e);
    virtual void leaveEvent(QEvent* e);
    virtual void resizeEvent(QResizeEvent*);
    virtual bool eventFilter(QObject*, QEvent* event);

    void wheelEvent ( QWheelEvent * event );

    int	dx,dy;
    int	isMotionCursor;
    int activeViewerId;
    HxObject* viewerToggleObject;

    QDialog* onExitDialog;
    QListWidget* onExitListBox;
    QPushButton* onExitSaveButton;

    QToolButton* mSelectBtn;
    QToolButton* mPanBtn;
    QPixmap mTrashPixmap;
    QCursor* mPanCursor;
    QCursor* mDeleteCursor;
    bool mIsPanMode;

    QMenu* poolMenu;
    QMenu* poolShowOnePopup;

    // Pool menu items
    QAction* idPoolHide;
    QAction* idPoolRemove;
    QAction* idPoolDuplicate;
    QAction* idPoolRename;
    QAction* idPoolShowAll;
    QAction* idPoolRemoveAll;
    QAction* idPoolDuplicateMode;
    QAction* idPoolAutoAdjustRangeOfColormaps;
    
    QTimer mTouchNodeTimer;
    QTimer mScrollTimer;

    // friend classes.
    friend class HxObjectPool;

  protected slots:
    void scrollBarChanged(int val);
    void popupSelected(int id);
    void popup2Selected(int id);
    void onExitSave();
    void onExitSelectionChanged();
    void touchNode();
    void autoScrollPool();
};

// ------------------------------ INLINE methods. ------------------------------
inline const HxObject*
HxObjectPoolGUI::getViewerToggleObject() const
{
  return viewerToggleObject;
}

inline int
HxObjectPoolGUI::getActiveViewerId() const
{
  return activeViewerId;
}

#endif

/// @}
