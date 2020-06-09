/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef SB_DATATYPE_MACROS_H
#define SB_DATATYPE_MACROS_H

#include <Inventor/SbDataType.h>

#include <Inventor/STL/cassert>

/**
 * This macro takes a function template with one argument
 * and instanciate it according to the data type given.
 * A typical usage, is the case where you have a void* pointer
 * and its type and you want to apply a function on elements of
 * the pointer. By defining a function template like this :
 * @code
 * template typename<T> void myFunc(void* data, size_t x)
 * {
 *  T* myBuffer = static_cast<T>(data);
 *  for ( size_t i = 0; i < x; i++ )
 *    myBuffer[i] = (T)rand();
 * }
 * @endcode
 * And then calling it like this:
 * @code
 * SB_DATATYPE_CALL(myFunc, (myData, 10), type)
 * @endcode
 * You avoid the use of a switch. Furthermore, because
 * myFunc is a template and not a macro, it's still debuggable
 * without problems.
 * @param Function is a function template
 * @param Params is a list of parameters enclosed by parens
 * to pass to Function
 * @param Type is a SbDataType
 */
#define SB_DATATYPE_CALL(Function, Params, Type)      \
  if(SbDataType::m_true)                              \
  {                                                   \
    switch((Type))                                    \
    {                                                 \
    case SbDataType::UNSIGNED_SHORT :                 \
      Function<unsigned short>Params;                 \
      break;                                          \
    case SbDataType::UNSIGNED_INT32 :                 \
      Function<uint32_t>Params;                       \
      break;                                          \
    case SbDataType::SIGNED_BYTE :                    \
      Function<signed char>Params;                    \
      break;                                          \
    case SbDataType::SIGNED_SHORT :                   \
      Function<signed short>Params;                   \
      break;                                          \
    case SbDataType::SIGNED_INT32 :                   \
      Function<int32_t>Params;                        \
      break;                                          \
    case SbDataType::FLOAT :                          \
      Function<float>Params;                          \
      break;                                          \
    case SbDataType::UNSIGNED_BYTE :                  \
      Function<unsigned char>Params;                  \
      break;                                          \
    case SbDataType::DOUBLE:                          \
      Function<double>Params;                         \
      break;                                          \
    default:                                          \
      assert(0);                                      \
      break;                                          \
    }                                                 \
  }                                                   \
  else                                                \
    (void)0

/**
 * This macro takes a function template with one argument
 * returning one value, and instanciate it
 * according to the data type given. See SB_DATATYPE_CALL for
 * an usage example.
 * @param Function is a function template
 * @param Params is a list of parameters enclosed by parens
 * to pass to Function
 * @param Dest is filled with the return value of Function
 * @param Type is a SbDataType
 */
#define SB_DATATYPE_CALL_ASSIGN(Function, Params, Dest, Type)   \
  if(SbDataType::m_true)                                        \
  {                                                             \
    switch((Type))                                              \
    {                                                           \
    case SbDataType::UNSIGNED_SHORT :                           \
      Dest = Function<unsigned short>Params;                    \
      break;                                                    \
    case SbDataType::UNSIGNED_INT32 :                           \
      Dest = Function<uint32_t>Params;                          \
      break;                                                    \
    case SbDataType::SIGNED_BYTE :                              \
      Dest = Function<signed char>Params;                       \
      break;                                                    \
    case SbDataType::SIGNED_SHORT :                             \
      Dest = Function<signed short>Params;                      \
      break;                                                    \
    case SbDataType::SIGNED_INT32 :                             \
      Dest = Function<int32_t>Params;                           \
      break;                                                    \
    case SbDataType::FLOAT :                                    \
      Dest = Function<float>Params;                             \
      break;                                                    \
    case SbDataType::UNSIGNED_BYTE :                            \
      Dest = Function<unsigned char>Params;                     \
      break;                                                    \
    case SbDataType::DOUBLE:                                    \
      Dest = Function<double>Params;                            \
      break;                                                    \
    default:                                                    \
      assert(0);                                                \
      break;                                                    \
    }                                                           \
  }                                                             \
  else                                                          \
    (void)0

#endif //SB_DATATYPE_MACROS_H
