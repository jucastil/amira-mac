/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_CIRCLE_ARC_
#define  _PO_CIRCLE_ARC_

#include <MeshViz/graph/PoGraphMaster.h>

/**
 * @DTEXT  Abstract class for 2D circle arc representation.
 * 
 * @ingroup GraphMisc
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZ_API PoCircleArc : public PoGraphMaster {

  SO_KIT_HEADER(PoCircleArc) ;
  
  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(circleArc) ;
  

 public:

  

  /**
   *  Type of the circle arc
   */
  enum ArcType {
    /**
     *  The arc is opened.
     */
    OPENED,       
    /**
     *  The arc is closed by its extremities.
     */
    END_CLOSE,    
    /**
     *  The arc is closed by the circle center.
     */
    CENTER_CLOSE  
  } ;

  /**
   * Indicates if the arc is opened, closed by its extremities or closed by its center.
   */
  SoSFEnum arcType ;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  // Conctructor
  PoCircleArc() ;

  // Destructor
  virtual ~PoCircleArc() ;

  // Methods
  virtual void   setDefaultOnNonWritingFields() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
 private:
  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;
} ;

/*----------------------------------------------------------------------------*/

#endif /*  _PO_CIRCLE_ARC_ */

