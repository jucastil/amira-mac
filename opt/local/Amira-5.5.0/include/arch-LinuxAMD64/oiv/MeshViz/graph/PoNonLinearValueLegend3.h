/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_NON_LINEAR_VALUE_LEGEND3_
#define  _PO_NON_LINEAR_VALUE_LEGEND3_

#include <MeshViz/graph/PoAutoValueLegend.h>

/**
 * @DTEXT  Class to build a non linear legend (third representation).
 * 
 * @ingroup GraphLegend
 * 
 * @DESCRIPTION
 *    Each box represents the color associated with a value of a data mapping 
 *    object or an isovalue list object, so the representation is similar to the 
 *    representation of PoNonLinearValueLegend2 but the spacing between boxes is 
 *    null, and the legend consists of one column (or one row depending on 
 *    the orientation of the legend).
 *    
 *    The fields #incrementType, #numberColumns, and #boxRatio are not used for this 
 *    representation.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoNonLinearValueLegend3 {
 *    @TABLE_FILE_FORMAT
 *       @TR titleVisibility @TD VISIBILITY_OFF
 *       @TR titlePosition @TD POS_BOTTOM
 *       @TR titlePath @TD RIGHT_PATH
 *       @TR titleFontSize @TD 0
 *       @TR titleFontName @TD ""
 *       @TR titleString @TD ""
 *       @TR valueVisibility @TD VISIBILITY_ON
 *       @TR valuePosition @TD POS_RIGHT
 *       @TR valueFontName @TD ""
 *       @TR valueAddStringVisibility @TD FALSE
 *       @TR valueAddString @TD ""
 *       @TR marginType @TD REL_MARGIN
 *       @TR marginLeft @TD 0.05
 *       @TR marginRight @TD 0.05
 *       @TR marginBottom @TD 0.05
 *       @TR marginTop @TD 0.05
 *       @TR incrementType @TD VERTICAL_INCREMENT
 *       @TR numColumns @TD 1
 *       @TR boxRatio @TD 1
 *       @TR periodValue @TD 1
 *       @TR firstValue @TD 1
 *       @TR lastValue @TD 32767
 *       @TR start @TD 0 0
 *       @TR end @TD 1 1
 *       @TR maxValueSize @TD 0.6
 *       @TR lowerUndefString @TD "UNDEF>"
 *       @TR upperUndefString @TD "UNDEF>"
 *       @TR lowerUpperBoxes @TD TRUE
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pononlinearvaluelegend3.cat.html
 * 
 * 
 */
class MESHVIZ_API PoNonLinearValueLegend3 : public PoAutoValueLegend {

  SO_KIT_HEADER(PoNonLinearValueLegend3) ;


 public:

  

  /* Fields */

  /**
   * Indicates the maximum size of text values.
   * If the legend is vertical, this value is the maximum percentage 
   * of the width of text values relative to the legend width (without margin).
   * If the legend is horizontal, this value is the maximum percentage 
   * of the height of text values relative to the legend height (without margin).
   */
  SoSFFloat maxValueSize ;

  /**
   * Indicates if lower and upper boxes should be displayed.
   * The color of the lower box is the color associated with values less
   * than the minimum, and the color of the upper box is the color associated
   * with values greater than the maximum.
   * 
   * @FIELD_SINCE_OIV 6.0 
   */
  SoSFBool  lowerUpperBoxes ;

  /* Methods */

  /**
   * Default constructor.
   */
  PoNonLinearValueLegend3() ; 

  /**
   * Constructor.
   */
  PoNonLinearValueLegend3(const SbVec2f &_start, const SbVec2f &_end) ;

  /**
   * Forces node kit rebuilding. See PoBase.
   */
  virtual void rebuild() ;

  /*----------------------------------------------------------------------------*/


 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected: 
  // Destructor
  virtual ~PoNonLinearValueLegend3() ;

  // Methods
  virtual void   setDefaultOnNonWritingFields() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;

 private:
  // Init method
  void init() ;

    
  // Sensors
  FieldSensorList m_fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     m_fieldList ;

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_NON_LINEAR_VALUE_LEGEND3_ */



