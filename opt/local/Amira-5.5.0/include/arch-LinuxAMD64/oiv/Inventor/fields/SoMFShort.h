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


#ifndef  _SO_MF_SHORT_
#define  _SO_MF_SHORT_

#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFShort subclass of SoMField.
//
//////////////////////////////////////////////////////////////////////////////

#ifdef OIV_NET_DOC
/**
* Multiple-value field containing any number of short integers.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   A multiple-value field that contains any number of short (16-bit) integers.
*   
*   SoMFShorts are written to file as one or more short integer values, represented
*   as decimal, hexadecimal (beginning with '0x') or octal (beginning with '0')
*   values. When more than one value is present, all of the values are enclosed in
*   square brackets and separated by commas; for example:
*   
*   <PRE>
*    [ -7, 0xFF, -033 ]
*    </PRE>
*    Using an Application-Supplied Array
*   
*   The @B SetValuesPointer @b methods allow Open Inventor to directly use an array
*   of values supplied by the application. 
*   
*   The values may be modified by directly modifying the application memory and
*   calling @B touch @b to notify Open Inventor of the change. The values may also
*   be modified using the usual methods (@B Set1Value @b, etc.)
*   
*   However, note that some methods (@B SetNum @b, @B DeleteValues @b,
*   @B InsertSpace @b, @B SetValues @b, @B Set1Value @b, @B SetValue @b) may
*   force Open Inventor to allocate a larger block of memory to hold all the values.
*   In this case, Open Inventor will allocate memory and copy the data. 
*   
*   See SoMFVec3f for example code showing the use of @B SetValuesPointer @b.
* 
* 
*/ 
#else
/**
* Multiple-value field containing any number of short integers.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   A multiple-value field that contains any number of short (16-bit) integers.
*   
*   SoMFShorts are written to file as one or more short integer values, represented
*   as decimal, hexadecimal (beginning with '0x') or octal (beginning with '0')
*   values. When more than one value is present, all of the values are enclosed in
*   square brackets and separated by commas; for example:
*   
*   <PRE>
*    [ -7, 0xFF, -033 ]
*    </PRE>
*    Using an Application-Supplied Array
*   
*   The @B setValuesPointer @b methods allow Open Inventor to directly use an array
*   of values supplied by the application. The application data is not copied and
*   the memory will not be deleted by Open Inventor unless @B enableDeleteValues @b
*   is called. 
*   
*   The values may be modified by directly modifying the application memory and
*   calling @B touch @b to notify Open Inventor of the change. The values may also
*   be modified using the usual methods (@B set1Value @b, etc.)
*   
*   However, note that some methods (@B setNum @b, @B deleteValues @b,
*   @B insertSpace @b, @B setValues @b, @B set1Value @b, @B setValue @b) may
*   force Open Inventor to allocate a larger block of memory to hold all the values.
*   In this case, Open Inventor will allocate memory (using @B realloc @b or
*   @B malloc @b) and copy the data. The application is still responsible for
*   freeing its memory unless @B enableDeleteValues @b has been called. Modifying
*   values in the application memory will not affect the field if Open Inventor has
*   allocated new memory.
*   
*   See SoMFVec3f for example code showing the use of @B setValuesPointer @b.
* 
* 
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SoMFShort : public SoMField {
  // Use standard field stuff
  SO_MFIELD_HEADER(SoMFShort, short, short);
  
  SO_MFIELD_SETVALUESPOINTER_HEADER(short);
  
 SoINTERNAL public:
    static void initClass();
    static void exitClass();

 private:
  // Returns number of ASCII values to write per output line
  virtual int getNumValuesPerLine() const;

};

#endif /* _SO_MF_SHORT_ */

