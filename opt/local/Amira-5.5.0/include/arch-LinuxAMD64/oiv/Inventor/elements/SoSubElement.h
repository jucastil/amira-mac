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


#ifndef  _SO_SUB_ELEMENT_
#define  _SO_SUB_ELEMENT_

#include <Inventor/elements/SoElement.h>

#if defined(_DEBUG)
#include <Inventor/SoDB.h>
#endif

/////////////////////////////////////////////////////////////////////////////
//
// Macros to be called within the class definition header for a element
// subclass:
//

////////////////////////////////////////////
//
// These define type-identifier and stack index variables and methods
// that all subclasses must support.
//

//
// This one is for abstract element classes.
//

#define SO_ELEMENT_ABSTRACT_HEADER(className)                                 \
  public:                                                                     \
    /** Returns the type identifier for this class.  */                       \
    static SoType       getClassTypeId();                                     \
    /** Returns the stack id for this element.  */                            \
    static int          getClassStackIndex();                                 \
  protected:                                                                  \
    className();                                                              \
  private:                                                                    \
    static int         classStackIndex;                      \
    static SoType      classTypeId

//
// This one is for non-abstract element classes.
//
#define SO_ELEMENT_HEADER(className)                                          \
    SO_ELEMENT_ABSTRACT_HEADER(className);                                    \
  private:                                                                    \
    static void *createInstance(SoType* dynamicType = NULL)

/////////////////////////////////////////////////////////////////////////////
//
// Macros to be called within the source file for a element subclass:
//

////////////////////////////////////////////
//
// This declares the static variables defined in SO_ELEMENT_HEADER
// or SO_ELEMENT_ABSTRACT_HEADER.
//

#define SO__ELEMENT_ABSTRACT_VARS(className)                                  \
  SoType  className::classTypeId;                         \
  int className::classStackIndex = 0;

#define SO__ELEMENT_VARS(className)                                           \
SO__ELEMENT_ABSTRACT_VARS(className)

#if defined(_DEBUG)
#define SO_ELEMENT_CHECK_INIT(className) { \
  if (classTypeId.isBad()) { \
    SoDebugError::post("Element Constructor", \
                       "Can't construct an element of type " \
                       SO__QUOTE(className) \
                       " until initClass() has been called"); \
    className::initClass(); \
  } \
  SoDB::checkDatabase(SO__QUOTE(className), this, className::getClassTypeId(), classTypeId); \
}
#else
#define SO_ELEMENT_CHECK_INIT(className) { \
  if (classTypeId.isBad()) { \
    className::initClass(); \
  } \
}
#endif

//
// Methods on an abstract type
//
#define SO__ELEMENT_ABSTRACT_METHODS(className)                               \
                                                                              \
className::className()                                                        \
{                                                                             \
  SO_ELEMENT_CHECK_INIT(className);                                    \
  commonInit() ;                                                              \
}                                                                             \
                                                                              \
SoType                                                                        \
className::getClassTypeId()                                                   \
{                                                                             \
  return classTypeId;                                                         \
}                                                                             \
                                                                              \
int                                                                           \
className::getClassStackIndex()                                               \
{                                                                             \
  return classStackIndex;                                                     \
}


//
// Methods on a non-abstract type
//
#define SO__ELEMENT_METHODS(className)                                        \
                                                                              \
className::className()                                                        \
{                                                                             \
    SO_ELEMENT_CHECK_INIT(className);                                  \
    commonInit() ;                                                            \
    setTypeId(classTypeId);                                                   \
    setStackIndex(classStackIndex);                                           \
}                                                                             \
                                                                              \
void *                                                                        \
className::createInstance(SoType *)                                           \
{                                                                             \
  return new className;                                                       \
}                                                                             \
                                                                              \
SoType                                                                        \
className::getClassTypeId()                                                   \
{                                                                             \
  return classTypeId;                                                         \
}                                                                             \
                                                                              \
int                                                                           \
className::getClassStackIndex()                                               \
{                                                                             \
  return classStackIndex;                                                     \
}


/////////////////////////////////////////////
//
// These include all the definitions required
// at file scope
//

#define SO_ELEMENT_ABSTRACT_SOURCE(className)                                 \
    SO__ELEMENT_ABSTRACT_VARS(className);                                     \
    SO__ELEMENT_ABSTRACT_METHODS(className)

#define SO_ELEMENT_SOURCE(className)                                          \
    SO__ELEMENT_VARS(className);                                              \
    SO__ELEMENT_METHODS(className)

////////////////////////////////////////////
//
// This initializes the type identifer variables defined in
// SO_ELEMENT_HEADER or SO_ELEMENT_ABSTRACT_HEADER. This macro
// should be called from within initClass(). The parentClass argument
// should be the class that this subclass is derived from.
//
#if defined(_DEBUG)
#define SO_ELEMENT_INIT_CLASS_CHECK_PARENT(className, parentClass)                   \
  if (parentClass::getClassTypeId().isBad()) {                                        \
    SoDebugError::post( SO__QUOTE(className)"::initClass",                            \
      SO__QUOTE(className)" initialized before parent class " \
      SO__QUOTE(parentClass)"\n");                                                    \
    parentClass::initClass();                                                         \
  }
#else
#define SO_ELEMENT_INIT_CLASS_CHECK_PARENT(className, parentClass)                   \
  if (parentClass::getClassTypeId().isBad())                                          \
    parentClass::initClass()
#endif

#define SO_ELEMENT_INIT_ABSTRACT_CLASS_INTERNAL(className,parentClass) \
    SO_ELEMENT_INIT_CLASS_CHECK_PARENT(className, parentClass); \
    classTypeId = SoType::createType( parentClass::getClassTypeId(), \
                                      SO__QUOTE(className), \
                                      NULL); \
    classStackIndex = parentClass::getClassStackIndex();

#define SO_ELEMENT_INIT_ABSTRACT_CLASS(className, parentClass) \
  SO_ELEMENT_INIT_ABSTRACT_CLASS_INTERNAL(className, parentClass);

#define SO_ELEMENT_INIT_CLASS_INTERNAL(className,parentClass) \
    SO_ELEMENT_INIT_CLASS_CHECK_PARENT(className, parentClass); \
    classTypeId = SoType::createType( parentClass::getClassTypeId(), \
                                      SO__QUOTE(className), \
                                      &className::createInstance); \
    if (classStackIndex == 0) \
    { \
      if (parentClass::getClassStackIndex() < 0) \
        classStackIndex = createStackIndex(classTypeId); \
      else \
        classStackIndex = parentClass::getClassStackIndex(); \
    }

#define SO_ELEMENT_INIT_CLASS(className, parentClass) \
  SO_ELEMENT_INIT_CLASS_INTERNAL(className, parentClass);

#if defined(_DEBUG)
#define SO_ELEMENT_EXIT_CLASS(className) \
  if (! SoType::removeType(classTypeId.getName())) { \
    SoDebugError::post(SO__QUOTE(className)"::exitClass", \
                       "Unable to remove type (%s) for this class. Check exitClass() " \
                       "method is implemented and is called only once.\n", \
                       classTypeId.getName().getString() ); \
  } \
  else { \
    classTypeId = SoType::badType(); \
    classStackIndex = 0; \
  }
#else
#define SO_ELEMENT_EXIT_CLASS(className) \
  SoType::removeType(classTypeId.getName()); \
  classTypeId = SoType::badType(); \
  classStackIndex = 0
#endif

#endif /* _SO_SUB_ELEMENT_ */
