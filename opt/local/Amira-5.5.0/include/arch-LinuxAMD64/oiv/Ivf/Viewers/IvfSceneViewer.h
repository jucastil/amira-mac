/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef __IVFSCENEVWR_H__
#define __IVFSCENEVWR_H__

#include <Ivf/IvfComponent.h>

class SbColor;
class SoSceneViewer ;
class SoType;

/**
 * Ivf wrapper for an SoSceneViewer.
 * 
 * @ingroup Ivf_Classes
 * 
 * @DESCRIPTION
 *   Note: Although the class name is CIvfSceneViewer, the header file name is
 *   IvfSceneViewer.h.
 * 
 * @SEE_ALSO
 *    SceneViewer
 * 
 * 
 */ 

class IVF_API CIvfSceneViewer : public CIvfComponent
{
 public:
  CIvfSceneViewer() ;

  /**
   * This macro declares the minimum number of methods necessary
   * to create a class derived from CIvfComponent
   */
  IVF_COMPONENT_BASE();

  virtual void                  IvfRemoveManips();
  virtual void                  IvfRestoreManips();


  /** Scene viewer type */
  enum IvfSvEViewerType
  {
    /** No viewer */
    SV_VWR_NONE = -1,
    /** Examiner viewer */
    SV_VWR_EXAMINER , 
    /** Fly viewer */
    SV_VWR_FLY, 
    /** Walk viewer */
    SV_VWR_WALK, 
    /** Plane viewer */
    SV_VWR_PLANE, 
  };
  //  we added SV_VWR_NONE

  /** Scene viewer manipulators */
  enum IvfSvEManipMode {
    SV_NONE,                         /** None */
    SV_TRANSFORMER,                  /** Transformer manip */
    SV_TRACKBALL,                    /** Trackball manip */
    SV_HANDLEBOX,                    /** Handlebox manip */
    SV_JACK,                         /** Jack manip */
    SV_CENTERBALL,                   /** Centerball manip */
    SV_XFBOX,                        /** TransformBox manip */
    SV_TABBOX                        /** TabBox manip */
  };
  // these are copied directly from
  // SoSceneViewer --  keep current

  IvfSvEManipMode IvfGetCurrManipMode();
  IvfSvEViewerType IvfGetCurrViewerType();

 protected: //PROTECTED_TO_DOCUMENT
  virtual                                       ~CIvfSceneViewer() ;

  virtual BOOL  IvfGetLightName(LPTSTR buf, int buflen,
                                SoType lightType, BOOL &modified);

  virtual void                  IvfPrePasteAction();
  virtual void                  IvfPostPasteAction();
  virtual void                  IvfPreCopyAction();
  virtual void                  IvfPostCopyAction();
  virtual void                  IvfPreCutAction();
  virtual void                  IvfOnPaint();
  virtual void                  IvfOnPaint(CWnd *pWnd);
  virtual BOOL                  IvfOnUpdateFrameTitle(CString &strTitle) ;
  virtual void                  IvfOnInitialUpdate(CWnd *pWnd);
  virtual void                  IvfOnDeactivateComponent();
  virtual void                  IvfOnActivateComponent(CView *pView = NULL);
  virtual BOOL                  IvfPreTranslateMessage(MSG *pMsg);
  virtual BOOL                  IvfOnCommand(WPARAM wParam, LPARAM lParam);
  virtual void                  IvfOnDestroy();

  /**
   * CIvfSceneViewer specific utility methods
   */
  BOOL                                  IvfUpdateWindowText();
  void                                  IvfFindTopWindow() ;
  void                                  IvfDrawTopMenuBar() ;

  /**
   * This method queries if the underlying viewer iss a
   * SceneViewer or not.
   */
  virtual BOOL IvfIsSceneViewer();

        

  /**
   * pointer to the SoSceneViewer object we create
   */
  SoSceneViewer *                       m_pSV;

  /**
   * CIvfSceneViewer specific member variables
   */
  CString                               m_strTitle ;
  CWnd *                                m_pTopWnd ;
  int                     m_nFirstLightMenuId;


  /**
   *  this is added to the background color editor to tell us
   *  when the background color has changed.
   *  rickb
   */
  static void IvfBgColorChangedCB(void *userData, const SbColor *c);

 public:
  /**
   * CIvfSceneViewer specific menu command handlers
   */
  void IvfOnFileInfo();
  void IvfOnUpdateFileInfo(CCmdUI* pCmdUI);
  void IvfOnFileImport();
  void IvfOnUpdateFileImport(CCmdUI* pCmdUI);
  void IvfOnViewScreendoortransparency();
  void IvfOnUpdateViewScreendoortransparency(CCmdUI* pCmdUI);
  void IvfOnViewBlendedtransparency();
  void IvfOnUpdateViewBlendedtransparency(CCmdUI* pCmdUI);
  void IvfOnViewDelayedblendedtransparency();
  void IvfOnUpdateViewDelayedblendedtransparency(CCmdUI* pCmdUI);
  void IvfOnViewSortedblendedtransparency();
  void IvfOnUpdateViewSortedblendedtransparency(CCmdUI* pCmdUI);
  void IvfOnViewSortedLayersblendedtransparency();
  void IvfOnUpdateViewSortedLayersblendedtransparency(CCmdUI* pCmdUI);
  void IvfOnViewSortedTrianglesblendedtransparency();
  void IvfOnUpdateViewSortedTrianglesblendedtransparency(CCmdUI* pCmdUI);
  void IvfOnViewSortedObjectTrianglesblendedtransparency();
  void IvfOnUpdateViewSortedObjectTrianglesblendedtransparency(CCmdUI* pCmdUI);
  void IvfOnViewViewselection();
  void IvfOnUpdateViewViewselection(CCmdUI* pCmdUI);
  void IvfOnViewFog();
  void IvfOnUpdateViewFog(CCmdUI* pCmdUI);
  void IvfOnViewAntialiasing();
  void IvfOnUpdateViewAntialiasing(CCmdUI* pCmdUI);
  void IvfOnViewEditbackgroundcolor();
  void IvfOnUpdateViewEditbackgroundcolor(CCmdUI* pCmdUI);
  void IvfOnUpdateViewExaminer(CCmdUI* pCmdUI);
  void IvfOnViewExaminer();
  void IvfOnViewFly();
  void IvfOnUpdateViewFly(CCmdUI* pCmdUI);
  void IvfOnViewPlane();
  void IvfOnUpdateViewPlane(CCmdUI* pCmdUI);
  void IvfOnViewWalk();
  void IvfOnUpdateViewWalk(CCmdUI* pCmdUI);
  void IvfOnViewPicedit();
  void IvfOnUpdateViewPicedit(CCmdUI* pCmdUI);
  void IvfOnSelectionShiftselection();
  void IvfOnUpdateSelectionShiftselection(CCmdUI* pCmdUI);
  void IvfOnSelectionSingleselection();
  void IvfOnUpdateSelectionSingleselection(CCmdUI* pCmdUI);
  void IvfOnSelectionToggleselection();
  void IvfOnUpdateSelectionToggleselection(CCmdUI* pCmdUI);
  void IvfOnEditorsColoreditor();
  void IvfOnUpdateEditorsColoreditor(CCmdUI* pCmdUI);
  void IvfOnEditorsMaterialeditor();
  void IvfOnUpdateEditorsMaterialeditor(CCmdUI* pCmdUI);
  void IvfOnEditorsTransformsliders();
  void IvfOnUpdateEditorsTransformsliders(CCmdUI* pCmdUI);
  void IvfOnManipsCenterball();
  void IvfOnUpdateManipsCenterball(CCmdUI* pCmdUI);
  void IvfOnManipsHandlebox();
  void IvfOnUpdateManipsHandlebox(CCmdUI* pCmdUI);
  void IvfOnManipsJack();
  void IvfOnUpdateManipsJack(CCmdUI* pCmdUI);
  void IvfOnManipsNone();
  void IvfOnUpdateManipsNone(CCmdUI* pCmdUI);
  void IvfOnManipsReplace();
  void IvfOnUpdateManipsReplace(CCmdUI* pCmdUI);
  void IvfOnManipsTabbox();
  void IvfOnUpdateManipsTabbox(CCmdUI* pCmdUI);
  void IvfOnManipsTransformer();
  void IvfOnUpdateManipsTransformer(CCmdUI* pCmdUI);
  void IvfOnManipsTrackball();
  void IvfOnUpdateManipsTrackball(CCmdUI* pCmdUI);
  void IvfOnManipsTransformbox();
  void IvfOnUpdateManipsTransformbox(CCmdUI* pCmdUI);
  void IvfOnLightsCreatedirlight();
  void IvfOnUpdateLightsCreatedirlight(CCmdUI* pCmdUI);
  void IvfOnLightsCreatepointlight();
  void IvfOnUpdateLightsCreatepointlight(CCmdUI* pCmdUI);
  void IvfOnLightsCreatespotlight();
  void IvfOnUpdateLightsCreatespotlight(CCmdUI* pCmdUI);
  void IvfOnUpdateLightsHideallicons(CCmdUI* pCmdUI);
  void IvfOnLightsHideallicons();
  void IvfOnLightsAmbientlighting();
  void IvfOnUpdateLightsAmbientlighting(CCmdUI* pCmdUI);
  void IvfOnLightsShowallicons();
  void IvfOnUpdateLightsShowallicons(CCmdUI* pCmdUI);
  void IvfOnLightsTurnalloff();
  void IvfOnUpdateLightsTurnalloff(CCmdUI* pCmdUI);
  void IvfOnLightsTurnallon();
  void IvfOnUpdateLightsTurnallon(CCmdUI* pCmdUI);
  void IvfOnUpdateFilePrint(CCmdUI* pCmdUI);
  void IvfOnUpdateFilePrintPreview(CCmdUI* pCmdUI);
  void IvfOnUpdateFilePrintSetup(CCmdUI* pCmdUI);
         
} ;


#endif

