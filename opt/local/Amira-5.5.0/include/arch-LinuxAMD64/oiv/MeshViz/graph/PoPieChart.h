/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_PIE_CHART_
#define  _PO_PIE_CHART_

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoMFShort.h>
#include <Inventor/fields/SoMFColor.h>

#include <MeshViz/graph/PoGraphMaster.h>
#include <MeshViz/graph/PbMiscTextAttr.h>
#include <MeshViz/graph/PbNumericDisplayFormat.h>

class PiText ;

/**
 * @DTEXT  Abstract class for pie chart representation.
 * 
 * @ingroup GraphPie
 * 
 * @DESCRIPTION
 *    Abstract class for all pie chart representations. This class handles all pie chart 
 *    attributes. A pie chart represents the relative size of one datum in relation to a set 
 *    of data. Each datum is given by a numerical value which is expressed as a 
 *    percentage of the sum of the values of the entire set of data. This percentage is 
 *    used to calculate the angle of the slice representing the datum. All slices together 
 *    make up a pie chart.
 * 
 *    The slices of which the value is small can be regroup in a same slice. 
 *    This slice is called the grouping slice.
 * 
 *    There are 2 types of pie chart annotations. Internal annotations and 
 *    external annotations. Futhermore annotations can be framed by a box.
 *    All annotations are draw with the Z-Buffer desactivated, that is, they
 *    are always visible.
 * 
 *    There are 5 groups of fields attributes
 *      - Geometric and data of the pie chart.
 *         - radius
 *         - sliceText
 *         - sliceValue
 *         - sliceColor
 *         - sliceAngleStep
 *
 *      - Attribute of internal annotations : annotations drawn inside each slices.
 *         - intAnnotPosition
 *         - intAnnotAlignment
 *         - intAnnotTextVisibility
 *         - intAnnotValueVisibility
 *         - intAnnotPercentVisibility
 *         - intAnnotAddStringVisibility
 *         - intAnnotTextFontName
 *         - intAnnotTextFontSize
 *         - intAnnotValueFontName
 *         - intAnnotValueFontSize
 *         - intAnnotPercentFontName
 *         - intAnnotPercentFontSize
 *         - intAnnotAddString
 *         - intAnnotDistance
 *
 *      - Attribute of external annotations : annotations drawn outside each slices.
 *         - extAnnotPosition
 *         - extAnnotAlignment
 *         - extAnnotTextVisibility
 *         - extAnnotValueVisibility
 *         - extAnnotPercentVisibility
 *         - extAnnotAddStringVisibility
 *         - extAnnotTextFontName
 *         - extAnnotTextFontSize
 *         - extAnnotValueFontName
 *         - extAnnotValueFontSize
 *         - extAnnotPercentFontName
 *         - extAnnotPercentFontSize
 *         - extAnnotAddString
 *         - extAnnotDistance1
 *         - extAnnotDistance2
 *         - extAnnotDistance3
 *
 *      - Attribute of arrows : an arrow is drawn between slices and each 
 *        external annotations.
 *         - arrowVisibility
 *         - arrowHeight
 *         - arrowWidth
 *
 *      - Attribute for the translation of slices. 
 *         - sliceToTranslateNumber
 *         - sliceToTranslateValue
 *
 *      - Attribute of the grouping slice : The slices of which the value is 
 *        small can be regroup in a same slice, call grouping slice.
 *         - sliceGroupActive
 *         - sliceGroupMinValue
 *         - sliceGroupFlagMin
 *         - sliceGroupString
 *
 * )
 * 
 *    All pie chart texts depend on the current miscellaneous text attributes which 
 *    define the font name, line length and so on. If the method setMiscTextAttr(textAttr)
 *    is called, the current miscellaneous text attributes is "textAttr". Otherwise
 *    the current miscellaneous text attributes are specified in the current 
 *    inherited state (cf property node PoMiscTextAttr).
 * 
 *    All pie chart numerical values depend on the current numerical display format.
 *    If the method setFormat(format) is called, the current numerical display format 
 *    is "format". Otherwise the current numerical display format is specified in 
 *    the current inherited state (cf property node PoNumericDisplayFormat).
 * 
 */

class MESHVIZ_API PoPieChart : public PoGraphMaster {
  SO_KIT_HEADER(PoPieChart) ;

  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(sliceSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(sliceApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(slice) ;

  SO_KIT_CATALOG_ENTRY_HEADER(sliceBorderSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(sliceBorderApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(sliceBorder) ;

  SO_KIT_CATALOG_ENTRY_HEADER(extAnnotBoxSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(extAnnotBoxApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(extAnnotBox) ;

  SO_KIT_CATALOG_ENTRY_HEADER(extAnnotBoxBorderSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(extAnnotBoxBorderApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(extAnnotBoxBorder) ;

  SO_KIT_CATALOG_ENTRY_HEADER(extAnnotTextSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(extAnnotTextApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(extAnnotText) ;

  SO_KIT_CATALOG_ENTRY_HEADER(extAnnotValueSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(extAnnotValueApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(extAnnotValue) ;

  SO_KIT_CATALOG_ENTRY_HEADER(extAnnotPercentSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(extAnnotPercentApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(extAnnotPercent) ;

  SO_KIT_CATALOG_ENTRY_HEADER(arrowSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(arrowApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(arrow) ;

  SO_KIT_CATALOG_ENTRY_HEADER(intAnnotBoxSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(intAnnotBoxApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(intAnnotBox) ;

  SO_KIT_CATALOG_ENTRY_HEADER(intAnnotBoxBorderSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(intAnnotBoxBorderApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(intAnnotBoxBorder) ;

  SO_KIT_CATALOG_ENTRY_HEADER(intAnnotTextSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(intAnnotTextApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(intAnnotText) ;

  SO_KIT_CATALOG_ENTRY_HEADER(intAnnotValueSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(intAnnotValueApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(intAnnotValue) ;

  SO_KIT_CATALOG_ENTRY_HEADER(intAnnotPercentSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(intAnnotPercentApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(intAnnotPercent) ;


 public:

  /**
   *  Type of internal annotation position.
   */
  enum IntAnnotPosition {
    /**
     *  Interior annotations are radial to the slices.
     */
    RADIAL_INT_POS, 
    /**
     *  Interior annotations are horizontal.
     */
    HOR_INT_POS     
  } ;

  /**
   *  Type of external annotation position.
   */
  enum ExtAnnotPosition {
    /**
     *  Exterior annotations are radial to the slices.
     */
    RADIAL_EXT_POS,         
    /**
     *  Exterior annotations are horizontal.
     */
    HOR_EXT_POS,            
    /**
     *  Exterior annotations are horizontally aligned.
     */
    HOR_ALIGNED_EXT_POS,    
    /**
     *  Exterior annotations are vertically aligned.
     */
    VERT_ALIGNED_EXT_POS,   
    /**
     *  Exterior annotations are aligned on a square.
     */
    SQUARE_ALIGNED_EXT_POS  
  } ;

  /**
   *  Type of annotation alignment.
   */
  enum Alignment {
    /**
     *  Annotations are aligned on the left of the annotation box.
     */
    LEFT_ALIGN,        
    /**
     *  Annotations are aligned on the center of the annotation box.
     */
    CENTER_ALIGN,      
    /**
     *  Annotations are aligned on the right of the annotation box.
     */
    RIGHT_ALIGN,       
    /**
     *  Annotations are aligned inward the pie chart.
     */
    INWARDS_ALIGN,     
    /**
     *  Annotations are aligned outward the pie chart.
     */
    OUTWARDS_ALIGN     
  } ;

#ifdef ABSOLUTE

#undef ABSOLUTE

#endif



  /**
   *  Type of threshold for the grouping slice.
   */
  enum PercentStatus {
    ABSOLUTE,
    PERCENTAGE
  } ;





  /* Fields */

  /**
   * Radius of the pie chart.
   */
  SoSFFloat  radius ;



  /* Slice attributes */

  /**
   * Text associated to each slice of the pie chart.
   * Take care that sliceText.getNum() is equal to sliceValue.getNum(), otherwise 
   * the number of slices of the pie chart is the minimun of sliceText.getNum() and 
   * sliceValue.getNum().
   */
  SoMFString sliceText  ;

  /**
   * Value associated to each slice of  the pie chart. 
   * Take care that sliceText.getNum() is equal to sliceValue.getNum(), otherwise 
   * the number of slices of the pie chart is the minimun of sliceText.getNum() and 
   * sliceValue.getNum().
   */
  SoMFFloat  sliceValue ;

  /**
   * Color associated to each slice of the pie chart. If 
   * sliceColor.getNum() < sliceText.getNum(), then the 
   * interpretation of sliceColor is cyclical.
   */
  SoMFColor  sliceColor ;



  /* Internal annotation attributes */

  /**
   * Interior annotation position.
   */
  SoSFEnum   intAnnotPosition            ;

  /**
   * Interior annotation alignment.
   */
  SoSFEnum   intAnnotAlignment           ;

  /**
   * Interior text visibility (texts of sliceText field).
   */
  SoSFBool   intAnnotTextVisibility      ;

  /**
   * Interior value visibility (values of sliceValue field).
   */
  SoSFBool   intAnnotValueVisibility     ;

  /**
   * Interior percent visibility (percent are 
   * computed from sliceValue field)
   */
  SoSFBool   intAnnotPercentVisibility   ;

  /**
   * Specify the visibility of a string concatenated 
   * with the interior values (if they are visible).
   */
  SoSFBool   intAnnotAddStringVisibility ;

  /**
   * String concatened with interior values.
   */
  SoSFString intAnnotAddString           ;

  /**
   * Interior text (texts of sliceText field) font 
   * name. If the font is equal to its default value, 
   * the font used is the font of
   * the current miscellaneous text attributes.
   */
  SoSFString intAnnotTextFontName        ;

  /**
   * Font size of interior texts (texts of sliceText 
   * field). If this value is less or equal to 0, the 
   * font size is fixed at 0.025. This value is a 
   * percentage of the current domain (cf PoBase description).
   */
  SoSFFloat  intAnnotTextFontSize        ;

  /**
   * Interior value (values of sliceValue field) 
   * font name. If the font is equal to its default 
   * value, the font used is the font of
   * the current miscellaneous text attributes.
   */
  SoSFString intAnnotValueFontName       ;

  /**
   * Font size of interior values (values of 
   * sliceValue field). If this value is less or equal 
   * to 0, the font size is fixed at 0.025. This value 
   * is a percentage of the current domain (cf PoBase description).
   */
  SoSFFloat  intAnnotValueFontSize       ;

  /**
   * Interior percentage font name. If the font is 
   * equal to its default value, the font used is the 
   * font of the current miscellaneous text attributes.
   */
  SoSFString intAnnotPercentFontName     ;

  /**
   * Font size of interior percentages. If this value 
   * is less or equal to 0, the font size is fixed at 
   * 0.025. This value is a percentage of the current 
   * domain (cf PoBase description).
   */
  SoSFFloat  intAnnotPercentFontSize     ;

  /**
   * Distance from the pie chart center to the 
   * interior annotation box center. If this value is less or 
   * equal to 0, the distance is fixed to 2/3 of the 
   * radius.
   */
  SoSFFloat  intAnnotDistance            ;



  /* External annotation attributes */

  /**
   * Exterior annotation position.
   */
  SoSFEnum   extAnnotPosition            ;

  /**
   * Exterior annotation alignment.
   */
  SoSFEnum   extAnnotAlignment           ;

  /**
   * Exterior text visibility (texts of sliceText field).
   */
  SoSFBool   extAnnotTextVisibility      ;

  /**
   * Exterior value visibility (values of sliceValue field).
   */
  SoSFBool   extAnnotValueVisibility     ;

  /**
   * Exterior percent visibility (percent are computed from sliceValue field)
   */
  SoSFBool   extAnnotPercentVisibility   ;

  /**
   * Specify the visibility of a string concatenated 
   * with the exterior values (if they are visible).
   */
  SoSFBool   extAnnotAddStringVisibility ;

  /**
   * String concatened with exterior values.
   */
  SoSFString extAnnotAddString           ;

  /**
   * Exterior text (texts of sliceText field) font 
   * name. If the font is equal to its default value, 
   * the font used is the font of
   * the current miscellaneous text attributes.
   */
  SoSFString extAnnotTextFontName        ;

  /**
   * Font size of exterior texts (texts of sliceText 
   * field). If this value is less or equal to 0, the 
   * font size is fixed at 0.025. This value is a 
   * percentage of the current domain (cf PoBase description).
   */
  SoSFFloat  extAnnotTextFontSize        ;

  /**
   * Exterior value (values of sliceValue field) 
   * font name. If the font is equal to its default 
   * value, the font used is the font of
   * the current miscellaneous text attributes.
   */
  SoSFString extAnnotValueFontName       ;

  /**
   * Font size of exterior values (values of 
   * sliceValue field). If this value is less or equal 
   * to 0, the font size is fixed at 0.025. This value 
   * is a percentage of the current domain (cf PoBase description).
   */
  SoSFFloat  extAnnotValueFontSize       ;

  /**
   * Exterior percentage font name. If the font is 
   * equal to its default value, the font used is the 
   * font of the current miscellaneous text attributes.
   */
  SoSFString extAnnotPercentFontName     ;

  /**
   * Font size of exterior percentages. If this 
   * value is less or equal to 0, the font size is 
   * fixed at 0.025. This value is a percentage of 
   * the current domain (cf PoBase description).
   */
  SoSFFloat  extAnnotPercentFontSize     ;

  /**
   * Distance from the pie chart center to the end 
   * of the arrow. If this value is less or equal to 
   * 0, the distance is fixed to 21/20 of the radius.
   */
  SoSFFloat  extAnnotDistance1           ;

  /**
   * Distance from the end of the arrow to the 
   * middle of the arrow. If this value is less or 
   * equal to 0, the distance is fixed to 1/10 of the 
   * radius.
   */
  SoSFFloat  extAnnotDistance2           ;

  /**
   * Distance from the middle of the arrow to the 
   * start of the arrow. If this value is less or 
   * equal to 0, the distance is fixed to 1/5 of the 
   * radius.
   */
  SoSFFloat  extAnnotDistance3           ;



  /* Arrow attributes */

  /**
   * Visibility of the arrow.
   */
  SoSFBool   arrowVisibility ;

  /**
   * Height of the arrow.
   */
  SoSFFloat  arrowHeight     ;

  /**
   * Width of the arrow.
   */
  SoSFFloat  arrowWidth      ;



  /* Small value regrouping attributes */

  /**
   * Activate or Deactivate the regrouping of small 
   * values.
   */
  SoSFBool   sliceGroupActive   ; 

  /**
   * Threshold underneath the slice are regrouped.
   */
  SoSFFloat  sliceGroupMinValue ;

  /**
   * Indicate if the value sliceGroupMinValue is 
   * interpreted as percentage (PERCENTAGE) or not (ABSOLUTE).
   */
  SoSFEnum   sliceGroupFlagMin  ;

  /**
   * String for the regrouping slice.
   */
  SoSFString sliceGroupString   ;



  /* Slices to translate attributes */

  /**
   * Numbers (slice numbers begin at 0) of the slices to translate.
   * sliceToTranslateNumber[i] is the number of the i-th slice to translate.
   * If sliceToTranslateNumber[i] is less than zero, it corresponds to the slice of 
   * regrouping small values.
   */
  SoMFShort sliceToTranslateNumber ;

  /**
   * Translation values along the bisectors of the slices.
   * sliceToTranslateValue[i] is the translate value along the bisector of the i-th slice. 
   */
  SoMFFloat sliceToTranslateValue  ;

  /**
   * Slice are approximated by a polygon, that is a sequence of straight line 
   * segments. sliceAngleStep is the angle formed by two consecutive points of the 
   * polygon relative to the center of the slice.
   */
  SoSFFloat sliceAngleStep ;





  /* Methods */

  /**
   * Sets a reference to a PbMiscTextAttr for miscellaneous text attributes.
   * If this method is not called (or called passing NULL as argument), 
   * this is the miscellaneous text attributes defined in the current inherited state 
   * (defined with the property node PoMiscTextAttr) which are used.
   */
  void setMiscTextAttr(PbMiscTextAttr *textAttr) ;

  /**
   * Gets a reference to a PbMiscTextAttr for miscellaneous text attributes. 
   */
  const PbMiscTextAttr *getMiscTextAttr() const ;

  /**
   * Sets a reference to a PbNumericDisplayFormat object for the numerical 
   * display format of values of the pie chart. If this method is not called
   * (or called passing NULL as argument), this is the numerical display format 
   * defined in the current inherited state (defined with the property node 
   * PoNumericDisplayFormat) which is used.
   */
  void setFormat(PbNumericDisplayFormat *format) ;

  /**
   * Gets a reference to a PbNumericDisplayFormat object for the numerical 
   * display format of values of the pie chart.
   */
  const PbNumericDisplayFormat *getFormat() const ;

  /**
   * Allow the user to retreive the slice number (sliceNumber argument) which has 
   * been picked from a picked path (path argument) (cf SoSelection node for more 
   * information about picking). 
   * @return FALSE, if the picked path does not correspond to a slice of the pie 
   * chart (sliceNumber is not significative), 
   * @return TRUE otherwise.
   * [OIVJAVA-WRAPPER-RETURN-TYPE SUCCESS_FLAG{throw new IllegalArgumentException()}]
   */
  SbBool getPickedSliceNumber(const SoPath *path, int &sliceNumber) const ;

  /**
   * Convenience methods to set the fields sliceToTranslateNumber and 
   * sliceToTranslateValue. 
   * As regards setSliceToTranslate() method, 
   *  if sliceNumber == sliceToTranslateNumber[i] (i=0 to sliceToTranslateNumber.getNum() - 1), 
   *    sliceToTranslateNumber[i] = translationValue, 
   *  else 
   *    sliceToTranslateNumber[sliceToTranslateNumber.getNum()] = translationValue.
   */
  void  setSliceToTranslate(int sliceNumber, float translateValue) ;

  /**
   * Gets the current translation of a slice.
   * Returns 0 if sliceNumber slice does not exist or 
   * sliceNumber slice is not translated, the translation value otherwise.
   */
  float getSliceToTranslate(int sliceNumber) const ;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  // Computed by GraphMaster attributes
  struct PieChartAttr {
    SbString intTextFontName ;
    float    intTextFontSize ;

    SbString extTextFontName ;
    float    extTextFontSize ;

    SbString intValFontName ;
    float    intValFontSize ;

    SbString extValFontName ;
    float    extValFontSize ;

    SbString intPercentFontName ;
    float    intPercentFontSize ;

    SbString extPercentFontName ;
    float    extPercentFontSize ;

    float    intDist ;

    float    extDist1 ;
    float    extDist2 ;
    float    extDist3 ;

    float    arrowWidth ;
    float    arrowHeight ;

    SbString sliceNames[360] ;

    int      numSlices ;
    int      displayedSlicesNum ;
    int      displayedSlices[360] ;
    float    slicesPercentages[360] ;
    SbString slicesValuesString[360] ;
    SbString slicesPercentagesString[360] ;
    float    slicesValues[360] ;
    float    slicesTranslation[360] ;

    int      slicesLowValuesNumbers ;

    char     endLineChar ;
    int      lineLength ;
  } ;

  PieChartAttr m_pieChartAttr ;

  enum AnnotPosPieChart { // Position of an annotation relative to the Pie Chart
    RIGHT_PIE_CHART,
    LEFT_PIE_CHART,
    UP_PIE_CHART,
    DOWN_PIE_CHART
  } ;
  
  // Constructors
  PoPieChart(SbBool isDefault=TRUE, float _radius=1., short numSlices=0,
             const char **_sliceTexts=NULL, const float *_sliceValues=NULL,
             int numSliceColors=0, const SbColor *_sliceColors=NULL) ;
  // Destructor
  virtual ~PoPieChart() ;

  // Methods
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void   setDefaultOnNonWritingFields() ;
  virtual void   basicObjectChange(PbBase *basicObj) ;

  // Save all pie chart attributes which can be modified by MeshViz.
  void  savePieChartAttr() ;

  // Compute slice part values to display.
  void computeSlicePartValuesToDisplay() ;

  // Compute  percentage or value (following isPercentage flag) 
  // strings to display with the request numeric display format.
  void computeStringsToDisplay(const float *values, int numValues, SbBool isPercentage) ;

  // Draw internal annotations
  void drawInternalAnnotations(const SbVec2f &pieChartCenter, const SbVec2f &pointz) ;

  // Draw an internal annotation
  void drawInternalAnnot(int sliceNum, const SbVec2f &annotCenterPoint, const SbVec2f &pointz,
                         AnnotPosPieChart annotPosPieChart, int nbAnnot, float rotateAnnotAngle,
                         PiText *intText, PiText *intValue, PiText *intPercent, 
                         SoGroup *intAnnotBoxGroup, SoGroup *intAnnotBoxBorderGroup) ;

  // Draw external annotations
  void drawExternalAnnotations(const SbVec2f &pieChartCenter, const SbVec2f &pointz) ;

  // Draw an external annotation
  void drawExternalAnnot(int sliceNum, const SbVec3f &arrowStartPoint, const SbVec2f &pointz,
                         AnnotPosPieChart annotPosPieChart, int nbAnnot, float rotateAnnotAngle, 
                         PiText *extText, PiText *extValue, PiText *extPercent, 
                         SoGroup *extAnnotBoxGroup, SoGroup *extAnnotBoxBorderGroup) ;

  // Set all part to NULL
  void resetAllPart() ;

  // Compute slice names
  void computeSliceNames() ;

  // Overloaded methods
  virtual void addElementsAllCaches() ;
  virtual void preRebuild() ;

 private:
  // Miscellaneous text attributes
  PbMiscTextAttr *m_miscTextAttr, m_defaultMiscTextAttr ;

  // Numeric Display format
  PbNumericDisplayFormat *m_numericDisplayFormat, m_defaultNumericDisplayFormat ;

  // Sensors
  FieldSensorList m_fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     m_fieldList ;

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_PIE_CHART_  */

