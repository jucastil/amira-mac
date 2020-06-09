/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Olivier Fedkiw (MMM yyyy)
**=======================================================================*/
#ifndef _SB_PIPE_H
#define _SB_PIPE_H

#include <Inventor/helpers/SbGlContextHelper.h>

#if !defined(_WIN32)
#  include <Xm/Xm.h>
#  include <Xm/RowColumn.h>
#  include <Inventor/Xt/SoXtDef.h>
#endif

#include <Inventor/SbLinear.h>

#ifdef _SO_QT_
#  if defined(_WIN32)
#    include <windows.h>
#    include <wingdi.h>
#  endif
#  include <Inventor/Qt/SoZt2SoQt.h>
#else
#  if defined(_WIN32)
#    include <Inventor/Win/SoWinDef.h>
#    include <Inventor/Win/SoXt2SoWin.h>
#  endif
#endif

#include <Inventor/misc/SoCallbackList.h>

class SoXtMPGLWidget;

class SbPipe;
typedef void SbPipeRenderCB(void * userData, SbPipe *pipe);

/**
 * @SCVEXT Stores the graphics info and resources for a MultiPipe window
 *
 * @ingroup ScaleVizMultiPipe
 *
 * @DESCRIPTION
 * @B UNDER CONSTRUCTION @b
 * SbPipe is the class that stores the graphics information and resources for
 * a MultiPipe window.
 * SbPipe
 * objects are created and initialized by SbConfig when the MultiPipe
 * configuration file is
 * read. There is one SbPipe object per screen (e.g., SoFlatScreen)
 * defined in the configuration
 * file. Two SbPipe objects can create and display two MultiPipe
 * windows on the same
 * physical graphics pipe, depending on the hardware.
 *
 *
 */
class INVENTORXT_API SbPipe {

 public:

   /** Multipipe view */
  enum mpView {
    /** Left */
    LEFT,
    /** Center */
    CENTER,
    /** Right */
    RIGHT,
    /** Top */
    TOP,
    /** bottom */
    BOTTOM,
    /** Top right */
    TOP_RIGHT,
    /** Top left */
    TOP_LEFT,
    /** Bottom right */
    BOTTOM_RIGHT,
    /** Bottom left */
    BOTTOM_LEFT,
    /** None */
    NONE,
    /** Stereo right */
    STEREO_RIGHT,
    /** Stereo left */
    STEREO_LEFT
  };


  /**
   * Constructor.
   */
  SbPipe();

  /**
   * Destructor.
   */
  ~SbPipe();

  /**
   * Sets viewport values to describe the part of the scene to be rendered into the
   * MultiPipe window.
   */
  void setViewportValues(SbVec4f);

  /**
   * Returns viewport values to describe the part of the scene to be rendered into the
   * MultiPipe window.
   */
  SbVec4f getViewportValues(void);

  /**
   * Returns the display connection.
   */
#if !defined(_WIN32)
  Display * getDisplay(void);
#else
  UINT * getDisplay(void);
#endif

  /**
   * Sets the display connection
   */
#if !defined(_WIN32)
  void setDisplay(Display *);
#else
  void setDisplay(UINT *);
#endif

  /**
   * Returns a string containing the name of the display.
   */
  char * getDisplayName(void);

  /**
   * Sets the name of the display.
   */
  void setDisplayName(char *);

  /**
   * Sets the wall coordinates.
   */
  void setWall(SbVec3f ll,SbVec3f lr, SbVec3f ul);

  /**
   * Returns the wall coordinates.
   */
  void getWall(SbVec3f & ll,SbVec3f & lr, SbVec3f & ul);

  /**
   * Returns TRUE if the wall coordinates have been set.
   */
  SbBool isWallSet(void);

  /**
   * Returns the widget containing the graphics (drawing area widget).
   */
  SoWidget getWidget(void);

  /**
   * Returns the widget containing the overlay graphics (drawing area widget).
   */
  SoWidget getOverlayWidget(void);

  /**
   * Returns the shell widget.
   */
  SoWidget getShell(void);

  /**
   * Returns the window ID of the drawing area widget.
   */
  Window getWindow(void);

  /**
   * Returns the window ID of the overlay drawing area widget.
   */
  Window getOverlayWindow(void);

  /**
   * Returns the form widget managing the drawing area widget.
   */
  SoWidget getFormWidget(void); //temp

  /**
   * Returns the popupWidget.
   */
  SoWidget getPopupWidget(void);
  /**
   * Sets the popupWidget.
   */
  void setPopupWidget(SoWidget);

  /**
   * Returns the OpenGL context.
   */
  SbGlContextHelper::GLContext getContext(void);

  /**
   * Sets the OpenGL context.
   */
  void setContext(SbGlContextHelper::GLContext);

  /**
   * Returns the OpenGL context for overlays.
   */
  SbGlContextHelper::GLContext getOverlayContext(void);

  /**
   * Sets the OpenGL context for overlays.
   */
  void setOverlayContext(SbGlContextHelper::GLContext);

  /**
   * Returns the visual info structure.
   */
  XVisualInfo * getVisual(void);

  /**
   * Sets the SbPipe id.
   */
  void setId(int);
  /**
   * Returns the SbPipe id.
   */
  int getId(void);

  /**
   * Sets the SbPipe view, (i.e., portion of the scene to render).
   */
  void setView(mpView);

#ifndef HIDDEN_FROM_DOC
  /**
   * Sets the SbPipe view, (i.e., portion of the scene to render).
   */
  int setView(char *);
#endif // HIDDEN_FROM_DOC
  /**
   * Returns the SbPipe view, (i.e., portion of the scene to render).
   */
  mpView getView(void);

  /**
   * Sets the size of the MultiPipe window in pixels. SbConfig, by default,
   * sets the size of the MultiPipe Window to the size of the X Display.
   */
  void setSize(SbVec2s);
  /**
   * Returns the size of the MultiPipe window in pixels.
   */
  SbVec2s getSize(void);

  /**
   * Sets the position of the MultiPipe window in pixels. The default value is
   * (0,0)
   */
  void setPosition(SbVec2s);
  /**
   * Returns the position of the MultiPipe window in pixels.
   */
  SbVec2s getPosition(void);

  /**
   * Sets values for edge blending. The values are percentages of the virtual
   * viewport (i.e., the viewport that contains the MultiPipe windows).
   */
  void setEdgeBlendingValues(float right, float left,
                             float top, float bottom);
  /**
   * Returns values for edge blending. The values are percentages of the virtual
   * viewport (i.e., the viewport that contains the MultiPipe windows).
   */
  void getEdgeBlendingValues(float& right, float& left,
                             float& top, float& bottom);


 SoINTERNAL public:
  /**
   * Configures the MultiPipe window to have no decoration.
   */
  void setNoBorder(void);

  /**
   * Opens a connection to the X display.
   */
  void openDisplay(void);

  /**
   * Sets OpenGL attributes for the choice of a Visual.
   */
  void setGLAttributes(int *);

  /**
   * Builds the Xt hierarchy.
   */
  void buildWidget( SoXtMPGLWidget * );
  /**
   * Builds the drawing area widget.
   */
  void buildGLXWidget(SoXtMPGLWidget *);

  /**
   * Builds the overlay drawing area widget.
   */
  void buildOverlayWidget( SoXtMPGLWidget * );

  /**
   * Builds the manager widget.
   */
  void buildFormWidget(void);

  /**
   * Builds the popup Menu widget.
   */
  void buildPopupMenu(void);

  /**
   * Destroys the Xt hierarchy.
   */
  void destroyWidget(void);

  /**
   * Destroys the drawing area widget.
   */
  void destroyGLXWidget(void);

  /**
   * Destroys the manager widget.
   */
  void destroyFormWidget(void);

  /**
   * Destroys the overlay drawing area widget.
   */
  void destroyOverlayWidget(void);

  /**
   * Sets a new colormap, allocate the cells with XColors, and install the
   colormap.
  */
  void setOverlayColormap(int, XColor *);

  /**
   * Re-installs the colormap.
   */
  void setOverlayColormap(void);

  /**
   * Allocates the colormap cells.
   */
#if !defined(_WIN32)
  void allocCell(Display*, Colormap, XColor*, int, int);
#else
  void allocCell(UINT*, Colormap, XColor*, int, int);
#endif

  /**
   *
   */
  void setRealized(int);

#if defined(_WIN32)
  HDC getDC(void) { return hdc; }
  void setDC(HDC newHdc) { hdc = newHdc; }
#endif

  private :

    int id;
  char * display_name;
  int * attribList;

#if !defined(_WIN32)
  Display * dpy;
#else
  UINT * dpy;
#endif

  XVisualInfo * vi;
  SbGlContextHelper::GLContext ctx;
  SbGlContextHelper::GLContext overlayCtx;

  Colormap overlayColormap;
  unsigned long transparentPixel;
  XColor * newOverlayColormap;
  int newOverlayColormapSize;

  SoWidget shell;
  SoWidget glw;
  SoWidget form;
  SoWidget overlayGlw;
  SoWidget popupWidget;

  mpView view;
  SbVec2s size;
  SbVec2s position;
  SbVec4f viewport;

  SbVec3f * wall;
  SbBool wallIsSet;

  int widgetRealized;

  float rightOverlap, leftOverlap, topOverlap, bottomOverlap;

#if defined(_WIN32)
  HDC hdc;
#endif
};

#endif /* _SB_PIPE_H */

