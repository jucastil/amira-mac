/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : A. SURE (Sep 2001)
**=======================================================================*/

                                                             /* include files */
#ifndef _SO_PARTICLE_EXPLOSION_
#define _SO_PARTICLE_EXPLOSION_

#include <FXViz/nodes/SoParticleAnimation.h>

/*-----------------------------------------------------------------------------*/
/**
 * @FXEXT Explosion particle system node.
 * 
 * @ingroup FXViz
 * 
 * @DESCRIPTION
 *   Class for producing an explosion effect. This node is simply a subclass
 *  of SoParticleAnimation that has a different set of default values for its fields 
 *  in order to produce the explosion effect. 
 *
 * @FILE_FORMAT_DEFAULT
 *    ParticleAnimation {
 *    @TABLE_FILE_FORMAT
 *               @TR numParticles            @TD 1000
 *               @TR numParticlesVariation       @TD 0.
 *               @TR initialColor                        @TD 0.8 0.44 0.01
 *               @TR initialColorVariation       @TD 0.25 0 0
 *               @TR initialOpacity                      @TD 0.8
 *               @TR initialOpacityVariation @TD 0.1
 *               @TR initialSize                         @TD 0.8
 *               @TR initialSizeVariation        @TD 0.8
 *
 *               @TR endColor                            @TD 0.3 0.1 0
 *               @TR endColorVariation           @TD 0.3 0 0
 *               @TR endOpacity                          @TD 0.8
 *               @TR endOpacityVariation         @TD 0.1
 *               @TR endSize                             @TD 4
 *               @TR endSizeVariation            @TD 0.5
 *
 *               @TR lifeSpan                            @TD 200
 *               @TR lifeSpanVariation           @TD 8.
 *
 *               @TR particleShape                       @TD BILLBOARD_SHAPE
 *       @TR 
 *               @TR emitShapeType                       @TD SPHERE
 *               @TR shapeScale                          @TD 1 1 1
 *
 *               @TR dispersionAngles        @TD 0.01 0.01
 *       @TR 
 *               @TR particleLife                        @TD ONE_EMISSION
 *       @TR
 *               @TR speed                                       @TD 1.4
 *               @TR speedVariation                      @TD 0.8
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
 *    SoParticleSmoke, SoParticleSnow.
 * 
 * 
 */ 
class FXVIZ_API SoParticleExplosion : public SoParticleAnimation {

 public:
  /**
   * Constructor.
   */
  SoParticleExplosion();
  
} ;


#endif // _SO_PARTICLE_EXPLOSION_

