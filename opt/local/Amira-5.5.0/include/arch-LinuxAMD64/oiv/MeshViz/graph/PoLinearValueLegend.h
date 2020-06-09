/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_LINEAR_VALUE_LEGEND_
#define  _PO_LINEAR_VALUE_LEGEND_

#include <MeshViz/graph/PoAutoValueLegend.h>

#include <Inventor/fields/SoSFEnum.h>
/**
 * @DTEXT  Class to build a linear auto value legend.
 * 
 * @ingroup GraphLegend
 * 
 * @DESCRIPTION
 *    Class to build a linear value legend. The space between boxes is null and their 
 *    width (or their height) is proportional to the difference between two consecutive 
 *    values. The legend is composed of one column (or one row depending on the 
 *    orientation of the legend).
 *    There are three possible representations:
 *    - The values displayed are calculated from a data mapping object or an 
 *    isovalue list object.
 *    - The values displayed are calculated as with a linear axis. They are linearly 
 *    distributed depending on the min and the max of the values of the data mapping 
 *    object or the isovalue list object.
 *    - Only the min and the max of the values of the data mapping object or the 
 *    isovalue list object are displayed.
 *    The fields #incrementType, #numberColumns, and #boxRatio are not used for this 
 *    representation.
 *
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoLinearValueLegend {
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
 *       @TR valueDistribution @TD ALL_VALUES
 *       @TR maxValueSize @TD 0.6
 *       @TR lowerUndefString @TD "UNDEF>"
 *       @TR upperUndefString @TD "UNDEF>"
 *       @TR lowerUpperBoxes @TD TRUE
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE polinearvaluelegend.cat.html
 * 
 * 
 */
class MESHVIZ_API PoLinearValueLegend : public PoAutoValueLegend {

  SO_KIT_HEADER(PoLinearValueLegend) ;


 public:

  /**
   *  Type of distribution of the values.
   */
  enum ValueDistribution {
    /**
     *  All the values of the legend are displayed.
     */
    ALL_VALUES,     
    /**
     *  The values of the legend are displayed like a linear axis.
     */
    LINEAR_VALUES,  
    /**
     *  Only the minimum and maximum of the values of the legend are displayed.
     */
    MIN_MAX_VALUES  
  } ;

  /* Fields */

  /**
   * Specifies the distribution of the values.
   */
  SoSFEnum  valueDistribution ;

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
  PoLinearValueLegend() ; 

  /**
   * Constructor.
   */
  PoLinearValueLegend(const SbVec2f &_start, const SbVec2f &_end, 
                      ValueDistribution distribution = ALL_VALUES) ;

  /**
   * Forces node kit rebuilding. See PoBase.
   */
  virtual void rebuild() ;

  /*----------------------------------------------------------------------------*/


 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  // Methods
  virtual void   setDefaultOnNonWritingFields() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  
  // Destructor
  virtual ~PoLinearValueLegend() ;

 private:
  // Init method
  void init(SbBool isDefault, ValueDistribution distribution = ALL_VALUES) ;

  // Sensors
  FieldSensorList m_fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     m_fieldList ;
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_LINEAR_VALUE_LEGEND_ */



