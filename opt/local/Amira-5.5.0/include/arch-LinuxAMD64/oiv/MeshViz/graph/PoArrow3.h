/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_ARROW3_
#define  _PO_ARROW3_

#include <MeshViz/graph/PoGraphMaster.h>


#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFVec3f.h>


/**
 * @DTEXT  Class to build a 3D arrow.
 * 
 * @ingroup GraphMisc
 * 
 * @DESCRIPTION
 *    This class builds a 3D arrow. The arrow is defined by a 
 *    point list. The start pattern and the end pattern can be parameterized.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoArrow3 {
 *    @TABLE_FILE_FORMAT
 *       @TR point @TD 0 0 0
 *       @TR startPatternType @TD NO_PATTERN
 *       @TR endPatternType @TD NO_PATTERN
 *       @TR patternWidth @TD 0.05
 *       @TR patternHeight @TD 0.03
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE poarrow3.cat.html
 * 
 * 
 */
class MESHVIZ_API PoArrow3 : public PoGraphMaster {
  
  SO_KIT_HEADER(PoArrow3) ;
  
  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(bodySep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(bodyApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(body)    ;

  SO_KIT_CATALOG_ENTRY_HEADER(startSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(startApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(start)    ;

  SO_KIT_CATALOG_ENTRY_HEADER(endSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(endApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(end)    ;


 public:

  /**
   *  Type of pattern at the arrow extremities.
   */
  enum PatternType {
    /**
     *  No pattern at the arrow extremity.
     */
    NO_PATTERN,        
    /**
     *  Direct triangle at the arrow extremity.
     */
    DIRECT_TRIANGLE,   
    /**
     *  Indirect triangle at the arrow extremity.
     */
    INDIRECT_TRIANGLE, 
    /**
     *  Rectangle at the arrow extremity.
     */
    RECTANGLE          
  } ;

  /* Fields */

  /**
   * Point list of the arrow.
   */
  SoMFVec3f point ;

  /**
   * Defines the start arrow pattern type.
   */
  SoSFEnum  startPatternType ;

  /**
   * Defines the end arrow pattern type.
   */
  SoSFEnum  endPatternType ;

  /**
   * Define the width of the start and end arrow pattern. It is
   * given in the normalized space [0-1]x[0-1]x([0-1]) defined by the 
   * current domain (cf PoBase description).
   */
  SoSFFloat patternWidth ;

  /**
   * Define the height of the start and end arrow pattern. It is
   * given in the normalized space [0-1]x[0-1]x([0-1]) defined by the 
   * current domain (cf PoBase description).
   */
  SoSFFloat patternHeight ;



  /* Methods */

  /**
   * Default constructor.
   */
  PoArrow3()
    { init(TRUE) ; }

  /**
   * Constructor.
   * [OIV-WRAPPER-ARG NO_WRAP{_point->Length},ARRAY,IN,IN,IN,IN]
   */
  PoArrow3(int numPoints, const SbVec3f *_point, PatternType startType = NO_PATTERN,
           PatternType endType = NO_PATTERN, float _patternWidth = 0.05f, 
           float _patternHeight = 0.03f)
    { init(FALSE, numPoints, _point, startType, endType, _patternWidth, _patternHeight) ; } 

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
  virtual ~PoArrow3() ;
  virtual void   setDefaultOnNonWritingFields() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;

 private:
  // Init method
  void init(SbBool isDefault, int numPoints = 0, const SbVec3f *_point = NULL, 
            PatternType startType = NO_PATTERN,  PatternType endType = NO_PATTERN, 
            float _patternWidth = 0.05f, float _patternHeight = 0.03f) ;
  
  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;

} ;

/*----------------------------------------------------------------------------*/

#endif /*  _PO_ARROW3_ */

