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
#ifndef HX_WORK_AREA_H
#define HX_WORK_AREA_H

#include <hxcore/HxAmiraWinDLLApi.h>
#include <hxcore/ProgressReceiverIface.h>

#include <mclib/McInterface.h>
#include <mclib/McProgressInterface.h>
#include <mclib/McDArray.h>
#include <mclib/McString.h>

class McProgressNode;
class QWidget;
class QScrollArea;
class QxStopButton;
class QResizeEvent;
class QVBoxLayout;
class QCheckBox;
class QPushButton;

class HxPort;
class HxPortDoIt;
class HxObject;
class QxProgressBar;
class QxToolButton;
class QxWorkAreaFramePrivate;
class HxPreferences;
class QxWorkAreaNotifier;

class HxWorkArea;

namespace WorkAreaIfaceNamespace {

class HXCORE_API ProgressReceiverIfaceImpl : public ProgressReceiverIface
{
    Q_OBJECT
public:
    ProgressReceiverIfaceImpl(HxWorkArea *workArea);
    ~ProgressReceiverIfaceImpl();
private:
    virtual void doStartWorkingNoStop(QString const &text);
    virtual void doStartWorking(QString const &text);
    virtual void doStopWorking(bool);
    virtual void doSetProgressValueGlobal(float percentDone);
    virtual void doSetProgressInfo(QString const &text);
    virtual void doSetInterruptible(bool);
    virtual void doDisconnect() {emit sigDisconnect(this);}

    virtual void doCancel() {emit sigCancel();}
    virtual void doSuspend() {}
    virtual void doResume() {}

    HxWorkArea *mWorkArea;
};

} // namespace

/** This class displays the ports of an object and provides a progress bar.
    For most developers only the progress interface of the work area will
    be of interest. The work area can be accessed via the global pointer
    theWorkArea. Derived from McProgressInterface @c theWorkArea
    can be passed as an argument to certain compute intensive routines
    defined in mclib.

    A mechanism for subdividing the progress bar for multiple consequtive actions
    is added. A progress bar can be recursively subdivided into subranges by the command
    @subdivide . Then each pair of @stopWorking and @startWorking addresses the progress
    bar within a subrange. After all sub-tasks have terminated, it must be followed by an
    @undivide command.
    The resulting structure is a tree of intervals. When busy, the progress has one active subrange
    as a leaf. The command @stopWorking automatically moves to the next sub-range.

    Example: We split the progress interval into two equal intervals and run a subtask in each of the intervals.
    \code

    HxWorkArea *progress = theWorkArea;

    int i;

    progress->subdivide(2);
    progress->startWorking("Do first task");

    // first task
    for (i=0; i<10; i++)
        progress->setProgressValue( i / 10.0);

    progress->stopWorking(); //Finish first task and move to next progress interval

    progress->startWorking("Do second task");

    // 2nd task
    for (i=0; i<10; i++)
        progress->setProgressValue( i / 10.0);

    progress->stopWorking();

    progress->undivide();

    \endcode

    */
class HXCORE_API HxWorkArea : public McInterface, public McProgressInterface
{
    MC_ABSTRACT_HEADER(HxWorkArea);
  public:
    /** Constructor. The work area itself will be created as a child of
        @c parent. The progress bar will be created as a child of @c frame. */
    HxWorkArea(QWidget* parent, QWidget* frame);

    /// Destructor
    virtual ~HxWorkArea();

    // Shows a port.
    void show(HxPort* port);

    // Hides a port.
    void hide(HxPort* port);

    /** Updates the work area. This method is called after objects are
        selected or deselected or after ports are shown or hidden. In some
        cases it may be necessary to call this method directly from an
        object itself, for example if ports should be shown or hidden from
        an Inventor callback instead from the ordinary
        HxObject::update or HxObject::compute. */
    void update();

    /// This is the parent widget for all the ports.
    QWidget* viewport();

    /// Move scroll bar so that last object gets visible.
    void scrollToBottom();

    /**@name Progress bar interface. */
    //@{

    /** Activates the busy cursor. Should be used for computations taking
        only a few seconds. If the busy cursor is active Amira will not
        process any mouse or button events. */
    void busy();

    /** Deactivates the busy cursor. For every call to busy there
        must be a corresponding call to this method. Multiple levels of
        busy calls are allowed. */
    void notBusy();

    /** Indicates the beginning of a non-interruptable time-consuming
        operation.  During the operation itself information about the
        progress should be given using setProgressValue().  In contrast
        to busy this method should be used when the operation takes
        longer than 5 seconds. A printf-like message string should be
        specified as an argument. */
    void startWorkingNoStop(const char* format, ...);

    /** Indicates the beginning of an interruptable time-consuming operation.
        This method behaves similar as startWorkingNoStop() except that
        the Amira stop button becomes active. By calling
        wasInterrupted a task may detect if the operation should be
        terminated prior to completion. */
    void startWorking(const char* format, ...);

    /** Indicates that time-consuming operation has been completed. For every
        call to startWorking() or startWorkingNoStop() there must
        be a corresponding call to this method. Multiple levels of calls to
        startWorking() or startWorkingNoStop() are allowed. After
        stopWorking() is called the previous state of the progress bar
        and the progress message are restored. */
    void stopWorking();

    /** Terminates all (recursive) startWorking() calls. This method should
    not be used by normal modules. It is intended for cleanup after
    exception handling. */
    void clearBusyStack();

    /** Returns the current progress value. */
    float getProgressValue();

    /** Updates text string displayed on the progress bar. This method can
        be called in order to describe more precisely the progress of a
        time-consuming operation.  For example, a call like
        @code
        theWorkArea->setProgressInfo("Processing slice %d of %d", i, n);
        @endcode
        may be used when operating on 3D image data.

        In addition, this method may also be used in order to display
        arbitrary messages in the progress bar area without calling
        startWorking() or startWorkingNoStop() before. For example,
        this might be useful during interactive edit operations to be
        performed in the 3D viewer. In this case you may want to print
        messages like <em> ``Click on the landmark to be deleted''</em> or <em>
        ``Click on the edge to be contracted''</em>. In order to clear the
        message again use @c setProgressInfo(""). */
    void setProgressInfo(const char* format, ...);

    /** Enters local event loop and returns 1 if user hit stop button. This
        method may be called between startWorking() and stopWorking(). Note,
        that unexpected callbacks may be invoked when entering the local event
        loop. However, viewer events will not be processed when calling this
        method. In particular, the scene graph will not be traversed. */
    int wasInterrupted(bool sync = true);

    /** Checks whether user did interrupt rendering (in case of very
        complex scenes with very low frame rates). Note that currently
        there is no convenient way to do so, so this is mainly for future
        use. */
    int wasRenderInterrupted();

    // internal use only
    int renderInterruptStatus;

    /** Alternative initialization of the progress bar. Assuming you know
        how many steps your operation requires, you can do the following:

        @li Initially, call <tt>startWorking(numSteps, message)</tt>
        @li For every step call
        @code
        if (!progressStep()) { stop your work; }
        @endcode
        If you want to do several steps at once specify the number of
        steps a an argument of @c progressStep().
        @li Finally, call stopWorking().
    */
    void startWorking(int numSteps, const char* format, ...);

    void startWorkingNoStop(int numSteps, const char* format, ...);

    /** Notify, that a step is taken. Will return 0 on interruption. The
        argument @c n can be specified if multiple steps are performed at
        once. */
    int progressStep(int n=1);

    /** Returns 1 if the application is in a busy state. This is the case if
        either busy or startWorking() or one of its variants
        has been called. */
    int isBusy() const { return busyStack.size(); }

    /** Enter local event loop. Caution: this may be dangerous since
        unexpected callbacks may be invoked. If @c allowViewerRedraw is
        true the Open Inventor scene graph might be traversed in response
        to a redraw event. */
    void handlePendingEvents(int allowViewerRedraw=1);

    // For internal use only.
    void suspendWorking();

    // For internal use only
    void resumeWorking();


    /** subdivides the current range into subranges.
        The subranges are defined by the list of scalar values.
     */
    virtual void subdivide(McDArray<float> &scales);

    /** subdivides the current range into @ranges subranges.
     */
    virtual void subdivide(int ranges);

    /// undo subdividision
    virtual void undivide();

    QWidget* getGUIContainer() const { return mContainer ; }

    //@}

    /** Indicates if one of the visible modules contain a port DoIt */
    bool containPortDoIt() const { return m_containPortDoIt ; }

    /** Hits all DoIt portAction of all visible modules */
    void hitDoIt() ;

    /** Snaps all DoIt portAction of all visible modules */
    void snapDoIt(bool state) ;

    /** Enables or disables viewer toggles on modules header.
    This method sets the value of the flag @c viewerTogglesOnHeaders and 
    call update(). Default is enabled*/
    void setViewerTogglesOnHeaders(bool value);

    /** Tell if the work area is currently displaying viewer toggles.*/
    bool isViewerToggledOnHeader() const { return viewerTogglesOnHeaders; }

    // To update the auto-refresh/apply/stop area.
    void updateApplyStopAreaState();

    QxProgressBar* getProgressBar() const { return progressBar; }

    QxStopButton* getStopButton() const { return stopButton; }

    QPushButton* getApplyButton() const { return wApplyButton; }

    QCheckBox*    getAutoRefreshCheck() const { return wAutoRefresh ; }

    static HxWorkArea*& getTheWorkArea();

    static int timeInterrupt;

    /** Connection point for Qt signals and slots.
      */
    QxWorkAreaNotifier* const mNotifier;

  protected:
      QScrollArea*   scrollView;
      QxProgressBar* progressBar;
      QxStopButton*  stopButton;
      QWidget*       mContainer ;
      QPushButton*   wApplyButton;
      QCheckBox*     wAutoRefresh;
      QVBoxLayout*   viewportLayout;

      // Indicates if one of the visible module contains a port DoIt
      bool           m_containPortDoIt ;

      // List of all DoIt ports of the visible modules.
      McDArray<HxPortDoIt*>  m_portDoItList ;

      /// set value in the root interval
      virtual void setProgressValueGlobal(float howMuch);

      void addChild(QWidget* child);

      struct BusyState {
          McString text;
          int progress;
          int totalSteps;
          unsigned int bigTask:1;
          unsigned int interruptable:1;
    };

    void pushBusyState(int bigTask, int interruptable);
    void popBusyState(int bigTask);
    McDArray<BusyState*> busyStack;

    /// Display or not the viewer toggles.
    static bool viewerTogglesOnHeaders;

 private:
     WorkAreaIfaceNamespace::ProgressReceiverIfaceImpl mProgressReceiverIfaceImpl;

  public:
    /**
     *  To be notified that preferences changed.
     */
    virtual void preferencesChanged(const HxPreferences& oldPreferences, const HxPreferences& newPreferences);
};

// Global instance of the work area
#define theWorkArea (HxWorkArea::getTheWorkArea())

#endif

/// @}
