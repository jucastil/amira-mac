/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Ronen Barzel (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_CONCATENATE_
#define  _SO_CONCATENATE_

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFName.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoConcatenate
//
//  Concatenate several fields together into one big field.
//
//////////////////////////////////////////////////////////////////////////////

class SoMField;

#ifdef OIV_NET_DOC
/**
* Joins separate fields into a single multiple-value field.
* 
* @ingroup engines
* 
* @DESCRIPTION
*   This engine joins up to 10 separate fields of a type into a single
*   multiple-valued field of the same type. The type of the input fields can be any
*   subclass of SoMField The type is specified when an instance of the class is
*   created. For example, SoConcatenate(SoMFFloat::getClassTypeId()) creates an
*   engine that concatenates floating-point values.
*   
*   The @B input @b field is a 10-element array, where each element can be connected
*   to single- or multiple-valued fields. All the values in the input are
*   concatenated together to form one multiple-value field. For example, if
*   @B input[0] @b contains 10 values and @B input[1] @b contains 3 values, the
*   output will contain 13 values.
*   
*   Note that, unlike the output of most engines, #output is a reference. Note
*   also that by default @B input @b does not contain any values, and no value is
*   output from the engine.
* 
* @FILE_FORMAT_DEFAULT
*    Concatenate {
*    @TABLE_FILE_FORMAT
*       @TR type     @TD \<inputType\>
*       @TR input0   @TD []
*       @TR input1   @TD []
*       @TR input2   @TD []
*       @TR input3   @TD []
*       @TR input4   @TD []
*       @TR input5   @TD []
*       @TR input6   @TD []
*       @TR input7   @TD []
*       @TR input8   @TD []
*       @TR input9   @TD []
*    @TABLE_END
*    }
* 
* @SEE_ALSO
*    SoEngineOutput,
*    SoGate,
*    SoSelectOne
* 
* 
*/ 
#else
/**
* Joins separate fields into a single multiple-value field.
* 
* @ingroup engines
* 
* @DESCRIPTION
*   This engine joins up to 10 separate fields of a type into a single
*   multiple-valued field of the same type. The type of the input fields can be any
*   subclass of SoMField The type is specified when an instance of the class is
*   created. For example, SoConcatenate(SoMFFloat::getClassTypeId()) creates an
*   engine that concatenates floating-point values.
*   
*   The @B input @b field is a 10-element array, where each element can be connected
*   to single- or multiple-valued fields. All the values in the input are
*   concatenated together to form one multiple-value field. For example, if
*   @B input[0] @b contains 10 values and @B input[1] @b contains 3 values, the
*   output will contain 13 values.
*   
*   Note that, unlike the output of most engines, #output is a pointer. Note
*   also that by default @B input @b does not contain any values, and no value is
*   output from the engine.
* 
* @FILE_FORMAT_DEFAULT
*    Concatenate {
*    @TABLE_FILE_FORMAT
*       @TR type     @TD \<inputType\>
*       @TR input0   @TD []
*       @TR input1   @TD []
*       @TR input2   @TD []
*       @TR input3   @TD []
*       @TR input4   @TD []
*       @TR input5   @TD []
*       @TR input6   @TD []
*       @TR input7   @TD []
*       @TR input8   @TD []
*       @TR input9   @TD []
*    @TABLE_END
*    }
* 
* @SEE_ALSO
*    SoEngineOutput,
*    SoGate,
*    SoSelectOne
* 
* 
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SoConcatenate : public SoEngine {
  
  SO_ENGINE_HEADER(SoConcatenate);
  
 public:
  /**
   * Constructor. The argument specifies the type of values to concatenate.
   */
  SoConcatenate(SoType mfInputType);

  /**
   * Array of Input.
   * Connect them like this:
   *    concatenate->input[0]->connectFrom(...)
   * The names of these inputs is input0 ... input9.
   * The default value for these fields is no values.
   */
  SoMField *input[10];
  
  /**
   * Output.
   * Is of the same type as the inputs (note that it is a pointer, unlike most engine outputs).
   */
  SoEngineOutput *output;
  
 SoINTERNAL public:
  // Initializes engine class
  static void initClass();
  static void exitClass();

  // Copies an instance that is encountered through a field connection
  virtual SoFieldContainer *copyThroughConnection() const;
  
 protected:
  ~SoConcatenate();

 private:
  // Constructor/Destructor.  This constructor is used only when
  // reading these from file.
  SoConcatenate();
  
  // Concatenate engines must write out their input type before writing
  // their fields, so these are overridden:
  virtual SbBool readInstance(SoInput *in, unsigned short flags);
  virtual void writeInstance(SoOutput *out);
  
  void setup(SoType);
  virtual void evaluate();
  
  int conversionCase;
  
  SoFieldData *myInputData;
  SoEngineOutputData *myOutputData;
  
  SoSFName typeField; // Used when reading/writing
};

#endif /* _SO_CONCATENATE_ */

