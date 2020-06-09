/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef SO_AUTO_REF_COUNTER_H
#define SO_AUTO_REF_COUNTER_H

#include <Inventor/SbBase.h>
#include <Inventor/misc/SoRefCounter.h>

/**
* Implements smart pointers to SoRefCounter objects.
* 
* @ingroup General
* 
* @DESCRIPTION
*
* This class implements smart pointers to SoRefCounter objects.
*
* @SEE_ALSO
*    SoRefCounter
*    SoRef
* 
* [OIV-WRAPPER-NO-WRAP]
*/

SoINTERNAL class INVENTORBASE_API SoAutoRef
{
public:
  /** Default constructor. */
  SoAutoRef();

  /** Copy constructor. */
  SoAutoRef(const SoAutoRef& that);

  /** Construct from C++ pointer. */
  SoAutoRef(SoRefCounter* pIn);

  /** Destructor. */
  virtual ~SoAutoRef();

  /** Assign another @c SoAutoRef. */
  SoAutoRef& operator=(const SoAutoRef& that)
  {
    (*this) = that.m_pointer;
    return *this;
  }

  /** Assign ordinary C pointer. */
  SoAutoRef& operator=(SoRefCounter* ptr);

  /** Dereference pointer. */
  SoRefCounter& operator*() const
  { return *(get()); }

  /** Cast to C pointer. */
  SoRefCounter* operator->() const
  { return get(); }

  /** Cast to C pointer. */
  SoRefCounter* ptr() const 
  { return get(); }

protected:
  SoRefCounter* get() const
  { return m_pointer; }

  /** handle the object pointer reference */
  SoRefCounter* m_pointer;
};

#endif // SO_AUTO_REF_COUNTER_H
