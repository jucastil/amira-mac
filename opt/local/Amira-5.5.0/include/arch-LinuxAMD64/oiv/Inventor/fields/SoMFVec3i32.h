/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _SO_MF_VEC3I32_
#define  _SO_MF_VEC3I32_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>

#ifdef OIV_NET_DOC
/**
* 
* @VSGEXT Multiple-value field containing any number of three-dimensional vectors.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   A multiple-value field that contains any number of three-dimensional vectors,
*   each vector component being an integer.
*   
*   SoMFVec3i32 are written to file as one or more triples of integer values
*   separated by whitespace.
*   
*   When more than one value is present, all of the values are enclosed in square
*   brackets and separated by commas; for example:
*   
*   <PRE>
*    [ 0 0 0, 1 4 6, 9 -4 2 ]
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
* 
*/ 
#else
/**
* 
* @VSGEXT Multiple-value field containing any number of three-dimensional vectors.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   A multiple-value field that contains any number of three-dimensional vectors,
*   each vector component being an integer.
*   
*   SoMFVec3i32 are written to file as one or more triples of integer values
*   separated by whitespace.
*   
*   When more than one value is present, all of the values are enclosed in square
*   brackets and separated by commas; for example:
*   
*   <PRE>
*    [ 0 0 0, 1 4 6, 9 -4 2 ]
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
*   @B malloc@b) and copy the data. The application is still responsible for
*   freeing its memory unless enableDeleteValues() has been called. Modifying
*   values in the application memory will not affect the field if Open Inventor has
*   allocated new memory.
*   
*   Example:
*   <PRE>
*     // Allocate memory for NUMBER vertices
*     SbVec3i32 *vertices = (SbVec3i32 *)malloc(NUMBER * sizeof(SbVec3i32)); 
*   
*     // Assign values to the vertices (application-specific code)
*     ... 
*     // Set the field's value to vertices in application memory
*     SoVertexProperty *myVertexProperty = new SoVertexProperty;
*     myVertexProperty->vertex.setValuesPointer(NUMBER, vertices); 
*   
*     // Change application data and notify Open Inventor
*     vertices[5].setValue(newx, newy, newz);
*     myVertexProperty->vertex->touch(); 
*  </PRE>
* 
* 
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SoMFVec3i32 : public SoMField {
  // Use standard field stuff
  SO_MFIELD_HEADER(SoMFVec3i32, SbVec3i32, const SbVec3i32 &);

  SO_MFIELD_SETVALUESPOINTER_HEADER(int32_t);
  SO_MFIELD_SETVALUESPOINTER_HEADER(SbVec3i32);
  SO_FIELD_SUPPORT_MEMOBJ();

    public:
  
  //
  // Some additional convenience functions:
  //
  /**
   * Sets values from array of arrays of 3 integers.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValues(start, num)}]
   */
  void setValues(int start, int num, const int32_t xyz[][3]);
#ifdef _WIN32
  // Need overload to work around MS compiler bug (fixed in VC++ 5.0)
  void  setValues(int start, int num,       int32_t xyz[][3]);
#endif
 
  /**
   * Sets one value from 3 integers.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSet1Value(index)}]
   */
  void  set1Value(int index, int32_t x, int32_t y, int32_t z);
  
  /**
   * Sets one value from 3 integers in array.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSet1Value(index)}]
   */
  void  set1Value(int index, const int32_t xyz[3]);
  
  /**
   * Sets to one value from 3 integers.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */
  void  setValue(int32_t x, int32_t y, int32_t z);
  
  /**
   * Sets to one value from 3 integers in array.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */
  void  setValue(const int32_t xyz[3]);

  /**
   * Sets one value from single precision vector.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSet1Value(index)}]
   */
  void set1Value(int index, const SbVec3f &vec3f);
  
  /**
   * Sets one value from double precision vector.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSet1Value(index)}]
   */
  void  set1Value(int index, const SbVec3d &vec3d);

  /**
   * Sets to one value from single precision vector.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */
  void setValue(const SbVec3f &vec3f);
  
  /**
   * Sets to one value from double precision vector.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */
  void  setValue(const SbVec3d &vec3d);
  
  /**
   * Sets values from array of single precision vectors.
   * [OIVNET-WRAPPER-ARG IN,NO_WRAP{vec3f->Length},ARRAY]
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValues(start, vec3f->Length)}]
   */
  void setValues(int start, int num, const SbVec3f *vec3f);

  /**
   * Sets values from array of double precision vectors.
   * [OIVNET-WRAPPER-ARG IN,NO_WRAP{vec3d->Length},ARRAY]
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValues(start, vec3d->Length)}]
   */
  void  setValues(int start, int num, const SbVec3d *vec3d);
  
 SoINTERNAL public:
  static void initClass();
  static void exitClass();
  virtual void writeBinaryValues(SoOutput*, int , int ) const;
  virtual SbBool readBinaryValues( SoInput*, int, int );

 private:
  // Write the values out as a block of data
  virtual void writeBinaryValues(SoOutput *out) const;
  virtual SbBool readBinaryValues(SoInput *in, int numToRead);

};

#endif /* _SO_MF_VEC3I32_ */
