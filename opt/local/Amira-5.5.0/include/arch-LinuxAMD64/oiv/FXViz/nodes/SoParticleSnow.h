/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : A. SURE (Sep 2001)
**=======================================================================*/

                                                             /* include files */
#ifndef _SO_PARTICLE_SNOW_
#define _SO_PARTICLE_SNOW_

#include <FXViz/nodes/SoParticleAnimation.h>

/*-----------------------------------------------------------------------------*/
/**
 * @FXEXT Particle system node for generating a snow effect.
 * 
 * @ingroup FXViz
 * 
 * @DESCRIPTION
 *   Class for producing a snow effect. This node is simply a 
 *   subclass of SoParticleAnimation that has a different set of default
 *   values for its fields in order to produce the snow effect.
 *
 * @FILE_FORMAT_DEFAULT
 *    ParticleAnimation {
 *    @TABLE_FILE_FORMAT
 *               @TR numParticles            @TD 15000
 *               @TR numParticlesVariation       @TD 0.5
 *               @TR initialColor                        @TD 1 1 1
 *               @TR initialColorVariation       @TD 0 0 0
 *               @TR initialOpacity                      @TD 0.8
 *               @TR initialOpacityVariation @TD 0.1
 *               @TR initialSize                         @TD 0.05
 *               @TR initialSizeVariation        @TD 0.1
 *
 *               @TR endColor                            @TD 1 1 1
 *               @TR endColorVariation           @TD 0 0 0
 *               @TR endOpacity                          @TD 0.8
 *               @TR endOpacityVariation         @TD 0.1
 *               @TR endSize                             @TD 0.1
 *               @TR endSizeVariation            @TD 0.5
 *
 *               @TR lifeSpan                            @TD 10000
 *               @TR lifeSpanVariation           @TD 1
 *
 *               @TR particleShape                       @TD BILLBOARD_SHAPE
 *       @TR 
 *               @TR emitShapeType                       @TD SQUARE
 *               @TR shapeScale                          @TD 10 10 10
 *
 *               @TR dispersionAngles        @TD 0.44 0.44
 *       @TR 
 *               @TR particleLife                        @TD CYCLIC_EMISSION
 *       @TR
 *               @TR speed                                       @TD 1
 *               @TR speedVariation                      @TD 0.3
 *
 *               @TR particleFilename            @TD ""
 *               @TR particleTexture             @TD 32 32 ....(white circle on a black background texture ) 
 *
 *               @TR goalFramesPerSecond         @TD 10
 *               @TR transparencyType    @TD ADD
 *
 *               @TR on                                          @TD TRUE
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoFXViz, SoParticleAnimation, SoParticleChemicalFlame, SoParticleFlame, SoParticleLightRay,
 *    SoParticleExplosion, SoParticleSmoke.
 * 
 * 
 */ 

class FXVIZ_API SoParticleSnow : public SoParticleAnimation {

 public:
  /**
   * Constructor.
   */
  SoParticleSnow();
  
} ;


#endif // _SO_PARTICLE_SNOW_

