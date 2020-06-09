/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Alain Dumesny (MMM yyyy)
**=======================================================================*/

#ifndef  _SO_QT_COLOR_EDITOR_
#define  _SO_QT_COLOR_EDITOR_
#include <Inventor/Qt/OivQtCompat.h>
#include <Inventor/SbColor.h>
#include <Inventor/misc/SoCallbackList.h>
#include <Inventor/Qt/SoQtComponent.h>

#include <QtCore/qglobal.h>
#include <QtCore/QPointer>

class SoBase;
class SoNodeSensor;
class SoMFColor;
class SoPathList;
class SoSFColor;
class SoSensor;
class SoQtColorPatch;
class SoQtColorWheel;
class SoQtColorSlider;
class QMenuBar;
class QMenu;
class QAction;
class QSlider;

class SoMFUInt32;

struct ColorEditorCBData;

/** 
 *  External change callback functions registered with the color editor should be of this type.
 */
typedef void SoQtColorEditorCB( void* userData, const SbColor* color );


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoQtColorEditor
//
//      SoQtColorEditor class which lets you interactively edit a color.
//
//////////////////////////////////////////////////////////////////////////////

/**
* @VSGEXT Component that lets you edit a color interactively.
* 
* @ingroup Qt
* 
* @DESCRIPTION
*   The SoQtColorEditor class lets you interactively edit colors using color
*   sliders and a color wheel. You can either use it directly to edit a color field
*   in the database by using the attach()/detach() routines, or use it
*   by registering a callback routine which will get called whenever the color
*   changes (passing an SbColor to that routine). 
*   
*   The editor can currently be attached to only one color at a time. Attaching two
*   different colors will automatically detach the first one before attaching the
*   second.
* 
* @SEE_ALSO
*    SoQtComponent
* 
* 
*/ 

class INVENTORQT_API SoQtColorEditor : public SoQtComponent {
 
  Q_OBJECT

public:
  
  /** Sliders.
   * List of possible slider combinations, which is used to specify
   * which sliders should be displayed at any time.
   */
  enum Sliders 
  {
    /**
     *  Display no sliders 
     */
    NONE, 
    /**
     *  Display intensity slider (default) 
     */
    INTENSITY,
    /**
     *  Display RGB sliders 
     */
    RGB, 
    /**
     *  Display HSV sliders 
     */
    HSV, 
    /**
     *  Display RGB and value sliders 
     */
    RGB_V, 
    /**
     *  Display RGB and HSV sliders 
     */
    RGB_HSV 
  };
  
  /** Update frequency.
   * UpdateFrequency is how often new values should be sent
   * to the node or the callback routine.                                  
   */
  enum UpdateFrequency 
  {
    /**
     *  Send updates with every mouse motion 
     */
    CONTINUOUS,
    /**
     *  Only send updates after user hits accept button 
     */
    AFTER_ACCEPT
  };
  
  /**
   * Constructor.
   */
  SoQtColorEditor( QWidget *parent = qApp->activeWindow(),
                   const char *name = NULL,              // a QDialog even if he has no direct parent
                   SbBool buildInsideParent = TRUE );
  /**
   * Destructor.
   */
  ~SoQtColorEditor();
  
  /**
   * Attaches the editor to a color node and edits the specified color.
   * Attaching to the color node increments the reference count of the color node.
   * 
   * The color editor uses a sensor on the color field to automatically update itself
   * when the color is changed externally.
   * 
   * NOTE: The node containing the field needs to also be passed to attach the sensor
   * to it (since field sensors are not yet supported). 
   * 
   * NOTE: The color editor can only be attached to either a single field or a
   * multiple field at any given time. Even when attached to a multiple field, only a
   * single color from that field is edited, as specified by @B index@b.
   */
  void          attach(SoSFColor *color, SoBase *node);
  /**
   * Attaches the editor to a color node and edits the specified color. See attach() for
   * details.
   */
  void  attach(SoMFColor *color, int index, SoBase *node);
  
  /** 
   * Attaches the editor to a color node and edits the color of the given index.
   * See attach() for details.
   */
  void  attach(SoMFUInt32 *color, int index, SoBase *node);
  
  /**
   * Detaches the editor from a color node.
   * Detaching from the color node decrements the reference count of the color
   * node.
   */
  void          detach();
  /**
   * Returns TRUE if the editor is attached.
   */
  SbBool                isAttached()            { return attached; }
  
  /**
   * Additional way of using the color editor, by registering a callback which will
   * be called whenever the color changes (check the @B UpdateFrequency @b to find
   * when the callbacks will be called).
   */
  inline void           addColorChangedCallback( SoQtColorEditorCB *f, 
                                                 void *userData = NULL );
  /**
   * Removes @B colorChanged@b callback.
   */
  inline void           removeColorChangedCallback( SoQtColorEditorCB *f, 
                                                    void *userData = NULL );
  
  /**
   * Sets a new color value. NOTE: setColor()
   * will call @B colorChanged @b callbacks if the color differs.
   */
  void          setColor(const SbColor &color);
  /**
   * Gets the current color value. 
   */
  const SbColor &       getColor()      { return baseRGB; }
  
  /**
   * Sets the WYSIWYG (what-you-see-is-what-you-get) mode on/off for the
   * colored backgrounds of the sliders.
   *
   * In WYSIWYG mode, the color shown on the slider background beneath the
   * slider pointer is what you get. For example, if R,G,B sliders in
   * WYSIWYG mode are set to (0,1,1), the color beneath each slider pointer 
   * will be cyan because (0,1,1) corresponds to cyan. 
   *
   * In non-WYSIWYG mode, the color shown on the slider background
   * reflects only the value of the parameter that the slider controls.
   * For example, the background of the red slider will display only red values,
   * the green slider will display only green values, and so forth.
   */
  void          setWYSIWYG(SbBool trueOrFalse);
  /**
   * Gets the WYSIWYG mode. 
   */
  SbBool                isWYSIWYG()             { return WYSIWYGmode; }
  
  /**
   * Sets which slider(s) should be displayed.
   */
  void          setCurrentSliders(SoQtColorEditor::Sliders whichSliders);
  /**
   * Gets which slider(s) should be displayed.
   */
  SoQtColorEditor::Sliders getCurrentSliders()  { return whichSliders; }
  
  /**
   * Sets the update frequency. See the @B UpdateFrequency @b enum declaration.
   */
  void  setUpdateFrequency(SoQtColorEditor::UpdateFrequency freq);
  /**
   * Gets the update frequency.
   */
  SoQtColorEditor::UpdateFrequency getUpdateFrequency()
  { return updateFreq; }
  
  /** 
   * Make the color editor visible
   */
  virtual void          show();

  /** 
   * Hide the color editor.
   */
  virtual void          hide();
  
  /** 
   * Boolean indicating if the editor should be always on top of the other windows.
   */
  SbBool alwaysOnTop;

protected:
      
  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoQtColorEditor::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER
  SoQtColorEditor(
                  QWidget *parent,
                  const char *name, 
                  SbBool buildInsideParent, 
                  SbBool buildNow);
    
  // redefine these
  virtual SbString    getDefaultWidgetName() const;
  virtual SbString    getDefaultTitle() const;
  virtual SbString    getDefaultIconTitle() const;
    
private:

  QMenuBar* menubar ;
    
  int nCurrSliderId;
  QPointer<QMenu> menu_sliders, edit;
  QPointer<SoQtButton> lpleftButton ;
  QPointer<SoQtButton> lprightButton ;
  QPointer<SoQtButton> lpswitchButton ;

  QAction* edAcCon, *edAcMan, *edAcWy;
  QAction* msAcNone, *msAcInt, *msAcRGB, *msAcHSV, *msAcRGB_V, *msAcRGB_HSV;
    
  // redefine these to do colorEditor specific things
  QWidget*            buildWidget(QWidget *parent);
    
  // local variables
  QPointer<QWidget>                   mgrWidget;
  SbBool                    WYSIWYGmode;
  Sliders           whichSliders;
  SbColor                   baseRGB;
  float                       baseHSV[3];
  SbBool              ignoreCallback;
  SoQtColorSlider     *sliders[6];
  SoQtColorWheel      *wheel;
  SoQtColorPatch      *current, *previous;
  ColorEditorCBData *dataId;
  SbPList             menuItems;      // Widgets
  SoQtColorEditor::UpdateFrequency    updateFreq;
    
  // attach/detach variables
  SbBool              attached;
  SoBase              *editNode;
  SoSFColor           *colorSF;
  SoMFColor           *colorMF;
  SoNodeSensor        *colorSensor;
  SoCallbackList      *callbackList;
  int                 index;
    
  // additional attach variables for handling "orderedRGBA" fields
  SoMFUInt32      *colorUInt32MF;
  float            transparency;
        
  // list of widgets which need to be accessed
  QPointer<SoQtButton> acceptButton;
  QWidget    *wheelForm;
    
  // build/destroy routines
  QMenuBar*             buildPulldownMenu(QWidget *parent);
  void            buildControls(QWidget *parent);
  void                buildSlidersForm(QWidget *parent);
    
  void                doSliderLayout();
  void                doDynamicTopLevelLayout();
  int                 numberOfSliders(SoQtColorEditor::Sliders slider);
    
    
  // do the updates - if attached, update the node; if callback, call it.
  void        doUpdates();
    
  // color field sensor callback and routine
  void        fieldChanged();
  static void fieldChangedCB(void *, SoSensor *);

    
  // callbacks and actual routine from sliders, wheel, buttons, menu...
  static void wheelCallback(void *, const float hsv[3]);
  static void wheelCloseCB(void *userData, SoQtComponent *);

  void        wheelChanged(const float hsv[3]);
  
  static void sliderCallback(void *, float);
  void        sliderChanged(short id, float value);

  void        buttonPressed(short id);
  
  void sliderMenuCallback(int id);
  void editMenuCallback(int id);
    
  // this is called by both constructors
  void constructorCommon(SbBool buildNow);

private Q_SLOTS:

void slot_none();
  void slot_intensity();
  void slot_rgb();
  void slot_hsv();
  void slot_rgb_v();
  void slot_rgb_hsv();

  void slot_continuous();
  void slot_manual();
  void slot_wysiwyg();

  void slot_leftButton();
  void slot_rightButton();
  void slot_switchButton();
  void slot_acceptButton();
  void slot_help();

  void visibilityChangeCB(SbBool visible);
    
};

// Inline functions
void
SoQtColorEditor::addColorChangedCallback(SoQtColorEditorCB *f, 
                                         void *userData)
{ callbackList->addCallback((SoCallbackListCB *) f, userData); }

void
SoQtColorEditor::removeColorChangedCallback(SoQtColorEditorCB *f, 
                                            void *userData)
{ callbackList->removeCallback((SoCallbackListCB *) f, userData); }


#endif  /* _SO_QT_COLOR_EDITOR_ */

