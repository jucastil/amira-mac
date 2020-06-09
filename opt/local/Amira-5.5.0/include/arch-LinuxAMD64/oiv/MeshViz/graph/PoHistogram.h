/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_HISTOGRAM_
#define  _PO_HISTOGRAM_

#include <MeshViz/graph/PoGraphMaster.h>

#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFColor.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFString.h>


class PbMiscTextAttr ;
class PbDataMapping ;
class PbNumericDisplayFormat ;

class PiText ;

/**
 * @DTEXT  Abstract class for histogram representations.
 * 
 * @ingroup GraphHistogram
 * 
 * @DESCRIPTION
 *    This class handles the start, the end, the values of the bars, the names 
 *    of the bars and the bars spacing of a histogram.
 * 
 *    All histogram texts depend on the current miscellaneous text attributes which 
 *    define the font name, line length and so on. If the method setMiscTextAttr(textAttr)
 *    is called, the current miscellaneous text attributes are defined by "textAttr". 
 *    Otherwise the current miscellaneous text attributes are specified in the current 
 *    inherited state (cf property node PoMiscTextAttr).
 * 
 *    All histogram numerical values depend on the current numerical display format.
 *    If the method setFormat(format) is called, the current numerical display format 
 *    is "format". Otherwise the current numerical display format is specified in 
 *    the current inherited state (cf property node PoNumericDisplayFormat).
 *   
 *    If coloring = DATA_MAPPING, colors of histogram bars depend on the current
 *    data mapping. If the method setDataMapping(dataMapping) is called, the 
 *    current data mapping is "dataMapping". Otherwise the current data mapping 
 *    is specified in the current inherited state (cf property node PoDataMapping 
 *    and its derived classes). If there is no current data-mapping
 *    (i.e setDataMapping() not called and no PoDataMapping node traversed before 
 *    in the scene graph), all bars get the same color which is the inherited color.
 * 
 */

class MESHVIZ_API PoHistogram : public PoGraphMaster {

  SO_KIT_HEADER(PoHistogram) ;

  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(transform) ;

  SO_KIT_CATALOG_ENTRY_HEADER(barSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(barApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(bar) ;

  SO_KIT_CATALOG_ENTRY_HEADER(valueTextSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(valueTextApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(valueText) ;

  SO_KIT_CATALOG_ENTRY_HEADER(nameTextSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(nameTextApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(nameText) ;


 public:

  /**
   *  Type of orientation of the histogram's bars
   */
  enum Type {
    /**
     *  Histogram bars are perpendicular to X-Axis.
     */
    X, 
    /**
     *  Histogram bars are perpendicular to Y-Axis.
     */
    Y  
  } ;

  /**
   *  Type of positions relative to a histogram bar
   */
  enum Position {
    /**
     *  At the top outside the bar.
     */
    POS_TOP_OUT,   
    /**
     *  At the top inside the bar.
     */
    POS_TOP_IN,    
    /**
     *  At the bottom outside the bar.
     */
    POS_BOTTOM_OUT,
    /**
     *  At the bottom inside the bar.
     */
    POS_BOTTOM_IN, 
    /**
     *  At the right outside the bar.
     */
    POS_RIGHT_OUT, 
    /**
     *  At the right inside the bar.
     */
    POS_RIGHT_IN,  
    /**
     *  At the left outside the bar.
     */
    POS_LEFT_OUT,  
    /**
     *  At the left inside the bar.
     */
    POS_LEFT_IN,   
    /**
     *  Centered in the bar.
     */
    POS_CENTER,    
    /**
     *  Depends on the type of histogram.
     */
    POS_DEPEND     
  } ;

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
   *  Type of text path.
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
    PATH_DOWN,    
    /**
     *  Depends on the type of histogram.
     */
    PATH_DEPEND   
  } ;

  /**
   *  Type of spacing between bars.
   */
  enum BarSpaceType {
    /**
     *  Relative histogram bar spacing.
     */
    REL_SPACE,    
    /**
     *  Fixed histogram bar spacing.
     */
    FIXED_SPACE   
  } ;

  /**
   *  Type of coloration of the bars.
   */
  enum Coloring {
    /**
     *  Histogram bars are colored by a list of colors.
     */
    COLOR_LIST,   
    /**
     *  Histogram bars are colored by data mapping.
     */
    DATA_MAPPING  
  } ;





  /* Fields */

  /**
   * Define the start point of the histogram.
   */
  SoSFVec2f  start ;

  /**
   * Define the end point of the histogram.
   */
  SoSFFloat  end ;

  /**
   * Defines if the histogram is an X histogram (bars are perpendicular to the X-
   * axis) or a Y histogram (bars are perpendicular to the Y-axis).
   */
  SoSFEnum   type ;

  /**
   * Color list for the histogram bars. This field is used only if coloring = 
   * COLOR_LIST. If the number of colors is less than the number of bars, all the 
   * bars get the same color which is the inherited color.
   */
  SoMFColor  color ;

  /**
   * Specifies how the histogram bars are colored. if coloring = COLOR_LIST, the 
   * bars are colored using the color list field color, otherwise the bars are colored 
   * according to their values (see the current data mapping for the association color-value
   * at the header description).
   */
  SoSFEnum   coloring ;

  /* Attribute of values */

  /**
   * Values visibility.
   */
  SoSFEnum   valueVisibility ;

  /**
   * Values position in relation to histogram bars.
   */
  SoSFEnum   valuePosition ;

  /**
   * Values path.
   */
  SoSFEnum   valuePath ;

  /**
   * Font size of values. if this value is less or 
   * equal to 0, the font size is fixed at 0.04. 
   * This value is a percentage of the current domain 
   * (cf PoBase description).
   */
  SoSFFloat  valueFontSize ;

  /**
   * Font name of values. If the font is equal to its 
   * default value, the font used is the font of
   * the current miscellaneous text attributes.
   */
  SoSFString valueFontName ;

  /**
   * Visibility of the string concatenated to the values.
   */
  SoSFBool   valueAddStringVisibility ;

  /**
   * String to be concatenated.
   */
  SoSFString valueAddString ;

  /* Attribute of bar names */

  /**
   * Bars names visibility.
   */
  SoSFEnum   nameVisibility ;

  /**
   * Bars names position in relation to histograms bars.
   */
  SoSFEnum   namePosition ;

  /**
   * Bars names path.
   */
  SoSFEnum   namePath ;

  /**
   * Font size of bars names. if this value is less or equal 
   * to 0, the font size is fixed at 0.04. This value is a 
   * percentage of the current domain (cf PoBase description).
   */
  SoSFFloat  nameFontSize ; 

  /**
   * Font name of bars names. If the font is equal to its 
   * default value, the font used is the font of the current 
   * miscellaneous text attributes.
   */
  SoSFString nameFontName ;

  /**
   * Type of bar spacing. The spacing between bars modifies 
   * the thickness of the histogram bars.
   */
  SoSFEnum   barSpaceType ;

  /**
   * Spacing value. If barSpaceType = REL_SPACE, 
   * real_spacing = barSpaceValue * width_bar, where 
   * width_bar is the distance between the histogram origin 
   * and the end point divided by the number of main bars. If 
   * barSpaceType = FIXED_SPACE, the real spacing is 
   * equal to barSpaceValue.
   */
  SoSFFloat  barSpaceValue ;





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
   * Sets a reference to a PbDataMapping object to the association color-value 
   * for coloring the bars. If this method is not called (or called passing NULL 
   * as argument), this is the data mapping defined in the current inherited state 
   * (defined with the property node PoDataMapping and its derived classes) which 
   * is used. This method is ignored if coloring = COLOR_LIST.
   */
  void setDataMapping(PbDataMapping *dataMapping) ;

  /**
   * Gets a reference to a PbDataMapping object to the association color-value 
   * for coloring the bars. 
   */
  const PbDataMapping* getDataMapping() const ;

  /**
   * Sets a reference to a PbNumericDisplayFormat object for the numerical 
   * display format of values of the histograms. If this method is not called
   * (or called passing NULL as argument), this is the numerical display format 
   * defined in the current inherited state (defined with the property node 
   * PoNumericDisplayFormat) which is used.
   */
  void setFormat(PbNumericDisplayFormat *format) ;

  /**
   * Gets a reference to a PbNumericDisplayFormat object for the numerical 
   * display format of values of the histograms.
   */
  const PbNumericDisplayFormat *getFormat() const ;
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

  struct ValueAttr {
    Position position ;
    TextPath path ;
    float    fontSize ;
    SbString fontName ;
  } ;

  struct NameAttr {
    Position position ;
    TextPath path ;
    float    fontSize ;
    SbString fontName ;
  } ;

 protected:
  struct HistogAttr {
    ValueAttr   value ;
    NameAttr    name ;
    float       scaleFactor ;
  } ;

  HistogAttr m_histogAttr ;

  // Methods
  virtual void   setDefaultOnNonWritingFields() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  
  // Manage the connection with PbBase objects
  virtual void basicObjectChange(PbBase *basicObj) ;

  virtual void setDefaultAttr() ;
  virtual void colorBars(SoGroup *group) ;

  // Constructor
  PoHistogram() ;

  // Destructor
  virtual ~PoHistogram() ;

  // Compute a reference point from a rectangle,
  // a position type relative to this one and the 
  // fontSize.
  static void computeTextPos(const SbVec2f *rectangle, Position textPos, float
                             fontSize, SbVec2f &pointText) ;

  // Compute text alignment for a position type and a path
  static void computeTextAlignPath(Position textPos, TextPath path, PiText *text) ;

  // Overloaded methods
  virtual void addElementsAllCaches() ;
  virtual void preRebuild() ;
  
 private:
  // Miscellaneous text attribute
  PbMiscTextAttr *m_miscTextAttr, *m_defaultMiscTextAttr ;

  // Data Mapping
  PbDataMapping *m_dataMap ;

  // Numeric display format
  PbNumericDisplayFormat *m_numericDisplayFormat, *m_defaultNumericDisplayFormat ;

  // Sensors
  FieldSensorList m_fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     m_fieldList ;

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_HISTOGRAM_ */

