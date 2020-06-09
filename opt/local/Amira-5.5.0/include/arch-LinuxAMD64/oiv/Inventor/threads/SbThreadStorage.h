/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Nov 2008)
**=======================================================================*/



#ifndef _SB_THREAD_STORAGE_H_
#define _SB_THREAD_STORAGE_H_

#include <Inventor/threads/SbThreadLocalStorage.h>
#include <Inventor/STL/algorithm>
#include <Inventor/STL/functional>

#define GET_THREAD_STORAGE_MAP() \
  static_cast<SbThreadStorageMap*>(GET_THREAD_LOCAL_VAR(SbThreadStorageBase, MTstruct, threadStorageMap))

template <class T>
class SbThreadStorage : public SbThreadStorageBase
{
public:
  SbThreadStorage<T>() { }

  SbThreadStorage<T>( const T t )
  {
    SbThreadStorageMap* threadStorageMap = GET_THREAD_STORAGE_MAP();
    SbThreadStorageMap::iterator iti = threadStorageMap->find( static_cast<SbThreadStorageBase*>(this) );
    if ( iti != threadStorageMap->end() )
      ((*iti).second) = t;
    else
      Register( t );
  }

  /**
   * Storage destructor:
   * Find current storage in the global storage map,
   * Delete thread dependent entry,
   * And remove each entry.
   */
  virtual ~SbThreadStorage()
  {
    s_threadStorageGlobalMutex.lock();
    SbThreadStorageGlobalList::iterator it_i = s_threadStorageGlobalList.begin();
    while(it_i != s_threadStorageGlobalList.end())
    { 
      SbThreadStorageMap::iterator it_j = (*it_i)->find( this );
      if ( it_j != (*it_i)->end() )
      {
        T val = (static_cast<T>((*it_j).second));
        if (val)
          val->unref();
        (*it_i)->erase(it_j);
        continue;
      }
      ++it_i;
    }
    s_threadStorageGlobalMutex.unlock();
  }

  /**
   * Override operator=
   * Set value of the storage for current thread.
   * If current thread storage was not existing, create it.
   */
  SbThreadStorage<T>& operator=(T t)
  {
    SbThreadStorageMap* threadStorageMap = GET_THREAD_STORAGE_MAP();
    SbThreadStorageMap::iterator iti = threadStorageMap->find( static_cast<SbThreadStorageBase*>(this) );
    if ( iti != threadStorageMap->end() )
      ((*iti).second) = t;
    else
      Register( t );
    return *this;
  }

  /**
   * Override operator->
   * Gets value of the storage for current thread.
   * Returns NULL if the storage does not exist for current thread.
   */
  T operator->() const
  {
#if defined(_DEBUG)
    T t = static_cast<T>(getValue());
    if (t == NULL)
      fprintf( stderr, "MT ERROR: in ::operator-> , object not initialized for current thread." );
    return t;
#else
    return static_cast<T>(getValue());
#endif
  }

  /**
   * Override operator T*() 
   * Destroying objects from delete operator is not allowed.
   */
  T operator*() const 
  {
    return static_cast<T>(getValue());
  }

  /**
   * Override operator bool() 
   * Comparing templated objects work as comparing direct object.
   * for example, for: SbThreadStorage< SoCache* > m_cache;
   * doing:  m_cache == NULL
   * run as doing 
   */
  operator bool() const
  {
    return ((static_cast<T>(getValue())) != NULL);
  }

  virtual void cleanStorage()
  {
    SbThreadStorageMap* threadStorageMap = GET_THREAD_STORAGE_MAP();
    SbThreadStorageMap::iterator iti = threadStorageMap->find( static_cast<SbThreadStorageBase*>(this) );
    if (iti != threadStorageMap->end())
    {
      T val = (static_cast<T>((*iti).second));
      if (val)
        val->unref();
      (*iti).second = NULL;
    }
  }

  /** Calls the passed function to all registered threads object. */
  template< typename Func>
  void call( Func f )
  {
    s_threadStorageGlobalMutex.lock();
    SbThreadStorageGlobalList::iterator it_i = s_threadStorageGlobalList.begin();
    while(it_i != s_threadStorageGlobalList.end())
    { // For each registered map, search for this threadStorage and apply function call.
      SbThreadStorageMap::iterator it_j = (*it_i)->find( static_cast<SbThreadStorageBase*>(this) );
      if ( it_j != (*it_i)->end() )
      {
        if ((*it_j).second != NULL)
          std::mem_fun(f)(static_cast<T>((*it_j).second) );
      }
      ++it_i;
    }
    s_threadStorageGlobalMutex.unlock();
  }

  template< typename Func, typename Param>
  void call( Func f, Param p )
  {
    s_threadStorageGlobalMutex.lock();
    SbThreadStorageGlobalList::iterator it_i = s_threadStorageGlobalList.begin();
    while(it_i != s_threadStorageGlobalList.end())
    { // For each registered map, search for this threadStorage and apply function call.
      SbThreadStorageMap::iterator it_j = (*it_i)->find( static_cast<SbThreadStorageBase*>(this) );
      if ( it_j != (*it_i)->end() )
      {
        if ((*it_j).second != NULL)
          std::bind2nd(std::mem_fun(f), p)(static_cast<T>((*it_j).second) );
      }
      ++it_i;
    }
    s_threadStorageGlobalMutex.unlock();
  }

private:
  // Disable several operators
  void* operator new[] (size_t) throw() { return 0; }
  void operator delete[] (void*) { }
  void* operator new( size_t, char ) throw() { return 0; }

};

template <>
class SbThreadStorage<bool> : public SbThreadStorageBase
{
public:

  virtual ~SbThreadStorage<bool>()
  {
    s_threadStorageGlobalMutex.lock();
    SbThreadStorageGlobalList::iterator it_i = s_threadStorageGlobalList.begin();
    // For each registered map, search for this threadStorage,
    // call cleanStorage method and remove the entry.
    while(it_i != s_threadStorageGlobalList.end())
    { 
      SbThreadStorageMap::iterator it_j = (*it_i)->find( this );
      if ( it_j != (*it_i)->end() )
      {
        it_j->first->cleanStorage();
        (*it_i)->erase(it_j);
      }
      ++it_i;
    }
    s_threadStorageGlobalMutex.unlock();
  }

  /**
   * Override default <<= operator
   * Set the specified value for the current thread.
   */
  SbThreadStorage<bool>& operator <<=(bool t)
  {
    SbThreadStorageMap* threadStorageMap = GET_THREAD_STORAGE_MAP();
    SbThreadStorageMap::iterator iti = threadStorageMap->find( static_cast<SbThreadStorageBase*>(this) );
    void* pt = reinterpret_cast<void*>(static_cast<uintptr_t>(t));
    if ( iti != threadStorageMap->end() )
      ((*iti).second) = pt;
    else
      Register( pt );
    return (*this);
  }

  /**
   * Override default >>= operator
   * Set the specified value for all threads.
   */
  SbThreadStorage<bool>& operator >>=(bool t)
  {
    SbThreadStorageMap* threadStorageMap = GET_THREAD_STORAGE_MAP();
    SbThreadStorageMap::const_iterator iti = threadStorageMap->find( static_cast<SbThreadStorageBase*>(this) );
    void *pt = reinterpret_cast<void*>(static_cast<uintptr_t>(t));
    if ( iti == threadStorageMap->end() )
      Register( pt );

    s_threadStorageGlobalMutex.lock();
    SbThreadStorageGlobalList::iterator it_i = s_threadStorageGlobalList.begin();
    while(it_i != s_threadStorageGlobalList.end())
    { // For each registered map, search for this threadStorage and apply function call.
      SbThreadStorageMap::iterator it_j = (*it_i)->find( static_cast<SbThreadStorageBase*>(this) );
      if ( it_j != (*it_i)->end() )
      {
        ((*it_j).second) = pt;
      }
      ++it_i;
    }
    s_threadStorageGlobalMutex.unlock();
    return *this;
  }

  virtual void cleanStorage()
  {
  }

  operator bool() const
  {
    return ((static_cast<bool>(getValue())) == true);
  }

private:
  // Disable several operators
  void* operator new[] (size_t) throw() { return 0; }
  void operator delete[] (void*) { }
  void* operator new( size_t , char  ) throw() { return 0; }
  SbThreadStorage<bool>& operator=(bool) { return *this; }
};

#undef GET_THREAD_STORAGE_MAP

#endif //_SB_THREAD_STORAGE_H_

/**/
