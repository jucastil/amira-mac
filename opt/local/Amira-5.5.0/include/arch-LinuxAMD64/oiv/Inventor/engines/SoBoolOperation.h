/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Ronen Barzel (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_BOOL_OPERATION_
#define  _SO_BOOL_OPERATION_

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoMFEnum.h>
#include <Inventor/fields/SoMFBool.h>

/**
 * Performs Boolean operations.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   This engine performs a Boolean operation on two inputs, and returns both the
 *   result of the operation and its inverse.
 *   
 *   The input fields can have multiple values, allowing the engine to perform several
 *   Boolean operations in parallel. One input may have more values than the other.
 *   In that case, the last value of the shorter input will be repeated as necessary.
 * 
 * @FILE_FORMAT_DEFAULT
 *    BoolOperation {
 *    @TABLE_FILE_FORMAT
 *       @TR a           @TD FALSE
 *       @TR b           @TD FALSE
 *       @TR operation   @TD A
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoEngineOutput,
 *    SoCalculator
 * 
 * 
 */ 

class INVENTOR_API SoBoolOperation : public SoEngine {

  SO_ENGINE_HEADER(SoBoolOperation);
    
 public:

   /** Operation */
  enum Operation {
    /** Clear */
    CLEAR,
    /** Set */
    SET,
    /** A */
    A,
    /** Not A */
    NOT_A,
    /** B */
    B,
    /** Not B */
    NOT_B,
    /** A or B */
    A_OR_B,
    /** Not A or B */
    NOT_A_OR_B,
    /** A or not B */
    A_OR_NOT_B,
    /** Not A or not B */
    NOT_A_OR_NOT_B,
    /** A and B */
    A_AND_B,
    /** Not A and B */
    NOT_A_AND_B,
    /** A and not B */
    A_AND_NOT_B,
    /** Not A and not B */
    NOT_A_AND_NOT_B,
    /** A equals B */
    A_EQUALS_B,
    /** A not equals B */
    A_NOT_EQUALS_B
  };

  /**
   * First argument to the Boolean operation. 
   */
  SoMFBool    a;
  /**
   * Second argument to the Boolean operation. 
   */
  SoMFBool    b;
  /**
   * The Boolean operation. 
   */
  SoMFEnum    operation;
    
  /**
   * ( SoMFBool )  Result of the Boolean operation applied to the inputs.
   */
  SoEngineOutput output;
  /**
   * ( SoMFBool )  Inverse of output.
   */
  SoEngineOutput inverse;
    
  /**
   * Constructor.
   */
  SoBoolOperation();
    
 SoINTERNAL public:

  static void initClass();
  static void exitClass();


 protected:
  // Destructor
  ~SoBoolOperation();

 private:
  // Evaluation method
  virtual void evaluate();
};

#endif  /* _SO_BOOL_OPERATION_ */

