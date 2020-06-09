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
#ifndef QXTIMELINEWIDGET_H
#define QXTIMELINEWIDGET_H

#include "hxdemodirector/QxItem.h"
#include "hxdemodirector/ui_QxTimelineWidget.h"
#include "hxdemodirector/ui_QxNewEventDialog.h"
#include "hxdemodirector/ui_QxPlayDialogBase.h"

#include <QString>

// Forward declarations
class QTreeWidgetItem;
class HxDemoDirector;

namespace hxdemodirector
{

/**
 The TimelineWidget is a GUI for the Demo Maker. It combines a \see{Timeline} with control buttons
 like stop, play, ... and a tree widget which contains all available Demo Maker events. A instance of the 
 class \see{HxDemoDirector} provides the interaction between this class and a Demo Maker.
*/
class QxTimelineWidget : public QWidget
{
    Q_OBJECT

public:
    QxTimelineWidget(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~QxTimelineWidget();

    /// Connects the widget with HxDemoDirector.
    void setDemoDirector(HxDemoDirector *demoDirector);

    /// Adds a demo maker numeric event.
    void addNumericEvent(int id, const QString &groupName, const QString &eventName, qreal begin, qreal end, qreal startValue, qreal endValue);
    /// Adds a demo maker toggle event.
    void addToggleEvent(int id, const QString &groupName, const QString &eventName, qreal time, bool toggleTo);
    /// Adds a demo maker select event.
    void addSelectEvent(int id, const QString &groupName, const QString &eventName, qreal time, int newValue, int oldValue);
    /// Adds a demo maker button event.
    void addButtonEvent(int id, const QString &groupName, const QString &eventName, qreal time, bool shiftPressed, bool ctrlPressed, bool altPressed);
    /// Adds a demo maker command event.
    void addCommandEvent(int id, const QString &eventName, qreal begin, qreal end, const QString &startValue, const QString &endValue);
    /// Adds a demo maker break event.
    void addBreakEvent(int id, qreal time);
    /// Adds a demo maker pause event.
    void addPauseEvent(int id, qreal begin, qreal end);
    /// Adds a demo maker goto event.
    void addGotoEvent(int id, qreal time, qreal gotoTime);
    
    /// Removes an event.
    void removeEvent(int id);
    /// Removes all events.
    void clearEvents();
    
    /// Calculates a scaling that shows all events and uses the available space best.
    void setOptimalScaling();
    /// Forces the calculation of an optimal scaling at the next painting.
    void invalidateScaling();

    /// Adds a global event to the list of available events.
    void addAvailableEvent(int id, const QString &eventName);
    /// Adds an event to the list of available events.
    void addAvailableEvent(int id, const QString &moduleName, const QString &eventName);
    /// Adds an event to the list of available events.
    void addAvailableEvent(int id, const QString &moduleName, const QString &portName, const QString &eventName);
    
    /// Clears the list of available events.
    void clearAvailableEvents();

    /// Sets the current time.
    void setCurrentTime(qreal curTime);
    
    /// Sets the flag which indicates the playing direction.
    void setForwardFlagChanged(int flag);
    
    /// Sets the flag which indicates the current animation state (running/stopped).
    void setAnimationStateChanged(int flag);

    /// Update the properties of a numeric event.
    void changeNumericEvent(int id, qreal start, qreal end, qreal startValue, qreal endValue);
    /// Update the properties of a toggle event.
    void changeToggleEvent(int id, qreal time, bool toggleTo);
    /// Update the properties of a select event.
    void changeSelectEvent(int id, qreal time, int newValue, int oldValue);
    /// Update the properties of a button event.
    void changeButtonEvent(int id, qreal time, bool shiftPressed, bool ctrlPressed, bool altPressed);
    /// Update the properties of a command event.
    void changeCommandEvent(int id, const QString &command, qreal begin, qreal end, const QString &startValue, const QString &endValue);
    /// Update the properties of a break event.
    void changeBreakEvent(int id, qreal time);
    /// Update the properties of a pause event.
    void changePauseEvent(int id, qreal start, qreal duration);
    /// Update the properties of a goto event.
    void changeGotoEvent(int id, qreal start, qreal gotoTime);
    /// Change the ID of an event.
    void changeEventId(int oldId, int newId);
    /// Changes the left and right boundary.
    void changeBoundaries(float left, float right);
    
    /// Sends a command string to HxDemoDirector.
    const char* sendCmd(const QString &string, bool setDirtyFlag) const;

public slots:
    /// The new event button was clicked.
    void newEventBtnClicked();
    /// The update event list button was clicked.
    void updateEventListBtnClicked();
    /// An available event was selected via a double click.
    void newEventDoubleClicked(QTreeWidgetItem * item, int column);
    /// The zoom in button was clicked.
    void zoomInBtnClicked();
    /// The zoom out button was clicked.
    void zoomOutBtnClicked();
    /// The overview button was clicked.
    void overview();
    /// The jump backward button was clicked.
    void jumpBackwardBtnClicked();
    /// The play backward button was clicked.
    void playBackwardBtnClicked();
    /// The step backward button was clicked.
    void stepBackwardBtnClicked();
    /// The step forward button was clicked.
    void stepForwardBtnClicked();
    /// The play forward button was clicked.
    void playForwardBtnClicked();
    /// The jump forward button was clicked.
    void jumpForwardBtnClicked();

    /// (In-)validates the event template list flag.
    void setEventTemplateListValid(bool valid);

protected:
    /// Prompts the Demo Maker to update the event template list.
    void initiateEventListUpdate();

protected slots:
    void playMenuAboutToShow();
    void playMenuTriggered(QAction *action);
private:

    enum PlayDirection {Backward, Forward}; ///< The current playing direction.
    enum AnimationState {Stopped, Running}; ///< The current animation state.
    enum PlayMode {Once, Loop, Swing};      ///< The current play mode.

    /// Tries to find a matching module entry in the tree widget. Creates one otherwise.
    QTreeWidgetItem *getTreeModuleItem(const QString &moduleName);
    /// Tries to find a matching port entry in the tree widget. Creates one otherwise.
    QTreeWidgetItem *getTreePortItem(const QString &portName, QTreeWidgetItem *parentModuleItem);
    /// Creates an item in the tree widget.
    QTreeWidgetItem *createTreeEventItem(int id, const QString &eventName, QTreeWidget *parent);
    /// Creates an item as sub item in the tree widget.
    QTreeWidgetItem *createTreeEventItem(int id, const QString &eventName, QTreeWidgetItem *parent);
 
    /// Updates the play/stop buttons.
    void updateButtons();

    /// Creates a string representation of the given play mode.
    QString createPlayModeSwitch(PlayMode playMode) const;

    QIcon *mIconJumpBwd;
    QIcon *mIconPlayBwd;
    QIcon *mIconStepBwd;
    QIcon *mIconStepFwd;
    QIcon *mIconPlayFwd;
    QIcon *mIconJumpFwd;
    QIcon *mIconStop;
    QIcon *mIconZoomIn;
    QIcon *mIconZoomOut;

    QAction *mPlayOnceAction;
    QAction *mLoopAction;
    QAction *mSwingAction;
    QAction *mConfigureAction;

    QDialog *mNewEventDialog;
    QTreeWidget *mTreeWidget;
    QDialog *mPlayMenuDialog;

    Ui::TimelineWidget ui;
    Ui::Dialog mUiNewEventDialog;
    Ui::PlayDialogBase mUiPlayDialog;

    HxDemoDirector *mDemoDirector;

    PlayDirection mPlayDirection;
    AnimationState mAnimationState;
    PlayMode mPlayMode;

    bool mEventListValid; ///< The event list in the tree widget needs to be recreated.
};

} // namespace timeline

#endif // QXTIMELINEWIDGET_H

/// @}
