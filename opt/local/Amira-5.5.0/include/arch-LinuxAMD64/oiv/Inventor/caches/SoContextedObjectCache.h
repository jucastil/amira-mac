/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef SO_CONTEXTED_OBJECT_CACHE_H
#define SO_CONTEXTED_OBJECT_CACHE_H

#include <Inventor/SbBasic.h>
#include <Inventor/SoDB.h>
#include <Inventor/threads/SbThreadStorage.h>
#include <Inventor/caches/SoBaseContextCache.h>
#include <Inventor/caches/SoContextedObjectCacheList.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/SbMathHelper.h>
#include <Inventor/devices/SoDeviceContextSharedGroup.h>
#include <Inventor/devices/SoGLContext.h>


class SbThreadMutex;
class SoState;

/**
 * This class cache a OpenGL object for each contexts.
 * [OIV-WRAPPER-NO-WRAP]
 */
template <typename TContextedObject>
class INVENTOR_API SoContextedObjectCache : public SoBaseContextCache
{
public:
  /**
   * Contsructor.
   */
  SoContextedObjectCache( bool sharable = true )
  : m_sharable(sharable)
  {
    m_numRenderCaches = SbMathHelper::Max(SoDB::getNumRenderCaches(), 1);
    ref();
  }

  /**
   * Return cached texture object.
   * @param state is the current Inventor state
   * @param recreated is true if the GL object has just been (re)created.
   */
  TContextedObject* getObject(SoState* state, bool& recreated)
  {
    // get/check context
    SoGLContext* context = SoGLContext::getCurrent();
    if ( context == NULL )
    {
      SoDebugError::post("SoContextedObjectCache<TContextedObject>::getObject()", "No active context !!\n");
      return NULL;
    }

    // if no cache already exist for this thread, create one
    if (!m_objCache)
      m_objCache = new SoContextedObjectCacheList<TContextedObject>(m_numRenderCaches, m_sharable);

    // try to get an existing cache object depending on the context sharedId 
    // as we consider that a cache is valid in any of its shared context
    int sharedId = context->getSharedId();
    TContextedObject *texObj = (m_objCache->getCache(state, 1.0f));
    recreated = false;

    // if no valid object exist then create one
    if ( !texObj )
    {
      recreated = true;
      texObj = createObject(state);
      m_objCache->setCache(sharedId, texObj, 1.0f, state);
      
      // do not forget to tell the context that we are attached to it
      // only if we are not already notified by this share group.
      if (!context->getSharedGroup()->contains(this))
        context->getSharedGroup()->ref(this);
    }

    return texObj;
  }

  /**
   * Return cached texture object.
   * @param state is the current Inventor state
   */
  TContextedObject* getObject(SoState* state)
  {
    bool recreated;
    return getObject(state, recreated);
  }

  /**
   * Return true if a cache object exists for this context
   */
  bool hasValidObject(SoDeviceContext* context)
  {
    if (context==NULL)
      return false;

    return (m_objCache && (m_objCache->getCache(context, 1.0f) != NULL));
  }

  /**
   * Return true if a cache object exists for this context
   */
  bool hasValidObject(SoState* /*state*/)
  {
    // get current context
    SoGLContext* context = SoGLContext::getCurrent();
    return hasValidObject(context);
  }


  /** Invalidate all caches */
  void invalidate()
  {
    m_objCache.call(&SoContextedObjectCacheList<TContextedObject>::invalidateAll, (SoState*)NULL);
  }

  /**
   * This function is called when a context has been requested 
   * to be deleted through the SoDeviceContext::dispose() method.
   * As some object might be still attached, it triggers all attached object
   * release() method to ask them to detach (and then get its refcount to zero).
   */
  virtual void release(SoDeviceContextSharedGroup *ctx)
  {
    // remove all object that belongs to this context
    if (!m_objCache)
    {
      SoDebugError::post("SoContextedObject::release()","There is no cache for this thread");
    }
    else
    {
      m_objCache->invalidateContext( ctx );
    }
    // detach from context.
    ctx->unref(this);
  }


protected:
   /**
    * called by unref before calling destructor
    * return false if there is still some context dependent object 
    * and then delete should not be called
    */
   virtual bool notifyDelete()
   {
     bool ret = true;

     // invalidate all objects
     invalidate();

     // we should release any context reference, but we don't know
     // which one to unref explicitly and we don't want to store such list
     // then we return true and rely on SoDevice::checkRefIssue called in destructor
     // to do the job thus avoiding memory leak
     // TODO: evaluate checkRefIssue cost if too much then we should store this list.
     // TODO: and do the unref here.

     return ret;
   }

  /**
   * Destructor.
   */
  virtual ~SoContextedObjectCache()
  {
    invalidate();
  }

  /**
   * Allocate a TContextedObject
   */
  virtual TContextedObject* createObject(SoState *state)
  {
    TContextedObject* obj = new TContextedObject(state);
    return obj;
  }

private:

  SbThreadStorage< SoContextedObjectCacheList<TContextedObject> * > m_objCache;
  int m_numRenderCaches;
  bool m_sharable;
};

#endif //SO_CONTEXTED_OBJECT_CACHE
