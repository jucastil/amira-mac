/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef SO_REF_H
#define SO_REF_H

#include <Inventor/misc/SoAutoRef.h>

/**
* Template class that implements typed smart pointers to any class inheriting SoRefCounter.
* 
* @ingroup General
* 
* @DESCRIPTION
*
* This class implements smart pointers to any class that inherits SoRefCounter.
*
* @SEE_ALSO
*    SoRefCounter
* 
* [OIV-WRAPPER-NO-WRAP]
*/

template <typename T>
class SoRef : public SoAutoRef
{
public:
  /// Default constructor.
  SoRef()
  {};

  /// Copy constructor.
  SoRef(const SoRef<T>& that)
  {
    m_pointer = that.m_pointer;
    if (m_pointer)
      m_pointer->ref();
  }

  /// Construct from C++ pointer.
  SoRef(T* pIn)
  {
    m_pointer = dynamic_cast<T*>(pIn);
    if (m_pointer)
      m_pointer->ref();
  }

  /// Construct from another SoRef
  template<typename Y>
  SoRef(const SoRef<Y>& that)
  {
    m_pointer = that.ptr();
    if (m_pointer)
      m_pointer->ref();
  }

  /// Destructor.
  virtual ~SoRef()
  {};

  /// Assign another @c SoRef.
  SoRef<T>& operator=(const SoRef<T>& that)
  {
    (*this) = (T*)(that.m_pointer);
    return *this;
  }

  /// Assign to another @c SoRef if the types are assignable (from derived to base classes).
  template<typename Y>
  SoRef<T>& operator=(const SoRef<Y>& that)
  {
    (*this) = dynamic_cast<T*>(that.m_pointer);
    return *this;
  }

  /// Assign ordinary C pointer.
  SoRef<T>& operator=(T* ptr)
  {
    if (m_pointer != ptr) {
      if (m_pointer)
        m_pointer->unref();
      m_pointer = ptr;
      if (m_pointer)
        m_pointer->ref();
    }
    return *this;
  }

  /// Cast to C pointer.
  operator T*() const 
  { return ((T*)(m_pointer)); }

  /// Dereference pointer.
  T& operator*() const
  { return *((T*)m_pointer); }

  /// Cast to C pointer.
  T* operator->() const
  { return ((T*)(m_pointer)); }

  /// Cast to C pointer.
  T* ptr() const 
  { return ((T*)(m_pointer)); }

};

#endif // SO_REF_H
