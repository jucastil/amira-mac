/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_HIGH_LOW_CLOSE_
#define  _PO_HIGH_LOW_CLOSE_

#include <MeshViz/graph/PoGraphMaster.h>


#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoMFFloat.h>


/**
 * @DTEXT  Class to build a high low close representation.
 * 
 * @ingroup GraphScatter
 * 
 * @DESCRIPTION
 *    Class to build a high low close representation in the plane XY.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoHighLowClose {
 *    @TABLE_FILE_FORMAT
 *       @TR valuesX @TD 0
 *       @TR valuesHigh @TD 0
 *       @TR valuesLow @TD 0
 *       @TR valuesClose @TD 0
 *       @TR horCloseBarPosition @TD LEFT
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pohighlowclose.cat.html
 * 
 * 
 */
class MESHVIZ_API PoHighLowClose : public PoGraphMaster {
  
  SO_KIT_HEADER(PoHighLowClose) ;
  
  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(highLowClose) ;
  

 public:

  

  /**
   *  Position of the horizontal close bar.
   */
  enum HorCloseBarPosition {
    /**
     *  The horizontal close bar is on the left of the vertical close bar.
     */
    LEFT,   
    /**
     *  The horizontal close bar is on the middle of the vertical close bar.
     */
    MIDDLE, 
    /**
     *  The horizontal close bar is on the right of the vertical close bar.
     */
    RIGHT   
  } ;



  /* Fields */

  /**
   * List of abscissas. Must have the same size than the other "values" fields.
   */
  SoMFFloat valuesX ;

  /**
   * List of high values. Must have the same size than the other "values" fields.
   */
  SoMFFloat valuesHigh ;

  /**
   * List of low values. Must have the same size than the other "values" fields.
   */
  SoMFFloat valuesLow ;

  /**
   * List of close values. Must have the same size than the other "values" fields.
   */
  SoMFFloat valuesClose ;

  /**
   * Position of the horizontal close bar in relation to the vertical line.
   */
  SoSFEnum  horCloseBarPosition ;



  /* Methods */

  /**
   * Default constructor.
   */
  PoHighLowClose()
    { init(TRUE) ; }

  /**
   * Constructor.
   */
  PoHighLowClose(int numValues, const float *x, const float *high,
                 const float *low, const float *close)
    { init(FALSE, numValues, x, high, low, close) ; }

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
  virtual ~PoHighLowClose() ;
  virtual void   setDefaultOnNonWritingFields() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;

 private:
  // Init method
  void init(SbBool isDefault, int numValues=0, const float *x=NULL, 
            const float *high=NULL, const float *low=NULL, const float *close=NULL) ;

  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;



} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_HIGH_LOW_CLOSE_ */

