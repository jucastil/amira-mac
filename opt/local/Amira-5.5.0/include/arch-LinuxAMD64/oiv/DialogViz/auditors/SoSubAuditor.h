/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/

#ifndef  _SO_SUB_AUDITOR_
#define  _SO_SUB_AUDITOR_

#include <Inventor/SoType.h>
#include <Inventor/SbString.h>
#include <Inventor/misc/SoBasic.h>

////////////////////////////////////////////
//
// These defines type-identifier and naming variables and methods that
// all subclasses and abstract subclasses must support.
//

#define SO_AUDITOR_HEADER()                                                   \
  public:                                                                     \
    static SoType       getClassTypeId();       /* Returns class type id */   \
                                                                              \
    virtual SoType      getTypeId() const;      /* Returns type id      */    \
  private:                                                                    \
    static SoType       classTypeId             /* Type id              */


/////////////////////////////////////////////////////////////////////////////
//
// Macros to be called within the source file for an event subclass:
//

////////////////////////////////////////////
//
// This declares the static variables defined in SO_AUDITOR_HEADER
//

#define SO__AUDITOR_VARS(className)                                           \
    SoType              className::classTypeId


////////////////////////////////////////////
//
// Methods on the type
//

#define SO__AUDITOR_METHODS(className)  \
                                        \
  SoType                                \
  className::getTypeId() const          \
  {                                     \
        return classTypeId;                 \
  }                                     \
                                        \
  SoType                                \
  className::getClassTypeId()           \
  {                                                                           \
    return classTypeId;                                               \
  }

/////////////////////////////////////////////
//
// These include all the definitions required
// at file scope
//

#define SO_AUDITOR_SOURCE(className)                                          \
    SO__AUDITOR_VARS(className);                                                      \
    SO__AUDITOR_METHODS(className)


////////////////////////////////////////////
//
// This initializes the type identifer variables defined in
// SO_AUDITOR_HEADER . This macro should be called from within initClass().
// The parentClass argument should be the class that this subclass is
// derived from.
//

#define SO_AUDITOR_INIT_CLASS_INTERNAL(className,parentClass)                          \
    classTypeId =                                                             \
        SoType::createType(parentClass::getClassTypeId(),                     \
                   SO__QUOTE(className))

#define SO_AUDITOR_INIT_CLASS(className,parentClass) \
  SO_AUDITOR_INIT_CLASS_INTERNAL(className,parentClass);

#define SO_AUDITOR_EXIT_CLASS(className) \
  SoType::removeType(SO__QUOTE(className))

#define ADD_MESSAGE_FIELD(field) \
  message += "\n\t\t -> "; \
  message += #field; \
  message += " \""; \
  message += cpt->field.getValue(); \
  message += "\""

#define NEW_MESSAGE_GROUP(className) \
  SbString message = "WARNING ! The DialogAuditor does not define the "; \
  message += #className; \
  message += " component :"

#define NEW_MESSAGE_AUDITOR(className) \
  SbString message = "WARNING ! Auditor not defined for the "; \
  message += #className; \
  message += " component :"; \
  ADD_MESSAGE_FIELD(auditorID)

#endif /* _SO_SUB_AUDITOR_ */

