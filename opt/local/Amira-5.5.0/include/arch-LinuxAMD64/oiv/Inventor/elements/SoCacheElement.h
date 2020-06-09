/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_CACHE_ELEMENT_
#define  _SO_CACHE_ELEMENT_

#include <Inventor/SbBasic.h>
#include <Inventor/elements/SoSubElement.h>
#include <Inventor/threads/SbThreadLocalStorage.h>

class SoCache;

/**
*   Stores the most recently opened cache.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the most recently opened cache.
*   @SEE_ALSO
*   SoSeparator, SoRenderList, SoVRMLCollision, SoVRMLGroup,
*   SoVRMLShape, SoVRMLStaticGroup
*/

SoEXTENDER_Documented class INVENTOR_API SoCacheElement : public SoElement {

  SO_ELEMENT_HEADER(SoCacheElement);

 public:
  /**
  *  Sets cache in element accessed from state.
  */
  static void         set(SoState *state, SoCache *cache);

  /**
  *  Returns the cache stored in an instance. This may be NULL.
  */
  SoCache *           getCache() const { return cache; }

  /**
  *  Returns TRUE if any cache is currently open in the state.
  */
  static SbBool       anyOpen(SoState *state);

  /**
  *  Closes any open cache.
  */
  static void         closeAnyOpen(SoState* state);

  /**
  *  Invalidate any open caches.  This is called by nodes that
  *  should not be cached.
  */
  static void         invalidate(SoState *state);

  /**
  *  Overrides this method to unref cache.
  */
  virtual void        pop(SoState *state, const SoElement *prevTopElement);

  /**
  *  Overrides this method to print an error message and return
  *  FALSE. Cache elements should never be compared, since they
  *  never appear in the elements-used list of caches!
  */
  virtual SbBool      matches(const SoElement *elt) const;

  /**
  *  Copy method prints error and returns NULL; see comment above.
  */
  virtual SoElement   *copyMatchInfo() const;

  /**
  *  Returns the next cache element in the stack.
  */
  SoCacheElement *    getNextCacheElement() const
    { return (SoCacheElement *) getNextInStack(); }

 SoINTERNAL public:
  // Initializes the SoCacheElement class
  static void initClass();
  static void exitClass();

  // Initializes element
  virtual void        init(SoState *state);

  // Adds the given element to the elements used lists of all
  // currently open caches in the state
  static void         addElement(SoState *state, const SoElement *elt);

  // Adds a dependency on the given cache to all currently open
  // caches in the state
  static void         addCacheDependency(SoState *state, SoCache *cache);

  // Sets invalidated bit, and returns its old value.  Used by
  // SoGLCacheList so auto-caching doesn't cache too much.
  static SbBool       setInvalid(SbBool newValue);

  // returns the current cache, from the top of the stack.  Does not
  // cause a cache dependence like getConstElement().
  static SoCache *    getCurrentCache(SoState *state)
  {return state->getElementNoPush<SoCacheElement>()->cache;}

  struct MTstruct
  {
    bool invalidated;
  };

  SB_THREAD_TLS_HEADER();

 protected:
  virtual ~SoCacheElement();

 private:
  SoCache* cache; // Stores pointer to cache

  friend class SoElement;
};

#endif /* _SO_CACHE_ELEMENT_ */
