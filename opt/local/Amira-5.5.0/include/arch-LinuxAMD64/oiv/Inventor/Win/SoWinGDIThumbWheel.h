/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _SO_WIN_GDI_THUMB_WHEEL_
#define  _SO_WIN_GDI_THUMB_WHEEL_

#include <Inventor/Win/SoWinBeginStrict.h>

#include <Inventor/Win/SoWinGDIWidget.h>
#include <Inventor/misc/SoCallbackList.h>


class SoWinMouse;
class SoDataCallbackList;

class SgThumbWheelPart ;
class XmPrimitivePart ;

// callback function prototypes
//mmh: typedef void SoWinGDIThumbWheelCB(void *userData, float val);
typedef void SoWinGDIThumbWheelCB( void *userData, void *data );

//mmh:
// callback data struct
typedef struct { int   reason;
  float value;
} SoWinGDIThumbWheelCBData;

//mmh:
// callback reasons
#define THUMBWHEEL_START                0
#define THUMBWHEEL_DRAG                 1
#define THUMBWHEEL_FINISH               2
#define THUMBWHEEL_VALUE_CHANGE 3


#define XmCR_DRAG THUMBWHEEL_DRAG
#define XmCR_VALUE_CHANGED THUMBWHEEL_VALUE_CHANGE


class SoWinGDIThumbWheel ;
typedef SoWinGDIThumbWheel *SgThumbWheelWidget ;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWinGDIThumbWheel
//
//
//////////////////////////////////////////////////////////////////////////////

class INVENTORW_API SoWinGDIThumbWheel : public SoWinGDIWidget {

 public:
    
  SoWinGDIThumbWheel(SbBool horizontal);
  SoWinGDIThumbWheel(
                     SoWidget parent = NULL,
                     const char *name = NULL, 
                     SbBool buildInsideParent = TRUE, 
                     SbBool horizontal = TRUE);
    
  // This constructor takes a boolean whether to build the widget now.
  // call realizeWidget() for it to be built.
  SoEXTENDER
    SoWinGDIThumbWheel(
                       SoWidget parent,
                       const char *name, 
                       SbBool buildInsideParent,
                       SbBool horizontal, 
                       SbBool buildNow);

  ~SoWinGDIThumbWheel();
    
  void        realizeWidget() ;

  //
  // Routines to specify the wheel value (a rotation given in radians) and get
  // the current wheel value.
  //
  // NOTE: setValue() will call valueChanged callbacks if the value differs.
  //
  void        setValue(float v);
  float       getValue()      { return (float)thumbWheel.value; }
    
  //
  // Those routines are used to register callbacks for the different thumb wheel
  // actions.
  //
  // NOTE: the start and finish callbacks are only to signal when the mouse
  // goes down and up. No valid callback data is passed (NULL passed).
  //
  void        addStartCallback(
                               SoWinGDIThumbWheelCB *f,
                               void *userData = NULL);
  void        addValueChangedCallback(
                                      SoWinGDIThumbWheelCB *f,
                                      void *userData = NULL);

  void        addDragCallback(
                              SoWinGDIThumbWheelCB *f,
                              void *userData = NULL);


  void        addFinishCallback(
                                SoWinGDIThumbWheelCB *f,
                                void *userData = NULL);

  void        removeStartCallback(
                                  SoWinGDIThumbWheelCB *f,
                                  void *userData = NULL);
  void        removeValueChangedCallback(
                                         SoWinGDIThumbWheelCB *f,
                                         void *userData = NULL);
    
  void        removeDragCallback(
                                 SoWinGDIThumbWheelCB *f,
                                 void *userData = NULL);

  void        removeFinishCallback(
                                   SoWinGDIThumbWheelCB *f,
                                   void *userData = NULL);

  // true while the value is changing interactively
  SbBool  isInteractive()                     { return interactive; }

  // new stuff
  void setBounds(int nLower,int nUpper)
    { thumbWheel.lower_bound = nLower ;
    thumbWheel.upper_bound = nUpper ; } ;

  void setHomePosition(int n) 
    { thumbWheel.home_position = n; } ;
  
  void setAngleRange(int n) 
    { thumbWheel.angle_range = n; } ;

  void setUnitsPerRotation(int n) 
    { thumbWheel.angle_factor = n; } ;

  void setHighlightThickness(int n) 
    { primitive.highlight_thickness = n; } ;

  void setShadowThickness(int n) 
    { primitive.shadow_thickness = n; } ;


  void setValue(int n) 
    { thumbWheel.value = n; } ;

  void setOrientation(unsigned char n) 
    { thumbWheel.orientation = n; } ;

  void setAnimate(SbBool n) 
    { thumbWheel.animate = n; } ;

  void setShowHomeButton(SbBool n) 
    { thumbWheel.show_home_button = n; } ;



 protected:


  SoWidget          buildWidget(SoWidget parent);
    
 protected:
  // redefine these to do thumb wheel specific things
  virtual void    redraw();
  virtual void    processEvent(XAnyEvent *anyevent);
  virtual void    sizeChanged(const SbVec2s &newSize);
    
  // local variables
  SbBool      horizontal;
  SbBool      realized;
  SoWinMouse  *mouse;
    
  // callback variables
  SoDataCallbackList *startCallbacks;
  SoDataCallbackList *finishCallbacks;
  SoDataCallbackList *changedCallbacks;
  SoDataCallbackList *dragCallbacks;
  SbBool      interactive;

  // this is called by both constructors
  void constructorCommon(SbBool horizontal, SbBool buildNow);

  // new stuff from motif thumbwheel

  typedef struct _XmPrimitivePart
  {
    int highlight_thickness ;
    int shadow_thickness ;
  } XmPrimitivePart ;

  typedef struct _XmCorePart
  {
    int width ;
    int height ;
    int depth ;
  } XmCorePart ;

  typedef int Dimension ;
  typedef int Cardinal ;
  typedef void XtString ;


  typedef struct _SgThumbWheelPart {
    /* resources */
    int lower_bound;
    int upper_bound;
    int home_position;
    int angle_range;
    int angle_factor;
    int value;
    unsigned char orientation;
    SbBool animate;
    SbBool show_home_button;

    /* private state */
    SbBool infinite;
    SbBool dragging;
    int drag_begin_value;
    int last_mouse_position;
    SbBool pegged;
    int pegged_mouse_position;
    Dimension viewable_pixels;
    int user_pixels;
    Pixmap pix1;
    Pixmap pix2;
    Pixmap pix3;
    Pixmap pix4;
    Pixmap pix1_hilite;
    Pixmap pix2_hilite;
    Pixmap pix3_hilite;
    Pixmap pix4_hilite;
    Pixmap current_quiet_pixmap; /* this will be equal to one of the others */
    Pixmap current_hilite_pixmap; /* this will be equal to one of the others */
    SbBool wheel_hilite;

    Pixmap button_quiet_pixmap;
    Pixmap button_hilite_pixmap;
    SbBool button_hilite;

    HDC foreground_GC;
    /*
      shaderptr shader;
    */

    int wheel_x;
    int wheel_y;
    int button_x;
    int button_y;

    SbBool home_button_armed;
    SbBool resizePixmaps ;

  } SgThumbWheelPart ;


  XmCorePart               core ;
  XmPrimitivePart  primitive;
  SgThumbWheelPart thumbWheel;

  HDC  hMemDC ;
  HPEN hPen[7] ;
  HBRUSH hBrush[7] ;
  HPEN hOldPen ;
  HBRUSH hOldBrush ;

  void Initialize();
  void GetForegroundGC() ;
  int ConvertPixelsToUserUnits(int pixels);
  int ConvertUserUnitsToPixels(int uu);
  void CreateAndRenderPixmaps() ;
  void Redisplay() ;

  HDC SetupGC(int nGC) ;

  void RenderPixmap(int which);
  void RenderButtonPixmaps();

  void Destroy() ;
  void FreePixmaps();
  void SetCurrentPixmap( SbBool value_increased) ;

  void Resize() ;

  SbBool MouseIsInWheel(int event_x,int event_y);
  SbBool MouseIsInButton(int event_x,int event_y);

  void Motion(XEvent *event, XtString *params, Cardinal *num_params);
  void Btn1Down(XEvent *event, XtString *params, Cardinal *num_params);
  void Btn2Down(XEvent *event, XtString *params, Cardinal *num_params);
  void Btn3Down(XEvent *event, XtString *params, Cardinal *num_params);
  void Btn1Motion(XEvent *event, XtString *params, Cardinal *num_params);
  void Btn2Motion(XEvent *event, XtString *params, Cardinal *num_params);
  void Btn3Motion(XEvent *event, XtString *params, Cardinal *num_params);
  void Btn1Up(XEvent *event, XtString *params, Cardinal *num_params) ;
  void Btn2Up(XEvent *event, XtString *params, Cardinal *num_params) ;
  void Btn3Up(XEvent *event, XtString *params, Cardinal *num_params) ;
  void Enter(XEvent *event, XtString *params, Cardinal *num_params);
  void Leave(XEvent *event, XtString *params, Cardinal *num_params);

  void PageUp(XEvent *event, XtString *params, Cardinal *num_params);
  void PageDown(XEvent *event, XtString *params, Cardinal *num_params);
  void Up(XEvent *event, XtString *params, Cardinal *num_params);
  void Down(XEvent *event, XtString *params, Cardinal *num_params);
  void Left(XEvent *event, XtString *params, Cardinal *num_params);
  void Right(XEvent *event, XtString *params, Cardinal *num_params);
  void Help(XEvent *event, XtString *params, Cardinal *num_params);
  void BeginLine(XEvent *event, XtString *params, Cardinal *num_params);
  void EndLine(XEvent *event, XtString *params, Cardinal *num_params);
  void ArmHomeButton() ;
  void DisarmHomeButton() ;
  void RenderButtonShadows() ;
  int ProcessMouseEvent( int event_x,int event_y) ;
  void IssueCallback( int reason, int value, XEvent *event) ;

  Boolean SetValues(SgThumbWheelWidget rw, SgThumbWheelWidget nw, ArgList args, Cardinal *num_args);
  Boolean ValidateFields(SgThumbWheelWidget req_w,
                         SgThumbWheelWidget new_w) ;



};

#include <Inventor/Win/SoWinEndStrict.h>

#endif  /* _SO_WIN_THUMB_WHEEL_ */
