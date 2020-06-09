/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_BASESTREAMLINE_
#define  _PO_BASESTREAMLINE_

#include <MeshViz/3Ddata/PoMesh.h>

class SbVec3f;
class PbCell;
class PiStreamPath;
class PoCellFilter;

/**
 * @DTEXT  Base class of all streamline representations on a mesh.
 * 
 * @ingroup MeshRepresentation
 * 
 * @DESCRIPTION
 *    Class to calculate the geometry of streamlines starting from a list of 
 *    source points. A streamline is a line that is everywhere tangent to the 
 *    vectors field. Streamlines are meaningless for unsteady flow, because the 
 *    time is not taken into account during the computation of the line. 
 *    Streamlines are calculated by using a Runge/Kutta method of order 2.
 * 
 *    The streamlines are calculated from a set of vectors in the current mesh.
 *    See PoMesh for more explanations about the current mesh. The index of
 *    vectors data set used to compute streamlines, is defined by the field 
 *    PoMesh::vecsIndex. If this vectors data set does not exist in the current
 *    mesh, the representation is empty. The origin of each vector is a node of
 *    the mesh. 
 * 
 *    The derived classes respect the following rules to color the representation:
 * 
 *    If PoMesh::coloringType = COLOR_INHERITED and if the field "colors" is empty, 
 *    the representation uses only one inherited color, so each part of the 
 *    representation have the same color. 
 * 
 *    If PoMesh::coloringType = COLOR_INHERITED and if the field colors is not 
 *    empty, the representation uses each colors of field for each streamline. 
 *    For example, the streamline starting from the i-th startPoints is colored 
 *    by colors[i%num_colors], where num_colors is the size of the field 
 *    "colors".
 * 
 *    If the field PoMesh::valuesIndex is not defined (i.e. < 0), and if 
 *    coloringType != COLOR_INHERITED, the representations are colored by using 
 *    the current data mapping applied to the velocity at each point of the 
 *    streamlines. The definition of the "current data mapping" is explained 
 *    in PoMesh.
 * 
 *    If the field PoMesh::valuesIndex is defined, and if coloringType != 
 *    COLOR_INHERITED, the representations are colored by using the current 
 *    data mapping applied to the value at each point of the streamlines.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoBaseStreamLine {
 *    @TABLE_FILE_FORMAT
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
 * 
 */
class MESHVIZ_API PoBaseStreamLine : public PoMesh {
  
  SO_KIT_HEADER(PoBaseStreamLine) ;
  

 public:

  /**
   * Constructor.
   */
  PoBaseStreamLine() ;

  /* Fields */

  /**
   * Start points of the streamlines. SbVec3f(0,0,0) by default.    
   */
  SoMFVec3f startPoints;                  

  /**
   * List of colors used by some derived class to color each streamline. 
   * Empty field by default.                
   */
  SoMFColor colors;     

  /**
   * The difference between the time of the start-point and the time of the last point of 
   * a streamline must be less than maxLifetime. maxLifetime <= 0 means an infinite 
   * lifetime. 0 by default.
   */
  SoSFFloat maxLifetime;

  /**
   * The curvilinear distance between the start-point and the last point of a streamline 
   * must be less than maxLength. maxLength <= 0 means an infinite distance. 0 by default.
   */
  SoSFFloat maxLength;  

  /**
   * The streamline ends when it goes through a point where the velocity is less than 
   * minSpeed. minSpeed <= 0 means an infinite speed. 0 by default.
   */
  SoSFFloat minSpeed;   

  /**
   * It is a factor of the size of a cell. It represents the gap between two consecutive 
   * points of the calculated streamline. The gap depends of the cell's size. If S is the 
   * size of the current cell, the gap is S*integrationStepLengthFactor. The lower this 
   * step is, the more accurate the streamline is. Setting a value < 1, ensures that each 
   * cell which cross the streamline is taken into account. 0.3 by default.
   */
  SoSFFloat integrationStepLengthFactor;

  /**
   * Computing the streamline is done while the number of integration step is
   * less than integrationMaxStepNumber. integrationMaxStepNumber <= 0 means infinite.
   * 0 by default.
   */
  SoSFInt32 integrationMaxStepNumber;

  /**
   * Direction of integration. FORWARD by default.
   */
  SoSFEnum  integrationDirection;

  /**
   *  Type of integration direction
   */
  enum IntegrationDirection {
    /**
     *  Integration is done as the direction of the vectors.
     */
    FORWARD,  
    /**
     *  Integration is done as the inverse of the direction of the vectors.
     */
    BACKWARD  
  } ;



  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

  void integrateStreamLine(const PbCell *start_cell, const SbVec3f &start_point, const SbVec3f &pcoord, PiStreamPath &stream_path, 
                           float &length, float &time,
                           const PoCellFilter* cell_filter,const float *values_filter);
  void integrateStreamLine(const SbVec3f &start_point, PiStreamPath &stream_path,
                           float &length, float &time);

 protected:
  virtual ~PoBaseStreamLine() ;  
  // Destructor

  // Methods
  virtual void   setDefaultOnNonWritingFields() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void addElementsAllCaches() ;
  virtual void preRebuild();

  virtual void saveNorm(PiStreamPath &stream_path, const PbCell *cell, SbVec3f &coord, SbVec3f &pcoords);
  virtual void saveSpeed(PiStreamPath &stream_path, SbVec3f &speed);
  virtual void saveTime(PiStreamPath &stream_path, float time);

 private:
  // Sensors
  FieldSensorList m_fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     m_fieldList ;
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_BASESTREAMLINE_ */


