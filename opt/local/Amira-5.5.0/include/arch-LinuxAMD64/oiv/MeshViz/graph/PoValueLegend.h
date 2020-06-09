/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_VALUE_LEGEND_
#define  _PO_VALUE_LEGEND_

#include <MeshViz/graph/PoLegend.h>

#include <MeshViz/graph/PbNumericDisplayFormat.h>
#include <MeshViz/graph/PbDataMapping.h>

#include <Inventor/fields/SoSFUShort.h>
#include <Inventor/fields/SoSFString.h>

class PbIsovaluesList ;

/**
 * @DTEXT  Abstract class for values legend.
 * 
 * @ingroup GraphLegend
 * 
 * @DESCRIPTION
 *    This class handles a period of values, a first value and a last value 
 *    to be displayed in a legend, specific strings.
 * 
 *    Values of the legends depend on :
 *      - the current list of isovalues only if this list exists. In this case,
 *        values of the legend are the values defined by the current list of isovalues.
 *        The current data mapping is only used for coloring boxes of the legend.
 *      - the current data mapping only if the current list of isovalues does no exist.
 *        In this case, the values of the legend are the values of the current data 
 *        mapping. If the current data mapping is linear, about ten values are computed.
 *        If the current data mapping is defined by a function or it does not exist, the 
 *        list of legend values is empty.
 *
 * 
 *    If setIsovaluesList(isovaluesList) method is called with "isovaluesList" 
 *    derived from PbIsovaluesList, the current isovalues list is "isovaluesList".
 *    Otherwise the current isovalues list is specified in the current inherited state
 *    (cf PoIsovaluesList property node).
 *    The current isovalues list does not exist if setIsovaluesList() method is not 
 *    called and no PoIsovaluesList node is traversed before in the scene graph.
 * 
 *    If setDataMapping(dataMapping) method is called with "dataMapping" 
 *    derived from PbDataMapping, the current data mapping is "dataMapping".
 *    Otherwise the current data mapping is specified in the current inherited state
 *    (cf property node PoDataMapping and its derived classes).
 *    The current data mapping does not exist if setDataMapping() method is not 
 *    called and no PoDataMapping node is traversed before in the scene graph.
 * 
 *    Values format depends on the current numerical display format.
 *    If the method setFormat(format) is called, the current numerical display 
 *    format is "format". Otherwise the current numerical display format 
 *    is specified in the current inherited state (cf property node 
 *    PoNumericDisplayFormat).
 * 
 */

class MESHVIZ_API PoValueLegend : public PoLegend {

  SO_KIT_HEADER(PoValueLegend) ;

  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(multFactorSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(multFactorApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(multFactor) ;


 public:

  /* Fields */

  /**
   * String indicating the upper undefined level. 
   * (Corresponds to the maximum threshold of data 
   * mapping. Not used if no data mapping object is 
   * specified or if the maximum threshold is disabled).
   */
  SoSFString upperUndefString ;

  /**
   * String indicating the lower undefined level.
   * (Corresponds to the minimum threshold of data 
   * mapping Not used if no data mapping object is 
   * specified or if the minimum threshold is disabled).
   */
  SoSFString lowerUndefString ;

  /**
   * Period to display the values in the legend.
   */
  SoSFUShort periodValue ;

  /**
   * Number of the first value to display.
   */
  SoSFUShort firstValue ;

  /**
   * Number of the last value to display.
   */
  SoSFUShort lastValue ;



  /* Methods */

  /**
   * Sets a reference to a PbIsovaluesList object. A PbIsovaluesList object 
   * defines an isovalue list used for the legend values.
   * If this method is not called (or called passing NULL as argument), 
   * this is the isovalue list defined in the current inherited state 
   * (defined with the property node PoIsovaluesList) which is used.
   */
  void setIsovaluesList(PbIsovaluesList *isovaluesList) ;

  /**
   * Gets a reference to a PbIsovaluesList object. 
   */
  const PbIsovaluesList* getIsovaluesList() const ;

  /**
   * Sets a reference to a PbDataMapping object to the association color-values.
   * If this method is not called (or called passing NULL as argument), this is 
   * the data mapping defined in the current inherited state (defined with the 
   * property node PoDataMapping and its derived classes) which is used.
   */
  void setDataMapping(PbDataMapping *dataMapping) ;

  /**
   * Gets a reference to a PbDataMapping object to the association color-values.
   */
  const PbDataMapping *getDataMapping() const ;

  /**
   * Sets a reference to a PbNumericDisplayFormat object for the numerical 
   * display format of the legend values. If this method is not called
   * (or called passing NULL as argument), this is the numerical display format 
   * defined in the current inherited state (defined with the property node 
   * PoNumericDisplayFormat) which is used.
   */
  void setFormat(PbNumericDisplayFormat *format) ;

  /**
   * Gets a reference to a PbNumericDisplayFormat object for the numerical 
   * display format of the legend values. 
   */
  const PbNumericDisplayFormat *getFormat() const ;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  // Box representation definition
  // This structure is the representation of one box
  struct BoxRepresentation {
    int      numColors ;          // = 0 no color, = -1 inherited color
    SbColor  colorList[2] ; 
    float    value ;
    float    value2 ;             // Use for interval legend
    float    transparency  ;
    float    transparency2 ;      // Use for interval legend  
    SbBool   isTransparency ;
    SbString string ;

    float    *percentPerColor ;   // Not used for the moment
    SbBool   isColorShaded ;      // Not used for the moment
  } ;

  enum LegendType {
    DATA_MAPPING_LEGEND,
    ISOVALUE_LEGEND,
    NO_LEGEND
  } ;

  enum LegendOrientation {
    HORIZONTAL_LEGEND,
    VERTICAL_LEGEND
  } ;
  
  enum MultFactorPosition {
    MULT_FACTOR_POS_UP_MIDDLE,
    MULT_FACTOR_POS_RIGHT_MIDDLE,
    MULT_FACTOR_POS_DOWN_MIDDLE
  } ;

  // Constructor
  PoValueLegend() ;

  // Methods
  virtual void   setDefaultOnNonWritingFields() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  
  // Destructor
  virtual ~PoValueLegend() ;

  // Manage the connection with PbBase objects
  virtual void basicObjectChange(PbBase *basicObj) ;

  // Compute boxes representation
  void computeBoxColors(int index, SbBool isIntervalLegend) ;

  // Compute undef box representation
  // lowerUndefIndex = -1 no lower undef representation
  // upperUndefIndex = -1 no upper undef representation
  void computeUndefBoxRepresentation(int lowerUndefIndex, int upperUndefIndex) ;

  // Compute list of values
  void computeValuesList() ;

  // Create box representation list
  void newBoxRepresentationList(int num) ;

  // Delete box representation list
  void deleteBoxRepresentationList() ;

  // Overloaded methods
  virtual void addElementsAllCaches() ;
  virtual void preRebuild() ;

  // List of boxes representation
  BoxRepresentation *m_boxRepresentationList ;
  int               m_numBoxRepresentation ;
  
  // List of values to display (this list is computed thanks to
  // data mapping and isovalues list).
  float      *m_valuesList ;
  int        m_numberValues ;
  SbBool     m_isLowerUndef, m_isUpperUndef ;
  LegendType m_legendType ; 
  
  // DataMapping Type
  PbDataMapping::ClassType m_dataMappingType ;
  float                    m_transparencyDeletedParts ;
  
  // Orientation of the legend (HORIZONTAL or VERTICAL)
  LegendOrientation m_legendOrientation ;
  
  // Multiplicative factor in the legend
  SbBool    m_isMultFactor ;
  SbString  m_multFactorExpString ;   // Exponent of the mult factor
  float     m_multFactorWidth ;

 private:
  // Default numeric format
  PbNumericDisplayFormat m_defaultNumericFormat ;

  // Numeric diplay format 
  PbNumericDisplayFormat *m_numericDisplayFormat ;

  // Data mapping
  PbDataMapping *m_dataMap ;

  // Isovalue list
  PbIsovaluesList *m_isovalList ;

  // Sensors
  FieldSensorList m_fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     m_fieldList ;
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_VALUE_LEGEND_ */




