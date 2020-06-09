/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_LOG_AXIS_
#define  _PO_LOG_AXIS_


#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFUShort.h>
#include <Inventor/fields/SoSFString.h>


#include <MeshViz/graph/PoCartesianAxis.h>

/**
 * @DTEXT  Class to build a logarithmic axis.
 * 
 * @ingroup GraphAxis
 * 
 * @DESCRIPTION
 *    This class builds a logarithmic axis. This axis will be generated between the point 
 *    start to the point end. The graduations will be in the plane given by the user (cf 
 *    type field). For instance, it can be used for building a logarithmic axis in the plane 
 *    XY, with the first decade graduation being 10E3 and the last decade graduation 
 *    being 108 (graduation values are: 10E3, 10E4, 10E5, ...,10E8): start = (3, 0, 0), end = 8 
 *    and plane = XY.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoLogAxis {
 *    @TABLE_FILE_FORMAT
 *       @TR gradVisibility @TD VISILITY_DEPEND
 *       @TR gradPosition @TD GRAD_DEPEND
 *       @TR gradPath @TD PATH_DEPEND
 *       @TR gradFontName @TD ""
 *       @TR gradFontSize @TD 0
 *       @TR gradDistAxis @TD 0
 *       @TR gradAddStringVisibility @TD FALSE
 *       @TR gradAddString @TD ""
 *       @TR marginType @TD REL_MARGIN
 *       @TR marginStart @TD 0
 *       @TR marginEnd @TD 0
 *       @TR titleVisibility @TD VISILITY_DEPEND
 *       @TR titlePosition @TD TITLE_DEPEND
 *       @TR titlePath @TD PATH_DEPEND
 *       @TR titleFontName @TD ""
 *       @TR titleFontSize @TD 0
 *       @TR titleDistAxis @TD 0
 *       @TR titleString @TD ""
 *       @TR gridVisibility @TD VISILITY_DEPEND
 *       @TR gridLengthGradSide @TD 0
 *       @TR gridLengthGradOtherSide @TD 1
 *       @TR arrowVisibility @TD VISIBILITY_DEPEND
 *       @TR arrowHeight @TD 0.03
 *       @TR arrowLength @TD 0.05
 *       @TR tickVisibility @TD VISIBILITY_DEPEND
 *       @TR tickPosition @TD TICK_GRAD_SIDE
 *       @TR tickMainLength @TD 0
 *       @TR tickSubLength @TD 0
 *       @TR tickSubDef @TD PERIOD_MAIN_TICK
 *       @TR tickNumOrPeriod @TD 1
 *       @TR tickFirstGrad @TD 1
 *       @TR tickLastGrad @TD 1
 *       @TR reverseFlag @TD AXIS_REVERSE_DEPEND
 *       @TR start @TD 0 0 0
 *       @TR end @TD 1
 *       @TR type @TD XY
 *       @TR decadeListDef @TD DECADE_LIST_AUTO
 *       @TR decadeList @TD 2
 *       @TR tenPowerRep @TD TEN_POWER_POW10
 *       @TR decadeRep @TD DECADE_NONE
 *       @TR decadeFontName @TD ""
 *       @TR decadeFontSize @TD 0
 *       @TR multFactorPosition @TD MULT_FACTOR_END
 *       @TR multFactorDistAxis @TD 0
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pologaxis.cat.html
 * 
 * 
 */
class MESHVIZ_API PoLogAxis : public PoCartesianAxis {

  SO_KIT_HEADER(PoLogAxis) ;

  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(multFactorSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(multFactorApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(multFactor) ;

  SO_KIT_CATALOG_ENTRY_HEADER(decadeTextSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(decadeTextApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(decadeText) ;


 public:

  /**
   *  Decade list computed automatically or given by the user.
   */
  enum DecadeListDef {
    /**
     *  The list of decade graduations is automatically computed.  
     */
    DECADE_LIST_AUTO,    
    /**
     *  The list of decade graduations is given by the user. 
     */
    DECADE_LIST_NON_AUTO 
  } ;

  /**
   *  Type of presentation of the power of ten.
   */
  enum TenPowGradRep {
    /**
     *  The graduations are specified in powers of ten.
     */
    TEN_POWER_POW10,    
    /**
     *  The graduations are specified in decimals.
     */
    TEN_POWER_DECIMAL,  
    /**
     *  The graduations are specified in powers of ten or in decimals, 
     */
    TEN_POWER_AUTO      
    /**
     *  depending on the axis range.
     */
                        
  } ;

  /**
   *  Type of presentation of the axis decades.
   */
  enum DecadeRep {
    /**
     *  No decade graduations are displayed.
     */
    DECADE_NONE,         
    /**
     *  Decade graduations are displayed as power of ten graduations.
     */
    DECADE_AS_TEN_POWER, 
    /**
     *  Decade graduations are displayed in decimals.
     */
    DECADE_DECIMAL,      
    /**
     *  Decade graduations are displayed using a digit from 2 to 9  
     */
    DECADE_DIGIT,        
    /**
     *  giving the multiple of the power of ten.
     */
                         
    /**
     *  Automatic mode, one of the three previous type is used 
     */
    DECADE_AUTO          
    /**
     *  depending on the axis range.
     */
                         
  } ;

  /**
   *  Type of position of the multiplicative factor.
   */
  enum MultFactorPosition {
    /**
     *  The multiplicative factor is at the start of the axis.
     */
    MULT_FACTOR_START,   
    /**
     *  The multiplicative factor is at the end of the axis.
     */
    MULT_FACTOR_END,     
    /**
     *  The multiplicative factor is at the start and at the end of the axis.
     */
    MULT_FACTOR_EXTR,    
    /**
     *  The multiplicative factor is at the graduations of the axis.
     */
    MULT_FACTOR_GRAD     
  } ;



  /* Fields */

  /**
   * List of graduations between two power of ten graduations (decade 
   * graduations). For each integer value i of decadeList, 2 <= i <= 9, only the 8 first 
   * values of decadeList are used. This field is used to build the axis only if 
   * decadeListDef = DECADE_LIST_NON_AUTO.
   */
  SoMFUShort decadeList ;

  /**
   * Specifies if the list of decade graduations is given by the user or is 
   * automatically computed.
   */
  SoSFEnum   decadeListDef ;

  /**
   * Defines the representation of power of ten graduations.
   */
  SoSFEnum   tenPowerRep ;

  /**
   * Defines the representation of the decade graduations between two power of ten 
   * graduations.
   */
  SoSFEnum   decadeRep ;

  /**
   * Decade font name. If the font is equal to its default value, the font used is the 
   * font of the current miscellaneous text attributes (cf PoAxis description).
   */
  SoSFString decadeFontName ;

  /**
   * Decade graduations font size. If this value is <= 0, the font size is fixed at 0.04 
   * if the graduations do not cross each other. This value is a percentage of the 
   * current domain (cf PoBase description).
   */
  SoSFFloat  decadeFontSize ;

  /**
   * Position of the multiplicative factor.
   */
  SoSFEnum   multFactorPosition ;

  /**
   * Distance from the multiplicative factor to the axis. 
   * This value is a percentage of the current domain 
   * (cf PoBase description). If this value is <= 
   * 0, the distance is automatically calculated.
   */
  SoSFFloat  multFactorDistAxis ;

  /**
   * Constructor.
   */
  PoLogAxis()
    { init(TRUE, SbVec3f(0.,0.,0.), 1, XY, DECADE_LIST_AUTO, NULL, 0) ; }

  /**
   * Constructor.
   * [OIV-WRAPPER-ARG IN,IN,IN,IN,ARRAY,NO_WRAP{_decadeList->Length}]
   */
   PoLogAxis(const SbVec3f &_start, float _end, PoCartesianAxis::Type _type, 
            DecadeListDef _decadeListDef = DECADE_LIST_AUTO,
            const unsigned short *_decadeList = NULL, short _numDecade = 0) 
    { init(FALSE, _start, _end, _type, _decadeListDef, _decadeList, _numDecade) ; }



  /* Methods */

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void   rebuild() ;

  /**
   * Returns the current logarithmic graduations attributes (those computed can be 
   * different from the associated fields).
   * [OIVJAVA-WRAPPER PACK{GradAttributes}]
   */
  void getLogGrad(unsigned short &numDecade, unsigned short decadeList[8],
                  TenPowGradRep &tenPowerRep, DecadeRep &decadeRep, 
                  SbString &decadeFontName, float &decadeFontSize) const ;

  /**
   * Returns the current multiplicative factor attributes (those computed can be 
   * different from the associated fields).
   * [OIVJAVA-WRAPPER PACK{MultFactor}]
   */
  void getMultFactor(MultFactorPosition &position, float &distAxis) const ;

  /*----------------------------------------------------------------------------*/


 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

  struct MultFactor {
    MultFactorPosition position ;
    float              distAxis ;
  } ;
  
  struct Decade {
    DecadeRep       rep ;
    DecadeListDef   listDef ;
    int             *gradList ;
    int             number ;
    SbString        fontName ;
    float           fontSize ;
  } ;

 protected:
  struct LogAxisAttr {
    MultFactor      multFactor ;
    TenPowGradRep   tenPowerRep ;
    Decade          decadeGrad ;
  } ;
  // Log axis attr

  // Methods
  // Destructor
  virtual ~PoLogAxis() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void   setDefaultOnNonWritingFields() ;

  // Save all axis attributes which can be modified by MeshViz.
  virtual void saveAxisAttr() ;

 private:
  // Init method
  void init(SbBool isDefault, const SbVec3f &start, float end, Type typeAxis, 
            DecadeListDef decadeListDef, const unsigned short *decadeList, 
            short numDecade) ;

  // Build log graduations - The graduations (main grad and decades grad)
  // are built under the nodes mainGroup and secondaryGroup.
  void buildLogGrad(int numMainGrad, float *mainGradX, int numSecdGrad, 
                    float *secdGradX, int numDecades, int *decades, int firstDecInd,
                    SoGroup *mainGroup, SoGroup *secondaryGroup) ;

  // Compute log grad font size
  void computeLogGradFontSize(int numMainGrad, const char **main_str, 
                              const char **main_ten_pow_str, int numSecdGrad, 
                              const char **secd_str, const char **secd_ten_pow_str, 
                              float min_grad_dist, SbBool main_grad_pres_auto,
                              float &main_font_size, float &secd_font_size) ;

  // Computed logarithmic axis attributes
  LogAxisAttr  logAxisAttr ;

  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_LOG_AXIS_ */


