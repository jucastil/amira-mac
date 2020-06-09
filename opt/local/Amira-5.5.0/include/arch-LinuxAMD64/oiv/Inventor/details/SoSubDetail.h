/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_SUB_DETAIL_
#define  _SO_SUB_DETAIL_

#include <Inventor/details/SoDetail.h>
#include <Inventor/errors/SoDebugError.h>

/////////////////////////////////////////////////////////////////////////////
//
// Macros to be called within the class definition header for a detail
// subclass:
//

////////////////////////////////////////////
//
// This defines type-identifier variables and methods that all
// subclasses must support. 
//

#define SO_DETAIL_HEADER(className)                                           \
  public:                                                                     \
    /** Returns the type identifier for this specific instance. */            \
    virtual SoType              getTypeId() const;                            \
    /** Returns the type identifier for this class.  */                       \
    static SoType               getClassTypeId() ;                            \
  private:                                                                    \
    static SoType              classTypeId

/////////////////////////////////////////////////////////////////////////////
//
// Macros to be called within the source file for a detail subclass:
//

////////////////////////////////////////////
//
// This declares the static variables defined in SO_DETAIL_HEADER.
//

#define SO__DETAIL_ID_VARS(className)                                         \
  SoType className::classTypeId;

////////////////////////////////////////////
//
// This implements the methods defined in SO_DETAIL_HEADER.
//

#define SO__DETAIL_ID_METHODS(className)                                      \
                                                                              \
SoType                                                                        \
className::getClassTypeId()                                                   \
{                                                                             \
    return classTypeId;                                                       \
}                                                                             \
SoType                                                                        \
className::getTypeId() const                                                  \
{                                                                             \
    return classTypeId;                                                       \
}

////////////////////////////////////////////
//
// This contains the definitions necessary at file scope
//
#define SO_DETAIL_SOURCE(className)                                           \
    SO__DETAIL_ID_VARS(className);                                            \
    SO__DETAIL_ID_METHODS(className)


#if defined(_DEBUG)
#define SO_DETAIL_INIT_CLASS_CHECK_PARENT(className, parentClass)                   \
  if (parentClass::getClassTypeId().isBad()) {                                        \
    SoDebugError::post( SO__QUOTE(className)"::initClass",                            \
      SO__QUOTE(className)" initialized before parent class " \
      SO__QUOTE(parentClass)"\n");                                                    \
    parentClass::initClass();                                                         \
  }
#else
#define SO_DETAIL_INIT_CLASS_CHECK_PARENT(className, parentClass)                   \
  if (parentClass::getClassTypeId().isBad())                                          \
    parentClass::initClass()
#endif

////////////////////////////////////////////
//
// This initializes the type identifer variables defined in
// SO_DETAIL_HEADER. This macro should be called from within
// initClass().
//
#define SO_DETAIL_INIT_CLASS_INTERNAL(className, parentClass) \
  SO_DETAIL_INIT_CLASS_CHECK_PARENT(className, parentClass); \
  classTypeId = SoType::createType(parentClass::getClassTypeId(), SO__QUOTE(className), NULL);

#define SO_DETAIL_INIT_CLASS(className, parentClass) \
  SO_DETAIL_INIT_CLASS_INTERNAL(className, parentClass)

#if defined(_DEBUG)
#define SO_DETAIL_EXIT_CLASS(className) \
  if (! SoType::removeType(classTypeId.getName())) { \
    SoDebugError::post(SO__QUOTE(className)"::exitClass", \
                       "Unable to remove type (%s) for this class. Check exitClass() " \
                       "method is implemented and is called only once.\n", \
                       classTypeId.getName().getString() ); \
  } \
  else \
    classTypeId = SoType::badType()
#else
#define SO_DETAIL_EXIT_CLASS(className) \
  SoType::removeType(classTypeId.getName()); \
  classTypeId = SoType::badType()
#endif

#endif /* _SO_SUB_DETAIL_ */
