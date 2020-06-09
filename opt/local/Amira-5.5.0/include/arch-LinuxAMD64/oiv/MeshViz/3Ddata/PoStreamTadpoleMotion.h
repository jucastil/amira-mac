/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_STREAMTADPOLEMOTION_
#define  _PO_STREAMTADPOLEMOTION_

#include <MeshViz/3Ddata/PoStreamParticleMotion.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFColor.h>

/**
 * @DTEXT  Animation of tadpole particles along streamline.
 * 
 * @ingroup MeshRepresentation
 * 
 * @DESCRIPTION
 *    Class to visualize particle along streamlines on a mesh.
 *    Each particle is represented by a line set which looks like a tadpole.
 *    
 *    Each particle is represented by a segment made up of 3 aligned points. 
 *    The segment's length is equal to lengthFactor*V, where V is the
 *    velocity interpolated at the position of the particle. Each segment
 *    has a width attribute equal width. 
 * 
 *    The 2 end points of each segment is colored by backColor. 
 *    If PoMesh::coloringType != COLOR_INHERITED and if PoMesh::valuesIndex
 *    is defined (i.e. >=0) the middle point is colored in applying the current
 *    data mapping to the scalar value interpolated at the particle position. 
 *    If PoMesh::valuesIndex is undefined (i.e. <0) the middle point is colored 
 *    in applying the current data mapping to the velocity interpolated at the
 *    position of the particle. Otherwise (PoMesh::coloringType = COLOR_INHERITED),
 *    if PoBaseStreamLine::colors is not empty, the middle point is colored by 
 *    one of these colors (all the particle of the same streamline have the same
 *    color), or by particleColor if PoBaseStreamLine::colors is empty.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoStreamTadpoleMotion {
 *    @TABLE_FILE_FORMAT
 *       @TR width @TD 2.0
 *       @TR backColor @TD (0.0,0.0,0.0)
 *       @TR particleColor @TD SbColor(0.0,0.9,0.9)
 *       @TR lengthFactor @TD 1.0
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
 * @CATALOG_PARTS_INCLUDE postreamtadpolemotion.cat.html
 * 
 * 
 */
class MESHVIZ_API PoStreamTadpoleMotion : public PoStreamParticleMotion {
  
  SO_KIT_HEADER(PoStreamTadpoleMotion) ;
  
  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(groupStreamTadpoleMotion) ;
  

 public:

  /**
   * Constructor.
   */
  PoStreamTadpoleMotion();

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void   rebuild();

  /**
   * Width of each tadpole segment. 2.0 by default.
   */
  SoSFFloat width;

  /**
   * Length factor applied to the velocity.
   */
  SoSFFloat lengthFactor;

  /**
   * Background color applied on the end points of each segment.
   */
  SoSFColor backColor;

  /**
   * Color used at the middle point of each segment. Used only
   * if PoMesh::coloringType = COLOR_INHERITED, and PoBaseStreamLine::colors empty.
   */
  SoSFColor particleColor;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  // Destructor
  virtual ~PoStreamTadpoleMotion() ;  

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

  int m_lineNumPoints;
  SoCoordinate3 *m_lineCoordinate;
  
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_STREAMTADPOLEMOTION_ */


