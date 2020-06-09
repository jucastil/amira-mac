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



#ifndef  _SO_GL_CACHE_LIST
#define  _SO_GL_CACHE_LIST

#include <Inventor/SbBasic.h>
#include <Inventor/SbString.h>


struct SoGLCacheListEntry;
class SoGLRenderAction;
class SoState;
class SoElement;
class SoNode;

#include <Inventor/threads/SbThread.h>
#include <Inventor/threads/SbThreadRWMutex.h>

SoEXTENDER class INVENTOR_API SoGLCacheList {
    
 public:
  // Constructor.  Takes the maximum number of caches to build.
  SoGLCacheList(int numCaches = 2);

  // Destructor.
  ~SoGLCacheList();
    
  // Given an SoGLRenderAction, try to use one of the caches we've
  // built.  If none of the caches can be used, this returns FALSE.
  // If this returns TRUE, then a cache has been called and all the
  // GL commands in it have already been done.
  SbBool call(SoGLRenderAction *);
    
  // Open a new cache, maybe.  If the autoCache flag is TRUE, a
  // heuristic will be used to figure out whether or not caching
  // should be done (based on when caches were built, when they were
  // used, etc).  If the flag is FALSE, always try to open a cache
  // (and possibly delete an old cache).
  // Returns TRUE if a cache was actually opened. -mmh Mar-01
  SbBool open(SoGLRenderAction *, SbBool autoCache = TRUE);

  // Close an open cache, if any.  If open() didn't open a cache,
  // this routine does nothing.
  // Returns FALSE if the cache list cannot be closed properly.
  bool close(SoGLRenderAction* );
    
  // Mark all caches as invalid.  This should be called when a node
  // is notified of changes in its children or fields.
  void invalidateAll();
  
  void unref() { delete this; }

 private:
  SoGLCacheListEntry *getLRU();
  void setMRU(SoGLCacheListEntry *e);
  void setLRU(SoGLCacheListEntry *e);
  void blow(SoState *, SoGLCacheListEntry *);

  // MRU is the head of a looped list of caches.  Every time
  // a cache is used, it is added to the front of the list.  When we
  // decide to replace a cache, the end cache on the list is used.
  SoGLCacheListEntry *MRU;
  int maxCaches, numCaches;
  SoGLCacheListEntry *openCache;
  int threshold;      // Number of frames to wait before trying to
  // build a cache.  This is increased when caches
  // are found to be invalid, and decreased when a
  // cache is successfully used.
  int mightBeUsed;    // When we can't use a cache, this counts the
  // number of times open() is called and we
  // think we might have been able to use a cache, if
  // there was one built.  The bigger this gets,
  // the more likely we are to use a cache.
  SoElement *invalidElement;
  // This is the element that caused the most
  // recently used cache to be considered
  // invalid.  If it doesn't change, a cache
  // will be built (if it does continue to
  // change, we'll avoid building a cache).
  SbBool saveInvalid; // Used to remember whether or not a node
  // called SoCacheElement::invalidate() between
  // open() and close().  This scheme assumes
  // that nodes won't apply() another action
  // that uses the CacheElement during
  // rendering (that would screw up caching
  // anyway, so that is a good assumption).
  int saveACacheBits; // At cache->open() time we get these from the
  // SoGLCacheContextElement, clear them before
  // traversing children, and reset them at
  // cache->close() time.

  SbThreadRWMutex  m_mutex;
  SbThreadId_t     openCacheThreadId;
  SoNode          *node;
  SbName           name;

  // Traditionally the initial (and minimum) threshold was 1.
  // When multiple render threads are used, initial threshold
  // depends on the number of render threads.
  int              initialThreshold;

  // How should display lists be created?
  int              renderCacheMode;
};


#endif /* _SO_GL_CACHE_LIST */
