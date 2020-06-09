/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_STREAMSPHEREMOTION_
#define  _PO_STREAMSPHEREMOTION_

#include <MeshViz/3Ddata/PoStreamParticleMotion.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoSphere.h>

/**
 * @DTEXT  Animation of sphere particles along streamline.
 * 
 * @ingroup MeshRepresentation
 * 
 * @DESCRIPTION
 *    This class realizes animation as described in PoStreamParticleMotion. 
 *    A sphere of which radius is sphereRadius represents each particle.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoStreamSphereMotion {
 *    @TABLE_FILE_FORMAT
 *       @TR sphereRadius @TD 1.0
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
 * @CATALOG_PARTS_INCLUDE postreamspheremotion.cat.html
 * 
 * 
 */
class MESHVIZ_API PoStreamSphereMotion : public PoStreamParticleMotion {
  
  SO_KIT_HEADER(PoStreamSphereMotion) ;
  
  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(groupStreamSphereMotion) ;
  

 public:

  /**
   * Constructor.
   */
  PoStreamSphereMotion();

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void   rebuild();

  /**
   * Defines the radius of each sphere drawn. 1.0 by default.
   */
  SoSFFloat sphereRadius;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  // Destructor
  virtual ~PoStreamSphereMotion() ;  

  // Methods
  virtual void   setDefaultOnNonWritingFields();
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;

 private:
  // Sensors
  FieldSensorList m_fieldSensorList ;

  // List of fields defined in this class
  SoFieldList     m_fieldList ;

  // method to build the frames to be animated
  void newAnimator(SoGroup *group, SoLineSet *line_set, 
                   SoCoordinate3 *particle_coord, SoCoordinate3 *particle_speed, 
                   SoMFColor *particle_color);
  void endAnimator(SoGroup *group, SoLineSet *line_set, 
                   SoCoordinate3 *particle_coord, SoCoordinate3 *particle_speed, 
                   SoMFColor *particle_color);
  void newFrame(SoGroup *frame, int frame_ind);
  void endFrame(SoGroup *frame, int frame_ind);
  void newLine(SoGroup *line, int line_ind);
  void endLine(SoGroup *line, int line_ind);
  void newParticle(const SbVec3f &pos, const SbVec3f &speed, const SbVec3f &norm, const SbColor *color, int ind);

  SoGroup *m_currentLine;
  SoSphere *m_sphere;
  SoMFColor     *m_particleColor;
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_STREAMSPHEREMOTION_ */


