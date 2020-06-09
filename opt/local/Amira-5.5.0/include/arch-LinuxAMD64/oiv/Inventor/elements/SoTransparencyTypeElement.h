/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas Daguise (Dec 2003)
**=======================================================================*/

#ifndef  _SO_TRANSPARENCY_TYPE_ELEMENT
#define  _SO_TRANSPARENCY_TYPE_ELEMENT

#include <Inventor/elements/SoInt32Element.h>
#include <Inventor/threads/SbThreadLocalStorage.h>

/**
 * @VSGEXT Stores the current transparency type.
 *
 * @ingroup elements
 *
 * @DESCRIPTION
 * This element stores the current transparency type.
 *
 * @SEE_ALSO
 * SoTransparencyType, SoGLRenderAction
 *
 */

SoEXTENDER_Documented class INVENTOR_API SoTransparencyTypeElement : public SoInt32Element {

  SO_ELEMENT_HEADER(SoTransparencyTypeElement);

 public: 
    /** TransparencyType */
  enum TransparencyType {
    /**
     *  Uses stipple patterns for screen-door transparency
     */
    SCREEN_DOOR,

    /**
     *  Uses additive alpha blending
     */
    ADD,

    /**
     *  Uses additive blending, rendering all transparent objects after opaque ones
     */
    DELAYED_ADD,

    /**
     *  Uses multiplicative alpha blending
     */
    BLEND,

    /**
     *  Uses multiplicative alpha blending, rendering all transparent objects after
     * opaque ones
     */
    DELAYED_BLEND,

    /**
     * Same as DELAYED_ADD, but sorts transparent objects by distances of bounding
     * boxes from camera
     */
    SORTED_OBJECT_ADD,

    /**
     * Same as DELAYED_BLEND, but sorts transparent objects by distances of bounding
     * boxes from camera
     */
    SORTED_OBJECT_BLEND,

    /**
     * Uses a fragment-level depth sorting technique. This gives better results
     * for complex transparent objects.
     * @B Multi-Texture@b, @B Texture Environment Combine@b, @B Depth texture@b,
     * and @B Shadow @b OpenGL extensions
     * must be supported by your graphics board.
     * All these extensions are standard with OpenGL 1.4.
     * If the graphics board does not support these extensions,
     * behaves as if SORTED_OBJECT_BLEND was set. @BR
     * The method setSortedLayersNumPasses() allows you to set the number of
     * rendering passes for more correct transparency. Usually, four passes
     * gives good results.
     * 
     * Limitations:
     *  - This transparency type is not compatible with VolumeViz nodes
     *  - This transparency type is not compatible with interlaced stereo.
     *  - Texturing on transparent objects is limited to one texture and to MODULATE mode
     */
    SORTED_LAYERS_BLEND,

    /**
     * Same as SORTED_LAYERS_BLEND but rendering all transparent objects after opaque ones.
     */
    DELAYED_SORTED_LAYERS_BLEND,

    /**
     * Renders all the transparent triangles of the scene using additive blending.
     * All of the transparent triangles of all objects of the scene are collected,
     * and then sorted by triangle position.
     */
    SORTED_TRIANGLES_ADD,

    /**
     * Same as SORTED_TRIANGLES_ADD, but uses multiplicative alpha blending.
     */
    SORTED_TRIANGLES_BLEND,

    /**
     * Renders all the transparent triangles of the scene using additive blending.
     * All of the triangles of all transparent objects of the scene are
     * collected and then sorted by object.
     */
    SORTED_OBJECT_TRIANGLES_ADD,

    /**
     * Same as SORTED_OBJECT_TRIANGLES_ADD, but uses multiplicative alpha blending.
     */
    SORTED_OBJECT_TRIANGLES_BLEND

  };

  /**
   * Sets the current draw style in the state.
   */
  static void set(SoState *state, TransparencyType type);

#ifndef IV_STRICT
  /**
   * Sets the current draw style in the state.
   */
  static void set(SoState *state, SoNode *, TransparencyType type);
#endif

  /**
   * Returns current draw style from the state.
   */
  static TransparencyType get(SoState *state);

  /**
   * Returns the default draw style.
   */
  static TransparencyType getDefault();

  /**
   * Prints element (for debugging).
   */
  virtual void print(FILE *fp) const;

 SoINTERNAL public:
  /** register in database */
  static void initClass();

  /** unregister from database */
  static void exitClass();

  /** Initializes element. */
  virtual void init(SoState *state);

  static void setSmooth(const SbBool smooth);
  static SbBool isSmoothing();

  static void setSmoothingChanged(const SbBool smooth);
  static SbBool isSmoothingChanged();

  /** register TLS */
  SB_THREAD_TLS_HEADER();

 protected:
  virtual ~SoTransparencyTypeElement();

  /** TLS struct declaration **/
  static SbThreadMutex s_classMutex;
  struct MTstruct
  {
    SbBool doSmooth;
    SbBool smoothingChanged;
  };
};

#endif // _SO_TRANSPARENCY_TYPE_ELEMENT

/**/
