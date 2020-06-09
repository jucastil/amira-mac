/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Alain Dumesny (MMM yyyy)
** Modified by : David Mott (MMM yyyy)
**=======================================================================*/


#ifndef _SO_QT_PAINTWIDGET_
#define _SO_QT_PAINTWIDGET_
#include <Inventor/Qt/OivQtCompat.h>

#include <Inventor/Qt/SoQtComponent.h>
#include <Inventor/helpers/SbGlContextHelper.h>

#include <QtCore/QPointer>

class INVENTORQT_API SoQtPaintWidget : public SoQtComponent
{
  Q_OBJECT
                
    public:
        
        
  /**
   * Gets the normal GL window, which is
   * needed as an argument to SbGlContextHelper::makeCurrent() when drawing in the normal
   * planes.
   * 
   * Note: This should @B not @b be cached by users because it will change as
   * single/double buffering changes.
   */
  virtual WindowQt getNormalWindow();

  /**
   * Gets the current normal context, which is
   * needed as an argument to glXMakeCurrent() when drawing in the normal
   * planes.
   * 
   * Note: This should @B not @b be cached by users because it will change as
   * single/double buffering changes.
   */
  SbGlContextHelper::GLContext getNormalContext()          { return ctxNormal; }

  /**
   * Gets the current normal widget, which is
   * needed as an argument to glXMakeCurrent() when drawing in the normal 
   * planes.
   * 
   * Note: This should @B not @b be cached by users because it will change as
   * single/double buffering changes.
   */
  QWidget *getNormalWidget() { return singleBufferWidget; }
        
#ifdef _WIN32
  /**
   * Returns the device context (which is needed for SbGlContextHelper::makeCurrent).
   */
  Hdc getNormalDC()  { return hdcNormal; }
        
 SoEXTENDER public:
        
  // Set/get thread this context belongs to -- mmh Apr-99
  DWORD getThreadId() { return dwThreadId; };
  void setThreadId(DWORD id) { dwThreadId=id; };
#endif  

 SoEXTENDER public:
        
  virtual SbBool makeNormalCurrent();
    
 protected:
        
  SoQtPaintWidget(QWidget *parent = NULL,
                  const char *name = NULL, 
                  SbBool buildInsideParent = TRUE, 
                  SbBool buildNow = TRUE);
        
  virtual ~SoQtPaintWidget();
        
  // subclasses MUST redefine redraw() to draw in the normal bit planes.
  // redrawOverlay() should be defined if the overlay planes are being
  // used, and processEvent() should be defined if X events are being 
  // received (see eventMask).
  virtual void        redraw() = 0;
  virtual void    processEvent(QEvent *anyevent);
        
  // subclasses can redefine these to do something useful.
  // initGraphic() is called whenever a GLX window gets created
  // sizeChanged() is called whenever the window changes size
  // widgetChanged() is called whenever the widget is changed (i.e. at
  //    initialization or after switching from single->double buffer)
  virtual void        initGraphic();
  virtual void        sizeChanged(const SbVec2s &newSize);
  virtual void        widgetChanged(QWidget *newWidget);
    
  // sets/gets the size of the glx widget(s) - Note this size could be
  // different from the SoWinComponent::getSize() method which return
  // the size of the component, not necessary the same as the glx widget
  // window (because of extra stuff like the decoration in the viewers).
  void  setGlxSize(SbVec2s newSize);
  const SbVec2s &     getGlxSize() const                      { return glxSize; }
        
  // subclasses can use this routine as the event handler for any
  // devices they wish to get input from.
  static void eventHandler(QWidget *, SoQtPaintWidget *, QEvent *, bool *);

  // returns TRUE if main window is in rgb mode (FALSE if color index)
  SbBool isRGBMode() 
    { return ((glModes & SO_GLX_RGB) ? 1 : 0); }
        
  Colormap        colorMap;       // set when color index is used
  int colorMapSize;
        
  SbBool      waitForExpose;
  SbBool      drawToFrontBuffer;
        
  QWidget *buildWidget(QWidget *parent);
  QWidget *getGlxMgrWidget() { return mgrWidget; }
        
  unsigned long transparentPixel;

  bool eventFilter(QObject * object,QEvent *event);

  virtual void onExpose();
  
 private:
        
  // local vars
  QWidget *mgrWidget;
  QPointer<QWidget> singleBufferWidget;
  GLXContext      ctxNormal, ctxSingle;
  SbVec2s glxSize; // size of glx widgets which is always up to date
        
        
#ifdef _WIN32
        
  // For _WIN32 this struct functionally replaces attribList
  PIXELFORMATDESCRIPTOR pfd;
  int                   m_nPixelFormat;
        
  // For _WIN32 these are saved because XGetVisualInfo doesn't exist...
  PIXELFORMATDESCRIPTOR pfdNormal, pfdOverlay, pfdSingle, pfdDouble;
        
  // For _WIN32 we need a GL context *and* a device context for each
  // GL drawing window (we don't need one for the mgr because we don't
  // plan to ever draw in it).  These correspond to the "ctx..." vars.
  // Note: This plan depends on use of the CS_OWNDC style.
        
  Hdc hdcNormal, hdcOverlay, hdcSingle, hdcDouble;
        
  // For _WIN32 we also need a logical color palette for each drawing
  // area if we happen to running on an 8bit device...
        
  HPALETTE palNormal, oldPalette;
        
  // For _WIN32 we also need to remember our parent and our
  // "ancestor" (the toplevel window that we're descended from).
  QWidget *parent;
  QWidget *ancestor;
        
  // For _WIN32 we have to simulate the "focus follows pointer" behavior
  // that X provides for free.  Otherwise the app would have to be
  // responsible for giving focus to the GL window and/or the user
  // would have to keep clicking to get focus in the GL window.  Focus
  // is required for the 1-button mouse viewer behaviors like Ctrl-Left
  // Button and so on.  This variable tracks whether we have focus
  // based on the WM_SETFOCUS/WM_KILLFOCUS messages (see glxWindowProc).
  int haveFocus;
        
  // This flag tracks whether "focus follows pointer" is enabled.
  int stealFocus;
        
  // For _WIN32 we have to simulate the behavior of X where getting a
  // mouse button down event guarantees you will also get the
  // corresponding button up event.  Otherwise examiner viewer windows
  // get out of sync if a mouse button is released outside the window.
  UINT mouseCaptured;
        
  DWORD dwThreadId; // thread to which this context belongs -- mmh Apr-99
        
#endif //_WIN32

        
  int *attribList;
  int glModes;
  int borderSize;
  SbBool enableDrawToFrontBuffer;
        
  SbBool windowResized;
        
  // set of windows, color maps, etc...
  void destroyNormalWindows();
  void destroyWidget(QWidget *w);

  // callbacks from glx widget
  static void     ginitCB(QWidget *, SoQtPaintWidget *, void *);
  static void     exposeCB(QWidget *, SoQtPaintWidget *, void *);
  static void     resizeCB(QWidget *, SoQtPaintWidget *, void *);
        
};

#endif // _SO_QT_PAINTWIDGET_
