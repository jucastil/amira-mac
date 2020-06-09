/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. OGNIER (Jun 2003)
**=======================================================================*/


#ifndef _SOSUBIMAGERASTERRW_
#define _SOSUBIMAGERASTERRW_

#include <Inventor/SoType.h> 

///////////////////////////////////////////////////////////
//
//  Internal initialization macros
//
#define SO_IMAGE_RASTER_RW_SOURCE(parent, className, classPrintName) \
\
  SoType className::m_classTypeId; \
\
  SoType \
  className::getClassTypeId() \
  { \
    return m_classTypeId; \
  } \
\
  SoType \
  className::getTypeId() const \
  { \
    return m_classTypeId; \
  } \
\
  void \
  className::initClass() \
  { \
    if ( m_classTypeId.isBad() ) { \
      if (parent::getClassTypeId().isBad() ) \
        parent::initClass(); \
      m_classTypeId = SoType::createType(parent::getClassTypeId(), classPrintName); \
    } \
  } \
\
  void \
  className::exitClass() \
  { \
    if ( m_classTypeId != SoType::badType() ) { \
      SoType::removeType(m_classTypeId.getName()); \
      m_classTypeId = SoType::badType(); \
    } \
  } 



#define SO_IMAGE_RASTER_RW_ABSTRACT_SOURCE(className, classPrintName) \
\
  SoType className::m_classTypeId; \
\
  SoType \
  className::getClassTypeId() \
  { \
    return m_classTypeId; \
  } \
\
  void \
  className::initClass() \
  { \
    if ( m_classTypeId.isBad() ) { \
      m_classTypeId = SoType::createType(SoType::badType(), classPrintName); \
    } \
  } \
\
  void \
  className::exitClass() \
  { \
    if ( m_classTypeId != SoType::badType() ) { \
      SoType::removeType(m_classTypeId.getName()); \
      m_classTypeId = SoType::badType(); \
    } \
  } 



#define SO_IMAGE_RASTER_RW_HEADER() \
  public: \
    /** Returns the type identifier for this specific instance. */ \
    virtual SoType getTypeId() const; \
    /** Returns the type identifier for this class.  */ \
    static SoType getClassTypeId(); \
  SoINTERNAL public: \
    static void initClass(); \
    static void exitClass(); \
\
  private: \
    static SoType   m_classTypeId;

#define SO_IMAGE_RASTER_RW_ABSTRACT_HEADER() \
  public: \
     /** Returns the type identifier for this specific instance. */ \
     virtual SoType getTypeId() const = 0; \
     /** Returns the type identifier for this class.  */ \
     static SoType getClassTypeId(); \
  SoINTERNAL public: \
     static void initClass(); \
     static void exitClass(); \
\
  private: \
    static SoType   m_classTypeId;

#endif

