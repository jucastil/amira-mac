/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SO_WIN_GDI_WIDGET_H_
#define _SO_WIN_GDI_WIDGET_H_

#include <Inventor/Win/SoWinBeginStrict.h>

#include <Inventor/Win/SoWinComponent.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWinGDIWidget
//
//
//////////////////////////////////////////////////////////////////////////////

class INVENTORW_API SoWinGDIWidget : public SoWinComponent {
 public:
    
  virtual Window getNormalWindow();
  Window      getOverlayWindow();
    

  Hdc getNormalDC()  { return hdcNormal; }
  Hdc copyWindowBits() ;
    
  SoWidget      getNormalWidget()           { return singleBufferWidget; }
    
  //
  // shows/hides a border of thickness 3 around the glx widgets. This
  // if OFF by default, but turned on by the render area.
  //
  void        setBorder(SbBool onOrOff);
  int             getBorderSize() {return borderSize;} ;
  SbBool      isBorder() const            { return borderSize != 0; }
        
 protected:
    
  SoWinGDIWidget(
                 SoWidget parent = NULL,
                 const char *name = NULL, 
                 SbBool buildInsideParent = TRUE, 
                 SbBool buildNow = TRUE,
                 SbBool sync = TRUE);

  virtual ~SoWinGDIWidget();
    
  // subclasses MUST redefine redraw() to draw in the normal bit planes.
  // redrawOverlay() should be defined if the overlay planes are being
  // used, and processEvent() should be defined if X events are being 
  // received (see eventMask).
  virtual void        redraw() = 0;
  virtual void        processEvent(XAnyEvent *anyevent);
    
  // subclasses can redefine these to do something useful.
  // initGraphic() is called whenever a GLX window gets created
  // sizeChanged() is called whenever the window changes size
  // widgetChanged() is called whenever the widget is changed (i.e. at
  //    initialization or after switching from single->double buffer)
  virtual void        initGraphic();
  virtual void        sizeChanged(const SbVec2s &newSize);
  virtual void        widgetChanged(SoWidget newWidget);
    
  // sets/gets the size of the glx widget(s) - Note this size could be
  // different from the SoWinComponent::getSize() method which return
  // the size of the component, not necessary the same as the glx widget
  // window (because of extra stuff like the decoration in the viewers).
  void                setGlxSize(SbVec2s newSize);
  const SbVec2s &     getGlxSize() const                      { return glxSize; }
  SbVec2s             glxSize; // size of glx widgets which is always up to date
    
  // subclasses can use this routine as the event handler for any
  // devices they wish to get input from.
  static void eventHandler(SoWidget, SoWinGDIWidget *, XAnyEvent *, Boolean *);
    
  SbBool              isRGBMode()         { return (TRUE); }
    
  Colormap            colorMap;       // set when color index is used
    
  // make those methods protected so enable the SoWinRenderArea to use them
  // directly when it needs to build the widget and get its resources.
  SoWidget              buildWidget(SoWidget parent);
  SoWidget              getGlxMgrWidget()               { return singleBufferWidget; }

  Pixmap XCreatePixmap(
                       UINT *dpy,
                       Window w,
                       int nWidth,
                       int nHeight,
                       int nDepth) ;
        
  void XFillRectangle(
                      UINT *dpy, 
                      Pixmap pix, 
                      HDC gc,
                      int x,int y,
                      int width,int height);
        
  void XDrawLine(
                 UINT *dpy, 
                 Pixmap pix, 
                 HDC gc, 
                 int x1, int y1, 
                 int x2, int y2);

  void XCopyArea(
                 UINT*         display ,
                 Hwnd            src   ,
                 Hwnd            dest  ,
                 HDC             src_gc , /* extra hack for windows */
                 HDC             dst_gc ,
                 int             src_x  ,
                 int             src_y  ,
                 unsigned int    width  ,
                 unsigned int    height ,
                 int             dest_x ,
                 int             dest_y 
                 );

    
 protected:
  // local vars
  SoWidget      singleBufferWidget;

  // Note for _WIN32:
  // 1) All the "SoWidget" values above are actually type "HWND".
  // 2) The "GLXContext" values above are actually type "HGLRC".

  // For _WIN32 we need a GL context *and* a device context for each
  // GL drawing window (we don't need one for the mgr because we don't
  // plan to ever draw in it).  These correspond to the "ctx..." vars.
  // Note: This plan depends on use of the CS_OWNDC style.

  Hdc hdcNormal;

  // For _WIN32 we also need a logical color palette for each drawing
  // area if we happen to running on an 8bit device...

  HPALETTE palNormal ;
  HPALETTE oldPalette;    // Need this for cleanup before deletion

  virtual void onExpose();

 private:
  // For _WIN32 we also need to remember who our parent is
  SoWidget parent;

  // For _WIN32 we have to simulate the behavior of X where getting a
  // mouse button down event guarantees you will also get the
  // corresponding button up event.  Otherwise examiner viewer windows
  // get out of sync if a mouse button is released outside the window.
  UINT mouseCaptured;

  // NOTYET?
  // If parent of glxMgrWindow is MDI we need to call DefMDIChildProc
  // in mgrWindowProce instead of DefWindowProc
  // SbBool m_nParentIsMDI ;


  int                 borderSize;
    
  // specify if sizeChanged() should be called when an expose event
  // is received (as opposed to when a resize event is received, where
  // the window hasn't yet been maped to the new size).
  // ??? a GlxDraw bug ?
  SbBool              windowResized;
    
  // creates a GLX widget of the correct current type and get the current
  // set of windows, color maps, etc...
  void                destroyNormalWindows();
  void                destroyGDIWidget(SoWidget &w);
    
  // callbacks from glx widget
  static void ginitCB(SoWidget, SoWinGDIWidget *, XtPointer);
  static void exposeCB(SoWidget, SoWinGDIWidget *, XtPointer);
  static void resizeCB(SoWidget, SoWinGDIWidget *, XtPointer);
  static void mgrStructureNotifyCB(SoWidget, SoWinGDIWidget *, XAnyEvent *, Boolean *);

  // Window proc for SoWinGDI drawing windows
  static LRESULT CALLBACK gdiWindowProc( Hwnd hwnd, UINT message,
                                         WPARAM wParam, LPARAM lParam );
};

#include <Inventor/Win/SoWinEndStrict.h>

#endif // _SO_WIN_GDI_WIDGET_H_

