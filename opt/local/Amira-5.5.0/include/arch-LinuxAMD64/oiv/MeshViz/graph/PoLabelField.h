/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_LABEL_FIELD_
#define  _PO_LABEL_FIELD_

#include <MeshViz/graph/PoGraphMaster.h>

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/fields/SoMFString.h>

class PbNumericDisplayFormat ;


/**
 * @DTEXT  Class to build a label field.
 * 
 * @ingroup GraphScatter
 * 
 * @DESCRIPTION
 *    Class to build a label field in the plane XY. This class represents a set
 *    of 2D points annotated by a string and a value. 
 * 
 *    All numerical values (if there are visible) depend on the current numerical 
 *    display format. If the method setFormat(format) is called, the current numeric 
 *    display format is "format". Otherwise the current numeric display format is 
 *    specified in the current inherited state (cf property node 
 *    PoNumericDisplayFormat).
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoLabelField {
 *    @TABLE_FILE_FORMAT
 *       @TR point @TD 0 0
 *       @TR string @TD ""
 *       @TR value @TD 0
 *       @TR concatType @TD STRING_BEFORE_VALUE
 *       @TR fontSize @TD 1
 *       @TR justification @TD LEFT
 *       @TR verticalJustification @TD BASE
 *       @TR coordinateType @TD COORDINATE_IN_CURRENT_UNIT
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE polabelfield.cat.html
 * 
 * 
 */
class MESHVIZ_API PoLabelField : public PoGraphMaster {
  
  SO_KIT_HEADER(PoLabelField) ;
  
  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(transform) ;
  SO_KIT_CATALOG_ENTRY_HEADER(labelField) ;


 public:

  enum Justification {
    /**
     *  Left edges of all string are aligned.
     */
    LEFT,   
    /**
     *  Right edges of all string are aligned.
     */
    RIGHT,  
    /**
     *  Centered of all strings are aligned.
     */
    CENTER  
  } ;

  

  enum VerticalJustification {
    /**
     *  Strings are aligned on the top of its characters.
     */
    TOP,    
    /**
     *  Strings are aligned on the capital of its characters.
     */
    CAP,    
    /**
     *  Strings are aligned on the half of its characters.
     */
    HALF,   
    /**
     *  Strings are aligned on the base of its characters.
     */
    BASE,   
    /**
     *  Strings are aligned on the bottom of its characters.
     */
    BOTTOM  
  } ;



  /**
   *  Type of coordinates.
   */
  enum CoordinateType {
    /**
     *  Coordinates are in the current domain.
     */
    COORDINATE_IN_DOMAIN,       
    /**
     *  Coordinates are in current unit.
     */
    COORDINATE_IN_CURRENT_UNIT  
  } ;

  /**
   *  Type of string concatenation.
   */
  enum ConcatType {
    /**
     *  Strings are concatenated before values.
     */
    STRING_BEFORE_VALUE, 
    /**
     *  Values are concatenated before strings.
     */
    VALUE_BEFORE_STRING, 
    /**
     *  Strings are concatenated above values.
     */
    STRING_ABOVE_VALUE,  
    /**
     *  Values are concatenated above strings.
     */
    VALUE_ABOVE_STRING   
  } ;



  /* Fields */

  /**
   * List of points which are the coordinates of the strings.
   */
  SoMFVec2f  point ;

  /**
   * List of strings to display. To be displayed, the number of strings must be equal 
   * to the number of points of point.
   */
  SoMFString string ;

  /**
   * List of values to display. The values are converted into strings 
   * according to the current numerical display format. 
   * To be displayed, the number of values must be equal to the number 
   * of points of point.
   */
  SoMFFloat  value ;

  /**
   * Concatenation type between values and strings.
   */
  SoSFEnum   concatType ;

  /**
   * Font size for strings to display.
   */
  SoSFFloat  fontSize ;

  /**
   * Horizontal justification.
   */
  SoSFEnum   justification ;

  /**
   * Vertical justification.
   */
  SoSFEnum   verticalJustification ;

  /**
   * Type of coordinates.
   *   - coordinateType = COORDINATE_IN_DOMAIN: coordinates are expressed in
   *     the current domain (cf PoBase description),
   *   - coordinateType = COORDINATE_IN_CURRENT_UNIT: coordinates are expressed 
   *     in the current unit.
   *
   */
  SoSFEnum   coordinateType ;

  /* Methods */

  /**
   * Default constructor.
   */
  PoLabelField()
    { init(TRUE) ; }

  /**
   * Constructor.
   * [OIV-WRAPPER-ARG NO_WRAP{_point->Length},ARRAY,ARRAY,ARRAY,IN,IN,IN,IN]
   */
  PoLabelField(int numPoints, const SbVec2f *_point, const char **_string, 
               const float *_value, float _fontSize, 
               ConcatType type = STRING_BEFORE_VALUE, Justification _justification 
               = LEFT, VerticalJustification _verticalJustification = BASE)
    { init(FALSE, numPoints, _point, _string, _value, _fontSize, type, _justification, 
           _verticalJustification) ; } 

  /**
   * Sets a reference to a PbNumericDisplayFormat object for the numeric 
   * display format for the values. If this method is not called
   * (or called passing NULL as argument), this is the numeric display format 
   * defined in the current inherited state (defined with the property node 
   * PoNumericDisplayFormat) which is used.
   */
  void setFormat(PbNumericDisplayFormat *format) ;

  /**
   * Gets a reference to a PbNumericDisplayFormat object for the numeric 
   * display format for the values. 
   */
  const PbNumericDisplayFormat *getFormat() const ;

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
  // Destructor
  virtual ~PoLabelField() ;
  virtual void   setDefaultOnNonWritingFields() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;

  // Manage the connection with PbBase objects
  virtual void basicObjectChange(PbBase *basicObj) ;

  // Overloaded methods
  virtual void addElementsAllCaches() ;
  virtual void preRebuild() ;
  
 private:
  // Init method
  void init(SbBool isDefault, int numPoints=0, const SbVec2f *_point=NULL, 
            const char **_string=NULL, 
            const float *_value=NULL, float _fontSize=1.0, 
            ConcatType type = STRING_BEFORE_VALUE, Justification _justification 
            = LEFT, VerticalJustification _verticalJustification = BASE) ;

  // Numeric Display format
  PbNumericDisplayFormat *m_numericDisplayFormat, *m_defaultNumericDisplayFormat ;

  // Sensors
  FieldSensorList m_fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     m_fieldList ;

} ;

/*----------------------------------------------------------------------------*/

#endif /*  _PO_LABEL_FIELD_ */

