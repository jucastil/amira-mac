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


#ifndef  _SO_TRIGGER_ANY_
#define  _SO_TRIGGER_ANY_

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFTrigger.h>

/**
 * Provides fan-in for triggers.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   This engine takes up to 10 input triggers, and produces one trigger output. The
 *   output is triggered whenever one of the inputs is touched.
 * 
 * @FILE_FORMAT_DEFAULT
 *    TriggerAny {
 *    @TABLE_FILE_FORMAT
 *       @TR input0   @TD 
 *       @TR input1   @TD 
 *       @TR input2   @TD 
 *       @TR input3   @TD 
 *       @TR input4   @TD 
 *       @TR input5   @TD 
 *       @TR input6   @TD 
 *       @TR input7   @TD 
 *       @TR input8   @TD 
 *       @TR input9   @TD 
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoEngineOutput,
 *    SoSFTrigger
 * 
 * 
 */ 

class INVENTOR_API SoTriggerAny : public SoEngine {

  SO_ENGINE_HEADER(SoTriggerAny);

 public:
  /**
   *  The output is triggered whenever one of the inputs is touched.
   */
  SoSFTrigger                 input0;
  /**
   *  The output is triggered whenever one of the inputs is touched.
   */
  SoSFTrigger                 input1;
  /**
   *  The output is triggered whenever one of the inputs is touched.
   */
  SoSFTrigger                 input2;
  /**
   *  The output is triggered whenever one of the inputs is touched.
   */
  SoSFTrigger                 input3;
  /**
   *  The output is triggered whenever one of the inputs is touched.
   */
  SoSFTrigger                 input4;
  /**
   *  The output is triggered whenever one of the inputs is touched.
   */
  SoSFTrigger                 input5;
  /**
   *  The output is triggered whenever one of the inputs is touched.
   */
  SoSFTrigger                 input6;
  /**
   *  The output is triggered whenever one of the inputs is touched.
   */
  SoSFTrigger                 input7;
  /**
   *  The output is triggered whenever one of the inputs is touched.
   */
  SoSFTrigger                 input8;
  /**
   *  The output is triggered whenever one of the inputs is touched.
   */
  SoSFTrigger                  input9;
  /**
   *  Triggered when any of the inputs is touched.
   */
  SoEngineOutput              output;

  /**
   * Constructor
   */
  SoTriggerAny();

 SoINTERNAL public:
  static void                 initClass();
  static void                 exitClass();

 protected:
  ~SoTriggerAny();
 private:
  virtual void                evaluate();
};

#endif  /* _SO_TRIGGER_ANY_ */

