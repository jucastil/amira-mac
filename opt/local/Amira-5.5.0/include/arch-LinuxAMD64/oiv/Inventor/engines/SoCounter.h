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


#ifndef  _SO_COUNTER_
#define  _SO_COUNTER_

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFTrigger.h>

/**
 * Triggered integer counter.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   This engine is a counter that outputs numbers, starting at a minimum value,
 *   increasing by a step value, and ending with a number that does not exceed the
 *   maximum value. It outputs the next number whenever the #trigger input is
 *   touched. When the maximum number is reached, it starts counting from the
 *   beginning again.
 *   
 *   At any time the counter can be reset to a specific value by setting the
 *   #reset input field to that value. The next time the counter is triggered
 *   it will start counting from there. Note that the counter will always output
 *   numbers based on the min, max and step values, and setting the reset value does
 *   not affect those input fields. If the reset value is not a legal counter value,
 *   the counter will still behave as though it is.
 *   
 *   - If #reset is greater than #max, the counter is set to #max.
 *   
 *   - If #reset is less than #min, the counter is set to #min.
 *   
 *   - If #reset is between steps, the counter is set to the lower step value.
 *   
 *   Each time a counting cycle is started, the #syncOut output is triggered.
 *   This output can be used to synchronize some other event with the counting cycle.
 * 
 * @FILE_FORMAT_DEFAULT
 *    Counter {
 *    @TABLE_FILE_FORMAT
 *       @TR min       @TD 0
 *       @TR max       @TD 1
 *       @TR step      @TD 1
 *       @TR trigger   @TD 
 *       @TR reset     @TD 0
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoTimeCounter,
 *    SoEngineOutput
 * 
 * 
 */ 

class INVENTOR_API SoCounter : public SoEngine {

  SO_ENGINE_HEADER(SoCounter);

 public:
  /**
   * Minimum value for the counter. 
   */
  SoSFShort           min;
  /**
   * Maximum value for the counter. 
   */
  SoSFShort           max;
  /**
   * Counter step value. 
   */
  SoSFShort           step;
  /**
   * Go to the next step. 
   */
  SoSFTrigger         trigger;
  /**
   * At the next trigger, reset the counter to the specified value. 
   */
  SoSFShort           reset;

  /**
   * ( SoSFShort )  Counts min-to-max in step increments.
   */
  SoEngineOutput      output;
  /**
   * ( SoSFTrigger )  Triggers at cycle start.
   */
  SoEngineOutput      syncOut;

  /**
   * Constructor
   */
  SoCounter();

 SoINTERNAL public:

  static void initClass();
  static void exitClass();

 protected:
  virtual void        inputChanged(SoField *whichInput);

  // Destructor
  ~SoCounter();
 private:
  enum Todo {
    RECALC  = (1<<0),
    RESET   = (1<<1),
    STEP    = (1<<2)
  };
  unsigned int        todo;
  int                 nStages;
  int                 curStage;
  struct Stage {
    int     val;            // counter value for stage
  }                   *stages;

  // Evaluation method
  virtual void        evaluate();
};

#endif  /* _SO_COUNTER_ */

