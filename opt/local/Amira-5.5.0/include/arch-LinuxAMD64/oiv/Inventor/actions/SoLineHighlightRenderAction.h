/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Mott (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/



#ifndef _SO_LINE_HIGHLIGHT_RENDER_ACTION_
#define _SO_LINE_HIGHLIGHT_RENDER_ACTION_

#include <Inventor/actions/SoGLRenderAction.h>

class SbColor;
class SoSeparator;
class SoLightModel;
class SoBaseColor;
class SoDrawStyle;
class SoTexture2;
class SoMaterialBinding;

//////////////////////////////////////////////////////////////////////////////
//
// Line highlight - a subclass of SoGLRenderAction which renders the
// scene graph, then renders wireframe boxes surrounding each selected object.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Selection highlight style.
 *
 * @ingroup actions
 *
 * @DESCRIPTION
 *   SoLineHighlightRenderAction is a render action which renders the specified scene
 *   graph, then renders each selected object again in wireframe. Selected objects
 *   are specified by the first SoSelection node in the scene to which this action is
 *   applied. If there is no renderable geometry in a selected object, no highlight
 *   is rendered for that object. A highlight render action can be passed to the
 *   setGLRenderAction() method of SoWinRenderArea to have an effect on scene
 *   graphs.
 *
 * @EXAMPLE
 *    Here is an example of how a line highlight can be specified for a particular
 *   selection node and render area.
 *
 *   SoWinRenderArea *myRenderArea;
 *
 *   SoSelection *mySelection;
 *
 *
 *   // Set the highlight render action
 *
 *   myRenderArea->setGLRenderAction(
 *
 *   new SoLineHighlightRenderAction());
 *
 *
 *   // Automatic redraw on selection changes
 *
 *   myRenderArea->redrawOnSelectionChange(mySelection);
 *
 *
 * @SEE_ALSO
 *    SoBoxHighlightRenderAction,
 *    SoGLRenderAction,
 *    SoSelection,
 *    SoWinRenderArea,
 *    SoDrawStyle,
 *    SoInteraction
 *
 *
 */

class INVENTOR_API SoLineHighlightRenderAction : public SoGLRenderAction {
  SO_ACTION_HEADER(SoLineHighlightRenderAction);
 public:
  /**
   * Constructor.
   */
  SoLineHighlightRenderAction();

  /**
   * Constructor which takes the normal SoGLRenderAction parameters.
   */
  SoLineHighlightRenderAction(const SbViewportRegion &viewportRegion);


#ifndef HIDDEN_FROM_DOC
  virtual ~SoLineHighlightRenderAction();
#endif // HIDDEN_FROM_DOC

  /**
   * This renders the passed scene graph, and also renders each selected object in
   * wireframe, as specified by the first SoSelection node found in the scene graph.
   */
  virtual void    apply(SoNode *node);

  // Applies action to the graph defined by a path or path list.
  // These simply invoke the parent class apply() methods.
  // These do NOT highlight the path, whether selected or not.
  virtual void    apply(SoPath *path);
  virtual void    apply(const SoPathList &pathList, SbBool obeysRules = FALSE);

  /**
   * This provides a convenient mechanism for turning highlights off or back on. When
   * FALSE is passed, subsequent calls to apply() render the scene graph
   * without rendering highlights. The application is responsible for forcing a
   * redraw of the scene after changing this state. The default visibility is on.
   */
  void setVisible(SbBool b);

  /**
   * Returns whether highlights will be rendered or not.
   */
  SbBool isVisible() const { return hlVisible; }

  /**
   * Sets the color of the highlight. Default is red (1,0,0). The application
   * is responsible for forcing a redraw of the scene to see the effects of this
   * change.
   */
  void            setColor( const SbColor &c );
  /**
   * Gets the color of the highlight.
   */
  const SbColor & getColor();
  /**
   * Sets the line pattern of the highlight. Default is solid, 0xffff. The
   * pattern of bits in the passed variable specifies the pattern of the line. See
   * SoDrawStyle for more information. The application is responsible for forcing a
   * redraw of the scene to see the effects of this change.
   */
  void            setLinePattern( unsigned short pattern );
  /**
   * Gets the line pattern of the highlight.
   */
  unsigned short  getLinePattern();
  /**
   * Sets the line width of the highlight. Default is 3. The application is
   * responsible for forcing a redraw of the scene to see the effects of this change.
   */
  void            setLineWidth( float width );
  /**
   * Gets the line width of the highlight.
   */
  float           getLineWidth();
  /**
   * Sets the size of points (diameter in pixels) rendered by the highlight.  Default is 1.
   * Value must be greater than zero. Only applies to point primitives, e.g. SoPointSet.
   */
  void            setPointSize( float size );
  /**
   * Gets the point size of the highlight.
   */
  float           getPointSize();

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  SoSeparator* getLocalRoot();
  void setLocalRoot( SoSeparator* );

  /** Return true if action is doing highlighting rendering */
  bool isApplying() const { return m_applyingHlAction; }

protected:
  // Nodes which comprise the local highlight graph
  SoSeparator     *localRoot;
  SoLightModel    *lightModel;
  SoBaseColor     *baseColor;
  SoDrawStyle     *drawStyle;
  SoTexture2      *texture;
  SoMaterialBinding *mb;
  SoSearchAction      *sa;

  SbBool          hlVisible;

 private:

  // Copy Constructor Forbidden
  SoLineHighlightRenderAction( const SoLineHighlightRenderAction& ) : SoGLRenderAction(SbVec2s(1, 1)){};

  void constructorCommon();

  bool m_applyingHlAction;
};

inline SoSeparator*
SoLineHighlightRenderAction::getLocalRoot()
{
  return localRoot;
}

#endif /* _SO_LINE_HIGHLIGHT_RENDER_ACTION_ */


