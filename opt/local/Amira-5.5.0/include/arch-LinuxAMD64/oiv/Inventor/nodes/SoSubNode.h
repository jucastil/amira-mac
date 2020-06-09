/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
** Modified by : Ronen Barzel (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_SUB_NODE_
#define  _SO_SUB_NODE_

#include <Inventor/errors/SoDebugError.h>
#include <Inventor/fields/SoFieldData.h>
#include <Inventor/threads/SbThreadLocalStorage.h>
#include <Inventor/threads/SbThreadMutex.h>
#if defined(_DEBUG)
#include <Inventor/SoDB.h>
#endif

//  *** note: many of the macros use the "do { ... } while(0)"
//  ***       hack to define multiline blocks as a single statement
//  ***       of code that can be used anywhere and ended with a semicolon

///////////////////////////////////////////////////////////
//
//  Debugging macros (used by other macros in this file)
//
#if defined(_DEBUG)
#define SO__NODE_CHECK_INIT(className) { \
  if (classTypeId.isBad()) { \
    SoDebugError::post("SO_NODE_CONSTRUCTOR", \
                       "Can't construct a node of type " \
                       SO__QUOTE(className) \
                       " until initClass() has been called"); \
    className::initClass(); \
  } \
  SoDB::checkDatabase(SO__QUOTE(className), this, className::getClassTypeId(), classTypeId); \
}

#define SO__NODE_CHECK_CONSTRUCT(where) { \
  if (fieldData == NULL) { \
    SoDebugError::post(where, \
                       "Instance not properly constructed.\n" \
                       "Did you forget to put SO_NODE_CONSTRUCTOR()" \
                       " in the constructor?"); \
    fieldData = new SoFieldData(parentFieldData ? *parentFieldData : NULL); \
  } \
}

#else
#define SO__NODE_CHECK_INIT(className) { \
  if (classTypeId.isBad()) { \
    className::initClass(); \
  } \
}

#define SO__NODE_CHECK_CONSTRUCT(where) { \
  if (fieldData == NULL) { \
    fieldData = new SoFieldData(parentFieldData ? *parentFieldData : NULL); \
  } \
}
#endif

/////////////////////////////////////////////////////////////////////////////
//
// Macros to be called within the class definition header for a node
// subclass:
//

////////////////////////////////////////////
//
// These defines type-identifier and naming variables and methods that
// all subclasses and abstract subclasses must support.
//

#define SO_NODE_ABSTRACT_HEADER(className) \
  public: \
    /** Returns the type identifier for this class.  */ \
    static  SoType getClassTypeId();        \
    /** Returns the type identifier for this specific instance. */ \
    virtual SoType getTypeId() const;     \
  SoINTERNAL public: \
    virtual SbBool getIsBuiltIn() const ;                              \
    virtual const SoFieldData   *getFieldData() const; \
  protected: \
    static const SoFieldData **getFieldDataPtr(); \
  private: \
    static  SbThreadMutex classMutex;               \
    static  SoType classTypeId;       /* Type id */ \
    static  SbBool isBuiltIn; \
    static  SbBool firstInstance;     /* true until 2nd c'tor call */ \
    static  SoFieldData         *fieldData; \
    static  const SoFieldData   **parentFieldData

//
// Non-abstract classes have everything abstract classes have, plus a way
// to create an instance
//
#define SO_NODE_HEADER(className) \
    SO_NODE_ABSTRACT_HEADER(className); \
    static void *createInstance(SoType* dynamicType = NULL)

/////////////////////////////////////////////////////////////////////////////
//
// Macros to be called within the source file for a node subclass:
//

////////////////////////////////////////////
//
// This declares the static variables defined in SO_NODE_HEADER
// or SO_NODE_ABSTRACT_HEADER.
//

#define SO__NODE_ABSTRACT_VARS(className)                  \
    SbThreadMutex className::classMutex;                   \
    SoType className::classTypeId;                         \
    SbBool className::isBuiltIn = FALSE;                   \
    SoFieldData *className::fieldData = NULL;              \
    const SoFieldData **className::parentFieldData = NULL; \
    SbBool className::firstInstance = TRUE;

//
// Non-abstract nodes have all the stuff abstract nodes do
//
#define SO__NODE_VARS(className) \
    SO__NODE_ABSTRACT_VARS(className)

////////////////////////////////////////////
//
// Methods on the abstract type
//

#define SO__NODE_ABSTRACT_METHODS(className) \
 \
    SoType       \
    className::getTypeId() const         \
    { \
        return classTypeId; \
    } \
 \
    const SoFieldData * \
    className::getFieldData() const      \
    { \
    classMutex.lock(); \
        SO__NODE_CHECK_CONSTRUCT(SO__QUOTE(className)); \
        SoFieldData * result = fieldData; \
        classMutex.unlock(); \
        return result; \
    } \
 \
    SoType className::getClassTypeId() \
    { \
      return classTypeId; \
    } \
 \
    SbBool className::getIsBuiltIn() const \
    { \
      return isBuiltIn; \
    } \
 \
    const SoFieldData **className::getFieldDataPtr() \
    { \
      classMutex.lock(); \
      const SoFieldData **result = (const SoFieldData **)&fieldData; \
      classMutex.unlock(); \
      return result; \
    }

////////////////////////////////////////////
//
// These implement the methods defined in SO_NODE_HEADER or
// SO_NODE_ABSTRACT_HEADER.
//

#define SO__NODE_METHODS(className) \
 \
    SO__NODE_ABSTRACT_METHODS(className) \
 \
    void * \
    className::createInstance(SoType *) \
    { \
        return (void *)(new className); \
    }



/////////////////////////////////////////////
//
// These include all the definitions required
// at file scope
//

#define SO_NODE_SOURCE(className) \
    SO__NODE_VARS(className); \
    SO__NODE_METHODS(className)

#define SO_NODE_ABSTRACT_SOURCE(className) \
    SO__NODE_ABSTRACT_VARS(className); \
    SO__NODE_ABSTRACT_METHODS(className)


///////////////////////////////////////////////////////////
//
//  Internal initialization macros
//

#if defined(_DEBUG)
#define SO_NODE_INIT_CLASS_CHECK_PARENT(className, parentClass) \
  if (parentClass::getClassTypeId().isBad()) {                  \
    SoDebugError::post( SO__QUOTE(className)"::initClass",      \
      SO__QUOTE(className)" initialized before parent class " \
      SO__QUOTE(parentClass)"\n");                              \
    parentClass::initClass();                                   \
  }
#else
#define SO_NODE_INIT_CLASS_CHECK_PARENT(className, parentClass) \
  if (parentClass::getClassTypeId().isBad())                    \
    parentClass::initClass()
#endif

#define SO__NODE_INIT_CLASS_INTERNAL(className,classPrintName,parentClass) \
  classMutex.lock(); \
  SO_NODE_INIT_CLASS_CHECK_PARENT(className, parentClass); \
  classTypeId = SoType::createType( parentClass::getClassTypeId(), \
                                    classPrintName, \
                                    &className::createInstance, \
                                    (short)SoNode::getNextActionMethodIndex()); \
  if (parentFieldData == NULL) \
    SoNode::incNextActionMethodIndex(); \
  parentFieldData = parentClass::getFieldDataPtr(); \
  classMutex.unlock();

#define SO__NODE_INIT_CLASS(className,classPrintName,parentClass) \
  SO__NODE_INIT_CLASS_INTERNAL(className,classPrintName,parentClass)

#define SO__NODE_INIT_ABSTRACT_CLASS_INTERNAL(className,classPrintName,parentClass) \
  classMutex.lock(); \
  SO_NODE_INIT_CLASS_CHECK_PARENT(className, parentClass); \
  classTypeId = SoType::createType( parentClass::getClassTypeId(), \
                                    classPrintName, \
                                    NULL, \
                                    (short)SoNode::getNextActionMethodIndex()); \
  if (parentFieldData == NULL) \
    SoNode::incNextActionMethodIndex(); \
  parentFieldData = parentClass::getFieldDataPtr(); \
  classMutex.unlock();

#define SO__NODE_INIT_ABSTRACT_CLASS(className,classPrintName,parentClass) \
  SO__NODE_INIT_ABSTRACT_CLASS_INTERNAL(className,classPrintName,parentClass)

#if defined(_DEBUG)
#define SO__NODE_EXIT_CLASS(className) \
  if (! SoType::removeType(classTypeId.getName())) { \
    SoDebugError::post(SO__QUOTE(className)"::exitClass", \
                       "Unable to remove type (%s) for this class. Check exitClass() " \
                       "method is implemented and is called only once.\n", \
                       classTypeId.getName().getString() ); \
  } \
  else \
  { \
    classTypeId = SoType::badType(); \
    if (fieldData != NULL) \
    { \
      delete fieldData; \
      fieldData = NULL; \
    } \
    parentFieldData = NULL; \
    firstInstance = TRUE; \
  }
#else
#define SO__NODE_EXIT_CLASS(className) \
  SoType::removeType(classTypeId.getName()); \
  classTypeId = SoType::badType(); \
  if (fieldData != NULL) \
  { \
    delete fieldData; \
    fieldData = NULL; \
  } \
  parentFieldData = NULL; \
  firstInstance = TRUE
#endif

////////////////////////////////////////////
//
// This requests allocation of thread local storage. This macro
// should be called within initClass(). The structName argument
// should be the structure (the type name) defining what size
// of memory should be allocated for each thread, for this class
//
// LOCAL_THREAD_VAR gives access to the thread local storage
// variable. _structName_ should be the same as structName, and
// _varName_ should be a type declared within structName.
// Note that LOCAL_THREAD_VAR should not be called before the
// thread local storage has been initialized (see SoDB::threadInit)
//
// KEEP FOR COMPATIBILITY... Macros have been moved to SoTLS.h
#define SO_THREAD_NODE_INIT_CLASS(className,structName) \
  \
  SB_THREAD_INIT_CLASS(className,structName)

#define SO_THREAD_NODE_EXIT_CLASS(className) \
  \
  SB_THREAD_EXIT_CLASS(className)

#define LOCAL_THREAD_VAR(_className_, _structName_, _varName_) \
  \
  GET_THREAD_LOCAL_VAR(_className_, _structName_, _varName_)

#define LOCAL_THREAD_STORAGE(_className_) \
  \
  GET_THREAD_LOCAL_STORAGE(_className_)


////////////////////////////////////////////
//
// This initializes the type identifer variables defined in
// SO_NODE_HEADER or SO_NODE_ABSTRACT_HEADER. This macro
// should be called from within initClass(). The parentClass argument
// should be the class that this subclass is derived from.
//
#define SO_NODE_INIT_CLASS_INTERNAL(className,parentClass,parentPrintClass) \
  classMutex.lock(); \
  SO_NODE_INIT_CLASS_CHECK_PARENT(className, parentClass); \
  classTypeId = SoType::createType( SoType::fromName(parentPrintClass), \
                                    SO__QUOTE(className), \
                                    &className::createInstance, \
                                    (short)SoNode::getNextActionMethodIndex()); \
  if (parentFieldData == NULL) \
    SoNode::incNextActionMethodIndex(); \
  parentFieldData = parentClass::getFieldDataPtr(); \
  classMutex.unlock();

#define SO_NODE_INIT_CLASS(className,parentClass,parentPrintClass) \
  \
  SO_NODE_INIT_CLASS_INTERNAL(className,parentClass,parentPrintClass)

#define SO_NODE_INIT_ABSTRACT_CLASS_INTERNAL(className, parentClass, parentPrintClass) \
  classMutex.lock(); \
  SO_NODE_INIT_CLASS_CHECK_PARENT(className, parentClass); \
  classTypeId = SoType::createType( SoType::fromName(parentPrintClass), \
                                    SO__QUOTE(className), \
                                    NULL, \
                                    (short)SoNode::getNextActionMethodIndex()); \
  if (parentFieldData == NULL) \
    SoNode::incNextActionMethodIndex(); \
  parentFieldData = parentClass::getFieldDataPtr(); \
  classMutex.unlock();

#define SO_NODE_INIT_ABSTRACT_CLASS(className, parentClass, parentPrintClass) \
  \
  SO_NODE_INIT_ABSTRACT_CLASS_INTERNAL(className,parentClass,parentPrintClass)

/**
 * This is included at the beginning of
 * a constructor, to do required initializations
 */
#define SO_NODE_CONSTRUCTOR(className) \
  SoBaseInitializer sbi(this); \
  classMutex.lock(); \
  SO__NODE_CHECK_INIT(className); \
  if (fieldData == NULL) \
    fieldData = new SoFieldData(parentFieldData ? \
                      (SoFieldData *)*parentFieldData : \
                      (SoFieldData *)NULL); \
  else \
    firstInstance = FALSE; \
  classMutex.unlock()


/**
 * Boolean check that can be used in constructors.
 */
#define SO_NODE_IS_FIRST_INSTANCE() \
  \
    (firstInstance == TRUE)



/**
 * This adds the info for a field to the SoFieldData and sets the
 * default value for it. The parameters are as follows:
 *      fieldName:      the name of the field (as a member)
 *      defValue:       the default value enclosed in parentheses
 *
 * For example,
 *
 *      SO_NODE_ADD_FIELD(ambientColor, (0.2, 0.2, 0.2));
 *      SO_NODE_ADD_FIELD(shininess,    (0.0));
 *
 * adds info about fields named ambientColor and shininess with the
 * given default values.
 */

#if defined(_DEBUG)
// In fact it is allowed to initialize a MField with a single value with this macro...
#define CHECK_FIELD_INIT(fieldName) /*\
  if ( dynamic_cast<SoMField*>(&this->fieldName) != NULL) \
    SoDebugError::post("SO_NODE_ADD_FIELD","Used for a SoMField.")*/

#define CHECK_MFIELD_INIT(fieldName) \
  if ( dynamic_cast<SoSField*>(&this->fieldName) != NULL) \
    SoDebugError::post("SO_NODE_ADD_MFIELD","Used for a SoSFField.")
#else
#define CHECK_FIELD_INIT(fieldName)
#define CHECK_MFIELD_INIT(fieldName)
#endif

#define SO_NODE_ADD_FIELD(fieldName,defValue) { \
  classMutex.lock(); \
  SO__NODE_CHECK_CONSTRUCT(__FILE__); \
  if (firstInstance) \
    fieldData->addField(this, SO__QUOTE(fieldName), \
                        &this->fieldName); \
  this->fieldName.setValue defValue; \
  this->fieldName.setContainer(this); \
  this->fieldName.setFieldType(5); \
  CHECK_FIELD_INIT(fieldName); \
  classMutex.unlock(); \
}

/////////////////////////////////////////////////
// Same as above but the fieldName is chosen by
// the user
//

#define SO_NODE_ADD_NAMED_FIELD(fieldName,memberName,defValue) {        \
  classMutex.lock(); \
  SO__NODE_CHECK_CONSTRUCT(__FILE__); \
  if (firstInstance) \
    fieldData->addField(this, SO__QUOTE(fieldName), \
                        &this->memberName); \
  this->memberName.setValue defValue; \
  this->memberName.setContainer(this); \
  this->memberName.setFieldType(5); \
  classMutex.unlock(); \
}

////////////////////////////////////////////
//
// This adds the info for a multifield to the SoFieldData.
// The multifield is left empty.
// The parameter is as follows:
//      fieldName:      the name of the field (as a member)
//
// For example,
//
//      SO_NODE_ADD_MFIELD(ambientColor)
//      SO_NODE_ADD_MFIELD(shininess)
//
// adds info about fields named ambientColor and shininess with the
// given default values.
//

#define SO_NODE_ADD_MFIELD(fieldName) { \
  classMutex.lock(); \
  SO__NODE_CHECK_CONSTRUCT(__FILE__); \
  if (firstInstance) \
    fieldData->addField(this, SO__QUOTE(fieldName), \
                        &this->fieldName); \
  this->fieldName.setContainer(this); \
  this->fieldName.setFieldType(5); \
  CHECK_MFIELD_INIT(fieldName); \
  classMutex.unlock(); \
}

////////////////////////////////////////////
//
// This adds the info for a VRML field to the SoFieldData and sets the
// default value for it. The parameters are as follows:
//      fieldName:      the name of the field (as a member)
//      defValue:       the default value enclosed in parentheses
//
// For example,
//
//      SO_NODE_ADD_PRIVATEFIELD(ambientColor, (0.2, 0.2, 0.2));
//      SO_NODE_ADD_PRIVATEFIELD(shininess,    (0.0));
//
// adds info about fields named ambientColor and shininess with the
// given default values.
//

#define SO_NODE_ADD_PRIVATEFIELD(fieldName,defValue) { \
  classMutex.lock(); \
  SO__NODE_CHECK_CONSTRUCT(__FILE__); \
  if (firstInstance) \
    fieldData->addField(this, SO__QUOTE(fieldName), \
                        &this->fieldName); \
  this->fieldName.setValue defValue; \
  this->fieldName.setContainer(this); \
  this->fieldName.setFieldType(0); \
  classMutex.unlock(); \
}

////////////////////////////////////////////
//
// This adds the info for a VRML field to the SoFieldData and sets the
// default value for it. The parameters are as follows:
//      fieldName:      the name of the field (as a member)
//      defValue:       the default value enclosed in parentheses
//
// For example,
//
//      SO_NODE_ADD_PRIVATEMFIELD(ambientColor);
//      SO_NODE_ADD_PRIVATEMFIELD(shininess);
//
// adds info about fields named ambientColor and shininess with the
// given default values.
//

#define SO_NODE_ADD_PRIVATEMFIELD(fieldName) { \
  classMutex.lock(); \
  SO__NODE_CHECK_CONSTRUCT(__FILE__); \
  if (firstInstance) \
    fieldData->addField(this, SO__QUOTE(fieldName), \
                        &this->fieldName); \
  this->fieldName.setContainer(this); \
  this->fieldName.setFieldType(0); \
  classMutex.unlock(); \
}

////////////////////////////////////////////
//
// This adds the info for an exposedField to the SoFieldData and sets the
// default value for it. The parameters are as follows:
//      fieldName:      the name of the exposedField (as a member)
//      defValue:       the default value enclosed in parentheses
// Exposed fields are in the VRML2 nodes. If a field is an exposedField
// there is a corresponding eventIn and eventOut for the field. For
// examples, if the exposedField is foo, there is a set_foo eventIn and
// a foo_changed eventOut.
//
// For example,
//
//      SO_NODE_ADD_EXPOSEDFIELD(ambientIntensity, (0));
//
// adds info about the exposedField named ambientIntensity with the
// given default values.
//

#define SO_NODE_ADD_EXPOSEDFIELD(fieldName,defValue) { \
  classMutex.lock(); \
  SO__NODE_CHECK_CONSTRUCT(__FILE__); \
  if (firstInstance) \
    fieldData->addField(this, SO__QUOTE(fieldName), \
                        &this->fieldName); \
  this->fieldName.setValue defValue; \
  this->fieldName.setContainer(this); \
  this->fieldName.setFieldType(5); \
  classMutex.unlock(); \
}

////////////////////////////////////////////
//
// This adds the info for an eventIn field to the SoFieldData
// The parameter is:
//      fieldName:      the name of the eventIn field (as a member)
//
// For example,
//
//      SO_NODE_ADD_EVENTIN(set_fraction);
//
// adds info about the eventIn set_fraction
//

#define SO_NODE_ADD_EVENTIN(fieldName) { \
  classMutex.lock(); \
  SO__NODE_CHECK_CONSTRUCT(__FILE__); \
  if (firstInstance) \
    fieldData->addField(this, SO__QUOTE(fieldName), \
                        &this->fieldName); \
  this->fieldName.setContainer(this); \
  this->fieldName.setFieldType(1); \
  classMutex.unlock(); \
}

////////////////////////////////////////////
//
// This adds the info for an eventOut field to the SoFieldData
// The parameter is:
//      fieldName:      the name of the eventOut field (as a member)
//
// For example,
//
//      SO_NODE_ADD_EVENTOUT(value_changed, defValue);
//
// adds info about the eventOut value_changed
//

#define SO_NODE_ADD_EVENTOUT(fieldName, defValue) { \
  classMutex.lock(); \
  SO__NODE_CHECK_CONSTRUCT(__FILE__); \
  if (firstInstance) \
    fieldData->addField(this, SO__QUOTE(fieldName), \
                        &this->fieldName); \
  this->fieldName.setValue defValue; \
  this->fieldName.setContainer(this); \
  this->fieldName.setFieldType(2); \
  classMutex.unlock(); \
}

////////////////////////////////////////////
//
// This adds the info for a hidden field to the SoFieldData
// The parameter is:
//      fieldName:      the name of the hidden field (as a member)
//
// For example,
//
//      SO_NODE_ADD_HIDDEN_FIELD(timeIn, defValue);
//
// adds info about the hidden field timeIn
//

#define SO_NODE_ADD_HIDDEN_FIELD(fieldName, defValue) { \
  classMutex.lock(); \
  SO__NODE_CHECK_CONSTRUCT(__FILE__); \
  if (firstInstance) \
    fieldData->addField(this, SO__QUOTE(fieldName), \
                        &this->fieldName); \
  this->fieldName.setValue defValue; \
  this->fieldName.setContainer(this); \
  this->fieldName.setFieldType(4); \
  classMutex.unlock(); \
}

////////////////////////////////////////////
//
// This adds the info for a field with an eventIn to the SoFieldData
// The parameter is:
//      fieldName:      the name of the eventIn and field (as a member)
//
// For example,
//
//      SO_NODE_ADD_FIELD_EVENTIN(colorIndex, 0);
//

#define SO_NODE_ADD_FIELD_EVENTIN(fieldName, defValue) { \
  classMutex.lock(); \
  SO__NODE_CHECK_CONSTRUCT(__FILE__); \
  if (firstInstance) \
    fieldData->addField(this, SO__QUOTE(fieldName), \
                        &this->fieldName); \
  this->fieldName.setValue defValue; \
  this->fieldName.setContainer(this); \
  this->fieldName.setFieldType(3); \
  classMutex.unlock(); \
}

////////////////////////////////////////////
//
// This registers a value of an enum type.
//      enumType:       the name of the enum type
//      enumValue:      the name of a value of that enum type
//
// If a node defines an enum, each of the enum's values
// should be registered using this macro.  For example:
//
//    [ in MyNode.h file: ]
//      class MyNode {
//        ...
//      enum Chipmunk { ALVIN, SIMON, THEODORE };
//              ...
//      }
//
//    [ in constructor MyNode::MyNode(): ]
//      SO_NODE_DEFINE_ENUM_VALUE(Chipmunk, ALVIN);
//      SO_NODE_DEFINE_ENUM_VALUE(Chipmunk, SIMON);
//      SO_NODE_DEFINE_ENUM_VALUE(Chipmunk, THEODORE);
//

#define SO_NODE_DEFINE_ENUM_VALUE(enumType,enumValue) { \
  classMutex.lock(); \
  SO__NODE_CHECK_CONSTRUCT(__FILE__); \
  if (firstInstance) \
    fieldData->addEnumValue(SO__QUOTE(enumType), \
                            SO__QUOTE(enumValue), \
                            enumValue); \
  classMutex.unlock(); \
}

////////////////////////////////////////////
//
// Variant of previous macro. Allows to define a enum with
// values that are holds by an external class.
// This registers a value of an enum type.
//      enumType:         the name of the enum type
//      enumValueName:    the name of a value of that enum type
//      enumValue:        the enum value
//
// If a node defines an enum, each of the enum's values
// should be registered using this macro.  For example:
//
//    [ in MyClassWithEnumValues.h file: ]
//      class MyClassWithEnumValues {
//        ...
//        enum Chipmunk { ALVIN, SIMON, THEODORE };
//        ...
//     };
//
//    [ in constructor MyNode::MyNode(): ]
//      SO_NODE_DEFINE_ENUM_VALUE(Chipmunk, ALVIN, MyClassWithEnumValues::ALVIN);
//      SO_NODE_DEFINE_ENUM_VALUE(Chipmunk, SIMON, MyClassWithEnumValues::SIMON);
//      SO_NODE_DEFINE_ENUM_VALUE(Chipmunk, THEODORE, MyClassWithEnumValues::THEODORE);
//
#define SO__NODE_DEFINE_ENUM_VALUE(enumType,enumValueName,enumValue) { \
  classMutex.lock(); \
  SO__NODE_CHECK_CONSTRUCT(__FILE__); \
  if (firstInstance) \
  fieldData->addEnumValue(SO__QUOTE(enumType), \
                          enumValueName, \
                          enumValue); \
  classMutex.unlock(); \
}

#endif /* _SO_SUB_NODE_ */

