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
** Modified by : Damien Dallarosa (Nov 2009)
**=======================================================================*/


#ifndef _SO_BOX_HIGHLIGHT_RENDER_ACTION_
#define _SO_BOX_HIGHLIGHT_RENDER_ACTION_

#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoCallbackAction.h>

class SbColor;
class SoSeparator;
class SoLightModel;
class SoBaseColor;
class SoDrawStyle;
class SoTexture2;
class SoTranslation;
class SoMatrixTransform;
class SoCallback;
class SoMaterialBinding;
class SoComplexity;
class SoCube;
class SoIndexedLineSet;
class SoSelection;
class SoNodeSensor;

/**
 * A selection highlight style.
 * 
 * @ingroup actions
 * 
 * @DESCRIPTION
 *   SoBoxHighlightRenderAction is a render action which renders the specified scene
 *   graph, then renders wireframe boxes surrounding each selected object. Selected
 *   objects are specified by the first SoSelection node in the scene to which this
 *   action is applied. If an SoGetBoundingBoxAction applied to a selected object
 *   produces an empty bounding box, no highlight is rendered for that object. A
 *   highlight render action can be passed to the setGLRenderAction() method
 *   of render area and viewer classes to have an effect on scene graphs.
 * 
 * @EXAMPLE
 *   Here is an example of how a box highlight can be specified for a particular
 *   selection node and viewer:
 *   
 *   \oivnetdoc
 *     \code
 *     SoWinExaminerViewer Viewer = new SoWinExaminerViewer();
 *     SoSelection SelectionNode  = new SoSelection();
 *     . . .
 *     // Set the highlight render action
 *     Viewer.SetGLRenderAction( new SoBoxHighlightRenderAction() );
 *    
 *     // Request automatic redraw when selection changes
 *     Viewer.RedrawOnSelectionChange( SelectionNode );
 *     \endcode
 *   \else
 *     \code
 *     SoWinExaminerViewer *pViewer = new SoWinExaminerViewer();
 *     SoSelection      *pSelection = new SoSelection();
 *     . . .
 *     // Set the highlight render action
 *     pViewer->setGLRenderAction( new SoBoxHighlightRenderAction() );
 *    
 *     // Request automatic redraw when selection changes
 *     pViewer->redrawOnSelectionChange( pSelection );
 *     \endcode
 *   \endoivnetdoc
 * 
 * @SEE_ALSO
 *    SoLineHighlightRenderAction,
 *    SoGLRenderAction,
 *    SoSelection,
 *    SoWinRenderArea,
 *    SoDrawStyle,
 *    SoInteraction
 * 
 * 
 */ 

class INVENTOR_API SoBoxHighlightRenderAction : public SoGLRenderAction {
  
  SO_ACTION_HEADER(SoBoxHighlightRenderAction);
  
 public:
  /**
   * Constructor.
   */
  SoBoxHighlightRenderAction();
  
  /**
   * Constructor which takes the normal SoGLRenderAction parameters.
   */
  SoBoxHighlightRenderAction(const SbViewportRegion &viewportRegion);

#ifndef HIDDEN_FROM_DOC  
  /**
   * Destructor
   */
  virtual ~SoBoxHighlightRenderAction();
#endif // HIDDEN_FROM_DOC
  
  /**
   * This renders the passed scene graph, and also renders wireframe boxes around
   * selected objects as specified by the first SoSelection node found in the scene
   * graph.
   */
  virtual void apply(SoNode *node);
  
  /**
   * Applies action to the graph defined by a path.
   * It simply invokes the parent class apply() methods.
   * It does NOT highlight the path, whether selected or not.
   */
  virtual void apply(SoPath *path);
  /**
   * Applies action to the graph defined by a path list.
   * It simply invokes the parent class apply() methods.
   * It does NOT highlight the path, whether selected or not.
   */
  virtual void apply(const SoPathList &pathList,
                     SbBool obeysRules = FALSE);
  
  /**
   * This provides a convenient mechanism for turning highlights off or on. When
   * @B FALSE @b is passed, subsequent calls to apply() render the scene
   * graph without rendering highlights. The application is responsible for forcing a
   * redraw of the scene after changing this state. The default visibility is on.
   */
  void setVisible(SbBool b);

  /**
   * Returns whether highlights will be rendered or not.
   */
  SbBool isVisible() const { return hlVisible; }
  
  /**
   * Sets the color of the highlight. Default is red @B (1,0,0) @b.
   * Application is responsible for forcing a redraw of the scene to see the effects
   * of this change.
   */
  void setColor(const SbColor &c);
  /**
   * Gets the color of the highlight. 
   */
  const SbColor & getColor();
  /**
   * Sets the line pattern of the highlight. Default is solid, @B 0xffff @b.
   * The pattern of bits in the passed variable specifies the pattern of the line.
   * See SoDrawStyle for a description. Application is responsible for forcing a
   * redraw of the scene to see the effects of this change.
   */
  void setLinePattern(unsigned short pattern);
  /**
   * Gets the line pattern of the highlight.
   */
  unsigned short getLinePattern();
  /**
   * Sets the line width of the highlight. Default is @B 3 @b. Application is
   * responsible for forcing a redraw of the scene to see the effects of this change.
   */
  void setLineWidth(float width);
  /**
   * Gets the line width of the highlight.
   */
  float getLineWidth();

protected:
  
 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  SoSeparator* getLocalRoot();
  void setLocalRoot( SoSeparator* );

 private:
  
  // Nodes which comprise the local highlight graph
  SoSeparator *localRoot;

  SoSearchAction *searchAct;

  SbBool hlVisible;
  
  SoSelection* m_selectionNode;

 private:

  // Copy Constructor Forbidden
  SoBoxHighlightRenderAction( const SoBoxHighlightRenderAction& ) : SoGLRenderAction(SbVec2s(1, 1)) {}

  void constructorCommon();

  // track changes on selection node
  static void selectionChangedCB(void * userData, SoSelection* data);

  static void notificationCB(void* userData, SoSensor* sensor );

  // track selection node removal
  SoNodeSensor* m_selectionNodeSensor;
  static void selectionRemovedCB(void *data, SoSensor * sensor);

  bool updateBBoxSceneGraph(SoNode *renderRoot);

  SbViewportRegion *viewportPtr;

  static void viewportCallbackRoutine(void *userData, SoAction *action);

  // internal state var
  bool m_selectionChanged;

  SoNodeSensor* m_notificationNodeSensor;
};

inline SoSeparator*
SoBoxHighlightRenderAction::getLocalRoot()
{
  return localRoot;
}
#endif /* _SO_BOX_HIGHLIGHT_RENDER_ACTION_ */
