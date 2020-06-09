/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : A. SURE (Sep 2001)
**=======================================================================*/

                                                             /* include files */
#ifndef _SO_PARTICLE_CHEMICAL_FLAME_
#define _SO_PARTICLE_CHEMICAL_FLAME_

#include <FXViz/nodes/SoParticleAnimation.h>

/*-----------------------------------------------------------------------------*/

/**
 * @FXEXT Particle system node for generating a chemical flame effect.
 * 
 * @ingroup FXViz
 * 
 * @DESCRIPTION
 *   Class for producing a chemical flame effect. This node is simply a 
 *   subclass of SoParticleAnimation that has a different set of default
 *   values for its fields in order to produce the chemical flame effect. 
 *
 * @FILE_FORMAT_DEFAULT
 *    ParticleAnimation {
 *    @TABLE_FILE_FORMAT
 *               @TR numParticles            @TD 1000
 *               @TR numParticlesVariation       @TD 0.1
 *               @TR initialColor                        @TD 0.15 0.27 0.97
 *               @TR initialColorVariation       @TD 0 0 0
 *               @TR initialOpacity                      @TD 0.8
 *               @TR initialOpacityVariation @TD 0.1
 *               @TR initialSize                         @TD 0.5
 *               @TR initialSizeVariation        @TD 0.5
 *
 *               @TR endColor                            @TD 0 0.25 0
 *               @TR endColorVariation           @TD 0 0 0
 *               @TR endOpacity                          @TD 0.8
 *               @TR endOpacityVariation         @TD 1
 *               @TR endSize                             @TD 0.8
 *               @TR endSizeVariation            @TD 1
 *
 *               @TR lifeSpan                            @TD 1000
 *               @TR lifeSpanVariation           @TD 0.5
 *
 *               @TR particleShape                       @TD BILLBOARD_SHAPE
 *       @TR 
 *               @TR emitShapeType                       @TD POINT
 *               @TR shapeScale                          @TD 1 1 1
 *
 *               @TR dispersionAngles        @TD 0.44 0.44
 *       @TR 
 *               @TR particleLife                        @TD CYCLIC_EMISSION
 *       @TR
 *               @TR speed                                       @TD 4
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
 *    SoFXViz, SoParticleAnimation, SoParticleExplosion, SoParticleFlame, SoParticleLightRay,
 *    SoParticleSmoke, SoParticleSnow.
 * 
 * 
 */ 
class FXVIZ_API SoParticleChemicalFlame : public SoParticleAnimation {

 public:
  /**
   * Constructor.
   */
  SoParticleChemicalFlame();
  
} ;


#endif // _SO_PARTICLE__CHEMICAL_FLAME_

