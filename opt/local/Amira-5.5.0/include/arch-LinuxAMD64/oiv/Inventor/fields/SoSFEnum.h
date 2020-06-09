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


#ifndef  _SO_SF_ENUM_
#define  _SO_SF_ENUM_

#include <Inventor/SbString.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFEnum subclass of SoSField. This field holds enumerated types.
//  Each instance of the field must define enumeration mnemonics and
//  character strings. This stores the enumeration values as integers
//  (as allowed by C++).
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Field containing an enumerated value.
 *
 * @ingroup fields
 *
 * @DESCRIPTION
 *   A single-value field that contains an enumerated type value, stored as an
 *   integer. Nodes that use this field class define mnemonic names for the values.
 *   These names should be used when setting or testing the values of the field, even
 *   though the values are treated as integers in the methods.
 *
 *   SoSFEnums are written to file as a mnemonic enumerated type name. The name
 *   differs among uses of this field in various node or engine classes. See the
 *   reference pages for specific nodes or engines for the names (e.g. SoDrawStyle).
 *
 * @SEE_ALSO
 *    SoField,
 *    SoSField,
 *    SoMFEnum
 *
 *
 */

class INVENTOR_API SoSFEnum : public SoSField {
  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFEnum, int, int);

 public:
  /**
   * Sets this field to contain the given mnemonic name, passed in as a name or
   * string.
   */
  void                setValue(const SbName &name);

  /**
    * Gets value/name correspondances.
    * [OIV-WRAPPER-ARG NO_WRAP,OUT&ARRAY{num},OUT&ARRAY{num}]
    */
  void                getEnums(int &num, int *&vals, SbName *&names);

 SoEXTENDER public:

  // Sets up value/name correspondances
  void                setEnums(int num, int *vals, SbName *names);


 SoINTERNAL public:
  static void         initClass();
  static void exitClass();

  // Looks up enum name, returns value. Returns FALSE if not found.
  virtual SbBool      findEnumValue(const SbName &name, int &val);

 protected:
  bool                legalValuesSet; // TRUE if setEnums called
  int                 numEnums;       // Number of enumeration values
  int                 *enumValues;    // Enumeration values
  SbName              *enumNames;     // Mnemonic names of values

  // Looks up enum value, returns ptr to name. Returns FALSE if not found.
  virtual SbBool      findEnumName(int val, const SbName *&name) const;

};


////////////////////////////////////////////
//
//  Debugging macros (used by other macros in this file).
//  The container must have a field 'firstInstance'.
//
#if defined(_DEBUG)
#define SO__SF_ENUM_CHECK_DATA(vals, typeName, fieldName, containerMacroName) { \
  if (vals == NULL && firstInstance)                                  \
    SoDebugError::post("SO_SET_SF_ENUM_TYPE",                         \
                       "Field %s (%s, line %d): Did you forget to"    \
                       " use SO_%s_DEFINE_ENUM_VALUE(%s, ...)?",      \
                       fieldName, __FILE__, __LINE__,                 \
                       containerMacroName, typeName);                 \
}
#else
#define SO__SF_ENUM_CHECK_DATA(vals, typeName, fieldName, containerMacroName) {}
#endif


////////////////////////////////////////////
//
// This defines the specific type of enum expected by a particular
// SoSFEnum field.
//

#define SO__SF_ENUM_SET_TYPE(fieldName, enumType, contMacroName, contData) {    \
  int _so_sf_enum_num;                                                \
  int *_so_sf_enum_vals;                                                      \
  SbName *_so_sf_enum_names;                                          \
  contData->getEnumData((char *)SO__QUOTE(enumType),                  \
                        _so_sf_enum_num,                              \
                        _so_sf_enum_vals,                             \
                        _so_sf_enum_names);                           \
  SO__SF_ENUM_CHECK_DATA(_so_sf_enum_vals,                            \
                         SO__QUOTE(enumType),                         \
                         SO__QUOTE(fieldName),                        \
                         contMacroName);                                      \
  fieldName.setEnums(_so_sf_enum_num,                                 \
                     _so_sf_enum_vals,                                \
                     _so_sf_enum_names);                                      \
}

#define SO_NODE_SET_SF_ENUM_TYPE(fieldName, enumType)                         \
    SO__SF_ENUM_SET_TYPE(fieldName,enumType,"NODE",fieldData)

#define SO_ENGINE_SET_SF_ENUM_TYPE(fieldName, enumType)                       \
    SO__SF_ENUM_SET_TYPE(fieldName,enumType,"ENGINE",inputData)

//
// End of macros
//
/////////////////////////////////////////////////////////////////////////////


#endif /* _SO_SF_ENUM_ */

