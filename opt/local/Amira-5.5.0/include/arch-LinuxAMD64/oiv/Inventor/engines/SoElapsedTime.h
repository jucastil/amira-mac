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


#ifndef  _SO_ELAPSED_TIME_
#define  _SO_ELAPSED_TIME_

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/fields/SoSFTrigger.h>

/**
 * Basic controllable time source.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   This engine functions as a stopwatch; it outputs the time that has elapsed since
 *   it started running. By default, the #timeIn input is connected to the
 *   @B realTime @b global field. It can, however, be connected to any other time
 *   source.
 *   
 *   The ouput from the engine is the time that has elapsed since it started running,
 *   or since the #reset input was last triggered. You can affect the speed of
 *   the output time by setting the #speed scale factor. A value greater than
 *   1.0 will speed up the output, and a value less than 1.0 will slow it down.
 *   
 *   If you pause the engine, by setting the #pause input to TRUE, it stops
 *   updating the #timeOut output. When you turn off the pause, it jumps to its
 *   current position without losing time. Alternatively, if you want to stop the
 *   engine for a while, and then restart it from where it left off, use the
 *   #on input field.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ElapsedTime {
 *    @TABLE_FILE_FORMAT
 *       @TR timeIn   @TD \<current time\>
 *       @TR speed    @TD 1
 *       @TR on       @TD TRUE
 *       @TR pause    @TD FALSE
 *       @TR reset    @TD 
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoTimeCounter,
 *    SoOneShot,
 *    SoEngineOutput
 * 
 * 
 */ 

class INVENTOR_API SoElapsedTime : public SoEngine {

  SO_ENGINE_HEADER(SoElapsedTime);

 public:
  /**
   * Running time. 
   */
  SoSFTime            timeIn;
  /**
   * Scale factor for time. 
   */
  SoSFFloat           speed;
  /**
   * TRUE to start running, FALSE to stop. 
   */
  SoSFBool            on;
  /**
   * TRUE to freeze, FALSE to continue running. 
   */
  SoSFBool            pause;
  /**
   * Reset the base time. 
   */
  SoSFTrigger         reset;

  /**
   * ( SoSFTime )  Time elapsed, modified by the speed factor.
   */
  SoEngineOutput      timeOut;

  /**
   * Constructor.
   */
  SoElapsedTime();

 SoINTERNAL public:

  static void initClass();
  static void exitClass();

 protected:

  // Detects when the running time input changed
  virtual void        inputChanged(SoField *whichInput);

  // Writes instance to SoOutput. Takes care of not writing out
  // connection to realTime that is created in constructor.
  virtual void        writeInstance(SoOutput *out);

  // Reads stuff into instance.  Works around a problem with old
  // files that contain explicit references to the default
  // connection to realTime.
  virtual SbBool      readInstance(SoInput *in, unsigned short flags);

  // Destructor
  ~SoElapsedTime();
 private:
  enum Todo {
    CHECK_ON        = (1<<0),
    CHECK_PAUSE     = (1<<1),
    RESET           = (1<<2)
  };
  enum State {
    STOPPED,        // Clock is not running
    RUNNING,        // Clock is running
    PAUSED          // Clock is running, but output is frozen
  };

  enum State          state;
  unsigned int        todo;
  SbTime              prevTimeOfDay;   // Time of day when last
  // evaluate was called.
  SbTime              prevTimeOut;     // Last 'clock' time that 
  // was output.
  float               prevClockTime;   // 'Clock' time when last 
  // evaluate was called.


  // Evaluation method
  virtual void        evaluate();
};

#endif  /* _SO_ELAPSED_TIME_ */

