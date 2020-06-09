/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : A. SURE (Sep 2001)
**=======================================================================*/

                                                             /* include files */
#ifndef _SO_PARTICLE_LIGHT_RAY_
#define _SO_PARTICLE_LIGHT_RAY_

#include <FXViz/nodes/SoParticleAnimation.h>

/*-----------------------------------------------------------------------------*/
/**
 * @FXEXT Particle system node for generating a light ray effect.
 * 
 * @ingroup FXViz
 * 
 * @DESCRIPTION
 *   Class for producing a light ray effect. This node is simply a 
 *   subclass of SoParticleAnimation that has a different set of default
 *   values for its fields in order to produce the light ray effect.
 *
 * @FILE_FORMAT_DEFAULT
 *    ParticleAnimation {
 *    @TABLE_FILE_FORMAT
 *               @TR numParticles            @TD 5000
 *               @TR numParticlesVariation       @TD 0.
 *               @TR initialColor                        @TD 0.7 0.7 0.9
 *               @TR initialColorVariation       @TD 0.1 0.1 0.1
 *               @TR initialOpacity                      @TD 0.8
 *               @TR initialOpacityVariation @TD 0.1
 *               @TR initialSize                         @TD 0.1
 *               @TR initialSizeVariation        @TD 2
 *
 *               @TR endColor                            @TD 0.7 0.7 0.9
 *               @TR endColorVariation           @TD 0.1 0.1 0.1
 *               @TR endOpacity                          @TD 0.8
 *               @TR endOpacityVariation         @TD 0.1
 *               @TR endSize                             @TD 0.1
 *               @TR endSizeVariation            @TD 2
 *
 *               @TR lifeSpan                            @TD 100
 *               @TR lifeSpanVariation           @TD 0.5
 *
 *               @TR particleShape                       @TD BILLBOARD_SHAPE
 *       @TR 
 *               @TR emitShapeType                       @TD POINT
 *               @TR shapeScale                          @TD 1 1 1
 *
 *               @TR dispersionAngles        @TD 0 0
 *       @TR 
 *               @TR particleLife                        @TD CYCLIC_EMISSION
 *       @TR
 *               @TR speed                                       @TD 50
 *               @TR speedVariation                      @TD 1
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
 *    SoFXViz, SoParticleAnimation, SoParticleChemicalFlame, SoParticleFlame, SoParticleExplosion,
 *    SoParticleSmoke, SoParticleSnow.
 * 
 * 
 */ 

class FXVIZ_API SoParticleLightRay : public SoParticleAnimation {

 public:
  /**
   * Constructor.
   */
  SoParticleLightRay();
  
} ;


#endif // _SO_PARTICLE_LIGHT_RAY_

