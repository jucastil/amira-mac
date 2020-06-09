/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _SO_BASE_CONTEXT_CACHE_H_
#define _SO_BASE_CONTEXT_CACHE_H_

#include <Inventor/SbBase.h>

class SbThreadMutex;
class SoDeviceContextSharedGroup;

/**
 * @VSGEXT Base context dependent cache management class.
 *
 * @ingroup helpers
 * 
 * @DESCRIPTION
 *
 *  A helper base class used to store context dependent cache objects.
 *
 */
#ifdef OIV_NET_DOC
class INVENTORBASE_API SoBaseContextCache
#else
SoINTERNAL class INVENTORBASE_API SoBaseContextCache
#endif
{
 public:

  /**
   * Constructor.
   */
  SoBaseContextCache();

  /**
   * Increment reference count. @BR
   * Reference count is initially zero.
   */
  void ref();

  /**
   * Decrement reference count. @BR
   * If this call changes the reference count to zero, the object
   * will be destroyed (just like node classes).
   *
   * Context dependent objects can only be destroyed if the context that owns
   * them is active. The @I state @i parameter is used to determine
   * the correct context for this object.
   * You can pass a NULL state to unref(), but deletion of the object
   * will be delayed until an action is applied in the correct context.
   */
  void unref();

  /**
   * Returns the reference count of this instance (initially zero).
   */
  inline int getRefCount() const { return refCount; } // useful for debugging

  /**
   * This function is called when a context has been requested 
   * to delete the context through the SoDeviceContext::dispose() method.
   * As some object might be still attached, it triggers all attached object
   * release() method to ask them to detach (and then get it refcount to zero).
   */
  virtual void release( SoDeviceContextSharedGroup* ) = 0;

   /**
    * Object is considered not context dependent as long as 
    * SoDeviceContext was not ref by this object. Once at least one device is ref then
    * it calls this function to enbale later check checks deleting this object.
    * see (SoDeviceContext::checkRefIssue call in destructor).
    */
   inline void setContextDependent(const bool flag=true)
   { m_isContextDependent=flag; }

   /**
    * return current context dependency state.
    * (by default all caches are context dependent).
    */
   inline bool isContextDependent() const
   { return m_isContextDependent;}

 protected:

   /**
    * called by unref before calling destructor 
    * if it returns false then it means that delete should not be called
    * as some object were not freed because of context dependency
    */
   virtual bool notifyDelete() = 0;

   /** Destructors (used by unref ) */
   virtual ~SoBaseContextCache();

private:
  /** current refcount */
  int refCount;
  /** current context dependencie */
  bool m_isContextDependent;
};

#endif //SO_CONTEXTED_OBJECT
