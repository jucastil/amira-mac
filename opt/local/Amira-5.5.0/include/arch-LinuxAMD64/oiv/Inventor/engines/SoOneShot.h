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


#ifndef  _SO_ONE_SHOT_
#define  _SO_ONE_SHOT_

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/fields/SoSFBitMask.h>

/**
 * Timer that runs for a pre-set amount of time.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   This engine is a timer that runs for a pre-set amount of time and then stops. By
 *   default, the #timeIn input is connected to the @B realTime @b global
 *   field. It can, however, by connected to any other time source.
 *   
 *   The timer is started when the #trigger input is touched. It then runs for
 *   the specified #duration, and updates the #timeOut output with the
 *   time that has elapsed. During that time, the #ramp output is also updated.
 *   The #ramp output starts at 0.0 at the beginning of the cycle, and linearly
 *   increases until it reaches 1.0 at the end of the cycle.
 *   
 *   You can disable the timer by setting the #disable input to TRUE. The output
 *   value remains 0.0 while the timer is disabled. If the timer is disabled in the
 *   middle of a cycle the output values will be set to 0.0.
 *   
 *   The #flags input contains control flags. Using the flags you can set the
 *   timer to be retriggerable in the middle of a cycle, and set the output values to
 *   stay high after the cycle has been completed. By default, these flags are not
 *   set.
 * 
 * @FILE_FORMAT_DEFAULT
 *    OneShot {
 *    @TABLE_FILE_FORMAT
 *       @TR duration   @TD 1
 *       @TR trigger    @TD 
 *       @TR flags      @TD ()
 *       @TR disable    @TD FALSE
 *       @TR timeIn     @TD \<current time\>
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoElapsedTime,
 *    SoEngineOutput
 * 
 * 
 */ 

class INVENTOR_API SoOneShot : public SoEngine {

  SO_ENGINE_HEADER(SoOneShot);

 public:
  
   /** Flags */
  enum Flags {
    /** Can start over during the cycle */
    RETRIGGERABLE   = (1<<0),       
    /** Output values stay high after cycle */
    HOLD_FINAL      = (1<<1)
  };

  /**
   * Duration of the active cycle. 
   */
  SoSFTime            duration;
  /**
   * Start the cycle. The trigger will be ignored if it is touched in the middle of a
   * cycle and the RETRIGGERABLE flag is not set. 
   */
  SoSFTrigger         trigger;
  /**
   * Control flags. 
   */
  SoSFBitMask         flags;
  /**
   * If TRUE, the timer is disabled. 
   */
  SoSFBool            disable;
  /**
   * Running time. 
   */
  SoSFTime            timeIn;

  /**
   * ( SoSFTime )  Elapsed time from the start.
   */
  SoEngineOutput      timeOut;
  /**
   * ( SoSFBool )  Is TRUE during the active cycle.
   */
  SoEngineOutput      isActive;
  /**
   * ( SoSFFloat )  Ramps linearly from 0.0 to 1.0.
   */
  SoEngineOutput      ramp;

  /**
   * Constructor
   */
  SoOneShot();

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
  ~SoOneShot();
 private:
  enum State {
    DISABLED,               // everything clamped at 0 (via disable input)
    OFF,                    // normal idle state
    TRIGGERED,              // has been triggered, need to start running
    ON,                     // running, watching the time
    PEAKED                  // have reached the end, need to reset
  }                   state;
  SbTime              baseTime;       // Starting time for elapsed time 
  SbTime              timeVal;        // holds output time value
  double              rampVal;        // holds ramp value
  SbBool              outputPending;  // keeps outputs enabled until data is read


  // Evaluation method
  virtual void        evaluate();

  ///////////////////////EXCEPTION METHODS/////////////////////////////////////
  //
  // #unfound enum Flags
  //
  /////////////////////////////////////////////////////////////////////////////

};

#endif  /* _SO_ONE_SHOT_ */

