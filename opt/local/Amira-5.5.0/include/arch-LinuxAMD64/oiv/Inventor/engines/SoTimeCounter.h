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


#ifndef  _SO_TIME_COUNTER_
#define  _SO_TIME_COUNTER_

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFTrigger.h>

/**
 * Timed integer counter.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   This engine is a counter that outputs numbers, starting at a minimum value,
 *   increasing by a step value, and ending with a number that does not exceed the
 *   maximum value. When the maximum number is reached, it starts counting from the
 *   beginning again.
 *   
 *   The difference between this engine and the SoCounter engine, is that this engine
 *   also has a #timeIn input, which allows the counting cycles to be timed.
 *   This engine counts automatically over time; it does not need to be triggered to
 *   go to the next step. By default, the #timeIn input is connected to the
 *   @B realTime @b global field. It can, however, be connected to any time
 *   source.
 *   
 *   The #frequency input field controls how many min-to-max cycles are
 *   performed per second. For example, a #frequency value of 0.5 means that it
 *   will take 2 seconds to complete a single min-to-max cycle.
 *   
 *   The steps in the count cycle do not necessarily all have the same duration. Using
 *   the #duty input field, you can arbitrarily split the time period of the
 *   count cycle between the steps. For example, if there are 5 steps in the cycle, a
 *   duty input of (1., 2., 2., 2., 1.) will make the second, third, and fourth steps
 *   take twice as long as the first and last steps.
 *   
 *   At any time the counter can be reset to a specific value. If you set the
 *   #reset input field to a value, the engine will continue counting from
 *   there. Note that the counter will always output numbers based on the #min,
 *   #max and #step values, and setting the #reset value does not
 *   affect the those input fields. If the reset value is not a legal counter value,
 *   the counter will still behave as though it is:
 *   
 *   - If #reset is greater than #max, the counter is set to #max.
 *   
 *   - If #reset is less than #min, the counter is set to #min.
 *   
 *   - If #reset is between step values, the counter is set to the lower step.
 *   
 *   Each time a counting cycle is started, the #syncOut output is triggered.
 *   This output can be used to synchronize some other event with the counting cycle.
 *   Other events can also synchronize the counter by triggering the #syncIn
 *   input.
 *   
 *   You can pause the engine, by setting the #on input to FALSE, and it will
 *   stop updating the output field. When you turn off the pause, by setting
 *   #on to TRUE, it will start counting again from where it left off.
 * 
 * @FILE_FORMAT_DEFAULT
 *    TimeCounter {
 *    @TABLE_FILE_FORMAT
 *       @TR min         @TD 0
 *       @TR max         @TD 1
 *       @TR step        @TD 1
 *       @TR on          @TD TRUE
 *       @TR frequency   @TD 1
 *       @TR duty        @TD 1
 *       @TR timeIn      @TD \<current time\>
 *       @TR syncIn      @TD 
 *       @TR reset       @TD 0
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoCounter,
 *    SoElapsedTime,
 *    SoEngineOutput
 * 
 * 
 */ 

class INVENTOR_API SoTimeCounter : public SoEngine {

  SO_ENGINE_HEADER(SoTimeCounter);

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
   * Counter pauses if this is set to FALSE. 
   */
  SoSFBool            on;
  /**
   * Number of min-to-max cycles per second. 
   */
  SoSFFloat           frequency;
  /**
   * Duty cycle values. 
   */
  SoMFFloat           duty;
  /**
   * Running time. 
   */
  SoSFTime            timeIn;
  /**
   * Restart at the beginning of the cycle. 
   */
  SoSFTrigger         syncIn;
  /**
   * Reset the counter to the specified value. 
   */
  SoSFShort           reset;

  /**
   * ( SoSFShort )  Counts min-to-max, in step increments.
   */
  SoEngineOutput      output;
  /**
   * ( SoSFTrigger )  Triggers at cycle start.
   */
  SoEngineOutput      syncOut;

  /**
   * Constructor
   */
  SoTimeCounter();

 SoINTERNAL public:

  static void initClass();
  static void exitClass();

 protected:
  virtual void        inputChanged(SoField *whichInput);

  // Writes instance to SoOutput. Takes care of not writing out
  // connection to realTime that is created in constructor.
  virtual void        writeInstance(SoOutput *out);

  // Reads stuff into instance.  Works around a problem with old
  // files that contain explicit references to the default
  // connection to realTime.
  virtual SbBool      readInstance(SoInput *in, unsigned short flags);

  // Destructor
  ~SoTimeCounter();
 private:
  enum State {
    ON,                     // counting
    PAUSED                  // holding
  }                   state;
  enum Todo {
    RECALC  = (1<<0),
    RESET   = (1<<1),
    SYNC    = (1<<2),
    PAUSE   = (1<<3),
    UNPAUSE = (1<<4)
  };
  unsigned int        todo;
  SbTime              period;         // total cycle time
  int                 nStages;
  int                 curStage;
  int                 prevStage;
  struct Stage {
    int     val;            // counter value for stage
    float   duty;           // normalized fraction of cycle
    SbTime  offset;         // time from start of cycle
  }                   *stages;
  SbTime              baseTime;       // Starting time for cycle
  SbTime              pauseOffset;    // Starting time for cycle


  // Evaluation method
  virtual void        evaluate();

};

#endif  /* _SO_TIME_COUNTER_ */

