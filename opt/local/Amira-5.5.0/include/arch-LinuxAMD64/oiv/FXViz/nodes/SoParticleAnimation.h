/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : A. SURE (Aug 2001)
** Modified by : R.ALBOU (MMM yyyy)
**=======================================================================*/

                                                             /* include files */
#ifndef _SO_PARTICLE_ANIMATION_
#define _SO_PARTICLE_ANIMATION_

#include <Inventor/nodes/SoShape.h>

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFFilePathString.h>
#include <Inventor/fields/SoSFImage.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/fields/SoSFBool.h>

#include <Inventor/nodes/SoTexture2.h>

class CParticle;
class CPoint3D;
class CVector3D;
class CMatrix;
class CParticleList;
class SbPParticleList;

/*----------------------------------------------------------------------------*/

class SoGetPrimitiveCountAction ;
class SoGLRenderAction ;
class SoSensor ;
class SoFieldSensor ;
class SoOneShotSensor ;

/*-----------------------------------------------------------------------------*/

/**
 * @FXEXT Particle system animation node.
 * 
 * @ingroup FXViz
 * 
 * @DESCRIPTION
 *   Base class for particle system animation. Particle system animation is used for 
 *   generating real-time effects such as fire,
 *   chemical flame, explosions, fluid motion, smoke, snow, etc.
 *
 *   A particle system is a set of particles (#numParticles) where each particle is defined
 *   by the following properties:
 *
 *    - initial appearance (#initialColor, #initialOpacity, #initialSize,...) which defines
 *      the appearance of the particle at its birth.
 *
 *      - final appearance (#endColor, #endOpacity, #endSize,...) which defines the appearance
 *      of the particle just before its death.
 *
 *    - life span (#lifeSpan)
 *
 *      - speed (#speed)
 *
 *      - direction (#dispersionAngles) of the particle during its life span.
 * 
 *   All of these properties may fluctuate randomly for each particle within a specified range of values
 *   (#initialColorVariation, #initialOpacityVariation, #endColorVariation, #lifeSpanVariation...).
 *
 *   Each particle emitted from a predefined shape (#emitShapeType) evolves from an initial 
 *   appearance to a final appearance with a given speed and a life span in real time.
 * 
 *   Billboard particles can be textured (#particleFilename, #particleTexture) to produce 
 *   interesting realistic effects.
 *
 *   Like classical Open Inventor shapes, each particle is transformed by the current
 *   cumulative transformation 
 *   and is drawn with the current lighting model and drawing style. 
 *
 *   Classes derived from #SoParticleAnimation have 
 *   default field values pre-set for conveniently generating specific effects. For example,
 *   SoParticleSmoke has predefined field values for generating smoke effects.
 *
 *   @B Note@b: By default, particle animation uses transparency type ADD
 *   (see #transparencyType). Against a white background, particles will not be
 *   visible because with this transparency type,
 *   colors are added until full saturation is reached.
 *   Since white is already fully saturated, no additional visual effect is seen. 
 *   In this case, use BLEND transparency type instead and change the particle texture
 *   from the default (a circular gradient that is gray in the middle and
 *   black on the edges) to one that is gray in the middle and white on
 *   the edges. For additional realism, you can add transparency to the
 *   texture, with zero transparency in the middle increasing linearly to
 *   full transparency on the edges.
 *
 * @FILE_FORMAT_DEFAULT
 *    ParticleAnimation {
 *    @TABLE_FILE_FORMAT
 *     @TR numParticles            @TD 1000
 *     @TR numParticlesVariation   @TD 0.5
 *     @TR initialColor       @TD 1 1 1
 *     @TR initialColorVariation   @TD 0 0 0
 *     @TR initialOpacity       @TD 0.8
 *     @TR initialOpacityVariation @TD 0.1
 *     @TR initialSize       @TD 0.7
 *     @TR initialSizeVariation   @TD 0.0
 *
 *     @TR endColor         @TD 0 0 0
 *     @TR endColorVariation     @TD 0 0 0
 *     @TR endOpacity         @TD 0.8
 *     @TR endOpacityVariation   @TD 0.1
 *     @TR endSize         @TD 0.01
 *     @TR endSizeVariation     @TD 0.0
 *
 *     @TR lifeSpan         @TD 4000
 *     @TR lifeSpanVariation     @TD 0.5
 *
 *     @TR particleShape       @TD BILLBOARD_SHAPE
 *       @TR 
 *     @TR emitShapeType       @TD POINT
 *     @TR shapeScale         @TD 1 1 1
 *
 *     @TR dispersionAngles       @TD 0.01 0.01
 *       @TR 
 *     @TR particleLife       @TD CYCLIC_EMISSION
 *       @TR
 *     @TR speed           @TD 1
 *     @TR speedVariation       @TD 0.1
 *
 *     @TR particleFilename     @TD ""
 *     @TR particleTexture     @TD 32 32 ....(white circle on a black background texture ) 
 *
 *               @TR goalFramesPerSecond         @TD 0
 *
 *     @TR transparencyType    @TD ADD
 *
 *     @TR on             @TD TRUE
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoFXViz, SoParticleChemicalFlame, SoParticleExplosion, SoParticleFlame, SoParticleLightRay,
 *    SoParticleSmoke, SoParticleSnow.
 * 
 * 
 */ 
class FXVIZ_API SoParticleAnimation : public SoShape {

  SO_NODE_HEADER(SoParticleAnimation);
  
 public:
  /**
   * Particle shape type.
   */
  enum ParticleShape {
    /**
     * Each particle is a point.
     */
    POINT_SHAPE,
    /**
     * Each particle is a line.
     */
    LINE_SHAPE,  
    /**
     * Each particle is a rectangular billboard
     * (i.e., a screen-aligned rectangle).
     */
    BILLBOARD_SHAPE  
  };
  
  /**
   * Predefined shapes from which particles are emitted.
   */ 
  enum EmitShapeType {  
    /**
     * Emission from a point.
     */ 
    POINT,
    /**
     * Emission from a cylinder.
     */ 
    CYLINDER,
    /**
     * Emission from a line.
     */ 
    LINE,
    /**
     * Emission from a square.
     */ 
    SQUARE,
    /**
     * Emission from a sphere.
     */ 
    SPHERE,
    /**
     * Emission from a circle.
     */ 
    CIRCLE,
    /**
     * Emission from a disk.
     */ 
    DISK,
    /**
     * Emission from a specified geometric shape. Not implemented.
     */ 
    GEOMETRY
  };
  
  /**
   * Particle life.
   */ 
  enum ParticleLife {
    /**
     * Particles are emitted once.
     */
    ONE_EMISSION,
    /**
     * Particles are emitted cyclically.
     */
    CYCLIC_EMISSION
  };

  /**
   * Type of transparency used by particle.
   */
  enum TransparencyType {
    /**
     * Additive alpha blending.
     */
    ADD,
    /**
     * Multiplicative alpha blending.
     */
    BLEND,
    /**
     * Inherited alpha blending defined by SoGLRenderAction::setTransparencyType().
     */
    INHERITED 
  };
    
  /** 
   * Constructor
   */
  SoParticleAnimation();

  /** 
   * Number of emitted particles.
   */
  SoSFInt32 numParticles;
  
  /**
   * Controls magnitude of random variation in the number of emitted particles.
   * Emitted particles = #numParticles + (#numParticles * #numParticlesVariation * RF)
   * with -1 <= RF <= 1
   */
  SoSFFloat numParticlesVariation;
  
  /**
   * Initial particle color.
   */
  SoSFColor initialColor;  
  
  /**
   * Controls magnitude of random variation in the initial particle color.
   * Initial Color = #initialColor + (#initialColor * #initialColorVariation * RF)
   * with -1 <= RF <= 1.
   */
  SoSFVec3f initialColorVariation;  
  
  /**
   * Initial particle opacity: 
   * 0 is fully transparent,
   * 1 is opaque.
   */
  SoSFFloat initialOpacity;  
  
  /**
   * Controls magnitude of random variation in the initial particle opacity.
   * Initial Opacity = #initialOpacity + (#initialOpacity * #initialOpacityVariation * RF)
   * with -1 <= RF <= 1.
   */
  SoSFFloat initialOpacityVariation;
  
  /**
   * Initial particle size in world coordinates.
   */
  SoSFFloat initialSize;
  
  /**
   * Controls magnitude of random variation in the initial particle size.
   * Initial Size = #initialSize + (#initialSize * #initialSizeVariation * RF)
   * with -1 <= RF <= 1.
   */
  SoSFFloat initialSizeVariation;
 
  /**
   * Final particle color.
   */
  SoSFColor endColor;
  
  /**
   * Controls magnitude of random variation in the final particle color.
   * End Color = #endColor + (#endColor * #endColorVariation * RF)
   * with -1 <= RF <= 1.
   */
  SoSFVec3f endColorVariation;
  
  /**
   * Final particle opacity: 
   * 0 = fully transparent,
   * 1 = opaque.
   */
  SoSFFloat endOpacity;
  
  /**
   * Controls magnitude of random variation in the final particle opacity.
   * End Opacity = #endOpacity + (#endOpacity * #endOpacityVariation * RF)
   * with -1 <= RF <= 1.
   */
  SoSFFloat endOpacityVariation;
  
  /**
   * Final particle size in world coordinates.
   */
  SoSFFloat endSize;
  
  /**
   * Controls magnitude of random variation in the final particle size.
   * End Size = #endSize + (#endSize * #endSizeVariation * RF)
   * with -1 <= RF <= 1.
   */
  SoSFFloat endSizeVariation;
  
  /**
   * Particle life span in milliseconds.
   */
  SoSFInt32 lifeSpan;
  
  /**
   * Controls magnitude of random variation in the particle life span.
   * Life span = #lifeSpan + (#lifeSpan * #lifeSpanVariation * RF)
   * with -1 <= RF <= 1.
   */
  SoSFFloat lifeSpanVariation;
  
  /**
   * Specifies the shape of the particles.
   * Only SoParticleAnimation::BILLBOARD_SHAPE shapes are textured.
   */
  SoSFEnum particleShape;
   
  /**
   * Specifies a predefined shape from which particles are emitted.
   * Particles are transformed by the current cumulative transformation.
   * Particles can be uniformly emitted from:
   *    - a point (SoParticleAnimation::POINT): Centered at (0,0,0).
   *
   *    - a cylinder (SoParticleAnimation::CYLINDER): Centered at (0,0,0),
   *      Radius = 1, Height = 1, with the central axis parallel to the y-axis.
   *
   *    - a line (SoParticleAnimation::LINE): From (-1,0,0) to (1,0,0).
   *
   *    - a square (SoParticleAnimation::SQUARE): Centered at (0,0,0),
   *      Width = 2, Height = 2, aligned with the XY plane.
   *
   *    - a sphere (SoParticleAnimation::SPHERE): Centered at (0,0,0) with Radius = 1.
   *
   *    - a circle (SoParticleAnimation::CIRCLE): Centered at (0,0,0), Radius = 1, and
   *      aligned with the XY plane.      
   *
   *    - a disk (SoParticleAnimation::DISK): Centered at (0,0,0), Radius = 1, and
   *      aligned with the XY plane.
   */
  SoSFEnum emitShapeType;
  
  /**
   * Specifies a nonuniform scale factor applied to the predefined shape from
   * which particles are emitted.
   * Not used if #emitShapeType == SoParticleAnimation::POINT.
   */
  SoSFVec3f shapeScale;
  
  /**
   * Defines two angles (specified in radians) within which particles are randomly emitted.
   * yaw = #dispersionAngles[0] and pitch = #dispersionAngles[1].
   * yaw is an angle measured from y-axis and around the x-axis.
   * pitch is an angle measured from the z-axis and around the y-axis.
   * These two angles are ignored for all solid emitter shapes (SoParticleAnimation::SPHERE, 
   * SoParticleAnimation::CYLINDER).
   */
  SoSFVec2f dispersionAngles;
  
  /**
   * Specifies if particles are emitted one time (SoParticleAnimation::ONE_EMISSION) 
   * or cyclically (SoParticleAnimation::CYCLIC_EMISSION). 
   * If one-time emission is selected, particles are emitted when the field #trigger 
   * is set.
   */
  SoSFEnum particleLife;
  
  /**
   * Specifies the particle speed in units per second.
   */
  SoSFFloat speed;
  
  /**
   * Controls magnitude of random variation in the particle speed.
   * Particle Speed = #speed + (#speed * #speedVariation * RF)
   * with -1 <= RF <= 1.
   */
  SoSFFloat speedVariation;
  
  /**
   * Specifies the name of the file containing the texture
   * to be applied to the particles. 
   * As soon as the texture in the file is loaded, the field #particleTexture is updated.
   * The standard image file formats are
   * supported. See SoRasterImageRW for the list. 
   * If the filename is not an absolute path name, the list of directories maintained by 
   * SoInput is searched. 
   * If the texture is not found in any of those directories, 
   * then the file is searched for relative to the directory from which the 
   * #SoParticleAnimation node was read.
   */
  SoSFFilePathString particleFilename;
  
  /**
   * Specifies an in-memory texture used for particles.
   * It can be the contents of the file read from #particleFilename, an image read 
   * directly from an Open Inventor file, or an image defined programmatically 
   * using the methods provided by SoSFImage.
   * The default texture is a circular gradient, with gray in the middle and
   * black on the edges. It contains no alpha values.
   */
  SoSFImage particleTexture;
  
  /**
   * 
   * Indicates the goal number of frames per second for
   * refreshing the particles.
   * Setting the value to 0 requests that particles be refreshed
   * as often as possible.
   *
   * @FIELD_SINCE_OIV 4.0
   */
  SoSFFloat goalFramesPerSecond;
  
  /**
   * Has two meanings depending on the value of #particleLife:
   *
   * - #particleLife = SoParticleAnimation::ONE_EMISSION: Starts a new emission.
   *
   * - #particleLife = SoParticleAnimation::CYCLIC_EMISSION: Initializes the cyclic emission.
   */
  SoSFTrigger trigger;
 
  /**
   * Transparency type used for drawing particles.
   */
  SoSFEnum transparencyType;

  /**
   * Activates/deactivates the particle system.
   */
  SoSFBool on;
  
  /*-----------------------------------------------------------------------------*/

 SoEXTENDER public:
  virtual void computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center);
  virtual void rayPick(SoRayPickAction *action);
  virtual void GLRender(SoGLRenderAction *action);

 SoINTERNAL public:
  static void initClass();
  static void exitClass() ;

 protected:
  void init(void);
  // Destructor
  virtual ~SoParticleAnimation();
  
  virtual void generatePrimitives(SoAction *action);

  void loadTexture();
  
 private:
  // update positions particules (Particules.cxx) 
  void update(unsigned long currentTime);
  void initParticle(CParticle *p, unsigned long time);
  void getRandomPositionAndDirectionInShape(CPoint3D *position, CVector3D  *direction);
  void rotationToDirection(float pitch, float yaw, CVector3D *dir);


  void renderPoints();
  void renderLines();
  void renderBillboards();

  static void timerSensorCB(void *data, SoSensor *);

  // the dead ones
  SbPParticleList *m_deadParticles;
  // the funky ones
  SbPParticleList *m_aliveParticles;

  float m_emissionResidue;

  // rayPick
  SbBool pickingBoundingBox;

  // Time in ms
  unsigned long m_currentTime;
  unsigned long m_lastTime;

  // texturing 
  GLuint m_handle;

  // for ModelView matrix
  SbMatrix curModelMatrix;

  // Image management
  // to load image dynamically
  static void  imageChangedCB(void *, SoSensor *);
  static void filenameChangedCB(void *, SoSensor *);

  // Trigger management
  static void triggerFunc(void *data, SoSensor *);

  // These keep the image and filename fields in sync.
  SoFieldSensor *m_imageSensor;
  SoFieldSensor *m_filenameSensor;
  // for loading texture...one time
  SbBool m_textureLoaded;
  // trigger sensor
  SoFieldSensor *m_triggerSensor;

  // Timer sensor
  SoTimerSensor *m_timerSensor;
  SoOneShotSensor*  m_oneShotSensor ;

  // Previous cache context.
  int32_t m_prevCacheContext;

  int m_alreadyTriggered;
};


#endif // _SO_PARTICLE_ANIMATION_

