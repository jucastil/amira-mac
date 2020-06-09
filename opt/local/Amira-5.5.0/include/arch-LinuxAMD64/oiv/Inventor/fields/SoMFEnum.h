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


#ifndef  _SO_MF_ENUM_
#define  _SO_MF_ENUM_

#include <Inventor/SbString.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFEnum subclass of SoMField. This field holds enumerated types.
//  Each instance of the field must define enumeration mnemonics and
//  character strings. This stores the enumeration values as integers
//  (as allowed by C++).
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Multiple-value field containing any number of enumerated type values.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A multiple-value field that contains any number of enumerated type values,
 *   stored as ints. Nodes that use this field class define mnemonic names for
 *   values. These names should be used when setting or testing the values of the
 *   field, even though the values are treated as integers in the methods.
 *   
 *   SoMFEnums are written to file as a set of mnemonic enumerated type names. These
 *   names differ among uses of this field in various node classes. See the reference
 *   pages for specific nodes for the names.
 *   
 *   When more than one value is present, all of the values are enclosed in square
 *   brackets and separated by commas.
 * 
 * 
 */ 

class INVENTOR_API SoMFEnum : public SoMField {

  // Use standard field stuff
  SO_MFIELD_HEADER(SoMFEnum, int, int);
  SO_MFIELD_SETVALUESPOINTER_HEADER(int);

    public:
  //
  // Some convenience functions:
  //

  /**
   * Sets this field to contain one and only one value, which is the mnemonic name as
   * a string.
   * [OIVNET-WRAPPER HELPER_BEGIN{OnSetValue()}]
   */
  void setValue(const SbName &name);

  /**
    * Gets value/name correspondances.
	* [OIV-WRAPPER-CUSTOM-CODE]
    */
  void getEnums(int &num, int *&vals, SbName *&names);

  /**
   * Sets the @B index @b'th value to be the integer corresponding to the mnemonic
   * name in the given string.
   * [OIVNET-WRAPPER HELPER_BEGIN{OnSet1Value(index)}]
   */
  void set1Value(int index, const SbName &name);

 SoEXTENDER public:
  // Sets up value/name correspondances
  void setEnums(int num, int *vals, SbName *names);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  // TRUE if setEnums called
  bool legalValuesSet;

  // Number of enumeration values
  int numEnums;

  // Enumeration values
  int *enumValues;

  // Mnemonic names of values
  SbName *enumNames;

  // Looks up enum name, returns value. Returns FALSE if not found.
  virtual SbBool findEnumValue(const SbName &name, int &val);

  // Looks up enum value, returns ptr to name. Returns FALSE if not found.
  virtual SbBool findEnumName(int val, const SbName *&name) const;

};


////////////////////////////////////////////
//
//  Debugging macros (used by other macros in this file)
//  The container must have a field 'firstInstance'.
//
#if defined(_DEBUG)
#  define SO__MF_ENUM_CHECK_DATA(vals, typeName, fieldName, containerMacroName) { \
  if (vals == NULL && firstInstance) { \
    SoDebugError::post("SO_SET_MF_ENUM_TYPE", \
                       "Field %s (%s, line %d): Did you forget to" \
                       " use SO_%s_DEFINE_ENUM_VALUE(%s, ...)?", \
                       fieldName, __FILE__, __LINE__, \
                       containerMacroName, typeName); \
  } \
}
#else
#  define SO__MF_ENUM_CHECK_DATA(vals, typeName, fieldName, containerMacroName) ;
#endif
        

////////////////////////////////////////////
//
// This defines the specific type of enum expected by a particular
// SoMFEnum field.
//

#define SO__MF_ENUM_SET_TYPE(fieldName, enumType, contMacroName, contData) { \
  int _so_mf_enum_num; \
  int *_so_mf_enum_vals; \
  SbName *_so_mf_enum_names; \
  contData->getEnumData((char *)SO__QUOTE(enumType), \
                        _so_mf_enum_num, \
                        _so_mf_enum_vals, \
                        _so_mf_enum_names); \
  SO__MF_ENUM_CHECK_DATA(_so_mf_enum_vals, \
                         SO__QUOTE(enumType), \
                         SO__QUOTE(fieldName), \
                         contMacroName); \
  fieldName.setEnums(_so_mf_enum_num, \
                     _so_mf_enum_vals, \
                     _so_mf_enum_names); \
}

#define SO_NODE_SET_MF_ENUM_TYPE(fieldName, enumType) \
  SO__MF_ENUM_SET_TYPE(fieldName,enumType,"NODE",fieldData)

#define SO_ENGINE_SET_MF_ENUM_TYPE(fieldName, enumType) \
  SO__MF_ENUM_SET_TYPE(fieldName,enumType,"ENGINE",inputData)

//
// End of macros
//
/////////////////////////////////////////////////////////////////////////////

#endif /* _SO_MF_ENUM_ */

