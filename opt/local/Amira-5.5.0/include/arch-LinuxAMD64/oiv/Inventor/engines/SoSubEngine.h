/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_SUB_ENGINE_
#define  _SO_SUB_ENGINE_

#include <Inventor/engines/SoEngine.h>
#include <Inventor/engines/SoOutputData.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/fields/SoFieldData.h>


///////////////////////
//
// Debugging macros called by other macros in this file
//
#if defined(_DEBUG)
#define SO__ENGINE_CHECK_INIT(className) {                              \
  if (classTypeId.isBad()) {                                            \
    SoDebugError::post("SO_ENGINE_CONSTRUCTOR",                         \
                       "Can't construct an engine of type "             \
                       SO__QUOTE(className)                             \
                       " until initClass() has been called");           \
      className::initClass();                                           \
  } \
  SoDB::checkDatabase(SO__QUOTE(className), this, className::getClassTypeId(), classTypeId); \
}

#define SO__ENGINE_CHECK_CONSTRUCT(where)                             \
  if (inputData == NULL) {                                            \
    SoDebugError::post(where,                                         \
                       "Instance not properly constructed.\n"         \
                       "Did you forget to put "                       \
                       "SO_ENGINE_CONSTRUCTOR()"                      \
                       " in the constructor?");                       \
    inputData = new SoFieldData(parentInputData ?                     \
                                *parentInputData : NULL);             \
    outputData = new SoEngineOutputData(parentOutputData ?            \
                                        *parentOutputData : NULL);    \
  }

#else
#define SO__ENGINE_CHECK_INIT(className)   \
  if (classTypeId.isBad()) {  \
    className::initClass();                \
  }

#define SO__ENGINE_CHECK_CONSTRUCT(where)  \
  if (inputData == NULL) {                 \
    inputData = new SoFieldData(parentInputData ? *parentInputData : NULL);             \
    outputData = new SoEngineOutputData(parentOutputData ? *parentOutputData : NULL);   \
  }
#endif

/////////////////////////////////////////////////////////////////////////////
//
// Macros to be called within the class definition header:
//

////////////////////////////////////////////
//
// These defines type-identifier and naming variables and methods that
// all engines and abstract engines must support
//

#define SO_ENGINE_ABSTRACT_HEADER(className)                                  \
  public:                                                                     \
    /** Returns the type identifier for this class.  */                       \
    static SoType getClassTypeId();                                           \
    /** Returns the type identifier for this specific instance. */            \
    virtual SoType      getTypeId() const;                                    \
  SoINTERNAL public:                                                          \
    virtual SbBool      getIsBuiltIn() const;                                 \
    /** Returns SoFieldData */                                                \
    virtual const SoFieldData *         getFieldData()  const;                \
    /** Returns the SoEngineOutputData */                                     \
    virtual const SoEngineOutputData *  getOutputData() const;                \
  protected:                                                                  \
    static const SoFieldData **         getInputDataPtr();                    \
    static const SoEngineOutputData **  getOutputDataPtr();                   \
  private:                                                                    \
    static SoType      classTypeId;    /* Type id              */            \
    static SbBool      isBuiltIn;                                            \
    static SbBool      firstInstance;  /* True for first ctor call */        \
    static SoFieldData *inputData;     /* Info on input fields */            \
    static SoEngineOutputData  *outputData;            /* Info on outputs */ \
    static const SoFieldData   **parentInputData;      /* parent's fields */ \
    static const SoEngineOutputData **parentOutputData

#define SO_ENGINE_HEADER(className)                                           \
                                                                              \
    SO_ENGINE_ABSTRACT_HEADER(className);                                     \
                                                                              \
  private:                                                                    \
  /* Creates and returns instance */                                          \
  static void *createInstance(SoType* dynamicType = NULL)

////////////////////////////////////////////
//
// This declares the static variables defined in SO_ENGINE_HEADER
//

#define SO__ENGINE_ABSTRACT_VARS(className)                                   \
    SoType                        className::classTypeId;                     \
    SbBool                        className::isBuiltIn = FALSE;               \
    SbBool                        className::firstInstance = TRUE;            \
    SoEngineOutputData           *className::outputData = NULL;                      \
    SoFieldData *                 className::inputData = NULL;                       \
    const SoEngineOutputData    **className::parentOutputData = NULL;                \
    const SoFieldData **          className::parentInputData = NULL

#define SO__ENGINE_VARS(className)                                            \
    SO__ENGINE_ABSTRACT_VARS(className)

////////////////////////////////////////////
//
// These implement the methods defined in SO_ENGINE_HEADER
//

#define SO__ENGINE_ABSTRACT_METHODS(className)                                \
    SoType                                                                    \
    className::getClassTypeId()                                               \
    {                                                                         \
      return classTypeId;                                                     \
    }                                                                         \
                                                                              \
    SoType                                                                    \
    className::getTypeId() const                                              \
    {                                                                         \
        return classTypeId;                                                   \
    }                                                                         \
                                                                              \
    SbBool className::getIsBuiltIn() const                                    \
    {                                                                         \
        return isBuiltIn;                                                     \
    }                                                                         \
                                                                              \
    const SoFieldData *                                                       \
    className::getFieldData() const                                           \
    {                                                                         \
        return inputData;                                                     \
    }                                                                         \
                                                                              \
    const SoEngineOutputData *                                                \
    className::getOutputData() const                                          \
    {                                                                         \
        return outputData;                                                    \
    }                                                                         \
    const SoFieldData **                                                      \
    className::getInputDataPtr()                                              \
    {                                                                         \
      return (const SoFieldData **)&inputData;                                \
    }                                                                         \
    const SoEngineOutputData **                                               \
    className::getOutputDataPtr()                                             \
    {                                                                         \
      return (const SoEngineOutputData **)&outputData;                        \
    }

#define SO__ENGINE_METHODS(className)                                         \
                                                                              \
    SO__ENGINE_ABSTRACT_METHODS(className)                                    \
                                                                              \
    void *                                                                    \
    className::createInstance(SoType* )                                       \
    {                                                                         \
        return (void *)(new className);                                       \
    }

/////////////////////////////////////////////////////////////////////////////
//
// Macros to be called within the source file for a engine subclass:
//

#define SO_ENGINE_SOURCE(className)                                           \
    SO__ENGINE_VARS(className);                                               \
    SO__ENGINE_METHODS(className)

#define SO_ENGINE_ABSTRACT_SOURCE(className)                                  \
    SO__ENGINE_ABSTRACT_VARS(className);                                      \
    SO__ENGINE_ABSTRACT_METHODS(className)


#if defined(_DEBUG)
#define SO_ENGINE_INIT_CLASS_CHECK_PARENT(className, parentClass)                   \
  if (parentClass::getClassTypeId().isBad()) {                                        \
    SoDebugError::post( SO__QUOTE(className)"::initClass",                            \
      SO__QUOTE(className)" initialized before parent class " \
      SO__QUOTE(parentClass)"\n");                                                    \
    parentClass::initClass();                                                         \
  }
#else
#define SO_ENGINE_INIT_CLASS_CHECK_PARENT(className, parentClass)                   \
  if (parentClass::getClassTypeId().isBad())                                          \
    parentClass::initClass()
#endif

///////////////////////////////////////////////////////////
//
//  Internal initialization macros
//

#define SO__ENGINE_INIT_CLASS_INTERNAL(className, classPrintName, parentClass) {         \
  SO_ENGINE_INIT_CLASS_CHECK_PARENT(className, parentClass);                             \
  classTypeId = SoType::createType( parentClass::getClassTypeId(),                       \
                                    classPrintName,                                      \
                                    &className::createInstance);                         \
  parentInputData = parentClass::getInputDataPtr();                                      \
  parentOutputData = parentClass::getOutputDataPtr();                                    \
}

#define SO__ENGINE_INIT_CLASS(className, classPrintName, parentClass)                    \
  SO__ENGINE_INIT_CLASS_INTERNAL(className, classPrintName, parentClass);

#define SO__ENGINE_INIT_ABSTRACT_CLASS_INTERNAL(className,classPrintName,parentClass) {  \
  SO_ENGINE_INIT_CLASS_CHECK_PARENT(className, parentClass);                             \
  classTypeId = SoType::createType(parentClass::getClassTypeId(),                        \
                                   classPrintName);                                      \
  parentInputData = parentClass::getInputDataPtr();                                      \
  parentOutputData = parentClass::getOutputDataPtr();                                    \
}

#define SO__ENGINE_INIT_ABSTRACT_CLASS(className,classPrintName,parent) \
  SO__ENGINE_INIT_ABSTRACT_CLASS_INTERNAL(className,classPrintName,parent);

////////////////////////////////////////////
//
// This initializes the type identifer variables
// This macro should be called from within initClass(). The parentClass
// argument should be the class that this subclass is derived from.
//

#define SO_ENGINE_INIT_CLASS_INTERNAL(className,parentClass,parentPrintClass) {        \
  SO_ENGINE_INIT_CLASS_CHECK_PARENT(className, parentClass);            \
  classTypeId = SoType::createType(SoType::fromName(parentPrintClass),  \
                       SO__QUOTE(className),                            \
                       &className::createInstance);                     \
  parentInputData = parentClass::getInputDataPtr();                     \
  parentOutputData = parentClass::getOutputDataPtr();                   \
}

#define SO_ENGINE_INIT_CLASS(className,parentClass,parentPrintClass) \
  SO_ENGINE_INIT_CLASS_INTERNAL(className,parentClass,parentPrintClass);

#define SO_ENGINE_INIT_ABSTRACT_CLASS_INTERNAL(className,parentClass,parentPrintClass) { \
  SO_ENGINE_INIT_CLASS_CHECK_PARENT(className, parentClass); \
  classTypeId = SoType::createType(SoType::fromName(parentPrintClass), \
                                   SO__QUOTE(className)); \
  parentInputData = parentClass::getInputDataPtr(); \
  parentOutputData = parentClass::getOutputDataPtr(); \
}

#define SO_ENGINE_INIT_ABSTRACT_CLASS(className,parent,parentPrintClass) \
  SO_ENGINE_INIT_ABSTRACT_CLASS_INTERNAL(className,parent,parentPrintClass);


#define SO_ENGINE_EXIT_CLASS(className) \
  SoType::removeType(classTypeId.getName()); \
  classTypeId = SoType::badType(); \
  if (inputData) \
	{ \
    delete inputData; \
		inputData = NULL;\
	} \
  if (outputData) \
	{ \
    delete outputData;\
		outputData = NULL; \
	}\
	firstInstance = TRUE

/////////////////////////////////////////////////////////////////////////////
//
// Macro to be called within each constructor
//

#define SO_ENGINE_CONSTRUCTOR(className) \
  SoBaseInitializer sbi(this); \
  SO__ENGINE_CHECK_INIT(className); \
  if (inputData == NULL) { \
    inputData = new SoFieldData(parentInputData ?  *parentInputData : NULL); \
    outputData = new SoEngineOutputData(parentOutputData ? *parentOutputData : NULL);    \
  } \
  else { \
    firstInstance = FALSE; \
  }

////////////////////////////////////////////////
//
// This is a boolean value that can be tested
// in constructors.
//

#define SO_ENGINE_IS_FIRST_INSTANCE()   (firstInstance == TRUE)

////////////////////////////////////////////
//
// This adds the info for an input to the SoFieldData and sets the
// default value for it. The parameters are as follows:
//      inputName:      the name of the input (as a member)
//      defValue:       the default value enclosed in parentheses
//
// For example,
//
//      SO_ENGINE_ADD_INPUT(vector1, (0, 0, 0));
//      SO_ENGINE_ADD_INPUT(triggerTime, (0.0));
//
// adds info about inputs named vector1 and triggerTime with the
// given default values.  The inputs must be public member variables
// of a type derived from SoField.
//

#define SO_ENGINE_ADD_INPUT(inputName, defValue) {                            \
  SO__ENGINE_CHECK_CONSTRUCT(__FILE__);                               \
  if (firstInstance)                                                  \
    inputData->addField(this, SO__QUOTE(inputName),                   \
                        &this->inputName);                            \
  this->inputName.setValue defValue;                                  \
  this->inputName.setContainer(this);                                 \
}


////////////////////////////////////////////
//
// This adds the info for an output to the SoEngineOutputData.
// The parameters are as follows:
//      fieldName:      the name of the output (as a member)
//      type:           the type of the output (name of SoField subclass)
//
// For example,
//
//      SO_ENGINE_ADD_OUTPUT(result, SoSFVec3f);
//      SO_ENGINE_ADD_OUTPUT(hour, SoSFInt32);
//
// adds info about outputs named result and int32_t that can be hooked up
// to fields of the given type.
// The outputs must be public member variables of type SoEngineOutput.
//

#define SO_ENGINE_ADD_OUTPUT(outputName, type) {                                      \
  SO__ENGINE_CHECK_CONSTRUCT(__FILE__);                               \
  if (firstInstance)                                                  \
    outputData->addOutput(this, SO__QUOTE(outputName),                \
                          &this->outputName,                          \
                          type::getClassTypeId());                    \
  this->outputName.setContainer(this);                                \
}


////////////////////////////////////////////
//
// This registers a value of an enum type.
//      enumType:       the name of the enum type
//      enumValue:      the name of a value of that enum type
//
// If a engine defines an enum, each of the enum's values
// should be registered using this macro.  For example:
//
//      [ in MyFunc.h file: ]
//      class MyFunc {
//              ...
//              enum Chipmunk { ALVIN, SIMON, THEODORE };
//              ...
//      }
//
//      [ in constructor MyFunc::MyFunc(): ]
//      SO_ENGINE_DEFINE_ENUM_VALUE(Chipmunk, ALVIN);
//      SO_ENGINE_DEFINE_ENUM_VALUE(Chipmunk, SIMON);
//      SO_ENGINE_DEFINE_ENUM_VALUE(Chipmunk, THEODORE);
//

#define SO_ENGINE_DEFINE_ENUM_VALUE(enumType,enumValue) {                     \
  SO__ENGINE_CHECK_CONSTRUCT(__FILE__);                               \
  if (firstInstance)                                                  \
    inputData->addEnumValue(SO__QUOTE(enumType),                      \
                            SO__QUOTE(enumValue), enumValue);         \
}


////////////////////////////////////////////
//
// This takes care of writing the value to all connected outputs.
// This should be called in the evaluate() routine.
//

#define SO_ENGINE_OUTPUT(outputName,type,code) {                                      \
  if (outputName.isEnabled()) {                                       \
    for (int _eng_out_i = 0;                                          \
         _eng_out_i < outputName.getNumConnections();                 \
         _eng_out_i++) {                                              \
      type *_eng_out_temp = (type *) outputName[_eng_out_i];          \
      if (!_eng_out_temp->isReadOnly()) {                             \
        _eng_out_temp->code;                                  \
      }                                                       \
    }                                                                 \
  }                                                                   \
}



#endif /* _SO_SUB_ENGINE_ */
