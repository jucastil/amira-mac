/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  SB_DATATYPE_H
#define  SB_DATATYPE_H

#include <Inventor/STL/map>

#include <Inventor/SbBase.h>
#include <Inventor/SbString.h>
#include <Inventor/sys/port.h>
#include <Inventor/STL/limits>

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

/**
 * Class encoding a data type
 *
 * @ingroup Basics
 *
 * @DESCRIPTION
 *   This is a basic Open Inventor type that is used for representing a data type,
 *   for example unsigned int32, and some information about that type, for example
 *   is it signed or not. It is used by classes handling user buffers
 *   such as SoMemoryObject, SoSFArray2D, SoSFArray3D
 *
 * @SEE_ALSO
 *   SoMemoryObject,
 *   SoSFArray2D,
 *   SoSFArray3D
 *
 *
 */
class INVENTORBASE_API SbDataType
{
public:
  /**
   * Supported Data type
   */
  enum DataType
  {
    /** unsigned byte */
    UNSIGNED_BYTE = 0,
    /** unsigned short */
    UNSIGNED_SHORT = 1,
    /** unsigned int (32bits) */
    UNSIGNED_INT32 = 2,
    /** signed byte */
    SIGNED_BYTE = 4,
    /** signed short */
    SIGNED_SHORT = 5,
    /** signed int (32bits) */
    SIGNED_INT32 = 6,
    /** float */
    FLOAT = 10,
    /** Double */
    DOUBLE = 11,
    /** unknown data type */
    UNKNOWN = 0xFFFF
  };

  /**
   * Copy constructor
   */
  SbDataType(DataType type) : m_type(type) {}

  /**
   * Constructor from a string.
   * Valid strings are the enum names.
   */
  SbDataType(const SbString& type);

  /**
   * Default constructor.  The initial value is UNSIGNED_BYTE.
   */
  SbDataType() : m_type(UNSIGNED_BYTE) {}

  /**
   * Cast to unsigned int
   */
  inline operator unsigned int() const;

  /**
   * Return the type
   */
  inline DataType getType() const;

  /**
   * Return size in byte of the type
   */
  inline unsigned int getSize() const;

  /**
   * Return true if the type is signed
   */
  inline SbBool isSigned() const;

  /**
   * Return true if the type is an integer type
   */
  inline SbBool isInteger() const;

  /**
   * Return the numer of bits in the type
   */
  inline unsigned int getNumBits() const;

  /**
   * Return the string representation
   */
  SbString getString() const;

  /**
   * Return the minimum value of the type. @BR
   * For floating point type, returns the minimum positive normalized value.
   */
  double getMin() const;

  /**
   * Return the maximum value of the type
   */
  double getMax() const;


SoINTERNAL public:
  /**
   * Init static members
   */
  static void initClass();

  /**
   * Normalize given value into a double
   * precision floating point.
   * Floating point value are not normalized and returned as is.
   * @param val value to normalize
   * @return a double between [-1,1]
   */
  inline double normalize(double val) const;

  /**
   * Used to disable warning constant expression warning
   * in macros using the "if (true)" trick. See SbDataTypeMacros.h
   */
  static const bool m_true;

  /**
   * Constructor from a int.
   */
  SbDataType(int type) { m_type = static_cast<DataType>(type); };

  template<typename T> static SbDataType getTemplateType (const T&);

private:
  typedef std::map<DataType, SbString> TypeToStrMap;

  /** Return min value of given type */
  template<typename T> static double getMinInternal();

  /** Return max value of given type */
  template<typename T> static double getMaxInternal();


  /** The data type */
  DataType m_type;

  /** Used to map between type and string representation */
  static TypeToStrMap m_typeToStrMap;
};

/*******************************************************************************/
SbDataType::DataType
SbDataType::getType() const
{
  return m_type;
}

/*******************************************************************************/
SbDataType::operator unsigned int() const
{
  return static_cast<unsigned int>(m_type);
}


/*******************************************************************************/
SbBool
SbDataType::isSigned() const
{
  // signed type start from enum value 4
  return ( (m_type >> 2)?TRUE:FALSE );
}

/*******************************************************************************/
unsigned int
SbDataType::getSize() const
{
  return (1 << (m_type % 4));
}

/*******************************************************************************/
unsigned int
SbDataType::getNumBits() const
{
  return (1 << (m_type % 4)) * 8;
}

/*******************************************************************************/
SbBool
SbDataType::isInteger() const
{
  return ( (m_type < 10)?TRUE:FALSE );
}

/*******************************************************************************/
double
SbDataType::normalize(double val) const
{
  if ( m_type != SbDataType::FLOAT )
  {
    double minType = getMin();
    double maxType = getMax();
    val = (val-minType)/(maxType-minType);

    if ( isSigned() )
      val = (val-0.5)*2.;
  }

  return val;
}

template<>
inline 
SbDataType
SbDataType::getTemplateType (const unsigned char&)
{
  return SbDataType(SbDataType::UNSIGNED_BYTE);
}

template<>
inline 
SbDataType
SbDataType::getTemplateType (const unsigned short&)
{
  return SbDataType(SbDataType::UNSIGNED_SHORT);
}

template<>
inline 
SbDataType
SbDataType::getTemplateType (const uint32_t&)
{
  return SbDataType(SbDataType::UNSIGNED_INT32);
}

template<>
inline 
SbDataType
SbDataType::getTemplateType (const signed char&)
{
  return SbDataType(SbDataType::SIGNED_BYTE );
}

template<>
inline 
SbDataType
SbDataType::getTemplateType (const signed short&)
{
  return SbDataType(SbDataType::SIGNED_SHORT);
}

template<>
inline 
SbDataType
SbDataType::getTemplateType (const int&)
{
  return SbDataType(SbDataType::SIGNED_INT32);
}

template<>
inline 
SbDataType
SbDataType::getTemplateType (const float&)
{
  return SbDataType(SbDataType::FLOAT);
}

template<>
inline 
SbDataType
SbDataType::getTemplateType (const double&)
{
  return SbDataType(SbDataType::DOUBLE);
}

template<typename T> 
inline 
SbDataType 
SbDataType::getTemplateType (const T&)
{
  return SbDataType(SbDataType::UNKNOWN);
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // SB_DATATYPE_H


