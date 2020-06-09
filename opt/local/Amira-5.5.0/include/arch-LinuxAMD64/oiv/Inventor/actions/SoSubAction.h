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


#ifndef _SO_SUB_ACTION_
#define _SO_SUB_ACTION_

#include <Inventor/actions/SoAction.h>
#include <Inventor/SbString.h>
#include <Inventor/errors/SoDebugError.h>

/////////////////////////////////////////////////////////////////////////////
//
// Macros to be called within the class definition header for an action
// subclass:
//

////////////////////////////////////////////
//
// This defines type-identifier variables and methods that all
// subclasses must support.
//

#define SO_ACTION_HEADER(className) \
public: \
  /** Returns the type identifier for this specific instance. */ \
  virtual SoType getTypeId() const; \
  /** Returns the type identifier for this class.  */ \
  static SoType getClassTypeId(); \
 SoEXTENDER public:\
  static void addMethod(SoType t, SoActionMethod* method); \
  \
  static void enableElement(SoType t, int stkIndex); \
\
  /** [OIV-WRAPPER NAME{EnableElements}] [OIV-WRAPPER-RETURN-TYPE NO_WRAP] */ \
  virtual const SoEnabledElementsList & getEnabledElements() const; \
protected: \
  \
  static SoEnabledElementsList *enabledElements; \
  static SoActionMethodList *methods; \
  \
SoINTERNAL public: \
  virtual SoActionMethodList * getActionMethods(); \
  \
private: \
  static  SoType classTypeId; \
  static  SbBool classTypeIdIsSet

// Deprecated: use SO_ACTION_HEADER
#define SO_ACTION_HEADER_WITH_DEF(className) \
  SO_ACTION_HEADER(className)

/////////////////////////////////////////////////////////////////////////////
//
// Macros to be called within the source file for a action subclass:
//

////////////////////////////////////////////
//
// This declares the static variables defined in SO_ACTION_HEADER.
//

#define SO__ACTION_VARS(className) \
  SoEnabledElementsList *className::enabledElements = NULL; \
  SoActionMethodList *className::methods = NULL; \
  SoType className::classTypeId; \
  SbBool className::classTypeIdIsSet = FALSE

////////////////////////////////////////////
//
// This contains the definitions necessary at file scope
//
#define SO_ACTION_SOURCE(className) \
  SO__ACTION_VARS(className); \
  SO__ACTION_METHODS(className)

#define SO_ACTION_AUTOINIT_SOURCE(className, parentClass) \
  SO__ACTION_VARS(className); \
  SO__ACTION_AUTOINIT_METHODS(className, parentClass)

////////////////////////////////////////////
//
// This initializes the type identifer variables defined in
// SO_ACTION_HEADER. This macro should be called from within
// initClass().
//
#if defined(_DEBUG)
#define SO_ACTION_INIT_CLASS_CHECK_PARENT(className, parentClass)               \
  if (parentClass::getClassTypeId().isBad()) {                                        \
    SoDebugError::post( SO__QUOTE(className)"::initClass",                            \
      SO__QUOTE(className)" initialized before parent class " \
      SO__QUOTE(parentClass)"\n");                                                    \
    parentClass::initClass();                                                         \
  }
#else
#define SO_ACTION_INIT_CLASS_CHECK_PARENT(className, parentClass)  \
  if (parentClass::getClassTypeId().isBad())                             \
    parentClass::initClass()
#endif

#define SO_ACTION_INIT_CLASS_INTERNAL(className, parentClass) \
  enabledElements = new SoEnabledElementsList(parentClass::enabledElements); \
  methods = new ::SoActionMethodList(parentClass::methods); \
  SO_ACTION_INIT_CLASS_CHECK_PARENT(className, parentClass); \
  classTypeId = SoType::createType(parentClass::getClassTypeId(), \
                                     SO__QUOTE(className), NULL); \
  classTypeIdIsSet = TRUE;

#define SO_ACTION_INIT_CLASS(className, parentClass) \
  SO_ACTION_INIT_CLASS_INTERNAL(className, parentClass)

#if defined(_DEBUG)
#define SO_ACTION_EXIT_CLASS(className) \
  if (! SoType::removeType(classTypeId.getName())) { \
  SoDebugError::post(SO__QUOTE(className)"::exitClass", \
                     "Unable to remove type (%s) for this class. Check exitClass() " \
                     "method is implemented and is called only once.\n", \
                     classTypeId.getName().getString() ); \
  } \
  else { \
    classTypeId = SoType::badType(); \
    if (enabledElements) \
    { \
      delete enabledElements; \
      enabledElements = NULL; \
    } \
    if (methods) \
    { \
      delete methods; \
      methods = NULL; \
    } \
    classTypeIdIsSet = FALSE; \
  }
#else
#define SO_ACTION_EXIT_CLASS(className) \
  SoType::removeType(classTypeId.getName()); \
  classTypeId = SoType::badType(); \
  if (enabledElements) \
  { \
    delete enabledElements; \
    enabledElements = NULL; \
  } \
  if (methods) \
  { \
    delete methods; \
    methods = NULL; \
  } \
  classTypeIdIsSet = FALSE
#endif

#if defined(_DEBUG)
#define SO__ACTION_CHECK_INIT(className) { \
  if (classTypeId.isBad()) { \
    SoDebugError::post("SO_ACTION_CONSTRUCTOR", \
                       "Can't construct an action of type " \
                       SO__QUOTE(className) \
                       " until initClass() has been called." \
                       " Check SoDB::init() has been called."); \
    className::initClass(); \
  } \
  SoDB::checkDatabase(SO__QUOTE(className), this, className::getClassTypeId(), classTypeId); \
}
#else
#define SO__ACTION_CHECK_INIT(className) { \
  if (classTypeId.isBad()) { \
    className::initClass(); \
  } \
}
#endif

///////////////////////////////////////////////
//
// This is included at the beginning of
// a constructor, to do required initializations
//

#define SO_ACTION_CONSTRUCTOR(className) \
  SO__ACTION_CHECK_INIT(className);

////////////////////////////////////////////
//
// This macro can be used by action subclasses within initClass() to
// register a method to call for a specific node class. It is passed
// the name of the node class and the method to call.
//

#define SO_ACTION_ADD_METHOD(nodeClass, method) \
  addMethod(nodeClass::getClassTypeId(), method)

////////////////////////////////////////////
//
// This implements the methods defined in SO_ACTION_HEADER.
//

#define SO__ACTION_ELEMENTS_METHODS(className) \
const SoEnabledElementsList & \
className::getEnabledElements() const \
{ \
  return *enabledElements; \
} \
\
SoActionMethodList * \
className::getActionMethods() \
{ \
  return methods; \
} \
\
void \
className::addMethod(SoType t, SoActionMethod* method) \
{ \
  methods->addMethod(t, method); \
} \
\
void \
className::enableElement(SoType t, int stkIndex) \
{ \
  if ( t.isBad()) \
  { \
    SoDebugError::post("SO_ENABLE_ELEMENT", \
                       "Can't enable element for " \
                       SO__QUOTE(className) \
                       " until the element initClass function has been called"); \
    return; \
  } \
  enabledElements->enable(t, stkIndex); \
} 

#define SO__ACTION_METHODS(className) \
SoType \
className::getClassTypeId() \
{ \
  return classTypeId; \
} \
 \
SoType \
className::getTypeId() const \
{ \
  return classTypeId; \
} \
\
SO__ACTION_ELEMENTS_METHODS(className)

////////////////////////////////////////////
//
// This implements the methods defined in SO_ACTION_HEADER.
// If class type id is not initialized, jus do it.
//

#define SO__ACTION_AUTOINIT_METHODS(className, parentClass) \
SoType \
className::getClassTypeId() \
{ \
  if (!classTypeIdIsSet) { \
    SO_ACTION_INIT_CLASS(className, parentClass); \
  } \
  return classTypeId; \
} \
\
SoType \
className::getTypeId() const \
{ \
  if (classTypeIdIsSet == FALSE) { \
    SO_ACTION_INIT_CLASS(className, parentClass); \
  } \
  return classTypeId; \
} \
\
SO__ACTION_ELEMENTS_METHODS(className)

#endif /* _SO_SUB_ACTION_ */
