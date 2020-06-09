/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_GEN_AXIS_
#define  _PO_GEN_AXIS_

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoMFString.h>

#include <MeshViz/graph/PoCartesianAxis.h>

/**
 * @DTEXT  Class to build a generalized axis.
 * 
 * @ingroup GraphAxis
 * 
 * @DESCRIPTION
 *    This class builds a generalized axis. This axis will be generated between the point 
 *    start to the point end. The graduations will be in the plane given by the user (cf 
 *    field PoCartesianAxis::type). A generalized axis is an axis with strings for graduations.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoGenAxis {
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
 *       @TR gradList @TD ""
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pogenaxis.cat.html
 * 
 * 
 */
class MESHVIZ_API PoGenAxis : public PoCartesianAxis {

  SO_KIT_HEADER(PoGenAxis) ;


 public:

  /* Fields */

  /**
   * List of graduations.
   */
  SoMFString gradList ;

  /**
   * Default constructor.
   */
  PoGenAxis()
    { init(TRUE, SbVec3f(0.,0.,0.), 0., XY, NULL, 0) ; }

  /**
   * Constructor of a generalized axis with graduations _gradList
   * [OIV-WRAPPER-ARG IN,IN,IN,ARRAY,CAST_TO{short}&NO_WRAP{_gradList.Length}]
   */
  PoGenAxis(const SbVec3f &_start, float _end, PoCartesianAxis::Type _type, const char **_gradList,
            short numGrad)
    { init(FALSE, _start, _end, _type, _gradList, numGrad) ; }

  /* Methods */

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void   rebuild() ;

  /*----------------------------------------------------------------------------*/


 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
 protected:
  // Destructor
  virtual ~PoGenAxis() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void   setDefaultOnNonWritingFields() ;
  // Methods

 private:
  // Init method
  void init(SbBool isDefault, const SbVec3f &start, float end, 
            Type typeAxis, const char **grdList, short numGrad) ;

  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_GEN_AXIS_ */

