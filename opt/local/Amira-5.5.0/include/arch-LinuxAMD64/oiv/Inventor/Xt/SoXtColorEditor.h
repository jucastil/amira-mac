/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifdef SOQT
#  include <Inventor/Qt/SoQtColorEditor.h>
#elif defined(_WIN32)
#  include <Inventor/Win/SoWinColorEditor.h>
#else // _WIN32

#ifndef  _SO_XT_COLOR_EDITOR_
#define  _SO_XT_COLOR_EDITOR_

#include <Xm/Xm.h>
#include <Inventor/SbColor.h>
#include <Inventor/misc/SoCallbackList.h>
#include <Inventor/Xt/SoXtComponent.h>

class SoBase;
class SoNodeSensor;
class SoMFColor;
class SoPathList;
class SoSFColor;
class SoSensor;
class SoXtClipboard;
class SoXtColorPatch;
class SoXtColorWheel;
class SoXtColorSlider;

class SoMFUInt32;

struct _ColorEditorCBData;

// callback function prototypes
typedef void SoXtColorEditorCB(void *userData, const SbColor *color);
        
//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtColorEditor
//
// SoXtColorEditor class which lets you interactively edit a color.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Component that lets you edit a color interactively.
 * 
 * @ingroup Xt
 * 
 * @DESCRIPTION
 *   The SoXtColorEditor class lets you interactively edit colors using color sliders
 *   and a color wheel. You can either use it directly to edit a color field in the
 *   database by using the attach()/detach() routines, or use it by
 *   registering a callback routine which will get called whenever the color changes
 *   (passing an SbColor to that routine). 
 *   
 *   The editor can currently be attached to only one color at a time. Attaching two
 *   different colors will automatically detach the first one before attaching the
 *   second.
 * 
 * @SEE_ALSO
 *    SoXtComponent
 * 
 * 
 */ 

class INVENTORXT_API SoXtColorEditor : public SoXtComponent {
  
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
    RGB_HSV
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
    AFTER_ACCEPT
  };
  
  /**
   * Constructor.
   */
  SoXtColorEditor(SoWidget parent = NULL,
                  const char *name = NULL, 
                  SbBool buildInsideParent = TRUE);
  /**
   * Destructor.
   */
  ~SoXtColorEditor();
  
  /**
   * Attaches the editor to a color node and edits the specified color.
   * Attaching to the color node increments the reference count of the color node.
   * 
   * The color editor uses a sensor on the color field to automatically update itself
   * when the color is changed externally.
   * 
   * NOTE: The node containing the field needs to also be passed to attach the sensor
   * to it (since field sensors are not yet suported). 
   * 
   * NOTE: The color editor can only be attached to either a single field or a
   * multiple field at any given time. Even when attached to a multiple field, only a
   * single color from that field is edited, as specified by @B index @b.
   */
  void attach(SoSFColor *color, SoBase *node);
  /**
   * Attaches the editor to a color node and edits the color of the given index.
   * See attach() for details.
   */
  void attach(SoMFColor *color, int index, SoBase *node);
  /**
   * Attaches the editor to a color node and edits the color of the given index.
   * See attach() for details.
   */
  void attach(SoMFUInt32 *color, int index, SoBase *node);
  
  /**
   * Detaches the editor from a color node.
   * Detaching from the color node decrements the reference count of the color
   * node.
   */
  void detach();
  /**
   * Returns TRUE if the editor is attached.
   */
  SbBool isAttached() { return attached; }
  
  /**
   * Additional way of using the color editor, by registering a callback which will
   * be called whenever the color changes (check the @B UpdateFrequency @b to find
   * when the callbacks will be called).
   */
  inline void addColorChangedCallback(SoXtColorEditorCB *f, void *userData = NULL);
  /**
   * Removes @B colorChanged@b callback.
   */
  inline void removeColorChangedCallback(SoXtColorEditorCB *f, void *userData = NULL);
  
  /**
   * Sets a new color value. NOTE: setColor()
   * will call @B colorChanged @b callbacks if the color differs.
   */
  void setColor(const SbColor &color);
  /**
   * Gets the current color value.
   */
  const SbColor & getColor() { return baseRGB; }
  
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
   * For example, the colored background of the red slider will display only red values,
   * the green slider will display only green values, and so forth.
   */
  void setWYSIWYG(SbBool trueOrFalse);
  /**
   * Gets the WYSIWYG mode. 
   */
  SbBool isWYSIWYG() { return WYSIWYGmode; }
  
  /**
   * Sets which slider(s) should be displayed.
   */
  void setCurrentSliders(SoXtColorEditor::Sliders whichSliders);
  /**
   * Gets which slider(s) should be displayed.
   */
  SoXtColorEditor::Sliders getCurrentSliders() { return whichSliders; }
  
  /**
   * Sets the update frequency. See the @B UpdateFrequency @b enum declaration.
   */
  void setUpdateFrequency(SoXtColorEditor::UpdateFrequency freq);
  /**
   * Gets the update frequency. 
   */
  SoXtColorEditor::UpdateFrequency getUpdateFrequency() { return updateFreq; }
  
 protected:
  
  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoXtColorEditor::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER
    SoXtColorEditor(SoWidget parent,
                    const char *name, 
                    SbBool buildInsideParent, 
                    SbBool buildNow);
  
  // redefine these
  virtual SbString getDefaultWidgetName() const;
  virtual SbString getDefaultTitle() const;
  virtual SbString getDefaultIconTitle() const;
  
 private:
  
  // redefine these to do colorEditor specific things
  SoWidget buildWidget(SoWidget parent);
  static void visibilityChangeCB(void *pt, SbBool visible);
  
  // local variables
  SoWidget mgrWidget; // form manages all child widgets
  SbBool WYSIWYGmode;
  Sliders whichSliders;
  SbColor baseRGB;
  float baseHSV[3];
  SbBool ignoreCallback;
  SoXtColorSlider *sliders[6];
  SoXtColorWheel *wheel;
  SoXtColorPatch *current, *previous;
  _ColorEditorCBData *dataId;
  SbPList menuItems;   // Widgets
  SoXtColorEditor::UpdateFrequency updateFreq;
  
  // attach/detach variables
  SbBool attached;
  SoBase *editNode;
  SoSFColor *colorSF;
  SoMFColor *colorMF;
  SoNodeSensor *colorSensor;
  SoCallbackList *callbackList;
  int index;
  
  // Extension (mmh)
  // additional attach variables for handling "orderedRGBA" fields
  SoMFUInt32 *colorUInt32MF;
  float transparency;
  
  // copy/paste support
  SoXtClipboard *clipboard;
  void copy(Time eventTime);
  void paste(Time eventTime);
  void pasteDone(SoPathList *pathList);
  static void pasteDoneCB(void *userData, SoPathList *pathList);
  
  // list of widgets which need to be accessed
  SoWidget acceptButton, slidersForm, buttonsForm, wheelForm;
  
  // build/destroy routines
  SoWidget buildPulldownMenu(SoWidget parent);
  SoWidget buildControls(SoWidget parent);
  SoWidget buildSlidersForm(SoWidget parent);
  
  void doSliderLayout();
  void doDynamicTopLevelLayout();
  int numberOfSliders(SoXtColorEditor::Sliders slider);
  
  // do the updates - if attached, update the node; if callback, call it.
  void doUpdates();
  
  // color field sensor callback and routine
  void fieldChanged();
  static void fieldChangedCB(void *, SoSensor *);
  
  // callbacks and actual routine from sliders, wheel, buttons, menu...
  static void wheelCallback(void *, const float hsv[3]);
  void wheelChanged(const float hsv[3]);
  static void sliderCallback(void *, float);
  void sliderChanged(short id, float value);
  static void buttonsCallback(SoWidget, _ColorEditorCBData *, XtPointer);
  void buttonPressed(short id);
  static void editMenuCallback(SoWidget, _ColorEditorCBData *, XmAnyCallbackStruct *);
  static void sliderMenuCallback(SoWidget, _ColorEditorCBData *, XtPointer);
  
  static void menuDisplay(SoWidget, SoXtColorEditor *editor, XtPointer);
  
  // this is called by both constructors
  void constructorCommon(SbBool buildNow);
  // Function used to create strings in motif buttons/menus.
  void initStrings( void );

};

// Inline functions
void
SoXtColorEditor::addColorChangedCallback(SoXtColorEditorCB *f, void *userData)
{
  callbackList->addCallback((SoCallbackListCB *)f, userData);
}

void
SoXtColorEditor::removeColorChangedCallback(SoXtColorEditorCB *f, void *userData)
{
  callbackList->removeCallback((SoCallbackListCB *)f, userData);
}

#endif  /* _SO_XT_COLOR_EDITOR_ */

#endif // _WIN32
