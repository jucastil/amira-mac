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


#ifndef  _SO_MF_UINT32_
#define  _SO_MF_UINT32_

#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFUInt32 subclass of SoMField.
//
//////////////////////////////////////////////////////////////////////////////

#ifdef OIV_NET_DOC
/**
* Multiple-value field containing any number of uint32_t integers.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   A multiple-value field that contains any number of uint32_t (32-bit) integers.
*   
*   SoMFUInt32s are written to file as one or more uint32_t integers, in decimal,
*   hexadecimal or octal format.
*   
*   When more than one value is present, all of the values are enclosed in square
*   brackets and separated by commas; for example:
*   
*   <PRE>
*    [ 17, 0xFFFFE0, 0755 ]
*    </PRE>
*    @H3 Using an Application-Supplied Array @h3
*   
*   The SetValuesPointer() methods allow Open Inventor to directly use an array
*   of values supplied by the application. 
*   
*   The values may be modified by directly modifying the application memory and
*   calling Touch() to notify Open Inventor of the change. The values may also
*   be modified using the usual methods (Set1Value(), etc.)
*   
*   However, note that some methods (SetNum(), deleteValues(),
*   InsertSpace(), SetValues(), Set1Value(), SetValue()) may
*   force Open Inventor to allocate a larger block of memory to hold all the values.
*   In this case, Open Inventor will allocate memory and copy the data. 
*   
*   See SoMFVec3f for example code showing the use of setValuesPointer().
* 
* 
*/ 
#else
/**
* Multiple-value field containing any number of uint32_t integers.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   A multiple-value field that contains any number of uint32_t (32-bit) integers.
*   
*   SoMFUInt32s are written to file as one or more uint32_t integers, in decimal,
*   hexadecimal or octal format.
*   
*   When more than one value is present, all of the values are enclosed in square
*   brackets and separated by commas; for example:
*   
*   <PRE>
*    [ 17, 0xFFFFE0, 0755 ]
*    </PRE>
*    @H3 Using an Application-Supplied Array @h3
*   
*   The setValuesPointer() methods allow Open Inventor to directly use an array
*   of values supplied by the application. The application data is not copied and
*   the memory will not be deleted by Open Inventor unless enableDeleteValues()
*   is called. 
*   
*   The values may be modified by directly modifying the application memory and
*   calling touch() to notify Open Inventor of the change. The values may also
*   be modified using the usual methods (set1Value(), etc.)
*   
*   However, note that some methods (setNum(), deleteValues(),
*   insertSpace(), setValues(), set1Value(), setValue()) may
*   force Open Inventor to allocate a larger block of memory to hold all the values.
*   In this case, Open Inventor will allocate memory (using @B realloc @b or
*   @B malloc @b) and copy the data. The application is still responsible for
*   freeing its memory unless enableDeleteValues() has been called. Modifying
*   values in the application memory will not affect the field if Open Inventor has
*   allocated new memory.
*   
*   See SoMFVec3f for example code showing the use of setValuesPointer().
* 
* 
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SoMFUInt32 : public SoMField {
  
  // Use standard field stuff
  SO_MFIELD_HEADER(SoMFUInt32, uint32_t, uint32_t);
  
  SO_MFIELD_SETVALUESPOINTER_HEADER(uint32_t);
  SO_FIELD_SUPPORT_MEMOBJ();

 SoINTERNAL public:
#ifndef IV_STRICT
#if (_MIPS_SZLONG == 32)
  //
  //  If the system long has exactly 32 bits, support methods that have "long" 
  //  in the argument list.
  //
  int find(unsigned long targetValue, SbBool addIfNotFound = FALSE)
    { return find((uint32_t)targetValue, addIfNotFound); }
  
  /**
   * [OIV-WRAPPER-ARG IN,NO_WRAP{newValues->Length}, ARRAY]
   * [OIV-WRAPPER-HELPER BEGIN{OnSetValues(start, num)}]
   */
  void setValues(int start, int num, const unsigned long *newValues)
    { setValues(start, num, (const uint32_t *)newValues); }
  
  void set1Value(int index, unsigned long newValue)
    { set1Value(index, (uint32_t)newValue); }
  
  unsigned long operator =(unsigned long newValue)
  { setValue((uint32_t)newValue); return (newValue); }
  
  // Problems in SoFieldConverters.c++ (more than one instance of ...)
  //void setValue(unsigned long newValue)
  //    { setValue((uint32_t)newValue); }
#endif
#endif
  
  static void initClass();
  static void exitClass();
  virtual void writeBinaryValues(SoOutput*, int , int ) const;
  virtual SbBool readBinaryValues( SoInput*, int, int );

 private:
  // Returns number of ASCII values to write per output line
  virtual int getNumValuesPerLine() const;
  
  // Write/Read the values as a block of data
  virtual void writeBinaryValues(SoOutput *out) const;
  virtual SbBool readBinaryValues(SoInput *in, int numToRead);

};

#endif /* _SO_MF_UINT32_ */

