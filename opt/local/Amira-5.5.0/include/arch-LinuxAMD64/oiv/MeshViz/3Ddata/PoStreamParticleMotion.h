/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_STREAMPARTICLEMOTION_
#define  _PO_STREAMPARTICLEMOTION_

#include <MeshViz/3Ddata/PoBaseStreamLine.h>
#include <Inventor/fields/SoSFBool.h>


class SoLineSet;

/**
 * @DTEXT  Animation of particles along streamlines on a mesh.
 * 
 * @ingroup MeshRepresentation
 * 
 * @DESCRIPTION
 *    This class realizes animation of particle along the list of streamlines 
 *    starting from startPoints. First, it calculates the geometry of these 
 *    streamlines according to the fields of the inherited class. Then it 
 *    calculates a list of positions along the streamlines. Two consecutive 
 *    positions on streamlines must be separated by a constant timeStep, in order 
 *    to have an animation which respect the velocity. After that, blinking 
 *    several frames does the animation. Each frame represents a selection of 
 *    the calculated positions. This selection and the number of frame are 
 *    defined by the value of pulseFrequency. For example, if pulseFrequency = 5, 
 *    one position over 5 is kept in a frame. 5 frames are built, and the 
 *    animation process will blink by cycling switch-on/switch-off one of these
 *    5 frames. For a streamline made of 20 calculated positions, the 5 frames
 *    have the following position's indices:
 * <PRE>
 *       Frame 0:          0,5,10,15
 *       Frame 1:          1,6,11,16
 *       Frame 2:          2,7,12,17
 *       Frame 3:          3,8,13,18
 *       Frame 4:          4,9,14,19
 * </PRE>
 *    The first position of each streamline can be shifted in time, after  
 *    duration of shiftStart from the source point. If isStartRandomized is 
 *    FALSE, the first position's index of frame 0, is always 0. Otherwise, it 
 *    has a random value between 0 and pulseFrequency-1. Setting isStartRandomized
 *    to TRUE is interesting only when several startPoint are defined, because 
 *    it prevents each first position of the different streamlines to start 
 *    simultaneously. 
 *    
 *    Blinking from a frame to the next frame can be speeded up or speeded down 
 *    by the blinkSpeed field. It defines the number of cycles per second. 
 *    Setting isBlinking to FALSE can stop the animation. In that case, the 
 *    index of the visualized frame is viewFrame % pulseFrequency. 
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoStreamParticleMotion {
 *    @TABLE_FILE_FORMAT
 *       @TR pulseFrequency @TD 5
 *       @TR shiftStart @TD 0.0
 *       @TR timeStep @TD 1.0
 *       @TR isStartRandomized @TD TRUE
 *       @TR isBlinking @TD TRUE
 *       @TR viewFrame @TD 0
 *       @TR blinkSpeed @TD 3.0
 *       @TR startPoints @TD SbVec3f(0,0,0)
 *       @TR maxLifetime @TD 0 (i.e. infinite)
 *       @TR maxLength @TD 0 (i.e. infinite)
 *       @TR minSpeed @TD 0 (i.e. infinite)
 *       @TR integrationStepLengthFactor @TD 0.3
 *       @TR integrationMaxStepNumber @TD 0 (i.e. infinite)
 *       @TR integrationDirection @TD FORWARD 
 *       @TR colors @TD (SbColor(1,0,0)
 *       @TR coloringType @TD COLOR_INHERITED
 *       @TR valuesIndex @TD -1
 *       @TR valuesIndexForCellFilter  @TD -1
 *       @TR vecsIndex @TD -1
 *       @TR moduleDataMapping @TD NULL
 *    @TABLE_END
 *    }
 * 
 * 
 */
class MESHVIZ_API PoStreamParticleMotion : public PoBaseStreamLine {
  
  SO_KIT_HEADER(PoStreamParticleMotion) ;
  

 public:

  /* Fields */

  /**
   * Number of frames to be visualized during an animation cycle.
   * 5 by default.
   */
  SoSFInt32 pulseFrequency;

  /**
   * Duration from which the first position on the streamline is calculated.
   * 0 by default.
   */
  SoSFFloat shiftStart;

  /**
   * Time step between 2 consecutive points of a streamline.
   * 1 by default.
   */
  SoSFFloat timeStep;

  /**
   * Set it to TRUE prevents each first position of the different streamlines to start 
   * simultaneously.
   * TRUE by default.
   */
  SoSFBool  isStartRandomized;

  /**
   * Stop the animation if isBlinking is FALSE.
   * TRUE by default.
   */
  SoSFBool  isBlinking;

  /**
   * Visualized frame index (used only if isBlinking is FALSE).
   * 0 by default.
   */
  SoSFInt32 viewFrame;

  /**
   * Number of animation's cycles per second. 
   * 3.0 by default.
   */
  SoSFFloat blinkSpeed;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  PoStreamParticleMotion();
  // Constructor.

  virtual ~PoStreamParticleMotion() ;  
  // Destructor

  virtual void   setDefaultOnNonWritingFields();
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;

  void saveSpeed(PiStreamPath &stream_path, SbVec3f &speed);
  void saveTime(PiStreamPath &stream_path, float time);

  void rebuildFrames( const SbString& part_name );
  SbBool modifyBlinkerParams( const SbString& part_name );

  SbBool fieldsHaveChanged();

  PiStreamPath *m_streamPath;
  int          m_allocStreamPath;

 private:
  FieldSensorList m_fieldSensorList ;
  // Sensors

  SoFieldList     m_fieldList ;
  // List of fields defined in this class

  virtual void newAnimator(SoGroup *group, SoLineSet *line_set, 
                           SoCoordinate3 *particle_coord, SoCoordinate3 *particle_speed, 
                           SoMFColor *particle_color);
  virtual void endAnimator(SoGroup *group, SoLineSet *line_set, 
                           SoCoordinate3 *particle_coord, SoCoordinate3 *particle_speed, 
                           SoMFColor *particle_color);
  virtual void newFrame(SoGroup *frame, int frame_ind);
  virtual void endFrame(SoGroup *frame, int frame_ind);
  virtual void newLine(SoGroup *line, int line_ind);
  virtual void endLine(SoGroup *line, int line_ind);
  virtual void newParticle(const SbVec3f &pos, const SbVec3f &speed, const SbVec3f &norm, const SbColor *color, int ind);
  // method to build the frames to be animated
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_STREAMPARTICLEMOTION_ */


