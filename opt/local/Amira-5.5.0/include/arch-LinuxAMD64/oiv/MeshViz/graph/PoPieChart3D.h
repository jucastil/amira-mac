/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_PIE_CHART_3D_
#define  _PO_PIE_CHART_3D_

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFFloat.h>

#include <MeshViz/graph/PoPieChart.h>

/**
 * @DTEXT  Class for 3D pie chart representation.
 * 
 * @ingroup GraphPie
 * 
 * @DESCRIPTION
 *    Class to build a 2D pie chart in the plane XY. 
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoPieChart3D {
 *    @TABLE_FILE_FORMAT
 *       @TR radius @TD 1
 *       @TR sliceText @TD ""
 *       @TR sliceValue @TD 0.0
 *       @TR sliceColor @TD 0.0 0.0 0.0
 *       @TR intAnnotPosition @TD HOR_INT_POS
 *       @TR intAnnotAlignment @TD CENTER_ALIGN
 *       @TR intAnnotTextVisibility @TD FALSE
 *       @TR intAnnotValueVisibility @TD TRUE
 *       @TR intAnnotPercentVisibility @TD FALSE
 *       @TR intAnnotAddStringVisibility @TD FALSE
 *       @TR intAnnotTextFontName @TD ""
 *       @TR intAnnotTextFontSize @TD 0.0
 *       @TR intAnnotValueFontName @TD ""
 *       @TR intAnnotValueFontSize @TD 0.0
 *       @TR intAnnotPercentFontName @TD ""
 *       @TR intAnnotPercentFontSize @TD 0.0
 *       @TR intAnnotAddString @TD ""
 *       @TR intAnnotDistance @TD 0.0
 *       @TR extAnnotPosition @TD HOR_EXT_POS
 *       @TR extAnnotAlignment @TD INWARDS_ALIGN
 *       @TR extAnnotTextVisibility @TD TRUE
 *       @TR extAnnotValueVisibility @TD FALSE
 *       @TR extAnnotPercentVisibility @TD FALSE
 *       @TR extAnnotAddStringVisibility @TD FALSE
 *       @TR extAnnotTextFontName @TD ""
 *       @TR extAnnotTextFontSize @TD 0.0
 *       @TR extAnnotValueFontName @TD ""
 *       @TR extAnnotValueFontSize @TD 0.0
 *       @TR extAnnotPercentFontName @TD ""
 *       @TR extAnnotPercentFontSize @TD 0.0
 *       @TR extAnnotAddString @TD ""
 *       @TR extAnnotDistance1 @TD 0.0
 *       @TR extAnnotDistance2 @TD 0.0
 *       @TR extAnnotDistance3 @TD 0.0
 *       @TR arrowVisibility @TD TRUE
 *       @TR arrowHeight @TD 0.0
 *       @TR arrowWidth @TD 0.0
 *       @TR sliceGroupActive @TD TRUE
 *       @TR sliceGroupMinValue @TD 5.0
 *       @TR sliceGroupFlagMin @TD PERCENTAGE
 *       @TR sliceGroupString @TD "Others"
 *       @TR sliceToTranslateNumber @TD 0
 *       @TR sliceToTranslateValue @TD 0.0
 *       @TR sliceAngleStep @TD PI/90
 *       @TR center @TD 0.0 0.0
 *       @TR zCenter2 @TD 1.0
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE popiechart3d.cat.html
 * 
 * 
 */
class MESHVIZ_API PoPieChart3D : public PoPieChart {
  SO_KIT_HEADER(PoPieChart3D) ;


 public:

  /* Fields */

  /**
   * Coordinates of the center of the circle forming the first face of the pie chart.
   */
  SoSFVec3f center   ;

  /**
   * Z coordinate of the center of the circle forming the second face of the pie chart.
   */
  SoSFFloat zCenter2 ;



  /* Methods */

  /**
   * Default constructor.
   */
  PoPieChart3D();

  /**
   * Constructor.
   * [OIV-WRAPPER-ARG IN,IN,IN,CAST_TO{short}&NO_WRAP{sliceValues->Length},ARRAY,ARRAY,NO_WRAP{sliceColors->Length},ARRAY]
   */
  PoPieChart3D(const SbVec3f &_center, float _zCenter2, float _radius, short numSlices,
               const char **sliceTexts, const float *sliceValues, int numSliceColors,
               const SbColor *sliceColors) ;

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void rebuild() ;

  /*----------------------------------------------------------------------------*/


 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  // Methods
  // Destructor
  virtual ~PoPieChart3D() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void   setDefaultOnNonWritingFields() ;

 private:

  // Init
  void init(SbBool isDefault, const SbVec3f &_center, float _zCenter2) ;

  // Sensors
  FieldSensorList m_fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     m_fieldList ;

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_PIE_CHART_3D_  */

