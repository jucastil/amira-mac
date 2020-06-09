/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_STREAMLINEMOTION_
#define  _PO_STREAMLINEMOTION_

#include <MeshViz/3Ddata/PoStreamParticleMotion.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFColor.h>

/**
 * @DTEXT  Representation of streamlines with motion of colors.
 * 
 * @ingroup MeshRepresentation
 * 
 * @DESCRIPTION
 *     Class to visualize streamlines on a mesh, with a motion of color on the 
 *     lines that simulates a animation of particles. Each line is drawn with 
 *     only 2 colors : lineColor is the background color of the streamline, and
 *     particleColor is the color of some parts of the line that move during
 *     visualization. The field PoMesh::coloringType and PoMesh::valuesIndex
 *     are not used by this class.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoStreamLineMotion {
 *    @TABLE_FILE_FORMAT
 *       @TR lineWidth @TD 2.0
 *       @TR lineColor @TD SbColor(0.0,0.0,0.4)
 *       @TR particleColor @TD SbColor(0.0,0.9,0.9)
 *       @TR pulseFrequency @TD 5
 *       @TR shiftStart @TD 0.0
 *       @TR timeStep @TD 1.0
 *       @TR isStartRandomized @TD TRUE
 *       @TR isBlinking @TD TRUE
 *       @TR viewFrame @TD 0
 *       @TR blinkSpeed @TD 3.0
 *       @TR valuesIndex @TD -1
 *       @TR coloringType @TD COLOR_INHERITED
 *       @TR vecsIndex @TD -1
 *       @TR valuesIndexForCellFilter  @TD -1
 *       @TR moduleDataMapping @TD NULL
 *       @TR startPoints @TD SbVec3f(0,0,0)
 *       @TR maxLifetime @TD 0 (i.e. infinite)
 *       @TR maxLength @TD 0 (i.e. infinite)
 *       @TR minSpeed @TD 0 (i.e. infinite)
 *       @TR integrationStepLengthFactor @TD 0.3
 *       @TR integrationMaxStepNumber @TD 0 (i.e. infinite)
 *       @TR integrationDirection @TD FORWARD 
 *       @TR colors @TD (SbColor(1,0,0)
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE postreamlinemotion.cat.html
 * 
 * 
 */
class MESHVIZ_API PoStreamLineMotion : public PoStreamParticleMotion {
  
  SO_KIT_HEADER(PoStreamLineMotion) ;
  
  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(groupStreamLineMotion) ;
  

 public:

  /**
   * Constructor.
   */
  PoStreamLineMotion();

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void   rebuild();

  /* Fields */

  /**
   * Convenience field to set the width line attribute of each streamline drawn.
   * 2.0 by default.
   */
  SoSFFloat lineWidth;

  /**
   * Color of each streamlines. SbColor(0.0,0.0,0.4) by default.
   */
  SoSFColor lineColor;

  /**
   * Color of the particles that move along the streamline.
   * SbColor(0.0,0.9,0.9).
   */
  SoSFColor particleColor;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  virtual ~PoStreamLineMotion() ;  
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

  int m_numPoints;
  
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_STREAMLINEMOTION_ */


