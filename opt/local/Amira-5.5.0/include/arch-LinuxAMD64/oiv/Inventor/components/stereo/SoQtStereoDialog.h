/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _SOQT_STEREO_DIALOG_
#define _SOQT_STEREO_DIALOG_

#include <Inventor/components/stereo/SoWinXt2Stereo.h>
#include <Inventor/Qt/SoQtComponent.h>

class SoStereoViewer;
class SoBaseStereo;
class SoQtSlider;
class QGridLayout;
class QCheckBox;
class QComboBox;
class QGroupBox;
class QLabel;

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
*    SoQtViewer
* 
* [OIV-WRAPPER-NO-WRAP]
*/ 

class INVENTORQT_API SoStereoDialog : public SoQtComponent {
  
  Q_OBJECT
    
    public:
  
  /**
   * Constructor.
   */
  SoStereoDialog( QWidget *parent = qApp->activeWindow(),  SoStereoViewer * viewer = NULL,
                  const char *name = NULL, SbBool buildInsideParent = TRUE );
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
  SoEXTENDER SoStereoDialog(QWidget *parent,    SoStereoViewer * viewer,
                            const char *name, SbBool buildInsideParent, SbBool buildNow);

  // redefine these
  virtual SbString    getDefaultWidgetName() const;
  virtual SbString    getDefaultTitle() const;
  virtual SbString    getDefaultIconTitle() const;
        
  static void sliderCallback(void * userData, float value) ;

  static SoBaseStereo * getStereoViewType(int stereoTypeListIndex=0) ;
  
  // widgets to edit the material
  QWidget                       *mgrWidget;     // topmost widget
  
  // local scene vars
  SoStereoViewer        *stereoViewer;
  SoQtSlider* sliders[2];
  
  // Build routines
  QWidget* buildWidget(QWidget *parent);
  QWidget* buildControls(QWidget *parent);
  QWidget* buildSliders(QWidget *parent);
  
  
  // this is called by both constructors
  void constructorCommon(SoStereoViewer * viewer, SbBool buildNow);

  virtual bool eventFilter( QObject* object,QEvent *event );

  QComboBox* COMBO_STEREO;
  QCheckBox* CHECK_STEREO;
  QCheckBox* CHECK_BALANCE;
  QCheckBox* CHECK_CAMERA;
  SoQtSlider* SLIDER_BALNCE;
  SoQtSlider* SLIDER_CAMERA;
  QCheckBox* CHECK_REVERT_STEREO;

	int m_lastStereoMode;
	bool m_isStereoActive;
  bool m_lastStereoReversed;
  
  protected Q_SLOTS:
  void slot_stereo(int value);
  void slot_check_balance(bool onOff);
  void slot_check_camera(bool onOff);
  void slot_check_stereo(bool onOff);
  void slot_check_revert_stereo(bool onOff);

};


#endif // _SOQT_STEREO_DIALOG_
