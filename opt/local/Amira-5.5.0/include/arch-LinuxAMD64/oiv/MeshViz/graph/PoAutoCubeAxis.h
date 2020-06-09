/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_AUTO_CUBE_AXIS_
#define  _PO_AUTO_CUBE_AXIS_

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFMatrix.h>

#include <MeshViz/graph/PoBaseAxis.h>
#include <MeshViz/graph/PbMiscTextAttr.h>

struct Pedge ;
class  PoCartesianAxis ;

/**
 * @DTEXT  Class to build a set of axes on a parallelepiped relating to the view.
 * 
 * @ingroup GraphAxis
 * 
 * @DESCRIPTION
 *    This class builds a set of 3D axes displayed on some of the 12 edges of a 
 *    parallelepiped. The choice of the edges depends on the view defined by the 
 *    current camera (see SoCamera class). The graduations and the title of the axes are 
 *    always legible whatever the view definition. The two points (start and end fields) 
 *    define the diagonal of the parallelepiped and only the edges which are intersecting 
 *    a visible face and an invisible face will be graduated. The visible and invisible 
 *    faces depend on the view definition. The visible faces of the parallelepiped are the 
 *    back faces.
 * <PRE>
 *                        1-----------2
 *        Y              /|  (2)     /|
 *        |            /  |        /  |
 *        |          /    | (5)  /    |   Vertices numerotation.
 *        |         6----------5      |
 *        ----- X   |     |    | (1)  |
 *       /          |(3)  0----|------3
 *      /           |    /     | (4) / 
 *     /            |  /       |   /   
 *    Z             |/ (0)     | /     
 *                  7----------4       
 * 
 *     Face 0 : 4 5 6 7 ==> edges : (4,5) (5,6) (6,7) (7,4)
 *     Face 1 : 2 3 4 5 ==> edges : (2,3) (3,4) (4,5) (5,2)
 *     Face 2 : 0 1 2 3 ==> edges : (0,1) (1,2) (2,3) (3,0)
 *     Face 3 : 0 1 6 7 ==> edges : (0,1) (1,6) (6,7) (7,0)
 *     Face 4 : 0 3 4 7 ==> edges : (0,3) (3,4) (4,7) (7,0)
 *     Face 5 : 1 2 5 6 ==> edges : (1,2) (2,5) (5,6) (6,1)
 * </PRE>
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoAutoCubeAxis {
 *    @TABLE_FILE_FORMAT
 *       @TR start @TD 0 0 0
 *       @TR end @TD 1 1 1
 *       @TR xTitle @TD ""
 *       @TR yTitle @TD ""
 *       @TR zTitle @TD ""
 *       @TR isGridLinesXVisible @TD FALSE
 *       @TR isGridLinesYVisible @TD FALSE
 *       @TR isGridLinesZVisible @TD FALSE
 *       @TR isBackgroundFacesVisible @TD FALSE
 *       @TR isIntersectingGradsVisible @TD FALSE
 *       @TR modellingMatrix @TD 1 0 0 0   0 1 0 0   0 0 1 0   0 0 0 1   
 *       @TR viewingMatrix @TD 1 0 0 0   0 1 0 0   0 0 1 0   0 0 0 1
 *       @TR projectionMatrix @TD 1 0 0 0   0 1 0 0   0 0 1 0   0 0 0 1
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE poautocubeaxis.cat.html
 * 
 * 
 */
class MESHVIZ_API PoAutoCubeAxis : public PoBaseAxis {
  SO_KIT_HEADER(PoAutoCubeAxis) ;

  /* Define fields for new parts */
  // Faces of the background
  SO_KIT_CATALOG_ENTRY_HEADER(backgroundFaceSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(backgroundFaceApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(backgroundFace) ;

  // Grid lines of main graduations
  SO_KIT_CATALOG_ENTRY_HEADER(mainGradGridSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(mainGradGridApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(mainGradGrid) ;

  // Grid lines of sub graduations
  SO_KIT_CATALOG_ENTRY_HEADER(subGradGridSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(subGradGridApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(subGradGrid) ;

  //--------------- X axes --------------------
  // X axis with vertices 0-3
  SO_KIT_CATALOG_ENTRY_HEADER(xAxisSwitch03) ;
  SO_KIT_CATALOG_ENTRY_HEADER(xAxis03) ;

  // X axis with vertices 1-2
  SO_KIT_CATALOG_ENTRY_HEADER(xAxisSwitch12) ;
  SO_KIT_CATALOG_ENTRY_HEADER(xAxis12) ;

  // X axis with vertices 6-5
  SO_KIT_CATALOG_ENTRY_HEADER(xAxisSwitch65) ;
  SO_KIT_CATALOG_ENTRY_HEADER(xAxis65) ;

  // X axis with vertices 7-4
  SO_KIT_CATALOG_ENTRY_HEADER(xAxisSwitch74) ;
  SO_KIT_CATALOG_ENTRY_HEADER(xAxis74) ;

  //--------------- Y axes --------------------
  // Y axis with vertices 0-1
  SO_KIT_CATALOG_ENTRY_HEADER(yAxisSwitch01) ;
  SO_KIT_CATALOG_ENTRY_HEADER(yAxis01) ;

  // Y axis with vertices 7-6
  SO_KIT_CATALOG_ENTRY_HEADER(yAxisSwitch76) ;
  SO_KIT_CATALOG_ENTRY_HEADER(yAxis76) ;

  // Y axis with vertices 4-5
  SO_KIT_CATALOG_ENTRY_HEADER(yAxisSwitch45) ;
  SO_KIT_CATALOG_ENTRY_HEADER(yAxis45) ;

  // Y axis with vertices 3-2
  SO_KIT_CATALOG_ENTRY_HEADER(yAxisSwitch32) ;
  SO_KIT_CATALOG_ENTRY_HEADER(yAxis32) ;

  //--------------- Z axes --------------------
  // Z axis with vertices 0-7
  SO_KIT_CATALOG_ENTRY_HEADER(zAxisSwitch07) ;
  SO_KIT_CATALOG_ENTRY_HEADER(zAxis07) ;

  // Z axis with vertices 3-4
  SO_KIT_CATALOG_ENTRY_HEADER(zAxisSwitch34) ;
  SO_KIT_CATALOG_ENTRY_HEADER(zAxis34) ;

  // Z axis with vertices 2-5
  SO_KIT_CATALOG_ENTRY_HEADER(zAxisSwitch25) ;
  SO_KIT_CATALOG_ENTRY_HEADER(zAxis25) ;

  // Z axis with vertices 1-6
  SO_KIT_CATALOG_ENTRY_HEADER(zAxisSwitch16) ;
  SO_KIT_CATALOG_ENTRY_HEADER(zAxis16) ;


 public:

  /**
   *  Type of axes on the parallelepiped edges.
   */
  enum AxisType {
    /**
     *  Linear axis.
     */
    LINEAR,      
    /**
     *  Logarithmic axis.
     */
    LOGARITHMIC, 
    /**
     *  Generalized axes.
     */
    GENERALIZED  
  } ;

  /* Fields */

  /**
   * Start point of the parallelepiped's diagonal. (0,0,0) by default.
   */
  SoSFVec3f   start ;  

  /**
   * End point of the parallelepiped's diagonal. (1,1,1) by default.
   */
  SoSFVec3f   end   ;  



  /**
   * Title of the X axes. Empty by default.
   */
  SoSFString  xTitle ; 

  /**
   * Title of the Y axes. Empty by default.
   */
  SoSFString  yTitle ; 

  /**
   * Title of the Z axes. Empty by default.
   */
  SoSFString  zTitle ; 



  /**
   * Sets the visibility of the grid lines of the X axes displayed on the 
   * visible faces. (The attributes of grid lines of PoAxis cannot be used because 
   * the graduations of thes axes are not necessarily in the same plane than the 
   * visible faces). FALSE by default.
   */
  SoSFBool    isGridLinesXVisible ; 

  /**
   * Sets the visibility of the grid lines of the Y axes displayed on the 
   * visible faces. (The attributes of grid lines of PoAxis cannot be used because 
   * the graduations of thes axes are not necessarily in the same plane than the 
   * visible faces). FALSE by default.
   */
  SoSFBool    isGridLinesYVisible ; 

  /**
   * Sets the visibility of the grid lines of the Z axes displayed on the 
   * visible faces. (The attributes of grid lines of PoAxis cannot be used because 
   * the graduations of thes axes are not necessarily in the same plane than the 
   * visible faces). FALSE by default.
   */
  SoSFBool    isGridLinesZVisible ; 

  /**
   * Sets the visibility of visible faces. FALSE by default.
   */
  SoSFBool    isBackgroundFacesVisible ;

  /**
   * Given A1 and A2 2 consecutive axes with the first (the last) graduation of A1 
   * intersects the first or the last graduation of A2. This flag allows the application 
   * to suppress or not the first (the last) graduation  of A1.
   * The attribute tickFirstGrad (tickLastGrad) of PoAxis is used to suppress the 
   * first (the last) graduation. FALSE by default.
   */
  SoSFBool    isIntersectingGradsVisible ;

  /**
   * This modelling matrix is used to determine the visibility of each face (and thus the 
   * axes to draw). Each time an SoGLRenderAction, an SoCallbackAction, an 
   * SoRayPickAction or an SoVectorizeAction traverse this node, this matrix
   * is set to the current modelling matrix and the axes are rebuilt. 
   */
  SoSFMatrix  modellingMatrix  ;

  /**
   * This viewing matrix is used to determine the visibility of each face (and thus the 
   * axes to draw). Each time an SoGLRenderAction, an SoCallbackAction, an 
   * SoRayPickAction or an SoVectorizeAction traverse this node, this matrix
   * is set to the current viewing matrix and the axes are rebuilt. 
   * viewingMatrix depends on the current camera.
   */
  SoSFMatrix  viewingMatrix    ;

  /**
   * This modelling matrix is used to determine the visibility of each face (and thus the 
   * axes to draw). Each time an SoGLRenderAction, an SoCallbackAction, an 
   * SoRayPickAction or an SoVectorizeAction traverse this node, this matrix
   * is set to the current projection matrix and the axes are rebuilt. 
   * projectionMatrix depends on the current camera.
   */
  SoSFMatrix  projectionMatrix ;



  /* Methods */

  /**
   * Default constructor.
   */
  PoAutoCubeAxis() ;

  /**
   * Constructor. (By default the X, Y, and Z axes are linear).
   */
  PoAutoCubeAxis(const SbVec3f &_start, const SbVec3f &_end, AxisType xAxisType,
                 AxisType yAxisType, AxisType zAxisType, const char *xTtle = NULL, 
                 const char *yTtle = NULL, const char *zTtle = NULL) ;

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void GLRender( SoGLRenderAction *action );
  virtual void rebuild() ;


 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  virtual ~PoAutoCubeAxis() ;
  // Destructor

  // Methods
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void   setDefaultOnNonWritingFields() ;
  
 private:  
  // Init method
  void init(SbBool isDefault, const SbVec3f &_start, const SbVec3f &_end, 
            AxisType xAxisType, AxisType yAxisType, AxisType zAxisType, 
            const char *xTtle, const char *yTtle, const char *zTtle) ;

  // Compute the 8 vertices of the parallelepiped from the points start and end
  void computeParalVertices() ;

  // Compute the 6 normal of each face of the parallelepiped
  void computeParalFaceNormals() ;

  // Sets all attributes for the axis to build from to the edge it comes from 
  // and the coordinates of this edge (m_paralVertices)
  void buildAxis(const Pedge *edge, PoCartesianAxis *axis) ;

  // Draw all backgroud faces
  void drawBackgroundFaces() ;

  // Eliminate intersecting graduations
  void eliminateIntersectingGrads(const int *indexVisibleEdges, int nbVisibleEdges,
                                  PoCartesianAxis *axis[12]) ;

  // Draw grid lines for main and sub graduations
  void drawGridLines(PoCartesianAxis *axis[12]) ;

  // Reset all parts
  void resetAllParts() ;

  // Rebuild auto cube axis without taking into account
  // matrix transform
  void rebuildWithoutMatrix() ;

  // This method catch all actions on this nodekit
  // and if the nodekit is not update or modelling, viewing,
  // or projection matrix have changed then it rebuild the nodekit.
  static void catchActionCB(void *data, SoAction *action) ;

  // The 8 vertices of the parallelepiped
  SbVec3d m_paralVertices[8] ;

  // Indicate if the auto cube axis box must be rebuild
  // in function of matrix (modelling, viewing, projection) or
  // not (use for all action which not store modelling, viewing or
  // projection matrix.
  SbBool m_rebuildWithoutMatrix ;
          
  // Indicate if it the first instance of this class
  static SbBool m_firstInstance ;
  
  SoSFEnum xAxisType, yAxisType, zAxisType ;

  // Sensors
  FieldSensorList m_fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     m_fieldList ;
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_AUTO_CUBE_AXIS_  */

