/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef SO_CONTEXTED_OBJECT
#define SO_CONTEXTED_OBJECT

#include <Inventor/SbBase.h>
#include <Inventor/devices/SoDeviceContextSharedGroup.h>
#include <Inventor/devices/SoDeviceContext.h>

class SbThreadMutex;

/** 
 * @VSGEXT Context dependent object management class.
 *
 * @ingroup helpers
 * 
 * @DESCRIPTION
 *
 *  A helper base class used to store context dependent objects.
 *
 */ 

SoEXTENDER_Documented class INVENTORBASE_API SoBaseContextObject
{
 public:

  /**
   * Constructor.
   *
   * @param sharedContextGroup context shared group from which it depends.
   */
  SoBaseContextObject(SoDeviceContextSharedGroup *sharedContextGroup);

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
   * Returns the OpenGL context in which the OpenGL objects were created.
   */
  inline SoDeviceContextSharedGroup* getContextSharedGroup() const { return m_sharedContextGroup; }

  /**
   * Returns the reference count of this instance (initially zero).
   */
  inline int getRefCount() const { return refCount; } // useful for debugging

  /**
   * This function is called by the attached context when it has been requested 
   * to delete the context through the SoDeviceContext::dispose() method.
   * As some object might be still attached, it triggers all attached object
   * release() method to ask them to detach (and then get it refcount to zero).
   */
  virtual void release() {};

 protected:

   /** 
    * Called by unref before calling destructor, return true if object can be deleted.
    * if it returned false, then the object deletion will be postponned when the 
    * attached context will be freed or binded.
    * By default it returns false if the attached context is not bind.
    */
   virtual bool notifyDelete()
   {
     if ( m_sharedContextGroup )
     {
       SoDeviceContext* ctx = m_sharedContextGroup->getPrimaryContext();
       if ( ctx && ctx->isCurrent() )
         return true; 
     }
     
     return false;
   };

   /** Destructors (used by unref ) */
   virtual ~SoBaseContextObject();

private:
  /** current refcount */
  int refCount;

  /** refCoutn mutex */
  SbThreadMutex* refMutex;

  /** Context where the display list has been created */
  SoDeviceContextSharedGroup* m_sharedContextGroup;

  friend class SoDeviceContextSharedGroup;
};

#endif //SO_CONTEXTED_OBJECT
