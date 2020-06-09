/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_AXIS_
#define  _PO_AXIS_

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFUShort.h>
#include <Inventor/fields/SoSFBool.h>

#include <MeshViz/graph/PoBaseAxis.h>
#include <MeshViz/graph/PbMiscTextAttr.h>

class PiText ;


/**
 * @DTEXT  Abstract class for axis representations. 
 * 
 * @ingroup GraphAxis
 * 
 * @DESCRIPTION
 *    This class groups all common methods and 
 *    all common fields of all axes. Some enumerations are named DEPEND, in such a 
 *    case, the choice of these values is done when building the axis.
 * 
 *    All axis texts depend on the current miscellaneous text attributes which define
 *    the font name, line length and so on. If the method setMiscTextAttr(textAttr)
 *    is called, the current miscellaneous text attributes are defined by "textAttr". 
 *    Otherwise the current miscellaneous text attributes are specified in the current 
 *    inherited state (cf property node PoMiscTextAttr).
 * 
 */
class MESHVIZ_API PoAxis : public PoBaseAxis {

  SO_KIT_HEADER(PoAxis) ;

  // Define fields for new parts
  SO_KIT_CATALOG_ENTRY_HEADER(transform) ;

  SO_KIT_CATALOG_ENTRY_HEADER(bodySep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(bodyApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(body) ;

  SO_KIT_CATALOG_ENTRY_HEADER(arrowSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(arrowApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(arrow) ;

  SO_KIT_CATALOG_ENTRY_HEADER(titleSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(titleApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(title) ;

  SO_KIT_CATALOG_ENTRY_HEADER(subGradTickSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(subGradTickApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(subGradTick) ;

  SO_KIT_CATALOG_ENTRY_HEADER(subGradGridSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(subGradGridApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(subGradGrid) ;

  SO_KIT_CATALOG_ENTRY_HEADER(mainGradTickSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(mainGradTickApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(mainGradTick) ;

  SO_KIT_CATALOG_ENTRY_HEADER(mainGradGridSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(mainGradGridApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(mainGradGrid) ;

  SO_KIT_CATALOG_ENTRY_HEADER(mainGradTextSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(mainGradTextApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(mainGradText) ;


 public:

  /**
   * Enumerations
   */

  /**
   *  Visibility type
   */
  enum Visibility {
    /**
     *  Invisible.
     */
    VISIBILITY_OFF,   
    /**
     *  Visible.
     */
    VISIBILITY_ON,    
    /**
     *  Depends on the type of the axis.
     */
    VISIBILITY_DEPEND 
  } ;



  /**
   *  Text path type
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
     *  Depends on the type of the axis.
     */
    PATH_DEPEND  
  } ;



  /**
   *  Graduation position type
   */
  enum GradPosition {
    /**
     *  Graduations are above the axis.
     */
    GRAD_ABOVE,  
    /**
     *  Graduations are below the axis.
     */
    GRAD_BELOW,  
    /**
     *  Depends on the type of the axis.
     */
    GRAD_DEPEND  
  } ;



  /**
   *  Margin type 
   */
  enum MarginType {
    /**
     *  Relative margin on the axis.
     */
    REL_MARGIN,  
    /**
     *  Absolute margin on the axis.
     */
    FIXED_MARGIN 
  } ;



  /**
   *  Tick position type
   */
  enum TickPosition {
    /**
     *  Ticks are on the same side of graduations.
     */
    TICK_GRAD_SIDE,       
    /**
     *  Ticks are on the other side of graduations.
     */
    TICK_GRAD_OTHER_SIDE, 
    /**
     *  Ticks across the axis.
     */
    TICK_ACROSS_AXIS      
  } ;



  /**
   *  Title position type
   */
  enum TitlePosition {
    /**
     *  Title is at the middle of the axis.
     */
    TITLE_MIDDLE,  
    /**
     *  Title is at the end of the axis.
     */
    TITLE_END,     
    /**
     *  Depends on the axis type.
     */
    TITLE_DEPEND   
  } ;



  /**
   *  Sub-tick type
   */
  enum TickSubDef {
    /**
     *  Number of secondary graduations 
     */
    NUM_SUB_TICK,     
    /**
     *  or period of texts of graduations 
     */
    PERIOD_MAIN_TICK  
  } ;



  /**
   *  Axis reverse type
   */
  enum AxisReverse {
    /**
     *  Texts of the axis are no reversed.
     */
    AXIS_NO_REVERSE,    
    /**
     *  Texts of the axis are reversed (mirror effect).
     */
    AXIS_REVERSE,       
    /**
     *  Depends on the axis type.
     */
    AXIS_REVERSE_DEPEND 
  } ;



  /* Fields */



  /* Graduations attributes */

  /**
   * Graduations visibility.
   */
  SoSFEnum   gradVisibility ;  

  /**
   * Graduations position.
   */
  SoSFEnum   gradPosition ;    

  /**
   * Graduations path.
   */
  SoSFEnum   gradPath ;        

  /**
   * Graduations font name. If the font is equal to 
   * its default value, the font used is the font of 
   * the current miscellaneous text attributes.
   */
  SoSFString gradFontName ;    

  /**
   * Font size of the graduations. If this value is <= 
   * 0, the graduations font size is fixed at 0.04 if 
   * the graduations do not cross each other. This 
   * value is a percentage of the current domain (cf PoBase
   * description).
   */
  SoSFFloat  gradFontSize ;

  /**
   * Distance from the graduations to the axis. If 
   * this value is <= 0, the distance is automatically 
   * calculated. This value is a percentage of the 
   * current domain (cf PoBase description).
   */
  SoSFFloat  gradDistAxis ;

  /**
   * Specify the visibility of a string concatenated 
   * with the graduations.
   */
  SoSFBool   gradAddStringVisibility ;

  /**
   * String to be concatenated.
   */
  SoSFString gradAddString ;



  /* Margins attributes */

  /**
   * Relative or absolute margin.
   */
  SoSFEnum   marginType ;

  /**
   * Margin at the start of the axis.
   */
  SoSFFloat  marginStart ;

  /**
   * Margin at the end of the axis.
   */
  SoSFFloat  marginEnd  ;



  /* Title attributes */

  /**
   * Visibility of the title.
   */
  SoSFEnum   titleVisibility ;

  /**
   * Position of the title.
   */
  SoSFEnum   titlePosition ;

  /**
   * Path of the title.
   */
  SoSFEnum   titlePath ;

  /**
   * Title font name. If the font is equal to its default value, 
   * the font used is the font of the current miscellaneous 
   * text attributes.
   */
  SoSFString titleFontName ;

  /**
   * Font size of the title. If this value is <= 0, the graduations 
   * font size is fixed at 0.055. This value is a percentage of the 
   * current domain (cf PoBase description).
   */
  SoSFFloat  titleFontSize ;

  /**
   * Distance from the title to the axis. If this value is <= 0, the 
   * distance is automatically calculated. This value is a percentage 
   * of the current domain (cf PoBase description).
   */
  SoSFFloat  titleDistAxis ;

  /**
   * Title string.
   */
  SoSFString titleString ;



  /* Grid lines attributes */

  /**
   * Grid lines visibility.
   */
  SoSFEnum   gridVisibility ;

  /**
   * Grid lines length side graduation texts.
   */
  SoSFFloat  gridLengthGradSide ;

  /**
   * Grid lines length other side graduation texts.
   */
  SoSFFloat  gridLengthGradOtherSide ;



  /* Arrow attributes */

  /**
   * Arrow visibility.
   */
  SoSFEnum   arrowVisibility ;

  /**
   * Arrow height. If this value is <= 0, the height is fixed at 
   * 0.03. This value is a percentage of the current domain 
   * (cf PoBase description).
   */
  SoSFFloat  arrowHeight ;

  /**
   * Arrow length. If this value is <= 0, the length is fixed at 
   * 0.05. This value is a percentage of the current domain 
   * (cf PoBase description).
   */
  SoSFFloat  arrowLength ;



  /* Tick mark attributes */

  /**
   * Tick marks visibility.
   */
  SoSFEnum   tickVisibility ;

  /**
   * Position of the tick marks.
   */
  SoSFEnum   tickPosition ;

  /**
   * Main graduations ticks length. If this value is <= 0, 
   * the height is automatically calculated. This value is a 
   * percentage of the current domain (cf PoBase description).
   */
  SoSFFloat  tickMainLength ;

  /**
   * Secondary graduations ticks length. If this value is 
   * <= 0, the length is automatically calculated. This 
   * value is a percentage of the current domain 
   * (cf PoBase description).
   */
  SoSFFloat  tickSubLength ;

  /**
   * Secondary graduations tick definition. The 
   * secondary graduations can be given either by a 
   * number or by a period.
   */
  SoSFEnum   tickSubDef ;

  /**
   * Number of secondary graduations (tickSubDef = NUM_SUB_TICK), 
   * or period of texts of graduations (tickSubDef = PERIOD_MAIN_TICK).
   */
  SoSFUShort tickNumOrPeriod ;

  /**
   * First graduation to display.
   */
  SoSFUShort tickFirstGrad ;

  /**
   * Last graduation to display (number starting with 
   * the ending one).
   */
  SoSFUShort tickLastGrad ;

  /**
   * Allow to reverse the writing path of all axis texts.
   */
  SoSFEnum   reverseFlag ;





  /* Methods */

  /**
   * Sets a reference to PbMiscTextAttr object for miscellaneous text attributes. 
   * If this method is not called (or called passing NULL as argument), 
   * this is the miscellaneous text attributes defined in the current inherited state 
   * (defined with the property node PoMiscTextAttr) which are used.
   */
  void setMiscTextAttr(PbMiscTextAttr *textAttr) ;

  /**
   * Gets a reference to PbMiscTextAttr object for miscellaneous text attributes. 
   */
  const PbMiscTextAttr *getMiscTextAttr() const ;

  /* Get axis attributes methods */

  /**
   * Gets the graduations axis attributes computed by the last axis rebuilding. If 
   * the axis have never been built, the method return the value of the equivalent field.
   * [OIVJAVA-WRAPPER PACK{GradAttributes}]
   */
  void getGrad(Visibility &visibility, GradPosition &position, TextPath &path,
               SbString &fontName, float &fontSize, float &distAxis, SbBool
               &addStringVisibility, SbString &addString) const ;

  /**
   * Gets the margin axis attributes computed by the last axis rebuilding. If 
   * the axis have never been built, the method return the value of the equivalent field.
   * [OIVJAVA-WRAPPER PACK{MarginAttributes}]
   */
  void getMargin(MarginType &type, float &start, float &end) const ;

  /**
   * Gets the title axis attributes computed by the last axis rebuilding. If 
   * the axis have never been built, the method return the value of the equivalent field.
   * [OIVJAVA-WRAPPER PACK{TitleAttributes}]
   */
  void getTitle(Visibility &visibility, TitlePosition &position, TextPath
                &path,SbString &fontName, float &fontSize, float &distAxis, 
                SbString &string) const ;

  /**
   * Gets the grid axis attributes computed by the last axis rebuilding. If 
   * the axis have never been built, the method return the value of the equivalent field.
   * [OIVJAVA-WRAPPER PACK{GridAttributes}]
   */
  void getGrid(Visibility &visibility, float &lengthGradSide, float
               &lengthGradOtherSide) const ;

  /**
   * Gets the arrow axis attributes computed by the last axis rebuilding. If 
   * the axis have never been built, the method return the value of the equivalent field.
   * [OIVJAVA-WRAPPER PACK{ArrowAttributes}]
   */
  void getArrow(Visibility &visibility, float &height, float &length) const ;

  /**
   * Gets the tick axis attributes computed by the last axis rebuilding. If 
   * the axis have never been built, the method return the value of the equivalent field.
   * [OIVJAVA-WRAPPER PACK{TickAttributes}]
   */
  void getTick(Visibility &visibility, TickPosition &position, float &mainLength,
               float &subLength, TickSubDef &def, unsigned short &numOrPeriod, 
               unsigned short &firstGrad, unsigned short &lastGrad) const ;

  /**
   * Gets the reverse flag axis attributes computed by the last axis rebuilding. If 
   * the axis have never been built, the method return the value of the equivalent field.
   */
  AxisReverse getReverseFlag() const ;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

  struct GradAttr {
    Visibility         visibility ;
    GradPosition       position   ;
    TextPath           path       ;
    float              fontSize   ;
    SbString           fontName   ;
    float              distAxis   ;
  } ;
  // Grad attributes

  // Margin attributes
  struct MarginAttr {
    MarginType type  ;
    float      start ;
    float      end   ;
  } ;

  // Title attributes
  struct TitleAttr {
    Visibility    visibility ;
    TitlePosition position   ;
    TextPath      path       ; 
    float         fontSize   ;
    SbString      fontName   ;
    float         distAxis   ;
  } ;

  // Grid line attributes
  struct GridAttr {
    Visibility visibility       ;
    float      lenGradSide      ; 
    float      lenGradOtherSide ;
  } ;

  // Arrow attibutes
  struct ArrowAttr {
    Visibility visibility ;
    float      height     ;
    float      length     ;
  } ;

  // Tick mark attributes
  struct TickAttr {
    Visibility       visibility  ;
    TickPosition     position    ;
    float            mainLength  ;
    float            subLength   ;
    TickSubDef       subDef      ;
    int              numOrPeriod ;
    int              firstGrad   ;
    int              lastGrad    ;
  } ;

  // Miscellaneous attributes
  struct MiscAttr {
    float   deltaX          ;
    float   deltaY          ;
    Plimit  limit           ;
    char    endLineChar     ;
    int     lineLength      ;
    int     numGrad         ; 
    int     numMainGrad     ;
    int     numSubGrad      ;
    float   *mainGradCoords ;
    float   *subGradCoords  ;
  } ;

  enum Plane {
    XY,
    XZ,
    YX, 
    YZ, 
    ZX,
    ZY  
  } ;

  // Return main graduation coordinates and its number
  // For the moment available only for linear, log and gen axis
  int getMainGradCoords(const float* &coords) const ;

  // Return sub graduation coordinates and its number
  // For the moment available only for linear, log and gen axis
  int getSubGradCoords(const float* &coords) const ;

 protected:
  // Constructor
  PoAxis() ;
  // Destructor
  virtual ~PoAxis() ;

  // Axis attributes
  struct AxisAttr {
    GradAttr     grad        ;
    MarginAttr   margin      ;
    TitleAttr    title       ;
    GridAttr     grid        ;
    ArrowAttr    arrow       ;
    TickAttr     tick        ;
    AxisReverse  reverseFlag ;
    MiscAttr     misc        ;
  } ;

  // Methods
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void   setDefaultOnNonWritingFields() ;

  // Manage the connection with PbBase objects
  virtual void basicObjectChange(PbBase *basicObj) ;

  // Save all axis attributes which can be modified by MeshViz.
  virtual void   saveAxisAttr() ;
  
  // Set Default attributes
  virtual void setDefaultAttr(Plane plane = XY) ;

  // Compute limit coordinate for display graduation
  virtual void computeGradLimit(float xOrig, float xExtr, float &xmOrig, float &xmExtr) ;

  // Compute tick length
  virtual void computeTickLen(int numGrad, float &mainTickLen, float &secdTickLen) ;

  // Build arrow - The arrow is built under the node "group"
  virtual void buildArrow(float orig, float extr, SoGroup *group) ;

  // Build tick - The ticks are built under the node "group"
  virtual void buildTick(int numGrad, const float *xGrad, float tickLen, 
                         SoGroup *group) ;

  // Build grid lines - The grid lines are built under the node "group"
  virtual void buildGridLines(int numGrad, const float *xGrad, SoGroup *group) ;

  // Build title - The title is built under the node "group"
  void buildTitle(float xOrig, float xExtr, SoGroup *group) ;

  // Build graduations - The graduations are built under the node "group"
  // (used only by generalised, linear and polar linear axis)
  virtual void buildGrads(int numGrad, const float *xGrad, const char **gradStr, 
                          SoGroup *group) ;

  // Build multiplicative facot - The multiplicative factor is built under the node "group"
  // (used by log, linear, polar linear and polar log axis) 
  void buildMultFactorAtExtr(int tenPower, float xOrig, float xExtr, float &distAxis,
                             SoGroup *group) ;

  // Compute axis grad list 
  // (used by linear, angular, generalised, polar linear axis)
  void computeGradList(float xOrig, float xExtr, float step, int numAllGrad, 
                       const char** allGradStr, const float *allGradX,
                       int &numMainGrad, int &numSubGrad, char **mainGradStr,
                       float *mainGradX, float *secondaryGradX) ;

  // Allocate strings for graduations.
  static char **allocGradString(int numStr) ;

  // Overloaded methods
  virtual void addElementsAllCaches() ;
  virtual void preRebuild() ;

  //----------- These methods, types and vars are used ---------------------
  //--------------- only by log and polar log axis -------------------------

  enum LogGradType {
    TDECIMAL_TYPE,
    TDIGIT_TYPE,
    TPOWER_TYPE
  } ;

  // Convert log grad to string
  static void convertLogGradToStr(SbBool isMainGrad, LogGradType grad_type, int grad, 
                                  int ten_pow, char *string1, char *string2) ;
  
  // Compute min distance betwwen log graduations.
  static void computeLogGradMinDist(int numMainGrad, const float *mainGradX, 
                                    int numSecdGrad, const float *secdGradX, 
                                    float &min_grad_dist) ;
  
  // Compute decade list
  static void computeDecadeGradList(int numMainGrad, int **decades, 
                                    int &numDecades) ;

  // Compute width for a log grad text
  void computeLogGradWidth(const char *str, const char *tenPowStr,
                           float fontSize, float &width) ;

  // Compute max width for a list of log grad text
  void computeLogGradsMaxWidth(const char **strs, const char **tenPowStrs,
                               int numStr, float fontSize, float &width,
                               int &indexMaxWidth) ;

  // Draw a list of log graduations
  void drawLogGrad(float pyAtMax, float pyAtMin, float fontSize, 
                   LogGradType gradType, const float *gradX, 
                   int numGrad, const char **gradStr, const char **tenPowStr,
                   SoGroup *group) ;

  static char    *PStringToConcat ;
  static PiText  *PLogGradText ;

  //--------------------------- End log axis ------------------------------------

  // Computed axis attributes
  AxisAttr       axisAttr ;

 private:
  // Methods
  void buildTitleP(SbBool isTitleBuild, float xOrig, float xExtr, 
                   SoGroup *group, Plimit &limit) ;

  // Miscellaneous text attribute
  PbMiscTextAttr *m_miscTextAttr, m_defaultMiscTextAttr ;

  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_AXIS_  */

