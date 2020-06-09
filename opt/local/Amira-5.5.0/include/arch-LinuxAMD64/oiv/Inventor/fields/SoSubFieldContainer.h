/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Aug 2007)
**=======================================================================*/


#ifndef SO_SUB_FIELDCONTAINER_H
#define SO_SUB_FIELDCONTAINER_H

#include <Inventor/threads/SbThreadMutex.h>
#include <Inventor/fields/SoFieldData.h>

//////////////////////////////////////////////////////////////////////////////////////
// These defines type-identifier and naming variables and methods that
// all subclasses and abstract subclasses must support.
//
#define SO_FIELDCONTAINER_ABSTRACT_HEADER(className)                                  \
  public:                                                                             \
    /** Returns the type identifier for this class.  */                               \
    static SoType getClassTypeId();                                                   \
    /** Returns the type identifier for this specific instance. */                    \
    virtual SoType getTypeId() const;                                                 \
  SoINTERNAL public:                                                                  \
    virtual SbBool getIsBuiltIn() const ;                                             \
    virtual const SoFieldData* getFieldData() const;                                  \
    static void initClass();                                                          \
    static void exitClass();                                                          \
  protected:                                                                          \
    static const SoFieldData** getFieldDataPtr();                                     \
  private:                                                                            \
    static SbThreadMutex classMutex;                                                  \
    static SoType classTypeId;                                                        \
    static SbBool isBuiltIn;                                                          \
    static SbBool firstInstance;                                                      \
    static SoFieldData* fieldData;                                                    \
    static const SoFieldData** parentFieldData

//////////////////////////////////////////////////////////////////////////////////////
// Non-abstract classes have everything abstract classes have, plus a way
// to create an instance
//
#define SO_FIELDCONTAINER_HEADER(className)                                           \
  SO_FIELDCONTAINER_ABSTRACT_HEADER(className);                                       \
SoINTERNAL public:                                                                    \
  static void* createInstance(SoType* dynamicType = NULL)

#if defined(_DEBUG)

//////////////////////////////////////////////////////////////////////////////////////
#define SO__FIELDCONTAINER_CHECK_INIT(className)                                      \
  if (classTypeId.isBad())                                                            \
  {                                                                                   \
    SoDebugError::post(                                                               \
      "SO_FIELDCONTAINER_CONSTRUCTOR",                                                \
      "Can't construct a node of type "                                               \
      SO__QUOTE(className)                                                            \
      " until initClass() has been called");                                          \
    className::initClass();                                                           \
  } \
  SoDB::checkDatabase(SO__QUOTE(className), this, className::getClassTypeId(), classTypeId);

//////////////////////////////////////////////////////////////////////////////////////
#define SO__FIELDCONTAINER_CHECK_CONSTRUCT(where)                                     \
  if (fieldData == NULL)                                                              \
  {                                                                                   \
    SoDebugError::post(                                                               \
      where,                                                                          \
      "Instance not properly constructed.\n"                                          \
      "Did you forget to put SO_FIELDCONTAINER_CONSTRUCTOR()"                         \
      " in the constructor?" );                                                       \
    fieldData = new SoFieldData(                                                      \
      parentFieldData ? *parentFieldData : NULL);                                     \
  }

#else

//////////////////////////////////////////////////////////////////////////////////////
#define SO__FIELDCONTAINER_CHECK_INIT(className)                                      \
  if (classTypeId.isBad())                                                            \
    className::initClass()

//////////////////////////////////////////////////////////////////////////////////////
#define SO__FIELDCONTAINER_CHECK_CONSTRUCT(where)                                     \
  if (fieldData == NULL)                                                              \
    fieldData = new SoFieldData(                                                      \
      parentFieldData ? *parentFieldData : NULL)

#endif

//////////////////////////////////////////////////////////////////////////////////////
// This declares the static variables defined in SO_FIELDCONTAINER_HEADER
// or SO_FIELDCONTAINER_ABSTRACT_HEADER.
//
#define SO__FIELDCONTAINER_VARS(className)                                            \
  SbThreadMutex className::classMutex;                                                \
  SoType className::classTypeId;                                                      \
  SbBool className::isBuiltIn = TRUE;                                                 \
  SoFieldData* className::fieldData = NULL;                                           \
  const SoFieldData** className::parentFieldData = NULL;                              \
  SbBool className::firstInstance = TRUE

//////////////////////////////////////////////////////////////////////////////////////
#define SO_FIELDCONTAINER_ABSTRACT_SOURCE(className)                                  \
  SO__FIELDCONTAINER_VARS(className);                                                 \
  SoType className::getTypeId() const                                                 \
  {                                                                                   \
    return classTypeId;                                                               \
  }                                                                                   \
                                                                                      \
  const SoFieldData* className::getFieldData() const                                  \
  {                                                                                   \
    classMutex.lock();                                                                \
    SO__FIELDCONTAINER_CHECK_CONSTRUCT(SO__QUOTE(className));                         \
    SoFieldData* result = fieldData;                                                  \
    classMutex.unlock();                                                              \
    return result;                                                                    \
  }                                                                                   \
                                                                                      \
  SoType className::getClassTypeId()                                                  \
  {                                                                                   \
    return classTypeId;                                                               \
  }                                                                                   \
                                                                                      \
  SbBool className::getIsBuiltIn() const                                              \
  {                                                                                   \
    return isBuiltIn;                                                                 \
  }                                                                                   \
                                                                                      \
  const SoFieldData** className::getFieldDataPtr()                                    \
  {                                                                                   \
    classMutex.lock();                                                                \
    const SoFieldData** result = (const SoFieldData**)&fieldData;                     \
    classMutex.unlock();                                                              \
    return result;                                                                    \
  }

//////////////////////////////////////////////////////////////////////////////////////
#define SO_FIELDCONTAINER_SOURCE(className)                                           \
  SO_FIELDCONTAINER_ABSTRACT_SOURCE(className);                                       \
                                                                                      \
  void* className::createInstance(SoType* )                                           \
  {                                                                                   \
    return (void *)(new className);                                                   \
  }

#if defined(_DEBUG)
#define SO_FIELDCONTAINER_INIT_CLASS_CHECK_PARENT(className, parentClass)                   \
  if (parentClass::getClassTypeId().isBad()) {                                        \
    SoDebugError::post( SO__QUOTE(className)"::initClass",                            \
      SO__QUOTE(className)" initialized before parent class " \
      SO__QUOTE(parentClass)"\n");                                                    \
    parentClass::initClass();                                                         \
  }
#else
#define SO_FIELDCONTAINER_INIT_CLASS_CHECK_PARENT(className, parentClass)                   \
  if (parentClass::getClassTypeId().isBad())                                          \
    parentClass::initClass()
#endif

//////////////////////////////////////////////////////////////////////////////////////
// This initializes the type identifer variables defined in
// SO_FIELDCONTAINER_HEADER or SO_FIELDCONTAINER_ABSTRACT_HEADER. This macro
// should be called from within initClass(). The parentClass argument
// should be the class that this subclass is derived from.
//
#define SO_FIELDCONTAINER_INIT_CLASS(className, classPrintName, parentClass)          \
  classMutex.lock();                                                                  \
  SO_FIELDCONTAINER_INIT_CLASS_CHECK_PARENT(className, parentClass);                        \
  classTypeId = SoType::createType( parentClass::getClassTypeId(),                    \
                                    classPrintName,                                   \
                                    &className::createInstance, 0 );                  \
  parentFieldData = parentClass::getFieldDataPtr();                                   \
  classMutex.unlock()

//////////////////////////////////////////////////////////////////////////////////////
#define SO_FIELDCONTAINER_INIT_ABSTRACT_CLASS(className, classPrintName, parentClass) \
  classMutex.lock();                                                                  \
  SO_FIELDCONTAINER_INIT_CLASS_CHECK_PARENT(className, parentClass);                        \
  classTypeId = SoType::createType( parentClass::getClassTypeId(),                    \
                                    classPrintName,                                   \
                                    NULL, 0 );                                        \
  parentFieldData = parentClass::getFieldDataPtr();                                   \
  classMutex.unlock()

#if defined(_DEBUG)
#define SO__FIELDCONTAINER_EXIT_CLASS(className) \
  if (! SoType::removeType(classTypeId.getName())) { \
    SoDebugError::post(SO__QUOTE(className)"::exitClass", \
                       "Unable to remove type (%s) for this class. Check exitClass() " \
                       "method is implemented and is called only once.\n", \
                       classTypeId.getName().getString() ); \
  } \
  else \
  { \
    classTypeId = SoType::badType();                                                    \
	  firstInstance = TRUE;                                                               \
    if (fieldData != NULL)                                                              \
    {                                                                                   \
      delete fieldData;                                                                 \
      fieldData = NULL;                                                                 \
    }                                                                                   \
    parentFieldData = NULL;                                                             \
    firstInstance = TRUE;                                                               \
  }
#else
#define SO__FIELDCONTAINER_EXIT_CLASS(className)                                      \
  SoType::removeType(classTypeId.getName());                                          \
  classTypeId = SoType::badType();                                                    \
	firstInstance = TRUE;                                                               \
  if (fieldData != NULL)                                                              \
  {                                                                                   \
    delete fieldData;                                                                 \
    fieldData = NULL;                                                                 \
  }                                                                                   \
  parentFieldData = NULL;                                                             \
  firstInstance = TRUE
#endif

//////////////////////////////////////////////////////////////////////////////////////
// This is a boolean value that can be tested
// in constructors.
//
#define SO_FIELDCONTAINER_IS_FIRST_INSTANCE()                                         \
  (firstInstance == TRUE)


//////////////////////////////////////////////////////////////////////////////////////
#define SO__FIELDCONTAINER_ADD_FIELD( fieldName, defValue, type )                     \
  classMutex.lock();                                                                  \
  SO__FIELDCONTAINER_CHECK_CONSTRUCT(__FILE__);                                       \
  if (firstInstance)                                                                  \
    fieldData->addField(this, SO__QUOTE(fieldName), &this->fieldName);                \
  this->fieldName.setValue defValue;                                                  \
  this->fieldName.setContainer(this);                                                 \
  this->fieldName.setFieldType(type);                                                 \
  classMutex.unlock()

//////////////////////////////////////////////////////////////////////////////////////
#define SO_FIELDCONTAINER_ADD_FIELD( fieldName, defValue )                            \
  SO__FIELDCONTAINER_ADD_FIELD( fieldName, defValue, 5 )

//////////////////////////////////////////////////////////////////////////////////////
#define SO_FIELDCONTAINER_ADD_HIDDEN_FIELD( fieldName, defValue )                     \
  SO__FIELDCONTAINER_ADD_FIELD( fieldName, defValue, 4 )

//////////////////////////////////////////////////////////////////////////////////////
#define SO_FIELDCONTAINER_ADD_PRIVATEFIELD( fieldName, defValue )                     \
  SO__FIELDCONTAINER_ADD_FIELD( fieldName, defValue, 0 )

//////////////////////////////////////////////////////////////////////////////////////
#define SO_FIELDCONTAINER_SET_SF_ENUM_TYPE( fieldName, enumType )                     \
  SO__SF_ENUM_SET_TYPE( fieldName, enumType, "FIELDCONTAINER", fieldData )

//////////////////////////////////////////////////////////////////////////////////////
#define SO_FIELDCONTAINER_CONSTRUCTOR(className)                                      \
  SoBaseInitializer sbi(this);                                                        \
  classMutex.lock();                                                                  \
  SO__FIELDCONTAINER_CHECK_INIT(className);                                           \
  if (fieldData == NULL)                                                              \
    fieldData = new SoFieldData( parentFieldData ?                                    \
                                 (SoFieldData *)*parentFieldData :                    \
                                 (SoFieldData *)NULL);                                \
  else                                                                                \
    firstInstance = FALSE;                                                            \
  classMutex.unlock()

//////////////////////////////////////////////////////////////////////////////////////
#define SO__FIELDCONTAINER_DEFINE_ENUM_VALUE( enumType, enumValueName, enumValue )    \
  classMutex.lock();                                                                  \
  if (firstInstance)                                                                  \
    fieldData->addEnumValue(SO__QUOTE(enumType),                                      \
                            SO__QUOTE(enumValueName),                                 \
                            enumValue);                                               \
  classMutex.unlock()

//////////////////////////////////////////////////////////////////////////////////////
#define SO_FIELDCONTAINER_DEFINE_ENUM_VALUE( enumType, enumValue )                    \
  SO__FIELDCONTAINER_DEFINE_ENUM_VALUE( enumType, enumValue, enumValue )

#endif // SO_SUB_FIELDCONTAINER_H

/**/
