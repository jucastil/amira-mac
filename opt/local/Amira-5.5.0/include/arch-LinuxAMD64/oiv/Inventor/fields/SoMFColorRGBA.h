/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_MF_COLORRGBA_
#define  _SO_MF_COLORRGBA_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbColorRGBA.h>
#include <Inventor/fields/SoMFVec4f.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFColorRGBA subclass of SoMField.
//
//////////////////////////////////////////////////////////////////////////////

#ifdef OIV_NET_DOC
/**
* Multiple-value field containing any number of RGBA colors stored as four floats.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   A multiple-value field that contains any number of RGBA colors, stored as instances 
*   of SbColorRGBA. Value are set in RGBA (red, green, blue, alpha) color space.
*   
*   SoMFColorRGBAs are written to file as one or more RGBA quadruples of floating point
*   numbers in standard scientific notation. When more than one value is present,
*   all of the values are enclosed in square brackets and separated by commas. For
*   example:
*   
*   <PRE>
*    [ 1.0 0.0 0.0 0.5, 0 1 0 1, 0 0 1 .25 ]
*    </PRE>
*    represents the three colors half transparent red, fully opeque green,
*    and one quarter transparent blue.
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
*   See SoMFVec4f for example code showing the use of setValuesPointer().
* 
* @SEE_ALSO
*    SbColorRGBA
* 
* 
*/ 
#else
/**
* Multiple-value field containing any number of RGBA colors stored as four floats.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   A multiple-value field that contains any number of RGBA colors, stored as instances 
*   of SbColorRGBA. RGBA stands for red, green, blue and alpha.  Values should be in
*   the range 0 to 1.  Alpha is the inverse of "transparency", in other words 0 is 
*   fully transparent and 1 is fully opaque.
*
*   Values can also be specified or queried in the HSV (hue, saturation and value)
*   color space, but values are stored internally as RGBA values.
*   
*   SoMFColorRGBAs are written to file as one or more RGBA quadruples of floating point
*   numbers in standard scientific notation. When more than one value is present,
*   all of the values are enclosed in square brackets and separated by commas. For
*   example:
*   
*   <PRE>
*    [ 1.0 0.0 0.0 0.5, 0 1 0 1, 0 0 1 .25 ]
*    </PRE>
*    represents the three colors half transparent red, fully opeque green,
*    and one quarter transparent blue.
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
*   See SoMFVec4f for example code showing the use of setValuesPointer().
* 
* @SEE_ALSO
*    SbColorRGBA
* 
* 
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SoMFColorRGBA : public SoMField {
  // Use standard field stuff
  SO_MFIELD_HEADER(SoMFColorRGBA, SbColorRGBA, const SbColorRGBA &);
  
  SO_MFIELD_SETVALUESPOINTER_HEADER(float);
    
    public:
  //
  // Additional convenience functions
  //
  
  /**
   * Sets @B num@b RGBA values from an array of arrays of 4 floats.
   * Each float should be in the range 0.0 to 1.0, and there must be 4*@B num@b
   * total float values.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValues(start, num)}]
   * [OIVJAVA-WRAPPER-HELPER BEGIN{onSetValues(start, num)}]
   */ 
  void setValues(int start, int num, const float rgba[][4]);

  /**
   * Sets @B num@b HSV (hue, saturation and value) plus Alphe color values from an
   * array of arrays of 4 floats.
   * Each float should be in the range 0.0 to 1.0, and there must be 4*@B num@b
   * total float values.
   * [OIV-WRAPPER-CUSTOM-CODE]
   */ 
  void setHSVAValues(int start, int num, const float hsva[][4]);

  /** 
   * Sets the field to contain one and only one value, 
   * the given color (expressed as RGBA floating point values
   * in the range 0.0 to 1.0), and deletes the second and subsequent
   * values.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   * [OIVJAVA-WRAPPER-HELPER BEGIN{onSetValue()}]
   */ 
  void setValue(const SbVec4f &vec);

  /** 
   * Sets the field to contain one and only one value, 
   * the given color (expressed as RGBA floating point values
   * in the range 0.0 to 1.0), and deletes the second and subsequent
   * values.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   * [OIVJAVA-WRAPPER-HELPER BEGIN{onSetValue()}]
   */ 
  void setValue(float r, float g, float b, float a);
  
  /** 
   * Sets the field to contain one and only one value, 
   * the given color (expressed as an array of RGBA floating point values
   * in the range 0.0 to 1.0), and deletes the second and subsequent
   * values.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   * [OIVJAVA-WRAPPER-HELPER BEGIN{onSetValue()}]
   */ 
  void setValue(const float rgba[4]);
  
  /** 
   * Sets the field to contain one and only one value, 
   * the given color (expressed as HSV plus Alpha floating point values
   * in the range 0.0 to 1.0), and deletes the second and subsequent
   * values.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   * [OIVJAVA-WRAPPER-HELPER BEGIN{onSetValue()}]
   */ 
  void setHSVAValue(float h, float s, float v, float a);
  
  /** 
   * Sets the field to contain one and only one value, 
   * the given color (expressed as an array of HSV plus Alpha floating point values
   * in the range 0.0 to 1.0), and deletes the second and subsequent
   * values.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   * [OIVJAVA-WRAPPER-HELPER BEGIN{onSetValue()}]
   */ 
  void setHSVAValue(const float hsva[4]);

  /** 
   * Sets one of N RGBA colors from SbVec4f. 
   * The array will be expanded and filled with zeros as necessary.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSet1Value(index)}]
   * [OIVJAVA-WRAPPER-HELPER BEGIN{onSet1Value(index)}]
   */ 
  void set1Value(int index, const SbVec4f &vec);
  
  /** 
   * Sets one of N RGBA colors from 4 floats.
   * The array will be expanded and filled with zeros as necessary.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSet1Value(index)}]
   * [OIVJAVA-WRAPPER-HELPER BEGIN{onSet1Value(index)}]
   */ 
  void set1Value(int index, float r, float g, float b, float a);
  
  /** 
   * Sets one of N RGBA colors from an array of 4 floats.
   * The array will be expanded and filled with zeros as necessary.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSet1Value(index)}]
   * [OIVJAVA-WRAPPER-HELPER BEGIN{onSet1Value(index)}]
   */ 
  void set1Value(int index, const float rgba[4]);
  
  /** 
   * Sets one of N HSV plus Alpha colors from 4 floats.
   * The array will be expanded and filled with zeros as necessary.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSet1Value(index)}]
   * [OIVJAVA-WRAPPER-HELPER BEGIN{onSet1Value(index)}]
   */ 
  void set1HSVAValue(int index, float h, float s, float v, float a);

  /**
   * Sets one of N HSV plus Alpha colors from an array of 4 floats.
   * The array will be expanded and filled with zeros as necessary.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSet1Value(index)}]
   * [OIVJAVA-WRAPPER-HELPER BEGIN{onSet1Value(index)}]
   */ 
  void set1HSVAValue(int index, const float hsva[4]);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();
 
 private:

};

#endif /* _SO_MF_COLORRGBA_ */

