/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_CACHE
#define  _SO_CACHE

////////////////////////////////////////////////////////////////////////
//
//  Class SoCache:
//
//  This is the base class for all types of caches. Each cache
//  maintains the following information:
//
//      A reference count, used to allow sharing of cache instances.
//      ref() and unref() methods increment and decrement the count.
//
//      An elements-used list. This is a list of elements used in the
//      cache that are set outside it. A cache is invalidated if any
//      of these elements has changed since the cache was created.
//      There is also an elements-flag array so we can quickly tell if
//      an element type has already been added to the elements-used
//      list.
//
////////////////////////////////////////////////////////////////////////

#include <Inventor/SoLists.h>
#include <Inventor/SoTypedObject.h>
#include <Inventor/caches/SoBaseContextCache.h>

class SoElement;
class SoState;

SoEXTENDER class INVENTOR_API SoCache : public SoBaseContextCache, public SoTypedObject
{

 public:

  /**
   * Constructor. Takes the state in effect when the cache is used;
   * it is assumed that the state is pushed before the cache is
   * created.
   */
  SoCache(SoState *state);

  /**
   * Adds an element to elements-used list if not already there
   */
  void addElement(const SoElement *elt);

  /**
   * Adds a dependency of this instance on another cache instance.
   * The default method takes care of adding dependencies from the
   * child cache.
   */
  virtual void addCacheDependency(const SoState *state, SoCache *cache);

  /**
   * Returns TRUE if cache is valid with respect to the given state
   */
  virtual SbBool isValid(const SoState *state) const;

#ifndef HIDDEN_FROM_DOC
  /** kept from 7.2, only for .NET binary compatibility issues */
  virtual SbBool      isValid(const SoState *state, SbBool /*applyIgnored*/) const
  { return isValid(state); }
#endif // HIDDEN_FROM_DOC


  /**
   * Assuming isValid() returns FALSE, this will return the first
   * element that is invalid (auto-caching uses this in its
   * heuristic).  Returns NULL if the cache is not invalid because
   * of an element or if the cache is valid.
   */
  const SoElement* getInvalidElement(const SoState *state) const;

  /**
   * Return is the given element is valid
   * True if the element is not monitored
   */
  virtual SbBool isValid(const SoState* state, const SoElement* elf) const;

  /**
   * Make this cache invalid
   */
  void invalidate();

#ifndef HIDDEN_FROM_DOC
  /** kept from 7.2, only for .NET binary compatibility issues */
  void addIgnoredElement(const SoElement* ) {}
#endif // HIDDEN_FROM_DOC

  /**
   * return the class type.
   */
  static SoType getClassTypeId();

  /**
   * Returns type id.
   */
  virtual SoType getTypeId() const;

 SoINTERNAL public:
  /**
   * register class.
   */
  static void initClass();

  /**
   * Unregister class.
   */
  static void exitClass();

  /**
   * This function is called by when a context has been requested
   * to delete the context through the SoDeviceContext::dispose() method.
   * As some object might be still attached, it triggers all attached object
   * release() method to ask them to detach (and then get it refcount to zero).
   */
  virtual void release(SoDeviceContextSharedGroup *ctx);


  static bool isDebuggingCache()
  { return s_debugCaches; }

  static bool isDebuggingCache2()
  { return s_debugCaches2; }

 protected:

   /**
    * called by unref before calling destructor
    * if it returns false then it means that delete should not be called
    * as some object were not freed because of context dependency.
    * (used by RenderCache for example)
    */
   virtual bool notifyDelete()
   { return true; };

  /**
   * Destructor.
   * called by unref() if notifyDelete returned true.
   * else will be called through Dispose call
   */
  virtual ~SoCache();

  // Class type
  static SoType m_classTypeId;

 private:
  SbPList             m_elementsUsed;           // Elements used in cache
  unsigned char       *m_elementsUsedFlags;     // Which elements on list

  bool                m_invalidated;            // True if invalidate called
  int                 m_depth;                  // Depth of state

  // handle internal IV_DEBUG_CACHES and IV_DEBUG_CACHES2 debug env vars status
  static bool s_debugCaches;
  static bool s_debugCaches2;
};

#endif /* _SO_CACHE */
