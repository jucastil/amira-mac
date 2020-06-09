/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_MF_DOUBLE_
#define  _SO_MF_DOUBLE_

#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFDouble subclass of SoMField.
//
//////////////////////////////////////////////////////////////////////////////

#ifdef OIV_NET_DOC
/**
* Multiple-value field containing any number of double precision values.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   A multiple-value field that contains any number of double precision values.
*   
*   SoMFDoubles are written to file as one or more values in standard scientific
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
*   See SoMFVec3d for example code showing the use of setValuesPointer().
* 
* 
*/ 
#else
/**
* Multiple-value field containing any number of double precision values.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   A multiple-value field that contains any number of double precision values.
*   
*   SoMFDoubles are written to file as one or more values in standard scientific
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
*   See SoMFVec3d for example code showing the use of setValuesPointer().
* 
* 
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SoMFDouble : public SoMField {
  // Use standard field stuff
  SO_MFIELD_HEADER(SoMFDouble, double, double);
  
  SO_MFIELD_SETVALUESPOINTER_HEADER(double);
    
 SoINTERNAL public:
    static void initClass();
    static void exitClass();

 private:
  // Returns number of ASCII values to write per output line
  virtual int getNumValuesPerLine() const;
  
};

#endif /* _SO_MF_DOUBLE_ */

