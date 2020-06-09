/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_WIN_COLOR_EDITOR_
#define  _SO_WIN_COLOR_EDITOR_

#include <Inventor/sys/port.h>
#ifdef _WIN32
#  include <Inventor/Win/SoWinBeginStrict.h>
#else
#  include <Xm/Xm.h>
#endif
#include <Inventor/SbColor.h>
#include <Inventor/misc/SoCallbackList.h>
#include <Inventor/Win/SoWinComponent.h>


class SoBase;
class SoNodeSensor;
class SoMFColor;
class SoPathList;
class SoSFColor;
class SoSensor;
class SoWinClipboard;
class SoWinColorPatch;
class SoWinColorWheel;
class SoWinColorSlider;

#if !defined(__sgi)
class SoMFUInt32;      //Allow attaching to "orderedRGBA" field
#endif

struct ColorEditorCBData;

// callback function prototypes
/**
 * [OIV-WRAPPER NAME{EditorCB}]
 * [OIV-WRAPPER-ARG IN,IN]
 */
typedef void SoWinColorEditorCB(void *userData, const SbColor *color);

#ifdef _WIN32
class CBitButton ;
#endif
                                           
//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWinColorEditor
//
//      SoWinColorEditor class which lets you interactively edit a color.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Component that lets you edit a color interactively.
 * 
 * @ingroup Win
 * 
 * @DESCRIPTION
 *   The SoWinColorEditor class lets you interactively edit colors using color
 *   sliders and a color wheel. You can either use it directly to edit a color field
 *   in the database by using the attach()/detach() routines, or use it
 *   by registering a \oivnetdoc delegate \else callback \endoivnetdoc routine which will get called whenever the color
 *   changes (passing an SbColor to that routine). 
 *   
 *   The editor can currently be attached to only one color at a time. Attaching two
 *   different colors will automatically detach the first one before attaching the
 *   second.
 * 
 * @SEE_ALSO
 *    SoWinComponent
 * 
 * 
 */ 

class INVENTORW_API SoWinColorEditor : public SoWinComponent {
    
 public:
    /** 
     * list of possible slider combinations, which is used to specify
     * which sliders should be displayed at any time.
     */
  enum Sliders {
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
    RGB_HSV, 
  };
    
    /**
     * UpdateFrequency is how often new values should be sent
     * to the node or the callback routine.
     */
  enum UpdateFrequency {
    /**
     *  Send updates with every mouse motion 
     */
    CONTINUOUS,
    /**
     *  Only send updates after user hits accept button 
     */
    AFTER_ACCEPT,
  };
    
  /**
   * Constructor.
   */
  SoWinColorEditor(
                   SoWidget parent = NULL,
                   const char *name = NULL, 
                   SbBool buildInsideParent = TRUE);
  /**
   * Destructor.
   */
  ~SoWinColorEditor();
    
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
  void                attach(SoSFColor *color, SoBase *node);
  /**
   * Attaches the editor to a color node and edits the specified color. See attach() for
   * details.
   */
  void                attach(SoMFColor *color, int index, SoBase *node);

#if !defined(__sgi)
  /** 
   * Handles attaching to an "orderedRGBA" field (e.g.\ SoVertexProperty)
   */
  void        attach(SoMFUInt32 *color, int index, SoBase *node);
#endif

  /**
   * Detaches the editor from a color node.
   * Detaching from the color node decrements the reference count of the color
   * node.
   */
  void                detach();
  /**
   * Returns TRUE if the editor is attached.
   */
  SbBool              isAttached()            { return attached; }
    
  /**
   * Additional way of using the color editor, by registering a callback which will
   * be called whenever the color changes (check the @B UpdateFrequency @b to find
   * when the callbacks will be called).
   * [OIV-WRAPPER EVENT_NAME{ColorChanged}]
   */
  inline void         addColorChangedCallback(
                                              SoWinColorEditorCB *f, 
                                              void *userData = NULL);
  /**
   * Removes @B colorChanged@b callback.
   * [OIV-WRAPPER EVENT_NAME{ColorChanged}]
   */
  inline void         removeColorChangedCallback(
                                                 SoWinColorEditorCB *f, 
                                                 void *userData = NULL);

  /**
   * Sets a new color value. NOTE: setColor()
   * will call @B colorChanged @b callbacks if the color differs.
   */
  void                setColor(const SbColor &color);
  /**
   * Gets the current color value. 
   */
  const SbColor &     getColor()      { return baseRGB; }
    
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
  void                setWYSIWYG(SbBool trueOrFalse);
  /**
   * Gets the WYSIWYG mode. 
   */
  SbBool              isWYSIWYG()             { return WYSIWYGmode; }
    
  /**
   * Sets which slider(s) should be displayed.
   */
  void        setCurrentSliders(SoWinColorEditor::Sliders whichSliders);
  /**
   * Gets which slider(s) should be displayed.
   */
  SoWinColorEditor::Sliders getCurrentSliders()       { return whichSliders; }
    
  /**
   * Sets the update frequency. See the @B UpdateFrequency @b enum declaration.
   */
  void        setUpdateFrequency(SoWinColorEditor::UpdateFrequency freq);
  /**
   * Gets the update frequency.
   */
  SoWinColorEditor::UpdateFrequency getUpdateFrequency()
    { return updateFreq; }


  SbBool alwaysOnTop;
 protected:


  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoWinColorEditor::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER
    SoWinColorEditor(
                     SoWidget parent,
                     const char *name, 
                     SbBool buildInsideParent, 
                     SbBool buildNow);
    
  // redefine these
  virtual SbString    getDefaultWidgetName() const;
  virtual SbString    getDefaultTitle() const;
  virtual SbString    getDefaultIconTitle() const;
    
 private:

#ifdef _WIN32
  POINT sliderPos[6] ;
  POINT sliderLabPos[6] ;
  POINT sliderValPos[6] ;
  RECT areaPos[6] ;
  RECT rcDlg ;

  unsigned long sliderId[6] ;
  unsigned long sliderLabId[6] ;
  unsigned long sliderValId[6] ;
  unsigned long areaId[6] ;
  unsigned long nCurrSliderId ;
  unsigned long nCurrEditId ;

  HMENU menubar ;
  HGLOBAL hDlgTemplate;

  CBitButton *lpleftButton ;
  CBitButton *lprightButton ;
  CBitButton *lpswitchButton ;

  void finishBuild() ;
  void getControlPositions() ;
  void hideAllSliders() ;
  void showAllSliders() ;
  void moveSlider(int nSlider,int nPos) ;
  void showSlider(int nSlider) ;
  void hideSlider(int nSlider) ;
  void showControl(int nId) ;
  void hideControl(int nId) ;
  void sizeToArea(int n) ;
  void layoutAccept(WBOOL nReduceOk) ;
  void showArea0() ;
  void showArea1() ;
  void showArea2() ;
  void showArea3() ;
  void showArea4() ;
  void showArea5() ;

  static WBOOL CALLBACK mgrDlgProc( Hwnd hdlg, UINT message,
                                    WPARAM wParam, LPARAM lParam );
  static void onCommand(
                        Hwnd hdlg,
                        int id,
                        Hwnd hCtrl,
                        UINT codeNotify ) ;

  void handleEdit(
                  int nSlider,
                  Hwnd hEdit,
                  UINT codeNotify) ;

  WBOOL handleDrawItem(
                       WPARAM wParam,
                       LPARAM lParam ) ;


#endif
            
  // redefine these to do colorEditor specific things
  SoWidget              buildWidget(SoWidget parent);
  static void visibilityChangeCB(void *pt, SbBool visible);
    
  // local variables
  SoWidget              mgrWidget;      // form manages all child widgets
  SbBool              WYSIWYGmode;
  Sliders             whichSliders;
  SbColor             baseRGB;
  float               baseHSV[3];
  SbBool              ignoreCallback;
  SoWinColorSlider    *sliders[6];
  SoWinColorWheel     *wheel;
  SoWinColorPatch     *current, *previous;
  ColorEditorCBData *dataId;
  SbPList             menuItems;      // Widgets
  SoWinColorEditor::UpdateFrequency   updateFreq;
    
  // attach/detach variables
  SbBool              attached;
  SoBase              *editNode;
  SoSFColor           *colorSF;
  SoMFColor           *colorMF;
  SoNodeSensor        *colorSensor;
  SoCallbackList      *callbackList;
  int                 index;

#if !defined(__sgi)
  // additional attach variables for handling "orderedRGBA" fields
  SoMFUInt32      *colorUInt32MF;
  float            transparency;
#endif
    
  // copy/paste support
  SoWinClipboard      *clipboard;
  void                copy(Time eventTime);
  void                paste(Time eventTime);

  void                pasteDone(SoPathList *pathList);
  static void         pasteDoneCB(void *userData, SoPathList *pathList);
    
  // list of widgets which need to be accessed
  SoWidget      acceptButton, slidersForm, buttonsForm, wheelForm;
    
  // build/destroy routines
  SoWidget              buildPulldownMenu(SoWidget parent);
  SoWidget              buildControls(SoWidget parent);
  SoWidget              buildSlidersForm(SoWidget parent);
    
  void                doSliderLayout();
  void                doDynamicTopLevelLayout();
  int                 numberOfSliders(SoWinColorEditor::Sliders slider);

    
  // do the updates - if attached, update the node; if callback, call it.
  void        doUpdates();
    
  // color field sensor callback and routine
  void        fieldChanged();
  static void fieldChangedCB(void *, SoSensor *);
    
  // callbacks and actual routine from sliders, wheel, buttons, menu...
  static void wheelCallback(void *, const float hsv[3]);
  void        wheelChanged(const float hsv[3]);
  static void sliderCallback(void *, float);
  void        sliderChanged(short id, float value);

#ifdef _WIN32
  void buttonsCallback(int id);
#else
  static void buttonsCallback(SoWidget, ColorEditorCBData *, XtPointer);
#endif
  void        buttonPressed(short id);

#ifdef _WIN32
  void editMenuCallback(int id);
  void sliderMenuCallback(int id);
#else
  static void editMenuCallback(SoWidget, ColorEditorCBData *, XmAnyCallbackStruct *);
  static void sliderMenuCallback(SoWidget, ColorEditorCBData *, XtPointer);
#endif

  static void menuDisplay(SoWidget, SoWinColorEditor *editor, XtPointer);

  // this is called by both constructors
  void constructorCommon(SbBool buildNow);

};

// Inline functions
void
SoWinColorEditor::addColorChangedCallback(
                                          SoWinColorEditorCB *f, 
                                          void *userData)
{ callbackList->addCallback((SoCallbackListCB *) f, userData); }

void
SoWinColorEditor::removeColorChangedCallback(
                                             SoWinColorEditorCB *f, 
                                             void *userData)
{ callbackList->removeCallback((SoCallbackListCB *) f, userData); }


#ifdef _WIN32
#include <Inventor/Win/SoWinEndStrict.h>
#endif
#endif  /* _SO_WIN_COLOR_EDITOR_ */

