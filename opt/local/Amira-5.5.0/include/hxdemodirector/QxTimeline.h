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

/// @addtogroup hxdemodirector hxdemodirector
/// @{
#ifndef QXTIMELINE_H
#define QXTIMELINE_H

#include "hxdemodirector/QxGroupItem.h"

#include <QWidget>
#include <QBrush>
#include <QObject>

// Qt forward declarations
class QRubberBand;
class QScrollBar;
class QTimer;

namespace hxdemodirector
{

class QxTimelineControlItem;
class QxTimelineWidget;

/**
 This class displays and manages a timeline and its events. Usually a timeline object is part
 of a \see{TimelineWidget}. A timeline always contains left and right boundary events and a
 current time event which cannot be deleted. Events can be accessed via a uniqe ID. 
 A timeline has two coordinate systems: a logical coordinate system for the event positions 
 and durations and a device coordinate system for the visualization. The mapping is done via
 selection and translation methods.
*/
class QxTimeline : public QWidget, public QxGroupItem
{
    Q_OBJECT
public: 
    QxTimeline(QWidget *parent = 0, Qt::WFlags flags = 0);
    virtual ~QxTimeline();

    /// Paints the timeline with all events and a scale.
    virtual void paint(QPainter &painter) const;
    virtual QPointF getClosestSnapPos(const QPointF &pos, const QList<Selection> &selections) const;
    
    /// Via this method timeline events can change the cursor's shape.
    virtual void setCursor(const QCursor &cursor);
    
    /// Passes a command string to the timeline's parent.
    virtual const char* sendCmd(const QString &command, bool setDirtyFlag) const;
    
    /// Returns the item with the leftmost left border.
    QxItem* getLeftmostItem(bool ignoreFloatingItems=false, bool ignoreTimelineControls=true);
    /// Returns the item with the rightmost right border.
    QxItem* getRightmostItem(bool ignoreFloatingItems=false, bool ignoreTimelineControls=true);
    
    /// Creates a selection (see \see{GroupItem::createSelections}). The timeline controls are 
    /// handled in a special way so that they are always selected first in case of ambiguities.
    virtual QList<Selection> createSelections(const QPointF &pos);
    
    // Group stuff
    /// Adds an arbitrary item. Usually the methods add*Event should be used instead.
    virtual void addItem(QxItem *item);
    /// Adds a demo maker numeric event.
    void addNumericEvent(int id, const QString &groupName, const QString &eventName, qreal begin, qreal end, qreal startValue, qreal endValue);
    /// Adds a demo maker toggle event.
    void addToggleEvent(int id, const QString &groupName, const QString &eventName, qreal time, bool toggleTo);
    /// Adds a demo maker select event.
    void addSelectEvent(int id, const QString &groupName, const QString &eventName, qreal time, int newValue, int oldValue);
    /// Adds a demo button event.
    void addButtonEvent(int id, const QString &groupName, const QString &eventName, qreal time, bool shiftPressed, bool ctrlPressed, bool altPressed);
    /// Adds a demo maker command event.
    void addCommandEvent(int id, const QString &eventName, qreal begin, qreal end, const QString &startValue, const QString &endValue);
    /// Adds a demo maker break event.
    void addBreakEvent(int id, qreal time);
    /// Adds a demo maker pause event.
    void addPauseEvent(int id, qreal begin, qreal duration);
    /// Adds a demo maker goto event.
    void addGotoEvent(int id, qreal time, qreal gotoTime);
    
    // Update event properties
    /// Update the properties of a numeric event.
    void changeNumericEvent(int id, qreal start, qreal end, qreal startValue, qreal endValue);
    /// Updates the properties of a toggle event.
    void changeToggleEvent(int id, qreal time, bool toggleTo);
    /// Updates the properties of a select event.
    void changeSelectEvent(int id, qreal time, int newValue, int oldValue);
    /// Updates the properties of a button event.
    void changeButtonEvent(int id, qreal time, bool shiftPressed, bool ctrlPressed, bool altPressed);
    /// Updates the properties of a command event.
    void changeCommandEvent(int id, const QString &command, qreal begin, qreal end, const QString &startValue, const QString &endValue);
    /// Updates the properties of a break event.
    void changeBreakEvent(int id, qreal time);
    /// Updates the properties of a pause event.
    void changePauseEvent(int id, qreal start, qreal duration);
    /// Updates the properties of a goto event.
    void changeGotoEvent(int id, qreal start, qreal gotoTime);
    /// Changes the ID of an event.
    void changeEventId(int oldId, int newId);
    
    /// Sets the current time.
    void setCurrentTime(qreal curTime, bool longJump=false);
    /// Jumps the current time to the left boundary or leftmost object.
    /// Returns the jump destination.
    qreal jumpCurrentTimeToLeft(bool ignoreLeftBoundary);
    /// Jumps the current time to the right boundary or rightmost object.
    /// Returns the jump destination.
    qreal jumpCurrentTimeToRight(bool ignoreRightBoundary);
    /// Moves to the left boundary or leftmost object.
    /// Returns the jump destination.
    qreal jumpGUIToLeft(bool ignoreLeftBoundary);
    /// Moves to the right boundary or rightmost object.
    /// Returns the jump destination.
    qreal jumpGUIToRight(bool ignoreRightBoundary);
    /// Changes the left and right boundary.
    void changeBoundaries(float left, float right);
    
    /// Removes an event.
    void removeEvent(int id);
    /// Removes all events (except left/right boundary and current time).
    virtual void clear();
    
    // Dependent qt widgets
    void setParentWidget(QxTimelineWidget *widget);
    /// Announce a vertical scroll bar to the timeline.
    void setVertScrollBar(QScrollBar *scrollBar);
    
    /// Arrange all (non-floating) items so that they are not intersecting each other.
    virtual void arrange();
    /// Recalculate height of this group.
    virtual void reheight();
    
    // Scaling/zooming stuff
    /// Returns the current scaling factor between the logical and the device coordinate system.
    QPointF getScaling() const;
    /// Sets the scaling factor between the logical and the device coordinate system. 
    void setScaling(const QPointF &scaling);
    /// Sets the scaling factor between the logical and the device coordinate system. 
    void setScaling(qreal xFactor, qreal yFactor);
    /// Returns the current left/upper corner of the visible area (in device coordinates).
    QPointF getTranslation() const;
    /// Sets the left/upper corner of the visible area (in device coordinates).
    void setTranslation(const QPointF &translation);
    /// Sets the left/upper corner of the visible area (in device coordinates).
    void setTranslation(qreal xPos, qreal yPos);
    /// Changes the scaling by a factor.
    void zoom(qreal xFactor, qreal yFactor);
    
    /// Calls \see{GroupItem::geometryChanged} and adapts the vertical scroll bar accordingly.
    void geometryChanged();
    /// Calculates a scaling that shows all events and uses the available space best.
    void setOptimalScaling();
    /// Forces the calculation of an optimal scaling at the next painting.
    void invalidateScaling();

public slots:
    /// Scrolls vertically.
    void setVerticalScroll(int yPos);
    /// Scrolls a bit to the left. Is used with a timer in order to implement autoscrolling.
    void autoScrollLeft();
    /// Scrolls a bit to the right. Is used with a timer in order to implement autoscrolling.
    void autoScrollRight();

    /// Sends a command string with the current time. Is used with a timer in order to update
    /// the visualization at a regularly basis while dragging the current time slider.
    void updateCurTime();

    /// Activates/deactivates the overview mode whic show all items simultaneously.
    void setOverviewMode(bool active);

    /// Enables/disables the timeline widget.
    void setEnabled(bool enabled);

protected:
    /// Mode for mouse dragging
    enum DragMode {None, MoveSelection, MoveTimeline, RubberBand};

    /// Finds a Groupitem by name. Creates a new group if no one with the given name exists.
    QxGroupItem *findOrCreateGroup(const QString &groupName);

    // Qt events
    virtual void paintEvent(QPaintEvent *paintEvent) ;
    virtual void mousePressEvent(QMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QMouseEvent *mouseEvent, bool autoScrolling);
    virtual void mouseReleaseEvent(QMouseEvent *mouseEvent);
    virtual void resizeEvent(QResizeEvent *resizeEvent);
    virtual void changeEvent(QEvent *changeEvent);
    virtual void keyPressEvent(QKeyEvent *keyEvent);
    virtual bool event(QEvent *qEvent);

    /// Adapts the vertical scroll bar to the current timeline's height.
    void updateVertScrollBar();

    /// Tests whether the mouse cursor is at the left or right border and initiates scrolling.
    void initiateAutoScroll(QMouseEvent *mouseEvent);
    void paintBackground(QPainter &painter) const;

    void showSelections();
    void hideSelections();
    void removeSelectedItems();

    /// Determines a pleasing step size for the scale.
    void calcScaleStepSize();
    /// Determines a scaling which shows all events simultaneously.
    void calcOverviewScaling();

    Transform mTrans; ///< Transformation between logical and device coordinate system.

    // selection
    QRubberBand *mRubberBand;     ///< Rubber band while creating a selection.
    QRectF mSelectionArea;        ///< Current selection area.
    QPointF mDragStartPos;        ///< Positions where the mouse dragging starts.
    QList<Selection> mSelections; ///< Currently selected items.

    // auto scroll stuff
    QTimer *mAutoScrollTimer;           ///< Initiates the next auto scroll step.
    int mAutoScrollStepSize;            ///< Step size for auto scrolling.
    QMouseEvent *mAutoScrollMouseState; ///< Mouse state which should be used for the next auto scroll step.

    QTimer *mCurTimeUpdateTimer; ///< Timer for delayed update of curTime while dragging it.

    QList<QxItem*> mTimelineControls;          ///< List of pointers to the left/right boundary and current time item.
    QxTimelineControlItem *mLeftBoundaryCtrl;  ///< Left boundary item.
    QxTimelineControlItem *mRightBoundaryCtrl; ///< Right boundary item.
    QxTimelineControlItem *mCurTimeCtrl;       ///< Current time item.

    DragMode mDragMode;  ///< Current dragging mode.

    int mHeight; ///< Needed height for the timeline.

    QScrollBar *mVertScrollBar; ///< Pointer to a vertical scroll bar
    QxTimelineWidget *mWidget;    ///< Pointer to the parent widget.

    QMenu *mContextMenu;         ///< Context menu containing a "Remove event" entry.
    QAction *mRemoveItemAction;  ///< Action for removing an event.

    qreal mScaleStepSize;        ///< Distance between scale tick marks.
    bool mExtraTickMarks;        ///< Paint extra tick marks without numbers between the regular tick marks.

    QPointF mCurScaling;      ///< Stores previous scaling while in overview mode.
    QPointF mCurTranslation;  ///< Stores previous translation while in overview mode.

    bool mOverviewMode; ///< Currently in overview mode?
    bool mScalingValid; ///< Should the scaling be recalculated before the next painting?

    // Constants for the visualization
    static const int mRulerAreaHeight = 25;     ///< Height of the ruler.
    static const int mAutoScrollArea = 50;      ///< Area in which auto scrolling should be activated.
    static const int mAutoScrollInterval = 50;  ///< Repitition rate for auto scrolling.
    static const int mAutoScrollDivider = 5;    ///< Divider for calculating the auto scroll step size.
};

} // namespace hxdemodirector

#endif // QXTIMELINE_H

/// @}
