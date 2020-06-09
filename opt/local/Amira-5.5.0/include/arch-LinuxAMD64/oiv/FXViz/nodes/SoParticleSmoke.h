/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : A. SURE (Sep 2001)
**=======================================================================*/

                                                             /* include files */
#ifndef _SO_PARTICLE_SMOKE_
#define _SO_PARTICLE_SMOKE_

#include <FXViz/nodes/SoParticleAnimation.h>

/*-----------------------------------------------------------------------------*/
/**
 * @FXEXT Particle system node for generating a smoke effect.
 * 
 * @ingroup FXViz
 * 
 * @DESCRIPTION
 *   Class for producing a smoke effect. This node is simply a 
 *   subclass of SoParticleAnimation that has a different set of default
 *   values for its fields in order to produce the smoke effect.
 *
 * @FILE_FORMAT_DEFAULT
 *    ParticleAnimation {
 *    @TABLE_FILE_FORMAT
 *               @TR numParticles            @TD 800
 *               @TR numParticlesVariation       @TD 0.5
 *               @TR initialColor                        @TD 0.4 0.4 0.4
 *               @TR initialColorVariation       @TD 0.5 0.5 0.5
 *               @TR initialOpacity                      @TD 0.1
 *               @TR initialOpacityVariation @TD 0.2
 *               @TR initialSize                         @TD 0.5
 *               @TR initialSizeVariation        @TD 0.5
 *
 *               @TR endColor                            @TD 0.2 0.2 0.2
 *               @TR endColorVariation           @TD 0.2 0.2 0.2
 *               @TR endOpacity                          @TD 0.8
 *               @TR endOpacityVariation         @TD 0.5
 *               @TR endSize                             @TD 1
 *               @TR endSizeVariation            @TD 1
 *
 *               @TR lifeSpan                            @TD 6000
 *               @TR lifeSpanVariation           @TD 1
 *
 *               @TR particleShape                       @TD BILLBOARD_SHAPE
 *       @TR 
 *               @TR emitShapeType                       @TD POINT
 *               @TR shapeScale                          @TD 1 1 1
 *
 *               @TR dispersionAngles        @TD 1.5 1.5
 *       @TR 
 *               @TR particleLife                        @TD CYCLIC_EMISSION
 *       @TR
 *               @TR speed                                       @TD 0.5
 *               @TR speedVariation                      @TD 0.1
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
 *    SoParticleExplosion, SoParticleSnow.
 * 
 * 
 */ 

class FXVIZ_API SoParticleSmoke : public SoParticleAnimation {

 public:
  /**
   * Constructor.
   */
  SoParticleSmoke();
  
} ;


#endif // _SO_PARTICLE_SMOKE_

