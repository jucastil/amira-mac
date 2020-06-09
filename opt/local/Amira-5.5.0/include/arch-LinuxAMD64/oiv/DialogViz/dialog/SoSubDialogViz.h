/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef SOQT
  #ifdef _WIN32
    #define MAX_DIMENSION 0x7fffffff  // = max int32
  #else
    #define MAX_DIMENSION 65535 // = max unsigned short
  #endif
#else
  #define MAX_DIMENSION 32767 // = max short
#endif

#define FIELD_SENSOR(field) \
  SoFieldSensor* SO__CONCAT(field, Sensor)

#define SENSOR(field) \
  SO__CONCAT(field, Sensor)

#define SO_DG_HEADER(className) \
  SO_KIT_HEADER(className)

#define SO_DG_SOURCE(className) \
  SO_KIT_SOURCE(className)

#define SO_DG_CONSTRUCTOR(className) \
  SO_KIT_CONSTRUCTOR(className)

#define SO_DG_ADD_FIELD(fieldName, defValue) \
  SO_KIT_ADD_FIELD(fieldName, defValue)

#define SO_DG_ADD_CATALOG_ENTRY(partName, partClassName, nullByDefault, parentName, rightName, isPublicPart) \
  SO_KIT_ADD_CATALOG_ENTRY(partName, partClassName, nullByDefault, parentName, rightName, isPublicPart)

#define SO_DG_DEFINE_ENUM_VALUE(field, value) \
SO_KIT_DEFINE_ENUM_VALUE(field, value)

#define SO_DG_SET_SF_ENUM_TYPE(field, typeStruct) \
SO_KIT_SET_SF_ENUM_TYPE(field, typeStruct)

#define SO_DG_CATALOG_ENTRY_HEADER(resource) \
SO_KIT_CATALOG_ENTRY_HEADER(resource)

#define SO_DG_INIT_INSTANCE() \
  SO_KIT_INIT_INSTANCE()

#define SO__DG_INIT_CLASS(className, parentPrintClass, parentClass) \
  SO__KIT_INIT_CLASS(className, parentPrintClass, parentClass)

#define SO_DG_INIT_CLASS(className, parentClass, parentPrintClass) \
  SO_KIT_INIT_CLASS(className, parentClass, parentPrintClass)

#define SO__DG_EXIT_CLASS(className) \
  SO__KIT_EXIT_CLASS(className)

#define SO_DG_EXIT_CLASS(className) \
  SO__KIT_EXIT_CLASS(className)

#define ATTACH_FIELD(field) \
  if (SO__CONCAT(field, Sensor) && SO__CONCAT(field, Sensor)->getAttachedField() != &field) \
    SO__CONCAT(field, Sensor)->attach(&field)

#define DETACH_FIELD(field) \
  if (SO__CONCAT(field, Sensor) && SO__CONCAT(field, Sensor)->getAttachedField()) \
    SO__CONCAT(field, Sensor)->detach()

#define ADD_FIELD_SENSOR(field) \
  SO__CONCAT(field, Sensor) = NULL

#define DELETE_FIELD_SENSOR(field) \
  if (SO__CONCAT(field, Sensor)) \
    delete SO__CONCAT(field, Sensor)

#define INIT_FIELD_SENSOR(field) \
  if (SO__CONCAT(field, Sensor) == NULL) { \
    SO__CONCAT(field, Sensor) = new SoFieldSensor(fieldChangedCB, this); \
    SO__CONCAT(field, Sensor)->setPriority(0); \
    ATTACH_FIELD(field); }

#ifndef SOQT
  #ifdef _WIN32
    #define DG_FONT HFONT
  #else
    #define DG_FONT char*
  #endif
#else
  #define DG_FONT QFont
#endif

/**/
