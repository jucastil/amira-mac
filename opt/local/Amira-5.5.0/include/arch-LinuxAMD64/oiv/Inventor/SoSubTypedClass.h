/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef SO_TYPED_CLASS_
#define SO_TYPED_CLASS_

#include <Inventor/SoType.h>


#define SO_TYPED_CLASS_INTERNAL_HEADER()                        \
public:                                                         \
  SoType getTypeId() const;                                     \
  static SoType getClassTypeId();                               \
  static void *createFromSoType(SoType* dynamicType = NULL);    \
private:                                                        \
  static SoType   m_classTypeId;                                \
  static SbBool   m_isFirstTime

#define SO_TYPED_CLASS_HEADER()                                 \
  SO_TYPED_CLASS_INTERNAL_HEADER();                             \
public:                                                         \
  static void initClass();                                      \
  static void exitClass()

#define SO_TYPED_CLASS_ABSTRACT_VARS(className)                  \
    SoType className::m_classTypeId;                              \
    SbBool className::m_isFirstTime = TRUE;
//
// Non-abstract nodes have all the stuff abstract nodes do
//
#define SO_TYPED_CLASS_VARS(className) \
    SO_TYPED_CLASS_ABSTRACT_VARS(className)

#define SO_TYPED_CLASS_INTERNAL_SOURCE(parent, className, classPrintName)        \
                                                                        \
  SO_TYPED_CLASS_ABSTRACT_VARS(className)                                \
                                                                        \
  SoType                                                                \
  className::getTypeId() const                                          \
  {                                                                     \
    return m_classTypeId;                                               \
  }                                                                     \
                                                                        \
  SoType                                                                \
  className::getClassTypeId()                                           \
  {                                                                     \
    return m_classTypeId;                                               \
  }                                                                     \
                                                                        \
  void *                                                                \
  className::createFromSoType(SoType*)                                    \
  {                                                                     \
    return (void *)(new className);                                     \
  }

#define SO_TYPED_CLASS_SOURCE(parentClass, className, classPrintName)        \
  SO_TYPED_CLASS_INTERNAL_SOURCE(parentClass,className,classPrintName)       \
                                                                        \
  void                                                                  \
  className::initClass()                                                \
  {                                                                     \
    SO_TYPED_CLASS_INIT_CLASS(className,classPrintName,parentClass)     \
  }                                                                     \
                                                                        \
  void                                                                  \
  className::exitClass()                                                \
  {                                                                     \
    SO_TYPED_CLASS_EXIT_CLASS(className,classPrintName)                 \
  }

#define SO_TYPED_CLASS_ABSTRACT_INTERNAL_SOURCE(className)              \
  SO_TYPED_CLASS_ABSTRACT_VARS(className)

#define SO_TYPED_CLASS_ABSTRACT_SOURCE(className, classPrintName)       \
  SO_TYPED_CLASS_ABSTRACT_INTERNAL_SOURCE(className)                    \
  void                                                                  \
  className::initClass()                                                \
  {                                                                     \
    SO_TYPED_CLASS_INIT_ABSTRACT_CLASS(className, classPrintName)       \
  }                                                                     \
                                                                        \
  void                                                                  \
  className::exitClass()                                                \
  {                                                                     \
    SO_TYPED_CLASS_EXIT_ABSTRACT_CLASS(className,classPrintName)        \
  }

#define SO_TYPED_CLASS_ABSTRACT_INTERNAL_HEADER()               \
public:                                                         \
  virtual SoType getTypeId() const = 0;                         \
  static SoType getClassTypeId() { return m_classTypeId; }      \
                                                                \
private:                                                        \
  static SoType   m_classTypeId;                                \
  static SbBool   m_isFirstTime
  
#define SO_TYPED_CLASS_ABSTRACT_HEADER()                        \
  SO_TYPED_CLASS_ABSTRACT_INTERNAL_HEADER();                    \
public:                                                         \
  static void initClass();                                      \
  static void exitClass();

#define SO_TYPED_CLASS_INIT_ABSTRACT_CLASS(className,classPrintName) \
  if (m_isFirstTime) {                                                \
      m_classTypeId = SoType::createType(SoType::badType(), classPrintName); \
      m_isFirstTime = FALSE;                                            \
    }

#define SO_TYPED_CLASS_EXIT_ABSTRACT_CLASS(className,classPrintName) \
  SoType::removeType(classPrintName);                                 \
  m_classTypeId = SoType::badType();                                  \
  m_isFirstTime = TRUE;

#define SO_TYPED_CLASS_INIT_CLASS(className,classPrintName,parentClass) \
  if (m_isFirstTime)                                                  \
  {                                                                   \
    if (parentClass::getClassTypeId() == SoType::badType() )               \
      parentClass::initClass();                                            \
    m_classTypeId = SoType::createType(parentClass::getClassTypeId(),      \
                                        classPrintName,                \
                                        &className::createFromSoType);   \
    m_isFirstTime = FALSE;                                            \
  }

#define SO_TYPED_CLASS_EXIT_CLASS(className,classPrintName) \
  SO_TYPED_CLASS_EXIT_ABSTRACT_CLASS(className,classPrintName)

#endif
