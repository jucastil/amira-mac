/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/



#ifndef  _SO_VRMLTIMESENSOR_
#define  _SO_VRMLTIMESENSOR_

#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/VRMLnodes/SoVRMLInterpolator.h>
#include <Inventor/VRMLnodes/SoVRMLSubInterpolator.h>
#include <Inventor/sensors/SoIdleSensor.h>


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLTimeSensor
//
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Generates events as time passes.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   SoVRMLTimeSensors generate events as time passes. SoVRMLTimeSensors can be used
 *   to drive continuous simulations and animations, periodic activities (e.g., one
 *   per minute), and/or single occurrence events such as an alarm clock. 
 * 
 * @VRML2_SPECIFICATION
 *    This section describes the expected behavior of the node in a conforming VRML97
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *   This section may reference portions of the VRML97 specification that are not
 *   present in this help file. The complete VRML97 spec is available at
 *   @B http://www.web3d.org @b.
 *   
 *   SoVRMLTimeSensors generate events as time passes. SoVRMLTimeSensors can be used
 *   to drive continuous simulations and animations, periodic activities (e.g., one
 *   per minute), and/or single occurrence events such as an alarm clock.
 *   SoVRMLTimeSensor discrete eventOuts include: @B isActive @b, which becomes TRUE
 *   when the SoVRMLTimeSensor begins running, and FALSE when it stops running, and
 *   @B cycleTime @b, a time event at #startTime and at the beginning of each
 *   new cycle (useful for synchronization with other time-based objects). The
 *   remaining outputs generate continuous events and consist of
 *   @B fraction_changed @b, which is an SFFloat in the closed interval [0,1]
 *   representing the completed fraction of the current cycle, and @B time @b, an
 *   SFTime event specifying the absolute time for a given simulation tick.
 *   
 *   If the #enabled exposedField is TRUE, the SoVRMLTimeSensor is enabled and
 *   may be running. If a @B set_enabled @b FALSE event is received while the
 *   SoVRMLTimeSensor is running, then the sensor should evaluate and send all
 *   relevant outputs, send a FALSE value for @B isActive, @b and disable itself.
 *   However, events on the exposedFields of the SoVRMLTimeSensor (such as
 *   @B set_startTime) @b are processed and their corresponding eventOuts
 *   (@B startTime_changed) @b are sent regardless of the state of #enabled.
 *   The remaining discussion assumes #enabled is TRUE.
 *   
 *   The #loop, #startTime, and #stopTime exposedFields, and the
 *   @B isActive @b eventOut and their affects on the SoVRMLTimeSensor node, are
 *   discussed in detail in the "Concepts - Time Dependent Nodes" section. The
 *   "cycle" of an SoVRMLTimeSensor lasts for #cycleInterval seconds. The value
 *   of #cycleInterval must be greater than 0 (a value less than or equal to 0
 *   produces undefined results). Because the SoVRMLTimeSensor is more complex than
 *   the abstract SoVRMLTimeDep node and generates continuous eventOuts, some of the
 *   information in the "Time Dependent Nodes" section is repeated here.
 *   
 *   A @B cycleTime @b eventOut can be used for synchronization purposes, e.g., sound
 *   with animation. The value of a @B cycleTime @b eventOut will be equal to the
 *   time at the beginning of the current cycle. A @B cycleTime @b eventOut is
 *   generated at the beginning of every cycle, including the cycle starting at
 *   #startTime. The first @B cycleTime @b eventOut for an SoVRMLTimeSensor
 *   node can be used as an alarm (single pulse at a specified time). 
 *   
 *   When an SoVRMLTimeSensor becomes active it will generate an @B isActive @b =
 *   TRUE event and begin generating @B time @b, @B fraction_changed, @b and
 *   @B cycleTime @b events, which may be routed to other nodes to drive animation
 *   or simulated behaviors - (see below for behavior at read time). The @B time @b
 *   event outputs the absolute time for a given tick of the SoVRMLTimeSensor (time
 *   fields and events represent the number of seconds since midnight GMT January 1,
 *   1970). @B fraction_changed @b events output a floating point value in the
 *   closed interval [0, 1], where 0 corresponds to #startTime and 1
 *   corresponds to #startTime + N*#cycleInterval, where N = 1, 2, ... .
 *   That is, the @B time @b and @B fraction_changed @b eventOuts can be computed
 *   as:
 *   
 *   <PRE>
 *    time = now 
 *    f = fmod(now - startTime, cycleInterval) 
 *    if (f == 0.0 && now > startTime) 
 *    fraction_changed = 1.0 
 *    else 
 *    fraction_changed = f / cycleInterval 
 *    </PRE>
 *    A SoVRMLTimeSensor can be set up to be active at read time by specifying
 *   #loop TRUE (not the default) and #stopTime <= #startTime
 *   (satisfied by the default values). The @B time @b events output absolute times
 *   for each tick of the SoVRMLTimeSensor -- times must start at #startTime
 *   and end with either #startTime+#cycleInterval, #stopTime, or
 *   loop forever depending on the values of the other fields. An active
 *   SoVRMLTimeSensor must stop at the first simulation tick when time @I now @i >=
 *   #stopTime > #startTime. 
 *   
 *   No guarantees are made with respect to how often an SoVRMLTimeSensor will
 *   generate time events, but an SoVRMLTimeSensor should generate events at least at
 *   every simulation tick. SoVRMLTimeSensors are guaranteed to generate final
 *   @B time @b and @B fraction_changed @b events. If loop is FALSE, the final
 *   @B time @b event will be generated with a value of
 *   (#startTime+#cycleInterval) or #stopTime (if #stopTime >
 *   @B startTime), @b whichever value is less. If #loop is TRUE at the
 *   completion of every cycle, then the final event will be generated as evaluated
 *   at #stopTime (if #stopTime > #startTime) or never.
 *   
 *   An active SoVRMLTimeSensor ignores @B set_cycleInterval @b, and
 *   @B set_startTime @b events. An active SoVRMLTimeSensor also ignores
 *   @B set_stopTime @b events for @B set_stopTime @b < #startTime. For
 *   example, if a @B set_startTime @b event is received while an SoVRMLTimeSensor
 *   is active, then that @B set_startTime @b event is ignored (the #startTime
 *   field is not changed, and a @B startTime_changed @b eventOut is not generated).
 *   If an active SoVRMLTimeSensor receives a @B set_stopTime @b event that is less
 *   than @I now @i and greater than or equal to #startTime, it behaves as if
 *   the #stopTime requested is @I now @i and sends the final events based on
 *   @I now @i (note that #stopTime is set as specified in the eventIn).
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLTimeSensor {
 *    @TABLE_FILE_FORMAT
 *       @TR cycleInterval   @TD 1
 *       @TR enabled         @TD TRUE
 *       @TR loop            @TD FALSE
 *       @TR pauseTime       @TD 0
 *       @TR resumeTime      @TD 0
 *       @TR startTime       @TD 0
 *       @TR stopTime        @TD 0
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFTime   @TD   set_cycleInterval      
 *       @TR   SoSFBool   @TD   set_enabled      
 *       @TR   SoSFBool   @TD   set_loop 
 *       @TR   SoSFTime   @TD   set_pauseTime @NI  
 *       @TR   SoSFTime   @TD   set_resumeTime @NI 
 *       @TR   SoSFTime   @TD   set_startTime      
 *       @TR   SoSFTime   @TD   set_stopTime
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFTime   @TD   cycleTime      
 *       @TR   SoSFFloat  @TD   fraction_changed      
 *       @TR   SoSFBool   @TD   isActive 
 *       @TR   SoSFBool   @TD   isPaused @NI      
 *       @TR   SoSFTime   @TD   time      
 *       @TR   SoSFTime   @TD   cycleInterval_changed      
 *       @TR   SoSFBool   @TD   enabled_changed      
 *       @TR   SoSFBool   @TD   loop_changed 
 *       @TR   SoSFTime   @TD   pauseTime_changed @NI 
 *       @TR   SoSFTime   @TD   resumeTime_changed @NI 
 *       @TR   SoSFTime   @TD   startTime_changed      
 *       @TR   SoSFTime   @TD   stopTime_changed
 *       @TR   SoSFTime   @TD   elapsedTime
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLTimeSensor : public SoVRMLInterpolator {

  SO_INTERPOLATOR_HEADER(SoVRMLTimeSensor);

 public:
  // Fields

  /**
   * Time for each cycle in seconds.
   * 
   */
  SoSFTime            cycleInterval;
  /**
   * Enables (TRUE) or disables (FALSE) the sensor.
   * 
   */
  SoSFBool            enabled;
  /**
   * Specifies whether a cycle should be repeated (TRUE) or terminated (FALSE) at the
   * end of the cycle.
   * 
   */
  SoSFBool            loop;
  /**
   * @NI Pause time.
   *
   * @FIELD_SINCE_OIV 5.0
   *
   * @B NOTE 2:@b This field is not compatible with VRML97.
   * If you specify a non-default value for this field, when this node
   * is written to a VRML file, the file will contain this incompatible
   * field and standard VRML97 file readers will not be able to read it.
   */
  SoSFTime            pauseTime;
  /**
   * @NI Resume time.
   *
   * @FIELD_SINCE_OIV 5.0
   *
   * @B NOTE 2:@b This field is not compatible with VRML97.
   * If you specify a non-default value for this field, when this node
   * is written to a VRML file, the file will contain this incompatible
   * field and standard VRML97 file readers will not be able to read it.
   */
  SoSFTime            resumeTime;

  /**
   * Starting time of the cycle.
   * 
   */
  SoSFTime            startTime;
  /**
   * Stop time of the cycle.
   * 
   */
  SoSFTime            stopTime;


  /**
   * Constructor.
   */
  SoVRMLTimeSensor();

  /**
   * Enables/disables events for @I all @i SoVRMLTimeSensor objects. If you have
   * created several objects of this class, you can disable/enable events for all of
   * them with a single call to this method. 
   */
  static void enableEvents(SbBool OnOffFlag);
  /**
   * Queries if events are enabled for all objects of this class.
   */
  static SbBool isEventsEnabled();

 SoEXTENDER public:

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  virtual void        notify(SoNotList *list);

  // wrapper for the user's evaluate() engine
  SoVRMLInterpOutput  cycleTime;              // eventOut
  SoVRMLInterpOutput  fraction_changed;       // eventOut
  SoVRMLInterpOutput  isActive;               // eventOut
  SoVRMLInterpOutput  isPaused;               // eventOut
  SoVRMLInterpOutput  time;                   // eventOut
  SoVRMLInterpOutput  elapsedTime;            // eventOut

 protected:
  virtual void        inputChanged(SoField *whichInput);

  static  SbBool      enableEventsFlag;
  static void         scheduleDisconnect(void *data, SoSensor *sensor);

  // Writes instance to SoOutput. Takes care of not writing out
  // connection to realTime that is created in constructor.
  //virtual void        writeInstance(SoOutput *out);
  virtual SbBool      readInstance(SoInput *in, unsigned short flags);

  virtual void        evaluate(SoVRMLInterpOutput *interp);

  virtual ~SoVRMLTimeSensor();

 private:
  enum State {
    OFF,                     // not running
    ON                      // running
  }                   state;
  // Evaluation method
  virtual void        evaluate();
  void                evaluateNotify(SoNotList *list, bool noOutput = false);

  SbTime              baseTime;

  SbTime              localCycleInterval; 
  SbBool              localEnabled;
  SbBool              localLoop;
  SbTime              localStartTime;
  SbTime              localStopTime;
  SoSFTime            timeIn;
  SbBool              careFlag;
  SoIdleSensor        *m_Idle;
  SbBool              waitingToDisconnect;
  SbBool              wasRunning;
  SbTime              m_lastTime;
  SbTime              m_beginTime;
  static float        m_eventInterval;
};

#endif /* _SO_VRMLTIMESENSOR_ */

