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


#ifndef  _SO_MF_VEC4F_
#define  _SO_MF_VEC4F_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFVec4f subclass of SoMField.
//
//////////////////////////////////////////////////////////////////////////////

#ifdef OIV_NET_DOC
/**
* Multiple-value field containing any number of four-dimensional vectors.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   A multiple-value field that contains any number of four-dimensional vectors.
*   
*   SoMFVec4fs are written to file as one or more quadruples of floating point values
*   separated by whitespace.
*   
*   When more than one value is present, all of the values are enclosed in square
*   brackets and separated by commas; for example:
*   
*   <PRE>
*    [ 0 0 0 1, 1.2 3.4 5.6 1, 98.6 -4e1 212 1 ]
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
* Multiple-value field containing any number of four-dimensional vectors.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   A multiple-value field that contains any number of four-dimensional vectors.
*   
*   SoMFVec4fs are written to file as one or more quadruples of floating point values
*   separated by whitespace.
*   
*   When more than one value is present, all of the values are enclosed in square
*   brackets and separated by commas; for example:
*   
*   <PRE>
*    [ 0 0 0 1, 1.2 3.4 5.6 1, 98.6 -4e1 212 1 ]
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


class INVENTOR_API SoMFVec4f : public SoMField {
  // Use standard field stuff
  SO_MFIELD_HEADER(SoMFVec4f, SbVec4f, const SbVec4f &);
  
  SO_MFIELD_SETVALUESPOINTER_HEADER(float);
  SO_MFIELD_SETVALUESPOINTER_HEADER(SbVec4f);
  SO_FIELD_SUPPORT_MEMOBJ();

    public:
  //
  // Some additional convenience functions:
  //
  
  /**
   * Sets values from array of arrays of 4 floats.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValues(start, num)}]
   */
  void setValues(int start, int num, const float xyzw[][4]);
  
  /**
   * Sets one value from 4 floats.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSet1Value(index)}]
   */
  void set1Value(int index, float x, float y, float z, float w);
  
  /**
   * Sets one value from 4 floats in array.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSet1Value(index)}]
   */
  void set1Value(int index, const float xyzw[4]);
  
  /**
   * Sets to one value from 4 floats.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */
  void setValue(float x, float y, float z, float w);
  
  /**
   * Sets to one value from 4 floats in array.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */
  void setValue(const float xyzw[4]);
  
  /**
   * Sets one value from double precision vector.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSet1Value(index)}]
   */
  void set1Value(int index, const SbVec4d &vec4d);
  
  /**
   * Sets to one value from double precision vector.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */
  void setValue(const SbVec4d &vec4d);
  
  /**
   * Sets values from array of double precision vectors.
   * [OIVNET-WRAPPER-ARG IN,NO_WRAP{(vec4d != NULL? vec4d->get_Length(): 0)},ARRAY]
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValues(start, vec4d != NULL? vec4d->get_Length(): 0)}]
   */
  void setValues(int start, int num, const SbVec4d *vec4d);
  
 SoINTERNAL public:
  static void initClass();
  static void exitClass();
  virtual void writeBinaryValues(SoOutput*, int , int ) const;
  virtual SbBool readBinaryValues( SoInput*, int, int );

 private:
  virtual void writeBinaryValues(SoOutput *out) const;
  virtual SbBool readBinaryValues(SoInput *in, int numToRead);

};

#endif /* _SO_MF_VEC4F_ */
