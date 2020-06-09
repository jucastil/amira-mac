/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_MESH3DVEC_
#define  _PO_MESH3DVEC_

#include <Inventor/SbLinear.h>
#include <MeshViz/3Ddata/PoMesh3D.h>

class PiArrow;
class PbIndexedMesh3D;
class PbTetrahedronMesh3D;
class PbHexahedronMesh3D;
class PbCartesianGrid3D;
class PbParalCartesianGrid3D;
class PbRegularCartesianGrid3D;

/**
 * @DTEXT  Representation of vectors data of a volume mesh.
 * 
 * @ingroup MeshRepresentation
 * 
 * @DESCRIPTION
 *    Class to build a vectors field on a volume mesh. This class handles all 
 *    vectors attributes. A vector is represented by an arrow made of 3 parts, 
 *    the body, the start-shape and the end-shape. The body is a line or a 
 *    cylinder starting from a node of the mesh. The start-shape is a pattern 
 *    drawn at the node position. The end-shape is a pattern drawn at the other 
 *    extremity of the body. Several type of pattern can be used to draw the 
 *    shape. The 3 parts can be scaled and colored according to the value of 
 *    the different fields of the class.
 *    
 *    The current mesh is used for the representation of vectors. See PoMesh for 
 *    more explanations about the current mesh. The vectors of the mesh to be  
 *    drawn, are defined by the method addVecsSet of the current mesh (see 
 *    PoMeshProperty or PbMesh), and by the field PoMesh::vecsIndex. 
 *    The node of the mesh are used as start point of the representation of the 
 *    vectors.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoMesh3DVec {
 *    @TABLE_FILE_FORMAT
 *       @TR density @TD 1
 *       @TR eliminationStatus @TD NONE
 *       @TR minLength @TD 0.0
 *       @TR maxLength @TD 1E30
 *       @TR bodyShape @TD LINE
 *       @TR bodyLengthType @TD RELATIVE_LENGTH
 *       @TR bodyLengthFactor @TD 1.0
 *       @TR bodyRadiusType @TD CONSTANT_RADIUS
 *       @TR bodyRadiusFactor @TD 0.02
 *       @TR bodyColoringType @TD CONSTANT_COLOR
 *       @TR startArrowShape @TD NO_SHAPE
 *       @TR startArrowHeightType @TD RELATIVE_HEIGHT
 *       @TR startArrowHeightFactor @TD 0.1
 *       @TR startArrowRadiusFactor @TD 0.5
 *       @TR startArrowColoringType @TD CONSTANT_COLOR
 *       @TR endArrowShape @TD CHEVRON
 *       @TR endArrowHeightType @TD RELATIVE_HEIGHT
 *       @TR endArrowHeightFactor @TD 0.1
 *       @TR endArrowRadiusFactor @TD 0.5
 *       @TR endArrowColoringType @TD CONSTANT_COLOR
 *       @TR coloringType @TD COLOR_INHERITED
 *       @TR valuesIndex @TD -1
 *       @TR valuesIndexForCellFilter  @TD -1
 *       @TR vecsIndex @TD -1
 *       @TR moduleDataMapping @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pomesh3dvec.cat.html
 * 
 * 
 */
class MESHVIZ_API PoMesh3DVec : public PoMesh3D {

  SO_KIT_HEADER(PoMesh3DVec) ;

  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(bodySep);
  SO_KIT_CATALOG_ENTRY_HEADER(bodyApp);
  SO_KIT_CATALOG_ENTRY_HEADER(bodyGroup);

  SO_KIT_CATALOG_ENTRY_HEADER(startArrowSep);
  SO_KIT_CATALOG_ENTRY_HEADER(startArrowApp);
  SO_KIT_CATALOG_ENTRY_HEADER(startArrowGroup);

  SO_KIT_CATALOG_ENTRY_HEADER(endArrowSep);
  SO_KIT_CATALOG_ENTRY_HEADER(endArrowApp);
  SO_KIT_CATALOG_ENTRY_HEADER(endArrowGroup);


 public:

  /**
   * Constructor.
   */
  PoMesh3DVec() ;

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void   rebuild() ;

  /**
   *  Type of vector elimination
   */
  enum EliminationStatus {
    NONE,
    TOO_SMALL,
    TOO_LONG,
    TOO_SMALL_OR_LONG
  } ;



  /**
   *  Type of body shape
   */
  enum BodyShape {
    NO_BODY,
    LINE,
    CYLINDER
  } ;



  /**
   *  Type of body lenght
   */
  enum BodyLengthType {
    CONSTANT_LENGTH,
    RELATIVE_LENGTH
  } ;



  /**
   *  Type of body radius
   */
  enum BodyRadiusType {
    CONSTANT_RADIUS,
    RELATIVE_RADIUS
  } ;



  /**
   *  Type of arrow shape
   */
  enum ArrowShape {
    NO_SHAPE,
    POINT,
    CHEVRON,
    TRIANGLE, 
    RECTANGLE,
    CONE,
    BOX,
    SPHERE,
    INDIRECT_CHEVRON,
    INDIRECT_TRIANGLE,
    INDIRECT_CONE
  } ;



  /**
   *  Type of height of an arrow
   */
  enum ArrowHeightType {
    CONSTANT_HEIGHT,
    RELATIVE_HEIGHT
  } ;



  /**
   *  Type of arrow coloring
   */
  enum ArrowColoringType {
    CONSTANT_COLOR,
    MODULE_MAPPING_COLOR,
    SCALAR_MAPPING_COLOR
  } ;



  /* Fields */

  /**
   * Vector field density filter. If density = 1, each vector of the mesh is drawn. If 
   * density = 2, one vector every 2 vectors is drawn...
   */
  SoSFInt32  density;                

  /**
   * If eliminationStatus = TOO_SMALL, the vectors which module is lower than 
   * minLength are not drawn. If eliminationStatus = TOO_LONG, the vectors 
   * which module is greater than maxLength are not drawn. If eliminationStatus = 
   * TOO_SMALL_OR_LONG, the vectors which module is lower than minLength 
   * or greater than maxLength are not drawn. If eliminationStatus = NONE, each 
   * vector selected by the density filter is drawn.
   */
  SoSFEnum   eliminationStatus;      

  /**
   * Minimum length of the vector to be drawn. Only used when eliminationStatus
   * is TOO_SMALL or TOO_SMALL_OR_LONG
   */
  SoSFFloat  minLength;              

  /**
   * Maximum length of the vector to be drawn. Only used when eliminationStatus
   * is TOO_LONG or TOO_SMALL_OR_LONG
   */
  SoSFFloat  maxLength;              



  /* Body representation */

  /**
   * Type of shape (no body, line, cylinder) used to draw the body. If bodyShape = 
   * NO_BODY, the body of each vector is invisible.
   */
  SoSFEnum   bodyShape;              

  /**
   * If bodyLengthType = CONSTANT_LENGTH, each vector has the same body 
   * length = bodyLengthFactor . If bodyLengthType = RELATIVE_LENGTH, the 
   * body length of a vector is bodyLengthFactor * vector-module.
   */
  SoSFEnum   bodyLengthType;         

  /**
   * Length (or length multiplicative factor) of the body shape.
   */
  SoSFFloat  bodyLengthFactor;       

  /**
   * Defines type of method to compute the cylinder's radius.
   * If bodyRadiusType = CONSTANT_RADIUS, each vector has the same body 
   * radius = bodyRadiusFactor . If bodyRadiusType = RELATIVE_RADIUS, the 
   * body radius of a vector is bodyRadiusFactor * vector-module. The body radius 
   * is either a line-width or a cylinder-radius depending on the field's value 
   * bodyShape.
   */
  SoSFEnum   bodyRadiusType;         

  /**
   * Radius (or radius multiplicative factor) of the cylinder.
   */
  SoSFFloat  bodyRadiusFactor;       

  /**
   * coloring method of the body.                            
   *
   * If bodyColoringType = CONSTANT_COLOR, each vector has the same body 
   * color, which is the last found during the scene graph traversal. 
   *
   * If bodyColoringType = MODULE_MAPPING_COLOR, the body's color of a 
   * vector depends on its module, and by using the current module-data-mapping (see 
   * PoMesh for explanation of the current module-data-mapping).
   *
   * If bodyColoringType = SCALAR_MAPPING_COLOR, the body's color of a 
   * vector depends on the scalar value at the mesh node used as the start point of 
   * the body. In this case, the current data-mapping is used to compute the color in 
   * relation to the scalar-value (see PoMesh for more explanations about the
   * current data-mapping).
   */
  SoSFEnum   bodyColoringType;       



  /* Start arrow representation */

  /**
   * Type of shape to be drawn at the start point of the body. If startArrowShape = 
   * NO_SHAPE, the start-shape of each vector is invisible.
   */
  SoSFEnum   startArrowShape;        

  /**
   * Defines the type of method to compute the arrow height.
   * If startArrowHeightType = CONSTANT_HEIGHT, each vector has the same 
   * start-shape height = startArrowHeightFactor . 
   * If startArrowHeightType = RELATIVE_ HEIGHT, the end-shape height of a 
   * vector is startArrowHeightFactor * body's length. 
   */
  SoSFEnum   startArrowHeightType;   

  /**
   * Height (or Height multiplicative factor) of the arrow shape.
   */
  SoSFFloat  startArrowHeightFactor; 

  /**
   * The start-arrow's radius is start-arrow's height * startArrowRadiusFactor
   */
  SoSFFloat  startArrowRadiusFactor; 

  /**
   * Coloring method of the start shape.
   *
   * If startArrowColoringType = CONSTANT_COLOR, each vector has the same 
   * start-arrow's color, which is the last found during the scene graph traversal. 
   *
   * If startArrowColoringType = MODULE_MAPPING_COLOR, the start-arrow's 
   * color of a vector depends on its module, and by using the current module-data-
   * mapping (see PoMesh for explanation of the current module-data-mapping).
   *
   * If startArrowColoringType = SCALAR_MAPPING_COLOR, the start-arrow's 
   * color of a vector depends on the scalar value at the mesh node used as the start 
   * point of the start-arrow. In this case, the current data-mapping is used to 
   * compute the color in relation to the scalar-value (see PoMesh for more 
   * explanations about the current data-mapping).
   */
  SoSFEnum   startArrowColoringType; 



  /* End arrow representation */

  /**
   * Type of shape to be drawn at the end point of the body. If endArrowShape = 
   * NO_SHAPE, the end-shape of each vector is invisible.
   */
  SoSFEnum   endArrowShape;        

  /**
   * Defines the type of method to compute the arrow height.
   * If endArrowHeightType = CONSTANT_HEIGHT, each vector has the same 
   * end-shape height = endArrowHeightFactor . 
   * If endArrowHeightType = RELATIVE_ HEIGHT, the end-shape height of a 
   * vector is endArrowHeightFactor * body's length. 
   */
  SoSFEnum   endArrowHeightType;   

  /**
   * Height (or Height multiplicative factor) of the arrow shape.
   */
  SoSFFloat  endArrowHeightFactor; 

  /**
   * The end-arrow's radius is end-arrow's height * endArrowRadiusFactor
   */
  SoSFFloat  endArrowRadiusFactor; 

  /**
   * Coloring method of the end shape.
   *
   * If endArrowColoringType = CONSTANT_COLOR, each vector has the same 
   * end-arrow's color, which is the last found during the scene graph traversal. 
   *
   * If endArrowColoringType = MODULE_MAPPING_COLOR, the end-arrow's 
   * color of a vector depends on its module, and by using the current module-data-
   * mapping (see PoMesh for explanation of the current module-data-mapping).
   *
   * If endArrowColoringType = SCALAR_MAPPING_COLOR, the end-arrow's 
   * color of a vector depends on the scalar value at the mesh node used as the end 
   * point of the end-arrow. In this case, the current data-mapping is used to 
   * compute the color in relation to the scalar-value (see PoMesh for more 
   * explanations about the current data-mapping).
   */
  SoSFEnum   endArrowColoringType; 

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

  void indexedMesh3DVec(PbIndexedMesh3D *mesh) ;
  void tetrahedronMesh3DVec(PbTetrahedronMesh3D *mesh) ;
  void hexahedronMesh3DVec(PbHexahedronMesh3D *mesh) ;
  void cartGrid3DVec(PbCartesianGrid3D *mesh) ;
  void paralCartGrid3DVec(PbParalCartesianGrid3D *mesh) ;
  void regularGrid3DVec(PbRegularCartesianGrid3D *mesh) ;

 protected:
  virtual ~PoMesh3DVec() ;  
  // Destructor

  // Methods
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void   setDefaultOnNonWritingFields();
  virtual void addElementsAllCaches() ;
  virtual void preRebuild();

  void addVector(const SbVec3f &orig, const SbVec3f &vec);
  void startVectorField();
  void finishVectorField();

  SoGroup *m_bodyGroupNode, *m_startArrowGroupNode, *m_endArrowGroupNode;

  PiArrow *m_arrow;
  const float *m_scalarDataSet;
  int m_vecIndexToDraw, m_vecIndex;

  int   m_allocVecPoints, m_allocModuleColr, m_allocScalarColr,
    m_allocModuleTransparencies, m_allocScalarTransparencies,
    m_numVecP, m_numVec;
  float (*m_vecPoints)[3];
  float (*m_moduleColr)[3];
  float (*m_scalarColr)[3];
  float *m_moduleTransparencies, *m_scalarTransparencies;

  /*----------------------------------------------------------------------------*/
 private:

  void drawVectorLine(int nod_index);

  void drawVectorLineScalarColr(int nod_index);
  void drawVectorLineScalarTranspColr(int nod_index);

  void drawVectorLineModuleColr(int nod_index);
  void drawVectorLineModuleTranspColr(int nod_index);

  void drawVectorLineScalarModuleColr(int nod_index);
  void drawVectorLineScalarModuleTranspColr(int nod_index);

  void drawVectorElaborated(int nod_index);

  void finishQuickVectorField();
  void finishElaboratedVectorField();
  void buildVectorFieldBodies();
  void buildVectorFieldStartArrow();
  void buildVectorFieldEndArrow();

  void (PoMesh3DVec::*drawVector)(int nod_index);
  void (PoMesh3DVec::*finishVectorFieldPtr)();

  // Sensors
  FieldSensorList m_fieldSensorList ;

  // List of fields defined in this class
  SoFieldList     m_fieldList ;

  SbVec3f m_arrowPoints[2];
  float   m_vecLength, m_arrowLength;

  ArrowColoringType m_bodyColoringType, m_startArrowColoringType, m_endArrowColoringType;
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_MESH3DVEC_ */



