/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : SGI (MMM YYYY)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _SO_VRMLAUDIOCLIP_
#define  _SO_VRMLAUDIOCLIP_

#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoMFFilePathString.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLAudioClip
//
//  Node that defines a sound clip 
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Audio data node @WIN32_ONLY.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *
 *   This node has an effect only on Windows.
 *
 *   An SoVRMLAudioClip node specifies audio data that can be referenced by other
 *   nodes that require an audio source.
 * 
 * @VRML2_SPECIFICATION
 *    This section describes the expected behavior of the node in a conforming VRML97
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *   This section may reference portions of the VRML97 specification that are not
 *   present in this help file. The complete VRML97 spec is available at
 *   @B http://www.web3d.org@b.
 *   
 *   An SoVRMLAudioClip node specifies audio data that can be referenced by other
 *   nodes that require an audio source.
 *   
 *   The #description field is a textual description of the audio source. A
 *   browser is not required to display the #description field but may choose
 *   to do so in addition to or in place of playing the sound.
 *   
 *   The #url field specifies the URL from which the sound is loaded. Browsers
 *   must support at least the @B wavefile @b format in uncompressed PCM format. It
 *   is recommended that browsers also support the MIDI file type 1 sound format.
 *   MIDI files are presumed to use the General MIDI patch set. See the section on
 *   URLs and URNs in "Concepts - URLs and URNs" for details on the #url field.
 *   Results are not defined when the URL references unsupported data types.
 *   
 *   The #loop, #startTime, and #stopTime exposedFields and the
 *   @B isActive @b eventOut, and their effects on the SoVRMLAudioClip node, are
 *   discussed in detail in the "Concepts - Time Dependent Nodes" section. The
 *   "cycle" of an SoVRMLAudioClip is the length of time in seconds for one playing
 *   of the audio at the specified #pitch. 
 *   
 *   The #pitch field specifies a multiplier for the rate at which sampled sound
 *   is played. Only positive values are valid for #pitch (a value of zero or
 *   less will produce undefined results). Changing the #pitch field affects
 *   both the pitch and playback speed of a sound. A @B set_pitch @b event to an
 *   active SoVRMLAudioClip is ignored (and no @B pitch_changed @b eventOut is
 *   generated). If #pitch is set to 2.0, the sound should be played one octave
 *   higher than normal and played twice as fast. For a sampled sound, the
 *   #pitch field alters the sampling rate at which the sound is played. The
 *   proper implementation of the #pitch control for MIDI (or other note
 *   sequence sound clip) is to multiply the tempo of the playback by the
 *   #pitch value and adjust the MIDI Coarse Tune and Fine Tune controls to
 *   achieve the proper pitch change. The #pitch field must be > 0.0.
 *   
 *   A @B duration_changed @b event is sent whenever there is a new value for the
 *   "normal" duration of the clip. Typically this will only occur when the current
 *   #url in use changes and the sound data has been loaded, indicating that
 *   the clip is playing a different sound source. The duration is the length of time
 *   in seconds for one cycle of the audio for a #pitch set to 1.0. Changing
 *   the #pitch field will not trigger a @B duration_changed @b event. A
 *   duration value of -1 implies the sound data has not yet loaded or the value is
 *   unavailable for some reason.
 *   
 *   The @B isActive @b eventOut can be used by other nodes to determine if the clip
 *   is currently active. If an SoVRMLAudioClip is active, then it should be playing
 *   the sound corresponding to the sound time (i.e., in the sound's local time
 *   system with sample 0 at time 0):
 *   
 *   <PRE>
 *    fmod (now - startTime, duration / pitch).
 *    </PRE>
 *    
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLAudioClip {
 *    @TABLE_FILE_FORMAT
 *       @TR description   @TD ""
 *       @TR loop          @TD FALSE
 *       @TR pitch         @TD 1.0
 *       @TR startTime     @TD 0
 *       @TR stopTime      @TD 0
 *       @TR pauseTime     @TD 0
 *       @TR resumeTime    @TD 0
 *       @TR url           @TD []
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFString   @TD   set_description      
 *       @TR   SoSFBool   @TD   set_loop      
 *       @TR   SoSFFloat   @TD   set_pitch      
 *       @TR   SoSFTime   @TD   set_startTime      
 *       @TR   SoSFTime   @TD   set_stopTime
 *       @TR   SoSFTime   @TD   set_pauseTime @NI 
 *       @TR   SoSFTime   @TD   set_resumeTime @NI 
 *       @TR   SoMFFilePathString   @TD   set_url
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFTime   @TD   duration_changed  
 *       @TR   SoSFTime   @TD   elapsedTime  @NI      
 *       @TR   SoSFBool   @TD   isActive 
 *       @TR   SoSFBool   @TD   isPaused @NI       
 *       @TR   SoSFString   @TD   description_changed      
 *       @TR   SoSFBool   @TD   loop_changed      
 *       @TR   SoSFFloat   @TD   pitch_changed      
 *       @TR   SoSFTime   @TD   startTime_changed      
 *       @TR   SoSFTime   @TD   stopTime_changed
 *       @TR   SoSFTime   @TD   pauseTime_changed @NI       
 *       @TR   SoSFTime   @TD   resumeTime_changed  @NI      
 *       @TR   SoMFFilePathString   @TD   url_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLAudioClip : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLAudioClip);

 public:
  // Fields

  /**
   * Textual description of the audio source.
   * 
   */
  SoSFString          description;
  /**
   * Controls whether the sound continues when it reaches the end of a sound cycle as
   * defined in the audio file. If #loop is FALSE at the end of a cycle,
   * execution is terminated. If TRUE, the sound continues into the next cycle.
   * 
   */
  SoSFBool            loop;
  /**
   * Multiplier for the rate at which sampled sound is played.
   * 
   */
  SoSFFloat           pitch;
  /**
   * The starting time for the sound.
   * 
   */
  SoSFTime            startTime;
  /**
   * The stopping time for the sound. An SoVRMLAudioClip node with #loop TRUE
   * at the end of every cycle continues forever if #startTime>=#stopTime
   * or until #stopTime if #stopTime>#startTime.
   * 
   */
  SoSFTime            stopTime;
   /**
   * @NI The pause time for the sound. An SoVRMLAudioClip node with #loop TRUE
   * at the end of every cycle pauses if current time >= #pauseTime >#resumeTime
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
   * @NI The resume time for the sound. An SoVRMLAudioClip node with #loop TRUE
   * at the end of every cycle pauses if current time >= #resumeTime >#pauseTime
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
   * Specifies the URL from which the sound is loaded.
   * 
   */
  SoMFFilePathString          url;

  /**
   * Constructor.
   */
  SoVRMLAudioClip();

 SoINTERNAL public:

  /**
   * eventOut.
   */

  SoSFTime            duration_changed;// eventOut
  SoSFBool            isActive;        // eventOut
  SoSFBool            isPaused;        // eventOut
  SoSFTime            elapsedTime;     // eventOut
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoVRMLAudioClip();

};

#endif /* _SO_VRMLAUDIOCLIP_ */
