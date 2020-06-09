/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Mott (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_SUB_EVENT_
#define  _SO_SUB_EVENT_

#include <Inventor/events/SoEvent.h>
#include <Inventor/SoType.h>
#include <Inventor/misc/SoBasic.h>
#if defined(_DEBUG)
#include <Inventor/errors/SoDebugError.h>
#endif

//  *** note: many of the macros use the "do { ... } while(0)"
//  ***       hack to define multiline blocks as a single statement
//  ***       of code that can be used anywhere and ended with a semicolon

/////////////////////////////////////////////////////////////////////////////
//
// Macros to be called within the class definition header for an event
// subclass:
//

////////////////////////////////////////////
//
// These defines type-identifier and naming variables and methods that
// all subclasses and abstract subclasses must support.
//

#define SO_EVENT_HEADER()                                                     \
  public:                                                                     \
    /** Returns the type identifier for this class.  */                       \
    static SoType getClassTypeId();                                           \
    /** Returns the type identifier for this specific instance. */            \
    virtual SoType getTypeId() const;                                         \
  private:                                                                    \
    static SoType classTypeId              /* Type id              */


/////////////////////////////////////////////////////////////////////////////
//
// Macros to be called within the source file for an event subclass:
//

////////////////////////////////////////////
//
// This declares the static variables defined in SO_EVENT_HEADER
//

#define SO__EVENT_VARS(className) \
  SoType className::classTypeId;


////////////////////////////////////////////
//
// Methods on the type
//

#define SO__EVENT_METHODS(className)                                          \
                                                                              \
    SoType                                                                    \
    className::getTypeId() const                                              \
    {                                                                         \
        return classTypeId;                                                   \
    }                                                                         \
                                                                              \
    SoType                                                                    \
    className::getClassTypeId()                                               \
    {                                                                         \
      return classTypeId;                                                     \
    }

/////////////////////////////////////////////
//
// These include all the definitions required
// at file scope
//

#define SO_EVENT_SOURCE(className)                                            \
    SO__EVENT_VARS(className);                                                \
    SO__EVENT_METHODS(className)


#if defined(_DEBUG)
#define SO_EVENT_INIT_CLASS_CHECK_PARENT(className, parentClass)                   \
  if (parentClass::getClassTypeId().isBad()) {                                        \
    SoDebugError::post( SO__QUOTE(className)"::initClass",                            \
      SO__QUOTE(className)" initialized before parent class " \
      SO__QUOTE(parentClass)"\n");                                                    \
    parentClass::initClass();                                                         \
  }
#else
#define SO_EVENT_INIT_CLASS_CHECK_PARENT(className, parentClass)                   \
  if (parentClass::getClassTypeId().isBad())                                          \
    parentClass::initClass()
#endif

////////////////////////////////////////////
//
// This initializes the type identifer variables defined in
// SO_EVENT_HEADER . This macro should be called from within initClass().
// The parentClass argument should be the class that this subclass is
// derived from.
//

#define SO_EVENT_INIT_CLASS_INTERNAL(className,parentClass) \
  SO_EVENT_INIT_CLASS_CHECK_PARENT(className, parentClass); \
  classTypeId = SoType::createType(parentClass::getClassTypeId(), SO__QUOTE(className))

#define SO_EVENT_INIT_CLASS(className,parentClass) \
  SO_EVENT_INIT_CLASS_INTERNAL(className,parentClass);

#if defined(_DEBUG)
#define SO_EVENT_EXIT_CLASS(className) \
  if (! SoType::removeType(classTypeId.getName())) { \
    SoDebugError::post(SO__QUOTE(className)"::exitClass", \
                       "Unable to remove type (%s) for this class. Check exitClass() " \
                       "method is implemented and is called only once.\n", \
                       classTypeId.getName().getString() ); \
  } \
  else \
    classTypeId = SoType::badType()
#else
#define SO_EVENT_EXIT_CLASS(className) \
  SoType::removeType(classTypeId.getName()); \
  classTypeId = SoType::badType()
#endif

#endif /* _SO_SUB_EVENT_ */

