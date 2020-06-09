/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_CACHE_CONTEXT_ELEMENT
#define  _SO_CACHE_CONTEXT_ELEMENT

#include <Inventor/oglObjects/SoGLDisplayList.h>
#include <Inventor/elements/SoSubElement.h>
#include <Inventor/helpers/SbGlContextHelper.h>
#include <Inventor/threads/SbThreadMutex.h>

class SbIntList;

/**
 *
 *  Class: SoCacheContextElement
 *
 *  Element that stores the cache context.  There is a method on the
 *  render action to set this; if you are not rendering onto multiple
 *  displays, you will not need to set this (assuming that caches are
 *  shareable between different windows on the same display, which is
 *  true of GLX).
 *
 *  This element should be set before traversal starts, and must not
 *  be changed during traversal (you'll get a debug error if a node
 *  tries to set the cache context during traversal).
 *
 *  This method also has API for quickly finding out whether or not
 *  OpenGL extensions are supported.  Code that uses extension "foo"
 *  should look something like:
 *  @code
 *  #ifdef GL_EXT_foo
 *      static int fooExtInt = -1;
 *      if (fooExtInt == -1)
 *          fooExtInt = SoGLCacheContextElement::getExtID("GL_EXT_foo");
 *      if (SoGLCacheContextElement::extSupported(state, fooExtInt)) {
 *          glFoo(... make extension foo calls...);
 *      } else {
 *  #endif
 *          Extension not supported, make regular GL calls
 *  #ifdef GL_EXT_foo
 *      }
 *  #endif
 *  @endcode
 *
 *  Arranging the code that way ensures that it both compiles on
 *  systems that don't support the extension AND will run on any
 *  OpenGL-capable machine, even if the application displays on
 *  multiple displays (only some of which may support the extension).
 *
 */

SoEXTENDER class INVENTOR_API SoGLCacheContextElement : public SoElement {

  SO_ELEMENT_HEADER(SoGLCacheContextElement);

 public:
  /** Initializes element */
  virtual void        init(SoState *state);

  /**
   * Sets the current context.  This is done by the renderAction;
   * theoretically, a node that redirected the GL rendering context
   * to another X server would also set this.  This also frees up
   * any display lists that are waiting for the context to become
   * valid. The third argument indicates whether 2-pass
   * transparency is in effect (as for DELAYED or SORTED blending),
   * which means that caches containing transparent objects may not
   * be valid.  The fourth argument should be TRUE if remote
   * rendering is being done; the SoSeparator auto-caching algorithm
   * uses this information to help decide whether or not to build
   * caches.
   */
  static void         set(SoState *state, int context,
                          SbBool is2PassTransparency,
                          SbBool isRemoteRendering);

  /** Gets the current context */
  static int          get(SoState *state);

  /**
   * Methods to quickly figure out if an OpenGL extension is
   * available at run-time.
   * This is the slow routine-- convert from a string to an integer.
   * The integer should be saved to do quick lookups:
   */
  static int          getExtID(const char *str);

  /** This routine is pretty quick. */
  static SbBool       extSupported(SoState *state, int ext);

  /** TRUE if mip-mapped textures are known to be fast */
  static SbBool       areMipMapsFast(SoState *state);

  /** TRUE if we think GL_COMPILE is faster than GL_COMPILE_AND_EXECUTE */
  static SbBool       isCompileModeFaster( SoState *state );

  //
  // Methods used to improve auto-caching algorithm:
  //

  /**
   * Two bits are stored.  Nodes that should be cached will set the
   * DO_AUTO_CACHE bit, nodes that should NOT be cached will set the
   * DONT_AUTO_CACHE bit.  By default, DO_AUTO_CACHE is FALSE unless
   * remote rendering is being done.  DONT_AUTO_CACHE is FALSE by
   * default.  Separators will auto cache if DO_AUTO_CACHE is TRUE
   * and DONT_AUTO_CACHE is FALSE, otherwise they won't auto-cache.
   */
  enum AutoCacheMode{
    DO_AUTO_CACHE = 1,
    DONT_AUTO_CACHE = 2
  };

  /**
   * Called by nodes to say that they should/shouldn't be
   * auto-cached (pass TRUE if should, FALSE if shouldn't, don't
   * call this method at all if the node doesn't care):
   */
  static void shouldAutoCache(SoState* state, AutoCacheMode mode);

  /**
   * Called by nodes to say that they should/shouldn't be
   * auto-cached (pass TRUE if should, FALSE if shouldn't, don't
   * call this method at all if the node doesn't care):
   */
  static void shouldAutoCache(SoState *state, int bits);

  /** Used by Separators to set/reset the auto-caching bits. */
  static void setAutoCacheBits(SoState *state, int bits);

  /** Used by Separators to set/reset the auto-caching bits. */
  static int resetAutoCacheBits(SoState *state);

  static SbBool getIsRemoteRendering(SoState *state);

  //
  // Standard element stuff:
  //

  /** Returns TRUE if the widths match in both elements */
  virtual SbBool      matches(const SoElement *elt) const;

  /** Create and return a copy of this element */
  virtual SoElement   *copyMatchInfo() const;

  /** Prints element (for debugging) */
  virtual void        print(FILE *fp) const;

 SoINTERNAL public:
  /** register element in database */
  static void         initClass();
  /** unregister element from database */
  static void         exitClass();
  /** delete GL resources still attached to this context */
  static void         deleteContextResources(int ctxSharedId);

  /** Gets the current context */
  static SbGlContextHelper::GLContext getGlContext(SoState *state);

  /** Return an uniq id for the current context */
  static int getUniqId(SoState *state);

 protected:
  SbGlContextHelper::GLContext m_contextGL;
  int                 m_sharedGroup;
  SbBool              is2PassTransp;
  SbBool              isRemoteRendering;
  int                 autoCacheBits;

  /** Destructor */
  virtual ~SoGLCacheContextElement();

 private:
  // Frees up the given display lists right away, if possible.  If
  // not possible (because the state passed in is NULL or has a
  // different cache context than the display lists' state), this
  // adds the given display list/count to the list of display lists
  // that need to be freed the next time the given context is valid.
  // This method is necessary because nodes with caches can be
  // deleted at any time, but we can't necessarily send GL commands
  // to free up a display list at any time.
  static void freeList(SoState *state, SoGLDisplayList *list);

  static SbPList*   waitingToBeFreed;       // Allocated in ::init
  static SbIntList* mipmapSupportList;      // Allocated in ::init

  // listMutex is a mutex to protect the access to waitingToBeFreed.
  static SbThreadMutex listMutex;

  friend class SoGLDisplayList;

};
#endif /* _SO_CACHE_CONTEXT_ELEMENT */
