/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _PO_LEGEND_
#define  _PO_LEGEND_

#include <MeshViz/graph/PoGraphMaster.h>

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFUShort.h>
#include <Inventor/fields/SoSFString.h>

class PbMiscTextAttr ;
class PiText ;

/**
 * @DTEXT  Abstract class for legend representations.
 * 
 * @ingroup GraphLegend
 * 
 * @DESCRIPTION
 *    This class handles the title, the values, the margins and the path of 
 *    the legend.
 * 
 *    All legend texts depend on the current miscellaneous text attributes which 
 *    define the font name, line length and so on. If the method setMiscTextAttr(textAttr)
 *    is called, the current miscellaneous text attributes are defined by "textAttr". 
 *    Otherwise the current miscellaneous text attributes are specified in the current 
 *    inherited state (cf property node PoMiscTextAttr).
 * 
 */

class MESHVIZ_API PoLegend : public PoGraphMaster {

  SO_KIT_HEADER(PoLegend) ;

  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(backgroundSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(backgroundApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(background) ;

  SO_KIT_CATALOG_ENTRY_HEADER(backgroundBorderSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(backgroundBorderApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(backgroundBorder) ;

  SO_KIT_CATALOG_ENTRY_HEADER(boxSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(boxApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(box) ;

  SO_KIT_CATALOG_ENTRY_HEADER(boxBorderSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(boxBorderApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(boxBorder) ;

  SO_KIT_CATALOG_ENTRY_HEADER(titleSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(titleApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(title) ;

  SO_KIT_CATALOG_ENTRY_HEADER(valueTextSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(valueTextApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(valueText) ;


 public:

  /**
   *  Type of visibility.
   */
  enum Visibility {
    /**
     *  Invisible.
     */
    VISIBILITY_OFF, 
    /**
     *  Visible.
     */
    VISIBILITY_ON   
  } ;

  /**
   *  Text path.
   */
  enum TextPath {
    /**
     *  Writing from left to right.
     */
    PATH_RIGHT,   
    /**
     *  Writing from right to left.
     */
    PATH_LEFT,    
    /**
     *  Writing from bottom to top.
     */
    PATH_UP,      
    /**
     *  Writing from top to bottom.
     */
    PATH_DOWN     
  } ;

  /**
   *  Type of position.
   */
  enum Position {
    /**
     *  Bottom position.
     */
    POS_BOTTOM,  
    /**
     *  Top position.
     */
    POS_TOP,     
    /**
     *  Right position.
     */
    POS_RIGHT,   
    /**
     *  Left position.
     */
    POS_LEFT     
  } ;

  /**
   *  Type of margins.
   */
  enum MarginType {
    /**
     *  Relative margin.
     */
    REL_MARGIN,  
    /**
     *  Absolute margin.
     */
    FIXED_MARGIN 
  } ;

  /**
   *  Type of values incrementation.
   */
  enum IncrementType {
    /**
     *  Values of the legend are vertically incremented.
     */
    VERTICAL_INCREMENT,   
    /**
     *  Values of the legend are horizontally incremented.
     */
    HORIZONTAL_INCREMENT  
  } ;



  /* Fields */

  /* title attributes */

  /**
   * Title visibility.
   */
  SoSFEnum   titleVisibility ;

  /**
   * Title position.
   */
  SoSFEnum   titlePosition ;

  /**
   * Title path.
   */
  SoSFEnum   titlePath ;

  /**
   * Font size of the title.
   */
  SoSFFloat  titleFontSize ;

  /**
   * Font name of the title. If the font is equal to its default 
   * value, the font used is the font of 
   * the current miscellaneous text attributes.
   */
  SoSFString titleFontName ;

  /**
   * Title string.
   */
  SoSFString titleString ;

  /* values attributes */

  /**
   * Values visibility.
   */
  SoSFEnum   valueVisibility ;

  /**
   * Values positions.
   */
  SoSFEnum   valuePosition ;

  /**
   * Font name of values. If the font is equal to its 
   * default value, the font used is the font of 
   * the current miscellaneous text attributes.
   */
  SoSFString valueFontName ;

  /**
   * Visibility of a string concatenated to the values.
   */
  SoSFBool   valueAddStringVisibility ;

  /**
   * String to be concatenated.
   */
  SoSFString valueAddString ;

  /* margin attributes */

  /**
   * Margin type.
   */
  SoSFEnum   marginType ;

  /**
   * Left margin.
   */
  SoSFFloat  marginLeft ;

  /**
   * Right margin.
   */
  SoSFFloat  marginRight ;

  /**
   * Bottom margin.
   */
  SoSFFloat  marginBottom ;

  /**
   * Top margin.
   */
  SoSFFloat  marginTop ;



  /**
   * Increment type for the values of legend. (the values can be incremented 
   * vertically or horizontally).
   */
  SoSFEnum   incrementType ;

  /**
   * Number of columns of the legend.
   */
  SoSFUShort numColumns ;



  /**
   * Ratio between width and height of the colored boxes in the legend.
   */
  SoSFFloat  boxRatio ;



  /* Methods */

  /**
   * Sets a reference to a PbMiscTextAttr for miscellaneous text attributes of
   * all legend texts. If this method is not called (or called passing NULL as 
   * argument), this is the miscellaneous text attributes defined in the current 
   * inherited state (defined with the property node PoMiscTextAttr) which are used.
   */
  void setMiscTextAttr(PbMiscTextAttr *textAttr) ;

  /**
   * Gets a reference to a PbMiscTextAttr for miscellaneous text attributes. 
   */
  const PbMiscTextAttr *getMiscTextAttr() const ;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  struct LegendAttr {
    float    titleFontSize ;
    SbString titleFontName ;

    float    valueFontSize ;
    SbString valueFontName ;
  } ;

  // Methods
  virtual void   setDefaultOnNonWritingFields() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;

  // Manage the connection with PbBase objects
  virtual void basicObjectChange(PbBase *basicObj) ;

  //******************* Methods for automatic legends *************************

  // Compute margin for auto legend
  void computeMarginA(const SbVec2f &ptBoxOrig, float boxWidth,
                      float boxHeight, SbVec2f &ptLegendOrig,
                      float &legendWidth, float &legendHeight) ;

  // Compute title font size for auto legend
  void computeTitleSizeA(float legendWidth, float legendHeight,
                         float &titleWidth, float &titleHeight) ;

  // Draw background for auto legend
  void drawBackgroundA(const SbVec2f &ptBoxOrig, float boxWidth, float boxHeight) ;

  // Draw title for auto legend
  void drawTitleA(float titleHeight, float titleWidth, Plimit &limit) ;

  // Draw boxes for auto legend constitued of several boxes 
  void drawBoxesLegendBoxesA(SbBool isBoxVisible, float boxWidth, float boxHeight,
                             int nb_lines, int nb_columns, 
                             int numItems, const float *maxTextSizePerCol,
                             const SbVec2f &space_box, const Plimit &limit) ;
  
  // Draw a box with an interior color
  virtual void drawBoxLegendBoxesA(SoGroup *boxBorderGroup, SoGroup *boxGroup,
                                   const SbVec2f &topLeftCorner, float width, 
                                   float height, int repIndex) ;

  // Draw values for auto legend constitued of several boxes
  void drawValuesLegendBoxesA(int nb_lines, int nb_columns, int numStrings, 
                              const SbString *strings, const float *maxTextSizePerCol,
                              const SbVec2f &space_box, const Plimit &limit, 
                              PiText &valText) ;

  // Compute graphic size use to draw values in  auto legend constitued 
  // of several boxes
  virtual void computeGraphicSizeForValues(float &width, float &height,
                                           float &text_space) ;

  // Determines if the legend must be reverted or not.
  virtual void setRevertOrder(float startY, float endY) 
    { m_revertOrder =  (startY <= endY ? FALSE : TRUE) ; }
  SbBool isRevertOrder() const
    { return m_revertOrder ; }

  // Indicate if the values and boxes are
  // drawn from down to up (FALSE)
  // or from up to down (TRUE)
  SbBool m_revertOrder ;
  //****************** Methods for non automatic legend ************************
  
  // Set default attributes
  void setDefaultAttr() ;

  // Constructor
  PoLegend() ;

  // Destructor
  virtual ~PoLegend() ;

  // Overloaded methods
  virtual void addElementsAllCaches() ;
  virtual void preRebuild() ;

  // Attributes computed 
  LegendAttr m_legendAttr ;

 private:
  // Miscellaneous text attribute
  PbMiscTextAttr *m_miscTextAttr, *m_defaultMiscTextAttr ;

  // Sensors
  FieldSensorList m_fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     m_fieldList ;

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_LEGEND_ */



