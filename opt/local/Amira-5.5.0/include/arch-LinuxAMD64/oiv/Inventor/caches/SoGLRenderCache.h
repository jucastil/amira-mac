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



#ifndef  _SO_GL_RENDER_CACHE
#define  _SO_GL_RENDER_CACHE

#include <Inventor/caches/SoCache.h>
#include <Inventor/elements/SoGLLazyElement.h>

class SoGLDisplayList;
class SoGLCacheList;

////////////////////////////////////////////////////////////////////////
//
//  Class SoGLRenderCache:
//
//  A render cache stores a GL display list containing commands that
//  draw a representation of the shape(s) represented by the cache.
//  The display list id is stored in the cache instance.
//
//  Each instance has a list of all nested display lists
//  that it calls. This list maintains reference counts on the
//  instances within it.
//  
//  This version has a copy of SoGLLazyElement, which is handled differently
//  than other elements.
//
////////////////////////////////////////////////////////////////////////


SoEXTENDER class INVENTOR_API SoGLRenderCache : public SoCache {

 public:
  // Constructor and destructor
  SoGLRenderCache(SoState *state, SoGLCacheList* cList);
  virtual ~SoGLRenderCache();

  // Maintain list of cache dependencies.  If one cache calls
  // another inside of it, we have to make sure that the inner cache
  // isn't deleted before the outer one.
  virtual void        addNestedCache(SoGLDisplayList *child);

  // Opens/closes the cache. All GL commands made between an open()
  // and a close() will be part of the the display list cache.
  // Calling open automatically sets SoCacheElement.
  void                open(SoState *state);
  bool                close();

  // Calls the cache. The display list will be sent to GL.  This
  // automatically calls addCacheDependency on any open cache.
  void                call(SoState *state);

  // Returns TRUE if cache is valid with respect to the given state
  // The GL version tests for GL Enable flags, first.
  virtual SbBool      isValid(const SoState *state) const;
 
  // method for the lazy element to set flags:
  void setLazyBits(uint32_t ivFlag, uint32_t glFlag, uint32_t sendFlag)
  {
    m_checkGLFlag |= glFlag;
    m_checkIVFlag |= ivFlag;
    m_doSendFlag |= sendFlag;
  }
        
  SoGLLazyElement* getLazyElt() const
    {return m_GLCacheLazyElement;}

  // Whether display list is open
  SbBool isListOpened() const
  {return m_listOpen; }

  // Set whether to use GL_COMPILE or GL_COMPILE_AND_EXECUTE
  void   setCompileAndExecute( SbBool flag )
  { m_useCompileAndExecute = flag; }

  SbBool isCompileAndExecute() 
  { return m_useCompileAndExecute; }

  inline SoGLCacheList* getGLCacheList() 
  { return m_cList; };

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
   * Register class.
   */
  static void initClass();

  /**
   * unregister class.
   */
  static void exitClass();

  /**
   * This function is called by when a context has been requested 
   * to delete the context through the SoDeviceContext::dispose() method.
   * As some object might be still attached, it triggers all attached object
   * release() method to ask them to detach (and then get it refcount to zero).
   */
  virtual void release(SoDeviceContextSharedGroup *ctx);

 protected:
   /**
    * called by unref before calling destructor 
    * if it returns false then it means that delete should not be called
    * as some object were not freed because of context dependency.
    */
   virtual bool notifyDelete();

  // class type
  static SoType m_classTypeId;

 private:
  bool                m_listOpen;
  SoGLDisplayList     *m_list;          // Display list structure
  SbPList             m_nestedCaches;   // List of nested render caches
  SbPList             m_nestedDisplayLists; // List of nested display lists
  // Save state that opened a cache, to use when it is closed:
  SoState *           m_saveState;

  // Keep a copy of SoGLLazyElement for comparison
  SoGLLazyElement*    m_GLCacheLazyElement;
    
  // Keep a copy of the GL state for copying back after cache call:
  SoGLLazyElement::GLLazyState m_cachedGLState;

  // BitFlags for maintaining Lazy Element:
  // indicates that GL must match for cache to be valid
  uint32_t            m_checkGLFlag;

  // indicates that IV must match for cache to be valid
  uint32_t            m_checkIVFlag;

  // indicates that a send must be issued prior to calling cache.
  uint32_t            m_doSendFlag;
    
  // Whether to use GL_COMPILE or GL_COMPILE_AND_EXECUTE
  bool m_useCompileAndExecute;

  SoGLCacheList* m_cList;
};

#endif /* _SO_GL_RENDER_CACHE */
