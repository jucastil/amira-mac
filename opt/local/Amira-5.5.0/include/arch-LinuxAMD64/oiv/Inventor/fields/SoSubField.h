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


#ifndef  _SO_SUB_FIELD_
#define  _SO_SUB_FIELD_

#include <Inventor/fields/SoField.h>
#include <Inventor/SoInput.h>
#include <Inventor/SoOutput.h>
#include <Inventor/errors/SoMemoryError.h>

//===========================================================================
//
// These are all internal macros used by some of the public ones.
//
//===========================================================================

#define SO__FIELD_HEADER(className) \
  public: \
    /** Returns the type identifier for this specific instance. */ \
    virtual SoType getTypeId() const; \
    /** Returns the type identifier for this class.  */ \
    static SoType getClassTypeId(); \
\
    /** Copy from another field of same type */ \
    const className & operator =(const className &f); \
\
 SoINTERNAL public:\
    /* Copy from another field of unknown type (assumed to be same type) */ \
    virtual void copyFrom(const SoField &f); \
\
    static void * createInstance(SoType* dynamicType = NULL);  \
\
    /* Returns TRUE if fields are same type and have same values */ \
    virtual SbBool isSame(const SoField &f) const; \
\
  private: \
    static  SoType classTypeId

#define SO__SFIELD_RW_HEADER(className) \
  protected: \
    /* Reads value of field from file */ \
    virtual SbBool readValue(SoInput *in); \
\
    /* Writes value of field to file */ \
    virtual void writeValue(SoOutput *out) const

#define SO__MFIELD_RW_HEADER(className) \
  private: \
    /* Reads indexed value of field from file */ \
    virtual SbBool read1Value(SoInput *in, int index); \
\
    /* Writes one (indexed) value to file */ \
    virtual void write1Value(SoOutput *out, int index) const

#if defined(_DEBUG)
#define SO_FIELD_INIT_CLASS_CHECK_PARENT(className, parentClass)                   \
  if (parentClass::getClassTypeId().isBad()) {                                        \
    SoDebugError::post( SO__QUOTE(className)"::initClass",                            \
      SO__QUOTE(className)" initialized before parent class " \
      SO__QUOTE(parentClass)"\n");                                                    \
    parentClass::initClass();                                                         \
  }
#else
#define SO_FIELD_INIT_CLASS_CHECK_PARENT(className, parentClass)                   \
  if (parentClass::getClassTypeId().isBad())                                          \
    parentClass::initClass()
#endif

#define SO__FIELD_INIT_CLASS_INTERNAL(className,classPrintName,parentClass) \
  SO_FIELD_INIT_CLASS_CHECK_PARENT(className, parentClass); \
  classTypeId = SoType::createType(parentClass::getClassTypeId(), \
                                   classPrintName, \
                                   &className::createInstance)

#define SO__FIELD_INIT_CLASS(className,classPrintName,parentClass) \
  SO__FIELD_INIT_CLASS_INTERNAL(className,classPrintName,parentClass);

#define SO__FIELD_INIT_ABSTRACT_CLASS_INTERNAL(className,classPrintName,parentClass) \
  SO_FIELD_INIT_CLASS_CHECK_PARENT(className, parentClass);                                           \
  classTypeId = SoType::createType(parentClass::getClassTypeId(),       \
                                   classPrintName,                      \
                                   NULL)

#define SO__FIELD_INIT_ABSTRACT_CLASS(className,classPrintName,parentClass) \
  SO__FIELD_INIT_ABSTRACT_CLASS_INTERNAL(className,classPrintName,parentClass);

#if defined(_DEBUG)
#define SO__FIELD_EXIT_CLASS(className) { \
  if (! SoType::removeType(classTypeId.getName())) { \
    SoDebugError::post(SO__QUOTE(className)"::exitClass", \
                       "Unable to remove type (%s) for this class. Check exitClass() " \
                       "method is implemented and is called only once.\n", \
                       classTypeId.getName().getString() ); \
  } \
  else \
    classTypeId = SoType::badType(); \
}
#else
#define SO__FIELD_EXIT_CLASS(className) \
  SoType::removeType(classTypeId.getName()); \
  classTypeId = SoType::badType()
#endif

#define SO__FIELD_ID_ABSTRACT_SOURCE(className) \
                                                \
  SoType className::classTypeId;                \
                                                \
  SoType                                        \
  className::getClassTypeId()                   \
  {                                             \
    return classTypeId;                         \
  }                                             \
                                                \
  SoType                                        \
  className::getTypeId() const                  \
  {                                             \
    return classTypeId;                         \
  }

#define SO__FIELD_ID_SOURCE(className)      \
  SO__FIELD_ID_ABSTRACT_SOURCE(className);  \
  void *                                    \
  className::createInstance(SoType *)       \
  {                                         \
    return (void *)(new className);         \
  }


#define SO__FIELD_EQ_SAME_SOURCE(className) \
\
void \
className::copyFrom(const SoField &f) \
{ \
  *this = * (const className *) &f; \
} \
\
SbBool \
className::isSame(const SoField &f) const \
{ \
  return (getTypeId() == f.getTypeId() && \
          (*this) == (const className &) f); \
}

//===========================================================================
//
// Macros to be called within the class definition header for a
// single-value field subclass:
//
//===========================================================================

////////////////////////////////////////////////////////////////////////////
//
// This declares all header info required for a single-value field class.
//
////////////////////////////////////////////////////////////////////////////

#define SO_SFIELD_REQUIRED_HEADER(className) \
  SO__FIELD_HEADER(className)

////////////////////////////////////////////////////////////////////////////
//
// This declares a constructor and destructor for a single-value field class.
//
////////////////////////////////////////////////////////////////////////////

#define SO_SFIELD_CONSTRUCTOR_HEADER(className) \
  public: \
    /** Default constructor */ \
    className(); \
    \
    /** Destructor */ \
    virtual ~className()

////////////////////////////////////////////////////////////////////////////
//
// This declares value processing methods and variables for a
// single-value field class.
//
////////////////////////////////////////////////////////////////////////////

#define SO_SFIELD_VALUE_HEADER(className, valueType, valueRef) \
  SO__SFIELD_RW_HEADER(className); \
\
  public: \
    /** Returns this field's value. */ \
    valueRef getValue() const \
    { evaluate(); return value; } \
\
    /** Sets this field to <I>newValue</I>. */ \
    void setValue(valueRef newValue); \
\
    /** Sets this field to <I>newValue</I>. */ \
    valueRef operator =(valueRef newValue) \
    { setValue(newValue); return value; } \
\
    /** Returns TRUE if <I>otherField</I> is of the same type and has the same value as this field. */ \
    int operator ==(const className &f) const; \
\
    /** Returns FALSE if <I>otherField</I> is of the same type and has the same value as this field. */ \
    int operator !=(const className &f) const \
    { return ! ((*this) == f); } \
\
    /** Get size of the value */ \
    virtual size_t getValueSize() const { return sizeof(valueType); } \
\
  protected: \
    valueType value

////////////////////////////////////////////////////////////////////////////
//
// This is like the above macro, but can be used by a field class
// derived from another (non-abstract) field class. It will inherit
// most of the field processing stuff.
//
////////////////////////////////////////////////////////////////////////////

#define SO_SFIELD_DERIVED_VALUE_HEADER(className, valueType, valueRef) \
    SO__SFIELD_RW_HEADER(className); \
  public: \
    /** Sets this field to <I>newValue</I>. */ \
    valueRef operator =(valueRef newValue) \
    { setValue(newValue); return (valueRef)value; }

////////////////////////////////////////////////////////////////////////////
//
// This macro is all that is needed for most single-value field
// classes. It includes the relevant macros.
//
////////////////////////////////////////////////////////////////////////////

#define SO_SFIELD_HEADER(className, valueType, valueRef) \
  SO_SFIELD_REQUIRED_HEADER(className); \
  SO_SFIELD_CONSTRUCTOR_HEADER(className); \
  SO_SFIELD_VALUE_HEADER(className, valueType, valueRef)

////////////////////////////////////////////////////////////////////////////
//
// This macro is all that is needed for most single-value field
// classes that are derived from other field classes. It includes the
// relevant macros.
//
////////////////////////////////////////////////////////////////////////////

#define SO_SFIELD_DERIVED_HEADER(className, valueType, valueRef) \
  SO_SFIELD_REQUIRED_HEADER(className); \
  SO_SFIELD_CONSTRUCTOR_HEADER(className); \
  SO_SFIELD_DERIVED_VALUE_HEADER(className, valueType, valueRef)

//===========================================================================
//
// Macros to be called within the class definition header for a
// multiple-value field subclass:
//
//===========================================================================

////////////////////////////////////////////////////////////////////////////
//
// This declares all header info required for a multiple-value field class.
//
////////////////////////////////////////////////////////////////////////////

#define SO_MFIELD_REQUIRED_HEADER(className) \
  SO__FIELD_HEADER(className)

////////////////////////////////////////////////////////////////////////////
//
// This declares a constructor and destructor for a multiple-value field class.
//
////////////////////////////////////////////////////////////////////////////

#define SO_MFIELD_CONSTRUCTOR_HEADER(className) \
  public: \
    /** Default constructor */ \
    className(); \
    \
    /** Destructor */ \
    virtual ~className()

////////////////////////////////////////////////////////////////////////////
//
// This declares value processing methods and variables for a
// multiple-value field class.
//
////////////////////////////////////////////////////////////////////////////

#define SO_MFIELD_VALUE_HEADER(className, valueType, valueRef) \
  SO__MFIELD_RW_HEADER(className); \
\
  public: \
    /** Returns the i'th value of the field. Indexing past the end of the field (passing in i greater than getNum()) will return garbage. */ \
    valueRef operator [](int i) const \
    { evaluate(); return values[i]; } \
\
    /** Returns a pointer into the array of values in the field, starting at index start. */ \
    /** The values are read-only. See the startEditing()/finishEditing() */ \
    /** methods for a way of modifying values in place. */ \
    /** [OIVNET-WRAPPER HELPER_BEGIN{if (GetNum() == 0) return nullptr; if ((start < 0) || (start >= GetNum())) throw gcnew System::IndexOutOfRangeException();}] */ \
    /** [OIVNET-WRAPPER-RETURN-TYPE ARRAY{GetNum()-start}] */ \
    /** [OIVJAVA-WRAPPER HELPER_BEGIN{if (getNum() == 0) return null; if ((start < 0) || (start >= getNum())) throw new IndexOutOfBoundsException("Index "+start+" is out of range [0,"+getNum()+"[");}] */ \
    /** [OIVJAVA-WRAPPER-RETURN-TYPE ARRAY{getNum()-start}] */ \
    const valueType *getValues(int start) const \
    { evaluate(); return (const valueType*)(static_cast<valueType *>(values + start)); } \
\
    /** Finds the given <I>targetValue</I> in the array and returns the index of that value */ \
    /** in the array. If the value is not found, -1 is returned. If <I>addIfNotFound</I> */ \
    /** is set, then <I>targetValue</I> is added to the end of the array */ \
    /** (but -1 is still returned). */ \
    int find(valueRef targetValue, SbBool addIfNotFound = FALSE); \
\
    /** Sets <I>num</I> values starting at index <I>start</I> to the values */ \
    /** in <I>newValues</I>. The array will automatically be made larger to accommodate */ \
    /** the new values, if necessary. */ \
    /** [OIVNET-WRAPPER-ARG IN,NO_WRAP{newValues->Length},ARRAY] */ \
    /** [OIVNET-WRAPPER HELPER_BEGIN{OnSetValues(start,newValues->Length)}] */ \
    /** [OIVJAVA-WRAPPER-ARG IN,NO_WRAP{newValues.length},ARRAY] */ \
    /** [OIVJAVA-WRAPPER HELPER_BEGIN{onSetValues(start,newValues.length)}] */ \
    void setValues(int start, int num, const valueType *newValues); \
\
    /** Sets the <I>index</I>'th value in the array to <I>newValue</I>. */ \
    /** The array will be automatically expanded, if necessary. */ \
    /** [OIVNET-WRAPPER HELPER_BEGIN{OnSet1Value(index)}] */ \
    /** [OIVJAVA-WRAPPER HELPER_BEGIN{onSet1Value(index)}] */ \
    void set1Value(int index, valueRef newValue); \
\
    /** Sets the first value in the array to <I>newValue</I>, and deletes */ \
    /** the second and subsequent values. */ \
    /** [OIVNET-WRAPPER HELPER_BEGIN{OnSetValue()}] */ \
    /** [OIVJAVA-WRAPPER HELPER_BEGIN{onSetValue()}] */ \
    void setValue(valueRef newValue); \
\
    /** Sets the first value in the array to <I>newValue</I>, and deletes */ \
    /** the second and subsequent values. */ \
    /** [OIVNET-WRAPPER HELPER_BEGIN{dst->OnSetValue()}] */ \
    /** [OIVJAVA-WRAPPER HELPER_BEGIN{dst.onSetValue()}] */ \
    valueRef operator =(valueRef newValue) \
    { setValue(newValue); return newValue; } \
\
    /** Returns TRUE if all of the values of this field equal those of */ \
    /** the given <I>f</I>. If the fields are different types FALSE will */ \
    /** always be returned. */ \
    int operator ==(const className &f) const; \
\
    /** Returns TRUE if all of the values of this field do not equal */ \
    /** those of the given <I>f</I>. If the fields are different types */ \
    /** TRUE will always be returned. */ \
    int operator !=(const className &f) const \
    { return ! ((*this) == f); } \
\
    /** Sets the enableDeleteValues flag. This flag (if TRUE) allows Open Inventor */ \
    /** to destroy the user data array given to setValuesPointer(). This user data array */  \
    /** will be managed exactly like internal field data values. Default is FALSE. */ \
    /** [OIV-WRAPPER-NOT-WRAP] */ \
    virtual void enableDeleteValues() \
    { userDataIsUsed = false; } \
\
    /** Temporary disable value deleting */ \
    virtual void disableDeleteValues(){userDataIsUsed = true;} \
\
    /** Returns FALSE if user data array has been given to  */ \
    /** setValuesPointer() and enableDeleteValues() */ \
    /** has never been called, and memory for data has not been reallocated. */ \
    /** Otherwise, returns TRUE. */ \
    /** [OIV-WRAPPER-NOT-WRAP] */ \
    virtual SbBool isDeleteValuesEnabled() \
    { return (!userDataIsUsed)?TRUE:FALSE; } \
\
    /** Get size of the value */ \
    virtual size_t getValueSize() const { return sizeof(valueType); } \
\
  protected: \
    /* Allocates room for num values. Copies old values (if any) into    */ \
    /* new area.  Deletes old area, if any.  Will reduce room if needed, */ \
    /* so a value of newNum==0 will delete all values.                   */ \
    virtual void allocValues(int newNum); \
\
    /* Deletes all current values, resets number of values */ \
    virtual void deleteAllValues(); \
\
    /* Copies value indexed by "from" to value indexed by "to" */ \
    virtual void copyValue(int to, int from); \
\
    /* TRUE if user data array is used and if */ \
    /* enableDeleteValues has never been called. */ \
    bool userDataIsUsed; \
\
    valueType *values; \
\
    /* Get pointer into array of values */ \
    virtual void* getValuesPointer(int start) \
    { return static_cast<void*>(values + start); }


////////////////////////////////////////////////////////////////////////////
//
// This is like the above macro, but can be used by a field class
// derived from another (non-abstract) field class. It will inherit
// most of the field processing stuff.
//
////////////////////////////////////////////////////////////////////////////

#define SO_MFIELD_DERIVED_VALUE_HEADER(className, valueType, valueRef) \
    SO__MFIELD_RW_HEADER(className); \
  public: \
    /** Sets this field to <I>newValue</I>. */ \
    valueRef operator =(valueRef newValue) \
    { setValue(newValue); return newValue; }

#define SO_FIELD_SUPPORT_MEMOBJ() \
SoINTERNAL public: \
  virtual bool isEnabledMemObj() { return true; } \
  virtual SoMemoryObject* getMemObj() { return m_memObj; } \
  virtual void setMemObj( SoMemoryObject* memObj ) { m_memObj = memObj; }


////////////////////////////////////////////////////////////////////////////
//
// This macro defines the start and finish editing methods.
//
////////////////////////////////////////////////////////////////////////////

#define SO_MFIELD_EDITING_HEADER(className, valueType) \
  /** Returns a pointer to the internally maintained array that can be modified. */ \
  /** The values in the array may be changed, but values cannot be added or removed. It is illegal to call any other */ \
  /** editing methods between startEditing() and finishEditing() (e.g. set1Value(), setValue(), etc.). */ \
  /** */ \
  /** Fields, engines or sensors connected to this field and sensors are not notified that this field has changed until */ \
  /** finishEditing() is called. Calling finishEditing() always sets the isDefault() flag to FALSE and informs engines */ \
  /** and sensors that the field changed, even if none of the values actually were changed. */ \
  /** [OIV-WRAPPER-RETURN-TYPE ARRAY{GetNum()}] */ \
  valueType *startEditing() { \
    evaluate(); \
    return values; \
  } \
\
  /** Indicates that batch edits have finished. See startEditing(). */ \
  void finishEditing() { \
    valueChanged(0, getNum()); \
  }

////////////////////////////////////////////////////////////////////////////
//
// This macro is all that is needed for most multiple-value field
// classes. It includes the relevant macros.
//
////////////////////////////////////////////////////////////////////////////

#define SO_MFIELD_HEADER(className, valueType, valueRef) \
  SO_MFIELD_REQUIRED_HEADER(className); \
  SO_MFIELD_CONSTRUCTOR_HEADER(className); \
  SO_MFIELD_EDITING_HEADER(className, valueType); \
  SO_MFIELD_VALUE_HEADER(className, valueType, valueRef)

////////////////////////////////////////////////////////////////////////////
//
// This macro is all that is needed for most multiple-value field
// classes that are derived from other field classes. It includes the
// relevant macros.
//
////////////////////////////////////////////////////////////////////////////

#define SO_MFIELD_DERIVED_HEADER(className, valueType, valueRef) \
  SO_MFIELD_REQUIRED_HEADER(className); \
  SO_MFIELD_CONSTRUCTOR_HEADER(className); \
  SO_MFIELD_DERIVED_VALUE_HEADER(className, valueType, valueRef)

//===========================================================================
//
// Macros to be called within the source file for a single-value field
// subclass:
//
//===========================================================================

////////////////////////////////////////////////////////////////////////////
//
// This initializes type identifer variables. It should be called from
// within initClass().
//
////////////////////////////////////////////////////////////////////////////

#define SO_SFIELD_INIT_CLASS(className,parentClass) \
  SO__FIELD_INIT_CLASS(className, SO__QUOTE(className), parentClass);

#define SO_SFIELD_EXIT_CLASS(className) \
  SO__FIELD_EXIT_CLASS(className)

////////////////////////////////////////////////////////////////////////////
//
// This defines the variables and methods declared in
// SO_SFIELD_REQUIRED_HEADER().
//
////////////////////////////////////////////////////////////////////////////

#define SO_SFIELD_REQUIRED_SOURCE(className) \
\
  SO__FIELD_ID_SOURCE(className)/*;*/ \
  SO__FIELD_EQ_SAME_SOURCE(className) \
\
const className & \
className::operator =(const className &f) \
{ \
  setValue(f.getValue()); \
  return *this; \
}

#if defined(_DEBUG)
#define SO_FIELD_CHECK_INIT(className) { \
  if (classTypeId.isBad()) { \
    SoDebugError::post("Field Constructor", \
                       "Can't construct a field of type " \
                       SO__QUOTE(className) \
                       " until initClass() has been called"); \
    className::initClass(); \
  } \
  SoDB::checkDatabase(SO__QUOTE(className), this, className::getClassTypeId(), classTypeId); \
}
#else
#define SO_FIELD_CHECK_INIT(className) { \
  if (classTypeId.isBad()) { \
    className::initClass(); \
  } \
}
#endif

////////////////////////////////////////////////////////////////////////////
//
// This defines the constructor and destructor.
//
////////////////////////////////////////////////////////////////////////////

#define SO_SFIELD_CONSTRUCTOR_SOURCE(className) \
\
className::className() \
{ \
  SO_FIELD_CHECK_INIT(className) \
} \
className::~className() \
{ \
}

////////////////////////////////////////////////////////////////////////////
//
// This defines the variables and methods declared in
// SO_SFIELD_VALUE_HEADER().
//
////////////////////////////////////////////////////////////////////////////

#define SO_SFIELD_VALUE_SOURCE(className, valueType, valueRef) \
\
void \
className::setValue(valueRef newValue) \
{ \
  value = newValue; \
  valueChanged(); \
} \
\
int \
className::operator ==(const className &f) const \
{ \
  return getValue() == f.getValue(); \
}

////////////////////////////////////////////////////////////////////////////
//
// This macro is all that is needed for most single-value field
// classes. It includes the relevant macros.
//
////////////////////////////////////////////////////////////////////////////

#define SO_SFIELD_SOURCE(className, valueType, valueRef) \
  SO_SFIELD_REQUIRED_SOURCE(className)/*;*/ \
  SO_SFIELD_CONSTRUCTOR_SOURCE(className)/*;*/ \
  SO_SFIELD_VALUE_SOURCE(className, valueType, valueRef)

////////////////////////////////////////////////////////////////////////////
//
// This macro is all that is needed for most single-value field
// classes that are derived from other field classes. It includes the
// relevant macros.
//
////////////////////////////////////////////////////////////////////////////

#define SO_SFIELD_DERIVED_SOURCE(className, valueType, valueRef) \
  SO_SFIELD_REQUIRED_SOURCE(className)/*;*/ \
  SO_SFIELD_CONSTRUCTOR_SOURCE(className)

//===========================================================================
//
// Macros to be called within the source file for a multiple-value field
// subclass:
//
//===========================================================================

////////////////////////////////////////////////////////////////////////////
//
// This initializes type identifer variables. It should be called from
// within initClass().
//
////////////////////////////////////////////////////////////////////////////

#define SO_MFIELD_INIT_CLASS(className,parentClass) \
  SO__FIELD_INIT_CLASS(className, SO__QUOTE(className), parentClass);

#define SO_MFIELD_EXIT_CLASS(className) \
  SO__FIELD_EXIT_CLASS(className)

////////////////////////////////////////////////////////////////////////////
//
// This defines the variables and methods declared in
// SO_MFIELD_REQUIRED_HEADER().
//
////////////////////////////////////////////////////////////////////////////

#define SO_MFIELD_REQUIRED_SOURCE(className) \
\
  SO__FIELD_ID_SOURCE(className) \
  SO__FIELD_EQ_SAME_SOURCE(className) \
\
const className & \
className::operator =(const className &f) \
{ \
  if (f.getNum() < getNum()) \
   deleteAllValues(); \
  setValues(0, f.getNum(), f.getValues(0)); \
  return *this; \
}

////////////////////////////////////////////////////////////////////////////
//
// This defines a constructor and destructor that work with the
// variables and methods defined in SO_MFIELD_VALUE_HEADER(). If you
// define your own value processing differently, you may not be able
// to use these.
//
////////////////////////////////////////////////////////////////////////////

#define SO_MFIELD_CONSTRUCTOR_SOURCE(className) \
\
className::className() \
{ \
  SO_FIELD_CHECK_INIT(className) \
  values = NULL; \
  userDataIsUsed = false; \
  resetChangedStatus (); \
  m_memObj = NULL; \
} \
\
className::~className() \
{ \
    deleteAllValues(); \
\
}

////////////////////////////////////////////////////////////////////////////
//
// This defines an empty constructor and destructor for classes
// derived from other field classes, since they inherit value
// processing.
//
////////////////////////////////////////////////////////////////////////////

#define SO_MFIELD_DERIVED_CONSTRUCTOR_SOURCE(className) \
\
className::className() \
{ \
  SO_FIELD_CHECK_INIT(className) \
  resetChangedStatus (); \
} \
\
className::~className() \
{ \
}

////////////////////////////////////////////////////////////////////////////
//
// This defines the variables and methods declared in
// SO_MFIELD_VALUE_HEADER().
//
////////////////////////////////////////////////////////////////////////////

#define SO_MFIELD_VALUE_SOURCE(className, valueType, valueRef) \
\
int \
className::find(valueRef targetValue, SbBool addIfNotFound) \
{ \
  int i, myNum = getNum(); \
\
  if (values) { \
    for (i = 0; i < myNum; i++) \
      if (values[i] == targetValue) \
        return i; \
  } \
\
  if (addIfNotFound) \
    set1Value(myNum, targetValue); \
\
  return -1; \
} \
\
void \
className::setValues(int start, int myNum, const valueType *newValues) \
{ \
  int newNum = start + myNum, i; \
\
  if (newNum > getNum()) \
    makeRoom(newNum); \
\
  if (values) { \
    for (i = 0; i < myNum; i++) \
      values[start + i] = newValues[i]; \
\
    valueChanged(start, myNum); \
  } \
} \
\
void \
className::set1Value(int index, valueRef newValue) \
{ \
  if (index >= getNum()) \
    makeRoom(index + 1); \
  if (values) { \
    values[index] = newValue; \
    valueChanged(index, 1); \
  } \
} \
\
void \
className::setValue(valueRef newValue) \
{ \
  makeRoom(1); \
  if (values) { \
    values[0] = newValue; \
    valueChanged(0,1); \
  } \
} \
\
int \
className::operator ==(const className &f) const \
{ \
  int i, myNum = getNum(); \
  const valueType *myVals, *itsVals; \
\
  if (myNum != f.getNum()) \
    return FALSE; \
\
  myVals  = getValues(0); \
  itsVals = f.getValues(0); \
\
  for (i = 0; i < myNum; i++) \
    if (! (myVals[i] == itsVals[i])) \
      return FALSE; \
\
  return TRUE; \
} \
\
void \
className::deleteAllValues() \
{ \
    allocValues(0); \
} \
\
void \
className::copyValue(int to, int from) \
{ \
    values[to] = values[from]; \
}

////////////////////////////////////////////////////////////////////////////
//
// This allocates/reallocates room for values, using the "new" and
// "delete" operators, so the constructor and destructor are called
// for new and deleted values.
//
////////////////////////////////////////////////////////////////////////////

#define SO_MFIELD_ALLOC_SOURCE(className, valueType) \
void \
className::allocValues(int newNum) \
{ \
  if (values == NULL) { \
    if (newNum > 0) { \
      values = new valueType[newNum]; \
      if (values == NULL) { \
        SoMemoryError::post( "SO_MFIELD_ALLOC_SOURCE: Cannot allocate memory for the fields!" ); \
        newNum = 0; \
      } \
    } \
  } \
  else { \
    valueType *oldValues = values; \
    int i; \
\
    if (newNum > 0) { \
      values = new valueType[newNum]; \
      if (values == NULL) { \
        SoMemoryError::post( "SO_MFIELD_ALLOC_SOURCE: Cannot allocate memory for the fields!" ); \
        newNum = num; \
      } \
      else { \
        for (i = 0; i < num && i < newNum; i++) \
          values[i] = oldValues[i]; \
        delete [] oldValues; \
      } \
    } \
    else { \
      values = NULL; \
      delete [] oldValues; \
    } \
  } \
\
  num = newNum; \
}

////////////////////////////////////////////////////////////////////////////
//
// This allocates/reallocates room for values, using malloc() and
// realloc(). This means that constructors and destructors will NOT be
// called for values. Therefore, this macro should not be used for any
// value types that have constructors or destructors! (It is used for
// fields that have simple types, like shorts and floats.)
//
// It's not clear why realloc won't work in the "newNum == 1" case, but
// we definitely need to save that last value before freeing the memory!
//
////////////////////////////////////////////////////////////////////////////

#define SO_MFIELD_MALLOC_SOURCE(className, valueType) \
void \
className::allocValues(int newNum) \
{ \
  void *before = (void *)values; \
\
  if (values == NULL) { \
    if (newNum > 0) { \
      values = static_cast<valueType*>(malloc(sizeof(valueType) * newNum)); \
      if (values == NULL) { \
        SoMemoryError::post( "SO_MFIELD_MALLOC_SOURCE: Cannot allocate memory for the fields!" ); \
        newNum = 0; \
      } \
    } \
  } \
  else { \
    /* Jerome Lague BEGIN ADDED on 7/03/06*/ \
    /* Special case when user calls setValue(newValue) to reset field */ \
    /* Necessary to wrap the setValuesPointer method in .NET */ \
    if (newNum == 1) {\
      valueType value0 = *(static_cast<valueType*>(values)); /* Save last value */ \
      if (isDeleteValuesEnabled()) \
        free((char *) values);\
      values = (valueType *) malloc(sizeof(valueType)); \
      if (values == NULL) { \
        SoMemoryError::post( "SO_MFIELD_MALLOC_SOURCE: Cannot allocate memory for the fields!" ); \
        newNum = num; \
      } \
      else { \
        *((valueType *)values) = value0; /* Restore last value */ \
        userDataIsUsed = false;\
      } \
    } \
    /* Jerome Lague END ADDED on 7/03/06*/ \
    else if (newNum > 1) { \
      void *after = NULL; \
      if (userDataIsUsed == false) { \
        after = realloc(values, sizeof(valueType) * newNum); \
      } else { \
        /* if user data is used, allocates a new buffer and copy data into without deleting the user buffer. */ \
        after = malloc(sizeof(valueType) * newNum); \
        if ( after ) \
          memcpy(after, before, sizeof(valueType) * (num < newNum ? num : newNum) ); \
      } \
      if (after == NULL) { \
        SoMemoryError::post( "SO_MFIELD_MALLOC_SOURCE: Cannot allocate memory for the fields!" ); \
        newNum = num; \
      } \
      else \
        values = (valueType *)after; \
    } \
    else { \
      if (userDataIsUsed == false) { \
        free((char *)values); \
      } \
      values = NULL; \
    } \
  } \
  num = newNum; \
\
  if (before != (void *)values) { \
    userDataIsUsed = false; \
  } \
}

////////////////////////////////////////////////////////////////////////////
//
// This macro is all that is needed for most multiple-value field
// classes. It includes the relevant macros, including the allocation
// macro that uses new and delete.
//
////////////////////////////////////////////////////////////////////////////

#define SO_MFIELD_SOURCE(className, valueType, valueRef) \
  SO_MFIELD_REQUIRED_SOURCE(className) \
  SO_MFIELD_CONSTRUCTOR_SOURCE(className) \
  SO_MFIELD_VALUE_SOURCE(className, valueType, valueRef) \
  SO_MFIELD_ALLOC_SOURCE(className, valueType)

////////////////////////////////////////////////////////////////////////////
//
// This is like the above macro, but uses the allocation macro that
// uses malloc() and realloc().
//
////////////////////////////////////////////////////////////////////////////

#define SO_MFIELD_SOURCE_MALLOC(className, valueType, valueRef) \
  SO_MFIELD_REQUIRED_SOURCE(className) \
  SO_MFIELD_CONSTRUCTOR_SOURCE(className) \
  SO_MFIELD_VALUE_SOURCE(className, valueType, valueRef) \
  SO_MFIELD_MALLOC_SOURCE(className, valueType)

////////////////////////////////////////////////////////////////////////////
//
// This macro is all that is needed for most multiple-value field
// classes that are derived from other field classes. It includes the
// relevant macros.
//
////////////////////////////////////////////////////////////////////////////

#define SO_MFIELD_DERIVED_SOURCE(className, valueType, valueRef) \
  SO_MFIELD_REQUIRED_SOURCE(className); \
  SO_MFIELD_DERIVED_CONSTRUCTOR_SOURCE(className)


////////////////////////////////////////////////////////////////////////
//
//  This declares header info required for setValues using user data.
//

#define SO_MFIELD_SETVALUESPOINTER_HEADER(userType) \
public: \
  /** Sets the field to contain the <I>num</I> values stored in <I>userData</I> array. */ \
  /** This array will not be copied */ \
  /** into the field: it will be directly used by the field. */ \
  /** If <I>num</I> and <I>userData</I> are not correctly specified, */ \
  /** the results are undefined (and probably undesirable). */ \
  /** */ \
  /** @param num is the number of values that <I>userData</I> contains */ \
  /** and must be a positive integer. */ \
  /** */ \
  /** @param userData is an array allocated by malloc or realloc and */ \
  /** can be deallocated by free (no constructor or destructor is called). */ \
  /** <I>userData</I> must not be NULL. Its size must be at least */ \
  /** num*sizeof(valueType). */ \
  /** [OIVNET-WRAPPER-ARG NO_WRAP{numElements},ARRAY&ALLOC_REF{Pinned}] */ \
  /** [OIVNET-WRAPPER HELPER_BEGIN{int numElements; OnSetValuesBuffer(userData, numElements);}] */ \
  /** [OIVJAVA-WRAPPER-ARG NO_WRAP{numElements},ARRAY&SHARED] */ \
  /** [OIVJAVA-WRAPPER HELPER_BEGIN{int numElements = onSetValuesBuffer(userData);}] */ \
  void setValuesPointer(int num, const userType *userData); \
\
  /** See setValuesPointer(int, const userType *) */ \
  /** [OIV-WRAPPER-NOT-WRAP] */ \
  void setValuesPointer(int num, userType *userData) 



////////////////////////////////////////////////////////////////////////
//
//  This macro defines setValues method using user data
//  Data will not be duplicated into the field.
//

#include <Inventor/errors/SoDebugError.h>
#define SO_MFIELD_SETVALUESPOINTER_SOURCE(className, valueType, userType) \
void \
className::setValuesPointer(int myNum, const userType *userData) \
{ \
  if (myNum > 0 && userData != NULL) { \
    if ( userDataIsUsed && userData == (const userType*)values ) { \
    } \
    else if (getNum() > 0) { \
      makeRoom(0); \
    } \
    values = (valueType *)userData; \
    userDataIsUsed = true; \
    num = myNum; \
    valueChanged(0, num); \
  } \
  else { \
    const char *error1 = NULL, *error2 = NULL; \
\
    if (myNum <= 0) { \
      error1 = "Bad argument : num (arg 1) is not positive"; \
    } \
    if (userData != NULL) { \
      error2 = "Bad argument : data (arg 2) is NULL"; \
    } \
    SoDebugError::post("setValues", error1, error2); \
  } \
} \
\
void \
className::setValuesPointer(int myNum, userType *userData) \
{ \
  setValuesPointer(myNum, (const userType *)userData); \
}

#endif /* _SO_SUB_FIELD_ */
