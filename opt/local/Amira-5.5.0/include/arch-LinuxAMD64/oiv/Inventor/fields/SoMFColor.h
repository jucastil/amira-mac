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


#ifndef  _SO_MF_COLOR_
#define  _SO_MF_COLOR_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbColor.h>
#include <Inventor/fields/SoMFVec3f.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFColor subclass of SoMField.
//
//////////////////////////////////////////////////////////////////////////////

#ifdef OIV_NET_DOC
/**
* Multiple-value field containing any number of RGB colors stored as three floats.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   A multiple-value field that contains any number of RGB colors, stored as
*   instances of SbColor. Values may be set in either RGB (red, green, blue) or HSV
*   (hue, saturation, value) color spaces.
*   
*   SoMFColors are written to file as one or more RGB triples of floating point
*   numbers in standard scientific notation. When more than one value is present,
*   all of the values are enclosed in square brackets and separated by commas. For
*   example:
*   
*   <PRE>
*    [ 1.0 0.0 0.0, 0 1 0, 0 0 1 ]
*    </PRE>
*    represents the three colors red, green, and blue.
*   
* @H3 Using an Application-Supplied Array @h3
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
*   In this case, Open Inventor will allocate memory (using @B realloc @b or
*   @B malloc @b) and copy the data. 
*   
*   See SoMFVec3f for example code showing the use of setValuesPointer().
* 
* @SEE_ALSO
*    SbColor
* 
* 
*/ 
#else
/**
* Multiple-value field containing any number of RGB colors stored as three floats.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   A multiple-value field that contains any number of RGB colors, stored as
*   instances of SbColor. Values may be set in either RGB (red, green, blue) or HSV
*   (hue, saturation, value) color spaces.
*   
*   SoMFColors are written to file as one or more RGB triples of floating point
*   numbers in standard scientific notation. When more than one value is present,
*   all of the values are enclosed in square brackets and separated by commas. For
*   example:
*   
*   <PRE>
*    [ 1.0 0.0 0.0, 0 1 0, 0 0 1 ]
*    </PRE>
*    represents the three colors red, green, and blue.
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
* @SEE_ALSO
*    SbColor
* 
* 
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SoMFColor : public SoMField {
  // Use standard field stuff
  SO_MFIELD_HEADER(SoMFColor, SbColor, const SbColor &);
  
  SO_MFIELD_SETVALUESPOINTER_HEADER(float);
  SO_FIELD_SUPPORT_MEMOBJ();
public:
  //
  // Additional convenience functions
  //
  
  /**
   * Sets @B num@b RGB values from an array of arrays of 3 floats.
   * Each float should be in the range 0.0 to 1.0, and there must be 3*@B num@b floats
   * in the array.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValues(start, num)}]
   */ 
  void setValues(int start, int num, const float rgb[][3]);
  /**
   * Sets @B num@b HSV values from an array of arrays of 3 floats.
   * Each float should be in the range 0.0 to 1.0, and there must be 3*@B num@b floats
   * in the array.
   * [OIV-WRAPPER-CUSTOM-CODE]
   */ 
  void setHSVValues(int start, int num, const float hsv[][3]);
  
  /** 
   * Sets the field to contain one and only one value, 
   * the given color (expressed as RGB floating point values
   * in the range 0.0 to 1.0), and deletes the second and subsequent
   * values.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */ 
  void setValue(const SbVec3f &vec);
  /** 
   * Sets the field to contain one and only one value, 
   * the given color (expressed as RGB floating point values
   * in the range 0.0 to 1.0), and deletes the second and subsequent
   * values.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */ 
  void setValue(float r, float g, float b);
  /** 
   * Sets the field to contain one and only one value, 
   * the given color (expressed as an array of RGB floating point values
   * in the range 0.0 to 1.0), and deletes the second and subsequent
   * values.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */ 
  void setValue(const float rgb[3]);
  
  /** 
   * Sets the field to contain one and only one value, 
   * the given color (expressed as HSV floating point values
   * in the range 0.0 to 1.0), and deletes the second and subsequent
   * values.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */ 
  void setHSVValue(float h, float s, float v);
  /** 
   * Sets the field to contain one and only one value, 
   * the given color (expressed as an array of HSV floating point values
   * in the range 0.0 to 1.0), and deletes the second and subsequent
   * values.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */ 
  void setHSVValue(const float hsv[3]);
  
  /** 
   * Sets one of N RGB colors from SbVec3f. 
   * The array will be expanded and filled with zeros as necessary.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSet1Value(index)}]
   */ 
  void set1Value(int index, const SbVec3f &vec);
  /** 
   * Sets one of N RGB colors from 3 floats.
   * The array will be expanded and filled with zeros as necessary.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSet1Value(index)}]
   */ 
  void set1Value(int index, float r, float g, float b);
  /** 
   * Sets one of N RGB colors from an array of 3 floats.
   * The array will be expanded and filled with zeros as necessary.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSet1Value(index)}]
   */ 
  void set1Value(int index, const float rgb[3]);
  
  /** 
   * Sets one of N HSV colors from 3 floats.
   * The array will be expanded and filled with zeros as necessary.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSet1Value(index)}]
   */ 
  void set1HSVValue(int index, float h, float s, float v);
  /** 
   * Sets one of N HSV colors from an array of 3 floats.
   * The array will be expanded and filled with zeros as necessary.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSet1Value(index)}]
   */ 
  void set1HSVValue(int index, const float hsv[3]);
  
 SoINTERNAL public:
  static void initClass();
  static void exitClass();
  virtual void writeBinaryValues(SoOutput*, int , int ) const;
  virtual SbBool readBinaryValues( SoInput*, int, int );

 private:
  virtual void writeBinaryValues(SoOutput *out) const;
  virtual SbBool readBinaryValues(SoInput *in, int numToRead);

  ///////////////////////EXCEPTION METHODS/////////////////////////////////////
  //
  // #unfound setValues(int start, int num, float rgb[][3])
  // #unfound setHSVValues(int start, int num, float hsv[][3])
  // #unfound setValue(SbVec3f & vec)
  // #unfound setValue(float red, float green, float blue)
  // #unfound setHSVValue(float hue, float saturation, float value)
  // #unfound setValue(float rgb[3])
  // #unfound setHSVValue(float hsv[3])
  // #unfound set1Value(index , SbVec3f & vec)
  // #unfound set1Value(index , float r, float g, float b)
  // #unfound set1HSVValue(index , float h, float s, float v)
  // #unfound set1Value(index , float rgb[3])
  // #unfound set1HSVValue(index , float hsv[3])
  // #unfound [](int i)
  // #unfound getValues(int start)
  // #unfound find(SbColor & targetValue, SbBool addIfNotFound)
  // #unfound setValues(int start, int num, SbColor * newValues)
  // #unfound set1Value(int index, SbColor & newValue)
  // #unfound =(SbColor & newValue)
  // #unfound setValue(SbColor & newValue)
  // #unfound ==(SoMFColor & f)
  // #unfound !=(SoMFColor & f)
  // #unfound startEditing()
  // #unfound finishEditing()
  // #unfound setValuesPointer(int num, SbColor * data)
  // #unfound enableDeleteValues()
  // #unfound isDeleteValuesEnabled()
  // #grouped setHSVValues(int start, int num, float hsv[][3])
  // #grouped setValue(float red, float green, float blue)
  // #grouped setHSVValue(float hue, float saturation, float value)
  // #grouped setValue(float rgb[3])
  // #grouped setHSVValue(float hsv[3])
  // #grouped set1Value(index , float r, float g, float b)
  // #grouped set1HSVValue(index , float h, float s, float v)
  // #grouped set1Value(index , float rgb[3])
  // #grouped set1HSVValue(index , float hsv[3])
  // #grouped getTypeId()
  // #grouped setValue(SbColor & newValue)
  // #grouped !=(SoMFColor & f)
  // #grouped finishEditing()
  // #grouped isDeleteValuesEnabled()
  //
  /////////////////////////////////////////////////////////////////////////////

};

#endif /* _SO_MF_COLOR_ */

