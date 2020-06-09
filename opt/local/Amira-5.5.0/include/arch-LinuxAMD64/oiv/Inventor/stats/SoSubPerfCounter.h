/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2005)
**=======================================================================*/


#include <Inventor/SoType.h>

/*************************************************************************/
// SO_PERF_COUNTER_HEADER macro.
// Description :
//  Defines common methods and definition for all stats commands.
//  The macro takes one parameter: the class.
//-------------------------------------------------------------------------
#define SO_PERF_COUNTER_HEADER(className) \
public: \
  static void initClass(); \
  static void exitClass(); \
  static SoType getClassTypeId(); \
  virtual SoType getTypeId() const; \
private:  \
  static SoType m_classTypeId;

/*************************************************************************/
// SO_PERF_COUNTER_SOURCE macro.
// Description :
//  Defines common methods and definition for all stats commands.
//  The macro takes two parameters:
//  - the class
//  - the inherited class
//-------------------------------------------------------------------------
#define SO_PERF_COUNTER_SOURCE(className, inheritClass) \
SoType className::m_classTypeId; \
void className::initClass() { \
  if (m_classTypeId.isBad()) { \
    if (inheritClass::getClassTypeId().isBad() ) \
      inheritClass::initClass(); \
    m_classTypeId = SoType::createType(inheritClass::getClassTypeId(), #className);  \
    m_classTypeId.makeInternal(); \
  } \
} \
void className::exitClass() { \
  if (m_classTypeId != SoType::badType()) { \
    SoType::removeType(m_classTypeId.getName());  \
    m_classTypeId = SoType::badType(); \
  } \
} \
SoType className::getClassTypeId() { return className::m_classTypeId; } \
SoType className::getTypeId() const { return className::m_classTypeId; }
/**/
