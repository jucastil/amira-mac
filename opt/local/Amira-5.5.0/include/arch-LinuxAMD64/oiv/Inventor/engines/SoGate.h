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


#ifndef  _SO_GATE_
#define  _SO_GATE_

#include <Inventor/SoDB.h>
#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFName.h>
#include <Inventor/fields/SoSFTrigger.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGate
//
//  Gate engine class. A gate engine copies its input to its output,
//  when the "enable" field is true.  It will also do a one-time copy
//  when the trigger field is touched.
//
//////////////////////////////////////////////////////////////////////////////


#ifdef OIV_NET_DOC
/**
* Selectively copies its input to its output.
* 
* @ingroup engines
* 
* @DESCRIPTION
*   This engine selectively copies its input to its output. The type of the input
*   field can be any subclass of SoMField. The type is specified when an instance of
*   the class is created. For example, SoGate(SoMFFloat::getClassTypeId())()
*   creates an engine that copies floating-point values.
*   
*   The #enable input controls continuous flow-through of values. While
*   #enable is true, the input will be copied to the output. Alternatively, by
*   touching the #trigger input, you can copy a single value from the input to
*   the output.
*   
*   Note that unlike most other engine fields, #input and #output are
*   references. Note also that by default #input does not contain any values.
* 
* @FILE_FORMAT_DEFAULT
*    Gate {
*    @TABLE_FILE_FORMAT
*       @TR type      @TD \<inputType\>
*       @TR input     @TD []
*       @TR enable    @TD false
*       @TR trigger   @TD 
*    @TABLE_END
*    }
* 
* @SEE_ALSO
*    SoEngineOutput,
*    SoConcatenate,
*    SoSelectOne
* 
* 
*/ 
#else
/**
* Selectively copies its input to its output.
* 
* @ingroup engines
* 
* @DESCRIPTION
*   This engine selectively copies its input to its output. The type of the input
*   field can be any subclass of SoMField. The type is specified when an instance of
*   the class is created. For example, SoGate(SoMFFloat::getClassTypeId())()
*   creates an engine that copies floating-point values.
*   
*   The #enable input controls continuous flow-through of values. While
*   #enable is TRUE, the input will be copied to the output. Alternatively, by
*   touching the #trigger input, you can copy a single value from the input to
*   the output.
*   
*   Note that unlike most other engine fields, #input and #output are
*   pointers. Note also that by default #input does not contain any values.
* 
* @FILE_FORMAT_DEFAULT
*    Gate {
*    @TABLE_FILE_FORMAT
*       @TR type      @TD \<inputType\>
*       @TR input     @TD []
*       @TR enable    @TD FALSE
*       @TR trigger   @TD 
*    @TABLE_END
*    }
* 
* @SEE_ALSO
*    SoEngineOutput,
*    SoConcatenate,
*    SoSelectOne
* 
* 
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SoGate : public SoEngine {
  
  SO_ENGINE_HEADER(SoGate);
  
 public:
  /**
   * Constructor. The argument specifies the type of the input field.
   */
  SoGate(SoType mfInputType);

  /**
   * Enable continous flow-through. 
   */
  SoSFBool enable;
  /**
   * Copy a single value. 
   */
  SoSFTrigger trigger;

  /**
   * The value that is copied to the output when the gate is open. 
   */
  SoMField *input;

  /**
   * ( lt )  Contains a copy of the input value if the gate is open.
   */
  SoEngineOutput *output;

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  // Copies an instance that is encountered through a field connection
  virtual SoFieldContainer *copyThroughConnection() const;
  
 protected:
  ~SoGate();
  virtual void inputChanged(SoField *whichInput);
  
  // Copies the contents of the given node into this instance
  virtual void copyContents(const SoFieldContainer *fromFC,
                            SbBool copyConnections);
  

 private:
  SoGate();
  
  // gate engines must write out their input type before writing
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

#endif /* _SO_GATE_ */

