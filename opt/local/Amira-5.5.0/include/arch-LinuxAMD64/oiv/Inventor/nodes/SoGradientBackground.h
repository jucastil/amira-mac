/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
/**
 * Gradient background node
 * 
 * @ingroup BackgroundNodes
 * 
 * @DESCRIPTION
 *  Draws a color gradient background.
 *
 *  This node provides a convenient way of drawing a color
 *  gradient background for a scene. The first color (color0)
 *  appears at the bottom of the window and the second color
 *  (color1) appears at the top of the window. Rendering
 *  of the gradient is automatically recalculated if the window
 *  size changes.
 *
 *  Generally background nodes should be placed at the
 *  beginning of the scene graph so that geometry is drawn on
 *  top of the background. Background nodes have no size, are
 *  not pickable, and do not modify the OpenGL depth buffer.
 *
 *  Another convenient feature is that this node renders
 *  correctly on a tiled display that represents a single large
 *  virtual window, for example using the MultiPipe extension
 *  (see SoXtMPExaminerViewer). The gradient will be interpolated
 *  smoothly across the entire virtual window.
 * 
 * @FILE_FORMAT_DEFAULT
 *    GradientBackground {
 *    @TABLE_FILE_FORMAT
 *       @TR color0          @TD 0.7 0.7 0.8
 *       @TR color1          @TD 0.0 0.1 0.3
 *       @TR swapColors      @TD FALSE
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Renders background, does not affect state.
 * 
 * @SEE_ALSO
 *    SoBackground,
 *    SoImageBackground
 * 
 * 
 */ 

#ifndef _SO_GRADIENT_BACKGROUND_H_
#define _SO_GRADIENT_BACKGROUND_H_

#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFBool.h>

#include <Inventor/nodes/SoBackground.h>

class INVENTOR_API SoGradientBackground : public SoBackground {

   SO_NODE_HEADER(SoGradientBackground);

 public:
   // Fields:
   // 
  /**
   * First color in gradient (0.7 0.7 0.8 by default).
   * This color appears at the bottom of the window
   * (unless the swapColors field is TRUE).
   */
   SoSFColor    color0;
  /**
   * Second color in gradient (0.0 0.1 0.3 by default).
   * This color appears at the top of the
   * window (unless the swapColors field is TRUE).
   */
   SoSFColor    color1;
  /**
   * Reverse colors (default is FALSE).
   */
   SoSFBool     swapColors;

  /**
   * Creates a background gradient node with default settings.
   */
   SoGradientBackground();

 SoINTERNAL public:
   // Initializes this class for use in scene graphs. This
   // should be called after database initialization and before
   // any instance of this node is constructed.
   static void    initClass();
   static void    exitClass();

 SoEXTENDER public:
   // Implement render action
   // We will inherit all other action methods from SoNode.
   // We don't need a doAction because this node has no effect
   // on traversal state (or at least it shouldn't :-).
   virtual void   GLRender(SoGLRenderAction *action);

 protected:
   // Destructor. Protected to keep people from trying to delete
   // nodes, rather than using the reference count mechanism.
   virtual ~SoGradientBackground();

   // Interpolate between two colors
   const SbColor interpColor( float t, SbColor &c0, SbColor &c1 ) const;

 private:
};

#endif //SoGradientBackground

