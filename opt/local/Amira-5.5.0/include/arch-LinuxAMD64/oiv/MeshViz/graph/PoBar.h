/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_BAR_
#define  _PO_BAR_

#include <MeshViz/graph/PoChart.h>

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>

/**
 * @DTEXT  Abstract base class for bar representations.
 * 
 * @ingroup GraphHistogram
 * 
 * @DESCRIPTION
 *    This is the abstract base class for building bars on 1D mesh 
 *    (PoIrregularMesh1D or PoRegularMesh1D).
 *    The orientation of the bars can be horizontal or vertical.
 *    The abscissas (ordinates if HORIZONTAL orientation) of the bars are given 
 *    by the geometry of the current mesh 1D, and the height (width if HORIZONTAL
 *    orientation) are given by one of the value-set of the current mesh 1D 
 *    specified by the field yValuesIndex.
 *    A threshold defines the origin of the bars. This value is either
 *    an ordinate (VERTICAL orientation) or an abscissas (HORIZONTAL orientation).
 *    This class also takes into account of the current mesh 1D hints 
 *    (PoMesh1DHints) and the current mesh 1D filter (PoMesh1DFilter) 
 *    to filter the geometry of the current mesh 1D .
 * 
 *    The interpretation of colorBinding is the following :
 * 
 *    - INHERITED: All bars are colored with the same inherited color.
 * 
 *    - PER_PART or PER_VERTEX : A color is used for each bar.
 * 
 * 
 */

class MESHVIZ_API PoBar : public PoChart {
  
  SO_KIT_HEADER(PoBar) ;

  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(bar) ;


 public:

  /**
   *  Orientation of the bars.
   */
  enum Orientation {
    HORIZONTAL,
    VERTICAL
  } ;



  /* Fields */

  /**
   * Defines the orientation of the bars.
   */
  SoSFEnum orientation ;

  /**
   * Defines the threshold of the origin of the bars. This value is
   * either an ordinate (VERTICAL orientation) or an abscissas 
   * (HORIZONTAL orientation).
   */
  SoSFFloat threshold ;

  /*----------------------------------------------------------------------------*/


 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  PoBar() ;
  // Constructor.

  virtual ~PoBar() ;
  // Destructor.

  // Overloaded methods
  virtual void addElementsAllCaches() ;
  virtual void preRebuild() ;

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

#endif /*  _PO_BAR_ */

