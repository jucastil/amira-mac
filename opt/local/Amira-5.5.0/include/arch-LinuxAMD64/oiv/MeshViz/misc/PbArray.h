/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _PB_ARRAY_
#define _PB_ARRAY_
#include <string.h>

#include <Inventor/SbBasic.h>

#include <Inventor/STL/vector>

#define PO_ARRAY_HEADER(className,valueType) \
/** @DTEXT Dynamic array of valueType. */ \
/**  */ \
/** @ingroup MeshMisc  */ \
/**  */ \
/** @DESCRIPTION Provides methods and operators for insertion and retrieval of valueType values. It automatically resizes itself when necessary.*/ \
/**  [OIV-WRAPPER-NO-WRAP] */ \
class MESHVIZ_API className { \
public: \
  className(): \
    m_array(0), \
    m_allocatedSize(0), \
    m_lastInd(-1), \
    m_extend(10) \
  {}; \
  /** When the array resizes itself, the extension is a multiple of extend */  \
  className(int init_size, int extend=10);   \
  className(const className& other_array); \
  ~className(); \
\
  /* access/insertion methods */ \
  /** Gets the adress of the internal array. */ \
  const valueType* get() const;  \
\
  /** Gets the valueType value at a particular index. */ \
  valueType get(int index) const;  \
\
  /** Finds the first index in the array of a given valueType value (-1 if not found). */ \
  int find(valueType val) const;  \
\
  /** Inserts valueType value at a specified position in the array. */ \
  void set(int index, valueType val);    \
\
  /** Inserts valueType value at the end of the array. Returns its location in the array. */ \
  int add(valueType val);                 \
\
  /** Inserts a list of valueType values at the end of the array. Returns the location of the last one inserted. */ \
  int add(int num_val, const valueType* val);             \
\
  /* special operators */ \
  /** Copy from other_array. */ \
  className &operator=(const className& other_array);     \
\
  /** Copy from an STL vector. */ \
  className &operator=(const std::vector<valueType>& other_array);     \
\
  /** Appends other_array to the end of the array. */ \
  void operator+=(const className& other_array); \
\
  /** Adds val at the end of the array. */ \
  void operator+=(valueType val);                         \
\
  valueType& operator[](int index);                              \
  const valueType& operator[](int index) const; \
\
  /** Equality comparison operator. */ \
  MESHVIZ_API friend int operator ==(const className &array_1, const className &array_2); \
\
  /** Inequality comparison operator. */ \
  MESHVIZ_API friend int operator !=(const className &array_1, const className &array_2) \
    { return !(array_1 == array_2); }                                         \
\
  /** set the capacity and allocate this capacity if necessary */ \
  void setCapacity(int capacity, int extend); \
\
  /* miscellaneous methods */   \
  void squeeze();                           \
\
  /** Gets the allocated size of the array */ \
  int getCapacity() const;  \
\
  /** Gets the number of values in the array */ \
  int getNum() const;  \
\
  /** Sorts array by increasing order */ \
  void increasingSort();      \
\
  /** Sorts array by decreasing order */ \
  void decreasingSort();     \
\
  /** After empty, the array appears like no valueType value has been previously inserted. */ \
\
  void empty();  \
  /* friend ostream& operator<<(ostream &stream, const className &array); */ \
\
private: \
  valueType *m_array;                                     /** pointer to valueType */ \
  int m_allocatedSize;                                    /** allocated size of the array */ \
  int m_lastInd;                                          /** maximum index inserted  */ \
  int m_extend;                                           /** grow array by this point */ \
  valueType *resize(int sz);                              /** method to resize array */ \
};  \
/*---------------------------------------------------------------------------*/ \
\
\
/* Get the adress of the internal array */ \
inline const valueType* \
className::get() const {return m_array;} \
 \
/* Get the valueType value at a particular index. */ \
inline valueType  \
className::get(int index) const {return m_array[index];} \
 \
/* Find the first index in the array of a given valueType value (-1 if not found) */ \
inline int  \
className::find(valueType val) const { \
  for (register int i=0; i<=m_lastInd; i++) if (m_array[i]==val) return i; \
  return -1; \
}/*---------------------------------------------------------------------------*/ \
 \
 \
/* Insert valueType value at a specified position in the array. */ \
inline void  \
className::set(int index, valueType val) \
{ \
  if ( index >= m_allocatedSize ) resize(index+1); \
  m_array[index] = val; \
  if ( index > m_lastInd ) m_lastInd = index; \
}/*---------------------------------------------------------------------------*/ \
 \
 \
/* Insert valueType value at the end of the array. Return its location in the array. */ \
inline int  \
className::add(valueType val) \
{ \
  m_lastInd++; \
  if ( m_lastInd >= m_allocatedSize ) resize(m_lastInd+1); \
  m_array[m_lastInd] = val; \
   \
  return m_lastInd; \
}/*---------------------------------------------------------------------------*/ \
 \
 \
inline void  \
className::operator+=(valueType val)  \
{ \
  add(val); \
}/*---------------------------------------------------------------------------*/ \
 \
 \
/* Get valueType value in a const array (location on rhs statement).  */ \
inline const valueType&  \
className::operator[](int index) const \
{ \
  return m_array[index]; \
}/*---------------------------------------------------------------------------*/ \
 \
 \
/* Does insert or get (depending on location on lhs or rhs of statement). Does */ \
/* not do automatic resizing - user's responsibility to range check. */ \
inline valueType&  \
className::operator[](int index) \
{ \
  if (index > m_lastInd) m_lastInd = index;  \
  return m_array[index]; \
}/*---------------------------------------------------------------------------*/ \
 \
 \
/* Get the allocated size of the array */ \
inline int  \
className::getCapacity() const {return m_allocatedSize;} \
 \
 \
/* Returning the maximum index of valueType values inserted so far. */ \
inline int  \
className::getNum() const {return m_lastInd+1;} \
 \
 \
/* Reuse the memory allocated by this array. It appears like */ \
/* no valueType value has been previously inserted. */ \
inline void  \
className::empty() {m_lastInd = -1;} 


#endif /* _PB_ARRAY_ */







