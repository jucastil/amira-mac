/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_MF_VEC3D_
#define  _SO_MF_VEC3D_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFVec3d subclass of SoMField.
//
//////////////////////////////////////////////////////////////////////////////

#ifdef OIV_NET_DOC
/**
* Multiple-value field containing any number of three-dimensional vectors.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   A multiple-value field that contains any number of three-dimensional vectors.
*   
*   SoMFVec3ds are written to file as one or more triples of double precision values
*   separated by whitespace.
*   
*   When more than one value is present, all of the values are enclosed in square
*   brackets and separated by commas; for example:
*   
*   <PRE>
*    [ 0 0 0, 1.2 3.4 5.6, 98.6 -4e1 212 ]
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
* 
*/ 
#else
/**
* Multiple-value field containing any number of three-dimensional vectors.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   A multiple-value field that contains any number of three-dimensional vectors.
*   
*   SoMFVec3ds are written to file as one or more triples of double precision values
*   separated by whitespace.
*   
*   When more than one value is present, all of the values are enclosed in square
*   brackets and separated by commas; for example:
*   
*   <PRE>
*    [ 0 0 0, 1.2 3.4 5.6, 98.6 -4e1 212 ]
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
*   Example:
*   <PRE>
*     // Allocate memory for NUMBER vertices
*     SbVec3d *vertices = (SbVec3d *)malloc(NUMBER * sizeof(SbVec3d)); 
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


class INVENTOR_API SoMFVec3d : public SoMField {
  // Use standard field stuff
  SO_MFIELD_HEADER(SoMFVec3d, SbVec3d, const SbVec3d &);

  SO_MFIELD_SETVALUESPOINTER_HEADER(double);
  SO_MFIELD_SETVALUESPOINTER_HEADER(SbVec3d);
  SO_FIELD_SUPPORT_MEMOBJ();

    public:
  
  //
  // Some additional convenience functions:
  //
  /**
   * Sets values from array of arrays of 3 doubles.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValues(start, num)}]
   */
  void setValues(int start, int num, const double xyz[][3]);
#ifdef _WIN32
  // Need overload to work around MS compiler bug (fixed in VC++ 5.0)
  void  setValues(int start, int num,       double xyz[][3]);
#endif
 
  /**
   * Sets one value from 3 doubles.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSet1Value(index)}]
   */
  void  set1Value(int index, double x, double y, double z);
  
  /**
   * Sets one value from 3 doubles in array.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSet1Value(index)}]
   */
  void  set1Value(int index, const double xyz[3]);
  
  /**
   * Sets to one value from 3 doubles.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */
  void  setValue(double x, double y, double z);
  
  /**
   * Sets to one value from 3 doubles in array.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */
  void  setValue(const double xyz[3]);
  
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

#endif /* _SO_MF_VEC3D_ */

