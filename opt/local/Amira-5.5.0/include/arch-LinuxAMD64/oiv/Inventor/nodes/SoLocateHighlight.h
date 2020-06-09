/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Alain Dumesny (MMM yyyy)
** Modified by : Paul Isaacs (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_LOCATE_HIGHLIGHT_
#define  _SO_LOCATE_HIGHLIGHT_

#include <Inventor/helpers/SbGlContextHelper.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/sys/SoGLType.h>

class SoAction;
class SoHandleEventAction;
class SoGLRenderAction;
class SoFullPath;
class SoColorPacker;


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoLocateHighlight
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Special separator that performs locate highlighting.
 * 
 * @ingroup GroupNodes
 * 
 * @DESCRIPTION
 *   This is a subclass of SoSeparator that redraws itself in a different color when
 *   the cursor is over the contents of the separator.
 *   
 *   The redraw happens for that separator only and not the entire window (redraw
 *   along the handle event pick path) and in the front buffer, to efficiently track
 *   the mouse motion. The highlighted redraw overrides the emissive and/or diffuse
 *   color of the subgraph based on the field values in this node.
 *   
 *   NOTE: when using SoLightModel::BASE_COLOR (to turn lighting off) only the diffuse
 *   color will be used to render objects, so EMISSIVE_DIFFUSE must be used for this
 *   node to have any effect.
 *   
 *   To override the default mode (off), set environment variable
 *   IV_ALLOW_LOCATE_HIGHLIGHT to 1. This will allow locate highlighting to happen by
 *   default.
 * 
 * @FILE_FORMAT_DEFAULT
 *    LocateHighlight {
 *    @TABLE_FILE_FORMAT
 *       @TR renderCaching        @TD AUTO
 *       @TR boundingBoxCaching   @TD AUTO
 *       @TR renderCulling        @TD AUTO
 *       @TR pickCulling          @TD AUTO
 *       @TR mode                 @TD OFF
 *       @TR style                @TD EMISSIVE
 *       @TR color                @TD 0.3 0.3 0.3
 *       @TR fastEditing          @TD DISABLE
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoHandleEventAction @BR
 *        Checks to see if the cursor moves onto or off of the contents of the separator,
 *        and redraws appropriately (if #mode is AUTO), otherwise traverses as a
 *        normal separator.
 * 
 *    SoGLRenderAction @BR
 *        Redraws either highlighted (if cursor is over the contents of the separator
 *        when #mode == AUTO or always if #mode == ON), otherwise traverses as
 *        a normal separator.
 * 
 * 
 * @SEE_ALSO
 *    SoSeparator,
 *    SoSelection,
 *    SoMaterial
 * 
 * 
 */ 

class INVENTOR_API SoLocateHighlight : public SoSeparator {

  SO_NODE_HEADER(SoLocateHighlight);

 public:

   /** Possible values for draw style */
  enum Styles {
    /**
     *  Changes emissive color only (default) 
     */
    EMISSIVE,
    /**
     *  Changes emissive and diffuse colors 
     */
    EMISSIVE_DIFFUSE
  };

  /** Possible values for the mode */
  enum Modes {
    /**
     *  Highlight when mouse is over 
     */
    AUTO,
    /**
     *  Always highlight 
     */
    ON,
    /**
     *  Never highlight (default) 
     */
    OFF
  };

  // Fields
  /**
   * Highlighting color - default [.3, .3, .3]
   * 
   */
  SoSFColor   color;
  /**
   * Highlighting draw style - default EMISSIVE.
   * Use enum #Styles.
   */
  SoSFEnum    style;
  /**
   * Whether to highlight or not - default OFF.
   * Use enum #Modes.
   */
  SoSFEnum    mode;

  /**
   * Creates a LocateHighlight node with default settings.
   */
  SoLocateHighlight();

 SoEXTENDER public:
  // Override handleEvent to look for mouse motion, to do a
  // pick and highlight if mouse is over us. The GLRender methods
  // are redefined to draw highlighted if needed.
  virtual void        handleEvent( SoHandleEventAction *action );
  virtual void        GLRenderBelowPath(SoGLRenderAction *action);
  virtual void        GLRenderInPath(SoGLRenderAction *action);

 SoINTERNAL public:
  static void         initClass();    // initialize the class
  static void         exitClass();    // exit the class

  SB_THREAD_TLS_HEADER();

  // This will de-highlight the currently highlighted node if any.
  // this should be called when the cursor leaves a window or a mode
  // changes happen which would prevent a highlighted node from receiving
  // more mouse motion events. The GL render action used to render into
  // that window needs to be passed to correctly un-highlight.
  /** [OIV-WRAPPER VISIBILITY{Public}] */
  static void         turnOffCurrentHighlight(SoGLRenderAction *action);

 protected:
  virtual ~SoLocateHighlight();
    
  // This is called when this nodes needs to highlight or de-highlight. It
  // can be used by subclasses to be told when the status change.
  virtual void        redrawHighlighted(SoAction *act, SbBool flag);
    
 private:
  
#if defined(_WIN32)
  struct MTstruct { 
    // highlighting stuff
    // The following info is saved when we draw a node highlighted.
    // VSG added the window, context, etc so we can unhighlight the
    // node in the same window where it was highlighted (previously
    // it unhighlighted the node in the current window which could
    // be completely different!).                   -- mmh March-00
    SoFullPath       *currentHighlightPath;
    void             *currentWindow;
    void             *currentContext;
    void             *currentDisplay;
    SoGLRenderAction *currentAction;
  };
#elif defined(__APPLE__)
  struct MTstruct {
       // highlighting stuff
       // The following info is saved when we draw a node highlighted.
       // VSG added the window, context, etc so we can unhighlight the
       // node in the same window where it was highlighted (previously
       // it unhighlighted the node in the current window which could
       // be completely different!).                   -- mmh March-00
       SoFullPath       *currentHighlightPath;
       SbGlContextHelper::Drawable  currentWindow;
       SbGlContextHelper::GLContext currentContext;
       SbGlContextHelper::Display   currentDisplay;
       SoGLRenderAction *currentAction;
     };
#else
   struct MTstruct {
     // highlighting stuff
     // The following info is saved when we draw a node highlighted.
     // VSG added the window, context, etc so we can unhighlight the
     // node in the same window where it was highlighted (previously
     // it unhighlighted the node in the current window which could
     // be completely different!).                   -- mmh March-00
     SoFullPath       *currentHighlightPath;
     Window            currentWindow;
     SbGlContextHelper::GLContext currentContext;
     SbGlContextHelper::Display   currentDisplay;
     SoGLRenderAction *currentAction;
   };
#endif

  SbBool              highlightingPass;
  SbBool              isHighlighted(SoAction *action);
  SbBool              preRender(SoGLRenderAction *act, GLint &oldDepthFunc);
  SoColorPacker       *colorPacker;
  SbBool              m_redrawAll;
};


#endif /* _SO_LOCATE_HIGHLIGHT_ */

