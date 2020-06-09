/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_STREAMPOINTMOTION_
#define  _PO_STREAMPOINTMOTION_

#include <MeshViz/3Ddata/PoStreamParticleMotion.h>
#include <Inventor/fields/SoSFBool.h>


/**
 * @DTEXT  Animation of point particles along streamline.
 * 
 * @ingroup MeshRepresentation
 * 
 * @DESCRIPTION
 *    Class for animation of particles along streamlines on a mesh. The 
 *    animation is done as described in PoStreamParticleMotion. 
 *    A point of which size is pointSize represents each particle.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoStreamPointMotion {
 *    @TABLE_FILE_FORMAT
 *       @TR pointSize @TD 3.0
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
 * @CATALOG_PARTS_INCLUDE postreampointmotion.cat.html
 * 
 * 
 */
class MESHVIZ_API PoStreamPointMotion : public PoStreamParticleMotion {
  
  SO_KIT_HEADER(PoStreamPointMotion) ;
  
  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(groupStreamPointMotion) ;


 public:

  /**
   * Constructor.
   */
  PoStreamPointMotion();

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void   rebuild();

  /* Fields */

  /**
   * Convenience field to set the point size attribute.
   * 3.0 by default.
   */
  SoSFFloat pointSize;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  virtual ~PoStreamPointMotion() ;  
  // Destructor

  virtual void   setDefaultOnNonWritingFields();
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;

 private:
  FieldSensorList m_fieldSensorList ;
  // Sensors

  SoFieldList     m_fieldList ;
  // List of fields defined in this class

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
  // method to build the frames to be animated

  SoCoordinate3 *m_lineCoordinate;
  SoMFColor     *m_particleColor;
  SoMFColor     *m_lineColor;
  int m_lineNumPoints;
  
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_STREAMPOINTMOTION_ */


