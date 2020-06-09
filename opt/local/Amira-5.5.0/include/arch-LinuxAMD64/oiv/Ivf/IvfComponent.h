/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef __CIVFCOMPONENT_H__
#define __CIVFCOMPONENT_H__

#include <Inventor/SbBasic.h>
#include <SoVersion.h>

// import the static IVF_IGNORE_* masks
#if defined(_DEBUG)
#ifdef UNICODE
#  define __IVFDLL "IvfUD.dll"
#  define __IVFLIB "IvfUD.lib"
#else
#  define __IVFDLL "IvfD.dll"
#  define __IVFLIB "IvfD.lib"
#endif
#else
#ifdef UNICODE
#  define __IVFDLL "IvfU.dll"
#  define __IVFLIB "IvfU.lib"
#else
#  define __IVFDLL "Ivf.dll"
#  define __IVFLIB "Ivf.lib"
#endif
#endif
#ifndef Ivf_EXPORTS
#ifndef OIV_DISABLE_AUTOLINK
#  pragma comment(lib,__IVFLIB)
#endif
#endif

#include <Inventor/SoModule.h>
SO_MODULE_HEADER(SoIvf, __IVFDLL)

class SbColor;
class SoError;
class SoWinComponent;
class SoNode;
class SoPathList;
class SoPath;
class SoPickedPoint;
class SoWinClipboard;
class SoGroup;
class SoCamera;
class SoEventCallback;
class SoSceneManager;
class SoSelection;
class SbViewportRegion;
class SoWWWAnchor;
class SoOffscreenRenderer;
class SoGLRenderAction;

class CIvfApp;
class CIvfMainFrame;
class CIvfDocument;

/**
 * Interface of the IVF component class.
 * 
 * @ingroup Ivf_Classes
 * 
 * @DESCRIPTION
 *   This class provides methods to process messages directed to the IVF component
 *   object and methods to interact with the SoWin component.
 *   
 *   Note: Although the class name is CIvfComponent, the header file name is
 *   IvfComponent.h.
 *   
 *   #m_pCreateArgs is a pointer to an array of type int containing (at least) the
 *   following:
 *   - #m_pCreateArgs[0] = Enable viewer decorations (default = TRUE) @BR
 *     If enabled, the viewer decorations (thumbwheels, etc.) are turned on. 
 *   - #m_pCreateArgs[1] = Enable display of URL (default = FALSE) @BR
 *     If enabled, IvfOnUrlDisplayChanged will be called. 
 *   - #m_pCreateArgs[2] = Enable viewpoints menu (default = FALSE) @BR
 *     If enabled, a Viewpoints menu will be added to the menu bar. 
 *   - #m_pCreateArgs[3] = Enable URL fetch callback (default = FALSE) @BR
 *     If enabled, IvfOnFetchUrl will be called. 
 * 
 * 
 */ 

class IVF_API CIvfComponent
{
  friend class CIvfMainFrame;
  friend class CIvfDocument;

 public: 
  CIvfComponent();

  /**
   * Get the active selection
   */
  virtual SoSelection *IvfGetSelectionNode();

  /**
   * This method creates an SoWin Component inside of the window
   * pointed to by pWnd. Use this method to create a component
   * inside of an arbitrary window.
   */
  virtual void      IvfCreateComponent(CWnd *pWnd,
                                       void *pCreateArgs=NULL) = 0;

  /**
   * This method destroys the component.
   */
  virtual void      IvfDestroyComponent() = 0;

  /**
   * This method returns the clipboard contained in the components
   */
  virtual SoWinClipboard *IvfGetClipboard();

  /**
   * This method returns a pointer to the component.
   */
  virtual SoWinComponent *IvfGetSoWinComponent() ;
   
  /**
   * This method responds to IvfSceneGraphChanged to reset the
   * viewer to the new scene graph and camera.
   */
  void IvfResetComponent(CIvfDocument *pDoc);

  /**
   * Is a selection active
   */
  virtual BOOL     IvfIsSelected();

  /**
   * Set the mode to selection or viewing
   */
  void IvfViewmodesSelectionmode();
  void IvfViewmodesViewingmode();

  /**
   * This method forces the component to use the scene graph pointed to
   * by pRoot instead of the scene graph contained in the document.
   */
  virtual void      IvfSetSceneGraph(SoNode *pRoot) = 0;

  /**
   * This method returns the scene graph contained in the
   * component.
   */
  virtual SoNode *  IvfGetSceneGraph()=0;

  /**
   * This returns the scene graph contained by the base viewer
   * (SoSceneViewer, SoExaminerViewer, etc.)
   */
  virtual SoNode *  IvfGetBaseViewerSceneGraph()=0;

  /**
   * This method causes the component to unreference its scene graph.
   */
  virtual void      IvfReleaseSceneGraph() = 0;

  /**
   * Set the Background color
   */
  virtual void       IvfSetBackgroundColor(SbColor &) = 0;

  /**
   * Set the Background color
   */
  virtual void       IvfSetHeadlight(BOOL) = 0;
  virtual BOOL       IvfIsHeadlight() = 0;

  /**
   * Set the component's camera to camera number nCamera from
   * the list of cameras pointed to by m_pCamList
   */
  virtual void      IvfSetActiveCamera(int nCamera);

  /**
   * Set the component's camera to pCam.
   */
  virtual void      IvfSetActiveCamera(SoCamera *pCam)=0;

  /**
   * Return a pointer to the component's camera.
   */
  virtual SoCamera *   IvfGetActiveCamera()=0;

  /**
   * Save the position of the component's camera as the home
   * position.
   */
  virtual void      IvfSaveHomePosition()=0;

  /**
   * Move the component's camera to the home position.
   */
  virtual void      IvfResetToHomePosition()=0;

  /**
   * Perform a viewAll on the component's scene graph.
   */
  virtual void      IvfViewAll()=0;

  /**
   * Get the component's viewport region.
   */
  virtual const SbViewportRegion & IvfGetViewportRegion()=0;

  /**
   * Get the component's render action.
   */
  virtual SoGLRenderAction *IvfGetGLRenderAction()=0;

  /**
   * Get the component's scene manager
   */
  virtual SoSceneManager *IvfGetSceneManager()=0;

  /**
   * Query component's viewing status
   */
  virtual BOOL    IvfIsViewing()=0;

  /**
   * Set component's viewing status
   */
  virtual void       IvfSetViewing(BOOL flag)=0;

  /** Viewer type */
  enum IvfViewerType 
  {
    /** No viewer */
    IVF_NONE, 
    /** Walk viewer */
    IVF_WALK,
    /** Examiner viewer */
    IVF_EXAMINER
  };


  static void setIgnoreError(WORD err_mask);
  static void clearIgnoreError(WORD err_mask);
  static BOOL isIgnoreError(WORD err_mask);

  static  WORD IVF_IGNORE_READERROR;
  static  WORD IVF_IGNORE_MEMERROR;
  static  WORD IVF_IGNORE_DBGINFO;
  static  WORD IVF_IGNORE_DBGWARNING;
  static  WORD IVF_IGNORE_DBGERROR;
  //  masks for error handling

 protected: //PROTECTED_TO_DOCUMENT
  /**
   * This method notifies the component that the scene graph contained 
   * in the document has changed.
   */
  virtual void      IvfSceneGraphChanged() ;

  /**
   * These handle printing.
   */
  void IvfOnBeginPrinting();
  void IvfOnPrint(CDC *);
  void IvfOnEndPrinting();
   
  /**
   * Save the scene graph as a bitmap (.bmp file).
   */
  BOOL IvfSaveAsBitmap(LPCTSTR pFilename);

  /**
   * These are called on selection and deselection.
   */
  virtual void IvfOnSelection(SoPath *);
  virtual void IvfOnDeSelection(SoPath *);
  static void IvfStaticSelectionCB(void *, SoPath *);
  static void IvfStaticDeSelectionCB(void *, SoPath *);

  /**
   * These functions prune and restore manipulators from and to
   * the scene graph.  Used before saving to storage, clipboard, etc.
   */
  virtual void IvfRemoveManips(void);
  virtual void IvfRestoreManips(void);

  /**
   *  following is direct support for cut/paste operations
   */
  void IvfOnEditCopy();
  void IvfOnUpdateEditCopy(CCmdUI* pCmdUI);
  void IvfOnEditCut();
  void IvfOnUpdateEditCut(CCmdUI* pCmdUI);
  void IvfOnEditPaste();
  void IvfOnUpdateEditPaste(CCmdUI* pCmdUI);
  void IvfOnUpdateEditUndo(CCmdUI* pCmdUI);

  /**
   * This method is invoked when the user selects a viewpoint from
   * the viewpoint menu.  If m_nEnableViewpoints is TRUE, 
   * CIvfComponent will maintain a viewpoint menu for the
   * application.  The cameras corresponding to each viewpoint
   * in the viewpoint menu are contained in a list pointed
   * to by the m_pCamList member variable.  If the scene graph
   * loaded by the application did not contain any cameras, then
   * the camera list will be empty, and the viewpoint menu will
   * contain the default item "Entry View".  If the camera list
   * is not empty, the viewpoint menu will contain items 
   * corresponding to the name of each camera.  The camera
   * corresponding the the selected menu item is 
   * (*m_pCamList)[nCamera].  In the case where the camera
   * list is empty and "Entry View" is selected, this method
   * is invoked with nCamera set to 0.
   */
  virtual void IvfOnSelectViewpoint(int nCamera);



  /**
   * If m_nEnableUrlDisplay is TRUE, this method is invoked
   * every time the mouse cursor passes over an SoWWWAnchor
   * node, and everytime the cursor moves out of a region
   * of the screen occupied by the SoWWWAnchor node.  This
   * enables applications to display a URL name in the
   * status bar.  The default implementation of this method
   * displays urlName in the application frame window's 
   * status bar.
   */
  virtual void     IvfOnUrlDisplayChanged(LPCTSTR urlName);

  /**
   * If the component contains a scene graph that has a
   * SoSelection node as the root, this method is invoked
   * when the user picks a node in the scene graph by clicking
   * the mouse button.  If m_nEnableSelection is TRUE, the
   * path to the selected node is returned.  This causes the
   * selected node to be highlighted.  If m_nEnableSelection is
   * FALSE, a path containing only the selection node is returned
   * and no highlighting occurs.
   */
  virtual SoPath *  IvfOnSelectionPick(const SoPickedPoint *pick );

  /**
   * This method performs a viewAll on the path pointed to 
   * by pPath.  If m_nEnableViewpoints is TRUE, CIvfComponent
   * will maintain a list of paths to all of the SoWWWAnchor
   * nodes in the component's scene graph.  This method is
   * invoked to cause the component's camera to be relocated
   * so that the anchor pointed to by pPath is visible.  Note
   * that performing a viewAll on the path to the anchor does
   * not guarantee that the geometry contained under the
   * anchor node will be visible.  Applications should overload
   * this method if a more robust behavior is desired.
   */
  virtual void      IvfOnViewAnchor(SoPath *pPath);

  /**
   *  Enable/disable selections.
   */
  void IvfOnSelectionEnable();
  void IvfOnUpdateSelectionEnable(CCmdUI* pCmdUI);

  /**
   * This method is invoked when an error is encountered.  A dialog
   * containing the error message is displayed.
   */
  static void    IvfErrorCallback( const SoError *error, void *data );

  /**
   * These are called just before and after the respective edit
   * operations to allow the viewer to make adjustments before and after.
   */
  virtual void IvfPrePasteAction();
  virtual void IvfPostPasteAction();
  virtual void IvfPreCopyAction();
  virtual void IvfPostCopyAction();
  virtual void IvfPreCutAction();

  virtual          ~CIvfComponent();

  /**
   * This method inserts an SoEventCallback node
   * into the scene graph contained in the document
   * object.  The callback node triggers a callback
   * for every SoLocation2Event (each time the cursor
   * moves).  The default implementation set's up
   * a mechanism so that IvfLoc2Callback is invoked
   * for each mouse move event.  This mechanism is
   * needed to enable display of URLs as the mouse
   * cursor moves over SoWWWAnchor nodes.  An
   * application should overload this method if another
   * method of URL display is desired.  This mechanism
   * is setup only if m_nEnableUrlDisplay is TRUE.
   */
  virtual void     IvfSetupUrlDisplayCallback(SoGroup *root);

  /**
   * This method removes the SoEventCallback node from the
   * scene graph.
   */
  virtual void     IvfRemoveUrlDisplayCallback(SoGroup *root);

  /**
   * If m_nEnableUrlDisplay is TRUE, this method is invoked
   * each time the cursor position changes while inside the
   * component's window. The default implementation performs
   * an SoRayPickAction action on the scene graph to determine if the
   * cursor is over a URL. In addition, the appropriate analysis
   * is performed to determine if the URL display needs to
   * be updated.  If the URL display needs to be changed,
   * IvfOnUrlDisplayChanged is invoked.
   */
  virtual void     IvfLoc2Callback(
                                   void *userData,
                                   SoEventCallback *node);

    
  /**
   * This static member function is invoked by the callback
   * node in placed in the scene graph by IvfSetupUrlDisplayCallback
   * for each mouse move event.  This method then invokes
   * IvfLoc2Callback.
   */
  static void      IvfStaticLoc2Callback(
                                         void *userData,
                                         SoEventCallback *node);

  /**
   * This method sets the selection pick filter callback to
   * IvfStaticSelectionPickCB.
   */
  virtual void     IvfSetupSelectionPickCallback();

  /**
   * This method sets the selection pick filter callback to NULL.
   */
  virtual void     IvfRemoveSelectionPickCallback();


  /**
   * These methods are invoked when the user picks a node in
   * the scene graph.  IvfOnSelectionPick is the instance version
   * called by IvfStaticSelectionPickCB.
   */
  static SoPath *  IvfStaticSelectionPickCB(
                                            void *userData, 
                                            const SoPickedPoint *pick);

  /**
   * This method happens on paste.  It is invoked from the
   * specific viewer and passes the paste list.  The first is
   * the static callback passed to the clipboard and the second
   * is the actual instance member function (that does all the work).
   */
  static void IvfPasteDoneCB(void *userData, SoPathList *pathList);
  void IvfPasteDone(SoPathList *pathList);

  /**
   * This is the implementation of the cut method.
   */
  void IvfDestroySelectedObjects();

  /**
   * This method is invoked when the MFC object that is polymorphic with
   * the IVF component object is about to be destroyed.
   */
  virtual void     IvfOnDestroy();

  /**
   * Paint message handler (default calls BeginPaint/EndPaint).
   //
   * No params version is the old one.  Starting with release 2.2.1, the
   * IVF AppWizard generates code in the app to override the default CView
   * OnPaint handler and call the second version.
   */
  virtual void     IvfOnPaint();
  virtual void     IvfOnPaint( CWnd *pWnd );

  /**
   * Erase background message handler (default just returns TRUE).
   //
   * The IVF AppWizard generates code in the app to override the default
   * CView handler so we can avoid drawing the background of the view's
   * window.  It is completely covered by the Inventor viewer window, so
   * drawing would be a waste of cpu cycles.
   */
  virtual BOOL IvfOnEraseBkgnd( CDC* pDC );

  /**
   * This method is called when the view object is created.
   */
  virtual void     IvfOnCreate(LPCREATESTRUCT lpCreateStruc);

  /**
   * This method is invoked during the first update of the window containing
   * the component.
   */
  virtual void     IvfOnInitialUpdate(CWnd *pWnd);

  /**
   * This method is invoked prior to activation of the component
   * in a MDI application.
   */
  virtual void     IvfOnActivateComponent(CView *pActivateView = NULL);

  /**
   * This method is invoked prior to component deactivation
   * in a MDI application.
   */
  virtual void     IvfOnDeactivateComponent();
    
  /**
   * This method is used to route commands to the SoWin component.
   * TRUE is returned if the command is processed, FALSE otherwise.
   */
  virtual BOOL     IvfOnCommand(WPARAM wParam, LPARAM lParam);

  /**
   * This method is used to route command messages to the component.
   * TRUE is returned if the command is processed, FALSE otherwise.
   */
  virtual BOOL     IvfOnCmdMsg(UINT nID, int nCode, void* pExtra,
                               AFX_CMDHANDLERINFO* pHandlerInfo) ;

  /**
   * If the camera list is not empty, the item "View Anchors..."
   * is appended to the end of the viewpoint menu.  This
   * method is invoked when "View Anchors..." is selected.
   */
  virtual void IvfOnSelectViewAnchors();
    
  /**
   * This method is used by IvfOnCmdMsg to determine if a message
   * pertains to the viewpoint menu.
   */
  virtual BOOL IvfIsViewpointMsg(UINT nID, int nCode, void* pExtra,
                                 AFX_CMDHANDLERINFO* pHandlerInfo);

  /**
   * This method queries if the underlying viewer iss a
   * SceneViewer or not.
   */
  virtual BOOL IvfIsSceneViewer();

  /**
   * Pointer to the SoWin Component
   */
  SoWinComponent * m_pComponent;
    
  /**
   * pointer to the component creation arguments
   */
  void *           m_pCreateArgs;

  /**
   * clipboard and selection now available to all viewers.
   */
  SoWinClipboard *m_pClipboard;
  SoSelection *m_pSelection;

  /**
   * offscreen renderer is used for printing
   */
  SoOffscreenRenderer *m_pOffscreen;

  /**
   * pointer to window which contains the SoWin component,
   * note this is not necessarily the CWnd derived object
   * that is polymorphic with CIvfComponent, it may be one 
   * of the children of that object (i.e. a child control
   * of a CDialog)
   */
  CWnd *           m_pWnd;


  /**
   * a pointer to the event callback node used to route
   * SoLocaton2 events
   */
  SoEventCallback *   m_pEventCB;

  /**
   * flag that enables node selection (highlighting)
   */
  BOOL          m_nEnableSelection;

  /**
   * flag to indicate the background color changed callback
   * has been set.
   */
  BOOL          m_bBgColorChangedSet;

  static WORD     m_fIgnoreError;
};



/**
 * This macro is used by classes derived from CIvfComponent
 * for convenient declaration of the minimum set of methods
 * that must be defined by the derived class.  These are all
 * of the methods that are declared as pure virtual functions
 * in CIvfComponent.
 */
#define IVF_COMPONENT_BASE()\
public:\
   virtual void      IvfCreateComponent(CWnd *pWnd, void *pVwrArgs=NULL);\
   virtual void      IvfDestroyComponent();\
   virtual void      IvfSetSceneGraph(SoNode *pRoot) ;\
   virtual SoNode *  IvfGetSceneGraph();\
   virtual SoNode *  IvfGetBaseViewerSceneGraph();\
   virtual void      IvfReleaseSceneGraph();\
   virtual void      IvfSetBackgroundColor(SbColor &bg);\
   virtual void      IvfSetHeadlight(BOOL);\
   virtual BOOL      IvfIsHeadlight();\
   virtual void      IvfSetActiveCamera(SoCamera *pCam);\
   virtual SoCamera *   IvfGetActiveCamera();\
   virtual void      IvfSaveHomePosition();\
   virtual void      IvfResetToHomePosition();\
   virtual void      IvfViewAll();\
   virtual SoGLRenderAction * IvfGetGLRenderAction();\
   virtual const SbViewportRegion & IvfGetViewportRegion();\
   virtual SoSceneManager *IvfGetSceneManager();\
   virtual BOOL      IvfIsViewing();\
   virtual void      IvfSetViewing(BOOL flag);


/**
 * These macros are used in the MFC application view class implementation
 * to route commands to the IVF component object.  If you use these
 * macros, you cannot use the ClassWizard to edit the view's code.
 */
#define IVF_MFC_ON_METHOD_NAME(CmdName) On##CmdName
#define IVF_MFC_ON_UPD_METHOD_NAME(CmdName) OnUpdate##CmdName 

#define IVF_ON_METHOD_NAME(CmdName) IvfOn##CmdName
#define IVF_ON_UPD_METHOD_NAME(CmdName) IvfOnUpdate##CmdName 

#define IVF_COMMAND_HANDLER(ComponentName,CmdName) \
void ComponentName::IVF_MFC_ON_METHOD_NAME(CmdName) () \
{ \
   IVF_ON_METHOD_NAME(CmdName) (); \
} \
void ComponentName::IVF_MFC_ON_UPD_METHOD_NAME(CmdName) (CCmdUI* pCmdUI)\
{ \
   IVF_ON_UPD_METHOD_NAME(CmdName) (pCmdUI); \
}

/**
 * for beta2 compatability
 */
#define IVF_COMMAND_HANDLER_BETA2(ComponentName,VwrName,CmdName) \
void ComponentName::IVF_MFC_ON_METHOD_NAME(CmdName) () \
{ \
   IVF_ON_METHOD_NAME(CmdName) (); \
} \
void ComponentName::IVF_MFC_ON_UPD_METHOD_NAME(CmdName) (CCmdUI* pCmdUI)\
{ \
   IVF_ON_UPD_METHOD_NAME(CmdName) (pCmdUI); \
}  

#endif

