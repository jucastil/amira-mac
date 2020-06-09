/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : mmh                                                               * (MMM yyyy)
**=======================================================================*/

#ifndef _SO_CONTEXTED_OBJECT_CACHE_LIST_H_
#define _SO_CONTEXTED_OBJECT_CACHE_LIST_H_

//////////////////////////////////////////////////////////////////////////////
//
// SoContextedObjectCacheList
// This class has some similarities to SoGLCacheList, which manages render
// caches (OpenGL display lists), but is significantly different because:
//
// 1) Texture caches (OpenGL texture objects) only depend on the OpenGL render
//    context (identified by cachectxSharedId in Inventor) and texture quality.
//    Render caches depend on a large number of traversal state elements
//    (including cachectxSharedId).  In fact SoGLCacheList is able to maintain
//    multiple render caches (with different attribute settings) for the same
//    cachectxSharedId.  For texture caches we do not need this complexity, so
//    we only maintain a single texture cache for each cachectxSharedId.
//
// 2) Texture nodes already have a slightly complicated relationship with the
//    SoGLTextureImageElement, where the element creates the texture object,
//    but the node stores the address of the object for later re-use.
//    SoGLCacheList, on the other hand, is relatively self-contained. It is
//    responsible for creating, using and destroying render caches and looks
//    more like a "black box" to Separator (etc) nodes.  SoContextedObjectCacheList is
//    more of a "helper" class that does some bookkeeping for the client node.
//    It will generally be safer and more efficient for the client node to
//    lock its own mutex, but we have provided an optional internal mutex.
//
// 3) Texture caches are used in a different way than render caches. A "call"
//    of a render cache (glCallList) is a somewhat atomic operation. We must
//    ensure the display list continues to exist until glCallList returns,
//    but after that it could be destroyed.  A texture cache is put into the
//    traversal state and must continue to exist until its TextureImageElement
//    is popped off the stack.  We don't know what other geometry the texture
//    might apply to.  To ensure this happens safely with multiple threads we
//    modified TextureImageElement to ref and unref the texture object.
//
// The number of texture caches that are required depends on the number of
// graphics pipes that the application will use.  However, it specifically
// depends on the number of different cachectxSharedIds.  So if all the pipes
// can share texture objects, they can (and should) all use the same
// cachectxSharedId, and only one texture cache is required.  If the pipes
// cannot share texture objects (eg. on SGI hardware), then they should each
// use a different cachectxSharedId and the number of texture caches should be
// equal to or greater than the number of pipes.  The number of caches can be
// set for both render and texture caches using SoDB::setNumRenderCaches.
//
// There are two cases that should account for 99% of the usage:
//
// Case 1: Classic single pipe Open Inventor program
//
//    The effective behavior in this case should be the same as before.
//    Typically the program will only have one cachectxSharedId value (even
//    if it uses multiple Open Inventor windows), so only one texture cache
//    is needed.  If the texture quality changes, the texture node will create
//    a new texture object and call setCache, but the cachectxSharedId will be
//    the same so the existing entry will be re-used.
//
// Case 2: Multi-pipe Open Inventor program
//
//    Typically each pipe will have a different cachectxSharedId, but once
//    the pipes are set up, the cachectxSharedIds will remain the same until
//    the program exits.  There are should be as many texture caches as
//    there are pipes and each cachectxSharedId will have its own cache (and
//    its own texture object).  If the texture quality changes, the texture
//    node will create a new texture object and call setCache in each render
//    thread, but the cachectxSharedId is the same for each thread, so the
//    existing entry will be re-used.
//
// In the unlikely, but possible, case that there are more cachectxSharedId
// values than there are texture caches, the SoContextedObjectCacheList will choose
// an existing cache entry to "clobber".  This is based on a useCount to
// encourage clobbering the least used cache entry.  However it is likely
// that in this case the cache list will be "thrashing", clobbering and
// re-using the same cache entry over and over.  This is not good, but no
// worse than the behavior in the 3.0 (and older) code. :-)
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/SbBasic.h>
#include <Inventor/helpers/SbGlContextHelper.h>
#include <Inventor/caches/SoBaseContextCache.h>

class SoState;
class SoDeviceContext;
class SbThreadRWMutex;


template <typename TContextedObject>
SoINTERNAL class INVENTOR_API SoContextedObjectCacheList : public SoBaseContextCache
{
 public:
  // Constructor.
  // Takes the maximum number of caches to build and an
  // optional flag specifying to use internal mutex.
  // It is more efficient, and safer, for the client code
  // to lock its own mutex.
  SoContextedObjectCacheList(int numCaches = 1, bool sharable = true, SbBool useMutex = FALSE);

  /**
   * Stores info about a tex cache.
   * [OIV-WRAPPER-NO-WRAP]
   */
  typedef struct 
  {
    TContextedObject* texObj;
    SoDeviceContextSharedGroup* contextSharedGroup;
    float quality;
    double lastUse;
  } SoGLTexCacheEntry;

  // Get the texture object for the specified context id and quality.
  //
  // Returns NULL if there is no cache for the specified context id.
  // Even if there is a cache, the current texObj may be NULL.
  //
  // NOTE: This method does not ref or unref the texObj.
  //       It does increment the useCount if a cache was found.
  TContextedObject *getCache( SoState *state, float quality  );
  TContextedObject *getCache( SoDeviceContext* ctx, float quality  );

  // Set the values in the cache for the specified context id.
  // If there is a cache for this context id, its values are modified.
  // Else if there is an unused cache entry, it becomes the cache for
  // this context id and its values are modified.  Else the least
  // used cache entry (lowest useCount) is chosen and becomes the
  // cache for this context id.
  //
  // NOTE: The specified texObj will be ref'd and the current texObj
  //       in the cache entry (if any) will be unref'd. A valid
  //       SoState* should be passed if possible so texObjs can be
  //       destroyed immediately (more efficient).
  void setCache( int sharedGroup, TContextedObject *texObj,
                 float quality, SoState *state = NULL );

  void setCache( int sharedGroup, TContextedObject *texObj,
                 float quality, SoState *state, TContextedObject*& oldTexObj );

  // Specifies that all texture caches are invalid.
  // This method would be called, for example, if the texture quality
  // or the wrap/repeat setting changes.  Because there is a single
  // texture cache for each context id, the change invalidates all
  // the caches.
  //
  // NOTE: All texObj's will be unref'd.  A valid SoState* should be
  //       passed if possible so texObjs can be destroyed immediately.
  void invalidateAll( SoState *state = NULL );

  // Specifies that all texture caches are invalid for a specific context.
  // This method would be called, for example, if the texture quality
  // or the wrap/repeat setting changes.  Because there is a single
  // texture cache for each context id, the change invalidates all
  // the caches.
  //
  // NOTE: All texObj's will be unref'd.  A valid SoState* should be
  //       passed if possible so texObjs can be destroyed immediately.
  bool invalidateContext( SoDeviceContextSharedGroup* ctx);


 SoINTERNAL public:

  // Get the cache for the specified context id.
  // Returns NULL if there is no cache for the specified context id.
  // If there is a cache, the current texObj may be NULL.
  //
  // NOTE: This method does not ref or unref the texObj.
  //       It does increment the useCount if a cache was found.
  SoGLTexCacheEntry *getCache( SoState *state);


  /**
   * This function is called when a context has been requested 
   * to be deleted through the SoDeviceContext::dispose() method.
   * As some object might be still attached, it triggers all attached object
   * release() method to ask them to detach (and then get its refcount to zero).
   */
  virtual void release(SoDeviceContextSharedGroup *ctx);

protected:

  /** Destructor. */
  virtual ~SoContextedObjectCacheList();

  /**
   * called by unref before calling destructor
   * return false if there is still some context dependent object 
   * and then delete should not be called
   */
  virtual bool notifyDelete();

 private:

  SoGLTexCacheEntry* m_cacheList;
  int                m_numCaches;
  SbThreadMutex*     m_mutex;

  /** True if the object can be shared between context */
  bool m_sharable;

  static int s_debugFlag;
};

#endif //_SO_CONTEXTED_OBJECT_CACHE_LIST_H_
