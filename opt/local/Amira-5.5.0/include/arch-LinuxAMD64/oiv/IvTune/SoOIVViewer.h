/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef SoOIVViewer_included
#define SoOIVViewer_included


#ifndef __APPLE__
// Used to block the translation of SoXt to SoQt that we don't want
#  define __SOXT2SOQT_H__
#endif

#include <Inventor/Qt/SoQtRenderArea.h>

#if defined(SOQT) && !defined(__APPLE__)
#  undef SOQT
#  undef Widget
#  include <Inventor/Xt/SoXtRenderArea.h>
#  include <Inventor/Xt/viewers/SoXtViewer.h>
#  define SOQT
#else
#  include <Inventor/Xt/SoXtRenderArea.h>
#  include <Inventor/Xt/viewers/SoXtViewer.h>
#endif

#include <Inventor/sys/port.h>
#include <Inventor/SbColor.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/actions/SoGLRenderAction.h>

class SoGuiRenderArea;
class SoNode;
class SoSelection;
class SoSceneManager;

/**
 * SoOIVViewer.
 * [OIVJAVA-WRAPPER-CLASS NO_WRAP]
 */
class IVTUNE_API SoOIVViewer
{

public:
  /**
   * Constructor.
   */
  SoOIVViewer(SoGuiRenderArea *viewer);

  /**
   * Destructor.
   */
  ~SoOIVViewer();

  /**
  * This returns the base widget handle for this component. 
  */ 
  QWidget *getWidget();
  
  /**
   * Returns true if the viewer was created by IvTune, false
   * if it was created by an application.
   */
  bool isOfflineViewer() const;

  /**
  * Sets the scene graph to be rendered in this component's window.
  */
  void setSceneGraph(SoNode *newScene);
  /**
  * Gets the scene graph to be rendered in this component's window.
  */
  SoNode* getSceneGraph();

  /**
  * Gets the background color for this window.
  */
  const SbColor& getBackgroundColor();

  /**
  * Gets current viewport region to use for rendering.
  */
  const SbViewportRegion &getViewportRegion();
  /**
  * Sets the GL render action to use. This is used to set selection
  * highlighting with the SoBoxHighlightRenderAction and SoLineHighlightRenderAction
  * classes.
  */
  void setGLRenderAction(SoGLRenderAction *ra);
  /**
  * Gets the GL render action to use. This is used to set selection
  * highlighting with the SoBoxHighlightRenderAction and SoLineHighlightRenderAction
  * classes.
  */
  SoGLRenderAction* getGLRenderAction();

  /**
  * Call this convenience method to have this render area redraw whenever the
  * selection list changes in the passed node. This is useful if using a highlight
  * render action like the SoBoxHighlightRenderAction to correctly render whenever
  * the selection changes. Pass NULL to turn this off.
  */
  void redrawOnSelectionChange(SoSelection *s);

  /**
  * Gets the normal scene manager.
  * 
  * Note: For convenience most of the SoSceneManager methods have already been added
  * to this class.
  */
  SoSceneManager* getSceneManager();
 
  /**
   * Gets the quality level for rendering transparent objects. See
   * SoGLRenderAction for possible transparency types.
   */
  SoGLRenderAction::TransparencyType  getTransparencyType();

  /**
   * Sets the background color for this window. Default is black (0,0,0). @BR
   *  @BR
   * The default value can be set using the environment variable
   * OIV_BACKGROUND_COLOR (3 floats representing RGB values of the colors separated by space).
   */
  void setBackgroundColor(const SbColor &c);

  /**
   * Sets the quality level for rendering transparent objects. See
   * SoGLRenderAction for possible transparency types.
   */
  void setTransparencyType(SoGLRenderAction::TransparencyType type);

  SbBool bindNormalContext();

  SbBool unbindNormalContext();

  /**
   * Return if the viewer is in viewing mode or not
   */
  SbBool isViewing();

  SoINTERNAL public:

  void setOfflineMode( bool isOffline );
  SoGuiRenderArea *getGuiRenderArea() const;

  private:
    SoGuiRenderArea *m_renderArea;

    SbColor def_background;
    SbViewportRegion def_viewport;

	bool m_isOffline;
};

inline SoGuiRenderArea *
SoOIVViewer::getGuiRenderArea() const
{
  return m_renderArea;
}

#endif

