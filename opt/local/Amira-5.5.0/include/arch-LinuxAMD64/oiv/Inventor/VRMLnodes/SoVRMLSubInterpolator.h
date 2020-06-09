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


#ifndef  _SO_SUB_INTERPOLATOR_
#define  _SO_SUB_INTERPOLATOR_

#include <Inventor/VRMLnodes/SoVRMLInterpolator.h>
#include <Inventor/VRMLnodes/SoVRMLInterpOutputData.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/fields/SoFieldData.h>


///////////////////////
//
// Debugging macros called by other macros in this file
//
#if defined(_DEBUG)
#define SO__INTERPOLATOR_CHECK_INIT(className)                                \
    if (classTypeId.isBad()) {                                   \
        SoDebugError::post("SO_INTERPOLATOR_CONSTRUCTOR",                     \
                           "Can't construct an interpolator of type "         \
                           SO__QUOTE(className)                               \
                           " until initClass() has been called");             \
        className::initClass();                                                               \
    } \
    SoDB::checkDatabase(SO__QUOTE(className), this, className::getClassTypeId(), classTypeId); \

#define SO__INTERPOLATOR_CHECK_CONSTRUCT(where)                               \
{ \
  if (inputData == NULL) {                                            \
    SoDebugError::post(where,                                         \
                       "Instance not properly constructed.\n"         \
                       "Did you forget to put "                       \
                       "SO_INTERPOLATOR_CONSTRUCTOR()"                \
                       " in the constructor?");                       \
    inputData = new SoFieldData(parentInputData ?                     \
                                *parentInputData : NULL);             \
    outputData = new SoVRMLInterpOutputData(parentOutputData ?        \
                                            *parentOutputData : NULL);    \
  }                                                                   \
}
#else
#define SO__INTERPOLATOR_CHECK_INIT(className)  {        }
#define SO__INTERPOLATOR_CHECK_CONSTRUCT(where) {        }
#endif

/////////////////////////////////////////////////////////////////////////////
//
// Macros to be called within the class definition header:
//

////////////////////////////////////////////
//
// These defines type-identifier and naming variables and methods that
// all interpolator and abstract interpolator must support
//

#define SO_INTERPOLATOR_ABSTRACT_HEADER(className)                            \
  public:                                                                     \
  static SoType getClassTypeId() ;                    \
    virtual SoType      getTypeId() const; /* Returns type id   */            \
  public:                                                                     \
    virtual const SoFieldData *         getFieldData()  const;                \
    virtual const SoVRMLInterpOutputData *      getOutputData() const;        \
  SoINTERNAL public:                                                          \
    virtual SbBool      getIsBuiltIn() const ;                                \
  protected:                                                                  \
    static const SoFieldData **         getInputDataPtr() ;                   \
    static const SoVRMLInterpOutputData **      getOutputDataPtr();           \
  private:                                                                    \
    static SoType      classTypeId;    /* Type id      */    \
    static SbBool      isBuiltIn;                            \
    static SbBool      firstInstance;  /* True for first ctor call */        \
    static SoFieldData *inputData;     /* Info on input fields */            \
    static SoVRMLInterpOutputData      *outputData;            /* Info on outputs */ \
    static const SoFieldData   **parentInputData;      /* parent's fields */ \
    static const SoVRMLInterpOutputData **parentOutputData

#define SO_INTERPOLATOR_HEADER(className)                                     \
                                                                              \
    SO_INTERPOLATOR_ABSTRACT_HEADER(className);                               \
                                                                              \
  private:                                                                    \
    static void *createInstance(SoType* dynamicType = NULL)       /* Creates and returns instance */

////////////////////////////////////////////
//
// This declares the static variables defined in SO_INTERPOLATOR_HEADER
//

#define SO__INTERPOLATOR_ABSTRACT_VARS(className)                             \
    SoType                        className::classTypeId;                     \
    SbBool                        className::isBuiltIn = FALSE;               \
    const SoFieldData           **className::parentInputData = NULL;          \
    const SoVRMLInterpOutputData **className::parentOutputData = NULL;        \
    SoFieldData *                 className::inputData = NULL;                \
    SoVRMLInterpOutputData *      className::outputData = NULL;               \
    SbBool                        className::firstInstance=TRUE

#define SO__INTERPOLATOR_VARS(className)                                      \
    SO__INTERPOLATOR_ABSTRACT_VARS(className)

////////////////////////////////////////////
//
// These implement the methods defined in SO_INTERPOLATOR_HEADER
//

#define SO__INTERPOLATOR_ABSTRACT_METHODS(className)                 \
    SoType      \
    className::getClassTypeId() { return classTypeId; }               \
                                                                              \
    SbBool                                                                    \
    className::getIsBuiltIn() const                                           \
    {                                                                         \
      return isBuiltIn;                                                       \
    }                                                                         \
                                                                              \
    SoType                                                                    \
    className::getTypeId() const                                              \
    {                                                                         \
        return classTypeId;                                                   \
    }                                                                         \
                                                                              \
    const SoFieldData *                                                       \
    className::getFieldData() const                                           \
    {                                                                         \
        return inputData;                                                     \
    }                                                                         \
                                                                              \
    const SoVRMLInterpOutputData *                                            \
    className::getOutputData() const                                          \
    {                                                                         \
        return outputData;                                                    \
    }                                                                         \
    const SoFieldData **                                                     \
    className::getInputDataPtr()                      \
        { return (const SoFieldData **)&inputData; }                          \
    const SoVRMLInterpOutputData **      \
    className::getOutputDataPtr()                     \
        { return (const SoVRMLInterpOutputData **)&outputData; }


#define SO__INTERPOLATOR_METHODS(className)                                   \
                                                                              \
    SO__INTERPOLATOR_ABSTRACT_METHODS(className)                              \
                                                                              \
    void *                                                                    \
    className::createInstance(SoType*)                                        \
    {                                                                         \
        return (void *)(new className);                                       \
    }

/////////////////////////////////////////////////////////////////////////////
//
// Macros to be called within the source file for a interpolator subclass:
//

#define SO_INTERPOLATOR_SOURCE(className)                                     \
    SO__INTERPOLATOR_VARS(className);                                         \
    SO__INTERPOLATOR_METHODS(className)

#define SO_INTERPOLATOR_ABSTRACT_SOURCE(className)                            \
    SO__INTERPOLATOR_ABSTRACT_VARS(className);                                \
    SO__INTERPOLATOR_ABSTRACT_METHODS(className)

///////////////////////////////////////////////////////////
//
//  Internal initialization macros
//
#if defined(_DEBUG)
#define SO_INTERPOLATOR_INIT_CLASS_CHECK_PARENT(className, parentClass)               \
  if (parentClass::getClassTypeId().isBad()) {                                        \
    SoDebugError::post( SO__QUOTE(className)"::initClass",                            \
      SO__QUOTE(className)" initialized before parent class " \
      SO__QUOTE(parentClass)"\n");                                                    \
    parentClass::initClass();                                                         \
  }
#else
#define SO_INTERPOLATOR_INIT_CLASS_CHECK_PARENT(className, parentClass)  \
  if (parentClass::getClassTypeId().isBad())                             \
    parentClass::initClass()
#endif

#define SO__INTERPOLATOR_INIT_CLASS_INTERNAL(className, classPrintName, parentClass)   \
  SO_INTERPOLATOR_INIT_CLASS_CHECK_PARENT(className, parentClass);    \
  classTypeId = SoType::createType(parentClass::getClassTypeId(),     \
                       classPrintName,                                \
                       &className::createInstance);                   \
  parentInputData = parentClass::getInputDataPtr();                   \
  parentOutputData = parentClass::getOutputDataPtr()

#define SO__INTERPOLATOR_INIT_CLASS(className, classPrintName, parentClass) \
  SO__INTERPOLATOR_INIT_CLASS_INTERNAL(className, classPrintName, parentClass)

#define SO__INTERPOLATOR_INIT_ABSTRACT_CLASS_INTERNAL(className,classPrintName,parentClass) \
  SO_INTERPOLATOR_INIT_CLASS_CHECK_PARENT(className, parentClass);    \
  classTypeId = SoType::createType(parentClass::getClassTypeId(),     \
                                   classPrintName);                   \
  parentInputData = parentClass::getInputDataPtr();                   \
  parentOutputData = parentClass::getOutputDataPtr()

#define SO__INTERPOLATOR_INIT_ABSTRACT_CLASS(className,classPrintName,parent) \
  SO__INTERPOLATOR_INIT_ABSTRACT_CLASS_INTERNAL(className,classPrintName,parent);

////////////////////////////////////////////
//
// This initializes the type identifer variables
// This macro should be called from within initClass(). The parentClass
// argument should be the class that this subclass is derived from.
//

#define SO_INTERPOLATOR_INIT_CLASS_INTERNAL(className,parentClass,parentPrintClass)    \
  SO_INTERPOLATOR_INIT_CLASS_CHECK_PARENT(className, parentClass);     \
  classTypeId = SoType::createType(SoType::fromName(parentPrintClass), \
                       SO__QUOTE(className),                           \
                       &className::createInstance);                    \
  parentInputData = parentClass::getInputDataPtr();                    \
  parentOutputData = parentClass::getOutputDataPtr()

#define SO_INTERPOLATOR_INIT_CLASS(className,parentClass,parentPrintClass) \
  SO_INTERPOLATOR_INIT_CLASS_INTERNAL(className,parentClass,parentPrintClass);

#define SO_INTERPOLATOR_INIT_ABSTRACT_CLASS_INTERNAL(className,parentClass,parentPrintClass)  \
  SO_INTERPOLATOR_INIT_CLASS_CHECK_PARENT(className, parentClass);                                                                 \
  classTypeId = SoType::createType(SoType::fromName(parentPrintClass), SO__QUOTE(className)); \
  parentInputData = parentClass::getInputDataPtr(); \
  parentOutputData = parentClass::getOutputDataPtr()

#define SO_INTERPOLATOR_INIT_ABSTRACT_CLASS(className, parentClass, parentPrintClass) \
  SO_INTERPOLATOR_INIT_ABSTRACT_CLASS_INTERNAL(className,parentClass,parentPrintClass);

#define SO_INTERPOLATOR_EXIT_CLASS(className)  \
  SoType::removeType(classTypeId.getName());   \
  classTypeId = SoType::badType();             \
  if (inputData) {                             \
    delete inputData;                          \
    inputData = NULL;                          \
  }                                            \
  if (outputData) {                            \
    delete outputData;                         \
    outputData = NULL;                         \
  }                                            \
  parentInputData = NULL;                      \
  parentOutputData = NULL;                     \
  firstInstance = TRUE

/////////////////////////////////////////////////////////////////////////////
//
// Macro to be called within each constructor
//

#define SO_INTERPOLATOR_CONSTRUCTOR(className)                                \
{ \
  SO__INTERPOLATOR_CHECK_INIT(className);                                     \
  if (inputData == NULL) {                                            \
    inputData = new SoFieldData(parentInputData ?                     \
                                *parentInputData : NULL);             \
    outputData = new SoVRMLInterpOutputData(parentOutputData ?        \
                                            *parentOutputData : NULL);    \
  }                                                                   \
  else {                                                                      \
    firstInstance = FALSE;                                            \
  }                                                                   \
  isBuiltIn = FALSE;                                                  \
}

////////////////////////////////////////////////
//
// This is a boolean value that can be tested
// in constructors.
//

#define SO_INTERPOLATOR_IS_FIRST_INSTANCE()     (firstInstance == TRUE)

////////////////////////////////////////////
//
// This adds the info for an input to the SoFieldData and sets the
// default value for it. The parameters are as follows:
//      inputName:      the name of the input (as a member)
//      defValue:       the default value enclosed in parentheses
//
// For example,
//
//      SO_INTERPOLATOR_ADD_INPUT(vector1, (0, 0, 0));
//      SO_INTERPOLATOR_ADD_INPUT(triggerTime, (0.0));
//
// adds info about inputs named vector1 and triggerTime with the
// given default values.  The inputs must be public member variables
// of a type derived from SoField.
//

#define SO_INTERPOLATOR_ADD_INPUT(inputName, defValue)                        \
{ \
  SO__INTERPOLATOR_CHECK_CONSTRUCT(__FILE__);                         \
  if (firstInstance)                                                  \
    inputData->addField(this, SO__QUOTE(inputName),                   \
                        &this->inputName);                            \
  this->inputName.setValue defValue;                                  \
  this->inputName.setContainer(this);                                 \
}

#define SO_INTERPOLATOR_ADD_EXPOSEDINPUT(inputName, defValue)                 \
{ \
  SO__INTERPOLATOR_CHECK_CONSTRUCT(__FILE__);                           \
  if (firstInstance)                                                    \
    inputData->addField(this, SO__QUOTE(inputName),                   \
                        &this->inputName);                            \
  this->inputName.setValue defValue;                                    \
  this->inputName.setContainer(this);                                   \
  this->inputName.setFieldType(5);                                     \
}

#define SO_INTERPOLATOR_ADD_EVENTIN(inputName)                                \
{ \
  SO__INTERPOLATOR_CHECK_CONSTRUCT(__FILE__);                           \
  if (firstInstance)                                                    \
    inputData->addField(this, SO__QUOTE(inputName),                   \
                        &this->inputName);                            \
  this->inputName.setContainer(this);                                   \
  this->inputName.setFieldType(1);                                     \
}

#define SO_INTERPOLATOR_ADD_HIDDEN_FIELD(inputName, defValue)                           \
{ \
  SO__INTERPOLATOR_CHECK_CONSTRUCT(__FILE__);                           \
  if (firstInstance)                                                    \
    inputData->addField(this, SO__QUOTE(inputName),                   \
                        &this->inputName);                            \
  this->inputName.setValue defValue;                                    \
  this->inputName.setContainer(this);                                   \
  this->inputName.setFieldType(4);                                     \
}

////////////////////////////////////////////
//
// This adds the info for an output to the SoVRMLInterpOutputData.
// The parameters are as follows:
//      fieldName:      the name of the output (as a member)
//      type:           the type of the output (name of SoField subclass)
//
// For example,
//
//      SO_INTERPOLATOR_ADD_OUTPUT(result, SoSFVec3f);
//      SO_INTERPOLATOR_ADD_OUTPUT(hour, SoSFInt32);
//
// adds info about outputs named result and int32_t that can be hooked up
// to fields of the given type.
// The outputs must be public member variables of type SoVRMLInterpOutput.
//

#define SO_INTERPOLATOR_ADD_OUTPUT(outputName, type) \
{ \
  SO__INTERPOLATOR_CHECK_CONSTRUCT(__FILE__); \
  if (firstInstance) { \
    outputData->addOutput(this, SO__QUOTE(outputName), \
                          &this->outputName, \
                          type::getClassTypeId()); \
  } \
  this->outputName.setContainer(this); \
}

////////////////////////////////////////////
//
// This registers a value of an enum type.
//      enumType:       the name of the enum type
//      enumValue:      the name of a value of that enum type
//
// If a interpolator defines an enum, each of the enum's values
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
//      SO_INTERPOLATOR_DEFINE_ENUM_VALUE(Chipmunk, ALVIN);
//      SO_INTERPOLATOR_DEFINE_ENUM_VALUE(Chipmunk, SIMON);
//      SO_INTERPOLATOR_DEFINE_ENUM_VALUE(Chipmunk, THEODORE);
//

#define SO_INTERPOLATOR_DEFINE_ENUM_VALUE(enumType,enumValue)                 \
{ \
  SO__INTERPOLATOR_CHECK_CONSTRUCT(__FILE__);                         \
  if (firstInstance)                                                  \
    inputData->addEnumValue(SO__QUOTE(enumType),                      \
                            SO__QUOTE(enumValue), enumValue);         \
}

////////////////////////////////////////////
//
// This takes care of writing the value to all connected outputs.
// This should be called in the evaluate() routine.
//

#define SO_INTERPOLATOR_OUTPUT(outputName,type,code)                          \
{ \
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

#endif /* _SO_SUB_INTERPOLATOR_ */
