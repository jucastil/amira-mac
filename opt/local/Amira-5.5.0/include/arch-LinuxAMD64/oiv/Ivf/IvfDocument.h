/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef __CIVFDOCUMENT_H__
#define __CIVFDOCUMENT_H__

#define IVF_MAX_URL_NAME_LENGTH     1024
#define MAX_SCRATCH_FILES     4  

#define DEF_CAMERA_GROUP_NAME           "TGS_DEFCAMERA"
#define NEW_CAMERA_GROUP_NAME           "TGS_NEWCAMERA"

/**
 * This is the resource ID of the first viewpoint added
 * to the viewpoint menu.
 */
#define ID_FIRST_VIEWPOINT 17410

#include <Inventor/SbBasic.h>

#include <Ivf/IvfComponent.h>
#include <Inventor/actions/SoCallbackAction.h>

class SbColor;
class SbString;
class SbPList;
class SoSwitch;
class SoGroup;
class SoSeparator;
class SoInput;
class SoInfo;
class SoNode;
class SoOutput;
class SoPathList;
class SoTexture2;
class SoWWWAnchor;
class SoWWWInline;
class SoPrimitiveVertex;

class CArchive;

class CInlineQueue;
class CInlineItem;
class CAsyncFileQueue;
class CIvfAsyncFile;

/**
 * Interface of the IVF document class.
 * 
 * @ingroup Ivf_Classes
 * 
 * @DESCRIPTION
 *   This class provides methods for manipulation of Open Inventor documents.
 *   
 *   Note: Although the class name is CIvfDocument, the header file name is
 *   IvfDocument.h.
 * 
 * @SEE_ALSO
 *    CIvfApp,
 *    CIvfArchiveInput,
 *    CIvfArchiveOutput,
 *    CIvfComponent,
 *    CIvfMainFrame
 * 
 * 
 */ 

class IVF_API CIvfDocument
{
  friend CIvfComponent;

 public:
  CIvfDocument();
  ~CIvfDocument();

 public:
  /**
   * Set the fileHeader. This is needed for 3SpaceAssistant's
   * reading of a dxf file so that there is a valid fileHeader.
   */
  void IvfSetFileHeader(LPCSTR header) { strcpy(m_fileHeader, header); }

  /**
   * This method invokes IvfDeleteContents and
   * unrefs the current scene graph.
   */
  virtual BOOL IvfOnNewDocument();

  /**
   * This method loads a file given a path name.  The
   * pointer for the scene graph that is produced is
   * stored in m_pSceneRoot.
   */
  virtual BOOL IvfOnOpenDocument(LPCTSTR lpszPathName);

  /**
   * This method stores the scene graph pointed to by
   * m_pSceneRoot in the file specified by the argument.
   */
  virtual BOOL IvfOnSaveDocument(LPCTSTR lpszPathName);

  /**
   * This method loads a file given file handle.  The
   * pointer for the scene graph that is produced is
   * stored in m_pSceneRoot.
   */
  virtual BOOL IvfOnOpenDocument(UINT hFile);
   
  /**
   * This method stores the scene graph pointed to by
   * m_pSceneRoot in the file specified by the argument.
   */
  virtual BOOL IvfOnSaveDocument(UINT hFile);

#if _MSC_VER >= 1300
  //  --romain dec2001 
  /**
   * New version of IvfOnOpenDocument for visual Studio .net
   * in the new CFILE class : hfile is an HANDLE 
   */
  virtual BOOL IvfOnOpenDocument(HANDLE hFile);
  /**
   * New version of IvfOnSaveDocument for visual Studio .net
   * in the new CFILE class : hfile is an HANDLE 
   */
  virtual BOOL IvfOnSaveDocument(HANDLE hFile);
#endif

  /**
   * This version uses a CFile object
   */
  virtual BOOL IvfOnSaveDocument(const CFile* cFile);

  /**
   * This method loads a file given an archive object. The
   * pointer for the scene graph that is produced is
   * stored in m_pSceneRoot.
   */
  virtual BOOL IvfOnOpenDocument(CArchive &rArchive);

  /**
   * This method stores the scene graph pointed to by
   * m_pSceneRoot in the file specified by the argument.
   */
  virtual BOOL IvfOnSaveDocument(CArchive &rArchive);

  /**
   * Pushthrough message handler from CDocument class
   * Note this is NOT a virtual (You already have control
   * from CDocument derived class)
   */
  BOOL IvfOnOpenDocumentMessage(LPCTSTR lpszPathName);

  /**
   * Opens document and adds it to the current document scene graph
   */
  void IvfImportDocument(LPTSTR PathName);

  /**
   * This enum guides the behavior of IvfOnOpenDocumentMessage.
   * It is set by the loading calls OnFileImport and OnFileLoad.
   //
  */
  static enum IVFDOC_OPEN_ENUM {
    IVFDOC_OPEN_NORMAL, 
    IVFDOC_OPEN_LOAD, 
    IVFDOC_OPEN_IMPORT
  };
  IVFDOC_OPEN_ENUM m_eOpenType;

  /**
   *  use this to pass create args to the document
   */
  void CIvfDocument::IvfInitDocument(void *pCreateArgs);

  /**
   * This method unrefs the scene graph pointed
   * to by m_pSceneRoot
   */
  virtual void IvfDeleteContents();

  /**
   *  This method retrieves the Url name for this Document
   */
  virtual LPCTSTR IvfGetUrlName(void);

  /**
   *  returns whether the document is embedded or not.  if you
   *  have access to the IsEmbedded() member from the C(Ole)Document
   *  class, use that.
   */
  virtual BOOL IvfIsEmbedded();

  /**
   * This method checks the titleHintFound flag and sets
   * the title if it is set.
   */
  virtual BOOL IvfIsTitleSet(void);
  virtual void  IvfUpdateTitle(void);
  virtual LPCTSTR IvfGetTitleString(void);

  /**
   * This retrieves the DocInfo string if it was set.
   */
  virtual BOOL IvfIsInfoSet(void);
  virtual LPCTSTR IvfGetDocInfoString(void);

  /**
   * This processes the OnFileViewInfo (forwarded from the application)
   */
  virtual void OnFileViewInfo(void);

  /**
   * This method sets m_pSceneRoot to pRoot.  The scene graph
   * previously pointed to by m_pSceneRoot (if any) is unrefed.
   */
  virtual void IvfSetSceneGraph(SoSeparator *pRoot);
  SoSeparator *IvfGetDocSceneGraph();

  /**
   * This method gets the currently active camera
   */
  SoCamera *IvfGetActiveCamera(int in_ix = -1);
  int IvfGetActiveCameraIX();
  SoGroup *IvfGetActiveCamParent();
  SbPList *IvfGetCameraList();
  
  /**
   * Sets the camera type that will be created if no cameras are
   * found in the scene graph (see SoPerspectiveCamera and SoOrthographicCamera). By
   * default an SoPerspectiveCamera will be created if no cameras are found.
   * 
   * Note: The set method will only take effect the next time a scene graph is
   * loaded (and if no cameras are found).
   */
  virtual void setCameraType(SoType type);
  
  /**
   * Gets the camera type that will be created by the viewer if no cameras are
   * found in the scene graph (see SoPerspectiveCamera and SoOrthographicCamera). 
   */
  SoType       getCameraType()
    { return m_cameraType; }

  /**
   * Replace the camera specified by the index.
   * returns the camera that was there, disposition is up to
   * the caller.
   */
  SoCamera *IvfReplaceCamera(SoCamera *cam, int ix);

  /**
   * This method is invoked by the document object prior
   * to saving the scene graph.  It allows the component
   * to undo any changes it has done to the scene graph.
   */
  virtual void IvfPrepareForSave();

  /**
   * This method is invoked by the document object to
   * notify the component that the scene graph save
   * operation has completed.  The component is then
   * free to re-institute any scene graph modifications
   * it has made (i.e. remove all cameras).
   */
  virtual void IvfPostSave();

  /**
   * This method locates all of the SoWWWAnchor nodes
   * in the document object's scene graph and places
   * the path to each node in a list pointed to by
   * m_pAnchorList.
   */
  virtual void IvfFindAnchors(SoGroup *root);

  /**
   * This method returns TRUE if this application is an
   * OLE server, FALSE otherwise.
   */
  BOOL IvfIsOleSrvr();

  /**
   * Add a headlight hint and set the contents to the value passed.
   */
  void IvfUpdateHeadlightHint(BOOL bOn);

  /**
   * This method loads the contents of an Open Inventor file.
   * A pointer to the scene graph is returned. The ref count
   * for the returned scene graph is zero.
   */
  static SoSeparator *IvfReadAll(SoInput *, CIvfDocument *);

  /**
   * This method saves the scene graph pointed to by pRoot in the
   * file specified by lpFname.  If successful, TRUE is returned.
   */
  static BOOL IvfSaveSceneGraph(LPCTSTR lpFname, SoSeparator *pRoot, 
                                CIvfDocument *);

  /**
   * This method loads the file specified by lpFname, and returns
   * a pointer to the scene graph.  The ref count for the
   * returned scene graph is zero.  Null is returned if the load fails.
   */
  static SoSeparator *IvfLoadSceneGraph(LPCTSTR lpFname,
                                        CIvfDocument *);

  /**
   * This method saves the scene graph pointed to by pRoot in the
   * file specified by hFile.  If successful, TRUE is returned.
   */
  static BOOL IvfSaveSceneGraph(UINT hFile, SoSeparator *pRoot,
                                CIvfDocument *);
   
  /**
   * This method saves the scene graph pointed to by pRoot in the
   * file stored in the SoOutput.  If successful, TRUE is returned.
   */
  static BOOL IvfSaveSceneGraph(SoOutput* out, SoSeparator *pRoot,
                                CIvfDocument *);

  /**
   * This method loads the file specified by lpFname, and returns
   * a pointer to the scene graph.  The ref count for the
   * returned scene graph is zero.  Null is returned if the load fails.
   */
  static SoSeparator *IvfLoadSceneGraph(UINT hFile, CIvfDocument *);

  /**
   * This method saves the scene graph pointed to by pRoot in the
   * archive specified by rArchive.  If successful, TRUE is returned.
   */
  static BOOL IvfSaveSceneGraph(CArchive &rArchive, SoSeparator *pRoot,
                                CIvfDocument *);

  /**
   * This method loads from the archive specified by lpFname, and returns
   * a pointer to the scene graph.  The ref count for the
   * returned scene graph is zero.  Null is returned if the load fails.
   */
  static SoSeparator *IvfLoadSceneGraph(CArchive &rArchive,
                                        CIvfDocument *);

  /**
   * This method deletes the scene graph pointed to by m_pSceneRoot.
   */
  virtual void IvfDeleteSceneGraph();
   
  /**
   * This method notifies the view object that the scene graph has
   * changed (but is not necessarily complete - see next).
   */
  virtual void IvfSceneGraphChanged();

  /**
   * Called to indicate all the inlines/textures have been retrieved.
   */
  virtual void IvfSceneGraphCompleted();

  /**
   * Forces resolution of inlines and replaces them with separators.
   * Used in embedded situation.
   */
  virtual void IvfScrubInlines();

  /**
   * This method is invoked by IvfOnLoadUrlMessage to indicate
   * that the location has changed.  An VRML viewer application 
   * can use this method to update the location display.  The default
   * implementation of this method does nothing.
   */
  virtual void IvfOnLocationChanged(LPCTSTR urlName);

  /**
   * This method is invoked by IvfOnCmdMsg to handle update
   * of the viewpoint menu.
   */
  virtual void IvfOnUpdateViewpoints(CCmdUI* pCmdUI);

  virtual void IvfRemoveViewpointMenu(CCmdUI* pCmdUI);

  /**
   *  return the number of components attached to this document
   */
  int IvfGetNumComponents();

  /**
   * Called by application OnIdle to process the inline queue.
   */
  virtual BOOL IdleProcessInlines(void);

  /**
   * This method returns TRUE if the named file is a valid Open Inventor file
   */
  static BOOL IvfIsInventorFile(LPCTSTR lpszFileName);

  /** File type */
  static enum IVF_FILETYPE {
    /** IV type */
    IVF_FILETYPE_IV, 
    /** VRML type */
    IVF_FILETYPE_VRML,
    /** VRML2 type */
    IVF_FILETYPE_VRML2,
    /** VRML3 type */
    IVF_FILETYPE_VRML3
  };

  void IvfSetFileType(IVF_FILETYPE);
  IVF_FILETYPE IvfGetFileType(void);

  virtual void IvfSetBgColor(const SbColor &);
  virtual SbColor &IvfGetBgColor(void);

  /**
   * This message processes thread specific messages
   //
   *    InlineQueue messages  (WMIVF_PROCPENDINGINLINE)
   *    LoadUrl messages      (WMIVF_LOADURL)
   //
  */
  virtual BOOL IvfPreTranslateMessage(MSG *);

  /**
   *  Override this to create an async file object derived
   *  from CIvfAsyncFile
   */
  virtual CIvfAsyncFile *IvfCreateAsyncFile(void *data);

  /**
   * Use this to open a new URL.
   */
  virtual BOOL IvfOnOpenUrl(LPCTSTR url);

  /**
   *  Use this when done with an async file - removes it from
   *  the queue
   */
  void IvfRemoveAsyncFile(CIvfAsyncFile *file);
  void IvfAbortAllAsyncFiles();

  /**
   *  Call to determine if there are any async files in the queue
   */
  BOOL IvfIsAsyncFilesPending();

  /**
   *  Call to determine if there are any inlines in the queue
   */
  int IvfIsInlinesPending();

  /**
   *  Enable or disable counter accumulations.  Called by frame
   *  on new graph. Override if you want to alter behavior.
   */
  virtual void IvfEnableStatAccumulation(BOOL bDoAccum);

  /**
   *  Clear the counters.  If ClearAll==FALSE, will not clear node
   *  counter (that's usually static per scene).
   */
  virtual void IvfClearStatCounters(BOOL bClearAll=FALSE);

  /**
   *  Scene graph stat values. These are public for anyone to get to.
   */
  ULONG m_nTriCount, m_nNodeCount, m_nLineCount, m_nPointCount;

  /**
   *  Indicates if there is/are SoVRMLTouchSensor(s) in the
   *  scene graph
   */
  BOOL  m_bHasTouchSensors;
  static BOOL m_queueingOff;
  void SetBaseUrlPath(LPCTSTR b_path);
  LPCTSTR GetBaseUrlPath(void) { return(m_BasePath); }
  static TCHAR m_StaticPath[IVF_MAX_URL_NAME_LENGTH];

 protected: //PROTECTED_TO_DOCUMENT
  /**
   * pointer to the root of the scene graph
   */
  SoSeparator *m_pSceneRoot;

  /**
   * This method is invoked from IvfSceneGraphChanged.  It
   * removes all of the cameras contained in the document
   * object's scene graph.  The cameras are placed in
   * a list pointed to by m_pCamList.  Each of the
   * cameras in the list are referenced.
   */
  virtual void IvfRemoveCameras(SoGroup *root);

  /**
   * This method restores the cameras removed from the 
   * document object's scene graph.
   */
  virtual void IvfRestoreCameras(SoGroup *root);

  /**
   * This method destroys the camera list pointed to by
   * m_pCamList. All of the cameras contained in the
   * list are unreferenced.
   */
  virtual void IvfDeleteCameraList();

  /**
   * This method is invoked when it receives the WMIVF_LOADURL
   * registered message.  If urlName points to a local file,
   * The default implementation replaces the document's scene
   * graph with the contents of the file.  If urlName does not
   * refer to a local file, the url is referred to a Url retrieval
   * mechanism (currently none).
   */
  virtual BOOL IvfOnLoadUrlMessage(CIvfAsyncFile *pIvfASFile);

  /**
   * This method sets up the mechanism to trigger IvfOnFetchUrl
   * each time the user clicks the left mouse button while
   * the cursor is placed over an SoWWWAnchor node.  This
   * mechanism is put in place only if m_nEnableUrlFetch
   * is TRUE.  This method calls SoWWWAnchor::setFetchURLCallBack
   * to set the URL fetch callback to IvfStaticFetchUrlCB.  An
   * application should overload this method if a different
   * URL fetch mechanism is desired.
   */
  virtual void IvfSetupUrlFetchCallback();

  /**
   * This method disables IVF's URL fetch callback mechanism.
   */
  virtual void IvfRemoveUrlFetchCallback();

  /**
   * If m_nEnableUrlFetch is TRUE and m_nEnableSelection is FALSE, 
   * this method is invoked when 
   * a user clicks the mouse button while the cursor is placed 
   * over an SoWWWAnchorNode (or one of its children).  When 
   * invoked, this method posts the WMIVF_LOADURL registered 
   * message to the application frame window. wparam is 
   * set to 0, and lparam contains a pointer to a null terminated 
   * string containing the URL name.
   */
  virtual void IvfOnFetchUrl(LPCTSTR urlName);

  /**
   * This method is invoked by SoWWWAnchor when the user
   * clicks on a URL.  If m_nEnableUrlFetch is TRUE and
   * m_nEnableSelection is FALSE, this method invokes
   * IvfOnFetchUrl.
   */
  static void IvfStaticFetchUrlCB(const SbString &url, 
                                  void *userData, 
                                  SoWWWAnchor *node);

  /**
   * Same as above, except for SoWWWInline (when inline is
   * traversed).
   */
  static void IvfStaticFetchInlineUrlCB(const SbString &url, 
                                        void *userData,
                                        SoNode *node);

  static BOOL IvfStaticFetchTexture2UrlCB(const SbString &url, 
                                          void *userData,
                                          void *node);

  /**
   * This method is called by the file retrieval layer to check if
   * retrieved file is an inline or not.  Processes if in the queue.
   * Returns: TRUE if file was processed as an inline: nothing more
   * should be done with the file.  status indicates success/error:
   *   0 = success
   */
  BOOL IsPendingAsyncRequest(CIvfAsyncFile *pIvfASFile, int &status);

  /**
   *  called when the async file is local (or resolved)
   */
  void OpenLocalAsyncDoc(CIvfAsyncFile *);
   
  /**
   * called to process the WMIVF_PROCPENDINGINLINE message
   */
  void OnProcessPendingInline(WPARAM, LPARAM);
  void ProcessPendingTexture2(CInlineItem *, BOOL);

  void PostInlineLocation(SoNode *, LPTSTR , void *);
  LPTSTR MakeFullUrlPath(LPTSTR out_url, LPCTSTR in_url);

  /**
   *  scratch file management
   */
  BOOL IsOKFile(LPTSTR filename);
  BOOL MakeScratchName(LPTSTR new_path, LPTSTR filename);
  void CleanupScratchFile(LPTSTR filename);

  /**
   *  Counts nodes, triangles, lines, and points in the
   *  Doc scene graph (m_pSceneRoot)
   */
  void CountPrimitives();

  /**
   * These contain info about any contained camera switches.
   */
  SoSwitch *m_pCameraSwitch;
  SoGroup *m_pCameraSwitchParent;
  SoInfo *m_pCameraSwitchInfo;

  SoType  m_cameraType;

  /**
   *  Do NOT expect this to hang around.  This is used as very
   *  very temporary storage internally to save the default camera
   *  group between ::IvfRestoreCameras and ::IvfRemoveCameras.
   *  allows us to keep the definition for restoral even though
   *  it isn't being stored with the scene graph (!Embedded condition)
   */
  SoGroup *m_pDefaultCameraGroup;
   
  /**
   * pointer to a list of the cameras removed from the scene graph.
   */
  SbPList *m_pCamList;

  /**
   * pointer to the parent of each camera in m_pCamList.
   * Used to restore the cameras.
   */
  SbPList *m_pCamParentList;

  /**
   * index to the active camera
   */
  int m_nActiveCameraIX;

  BOOL IVOpenError;

  /**
   * pointer to info nodes used as place holders in the
   * scene graph to mark the location we removed the
   * cameras from.
   */
  SbPList *m_pInfoList;

  /**
   * a list of paths to all of the SoWWWAnchor nodes in
   * the scene graph.
   */
  SoPathList *m_pAnchorList;

  /**
   * saved background color & headlight node
   */
  SoInfo *m_pBackColorInfo, *m_pHLInfo;

  /**
   * saved viewport window size and parent
   */
  SoGroup *m_pVPWindowSizePar; 
  SoInfo *m_pVPWindowSize;

  /**
   * flag that enables url fetching
   */
  BOOL m_nEnableUrlFetch;

  /**
   * flag that enables URL display mechanism
   */
  BOOL m_nEnableUrlDisplay;

  /**
   * flag that enables the viewpoint menu
   */
  BOOL m_nEnableViewpoints;

  /**
   * buffer used by IvfLoc2Callback to keep track of the
   * the most recent URL name.
   */
  TCHAR m_urlName[IVF_MAX_URL_NAME_LENGTH];

  /**
   * type of file to output.  default is IVF_FILETYPE_IV
   */
  IVF_FILETYPE m_fileType;
  char m_fileHeader[256];

  /**
   *  following is for inline support
   *  rickb
   //
  */
  void AddInlineChild(CInlineItem *);
  void AddInlineChild(SoNode *node, LPTSTR filename, void *cb);
  CInlineQueue *m_pInlineQueue;
  CAsyncFileQueue *m_pAsyncQueue;
  TCHAR m_BasePath[IVF_MAX_URL_NAME_LENGTH];
  TCHAR m_OriginalPath[IVF_MAX_URL_NAME_LENGTH];
  BOOL m_bSceneGraphComplete, m_bNewGraphPrepped, m_bBasePathPreset,
    m_bContainsInlines;

  TCHAR* lcl_scratch_filename[MAX_SCRATCH_FILES];
  int n_scratch_files;
  /**
   * probably never need more than one, but
   * this will provide for future capability,
   * if needed
   */

  /**
     //
     * Following is for hints support
     //
  */
  static BOOL viewerSpeedHintSet;
  static BOOL autoClipOffHintSet;
  static BOOL titleHintSet;
  static BOOL anyLightsSet;

  BOOL m_bTitleHintSet;
  BOOL m_bDocInfoSet;
  BOOL m_bSaveAsBinary;
  BOOL m_bDefHeadlightVal;
  /**
   * member version
   */

  float motionSpeedHintVal;
  CIvfComponent::IvfViewerType viewerTypeHintSet;

  SbString *sceneTitle, *docInfoString;
  void IvfScanForHints(SoNode *root);

  void DetermineViewerType(const SoInfo *info);
  void DetermineViewerSpeed(const SoInfo *info);
  void DetermineBackgroundColor(const SoInfo *info);
  void DetermineTitle(const SoInfo *info);
    
  /**
   * Callbacks used when searching for hints
   */
  static SoCallbackAction::Response InfoHintCB(void *userData, 
                                               SoCallbackAction *action,
                                               const SoNode *node);

  static SoCallbackAction::Response NavInfoCB(void *userData, 
                                              SoCallbackAction *action,
                                              const SoNode *node);

  static SoCallbackAction::Response WorldInfoCB(void *userData, 
                                                SoCallbackAction *action,
                                                const SoNode *node);

  static SoCallbackAction::Response WWWInlineCB(void *userData,
                                                SoCallbackAction *action,
                                                const SoNode *node);

  static SoCallbackAction::Response VRMLInlineCB(void *userData,
                                                 SoCallbackAction *action,
                                                 const SoNode *node);

  static SoCallbackAction::Response CheckForLightsCB(void *userData, 
                                                     SoCallbackAction *action,
                                                     const SoNode *node);

  static SoCallbackAction::Response CountNodesCB(void *userData, 
                                                 SoCallbackAction *action,
                                                 const SoNode *node);

  static void CountTrisCB(void *userData, 
                          SoCallbackAction *action,
                          const SoPrimitiveVertex *,
                          const SoPrimitiveVertex *,
                          const SoPrimitiveVertex *);

  static void CountLinesCB(void *userData, 
                           SoCallbackAction *action,
                           const SoPrimitiveVertex *,
                           const SoPrimitiveVertex *);

  static void CountPointsCB(void *userData, 
                            SoCallbackAction *action,
                            const SoPrimitiveVertex *);
};

extern UINT WMIVF_PROCPENDINGINLINE;
extern UINT WMIVF_LOADURL;

#if defined(_DEBUG)
void DumpSceneGraph(SoNode *pGraph);
#endif

#endif

