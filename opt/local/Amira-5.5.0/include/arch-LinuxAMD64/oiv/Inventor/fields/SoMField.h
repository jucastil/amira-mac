/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_MFIELD_
#define  _SO_MFIELD_

#include <Inventor/fields/SoField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoMField
//
//  Field that can have multiple values.
//
//////////////////////////////////////////////////////////////////////////////

#ifdef OIV_NET_DOC
/**
* Base class for all multiple-valued fields.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   Each class derived from SoMField begins with an SoMF prefix and contains a
*   dynamic array of values of a particular type. Each has a SetValues()
*   method that is passed a reference to an array of values of the correct type;
*   these values are copied into the array in the field, making extra room in the
*   array if necessary. The start and num parameters to this method indicate the
*   starting array index to copy into and the number of values to copy.
*   
*   The GetValues() method for a multiple-value field returns a reference
*   to the array of values in the field.
*   
*   In addition, the indexing operator "[ ]" is overloaded to return the @B i @b'th
*   value in the array; because it returns a const reference, it can be used only to
*   get values, not to set them.
*   
*   Methods are provided for getting the number of values in the field, inserting
*   space for new values in the middle, and deleting values.
*   
*   There are other methods that allow you to set only one value of several in the
*   field and to set the field to contain one and only one value.
*   
*   Two other methods can be used to make several changes to a multiple-value field
*   without the overhead of copying values into and out of the fields. The
*   StartEditing() method returns a native array reference to the array of values
*   in the field; this reference can then be used to change (but not add or remove)
*   any values in the array. The FinishEditing() method indicates that the
*   editing is done and notifies any sensors or engines that may be connected to the
*   field.
*   
*   SoMFields are written to file as a series of values separated by commas, all
*   enclosed in square brackets. If the field has no values (getNum() returns
*   zero), then only the square brackets ("[ ]") are written. The last value may
*   optionally be followed by a comma. Each field subtype defines how the values are
*   written; for example, a field whose values are integers might be written as:
*   
*   <PRE>
*    [ 1, 2, 3, 4 ]
*    </PRE>
*    or:
*   
*   <PRE>
*    [ 1, 2, 3, 4, ]
*    </PRE>
*    
* 
* @SEE_ALSO
*    SoNode,
*    SoEngine
* 
* 
*/ 
#else
/**
* Base class for all multiple-valued fields.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   Each class derived from SoMField begins with an SoMF prefix and contains a
*   dynamic array of values of a particular type. Each has a setValues()
*   method that is passed a pointer to a const array of values of the correct type;
*   these values are copied into the array in the field, making extra room in the
*   array if necessary. The start and num parameters to this method indicate the
*   starting array index to copy into and the number of values to copy.
*   
*   The getValues() method for a multiple-value field returns a const pointer
*   to the array of values in the field. (Because this pointer is const, it cannot
*   be used to change values in this array.)
*   
*   In addition, the indexing operator "[ ]" is overloaded to return the @B i @b'th
*   value in the array; because it returns a const reference, it can be used only to
*   get values, not to set them.
*   
*   Methods are provided for getting the number of values in the field, inserting
*   space for new values in the middle, and deleting values.
*   
*   There are other methods that allow you to set only one value of several in the
*   field and to set the field to contain one and only one value.
*   
*   Two other methods can be used to make several changes to a multiple-value field
*   without the overhead of copying values into and out of the fields. The
*   startEditing() method returns a non-const pointer to the array of values
*   in the field; this pointer can then be used to change (but not add or remove)
*   any values in the array. The finishEditing() method indicates that the
*   editing is done and notifies any sensors or engines that may be connected to the
*   field.
*   
*   SoMFields are written to file as a series of values separated by commas, all
*   enclosed in square brackets. If the field has no values (getNum() returns
*   zero), then only the square brackets ("[ ]") are written. The last value may
*   optionally be followed by a comma. Each field subtype defines how the values are
*   written; for example, a field whose values are integers might be written as:
*   
*   <PRE>
*    [ 1, 2, 3, 4 ]
*    </PRE>
*    or:
*   
*   <PRE>
*    [ 1, 2, 3, 4, ]
*    </PRE>
*    
* 
* @SEE_ALSO
*    SoNode,
*    SoEngine
* 
* 
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SoMField : public SoField {

 public:
  // Destructor
#ifndef HIDDEN_FROM_DOC
  virtual ~SoMField();
#endif // HIDDEN_FROM_DOC

  /**
   * Returns the number of values currently in the field.
   */
  int getNum() const { evaluate(); return num; }

  /**
   * Forces this field to have exactly @B num @b values, inserting or deleting
   * values as necessary.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetNum(num)}]
   * [OIVJAVA-WRAPPER-HELPER BEGIN{onSetNum(num)}]
   */
  void setNum(int num);

  /**
   * Deletes @B num @b values beginning at index @B start @b (index @B start @b
   * through @B start @b + @B num @b -1 will be deleted, and any leftover values will
   * be moved down to fill in the gap created). A @B num @b of -1 means delete all
   * values from @B start @b to the last value in the field; getNum() will
   * return @B start @b as the number of values in the field after this operation
   * ( @B deleteValues(0, -1) empties the field @b ).
   * [OIVNET-WRAPPER-HELPER BEGIN{OnDeleteValues(start, num)}]
   * [OIVJAVA-WRAPPER-HELPER BEGIN{onDeleteValues(start, num)}]
   */
  virtual void deleteValues(int start, int num = -1);

  /**
   * Inserts space for @B num @b values at index @B start @b. Index @B start @b
   * through @B start @b + @B num @b -1 will be moved up to make room. For example, to
   * make room for 7 new values at the beginning of the field call @B insertSpace(0,
   * 7) @b .
   * [OIVNET-WRAPPER-HELPER BEGIN{OnInsertSpace(start, num)}]
   * [OIVJAVA-WRAPPER-HELPER BEGIN{onInsertSpace(start, num)}]
   */
  virtual void insertSpace(int start, int num);

  /**
   * This is equivalent to the set() method of SoField,
   * but operates on only one value. See the SoField methods for details.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSet1Value(index)}]
   * [OIVJAVA-WRAPPER-HELPER BEGIN{onSet1Value(index)}]
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE SbBool set1(int index, const char *valueString);


  /**
   * This is equivalent to the set() method of SoField,
   * but operates on only one value. See the SoField methods for details.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSet1Value(index)}]
   * [OIVJAVA-WRAPPER-HELPER BEGIN{onSet1Value(index)}]
   */
  SbBool set1(int index, const SbString& valueString);

  /**
   * This is equivalent to the get() method of SoField,
   * but operates on only one value. See the SoField methods for details.
   */
  void get1(int index, SbString &valueString);

  /**
   * Return the type identifier for this field class.
   */
  static SoType getClassTypeId();
  
 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  static void *createInstance(SoType* dynamicType = NULL);
  
  // Data change notification
  int  getChangedStartIndex();
  int  getChangedNumValues();
  int  getChangedType();

  void valueChanged(int start = -1, int numValues = -1, SbBool resetDefault = TRUE);

  // Reads one indexed value of field from file
  virtual SbBool read1Value(SoInput *in, int index) = 0;
  
  // Writes indexed value to file
  virtual void write1Value(SoOutput *out, int index) const = 0;

  virtual void writeBinaryValues(SoOutput*, int , int ) const;
  virtual SbBool readBinaryValues(SoInput*, int , int );
  virtual void* getValuesPointer( int ) { return NULL; }

 protected:
  // Number of values
  int num;
  
  // Constructor
  SoMField();
  
  // Make sure there is room for newNum vals
  virtual void makeRoom(int newNum);

  // Notified changes
  void  resetChangedStatus();
  int   changedStartIndex;
  int   changedNumValues;

private:
  static SoType classTypeId;
  
  // Allocates room for num values. Copies old values (if any) into
  // new area. Deletes old area, if any.
  virtual void allocValues(int num) = 0;
  
  // Deletes all current values
  virtual void deleteAllValues() = 0;
  
  // Copies value indexed by "from" to value indexed by "to"
  virtual void copyValue(int to, int from) = 0;
  
  // Reads all values of field
  virtual SbBool readValue(SoInput *in);
  
  // Writes all values of field
  virtual void writeValue(SoOutput *out) const;
  
  // Reads array of binary values from file
  virtual SbBool readBinaryValues(SoInput *in, int numToRead);
  
  // Writes array of binary values to file
  virtual void writeBinaryValues(SoOutput *out) const;
  
  // Returns number of ASCII values to write per output line (default 1)
  virtual int   getNumValuesPerLine() const;
  
protected:
  SoMemoryObject* m_memObj;
};

#endif /* _SO_MFIELD_ */
