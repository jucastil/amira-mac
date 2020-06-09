/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _SOWIN_STEREO_DIALOG_
#define _SOWIN_STEREO_DIALOG_

#ifdef SOQT
#include <Inventor/components/stereo/SoQtStereoDialog.h>
#else // SOQT

#include <Inventor/sys/port.h>
#ifdef _WIN32
#  include <Inventor/Win/SoWinBeginStrict.h>
#else
#  include <Xm/Xm.h>
#  include <Inventor/Xt/SoXtMaterialEditor.h>
#endif

#include <Inventor/components/stereo/SoWinXt2Stereo.h>
#include <Inventor/Xt/SoXtComponent.h>

class SoStereoViewer;
class SoBaseStereo;
class SoWinSlider;

/**
 * @VSGEXT Component that lets you modify stereo attributes interactively.
 * 
 * @ingroup Stereo
 * 
 * @DESCRIPTION
 *   This component displays a dialog box for modifying stereo attributes
 *   interactively.
 * 
 * @SEE_ALSO
 *    SoStereoViewer,
 *    SoBaseStereo,
 *    SoWinViewer
 *    SoXtViewer
 * 
 * [OIVJAVA-WRAPPER-CLASS NO_WRAP]
 * 
 */ 

class INVENTORW_API SoStereoDialog : public SoXtComponent {
 public:
  
  /**
   * Constructor.
   */
  SoStereoDialog(SoWidget parent = NULL,  SoStereoViewer * viewer = NULL,
                 const char *name = NULL, SbBool buildInsideParent = TRUE);
  /**
   * Destructor.
   */
  ~SoStereoDialog();
  
  /**
   * Notify the stereo dialog that the viewer state may have changed.
   */
  virtual void update();

 protected:


  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoStereoDialog::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER SoStereoDialog(SoWidget parent,    SoStereoViewer * viewer,
                            const char *name, SbBool buildInsideParent, SbBool buildNow);
    
  // redefine these
  virtual SbString    getDefaultWidgetName() const;
  virtual SbString    getDefaultTitle() const;
  virtual SbString    getDefaultIconTitle() const;
    
  // NEW STEREO
  // Added by Squale on 11 sep 2000
 private:
  static void onParallaxToggleCB(SoWidget widget, XtPointer clientData, void *state );
  static void onCameraToggleCB(SoWidget widget, XtPointer clientData, void *state );
  static void onButtonCB( SoWidget widget, XtPointer clientData, void* cbs );
  static void onStereoToggleCB(SoWidget widget, XtPointer clientData, void *state );
  static void scaleParallaxCB( SoWidget w, XtPointer clientData, void* callData );
  static void scaleCameraCB( SoWidget w, XtPointer clientData, void* callData );

#ifndef _WIN32
  virtual void widgetDestroyed();
#endif

  SoWidget m_stereoItem[12], m_rawStereoItem;
  SoWidget m_stereoPopup;
  SoWidget m_stereoToggle;
  SoWidget m_adjustStereoToggle;
  SoWidget m_scaleParallax;
  SoWidget m_scaleCamOffset;
  SoWidget m_cameraToggle;
  SoWidget m_parallaxToggle;
  SoBaseStereo* m_viewType;
  
  SbBool   m_destroyFlag;
  SbBool   m_cameraFlag, m_parallaxFlag;

#ifdef _WIN32
  static WBOOL CALLBACK mgrDlgProc(Hwnd hdlg, UINT message, WPARAM wParam, LPARAM lParam);
  static void onCommand(Hwnd hdlg, int id, Hwnd hCtrl, UINT codeNotify ) ;
#endif

  static void sliderCallback(void * userData, float value) ;

  static SoBaseStereo * getStereoViewType(int stereoTypeListIndex=0) ;

  // widgets to edit the material
  SoWidget                      mgrWidget;      // topmost widget

  // local scene vars
  SoStereoViewer      *stereoViewer;
  SoWinSlider * sliders[2];
    
  // Callback routines from Xt/Motif
#ifndef _WIN32
  static void         menuPick(SoWidget, int, XmAnyCallbackStruct *);
  static void         menuDisplay(SoWidget, SoXtMaterialEditor *, XtPointer);
  static void         radioButtonPick(SoWidget, int, XtPointer);
  static void         diamondButtonPick(SoWidget, int, XtPointer);
#endif

  // Build routines
  SoWidget              buildWidget(SoWidget parent);
  SoWidget              buildControls(SoWidget parent);
  SoWidget              buildSliders(SoWidget parent);
    

  // this is called by both constructors
  void constructorCommon(SoStereoViewer * viewer, SbBool buildNow);
	int m_lastStereoMode;
	bool m_isStereoActive;
  bool m_lastStereoReversed;
};
#ifdef _WIN32
#include <Inventor/Win/SoWinEndStrict.h>
#endif

#endif // SOQT

#endif // _SOWIN_STEREO_DIALOG_

