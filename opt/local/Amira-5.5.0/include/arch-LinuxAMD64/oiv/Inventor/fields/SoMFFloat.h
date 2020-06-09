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


#ifndef  _SO_MF_FLOAT_
#define  _SO_MF_FLOAT_

#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFFloat subclass of SoMField.
//
//////////////////////////////////////////////////////////////////////////////

#ifdef OIV_NET_DOC
/**
* Multiple-value field containing any number of floating point values.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   A multiple-value field that contains any number of floating point values.
*   
*   SoMFFloats are written to file as one or more values in standard scientific
*   notation. When more than one value is present, all of the values are enclosed in
*   square brackets and separated by commas; for example:
*   
*   <PRE>
*    [ 1.0, 2.3, 5, 6.2e4, -100, ]
*    </PRE>
*    The last comma is optional.
*   
* @H3 Using an Application-Supplied Array @h3
*   
*   The setValuesPointer() methods allow Open Inventor to directly use an array
*   of values supplied by the application.
*   
*   The values may be modified by directly modifying the application memory and
*   calling touch() to notify Open Inventor of the change. The values may also
*   be modified using the usual methods (set1Value(), etc.)
*   
*   However, note that some methods (setNum(), deleteValues(),
*   insertSpace(), setValues(), set1Value(), setValue()) may
*   force Open Inventor to allocate a larger block of memory to hold all the values.
*   In this case, Open Inventor will allocate memory (using @B realloc @b or
*   @B malloc @b) and copy the data. 
*   
*   See SoMFVec3f for example code showing the use of setValuesPointer().
* 
* 
*/ 
#else
/**
* Multiple-value field containing any number of floating point values.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   A multiple-value field that contains any number of floating point values.
*   
*   SoMFFloats are written to file as one or more values in standard scientific
*   notation. When more than one value is present, all of the values are enclosed in
*   square brackets and separated by commas; for example:
*   
*   <PRE>
*    [ 1.0, 2.3, 5, 6.2e4, -100, ]
*    </PRE>
*    The last comma is optional.
*   
* @H3 Using an Application-Supplied Array @h3
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


class INVENTOR_API SoMFFloat : public SoMField {
  // Use standard field stuff
  SO_MFIELD_HEADER(SoMFFloat, float, float);
  
  SO_MFIELD_SETVALUESPOINTER_HEADER(float);
  SO_FIELD_SUPPORT_MEMOBJ();

SoINTERNAL public:
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

#endif /* _SO_MF_FLOAT_ */

