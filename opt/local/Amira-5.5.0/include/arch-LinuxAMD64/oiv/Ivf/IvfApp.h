/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef __CIVFAPP_H__
#define __CIVFAPP_H__

#include <Inventor/SbBasic.h>

class CIvfDocument ;
class CIvfMainFrame ;
class CIvfComponent;

class CDocument ;
class CDocTemplate ;
class CView ;
class CWnd ;
class CFrameWnd ;

/**
 * This type defines the interface for the application supplied conversion 
 * method that converts a MFC CView object pointer into an IVF 
 * CIvfComponent Object pointer.
 */
typedef CIvfComponent * (*IvfCvtAfxViewProc)(CView *) ;

/**
 *  This type defines the interface for the application supplied conversion 
 *  method that converts an IVF CIvfComponent Object pointer into an MFC 
 *  CView object pointer.
 */
typedef CView * (*IvfCvtIvfComponentProc)(CIvfComponent *) ;

/**
 *  This type defines the interface for the application supplied conversion 
 *  method that converts a MFC CWnd object pointer into an IVF 
 *  CIvfComponent Object pointer.
 */
typedef CIvfComponent * (*IvfCvtAfxWndProc)(CWnd *) ;

/**
 *  This type defines the interface for the application supplied conversion 
 *  method that converts an IVF CIvfComponent Object pointer into an MFC 
 *  CWnd object pointer.
 */
typedef CWnd * (*IvfCvtIvfComponentProcW)(CIvfComponent *) ;

/**
 *  This type defines the interface for the application supplied conversion 
 *  method that converts a MFC CDocument object pointer into an IVF 
 *  CIvfDocument Object pointer.
 */
typedef CIvfDocument * (*IvfCvtAfxDocProc)(CDocument *) ;

/**
 *  This type defines the interface for the application supplied conversion 
 *  method that converts an IVF CIvfDocument Object pointer into an MFC 
 *  CDocument object pointer.
 */
typedef CDocument * (*IvfCvtIvfDocProc)(CIvfDocument *) ;

/**
 *  This type defines the interface for the application supplied conversion 
 *  method that converts a MFC CFrameWnd object pointer into an IVF 
 *  CIvfMainFrame Object pointer.
 */
typedef CIvfMainFrame * (*IvfCvtAfxFrameProc)(CFrameWnd *pFrame);


/**
 * Interface of the IVF application class.
 * 
 * @ingroup Ivf_Classes
 * 
 * @DESCRIPTION
 *   This class provides methods for initialization of Open Inventor and the IVF
 *   Class library. 
 *   
 *   Note: Although the class name is CIvfApp, the header file name is IvfApp.h.
 *   
 *   #m_pCreateArgs is a pointer to an array of type int containing (at least) the
 *   following:
 *   
 *   - #m_pCreateArgs[0] = Enable viewer decorations (default = TRUE) @BR
 *     If enabled, the viewer decorations (thumbwheels, etc.) are turned on. 
 *   - #m_pCreateArgs[1] = Enable display of URL (default = FALSE) @BR
 *     If enabled, IvfOnUrlDisplayChanged will be called. 
 *   - #m_pCreateArgs[2] = Enable viewpoints menu (default = FALSE) @BR
 *     If enabled, a Viewpoints menu will be added to the menu bar. 
 *   - #m_pCreateArgs[3] = Enable URL fetch callback (default = FALSE) @BR
 *     If enabled, IvfOnFetchUrl will be called. 
 * 
 * @SEE_ALSO
 *    CIvfArchiveInput,
 *    CIvfArchiveOutput,
 *    CIvfComponent,
 *    CIvfDocument,
 *    CIvfMainFrame
 * 
 * 
 */ 

class IVF_API CIvfApp
{
 public:

  /**
   * Constructor.
   */
  CIvfApp();
  /**
   * Destructor.
   */
  ~CIvfApp();

  /**
   *  This method intializes the IVF class library.  It is called 
   *  from InitInstance in the MFC application object.
   */
  static void IvfInitInstance(CWinApp *pApp,
                              CIvfApp *pIvfApp,
                              IvfCvtAfxViewProc pAfxViewProc,
                              IvfCvtIvfComponentProc pIvfComponentProc,
                              IvfCvtAfxWndProc pAfxWndProc,
                              IvfCvtIvfComponentProcW pIvfComponentProcW,
                              IvfCvtAfxDocProc pAfxDocProc,
                              IvfCvtIvfDocProc pIvfDocProc,
                              IvfCvtAfxFrameProc pAfxFrameProc,
                              void *pCreateArgs,
                              BOOL nCreateComponent) ;


  /**
   * This method releases any resources allocated by Ivf
   */
  static void IvfExitInstance();
        
  /**
   * This method connects MFC's Idle processing to the SoWin component library's
   * delay queue processing mechanism.
   */
  static void IvfOnIdle( LONG lCount );

  /**
   * This method is used to initialize the SoWin component library.
   */
  static void IvfInitSoWin(CWnd *pTopLevel);
        
  /**
   * This method returns a pointer to the application object.
   */
  static CIvfApp *IvfGetApp();

  /**
   * This method returns a pointer to the application document template object.
   */
  static CDocTemplate *IvfGetDocTemplate();

  /**
   * Given a pointer to an IVF component object, this method will return a pointer to
   * the corresponding IVF document object. If the argument is NULL, the document
   * corresponding to the active component is returned. If the application is an MFC
   * dialog-based application, this method returns NULL.
   */
  static CIvfDocument *IvfGetDocument(CIvfComponent *pIvfComponent = NULL) ;
        
  /**
   * Given a pointer to an IVF document object, this method will return a pointer to
   * the corresponding IVF component object. The corresponding component is derived
   * by locating the active MFC view associated with the document, and converting the
   * MFC view pointer to an IVF component pointer using the application supplied
   * conversion method.
   */
  static CIvfComponent *IvfGetComponent(CIvfDocument *pIvfDoc = NULL) ;
        
  /**
   * This method returns a pointer to the application frame window.
   */
  static CFrameWnd *IvfGetAfxFrame(CIvfComponent *pIvfComponent = NULL) ;

  /**
   * This method returns a pointer to the application frame window.
   */
  static CIvfMainFrame *IvfGetIvfFrame() ;

  /**
   * Given a pointer to an IVF component object, this method calls the
   * application-supplied conversion method to perform a type safe cast down to the
   * application view class and then a cast up to the MFC view class. A pointer to
   * the MFC view object corresponding to the IVF component object is returned. If
   * the argument is NULL, a pointer to the active view is returned. If the
   * application is dialog based, this method returns NULL.
   */
  static CView *IvfGetAfxView(CIvfComponent *pIvfComponent = NULL) ;

  /**
   * Given a pointer to an IVF component object, this method calls the
   * application-supplied conversion method to perform a type safe cast down to the
   * application window class and then a cast up to the MFC window class. A pointer
   * to the MFC window object corresponding to the IVF component object is returned.
   * If the argument is NULL, a pointer to the active component is returned. If the
   * application is not dialog based, this method returns NULL.
   */
  static CWnd *IvfGetAfxWnd(CIvfComponent *pIvfComponent = NULL) ;

  /**
   * Given a pointer to an IVF component object, this method first locates the
   * corresponding IVF document object. It then calls the application supplied
   * conversion method to perform a type safe cast of the IVF document object pointer
   * down to the application document class and then a cast up to the MFC document
   * class. A pointer to the MFC document object corresponding to the IVF component
   * object is returned. If the argument is NULL, a pointer to the document object
   * corresponding to the active MFC view is returned. If the application is dialog
   * based, this method returns NULL.
   */
  static CDocument *IvfGetAfxDocument(CIvfComponent *pIvfComponent = NULL) ;

  /**
   * Given a pointer to an IVF document object, calls the application-supplied
   * conversion method to perform a type safe cast of the IVF document object pointer
   * down to the application document class, and then a cast up to the MFC document
   * class. A pointer to the MFC document object corresponding to the IVF document
   * object is returned. 
   */
  static CDocument *IvfGetAfxDocument(CIvfDocument *pIvfDoc) ;


  /**
   * This method invokes the application-supplied conversion method to convert an MFC
   * view object pointer into an IVF component object pointer. If the application is
   * dialog based, NULL is returned.
   */
  static CIvfComponent *ToIvfComponent(CView *pAfxView) ;

  /**
   * This method invokes the application-supplied conversion method to convert an IVF
   * component object pointer into an MFC view object pointer. If the application is
   * dialog based, NULL is returned.
   */
  static CView *ToAfxView(CIvfComponent *pIvfComponent) ;

  /**
   * This method invokes the application-supplied conversion method to convert an MFC
   * window object pointer into an IVF component object pointer. If the application
   * is not dialog based, NULL is returned.
   */
  static CIvfComponent *ToIvfComponentW(CWnd *pAfxWnd) ;

  /**
   * This method invokes the application-supplied conversion method to convert an IVF
   * component object pointer into an MFC window object pointer. If the application
   * is not dialog based, NULL is returned.
   */
  static CWnd *ToAfxWnd(CIvfComponent *pIvfComponent) ;

  /**
   * This method invokes the application-supplied conversion method to convert an MFC
   * document object pointer into an IVF document object pointer. If the application
   * is dialog based, NULL is returned.
   */
  static CIvfDocument *ToIvfDocument(CDocument *pAfxDoc) ;

  /**
   * This method invokes the application-supplied conversion method to convert an IVF
   * document object pointer into an MFC document object pointer. If the application
   * is dialog based, NULL is returned.
   */
  static CDocument *ToAfxDocument(CIvfDocument *pIvfDoc) ;


  /**
   * This method invokes the application-supplied conversion method to convert an IVF
   * document object pointer into an MFC document object pointer. If the application
   * is dialog based, NULL is returned.
   */
  static CIvfMainFrame *ToIvfFrame(CFrameWnd *pFrame) ;

  /**
   * This method returns a pointer to the arguments passed to the of the IVF view
   * class for component creation.
   */
  static void *IvfCreateArgs();

  /**
   * This method returns a Boolean that indicates if this an MDI application.
   */
  static BOOL IvfIsMdi();

  /**
   *  Utility routine to add afx object to Ivf corresponding
   *  list.  Not all objects in an IVF application have to be
   *  derived from CIvfComponent or CIvfDocument.  To distinguish
   *  between IVF and non-IVF objects, we keep a list of all
   *  views and documents that have been derived from Ivf
   *  equivalent classes.
   */
  static void IvfAddToIvfAfxObjectList(CObject *pAfxObj);

  /**
   *  Remove a view from the IVF view list.
   */
  static void IvfRemoveFromIvfAfxObjectList(CObject *pAfxObj);


  /**
   * Check if a CView object is derived from CIvfComponent
   */
  static BOOL IvfIsIvfComponent(CView *pAfxView);

  /**
   *  Same for documents.
   */
  static BOOL IvfIsIvfDocument(CDocument *pAfxDoc);


  /**
   *  pointer to the IVF application object
   */
  static CIvfApp *m_pApp ;

  /**
   *  Pointer to the application document template object
   */
  static CDocTemplate *m_pDocTemplate ;

  /**
   *  Pointer to the arguments for SoWin component creation
   */
  static void *m_pCreateArgs ;

  /**
   *  MDI flag
   */
  static BOOL m_nMDI ;

  /**
   *  Enable MT support in Open Inventor
   *  (call SoDB::threadInit instead of SoDB::init)
   */
  static void enableMultiThread(void);

 private:
  // pointer to application supplied type safe pointer
  // conversion methods
  static IvfCvtAfxViewProc      m_pAfxViewProc ;
  static IvfCvtIvfComponentProc m_pIvfComponentProc ;
  static IvfCvtAfxWndProc       m_pAfxWndProc ;
  static IvfCvtIvfComponentProcW m_pIvfComponentProcW ;
  static IvfCvtAfxDocProc   m_pAfxDocProc ;
  static IvfCvtIvfDocProc   m_pIvfDocProc ;
  static IvfCvtAfxFrameProc m_pAfxFrameProc ;

  // A list of all of the IVF components in the application.
  static CPtrList *m_pIvfAfxObjectList;
  static int isMTEnabled;

  ///////////////////////EXCEPTION METHODS/////////////////////////////////////
  //
  // #grouped IvfGetIvfFrame()
  // #grouped ToIvfFrame(CFrameWnd * pFrame)
  //
  /////////////////////////////////////////////////////////////////////////////

};


/**
 *  IVF_INIT_INSTANCE Macro
 *  This macro is invoked from the MFC application objects InitInstance method.
 *  It invokes the CIvfApp method IvfInitInstance to intialize IVF.
 */
#ifdef __TGS_DEMO_UNLOCK
#include <lock/demoUnlock.h>
#include <Inventor/lock/SoLockMgr.h>
#define IVF_INIT_INSTANCE_BETA2(CFrameClass,CViewClass,CDocClass,pVwrClass,pCreateArgs,nMDI) \
{ \
        SoLockManager::SetUnlockString(DEMO_UNLOCK_STRING) ; \
        CIvfApp::IvfInitInstance(\
                this,\
                this,\
                IvfCvtAfxView, \
                IvfCvtIvfComponent, \
                NULL,\
                NULL,\
                IvfCvtAfxDoc, \
                IvfCvtIvfDoc, \
                pCreateArgs, \
                TRUE); \
}

#define IVF_INIT_INSTANCE(pApp,IvfCvtAfxView,IvfCvtIvfComponent,IvfCvtAfxWnd,IvfCvtIvfComponentW,IvfCvtAfxDoc,IvfCvtIvfDoc,IvfCvtAfxFrame,pCreateArgs,nCreateVwr) \
{ \
        SoLockManager::SetUnlockString(DEMO_UNLOCK_STRING) ; \
        CIvfApp::IvfInitInstance( \
                pApp,\
                pApp,\
                IvfCvtAfxView, \
                IvfCvtIvfComponent, \
                IvfCvtAfxWnd, \
                IvfCvtIvfComponentW, \
                IvfCvtAfxDoc, \
                IvfCvtIvfDoc, \
                IvfCvtAfxFrame,\
                pCreateArgs, \
                nCreateVwr); \
}

#else
#define IVF_INIT_INSTANCE_BETA2(CFrameClass,CViewClass,CDocClass,pVwrClass,pCreateArgs,nMDI) \
{ \
        CIvfApp::IvfInitInstance(\
                this,\
                this,\
                IvfCvtAfxView, \
                IvfCvtIvfComponent, \
                NULL,\
                NULL,\
                IvfCvtAfxDoc, \
                IvfCvtIvfDoc, \
                IvfCvtAfxFrame,\
                pCreateArgs, \
                TRUE); \
}

#define IVF_INIT_INSTANCE(pApp,IvfCvtAfxView,IvfCvtIvfComponent,IvfCvtAfxWnd,IvfCvtIvfComponentW,IvfCvtAfxDoc,IvfCvtIvfDoc,IvfCvtAfxFrame,pCreateArgs,nCreateVwr) \
{ \
        CIvfApp::IvfInitInstance( \
                pApp,\
                pApp,\
                IvfCvtAfxView, \
                IvfCvtIvfComponent, \
                IvfCvtAfxWnd, \
                IvfCvtIvfComponentW, \
                IvfCvtAfxDoc, \
                IvfCvtIvfDoc, \
                IvfCvtAfxFrame,\
                pCreateArgs, \
                nCreateVwr); \
}
#endif


/**
 *  This macro is used to define the type safe conversion methods
 *  for view based applications.  Note there is a standard version
 *  and an ole version (see the IvfCvtAfxFrame method).
 * 
 */

#ifndef __AFXOLE_H__

#define IVF_AFX_CONVERSION_METHOD(AppViewClassName,AppDocClassName) \
static CIvfComponent *IvfCvtAfxView(CView *pAfxView) \
{ \
  AppViewClassName *pView = (AppViewClassName *) pAfxView ; \
  return pView ; \
} \
static CView *IvfCvtIvfComponent(CIvfComponent *pIvfComponent) \
{ \
  AppViewClassName *pView = (AppViewClassName *) pIvfComponent ; \
  return pView ; \
} \
static CIvfDocument *IvfCvtAfxDoc(CDocument *pAfxDoc) \
{ \
  AppDocClassName *pDoc = (AppDocClassName *) pAfxDoc ; \
  return pDoc ; \
} \
static CDocument *IvfCvtIvfDoc(CIvfDocument *pIvfDoc) \
{ \
  AppDocClassName *pDoc = (AppDocClassName *) pIvfDoc ; \
  return pDoc ; \
}\
static CIvfMainFrame *IvfCvtAfxFrame(CFrameWnd *pFrame)\
{\
  if (pFrame->IsKindOf( RUNTIME_CLASS(CMainFrame) ) )\
  {\
        CMainFrame *pMainFrame = (CMainFrame *)pFrame;\
        CIvfMainFrame *pIvfFrame = (CIvfMainFrame *)pMainFrame;\
        return pIvfFrame;\
  }\
  else\
        return NULL;\
}

#else

#define IVF_AFX_CONVERSION_METHOD(AppViewClassName,AppDocClassName) \
static CIvfComponent *IvfCvtAfxView(CView *pAfxView) \
{ \
  AppViewClassName *pView = (AppViewClassName *) pAfxView ; \
  return pView ; \
} \
static CView *IvfCvtIvfComponent(CIvfComponent *pIvfComponent) \
{ \
  AppViewClassName *pView = (AppViewClassName *) pIvfComponent ; \
  return pView ; \
} \
static CIvfDocument *IvfCvtAfxDoc(CDocument *pAfxDoc) \
{ \
  AppDocClassName *pDoc = (AppDocClassName *) pAfxDoc ; \
  return pDoc ; \
} \
static CDocument *IvfCvtIvfDoc(CIvfDocument *pIvfDoc) \
{ \
  AppDocClassName *pDoc = (AppDocClassName *) pIvfDoc ; \
  return pDoc ; \
}\
static CIvfMainFrame *IvfCvtAfxFrame(CFrameWnd *pFrame)\
{\
  if (pFrame->IsKindOf( RUNTIME_CLASS(CInPlaceFrame) ) )\
  {\
        CInPlaceFrame *pMainFrame = (CInPlaceFrame *)pFrame;\
        CIvfMainFrame *pIvfFrame = (CIvfMainFrame *)pMainFrame;\
        return pIvfFrame;\
  }\
  else if (pFrame->IsKindOf( RUNTIME_CLASS(CMainFrame) ) )\
  {\
        CMainFrame *pMainFrame = (CMainFrame *)pFrame;\
        CIvfMainFrame *pIvfFrame = (CIvfMainFrame *)pMainFrame;\
        return pIvfFrame;\
  }\
  else\
        return NULL;\
}

#endif


/**
 *  This macro is used to define the type safe conversion methods
 *  for dialog-based applications.
 */
#define IVF_AFX_WND_CONVERSION_METHOD(AppWndClassName) \
static CIvfComponent *IvfCvtAfxWnd(CWnd *pAfxWnd) \
{ \
  AppWndClassName *pWnd = (AppWndClassName *) pAfxWnd ; \
  return pWnd ; \
} \
static CWnd *IvfCvtIvfComponent(CIvfComponent *pIvfComponent) \
{ \
  AppWndClassName *pWnd = (AppWndClassName *) pIvfComponent ; \
  return pWnd ; \
}

extern UINT WMAPPU_PROCPENDINGINLINE;

/////////////////////////////////////////////////////////////////////////////
#endif

