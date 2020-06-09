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

#ifndef  _SO_VRML_MOVIE_TEXTURE
#define  _SO_VRML_MOVIE_TEXTURE

#include <Inventor/VRMLnodes/SoVRMLTexture.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/fields/SoSFImage.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoMFFilePathString.h>
#include <Inventor/nodes/SoNode.h>

#include <Inventor/threads/SbThread.h>
#include <Inventor/threads/SbThreadStorage.h>
#include <Inventor/caches/SoGLTexCacheList.h>
#include <Inventor/sys/SoGLType.h>

class SoState ;
class SoSensor;
class SoTimerSensor;
class SoAlarmSensor;
class SoFieldSensor;
class SoGLDisplayList;
class SoMPEG2Decoder;
class SoAVIDecoder;
class SoWebCamDecoder;
class SoVideoDecoder;
class SoVRMLMovieTexture;
class SbThreadRWMutex;
class SoSoundDecoder;

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

/** 
 * [OIV-WRAPPER NAME{MoviePrequalifyFileCallback}] 
 */
typedef SbBool VRMLMoviePrequalifyFileCallback(const SbString &, void *, SoVRMLMovieTexture *);

typedef int SoMovieType ;

/**
 * @VSGEXT Texture and sound node.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   The SoVRMLMovieTexture node defines a time-dependent texture map (contained in a
 *   movie file) and parameters for controlling the movie and the texture mapping. 
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
 *   The SoVRMLMovieTexture node defines a time dependent texture map (contained in a
 *   movie file) and parameters for controlling the movie and the texture mapping. An
 *   SoVRMLMovieTexture can also be used as the source of sound data for an
 *   SoVRMLSound node, but in this special case is not used for rendering.
 *   
 *   Texture maps are defined in a 2D coordinate system, (s,t), that ranges from 0.0
 *   to 1.0 in both directions. The bottom edge of the image corresponds to the
 *   S-axis of the texture map, and left edge of the image corresponds to the T-axis
 *   of the texture map. The lower-left pixel of the image corresponds to s=0, t=0,
 *   and the top-right pixel of the image corresponds to s=1, t=1.
 *   
 *   @IMAGE imagets.gif 
 *   
 *   The #url field that defines the movie data must support MPEG1-Systems
 *   (audio and video) or MPEG1-Video (video-only) movie file formats. See
 *   "Concepts - URLS and URNs" for details on the #url field. 
 *   It is recommended that
 *   implementations support grayscale or alpha transparency rendering if the
 *   specific movie format being used supports these features.
 *   
 *   See "Concepts - Lighting Model" for details on lighting equations and the
 *   interaction between textures, materials, and geometries.
 *   
 *   As soon as the movie is loaded, a #duration_changed eventOut is sent. This
 *   indicates the duration of the movie, in seconds. This eventOut value can be read
 *   (for instance, by a Script) to determine the duration of a movie. A value of -1
 *   implies the movie has not yet loaded or the value is unavailable for some
 *   reason. 
 *   
 *   The #loop, #startTime, and #stopTime exposedFields and the
 *   #isActive eventOut, and their affects on the SoVRMLMovieTexture node, are
 *   discussed in detail in the "Concepts - Time Dependent Nodes" section. The
 *   "cycle" of an SoVRMLMovieTexture is the length of time in seconds for one
 *   playing of the movie at the specified #speed. 
 *   
 *   If an SoVRMLMovieTexture is inactive when the movie is first loaded, then frame 0
 *   is shown in the texture if #speed is nonnegative, or the last frame of the
 *   movie if #speed is negative. A SoVRMLMovieTexture will always display
 *   frame 0 if #speed = 0. For positive values of #speed, the frame an
 *   active SoVRMLMovieTexture will display at time @I now @i corresponds to the
 *   frame at movie time (i.e., in the movie's local time system with frame 0 at time
 *   0, at #speed = 1):
 *   
 *   <PRE> 
 *    fmod (now - startTime, duration/speed)
 *    </PRE>
 *    If #speed is negative, then the frame to display is the frame at
 *   movie time:
 *   
 *   <PRE> 
 *    duration + fmod(now - startTime, duration/speed)
 *    </PRE>
 *    When an SoVRMLMovieTexture becomes inactive, the frame corresponding to
 *   the time at which the SoVRMLMovieTexture became inactive will remain as the
 *   texture.
 *   
 *   The #speed exposedField indicates how fast the movie should be played. A
 *   #speed of 2 indicates the movie plays twice as fast. Note that the
 *   #duration_changed output is not affected by the #speed exposedField.
 *   @B set_speed @b events are ignored while the movie is playing. A negative
 *   #speed implies that the movie will play backwards. However, content
 *   creators should note that this may not work for streaming movies or very large
 *   movie files.
 *   
 *   SoVRMLMovieTexture can be referenced by an SoVRMLAppearance node's texture field
 *   (as a movie texture) and by an SoVRMLSound node's source field (as an audio
 *   source only). A legal implementation of the SoVRMLMovieTexture node is not
 *   required to play audio if #speed is not equal to 1.
 * 
 *<H3> Differences between the VSG implementation and the VRML97 specification</H3>
 *
 *    - If the texture coordinates are less than 0, correct mapping is not
 *      guaranteed.
 *
 *    - If the texture coordinates are greater than 1, the mapping is not
 *      guaranteed if the #scaleTexCoord field is TRUE.
 *
 *    - MPEG1-Video and MPEG2-Video (video-only, not audio) are supported.
 *
 *    - AVI-System (audio and video) is supported @WIN32_ONLY.
 *
 *    - Video Capture system (camera...) is supported (see #url field and #setVideoCaptureFormat()).
 *
 *    - Negative speed values are not supported.
 *
 *    - Additional fields for controlling texture mapping (i.e., #alpha, #model and #blendColor) and 
 *      texture coordinates (#scaleTexCoord) were added. Note: These new fields are not
 *      compatible with VRML97. If you set these fields to non-default values and then
 *      write a VRML file, the VRML file will not be readable by standard VRML97 readers.
 *      Older versions of Open Inventor will not be able to read
 *      the file either and will generate an Inventor read error (unknown
 *      field).
 *
 * <H3> Limitations </H3>
 *     - This node is not thread safe, so it does not work with the MultiPipe extension.
 *
 *
 * @FILE_FORMAT_DEFAULT
 *    VRMLMovieTexture {
 *    @TABLE_FILE_FORMAT
 *       @TR loop             @TD FALSE
 *       @TR speed            @TD 1
 *       @TR startTime        @TD 0
 *       @TR stopTime         @TD 0
 *       @TR pauseTime        @TD 0 
 *       @TR resumeTime       @TD 0
 *       @TR url              @TD []
 *       @TR repeatS          @TD TRUE
 *       @TR repeatT          @TD TRUE
 *       @TR alpha            @TD 1.0
 *       @TR model            @TD MODULATE
 *       @TR blendColor       @TD 0 0 0
 *       @TR scaleTexCoord    @TD TRUE
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFBool   @TD   set_loop      
 *       @TR   SoSFFloat  @TD   set_speed      
 *       @TR   SoSFTime   @TD   set_startTime      
 *       @TR   SoSFTime   @TD   set_stopTime 
 *       @TR   SoSFTime   @TD   set_pauseTime @NI 
 *       @TR   SoSFTime   @TD   set_resumeTime @NI      
 *       @TR   SoMFFilePathString @TD   set_url
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFTime   @TD   duration_changed 
 *       @TR   SoSFTime   @TD   elapsedTime  @NI      
 *       @TR   SoSFBool   @TD   isPaused @NI       
 *       @TR   SoSFBool   @TD   isActive      
 *       @TR   SoSFBool   @TD   loop_changed      
 *       @TR   SoSFFloat  @TD   speed_changed      
 *       @TR   SoSFTime   @TD   startTime_changed      
 *       @TR   SoSFTime   @TD   stopTime_changed
 *       @TR   SoSFTime   @TD   pauseTime_changed @NI       
 *       @TR   SoSFTime   @TD   resumeTime_changed @NI             
 *       @TR   SoMFFilePathString @TD   url_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 


class INVENTOR_API SoVRMLMovieTexture : public SoVRMLTexture {

  SO_NODE_HEADER(SoVRMLMovieTexture);

 public:
 
    /** Model */
  enum Model {
    /**
     *  The texture color is multiplied by the surface color 
     */
    MODULATE  = GL_MODULATE,

    /**
     * In this mode, OpenGL requires that the specified texture image have 
     * either 3 or 4 components. 
     * For a 3-component texture, the texture color replaces the surface color.
     * For a 4-component texture, the texture color is blended with the 
     * surface color.
     * See OpenGL documentation on glTexEnv for details. 
     * 
     */
    DECAL = GL_DECAL,

    /**
     *  Blends between the surface color and a specified blend color 
     */
    BLEND = GL_BLEND,

    /**
     *  The texture color replaces the surface color.
     */
    REPLACE = GL_REPLACE
  };

  /**
   * Constructor
   */
  SoVRMLMovieTexture();


  /**
   * Controls whether the movie continues when it reaches the end as
   * defined in the movie texture file. If #loop is FALSE ,
   * execution is terminated. If TRUE, the movie restarts.
   * 
   */
  SoSFBool            loop; 

  /**
   * Indicates how fast the movie should be played.
   * 
   */
  SoSFFloat           speed;

  /**
   * The starting time for the movie.
   * 
   */
  SoSFTime            startTime;

  /**
   * The stopping time for the movie. An SoVRMLMovieTexture node with #loop
   * TRUE at the end of every cycle continues forever if
   * #startTime>=#stopTime or until #stopTime if
   * #stopTime>#startTime.
   * 
   */
  SoSFTime            stopTime;
  /**
   *  @NI The pause time for the sound. An SoVRMLAudioClip node with #loop TRUE
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
   *  @NI The resume time for the sound. An SoVRMLAudioClip node with #loop TRUE
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
   * Specifies the movie data. AVI files (.avi extension) @WIN32_ONLY,
   * MPEG1 and MPEG2 files (.mpg or .mpeg extension) are supported.
   * Specifying a .cam extension (whatever the base file name) @WIN32_ONLY allows you to capture video 
   * from a video input device such as a camera. In this case, the #setVideoCaptureFormat() method
   * allows you to specify the format you want to obtain from your video input device.
   */
  SoMFFilePathString          url;
   
  /**
   * Alpha value used with the video. If the value is less than 1, 
   * the movie texture will be an RGBA image.  This uses some additional 
   * memory and computation time.
   *
   * @FIELD_SINCE_OIV 4.0
   *
   * @B NOTE 2:@b This field is not compatible with VRML97.
   * If you specify a non-default value for this field, when this node
   * is written to a VRML file, the file will contain this incompatible
   * field and standard VRML97 file readers will not be able to read it.
   */
  SoSFFloat           alpha;

  /**
   * Specifies how to map the texture onto the surface.
   * Use enum #Model. Default is MODULATE.
   *
   * @FIELD_SINCE_OIV 4.0
   *
   * @B NOTE 2:@b This field is not compatible with VRML97.
   * If you specify a non-default value for this field, when this node
   * is written to a VRML file, the file will contain this incompatible
   * field and standard VRML97 file readers will not be able to read it.
   *
   */
  SoSFEnum                            model;

  /**
   * Color used for BLEND model.
   *
   * @FIELD_SINCE_OIV 4.0
   *
   * @B NOTE 2:@b This field is not compatible with VRML97.
   * If you specify a non-default value for this field, when this node
   * is written to a VRML file, the file will contain this incompatible
   * field and standard VRML97 file readers will not be able to read it.
   *
   */
  SoSFColor                             blendColor;
        
  /** 
   *  Boolean value which controls the way the image is mapped in case of non 
   *  power-of-two video size.
   *  OpenGL uses only power-of-two textures, so if the texture is not a power of two,
   *  it must be rescaled to the next higher power of two, which is time consuming.
   *
   *    - If scaleTexCoord is TRUE (default), the video image is not rescaled but only copied 
   *  the next higher power-of-two texture. Thus, this texture has some unused area.
   *  In order to map only the original part of the image, the texture coordinates are rescaled. 
   *  If other texture transforms are applied to the texture coordinates (especially if the texture
   *  is repeated), the unused part (black) could be displayed.
   *
   *    - If scaleTexCoord is FALSE, the video image is rescaled, which is time consuming.
   *
   * @FIELD_SINCE_OIV 4.0
   *
   * @B NOTE 2:@b This field is not compatible with VRML97.
   * If you specify a non-default value for this field, when this node
   * is written to a VRML file, the file will contain this incompatible
   * field and standard VRML97 file readers will not be able to read it.
   */
  SoSFBool            scaleTexCoord;
        
  /**
   * @WIN32_ONLY In case of video capture from a video input device (see #url), this method allows you
   * to configure the video capture settings (the video size format
   * and the video capture rate expressed in frames per second). 
   * If no format is specified, the size and frame rate will be the last used by
   * the capture device.
   * Because video size formats are device specific, the requested size may not be available
   * and a default size will be used instead.
   *
   */
  void setVideoCaptureFormat(int32_t width, int32_t height, int32_t framePerSec) ;
  /**
   * Specifies the application callback that will be invoked when the MovieTexture
   * node is about to read an image file (if the prequalify flag is TRUE).
   */
  static void setPrequalifyFileCallBack(VRMLMoviePrequalifyFileCallback *, void *);
  /**
   * Sets the prequalify file flag. If FALSE, the prequalification \oivnetdoc delegate \else callback \endoivnetdoc will not
   * be called. Default is TRUE.
   */
  void allowPrequalifyFile(SbBool);

  /*----------------------------------------------------------------------------*/

 SoEXTENDER public:

  virtual void GLRender(SoGLRenderAction *action);

 SoINTERNAL public:

  const SbString & getOverrideURL() { return overrideURL; }
  void setOverrideURL(const SbString &path) { overrideURL = path; }

  SoSFInt32 soundDecoded;  // Change when a SoSounDecoder object is built
  // A SoSounDecoder is built only if a sound sequence 
  // is found.
  // The node VRMLSound is connected to this field.
  //  0 = No sound has been decoded
  //  1 = A sound has been decoded
  // -1 = The video is closed. No sound will be decoded
  /**
   * eventOut.
   */

  SoSFTime            duration_changed;// eventOut
  SoSFBool            isActive;        // eventOut
  SoSFBool            isPaused;        // eventOut
  SoSFTime            elapsedTime;     // eventOut

  static void initClass();
  static void exitClass();

  // Indicate if the sound within the video should be decoded
  void shoudDecodeSound(SbBool decodeSound) ;

  // Return the sound decoder
  SoSoundDecoder* getSoundDecoder() ;

 protected:
  virtual ~SoVRMLMovieTexture();

 private:
  SbString overrideURL;
  static VRMLMoviePrequalifyFileCallback *prequalifyFileCB;
  static void *prequalifyFileCB_udata;

  SbBool prequalifyFileFlag;
        
  SoFieldSensor *filenameSensor;     // Controls the filename
  SoFieldSensor *loopChangedSensor;  // Controls the loop
  SoFieldSensor *startChangedSensor; // Controls the start time
  SoFieldSensor *endChangedSensor;   // Controls the end time
  SoFieldSensor *speedChangedSensor; // Controls the speed
  SoFieldSensor *wrapSChangedSensor; // Controls the wrapS
  SoFieldSensor *wrapTChangedSensor; // Controls the wrapT
  SoFieldSensor *scaleChangedSensor; // Controls the scale_tex_coord

  SoAlarmSensor *startSensor;        // Controls the beginning of the video playing
  SoAlarmSensor *endSensor;          // Controls the end of the video playing
  SoTimerSensor *grabSensor;         // Controls the retrieve of the images to put 
  // them in cache
                                      
  SoTimerSensor *displaySensor;      // Controls the display. Causes the call to GLRender.

  static void filenameChangedCB(void *, SoSensor *);
  static void loopChangedCB(void *data, SoSensor *);
  static void startVideoCB(void *data, SoSensor *);
  static void endChangedCB(void *data, SoSensor *);
  static void speedChangedCB(void *data, SoSensor *);
  static void scaleChangedCB(void *data, SoSensor *);

  static void wrapChangedCB(void *data, SoSensor *);
  static void endVideoCB(void *data, SoSensor *);
  static void startChangedCB(void *data, SoSensor *);
  static void grabNewFrame(void *data, SoSensor *);
  static void displayNewFrame(void *data, SoSensor *);

  void configStartTimeSensor() ;
  void configStopTimeSensor() ;
  void prepareVideoToBePlayed() ;
  void setGLTextureImageElement(SoState *state) ;

  void invalidateRenderList();      // Delete the TexObj

  // Display list info for this texture:
  SbThreadStorage< SoGLTexCacheList* > m_texList;

  // Used for threading decoding
  SbThreadRWMutex *m_mutex;
  SbThread *m_thread;
  static void *grab(void *data);
  SbBool createThread();
        
  // -1 = don't know yet, 0 = no transp, 1 = has transp
  int m_hasTransparency;
  int m_num_components; //alpha >=1 : 3  ; alpha <1 :  4 

  void openVideo();                       // Open the video
  void closeVideo(SbBool close_file = FALSE); // Close the video
  void displayFrame();                    // Display a frame of the video
  void init();                            // Initialise the booleans

  SbVec2s m_size_video; // Size of the video
  SbVec3f m_scale_vec;  // Size of the scaled video
  SbVec2s m_size_scale;

  unsigned char *m_video_buf; // Buffer that contain the frame to play
  unsigned char *m_scale_buf; // Buffer used when scale_tex_coord is FALSE
  unsigned char *m_alpha_buf; // Buffer used when alpha < 1

  SbTime m_startRealTime; // Time the video begin.
  int m_dispFrame;        // Num of the frame waiting to be displayed by glrender
  int m_cptFrame;         // Number of the frame related to the time of the video


  SbBool m_soundPlayed ;      // Indicate if the sound has been played
  SbBool m_shouldDecodeSound; // True the sound shoud be decoded
  SbBool m_END_VIDEO;         // The video is finished
  SbBool m_ADVANCE;           // Must slow the video
  SbBool m_ONCE;              // For the initialization in glRender
  SbBool m_FIRST_TRAVERSAL;   // To avoid skipping the first frame
  SbBool m_STOP_GRAB;         // No more rames to grab
  SbBool m_FIRST ;            // First time the video is played
  SbBool m_URL;               // Wether the url given is correct or not
  SbBool m_START;             // The video is being played
  SbBool m_CLOSED;            // The video is closed
  SbBool m_SCALED;            // The buffer is scaled by gluscaleimage
  SbBool m_SCALE_SIZED;       // The size of the scaled buffer is set
  SbBool m_BUFFER;            // If there is a new buffer taken from the cache
  SbBool m_CLOSED_FILE;       // If the file is closed

  int m_late ;              // Number of frames we're late

  SoMovieType checkFileType( const SbString& ); // Verify the extension
  SoMovieType m_movieType;                 // Type of the video : AVI or MPEG

  static SbString basePath;
  static SbBool basePathSet;

  // Dynamic type of the video
  SoMPEG2Decoder  *m_mpeg;
  SoAVIDecoder    *m_avi;
  SoWebCamDecoder *m_webcam;

  // Static type of the video 
  SoVideoDecoder  *m_video;

  // Corresponds to repeatS and repeatT
  SoSFEnum m_wrapS,m_wrapT;

  // Video Capture format
  int32_t m_videoCapWidth ;
  int32_t m_videoCapHeight ; 
  int32_t m_videoCapFPS ;

  int m_numRenderCaches;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif /* _SO_VRMLMOVIE_TEXTURE */

