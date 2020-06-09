/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _SO_QT_SLIDER_
#define  _SO_QT_SLIDER_

#include <Inventor/Qt/OivQtCompat.h>
#include <Inventor/misc/SoCallbackList.h>
#include <Inventor/Qt/SoQtComponent.h>
#include <Inventor/Qt/SoQtBasicSlider.h>

#include <QtCore/QPointer>

class SoFloatCallbackList;
class QLayout;
class QHBoxLayout;
class QLineEdit;
class QLabel;

// callback function prototypes
typedef void SoQtSliderCB(void *userData, float val);


//////////////////////////////////////////////////////////////////////////////
//  Class: SoQtSlider
//
//      This is the basic slider type, which lets you set the slider value with a
//  slot and emit signals (and register callbacks) when the slider is being
//  moved (either as soon as the slider changes values, or when the slider has
//  stopped moving (mouse up)).

class INVENTORQT_API SoQtSlider : public SoQtComponent {
  Q_OBJECT

    public:
    
  // constructor/destructor
  SoQtSlider( QWidget* parent = NULL,
              const char *name = NULL, 
              SbBool buildInsideParent = TRUE);
  ~SoQtSlider();

  // Access functions
  float       getValue() const;
  void  setLabel(const QString&);
  const QString& getLabel() const;
    
  // Display a numeric value in a text field to the right of the slider
  // which can be edited to change the value of the slider.
  // Default is TRUE (display the numeric value).
  void        setNumericFieldVisible(SbBool b = TRUE);
  SbBool      isNumericFieldVisible() const   { return numberVisible; }
    
  // Those routines are used to register callbacks for the different slider
  // actions.
  // NOTE: the start and finish callbacks are only to signal when the mouse
  // goes down and up. No valid callback data is passed (0.0 passed).
  void        addStartCallback (SoQtSliderCB *f, void *userData = NULL);
  void        addValueChangedCallback (SoQtSliderCB *f, void *userData = NULL);
  void        addFinishCallback (SoQtSliderCB *f, void *userData = NULL);

  void        removeStartCallback (SoQtSliderCB *f, void *userData = NULL);
  void        removeValueChangedCallback (SoQtSliderCB *f, void *userData = NULL);
  void        removeFinishCallback (SoQtSliderCB *f, void *userData = NULL);
                        
  // true while the value is changing interactively
  void interactivity( SbBool flag ) { sliderWidget->interactivity(flag); }
  SbBool isInteractive() { return sliderWidget->isInteractive(); }
    
  // sets/gets the size of the actual slider, excluding the label and
  // text field widget sizes which are fixed in size. 
  // This is the prefered behavior since it allows a user to align
  // multiple sliders (same size) regardless of the text label size
  // (which are usually different).
  // NOTE: this is different from most widgets, which do resize their
  // container widgets. This functionality can still be achieved using
  // the setSize() and getSize() methods.
  void            setSliderSize(const SbVec2s &size);
  SbVec2s       getSliderSize();


 protected:  
  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoQtSlider::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER SoQtSlider (QWidget* parent,
                         const char *name, 
                         SbBool buildInsideParent, 
                         SbBool buildNow);

  // Actualy build the widgets
  QWidget*  buildWidget(QWidget* parent, SoQtBasicSlider::Type t = SoQtBasicSlider::PLAIN_SLIDER);

  // Data
  SoQtBasicSlider* sliderWidget;

 private:
  // Data
  QPointer<QWidget>         mgrWidget;
  QPointer<QLineEdit>       numberWidget;
  QPointer<QLabel>          labelWidget;
  QHBoxLayout*     layout;
  SbBool           numberVisible;
  SbVec2s          sliderSize;
  QString          labelString;
    
  // build routines
  void constructorCommon(SbBool buildNow);
  void doLayout();
  void updateText ();

  // Callbacks
  void sliderChanged(float val);
  static void sliderChangedCB(void *p, float val) { ((SoQtSlider*)p)->sliderChanged (val); };
  void sliderStart();
  static void sliderStartCB(void *p, float val);
  void sliderStop();
  static void sliderStopCB(void *p, float val);
  static void textFieldCB(QWidget*, SoQtSlider *, XtPointer);

  private Q_SLOTS:
    // internal use only
    void textChangedSlot();

  public Q_SLOTS:
    // Set the value of the slider
    void setValue(float v);

  Q_SIGNALS:
    // Those signals are the pendant of the callbacks routines
    void start ();   
    void valueChanged (float value);
    void finish ();

};

inline void 
SoQtSlider::sliderStartCB(void *p, float )
{
  ((SoQtSlider*)p)->sliderStart ();
}

inline void 
SoQtSlider::sliderStopCB(void *p, float )
{ 
  ((SoQtSlider*)p)->sliderStop ();
}

#endif  /* _SO_QT_SLIDER_ */
