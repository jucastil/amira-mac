/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_MULTIPLE_HISTOGRAM_
#define  _PO_MULTIPLE_HISTOGRAM_

#include <MeshViz/graph/PoHistogram.h>

#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFUShort.h>
#include <Inventor/fields/SoSFEnum.h>

/**
 * @DTEXT  Class to build a multiple histogram.
 * 
 * @ingroup GraphHistogram
 * 
 * @DESCRIPTION
 *    Class to build a multiple histogram in the plane XY. This histogram is 
 *    based on multiple statistical data. Multiple statistical data is composed 
 *    of a matrix of values associated to a list of column names and a list of 
 *    row names.
 * 
 *    The histogram bars are perpendicular to the X-axis or to the Y-axis 
 *    (according to the field type). The statistic values correspond to the height
 *    (or width) of the bars.
 * 
 *    There are three possible representations of multiple histograms:
 *       - The histogram values are juxtaposed.
 *       - The histogram values are accumulated.
 *       - The histogram values are percentages.
 *
 *    The bars of the histogram can be colored using the fields color and coloring. 
 *    If the bars colors are defined by a list of colors (coloring = COLOR_LIST), 
 *    according to the field histogPath, the list of colors is associated to the 
 *    rows or to the columns and color.getNum() must be greater or equal to
 *    getNum(), otherwise all the bars get the same color which is the inherited
 *    color.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoMultipleHistogram {
 *    @TABLE_FILE_FORMAT
 *       @TR start @TD 0 0
 *       @TR end @TD 1
 *       @TR type @TD X
 *       @TR color @TD 0 0 0
 *       @TR coloring @TD COLOR_LIST
 *       @TR valueVisibility @TD VISIBILITY_ON
 *       @TR valuePosition @TD POS_DEPEND
 *       @TR valuePath @TD PATH_DEPEND  
 *       @TR valueFontSize @TD 0.0
 *       @TR valueFontName @TD ""
 *       @TR valueAddStringVisibility @TD FALSE  
 *       @TR valueAddString @TD ""
 *       @TR nameVisibility @TD VISIBILITY_ON
 *       @TR namePosition @TD POS_DEPEND
 *       @TR namePath @TD PATH_DEPEND
 *       @TR nameFontSize @TD 0.0
 *       @TR nameFontName @TD ""
 *       @TR barSpaceType @TD REL_SPACE
 *       @TR barSpaceValue @TD 0.25
 *       @TR representation @TD JUXTAPOSED
 *       @TR barHeight @TD 1.0
 *       @TR numRows @TD 1
 *       @TR numColumns @TD 1
 *       @TR value @TD 0
 *       @TR rowName @TD ""
 *       @TR columnName @TD ""
 *       @TR histogPath @TD ROW_COLUM
 *       @TR sumVisibility @TD VISIBILITY_ON
 *       @TR sumPosition @TD POS_DEPEND
 *       @TR sumPath @TD PATH_DEPEND
 *       @TR sumFontSize @TD 0.0
 *       @TR sumFontName @TD ""
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pomultiplehistogram.cat.html
 * 
 * 
 */
class MESHVIZ_API PoMultipleHistogram : public PoHistogram {

  SO_KIT_HEADER(PoMultipleHistogram) ;

  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(sumTextSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(sumTextApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(sumText) ;
  

 public:

  enum HistogPath {
    /**
     *  Histogram shows rows in function of columns.
     */
    ROW_COLUMN, 
    /**
     *  Histogram shows columns in function of rows.
     */
    COLUMN_ROW  
  } ;



  /**
   *  Type of presentation of multiple histogram.
   */
  enum Representation {
    /**
     *  Histogram bars are juxtaposed.
     */
    JUXTAPOSED,  
    /**
     *  Histogram bars are accumulated.
     */
    ACCUMULATED, 
    /**
     *  Histogram bars are percentage.
     */
    PERCENTAGE   
  } ;



  /* Fields */

  /**
   * Number of rows of the matrix of values.
   */
  SoSFUShort  numRows ;

  /**
   * Number of columns of the matrix of values.
   */
  SoSFUShort  numColumns ;

  /**
   * Matrix of values.
   */
  SoMFFloat   value ;

  /**
   * List of numRows names of the rows.
   */
  SoMFString  rowName ;

  /**
   * List of numColumns names of the columns.
   */
  SoMFString  columnName ;

  /**
   * Representation type of the multiple histogram.
   */
  SoSFEnum    representation ;

  /**
   * This field is used only for percentage histogram representation  
   * (representation = PERCENTAGE) and it corresponds to the height of the 
   * histogram (in this representation, all the bars have the same size).
   */
  SoSFFloat   barHeight ;

  /**
   * Indicates that the histogram shows rows as a function of columns, or columns 
   * as a function of rows.
   */
  SoSFEnum    histogPath ;

  /**
   * Bars sums visibility.
   */
  SoSFEnum    sumVisibility ;

  /**
   * Position of sums in relation to bars.
   */
  SoSFEnum    sumPosition ;

  /**
   * Writing path of bars sums.
   */
  SoSFEnum    sumPath ;

  /**
   * Font size of bars sums. if this value is less or equal to 0, 
   * the font size is fixed at 0.04.  This value is a percentage 
   * of the current domain (cf PoBase description).
   */
  SoSFFloat   sumFontSize ;

  /**
   * Font name of bars sums. If the font is equal to its default 
   * value, the font used is the font of the current miscellaneous 
   * text attributes (cf PoHistogram description).
   */
  SoSFString  sumFontName ;



  /* Methods */

  /**
   * Default constructor.
   */
  PoMultipleHistogram()
    { init(TRUE, SbVec2f(0.,0.), 1., X, 0, 0, NULL, NULL, NULL) ; }

  /**
   * Constructor.
   * [OIV-WRAPPER-ARG IN,IN,IN,IN,IN,ARRAY,ARRAY,ARRAY]
   */
  PoMultipleHistogram(const SbVec2f &_start, float _end, PoHistogram::Type _type,
                      int _numRows, int _numColumns, const float *_value,
                      const char **_rowName, const char **_columnName)
    { init(FALSE, _start, _end, _type, _numRows, _numColumns, _value, _rowName, 
           _columnName) ; }

  /**
   * Constructor.
   * [OIV-WRAPPER-NOT-WRAP]
   */
  PoMultipleHistogram(const SbVec2f &_start, float _end, PoHistogram::Type _type,
                      int _numRows, int _numColumns, const float **_value,
                      const char **_rowName, const char **_columnName) ;

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void rebuild() ;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

  struct SumAttr {
    Position position ;
    TextPath path ;
    float    fontSize ;
    SbString fontName ;
  } ;

 protected:
  struct MultHistogAttr {
    SumAttr sum ;
  } ;
  
  MultHistogAttr m_multHistogAttr ;
  
  // Methods
  // Destructor
  virtual ~PoMultipleHistogram() ;
  virtual void   setDefaultOnNonWritingFields() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;

  virtual void setDefaultAttr() ;

  // Color the bars
  void colorBars(SoGroup *group) ;

 private:
  // Init method
  void init(SbBool isDefault, const SbVec2f &_start, float _end, 
            Type _type, int _numRows, int _numColumns, const float *_value,
            const char **_rowName, const char **_columnName) ;

  // Build X or Y Histogram
  void buildXJuxtaposedHistog() ;
  void buildYJuxtaposedHistog() ;

  void buildXAccumulatedHistog() ;
  void buildYAccumulatedHistog() ;

  void buildXPercentageHistog() ;
  void buildYPercentageHistog() ;

  // Sensors
  FieldSensorList m_fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     m_fieldList ;

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_MULTIPLE_HISTOGRAM_ */

