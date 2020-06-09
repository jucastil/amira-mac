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
** Modified by : Gwenole Tallec (MMM yyyy)
**=======================================================================*/

#ifndef  _SO_VRMLSOUND_
#define  _SO_VRMLSOUND_

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>

#ifdef _WIN32
class SoSensor;
class SoFieldSensor;
class SoTimerSensor;
class SoWavDecoder;
class SoSoundDecoder;
class SoVRMLSound;
class SoSFNode;
class SoSoundSpatializer;
class SoVRMLAudioClip ;
enum  SoSoundType ;
#endif

#ifdef SO_MPEG_DECODER
#define MPEG_NUM_BUFFERS 5 // Number of buffers for MPEG streaming
#endif

/**
 * @VSGEXT Specifies position and spatial representation of a sound @WIN32_ONLY.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   This node has an effect only on Windows.
 * 
 *   The SoVRMLSound node describes the positioning and spatial presentation of a
 *   sound in a VRML scene. The sound may be located at a point and emit sound in a
 *   spherical or ellipsoid pattern, in the local coordinate system. The ellipsoid is
 *   pointed in a particular direction and may be shaped to provide more or less
 *   directional focus from the location of the sound. The sound node may also be
 *   used to describe an ambient sound which tapers off at a specified distance from
 *   the sound node.
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
 *   The SoVRMLSound node describes the positioning and spatial presentation of a
 *   sound in a VRML scene. The sound may be located at a point and emit sound in a
 *   spherical or ellipsoid pattern, in the local coordinate system. The ellipsoid is
 *   pointed in a particular direction and may be shaped to provide more or less
 *   directional focus from the location of the sound. The sound node may also be
 *   used to describe an ambient sound which tapers off at a specified distance from
 *   the sound node. 
 *   
 *   The SoVRMLSound node also enables ambient background sound to be created by
 *   setting of the #maxFront and #maxBack to the radius of the area for
 *   the ambient noise. If ambient noise is required for the whole scene then these
 *   values should be set to at least cover the distance from the location to the
 *   farthest point in scene from that point (including effects of transforms). 
 *   
 *   The #source field specifies the sound source for the sound node. If there
 *   is no source specified the SoVRMLSound will emit no audio. The source field
 *   will specify either an SoVRMLAudioClip or an SoVRMLMovieTexture node.
 *   Furthermore, the SoVRMLMovieTexture node must refer to a movie format that
 *   supports sound (e.g. MPEG1-Systems). 
 *   
 *   The #intensity field adjusts the volume of each sound source; The
 *   #intensity is an SFFloat that ranges from 0.0 to 1.0. An #intensity
 *   of 0 is silence, and an #intensity of 1 is the full volume of the sound in
 *   the sample or the full volume of the MIDI clip. 
 *   
 *   The #priority field gives the author some control over which sounds the
 *   browser will choose to play when there are more sounds active than sound
 *   channels available. The #priority varies between 0.0 and 1.0, with 1.0
 *   being the highest priority. For most applications priority 0.0 should be used
 *   for a normal sound and 1.0 should be used only for special event or cue sounds
 *   (usually of short duration) that the author wants the user to hear even if they
 *   are farther away and perhaps of lower intensity than some other ongoing sounds.
 *   Browsers should make as many sound channels available to the scene as is
 *   efficiently possible. 
 *   
 *   If the browser does not have enough sound channels to play all of the currently
 *   active sounds, it is recommended that the browser sort the active sounds into an
 *   ordered list using the following sort keys: 
 *   
 *   1. decreasing #priority; 
 *   
 *   2. for sounds with #priority > 0.5, increasing (now-@B startTime @b) 
 *   
 *   3. decreasing #intensity at viewer location
 *   ((#intensity/distance)**2); 
 *   
 *   where now represents the current time, and startTime is the @B startTime @b
 *   field of the audio source node specified in the #source field.
 *   
 *   It is important that sort key #2 be used for the high priority (event and cue)
 *   sounds so that new cues will be heard even when the channels are "full" of
 *   currently active high priority sounds. Sort key #2 should not be used for normal
 *   priority sounds so selection among them will be based on sort key #3 - intensity
 *   and distance from the viewer. 
 *   
 *   The browser should play as many sounds from the beginning of this sorted list as
 *   it has available channels. On most systems the number of concurrent sound
 *   channels is distinct from the number of concurrent MIDI streams. On these
 *   systems the browser may maintain separate ordered lists for sampled sounds and
 *   MIDI streams. 
 *   
 *   A sound's #location in the scene graph determines its spatial location (the
 *   sound's location is transformed by the current transformation) and whether or
 *   not it can be heard. A sound can only be heard while it is part of the traversed
 *   scene; sound nodes that are descended from SoVRMLLOD, SoVRMLSwitch, or any
 *   grouping or prototype node that disables traversal (i.e., drawing) of its
 *   children will not be audible unless they are traversed. If a sound is silenced
 *   for a time under an SoVRMLSwitch or SoVRMLLOD node, and later it becomes part of
 *   the traversal again, the sound picks up where it would have been had it been
 *   playing continuously. 
 *   
 *   Around the #location of the emitter, #minFront and #minBack
 *   determine the extent of the full intensity region in front of and behind the
 *   sound. If the location of the sound is taken as a focus of an ellipsoid, the
 *   #minBack and #minFront values, in combination with the
 *   #direction vector determine the two focii of an ellipsoid bounding the
 *   ambient region of the sound. Similarly, #maxFront and #maxBack
 *   determine the limits of audibility in front of and behind the sound; they
 *   describe a second, outer ellipsoid. If #minFront equals #minBack and
 *   #maxFront equals #maxBack, the sound is omnidirectional, the
 *   direction vector is ignored, and the min and max ellipsoids become spheres
 *   centered around the sound node. The fields #minFront, #maxFront,
 *   #minBack, and #maxBack are scaled by the parent transformations -
 *   these values must be >= 0.0.
 *   
 *   The inner ellipsoid defines a space of full intensity for the sound. Within that
 *   space the sound will play at the intensity specified in the sound node. The
 *   outer ellipsoid determines the maximum extent of the sound. Outside that space,
 *   the sound cannot be heard at all. In between the two ellipsoids, the intensity
 *   drops off proportionally with inverse square of the distance. With this model,
 *   an SoVRMLSound usually will have smooth changes in intensity over the entire
 *   extent is which it can be heard. However, if at any point the maximum is the
 *   same as or inside the minimum, the sound is cut off immediately at the edge of
 *   the minimum ellipsoid.
 *   
 *   The ideal implementation of the sound attenuation between the inner and outer
 *   ellipsoids is an inverse power dropoff. A reasonable approximation to this ideal
 *   model is a linear dropoff in decibel value. Since an inverse power dropoff never
 *   actually reaches zero, it is necessary to select an appropriate cutoff value for
 *   the outer ellipsoid so that the outer ellipsoid contains the space in which the
 *   sound is truly audible and excludes space where it would be negligible. Keeping
 *   the outer ellipsoid as small as possible will help limit resources used by
 *   nearly inaudible sounds. Experimentation suggests that a 20dB dropoff from the
 *   maximum intensity is a reasonable cutoff value that makes the bounding volume
 *   (the outer ellipsoid) contain the truly audible range of the sound. Since actual
 *   physical sound dropoff in an anechoic environment follows the inverse square
 *   law, using this algorithm it is possible to mimic real-world sound attenuation
 *   by making the maximum ellipsoid ten times larger than the minimum ellipsoid.
 *   This will yield inverse square dropoff between them.
 *   
 *   Browsers should support spatial localization of sound as well as their underlying
 *   sound libraries will allow. The #spatialize field is used to indicate to
 *   browsers that they should try to locate this sound. If the #spatialize
 *   field is TRUE, the sound should be treated as a monaural sound coming from a
 *   single point. A simple spatialization mechanism just places the sound properly
 *   in the pan of the stereo (or multichannel) sound output. Sounds are faded out
 *   over distance as described above. Browsers may use more elaborate sound
 *   spatialization algorithms if they wish. 
 *   
 *   Authors can create ambient sounds by setting the #spatialize field to
 *   FALSE. In that case, stereo and multichannel sounds should be played using their
 *   normal separate channels. The distance to the sound and the minimum and maximum
 *   ellipsoids (discussed above) should affect the intensity in the normal way.
 *   Authors can create ambient sound over the entire scene by setting the
 *   #minFront and #minBack to the maximum extents of the scene.
 * 
 *   <H3>Differences between the VSG implementation and the VRML97 specification</H3>
 *
 *    - Support of the Doppler effect. The Doppler effect depends on the velocities of the source 
 *    and the listener relative to the medium (air, water,...) and speed of sound propagation in that medium.
 *    If F is the original frequency, then F', the effective Doppler shifted frequency is computed as
 *    follows:
 *    @BR
 *         F' = #dopplerFactor * F * (#dopplerVelocity-VL)/(#dopplerVelocity+VS)
 *    @BR
 *    with
 *    VL being the listener velocity and VS being the source velocity.@BR
 *
 *   <H3> Limitations </H3>
 *    - This node is not thread safe so it does not work with the MultiPipe extension.
 *
 * @BR
 *    Note: These new fields are not
 *      compatible with VRML97. If you set these fields to non-default values and then
 *      write a VRML file, the VRML file will not be readable by standard VRML97 readers.
 *      Older versions of Open Inventor will not be able to read
 *      the file either and will generate an Inventor read error (unknown
 *      field). 
 *
 *    - The #priority and #spatialize fields are not implemented. Setting these fields has no effect.
 *
 *    - If #source is an SoVRMLAudioClip, only wave files (.wav extension) are supported.
 *
 *    - If #source is an SoVRMLMovieTexture, the sound is extracted only from AVI files.
 *
 *    - #minFront (but not #minBack, #maxFront or #maxBack) is used to specify the volume space
 *    of the sound. #minFront determines the radius of a sphere within which the sound is not attenuated.
 *    Outside of this sphere, the attenuation is as described by the VRML2 specification.
 *
 *    - OpenAL (@B http://connect.creativelabs.com/openal/default.aspx @b), the Open Audio Library, is used for the spatialization 
 *    of the sound. The OpenAL library is supplied separate from the Open Inventor libraries.  
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLSound {
 *    @TABLE_FILE_FORMAT
 *       @TR direction        @TD 0 0 1
 *       @TR intensity        @TD 1
 *       @TR location         @TD 0 0 0
 *       @TR maxBack          @TD 10
 *       @TR maxFront         @TD 10
 *       @TR minBack          @TD 1
 *       @TR minFront         @TD 1
 *       @TR priority         @TD 0
 *       @TR source           @TD NULL
 *       @TR spatialize       @TD TRUE
 *       @TR dopplerFactor    @TD 0.0
 *       @TR dopplerVelocity  @TD 343
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFVec3f   @TD   set_direction      
 *       @TR   SoSFFloat   @TD   set_intensity      
 *       @TR   SoSFVec3f   @TD   set_location      
 *       @TR   SoSFFloat   @TD   set_maxBack @NI       
 *       @TR   SoSFFloat   @TD   set_maxFront @NI       
 *       @TR   SoSFFloat   @TD   set_minBack @NI       
 *       @TR   SoSFFloat   @TD   set_minFront      
 *       @TR   SoSFFloat   @TD   set_priority @NI       
 *       @TR   SoSFNode    @TD   set_source
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFVec3f   @TD   direction_changed      
 *       @TR   SoSFFloat   @TD   intensity_changed      
 *       @TR   SoSFVec3f   @TD   location_changed      
 *       @TR   SoSFFloat   @TD   maxBack_changed @NI       
 *       @TR   SoSFFloat   @TD   maxFront_changed @NI       
 *       @TR   SoSFFloat   @TD   minBack_changed @NI       
 *       @TR   SoSFFloat   @TD   minFront_changed      
 *       @TR   SoSFFloat   @TD   priority_changed @NI       
 *       @TR   SoSFNode    @TD   source_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLSound : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLSound);

 public:
  // Fields

  /**
   * Sound source for the sound node.
   * 
   */
  SoSFNode            source;


  /**
   * Adjusts the volume of each sound source.
   * 
   */
  SoSFFloat           intensity;

  /**
   *  @NI Controls which sound is heard when more than one sound is active.
   * Not implemented.
   *
   */
  SoSFFloat           priority;

  /**
   * Position of the sound source.
   *
   */
  SoSFVec3f           location;

  /**
   * The direction the ellipsoidal sound pattern is pointing.
   * 
   */
  SoSFVec3f           direction;
  /**
   * Around the #location of the emitter, #minFront and #minBack
   * determine the extent of the full intensity region in front of and behind the
   * sound. If the location of the sound is taken as a focus of an ellipsoid, the
   * #minBack and #minFront values, in combination with the
   * #direction vector determine the two focii of an ellipsoid bounding the
   * ambient region of the sound. Similarly, #maxFront and #maxBack
   * determine the limits of audibility in front of and behind the sound; they
   * describe a second, outer ellipsoid.
   * 
   */
  SoSFFloat           minFront;

  //@{
  /**
   * @NI Around the #location of the emitter, #minFront and #minBack
   * determine the extent of the full intensity region in front of and behind the
   * sound. If the location of the sound is taken as a focus of an ellipsoid, the
   * #minBack and #minFront values, in combination with the
   * #direction vector determine the two focii of an ellipsoid bounding the
   * ambient region of the sound. Similarly, #maxFront and #maxBack
   * determine the limits of audibility in front of and behind the sound; they
   * describe a second, outer ellipsoid.
   * 
   */
  SoSFFloat           maxFront;
  SoSFFloat           minBack;
  SoSFFloat           maxBack;
  //@}

  /**
   * @NI If TRUE, the sound is treated as a monaural sound from a single point. If FALSE,
   * ambient sounds can be created.
   *
   */
  SoSFBool            spatialize;

  /**
   * Doppler factor value. 0 deactivates the Doppler effect.
   *
   * @FIELD_SINCE_OIV 4.0
   *
   * @B NOTE 2:@b This field is not compatible with VRML97.
   * If you specify a non-default value for this field, when this node
   * is written to a VRML file, the file will contain this incompatible
   * field and standard VRML97 file readers will not be able to read it.
   */
  SoSFFloat                             dopplerFactor ;

  /**
   * Doppler velocity value in meters/sec.
   *
   * @FIELD_SINCE_OIV 4.0
   *
   * @B NOTE 2:@b This field is not compatible with VRML97.
   * If you specify a non-default value for this field, when this node
   * is written to a VRML file, the file will contain this incompatible
   * field and standard VRML97 file readers will not be able to read it.
   */
  SoSFFloat                             dopplerVelocity ;

  /**
   * Constructor.
   */
  SoVRMLSound();

  /*----------------------------------------------------------------------------*/

 SoEXTENDER public:
  virtual void GLRender(SoGLRenderAction *action);

  /*----------------------------------------------------------------------------*/

 SoINTERNAL public:
  static void initClass();
  static void exitClass();
#ifdef _WIN32
  void   setSoundSpatializer(SoSoundSpatializer * ss);    //set a new sound Manager
#endif

 protected:
  virtual ~SoVRMLSound();

 private:
#ifdef _WIN32
  // Sensor callbacks
  static void grabCB(void *, SoSensor *);
  static void sourceChangedCB(void *, SoSensor *);
  static void dopplerFactorChangedCB(void *, SoSensor *);
  static void dopplerVelocityChangedCB(void *, SoSensor *);
  static void intensityChangedCB(void *, SoSensor *);
  static void soundBufferChangedCB(void *data, SoSensor *);
  static void computeDopplerEffectCB(void *data, SoSensor *);

  // SoVRMLAudioClip sensors    callbacks
  static void startChangedCB(void *data, SoSensor *);
  static void stopChangedCB(void *data, SoSensor *);
  static void startSoundCB(void *data, SoSensor *);
  static void stopSoundCB(void *data, SoSensor *);
  static void pitchChangedCB(void *, SoSensor *);
  static void filenameChangedCB(void *, SoSensor *);
  static void loopChangedCB(void *, SoSensor *);


  void configStartTimeSensor(SoVRMLAudioClip *audioClip) ;
  void configStopTimeSensor(SoVRMLAudioClip *audioClip) ;

  SoSoundType checkFileType();              // Verify the extension
  bool openSound();                               // Open the sound
  void closeSound(bool close_file=false);   // Close the sound
  SbBool initSoundSource();                   // Initialize the sound source

  // Dynamic types of the sound
  SoSoundDecoder *m_soundDecoder ;          // Static type of the sound

  SoFieldSensor  *m_sourceChangedSensor;            // Controls the modification of source
  SoFieldSensor  *m_soundBufferChangedSensor;         // Controls the modification of the video sound
  SoFieldSensor  *m_dopplerFactorChangedSensor ;    // Controls the modification of dopplerFactor
  SoFieldSensor  *m_dopplerVelocityChangedSensor ;  // Controls the modification of dopplerVelocity
  SoFieldSensor  *m_intensityChangedSensor;                     // Controls the modification of the intensity

  // SoVRMLAudioClip sensors    
  SoFieldSensor  *m_pitchChangedSensor;                    // Controls the pitch
  SoFieldSensor  *m_startChangedSensor;                    // Controls the start time
  SoFieldSensor  *m_stopChangedSensor;                     // Controls the end time
  SoFieldSensor  *m_loopChangedSensor;                     // Controls the loop
  SoFieldSensor  *m_filenameSensor;                                  // Controls the filename
        
  SoAlarmSensor  *m_startSensor;                                 // Controls the beginning  
  SoAlarmSensor  *m_stopSensor;                                          // Controls the end  
  SoTimerSensor  *m_grabSensor;                                          // Controls the streaming 
  SoTimerSensor  *m_dopplerEffectSensor;             // Controls the Doppler effect

  bool  m_loop;           // Corresponds to source->loop if source is a SoVRMLAudioClip
  float m_pitch;          // Corresponds to source->pitch if source is a SoVRMLAudioClip

  bool m_isEndDecodingSound;      // True if decoding the sound is finished
  bool m_isCorrectAudioClipFile ; // True if the extension of the file is correct and if the 
  // file exists
  bool m_shouldPlaySound;         // True if the sound should be played
  bool m_isSoundOpened;             // True if the sound is opened
  bool m_isEndPlayingSound;                   // True if the sound is finished
  bool m_isRenderedOnce;          // True if at least one rendering has been done.
  // Useful for Doppler effect.


  int m_soundBufferQueue ;                          // Sound buffer queue
  int m_numSoundBuffersInQueue;   // Nb sound buffers in the queue

  SoSoundType         m_soundType;          // Type of the sound
  SbString            m_audioClipURL;           // The url of the SoVRMLAudioClip
  int                 m_numSoundBuffers ;   // Numbers of sound buffers
  SoSoundSpatializer *m_soundSpatializer;   // 3D Sound Spatializer

  SoType              m_currentSourceType;  // Current source type (ie VRMLMovieTexture or
  // VRMLAudioClip)

  // Manage the doppler Effect
  double  m_prevRenderTime;                             // Previous GLRender time
  SbVec3f m_prevListenerPos;                    // Previous position of the Listener
  SbVec3f m_prevSourcePos;                        // Previous position of the source
#endif // _WIN32
};

#endif /* _SO_VRMLSOUND_ */

