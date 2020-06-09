/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef SO_REF_COUNTER_H
#define SO_REF_COUNTER_H

#include <stdio.h>
#include <Inventor/SbBase.h>
#include <Inventor/threads/SbThreadSpinlock.h>
#include <Inventor/errors/SoDebugError.h>

class SoRefCounter;

// callback function prototypes
typedef void SoBaseRefCountCB(void *userData, const SoRefCounter *base);


/**
* Base class for ref-counted objects.
* 
* @ingroup General
* 
* @DESCRIPTION
*
* If a single object or more precisely a pointer to a single object
* is used at multiple locations in a program there should be some
* way to detect if the object is still in use or if it can be destroyed.
*
* Reference counting as implemented by this class provides such a way.
* The behavior is the same as reference counting of Open Inventor nodes
* except that there is no automatic ref/unref (unless you use SoRef).
* Manual reference counting means that the user has to call the methods
* @c ref() and @c unref() whenever he wants to use or discard an object.
* These methods increment or decrement the reference count.  The initial
* reference count is zero.  The object is destroyed automatically if the
* is decremented to zero, i.e., the object isn't in use anymore.
*
* The related class SoRef implements smart pointers to
* reference counted objects. Such pointers automatically keep track of
* reference counting and therefore are safer than explicit use of @c ref()
* and @c unref().
*
* @SEE_ALSO
*    SoRef
* 
* 
* [OIV-WRAPPER-NO-WRAP]
*/ 


class INVENTORBASE_API SoRefCounter
{
public:
    /**
     * Adds a reference to an instance.
     * This is defined to be const so users can call it on any instance, even const ones.
     */
    virtual void ref() const;

    /** 
     * Removes a reference from an instance.
     * This method removes a reference from the object. If the reference
     * count goes to zero the object is automatically deleted.
     * This is defined to be const so users can call it on any instance, even const ones.
     */
    virtual void unref() const;

    /**
     * unrefNoDelete() should be called when it is desired to decrement the
     * reference count, but not delete the instance if this brings the reference count
     * to zero. This is most useful in returning an object to a zero-reference-count
     * state, like it was when it was created by @B new@b.
     * This is defined to be const so users can call it on any instance, even const ones.
     */
    virtual void unrefNoDelete() const;

    /**
     * Returns current reference count.
     */
    inline int getRefCount() const
    { return m_refcount; }

    /**
     * lock this instance.
     */
    inline void lock() const
    { m_refMutex.lock(); }

    /**
     * unlock this instance.
     */
    inline void unlock() const
    { m_refMutex.unlock(); }


SoINTERNAL public:
    /** init static members of this class */
    static void initClass();

    /** reset static members of this class */
    static void exitClass();

    /**
     * set a Callback called by invokeRefCountCB when a ref() / unref() 
     * has occurred and the object.
     */
    static void setRefCountCallback(SoBaseRefCountCB *f)
    { s_refCountCBFunc = f; }

    /**
     * set the user data pointer associated to the RefCountCB
     */
    void setRefCountCallbackData(void *userData = NULL)
    { m_refCountCBData = userData; }

    /**
     * Invoke the refCount callback if any each time the refcount is modified.
     */
    void invokeRefCountCB() const;

    /** Turns on/off reference count tracing (for debugging) */
    static inline void setTraceRefs(const bool enable)
    { s_traceRefs = enable; }

    /** get reference count */
    static inline SbBool getTraceRefs()
    { return s_traceRefs; }

    /**
     * Force the refcounter a specific value.
     * this should be never used (specific to ScaleViz).
     */
    void setRefCount(const int count);

protected:
    /** default constructor. */
    SoRefCounter();

    /** Copy constructor; explicitly DOES NOT copy the refcount. */
    SoRefCounter(const SoRefCounter &);

    /** Assignment operator; explicitly DOES NOT copy the refcount. */
    SoRefCounter & operator=(const SoRefCounter &)
    { return *this; }

    /** Destructor is protected. Use unref() instead. */
    virtual ~SoRefCounter();


    /** Will be called just before the object is deleted. 
     * You might want to override the method to detach objects or
     * do some other cleanup which needs to be done.
     * Some cleanup can't be deferred to the destructor because all
     * the derived stuff is already gone. default is true.
     */
    virtual bool notifyDelete() const
    { return true; }

    /**
     * Actually deletes an instance. Allows subclasses to do other
     * stuff before the deletion if necessary.
     */
    virtual void destroy()
    { delete this; }

private:
  /** Turns on/off reference count tracing (for debugging) */
  static bool s_traceRefs;

  /** RefCount is a single callback function, not a list */
  static SoBaseRefCountCB* s_refCountCBFunc;
  void* m_refCountCBData;

  /** Reference count (consider ref/unref as a const operation) */
  mutable int m_refcount;
  mutable SbThreadSpinlock m_refMutex;

};

#endif // SO_REF_COUNTER_H
