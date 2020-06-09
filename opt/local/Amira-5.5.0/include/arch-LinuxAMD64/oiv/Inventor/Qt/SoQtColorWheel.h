/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Alain Dumesny (MMM yyyy)
**=======================================================================*/

#ifndef  _SO_QT_COLOR_WHEEL_
#define  _SO_QT_COLOR_WHEEL_

#include <Inventor/Qt/OivQtCompat.h>
#include <Inventor/SbColor.h>
#include <Inventor/SbLinear.h>
#include <Inventor/Qt/SoQtGLWidget.h>
#include <Inventor/misc/SoCallbackList.h>


class SoQtMouse;

// callback function prototypes
typedef void SoQtColorWheelCB(void *userData, const float hsv[3]);
                                           
//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoQtColorWheel
//
//      Lets you interactively select colors using a color wheel. User register
//  callback(s) to be notified when a new color has been selected. There is
//  also a call to tell the color wheel what the current color is when it is
//  changed externally.
//
//////////////////////////////////////////////////////////////////////////////

class INVENTORQT_API SoQtColorWheel : public SoQtGLWidget
{
  Q_OBJECT

public:
    
  SoQtColorWheel(QWidget* parent = NULL,
                 const char *name = NULL, 
                 SbBool buildInsideParent = TRUE);
  ~SoQtColorWheel();
    
  //
  // Routine to tell the color wheel what the current HSV color is.
  //
  // NOTE: if calling setBaseColor() changes the marker position the
  // valueChanged callbacks will be called with the new hsv color.
  //
  void        setBaseColor(const float hsv[3]);
  const float *getBaseColor()         { return hsvColor; }
    
  //
  // This routine sets the WYSIWYG (What You See Is What You Get) mode.
  // When WYSIWYG is on the colors on the wheel will reflect the current
  // color intensity (i.e. get darker and brighter)
  //
  void        setWYSIWYG(SbBool trueOrFalse);    // default FALSE
  SbBool      isWYSIWYG()             { return WYSIWYGmode; }
    
  //
  // Those routines are used to register callbacks for the different 
  // color wheel actions.
  //
  // NOTE: the start and finish callbacks are only to signal when the mouse
  // goes down and up. No valid callback data is passed (NULL passed).
  //
  void    addStartCallback(
                           SoQtColorWheelCB *f,
                           void *userData = NULL)
  { startCallbacks->addCallback((SoCallbackListCB *) f, userData); }

  void    addValueChangedCallback(
                                  SoQtColorWheelCB *f, 
                                  void *userData = NULL)
  { changedCallbacks->addCallback((SoCallbackListCB *) f, userData); }
        
  void    addFinishCallback(
                            SoQtColorWheelCB *f,
                            void *userData = NULL)
  { finishCallbacks->addCallback((SoCallbackListCB *) f, userData); }
                                       
  void    removeStartCallback(
                              SoQtColorWheelCB *f,
                              void *userData = NULL)
  { startCallbacks->removeCallback((SoCallbackListCB *) f, userData); }

  void    removeValueChangedCallback(
                                     SoQtColorWheelCB *f,
                                     void *userData = NULL)
  { changedCallbacks->removeCallback((SoCallbackListCB *) f, userData); }

  void    removeFinishCallback(
                               SoQtColorWheelCB *f,
                               void *userData = NULL)
  { finishCallbacks->removeCallback((SoCallbackListCB *) f, userData); }
        
        
  // true while the color is changing interactively
  SbBool  isInteractive()                     { return interactive; }

protected:  

  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoQtColorWheel::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER
  SoQtColorWheel(
                 QWidget* parent,
                 const char *name, 
                 SbBool buildInsideParent, 
                 SbBool buildNow);

  QWidget*          buildWidget(QWidget* parent);

private:
    
  // redefine these to do color wheel specific things
  virtual void    redraw();
  virtual void    redrawOverlay();
  virtual void    processEvent(QEvent *anyevent);
  virtual void    initOverlayGraphic();
  virtual void    sizeChanged(const SbVec2s &newSize);
    
  // color wheels local variables
  SbBool      WYSIWYGmode;
  SbBool      blackMarker;
  float       hsvColor[3];
  int cx, cy, radius;
  SbColor     *defaultColors, *colors;
  SbVec2f     *geometry;
  SoQtMouse   *mouse;
    
  // callback variables
  SoCallbackList *startCallbacks;
  SoCallbackList *changedCallbacks;
  SoCallbackList *finishCallbacks;
  SbBool      interactive;
    
  // routines to make the wheel geometry, colors, draw it....
  void    makeWheelGeometry();
  void    makeWheelColors(SbColor *col, float intensity);
  void    drawWheelSurrounding();
  void    drawWheelColors();
  void    checkMarkerColor();
  void    drawWheelMarker();
  void    moveWheelMarker(short x, short y);

  // this is called by both constructors
  void constructorCommon(SbBool buildNow);
#ifdef _WIN32
  void SaveUnder(short x,short y);
  void RestoreUnder();

  SbBool nSaved;
  short nSaveX, nSaveY;
#  ifndef GDISAVE
  unsigned long *pSaveBuf;
#  else
  HBITMAP hSaveBits;
  HDC     hSaveDC;
#  endif
#endif
#if defined(__APPLE__) || defined(_WIN32)
  int nMarkR, nMarkG, nMarkB;
#endif
};

#endif  /* _SO_QT_COLOR_WHEEL_ */
