/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_CURVE_LINE_
#define  _PO_CURVE_LINE_

#include <MeshViz/graph/PoChart.h>

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFFloat.h>

/**
 * @DTEXT  Class to build a 2D line curve.
 * 
 * @ingroup GraphCurves
 * 
 * @DESCRIPTION
 *    Builds a 2D curve line on 1D mesh (PoIrregularMesh1D or PoRegularMesh1D).
 *    The abscissas of the curve are given by the geometry of the current mesh 1D,
 *    and the ordinates are given by one of the value-set of the current mesh 1D 
 *    specified by the field yValuesIndex.
 *    The thickness of the line is specified by the field thicknessIndex which is
 *    an index of a value-set of the current mesh 1D. If thicknessIndex == -1, 
 *    the thickness of the curve is inherited.
 *    This class also takes into account of the current mesh 1D hints (PoMesh1DHints).
 *    The interpretation of colorBinding is the following :
 * 
 *    - INHERITED: The entire curve is colored with the same inherited color.
 * 
 *    - PER_PART : Each part of the curve is colored with the same color.
 *    A part is the line(s) between two abscissas defined by the current mesh 1D.
 * 
 *    - PER_VERTEX: A color is used at each vertex of the curve.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoCurveLine {
 *    @TABLE_FILE_FORMAT
 *       @TR colorBinding @TD INHERITED
 *       @TR yValuesIndex @TD 0
 *       @TR colorValuesIndex @TD 1
 *       @TR material @TD NULL
 *       @TR thicknessIndex @TD -1
 *       @TR thicknessBinding @TD PER_VERTEX_THICKNESS
 *       @TR thicknessFactor @TD 1.0
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pocurveline.cat.html
 * 
 * 
 */

class MESHVIZ_API PoCurveLine : public PoChart {
  
  SO_KIT_HEADER(PoCurveLine) ;

  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(curve) ;


 public:

  /**
   *  Thickness binding.
   */
  enum ThicknessBinding {
    /**
     *  Each part of the curve has the same thickness.
     */
    PER_PART_THICKNESS,   
    /**
     *  The thickness between two consecutive vertices
     */
    PER_VERTEX_THICKNESS  
    /**
     *  is linearly interpolated according to the thickness 
     */
                          
    /**
     *  value associated to these vertices.
     */
                          
  } ;



  /* Fields */

  /**
   * Defines the index of the set of values used to specify the thickness.
   * If thicknessIndex = -1, all the curve has the same thickness which is
   * the inherited line width.
   */
  SoSFInt32 thicknessIndex ;

  /**
   * Defines how thickness values are bound to the curve.
   * If thicknessBinding = PER_PART_THICKNESS, each part of 
   * the curve has the same thickness otherwise the thickness between 
   * two consecutive vertices is linearly interpolated according to the 
   * thickness value associated to these vertices.
   * For curve line, PER_VERTEX_THICKNESS is interpreted as PER_PART_THICKNESS.
   */
  SoSFEnum  thicknessBinding ;

  /**
   * Defines a multiplicative factor applied to the thickness values.
   */
  SoSFFloat thicknessFactor ;

  /**
   * Constructor.
   */
  PoCurveLine() ;

  /*----------------------------------------------------------------------------*/


 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  virtual ~PoCurveLine() ;
  // Destructor.

  // Overloaded methods
  virtual void rebuild() ;
  virtual void addElementsAllCaches() ;
  virtual void preRebuild() ;

  // Methods
  virtual void   setDefaultOnNonWritingFields() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;

  // Computes from the curve given by the parameter x, y and size, and from
  // indices of the source points of the curve, the sums of distances between
  // 2 consecutive sources points and the distances between 2 points.
  void computeCurveDistances(const float *x, const float *y, int size,
                             const int *indexSource, float* &curveDist,
                             float* &sumDist) ;
 private:  
  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;
} ;

/*----------------------------------------------------------------------------*/

#endif /*  _PO_CURVE_LINE_ */

