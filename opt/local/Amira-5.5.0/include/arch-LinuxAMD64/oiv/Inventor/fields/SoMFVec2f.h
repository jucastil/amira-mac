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


#ifndef  _SO_MF_VEC2F_
#define  _SO_MF_VEC2F_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFVec2f subclass of SoMField.
//
//////////////////////////////////////////////////////////////////////////////

#ifdef OIV_NET_DOC
/**
* Multiple-value field containing any number of two-dimensional vectors.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   A multiple-value field that contains any number of two-dimensional vectors.
*   
*   SoMFVec2fs are written to file as one or more pairs of floating point values
*   separated by whitespace. When more than one value is present, all of the values
*   are enclosed in square brackets and separated by commas; for example:
*   
*   <PRE>
*    [ 0 0, 1.2 3.4, 98.6 -4e1 ]
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
*   However, note that some methods (SetNum(), DeleteValues(),
*   InsertSpace(), SetValues(), Set1Value(), SetValue()) may
*   force Open Inventor to allocate a larger block of memory to hold all the values.
*   In this case, Open Inventor will allocate memory and copy the data. 
*   
*   See SoMFVec3f for example code showing the use of SetValuesPointer().
* 
* 
*/ 
#else
/**
* Multiple-value field containing any number of two-dimensional vectors.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   A multiple-value field that contains any number of two-dimensional vectors.
*   
*   SoMFVec2fs are written to file as one or more pairs of floating point values
*   separated by whitespace. When more than one value is present, all of the values
*   are enclosed in square brackets and separated by commas; for example:
*   
*   <PRE>
*    [ 0 0, 1.2 3.4, 98.6 -4e1 ]
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


class INVENTOR_API SoMFVec2f : public SoMField {
  // Use standard field stuff
  SO_MFIELD_HEADER(SoMFVec2f, SbVec2f, const SbVec2f &);
  
  SO_MFIELD_SETVALUESPOINTER_HEADER(float);
  SO_MFIELD_SETVALUESPOINTER_HEADER(SbVec2f);
  SO_FIELD_SUPPORT_MEMOBJ();

    public:
  //
  // Some additional convenience functions:
  //
  
  /**
   * Sets values from array of arrays of 2 floats.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValues(start, num)}]
   */
  void setValues(int start, int num, const float xy[][2]);
  
  /**
   * Sets one value from 2 floats.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSet1Value(index)}]
   */
  void set1Value(int index, float x, float y);
  
  /**
   * Sets one value from 2 floats in array.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSet1Value(index)}]
   */
  void set1Value(int index, const float xy[2]);
  
  /**
   * Sets to one value from 2 floats.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */
  void setValue(float x, float y);
  
  /**
   * Sets to one value from 2 floats in array.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */
  void setValue(const float xy[2]);
  
  /**
   * Sets one value from double precision vector.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSet1Value(index)}]
   */
  void set1Value(int index, const SbVec2d &vec2d);
  
  /**
   * Sets to one value from double precision vector.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */
  void setValue(const SbVec2d &vec2d);
  
  /**
   * Sets values from array of double precision vectors.
   * [OIVNET-WRAPPER-ARG IN,NO_WRAP{vec2d->Length},ARRAY]
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValues(start, vec2d->Length)}]
   */
  void setValues(int start, int num, const SbVec2d *vec2d);
  
 SoINTERNAL public:
  static void initClass();
  static void exitClass();
  virtual void writeBinaryValues(SoOutput*, int , int ) const;
  virtual SbBool readBinaryValues( SoInput*, int, int );

 private:
  virtual void writeBinaryValues(SoOutput *out) const;
  virtual SbBool readBinaryValues(SoInput *in, int numToRead);

};

#endif /* _SO_MF_VEC2F_ */

