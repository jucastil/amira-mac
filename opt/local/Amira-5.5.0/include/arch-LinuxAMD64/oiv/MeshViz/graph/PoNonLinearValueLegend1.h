/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_NON_LINEAR_VALUE_LEGEND1_
#define  _PO_NON_LINEAR_VALUE_LEGEND1_

#include <MeshViz/graph/PoAutoValueLegend.h>

#include <Inventor/fields/SoSFString.h>

/**
 * @DTEXT  Class to build a non linear legend (first representation).
 * 
 * @ingroup GraphLegend
 * 
 * @DESCRIPTION
 *    Each color box represents a value (or level) which is between two  
 *    consecutive values of a data mapping object or an isovalue list object.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoNonLinearValueLegend1 {
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
 *       @TR lessLevelString @TD "<"
 *       @TR greaterLevelString @TD ">"
 *       @TR valueSeparatorString @TD " _ "
 *       @TR lowerUndefString @TD "UNDEF>"
 *       @TR upperUndefString @TD "UNDEF>"
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pononlinearvaluelegend1.cat.html
 * 
 * 
 */
class MESHVIZ_API PoNonLinearValueLegend1 : public PoAutoValueLegend {

  SO_KIT_HEADER(PoNonLinearValueLegend1) ;


 public:

  /* Fields */

  /**
   * String used for the lowest level.
   */
  SoSFString  lessLevelString ;

  /**
   * String used for the highest level.
   */
  SoSFString  greaterLevelString ;

  /**
   * String separator used between two consecutive values.
   */
  SoSFString  valueSeparatorString ;  



  /* Methods */

  /**
   * Default constructor.
   */
  PoNonLinearValueLegend1() ; 

  /**
   * Constructor.
   */
  PoNonLinearValueLegend1(const SbVec2f &_start, const SbVec2f &_end) ;

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
  virtual void   setDefaultOnNonWritingFields() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  
  // Destructor
  virtual ~PoNonLinearValueLegend1() ;

 private:
  // Init method
  void init() ;

  // Sensors
  FieldSensorList m_fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     m_fieldList ;
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_NON_LINEAR_VALUE_LEGEND1_ */



