/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Jan 2005)
**=======================================================================*/

#ifndef  SO_SF_ARRAY_H
#define  SO_SF_ARRAY_H

#include <Inventor/fields/SoSubField.h>
#include <Inventor/fields/SoSFImage.h>

class SoMemoryObject;
class SoBufferObject;

/**
 * Abstract Field containing an array of values.
 *
 * @ingroup fields
 *
 * @DESCRIPTION
 * Subclasses of this field can contain a 2D or 3D array of values of a specified type.
 *
 * @SEE_ALSO
 *    SoField,
 *    SoSField,
 *    SoSFArray2D,
 *    SoSFArray3D
 *
 *
 */

class INVENTOR_API SoSFArray : public SoSField
{
  SO_SFIELD_REQUIRED_HEADER(SoSFArray);
  SO_SFIELD_CONSTRUCTOR_HEADER(SoSFArray);

public:
  /**
   * SoSFArray may be manipulating some large amounts of memory.
   * It is therefore convienent to be able to set the memory usage
   * policy dynamically. By default, the memory
   * policy is COPY, which is consistent with other OIV fields.
   * The most likely to be efficient is NO_COPY. See also
   * setNeverWrite.
   */
  enum CopyPolicy {
    /**
     *  Open Inventor will make a copy of the data (default)
     */
    COPY = SoMemoryObject::COPY,
#ifdef OIV_NET_DOC
    /**
     *  Passed buffer used.
     */
#else
    /**
     *  Passed buffer used, user will delete
     */
#endif //OIV_NET_DOC
    NO_COPY = SoMemoryObject::NO_COPY,
    /**
     * Passed buffer used, SoSFImage will delete.
     * Use this if memory is allocated with "new".
     */
    NO_COPY_AND_DELETE = SoMemoryObject::NO_COPY_AND_DELETE,
    /**
     * Passed buffer used, SoSFImage will free.
     * Use this if memory is allocated with "malloc".
     */
    NO_COPY_AND_FREE = SoMemoryObject::NO_COPY_AND_FREE
  } ;

  /** Supported data type enumeration values. */
  enum DataType
  { 
    /** UNSIGNED_BYTE */
    UNSIGNED_BYTE  = SbDataType::UNSIGNED_BYTE, 
    /** UNSIGNED_SHORT */
    UNSIGNED_SHORT = SbDataType::UNSIGNED_SHORT, 
    /** UNSIGNED_INT32 */
    UNSIGNED_INT32 = SbDataType::UNSIGNED_INT32, 
    /** SIGNED_BYTE */
    SIGNED_BYTE  = SbDataType::SIGNED_BYTE, 
    /** SIGNED_SHORT */
    SIGNED_SHORT = SbDataType::SIGNED_SHORT, 
    /** SIGNED_INT32 */
    SIGNED_INT32 = SbDataType::SIGNED_INT32, 
    /** FLOAT */
    FLOAT = SbDataType::FLOAT
  } ;

  /**
   * Returns a read-only pointer to the array's values
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{GetSize().Value[0]*GetSize().Value[1]*GetSize().Value[2]*GetValueSize()}]
   * [OIVJAVA-WRAPPER NAME{getData}]
   */
  inline void* getValue() const ;

  /**
   * Returns the data type of the array.
   */
  DataType getDataType() const { return (DataType)m_dataType.getType(); }

  /**
   * Indicates that batch edits have finished. See startEditing().
   */
  void finishEditing();

  /**
   * Returns TRUE if all of the values of this field equal those of the given field f.
   * If the fields are different types FALSE will always be returned.
   */
  virtual int operator ==(const SoSFArray &f) const;

  /**
   * Returns TRUE if all of the values of this field do not equal those of the given field f.
   */
  virtual int operator !=(const SoSFArray &f) const
  { return ! ((*this) == f); }

  /**
   * Sets the "neverWrite" flag.
   * As this field may have to handle large amounts of data and its representation in
   * an .iv file is not very efficient, it is often a good idea not to allow that
   * data to be written out when required by a write action. By default, the
   * "neverWrite" condition is FALSE.
   */
  void setNeverWrite(SbBool neverWrite)
  { m_neverWrite = neverWrite ;}

  /**
   * Returns the "neverWrite" flag.
   */
  SbBool isNeverWrite()
  { return m_neverWrite ; }

  /**
   * Returns the dimensions of the array.
   */
  inline const SbVec3i32& getSize() const;

  /**
   * Returns a pointer to the internally maintained array that can be modified.
   * The values in the array may be changed, but values cannot be added or removed.
   * It is illegal to call any other editing methods between startEditing() and finishEditing()
   * (e.g. setValue(), etc.). Fields,  engines or sensors connected to this field
   * are not triggered until finishEditing() is called.
   * Calling finishEditing() always sets the isDefault() flag to FALSE and informs engines and sensors that
   * the field changed, even if none of the values actually were changed.
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{size.Value[0]*size.Value[1]*size.Value[2]*GetValueSize()}]
   */
  void* startEditing(SbVec3i32 &size, SbDataType& dataType);

  /**
   * Returns the size in bytes of one data value,
   * e.g. returns 1 if the data type is UNSIGNED_BYTE.
   */
  inline virtual size_t getValueSize() const ;

  /**
   * Returns a read-only pointer to the array's values and its dimensions and data type.
   * [OIV-WRAPPER-RETURN-TYPE NAME{buffer},ARRAY{size.Value[0]*size.Value[1]*size.Value[2]*GetValueSize()}]
   * [OIVJAVA-WRAPPER PACK{Array3D}]
   */
  const void* getValue(SbVec3i32 &size, SbDataType &dataType) const ;

  /**
   * Fill the array with data of the specified dimensions and type using the specified copy policy.
   * [OIV-WRAPPER-ARG IN,IN,ARRAY,IN]
   */
  void setValue(const SbVec3i32 &size, const SbDataType& dataType,
                const void* data, CopyPolicy copy=COPY);

  /**
   * Fill the array with the specified dimensions and data from an SoMemoryObject
   * using the specified copy policy.
   * [OIV-WRAPPER-NOT-WRAP]
   */
  void setValue(const SbVec3i32 &size,SoMemoryObject* memObj,
                CopyPolicy copy);

  /** 
   * Returns TRUE if the current array is empty.
   */
  SbBool isEmpty() const;

SoINTERNAL public:
  static void initClass();
  static void exitClass();

  SoBufferObject *getBufferObject() const;

protected:
  /** Dimension of the array */
  int m_dimension;

  /** Width and height of 3D array */
  SbVec3i32     m_size;

  /** Field reading */
  virtual SbBool readValue(SoInput *in);

  /** Field writting */
  virtual void   writeValue(SoOutput *out) const ;

  /** Memory object holding user data */
  SoMemoryObject* m_values ;

private:
  /**
   * When this value is the first data read in binary
   * mode, array has no data
   */
  static const int NO_DATA_FLAG;

  /** Alloc needed space according to dataType */
  template <typename T> void allocValues(int numValues);

  /**
   * Read the current value from the SoInput and store it in
   * m_values at position pos.
   */
  template <typename T> SbBool readAsciiValue(SoInput* in, size_t pos);

  /**
   * Write m_values[pos] at the current pos of SoOutput
   */
  template <typename T> void writeAsciiValue(SoOutput* out, size_t pos) const;

  /** Type of the data */
  SbDataType m_dataType ;

  /** Specify how to handle passed buffer */
  CopyPolicy  m_copyPolicy;

  /** If true, don't write data in the file */
  SbBool      m_neverWrite;
};

/*----------------------------------------------------------------------------*/
void*
SoSFArray::getValue() const
{
  if (isEmpty())
    return NULL;

  return m_values?m_values->get():NULL;
}

/*----------------------------------------------------------------------------*/
const SbVec3i32&
SoSFArray::getSize() const
{
  return m_size;
}

/*----------------------------------------------------------------------------*/
size_t
SoSFArray::getValueSize() const
{
  return m_dataType.getSize();
}/*----------------------------------------------------------------------------*/


#endif /* _SO_SF_ARRAY_H */
