/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Mar 2007)
**=======================================================================*/


#include <Inventor/threads/SbThreadRWMutex.h>
#include <Inventor/fields/SoFieldData.h>

/*************************************************************************/
// SO_VIEWER_ABSTRACT_HEADER(className)
//
// Description :
//   These defines type-identifier and naming variables and methods that
//   all viewers and abstract viewers must support.
//-------------------------------------------------------------------------
#define SO_VIEWER_ABSTRACT_HEADER(className) \
  public: \
    static SoType getClassTypeId(); \
    virtual SoType getTypeId() const; \
  SoINTERNAL public: \
    virtual const SoFieldData* getFieldData() const; \
  protected: \
    static const SoFieldData** getFieldDataPtr(); \
  private: \
    static SbThreadRWMutex *classMutex; \
    static SoType classTypeId; \
    static SbBool firstInstance; \
    static SoFieldData* fieldData; \
    static const SoFieldData** parentFieldData

/*************************************************************************/
// SO_VIEWER_HEADER(className)
//
// Description :
//   Non-abstract classes have everything abstract classes have,
//   plus a way to create an instance.
//-------------------------------------------------------------------------
#define SO_VIEWER_HEADER(className) \
  SO_VIEWER_ABSTRACT_HEADER(className); \
  static void *createInstance(SoType* dynamicType = NULL)

/*************************************************************************/
// SO__VIEWER_ABSTRACT_VARS(className)
//
// Description :
//   This declares the static variables defined in SO_NODE_HEADER
//   or SO_NODE_ABSTRACT_HEADER.
//-------------------------------------------------------------------------
#define SO__VIEWER_ABSTRACT_VARS(className) \
  SbThreadRWMutex* className::classMutex = NULL; \
  SoType className::classTypeId; \
  SoFieldData* className::fieldData = NULL; \
  const SoFieldData** className::parentFieldData = NULL; \
  SbBool className::firstInstance = TRUE;

/*************************************************************************/
// SO__VIEWER_VARS(className)
//
// Description :
//   Non-abstract viewers have all the stuff abstract viewers do.
//-------------------------------------------------------------------------
#define SO__VIEWER_VARS(className) \
  SO__VIEWER_ABSTRACT_VARS(className)

/*************************************************************************/
// SO__VIEWER_ABSTRACT_METHODS(className)
//
// Description :
//   Methods on the abstract type.
//-------------------------------------------------------------------------
#define SO__VIEWER_ABSTRACT_METHODS(className) \
\
  SoType className::getTypeId() const { \
    return classTypeId; \
  } \
\
  const SoFieldData* className::getFieldData() const { \
    classMutex->writelock(); \
    SoFieldData* result = fieldData; \
    classMutex->writeunlock(); \
    return result; \
  } \
\
  SoType className::getClassTypeId() { \
    return classTypeId; \
  } \
\
  const SoFieldData** className::getFieldDataPtr() { \
    classMutex->writelock(); \
    const SoFieldData** result = (const SoFieldData**)&fieldData; \
    classMutex->writeunlock(); \
    return result; \
  }

/*************************************************************************/
// SO__VIEWER_METHODS(className)
//
// Description :
//   These implement the methods defined in SO_VIEWER_HEADER or
//   SO_VIEWER_ABSTRACT_HEADER.
//-------------------------------------------------------------------------
#define SO__VIEWER_METHODS(className) \
\
  SO__VIEWER_ABSTRACT_METHODS(className) \
\
  void* className::createInstance(SoType *dynamicType) { \
    if (dynamicType == NULL) \
      return (void *)(new className); \
    else { \
      className *newInstance = new className; \
      return (void *)newInstance; \
    } \
  }

/*************************************************************************/
// SO_VIEWER_SOURCE(className)
// SO_VIEWER_ABSTRACT_SOURCE(className)
//
// Description :
//   These include all the definitions required
//   at file scope.
//-------------------------------------------------------------------------
#define SO_VIEWER_SOURCE(className) \
  SO__VIEWER_VARS(className); \
  SO__VIEWER_METHODS(className)

#define SO_VIEWER_ABSTRACT_SOURCE(className) \
  SO__VIEWER_ABSTRACT_VARS(className); \
  SO__VIEWER_ABSTRACT_METHODS(className)


/*************************************************************************/
// SO_VIEWER_CONSTRUCTOR(className)
//
// Description :
//-------------------------------------------------------------------------
#define SO_VIEWER_CONSTRUCTOR(className) { \
  if (fieldData == NULL) \
    fieldData = new SoFieldData(parentFieldData ? *parentFieldData : NULL); \
  else \
    firstInstance = FALSE; \
  isBuiltIn = TRUE; \
}

/*************************************************************************/
// SO_VIEWER_ADD_FIELD(className)
//
// Description :
//   This adds the info for a field to the SoFieldData and sets the
//   default value for it. The parameters are as follows:
//      fieldName: the name of the field (as a member)
//      defValue:  the default value enclosed in parentheses
//
//   For example,
//
//      SO_VIEWER_ADD_FIELD(ambientColor, (0.2, 0.2, 0.2));
//      SO_VIEWER_ADD_FIELD(shininess,    (0.0));
//
//   adds info about fields named ambientColor and shininess with the
//   given default values.
//-------------------------------------------------------------------------
#define SO_VIEWER_ADD_FIELD(fieldName,defValue) { \
  classMutex->writelock(); \
  if (firstInstance) \
    fieldData->addField(this, SO__QUOTE(fieldName), &this->fieldName); \
  this->fieldName.setValue defValue; \
  this->fieldName.setContainer(this); \
  this->fieldName.setFieldType(5); \
  classMutex->writeunlock(); \
}

#define SO_VIEWER_INIT_CLASS(className, classPrintName, parentClass) \
  SoDB::writelock(); \
  if (classMutex == NULL) \
    classMutex = new SbThreadRWMutex; \
  SoDB::writeunlock(); \
  classMutex->writelock(); \
  if (classTypeId.isBad()) \
  { \
    classTypeId = SoType::createType( parentClass::getClassTypeId(), \
                                      classPrintName, \
                                      &className::createInstance, \
                                      0 ); \
    parentFieldData = parentClass::getFieldDataPtr(); \
    } \
  classMutex->writeunlock();

#define SO_VIEWER_INIT_ABSTRACT_CLASS(className, classPrintName, parentClass) \
  SoDB::writelock(); \
  if (classMutex == NULL) \
    classMutex = new SbThreadRWMutex; \
  SoDB::writeunlock(); \
  classMutex->writelock(); \
  if (classTypeId.isBad()) \
  { \
    classTypeId = SoType::createType( parentClass::getClassTypeId(), \
                                      classPrintName, \
                                      NULL, \
                                      0 ); \
    parentFieldData = parentClass::getFieldDataPtr(); \
  } \
  classMutex->writeunlock();

/**/
