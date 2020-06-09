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
#ifndef HX_MAIN_H
#define HX_MAIN_H

#define DEFAULT_NETWORK_NAME "Untitled"

#include <hxcore/HxAmiraWinDLLApi.h>
#include <hxcore/HxThread.h>
#include <hxcore/HxBase.h>
#include <hxcore/HxDSO.h>

#include <QMainWindow>
#include <QSplitter>

#include <mclib/McHashTable.h>
#include <mclib/McFilename.h>

class QLabel;
class QToolButton;
class HxAxis;
class HxData;
class HxFileFormat;
class HxSubApplication;
class QxInfoDialog;
class QAbstractButton;
class QVBoxLayout;
class QxTabWidget;
class QSplashScreen;
class QToolBar;
class QAction;
class QStackedLayout;
class QMessageBox;
class Q3PopupMenu;
class HxPreferences;
class QxViewerPanel;
class ThreadNegotiator;
class HxMasterConnection;

typedef void (HxBase::*HxTimeOutMethod)();
typedef void (*HxTimeOutFunction)(void* userData);

/** Main window widget (better should be called QxMain). This class creates
    the main window containing menu, object pool, and work area. The slots
    called from the menu are defined here. In addition, the class also
    defines the static Amira main routine. Only one instance of this class
    will be created in Amira. This instance can be accessed via the global
    pointer @c theMain. */

/// The pool views.
enum {POOL_VIEW = 0, TREE_VIEW = 1, BOTH_VIEWS = 2};

class HXCORE_API HxMain : public QMainWindow
{
    Q_OBJECT

    struct ConsoleTabInfo {
        ConsoleTabInfo(const char* inName, QWidget* inPage)
            : name(inName) , page(inPage) {}
        const char* name;
        QWidget*    page;
    };

  public:
    /// Constructor.
    HxMain();

    /// Fixed width font, used e.g. in HxTextDialog.
    QFont fixedWidthFont() { return theFixedWidthFont; }

    /** Pops up the file dialog and save the data object. Returns 1 if the
        data could be successfully saved, 0 otherwise.
        if @c defaultSavePath is not NULL, this path will be used as the default path to save the data.
        */
    int saveData(HxData* data, int saveAsFlag, const McString* defaultSavePath=0);

    /** Pops up the file dialog and save the current network. Returns 1 if the
        data could be successfully saved, 0 otherwise. */
    int saveNetwork(bool forceAutoSave=false, bool saveAsFlag=true);

    /// Amira main routine (initializes everything and enters main loop).
    static int main(int argc, char** argv);

    /** Init Amira using an existing QApplication object. This method
        should be called when using Amira as a library in another
        application. If app is NULL a new QApplication will be created.
        Returns 0 on success, or -1 if an error occured. */
    static int initAmira(const char* amiraRoot, QApplication* app=0);

    void saveScreenLayout();
    void loadScreenLayout(bool showMainWindow = true);
    
    /// Get size of sub application main splitter
    bool loadSubAppScreenLayout(HxSubApplication *subApp, int &mainRectWidth, int &viewerRectWidth);

    /// Adjusts the position of a dialog so that it is centered over the object pool.
    void setDialogPosition(QWidget* widget) const;

    /** Returns root widget of screen containg the main window. The returned widget
        can be used as the parent widget of dialog windows which should be centered
        on the screen. */
    QWidget* desktop();

    /// Parse method associated with @c theMain command.
    int parse(Tcl_Interp* t, int argc, char** argv);

    void addTimeOutMethod(HxBase* base, HxTimeOutMethod, int msec, bool sshot=0);
    void addTimeOutFunction(void* userData, HxTimeOutFunction, int mesc, bool sshot=0);
    void removeTimeOutMethod(HxBase* base, HxTimeOutMethod);
    void removeTimeOutFunction(void* userData, HxTimeOutFunction);

    void initRecentFiles();
    void saveRecentFiles();
    void clearRecentFiles();
    void addToRecentFiles(int n, const char** files, HxFileFormat** formats, bool asTimeSeries);

    /** Returns true if Amira is being terminated. Before Amira terminates,
        all objects in the object pool are deleted. Modules can interprete
        this flag to simplify cleanup. */
    bool isTerminating();

    void setTopLevelPanel(bool enable);

    void setTopLevelConsole(bool enable);

    void setTopLevelHelp(bool enable);

    bool isTopLevelPanel() const;

    bool isTopLevelConsole() const;

    bool isTopLevelHelp() const;

    void setViewerSize(const QSize& size);

    QWidget* getTopWidget() const { return topWidget; }
    
    QLabel*  getPoolLabel() const { return poolLabel; }

    void activatePoolPage(bool toggle);

    QWidget* getCurrentWidget() const;

    void setCurrentSplitter(QSplitter *widget);

    void insertTreeSplitter(QSplitter *widget);

    /// Called to (re)load the style sheet file.
    static void loadStyleSheet();

	
    //////////////////////////////////////////////////////////////////////////
	// Tree view stuff

	/// To get the tree view dso.
	HxDSO& getTViewDSO() {return tViewDSO;};

	/// To know if the tree view is enabled.
	inline bool treeViewIsEnabled() const {return m_treeViewEnabled;};

	/// To know if we are in tree view mode.
	inline bool inTreeViewMode() const {return m_inTreeViewMode;};

    /** Sets tree view flag. This method is called if the tree view is enabled
        or disabled, e.g. by calling QxPreferenceDialog::enableTreeView().
        It does not enable or disable the tree view by itself. */
    void setTreeViewMode(bool inTreeViewMode);

    // End tree view stuff.
	//////////////////////////////////////////////////////////////////////////


	/// To manage the duplicateMode functionality.
	inline bool inDuplicateMode() const {return m_duplicateMode;};
	inline void setDuplicateMode(bool enabled = true) {m_duplicateMode = enabled;};
	void enableDuplicateMode(bool enable = true);

	/// To manage the auto adjust range functionality.
	bool inAutoAdjustRangeOfColormaps() const {return m_autoAdjustRangeForColormaps;};
	inline void setAutoAdjustRangeOfColormaps(bool enabled = true) {m_autoAdjustRangeForColormaps = enabled;};
	void enableAutoAdjustRangeOfColormaps(bool enable = true);

  /**
   * To get the wWorkAreaFrame.
   */
  QFrame* getWorkAreaFrame() const;

  /**
   * To get the wPoolSplitter.
   */
  QSplitter* getPoolSplitter() const;
  
  /// Returns a pointer to the splitter which splits 
  /// the viewer panel and the work area
  QSplitter* getMainSplitter() const;

  QToolBar* getSubApplicationToolBar() const { return wSubApplicationToolBar; }

  QStackedLayout* getMainStackedLayout() const { return wMainStackedLayout; }

  QStackedLayout* getViewerStackedLayout() const { return wViewerStackedLayout; }

  /** 
   * Returns a pointer to the current active viewer panel instance or returns NULL
   * if the current widget of wViewerStackedLayout is not of type QxViewerPanel.
   * e.g. this could happen for the Amira multi planar subapplication which is not 
   * derived from QxViewerPanel.
   *
   * Note: In cases were no sub applications are used (e.g. Avizo) the returned 
   *       pointer is identical with the pointer returned by 'thePanel' of QxViewerPanel.
   */
  QxViewerPanel* getCurrentViewerPanel() const;

  // Returns menu bar popup menus
  QMenu* getCreatePopupMenu()        const { return createMenu ;} 
  QMenu* getRecentFilePopupMenu()    const { return recentFilesPopup ;} 
  QMenu* getRecentNetworkPopupMenu() const { return recentNetworksPopup ;} 
  QMenu* getFileMenu()               const { return fileMenu ;} 

  QAction* getSaveNetworkAsAction() const { return saveNetworkAsAction; }

  /**
   * Insert a new file menu entry before "Save Network"
   */
  void insertActionBeforeSaveNetwork(QAction* newAction);

    // Initializes the create menu (for preset mechanism)
    void maskCreateMenu() ;

    /* Returns true if calling thread is the main thread. */
    // Update the application title with <m_mainCaptionName> + <m_networkName>
    void updateMainTitle() ;

    // Stores the network name in order to display it as application title.
    void setNetworkName(const McFilename &filename) ;

    // Get the path of the current network.
    const char* getNetworkPath() const;

    /// Returns true if calling thread is the main thread.
    static int isMainThread();

    // Renders the specified text into custom icon set and applies it to button @c b.
    static void setButtonText(QAbstractButton* b, const QString& text, const QColor& buttonColor, int width=-1);

    // Show/Hide the console
    void showConsole(bool flag);

    /// Internal: VR and TeamWork
    void checkRemoteMode();

    /** Set whether Amira main as to manage close event (default is true). 
    If true, Amira will call quit() which check if something as to be save (possibly asking if user really want to exit via a dialog), 
    save preferences, save recently opened file paths, stop httpd daemon and call exit(0).
    This method is useful when user add is own main window above Amira and want to manage the exit by himself.*/
    void manageCloseEvent(bool onOrOff);

    bool isManagingCloseEvent() {return m_isManagingCloseEvent;}

    /** 
     * To show a message when data objects will be deleted without been saved.
     */
    bool showCheckDataSaveMsg() const;

    /** 
     * Inherited from QMainWindow. Since Qt4, show() is not virtual anymore.
     * We have to use setVisible(bool) instead.
     */
    virtual void setVisible(bool visible);

    /** 
     * To send a key press event to the focus widget.
     * Used in the Edit menu to send Cut, Copy, Paste, Delete and SelectAll actions.
     */
    void commonSendEvent(const QKeySequence& keySequence);
    
    /**
     * Apppends a new console tab page \c page of name \c name
     * into the console tab widget.
     */
    void addConsoleTabPage(const char* name, QWidget* page);

    /**
     * Removes console tab page of name \c name from the console tab widget,
     * if name is a valid console tab page name.
     * Does nothing if the console tab page named \c name cannot be found.
     */
    void removeConsoleTabPage(const char* name);

    /**
     * Sets the console tab page with name \c name to current console tab page.
     * Does nothing if the console tab page named \c name cannot be found.
     */
    void setCurrentConsoleTabPage(const char* name);

    /**
     * Returns pointer to console tab page with name \c name, or NULL
     * if the page cannot be found.
     */
    QWidget* findConsoleTabPage(const char* name);

    /**
    * Verify if the current network must be saved.
    * Returns false if the user cancels the operation.
    * Returns true otherwise
    */
    bool verifySaveOfNetwork();

  public slots:
    // File menu
    void newNetwork();
    void fileOpenNetwork();
    void fileImportNetwork();
    void fileSaveNetwork();
    void fileSaveAsNetwork();

    bool fileOpenData();
    void timeSeries();
    int  fileSaveData(); // returns 1 if file was saved, 0 otherwise
    int  fileSaveDataAs();
    
    void jobDialog();
    bool quit();
    void configureFileMenu();

    // Edit menu
    void editCut() ;
    void editCopy() ;
    void editPaste() ;
    void editDelete() ;
    void editSelectAll() ;
    void editDatabase();
    void editPreferences();
    void editCreate(int id);

    // Help menu
    void demoDialog();
    void checkWebNews(bool forceShow = true);
    void about();
    void sysinfo();
    void license();
    void devWizard();
    void presetMgr();

    void layoutConfigure();
    void layoutChanged(int id);
    void backgroundDialog();
    void pickModule();
    void transparencyConfigure();
    void transparencyChanged(int id);
    void fogConfigure();
    void fogChanged(int id);
    void lightConfigure();
    void lightChanged(int id);
    void viewConfigure();
    void viewAxisToggle();
    void viewMeasureToolsToggle();
    void viewFrameCounter();
    void viewConsoleToggle();
    void moduleUsersguide();
    void subappUsersguide();
    void usersguide();
    void examples();
    void programmersguide();
    
    void recentNetworksSelected(QAction* action);
    void onlineSupport();

    void selectSubApplication(QAction* action);

    void connectToMaster();
    
    /* This simply calls theInterpreter->handleSocketEvent(). The method is
       defined here because HxInterpreter itself is not a QObject and
       therefore can't have slots which we can use in a QxSocketNotifier. */
    void handleSocketEvent(int socket);

    virtual void dropEvent ( QDropEvent * );
    void timerEvent(int timerId);
    void delayedTimerEvent();
    void deleteSplashScreen();

    void raise();
    bool loadData(const McDArray<McString> & filenames, const McDArray<HxFileFormat*> & formats);

    /**
     *  Update recent files list size according to maximum allowed
     *  number of recent files and build its corresponding popup menu. 
     */
    void updateRecentFiles();

    /**
     *  Update recent networks list size according to maximum allowed
     *  number of recent networks and build its corresponding popup menu.
     */
    void updateRecentNetworks();

    /**
     * Ask for permission to log various things. Send log files.
     */
    void initPerfLogging();

    /** 
     * Helper to register HxData objects from worker threads.
     * HxData objects need to be registered in the main thread (Qt GUI issues).
     * Calling this helper from a worker thread relays the call to the main
     * thread and then calls HxData::registerData.
     */
    void registerDataHelper(HxData *data, const char *filename, const char *ext);
    /** 
     * Helper to establish connections from worker threads (see registerDataHelper).
     */
    void connectHelper(HxMasterConnection *connection, HxObject *src, int *result);

    /**
     * Abort all file loading threads and wait until they are finished.
     */
    void abortLoadThreads();

  protected slots:
      void recentFilesSelected(QAction*);

   /*
    * Process cmd line files. The method is executed just after
    * starting the main event loop.
    */
    void loadCmdLineFiles();
   /*
    * The following methods are helpers for displaying GUI dialogs from 
    * a worker thread (see ThreadNegotiator for an explanation).
    */
    void createForkedObjectSlot(ThreadNegotiator *tn);
    void deleteForkedObjectSlot(ThreadNegotiator *tn);
    void putDataForkedObjectSlot(ThreadNegotiator *tn);
    void execForkedObjectSlot(ThreadNegotiator *tn);
    void getDataForkedObjectSlot(ThreadNegotiator *tn);
    friend class ThreadNegotiator;
    // Helper to register data from worker threads.
    void registerDataSlot(HxData *data, const char *filename, const char *ext);
    // Helper to establish connections from worker threads.
    void connectHelperSlot(HxMasterConnection *connection, HxObject *src, int *result);
  signals:

    void networkIsLoading(bool loadInProgress);
    void aboutToQuit();
    void saveNetworkCompleted();
    void saveNetworkAsCompleted();
    // Helper to register data from worker threads.
    void registerDataSig(HxData *data, const char *filename, const char *ext);
    // Helper to establish connections from worker threads.
    void connectHelperSig(HxMasterConnection *connection, HxObject *src, int *result);

  protected:
    McDArray<ConsoleTabInfo> mConsoleTabs;

    ///To know if this main window manage the close event.
    bool m_isManagingCloseEvent;

    enum OpenDataType {
      OPEN_NETWORK_DATA,
      IMPORT_NETWORK_DATA,
      OPEN_ANY_DATA 
    } ;

    QMenu*       fileMenu;
    QMenu*       editMenu;
    QMenu*       createMenu;
    Q3PopupMenu* viewMenu;
    Q3PopupMenu* layoutPopup;
    Q3PopupMenu* transparencyPopup;
    Q3PopupMenu* fogPopup;
    Q3PopupMenu* lightPopup;
    QMenu*       recentFilesPopup;
    QMenu*       recentNetworksPopup;
    QAction*     saveDataAction;
    QAction*     saveDataAsAction;
    QAction*     saveNetworkAction;
    QAction*     saveNetworkAsAction;

    int idViewAxis;
    int idMeasureTools;

    QFont theFixedWidthFont;

    McString   m_networkName ;
    McFilename m_networkPath ;
    bool       m_shouldUpdateNetworkName ;
    bool       m_topLevelHelp ;

    void createGUI();
    void showDefaultAmiraProductsLicenses();
    void initializeCreateMenu();
    bool openData(OpenDataType openDataType) ;
    
    int  saveData(int saveAsFlag);
    QRect getDefaultGeometry(const McString &);
    void createMenuBar();
    QSplitter*     wMainSplitter;
    QSplitter*     wPanelSplitter;
    QSplitter*     wPoolSplitter;
    QWidget*       wPoolTab;
    QSplitter*     wCurrentSplitter;
    QSplitter*     wTreeSplitter;
    QVBoxLayout*   mainbox;
    QToolButton*   poolSelect;
    QToolButton*   poolPan;
    QLabel*        poolLabel;


    //////////////////////////////////////////////////////////////////////////
    /// Tree view stuff

    /// The tree view DSO.
    HxDSO tViewDSO;

    /// To know if the tree view is enabled.
    bool m_treeViewEnabled;

    /// To know if we are in tree view mode.
    bool m_inTreeViewMode;

    /// End tree view stuff.
    //////////////////////////////////////////////////////////////////////////


    /// To allow duplicate mode for module.
    bool m_duplicateMode;

    /// To allow auto adjust range for port colormap.
    bool m_autoAdjustRangeForColormaps;

    QFrame*        wMainFrame;
    QFrame*        wViewerFrame;
    QFrame*        wConsoleFrame;
    QToolBar*      wSubApplicationToolBar;
    QFrame*        wPoolFrame;
    QFrame*        wWorkAreaFrame;
    QxTabWidget*   wConsoleTab;
    QWidget*       topWidget;
    QSplashScreen* wSplashScreen; 
    QStackedLayout* wMainStackedLayout;
    QStackedLayout* wViewerStackedLayout;

    virtual void timerEvent(QTimerEvent* e);
    virtual void closeEvent(QCloseEvent* e);
    HxAxis* getGlobalAxis();

    virtual void dragEnterEvent(QDragEnterEvent* event);

    static HxMain* _theMain;
    static QMainWindow* _theMainWindow;
    static QxInfoDialog* _theInfoDialog; // pointer to sys info dialog
    static QApplication* _theAmiraApplication ;

    static void commonPutenv();

  protected slots:
    /**
     *  To be notified that preferences (top level window options or viewer on left side) changed.
     */
    virtual void preferencesChanged(const HxPreferences& oldPreferences, const HxPreferences& newPreferences);

    /**
     *  To be notified that GUI layout has been reset.
     */
    virtual void layoutsReset();

    /**
     *  To be notified that recent documents has been reset.
     */
    virtual void recentDocumentsReset();

  protected:
    /** 
     * Called by timeSeries() and recentFilesSelected() to load time series data.
     */
    void openTimeSeries(int n, McDArray<const char*> fileNames, McDArray<HxFileFormat*> fileFormats);

    /**
     * @internal
     * Flag used to show or not the exit dialog when quitting the application.
     */
    static bool s_showExitDialog;


  protected slots:
    /**
     *  To be notified that a network is loading.
     */
    virtual void networkLoadingStarts();

    /**
     *  To be notified that a network loading is finished.
     */
    virtual void networkLoadingStops(int ret);

  protected:
    /// Calls when a network is loading.
    void updateStateDuringNetworkLoading(bool loadInProgress);

  public:
    static HxMain* getTheMain();
    // to give correct Qt parent for Hx widgets in other 
    // apps than Amira manually set the main window here
    static void setTheMainWindow(QMainWindow*);
    static QMainWindow* getTheMainWindow();

    /**
     * @internal
     * To show or not the exit dialog when quitting the application.
     * Called by the quitCmd of theInterpreter.
     */
    static void showExitDialog(bool show);
};

#define theMain       HxMain::getTheMain()
#define theMainWindow HxMain::getTheMainWindow()


// ------------------------------ INLINE methods. ------------------------------
inline QFrame*
HxMain::getWorkAreaFrame() const
{
  return wWorkAreaFrame;
}

inline QSplitter*
HxMain::getPoolSplitter() const
{
  return wPoolSplitter;
}

inline QSplitter*
HxMain::getMainSplitter() const
{
    return wMainSplitter;
}
inline QWidget *
HxMain::getCurrentWidget() const 
{
    return wCurrentSplitter;
}

inline void 
HxMain::setCurrentSplitter(QSplitter *widget)
{
    wCurrentSplitter = widget;
}

#endif


/// @}
