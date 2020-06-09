/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_CYLINDRICAL_BAR_
#define  _PO_CYLINDRICAL_BAR_

#include <Inventor/fields/SoSFFloat.h>

#include <MeshViz/graph/PoBar.h>

/**
 * @DTEXT  Class to build cylindrical bars.
 * 
 * @ingroup GraphHistogram
 * 
 * @DESCRIPTION
 *    Build cylindrical bars on 1D mesh (PoIrregularMesh1D or PoRegularMesh1D).
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
 * @FILE_FORMAT_DEFAULT
 *    PoCylindricalBar {
 *    @TABLE_FILE_FORMAT
 *       @TR colorBinding @TD INHERITED
 *       @TR yValuesIndex @TD 0
 *       @TR colorValuesIndex @TD 1
 *       @TR material @TD NULL
 *       @TR orientation @TD VERTICAL
 *       @TR threshold @TD 0.0
 *       @TR radius @TD 1.0
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pocylindricalbar.cat.html
 * 
 * 
 */

class MESHVIZ_API PoCylindricalBar : public PoBar {
  
  SO_KIT_HEADER(PoCylindricalBar) ;


 public:

  /**
   * Constructor.
   */
  PoCylindricalBar() ;

  /* Fields */

  /**
   * Defines the radius used for each cylindrical bar.
   */
  SoSFFloat radius ;

  /*---------------------------------------------------------------------------*/


 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  virtual ~PoCylindricalBar() ;
  // Destructor.

  // Overloaded methods
  virtual void rebuild() ;

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

#endif /*  _PO_CYLINDRICAL_BAR_ */

