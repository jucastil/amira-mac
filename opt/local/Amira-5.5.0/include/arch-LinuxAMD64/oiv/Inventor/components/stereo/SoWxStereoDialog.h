/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.MEHAMLI (Jul 2007)
**=======================================================================*/

#ifndef SO_WX_STEREO_DIALOG
#define SO_WX_STEREO_DIALOG

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWxStereoDialog
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/Wx/SoWxComponent.h>

#include <wx/combobox.h>
#include <wx/checkbox.h>
#include <wx/event.h>

#include <Inventor/components/stereo/SoWinXt2Stereo.h>

class SoStereoViewer;
class SoBaseStereo;

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
*    SoWxViewer
* 
* [OIV-WRAPPER-NO-WRAP] 
*/ 

class INVENTORWX_API SoStereoDialog : public SoWxComponent 
{
  public:
  
  /**
   * Constructor.
   */
  SoStereoDialog( wxWindow* parent = wxTheApp->GetTopWindow(), SoStereoViewer* viewer = NULL,
                  const char* name = NULL, SbBool buildInsideParent = TRUE );
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
  SoEXTENDER SoStereoDialog( wxWindow* parent, SoStereoViewer* viewer,
                             const char* name, SbBool buildInsideParent, SbBool buildNow);

  // redefine these
  virtual SbString getDefaultWidgetName() const;
  virtual SbString getDefaultTitle() const;
  virtual SbString getDefaultIconTitle() const;
        
  void sliderCallback( wxCommandEvent& ce ) ;

  static SoBaseStereo* getStereoViewType( int stereoTypeListIndex = 0 ) ;
  
  // widgets to edit the material
  wxWindow* mgrWidget;     // topmost widget
  
  // local scene vars
  SoStereoViewer* stereoViewer;
  wxSlider* sliders[2];
  bool interactiveSlider1, interactiveSlider2;
  
  // Build routines
  wxWindow* buildWidget( wxWindow* parent );
  wxWindow* buildControls( wxWindow* parent );
  
  // this is called by both constructors
  void constructorCommon( SoStereoViewer* viewer, SbBool buildNow );

  wxComboBox* COMBO_STEREO;
  wxCheckBox* CHECK_STEREO;
  wxCheckBox* CHECK_BALANCE;
  wxCheckBox* CHECK_CAMERA;
  wxCheckBox* CHECK_REVERT_STEREO;
  
  void stereo( wxCommandEvent& ce );
  void checkBalance( wxCommandEvent& ce );
  void checkCamera( wxCommandEvent& ce );
  void checkStereo( wxCommandEvent& ce );
  void checkRevertStereo( wxCommandEvent& ce );

  int m_lastStereoMode;
	bool m_isStereoActive;
  bool m_lastStereoReversed;
};

#endif // SO_WX_STEREO_DIALOG
