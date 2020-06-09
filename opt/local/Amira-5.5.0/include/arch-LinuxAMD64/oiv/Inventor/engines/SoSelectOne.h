/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_SELECTONE_
#define  _SO_SELECTONE_

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFName.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoSelectOne
//
//  Class that select a single value from a multiple-valued field.
//
//////////////////////////////////////////////////////////////////////////////


#ifdef OIV_NET_DOC
/**
* Selects one value from a multiple-value field.
* 
* @ingroup engines
* 
* @DESCRIPTION
*   This engine selects a single value from a multiple-value field, based on the
*   input field #index. The type of the input field can be any subclass of
*   SoMField, and the type of the output is the corresponding subclass of SoSField.
*   For example, if the input type is SoMFVec3f, the output type will be SoSFVec3f.
*   The type is specified when an instance of the class is created. For example,
*   SoSelectOne(SoMFFloat::getClassTypeId()) creates an engine that selects one
*   floating-point value.
*   
*   Note that unlike most other engine fields, the #input field and
*   #output are references. Note also that by default #input does not
*   contain any values, and no value is output from the engine.
* 
* @FILE_FORMAT_DEFAULT
*    SelectOne {
*    @TABLE_FILE_FORMAT
*       @TR type    @TD \<inputType\>
*       @TR input   @TD []
*       @TR index   @TD 0
*    @TABLE_END
*    }
* 
* @SEE_ALSO
*    SoEngineOutput,
*    SoConcatenate,
*    SoGate
* 
* 
*/ 
#else
/**
* Selects one value from a multiple-value field.
* 
* @ingroup engines
* 
* @DESCRIPTION
*   This engine selects a single value from a multiple-value field, based on the
*   input field #index. The type of the input field can be any subclass of
*   SoMField, and the type of the output is the corresponding subclass of SoSField.
*   For example, if the input type is SoMFVec3f, the output type will be SoSFVec3f.
*   The type is specified when an instance of the class is created. For example,
*   SoSelectOne(SoMFFloat::getClassTypeId()) creates an engine that selects one
*   floating-point value.
*   
*   Note that unlike most other engine fields, the #input field and
*   #output are pointers. Note also that by default #input does not
*   contain any values, and no value is output from the engine.
* 
* @FILE_FORMAT_DEFAULT
*    SelectOne {
*    @TABLE_FILE_FORMAT
*       @TR type    @TD \<inputType\>
*       @TR input   @TD []
*       @TR index   @TD 0
*    @TABLE_END
*    }
* 
* @SEE_ALSO
*    SoEngineOutput,
*    SoConcatenate,
*    SoGate
* 
* 
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SoSelectOne : public SoEngine {
  
  SO_ENGINE_HEADER(SoSelectOne);
  
 public:
  /**
   * Constructor. The argument specifies the type of the multiple-value input field.
   */
  SoSelectOne(SoType mfInputType);

  /**
   * Index of the value to select from the multiple-value field. 
   */
  SoSFInt32 index;

  /**
   * The multiple-value field from which the value will be selected. 
   */
  SoMField *input;

  /**
   * ( lt )  The single value selected.
   */
  SoEngineOutput *output;

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  // Copies an instance that is encountered through a field connection
  virtual SoFieldContainer *copyThroughConnection() const;

 protected:
  ~SoSelectOne();

 private:
  SoSelectOne();
  
  // SelectOne engines must write out their input type before writing
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

#endif /* _SO_SELECTONE_ */

