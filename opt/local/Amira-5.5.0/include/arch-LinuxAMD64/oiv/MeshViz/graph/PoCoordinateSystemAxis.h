/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_COORDINATE_SYSTEM_AXIS_
#define  _PO_COORDINATE_SYSTEM_AXIS_

#include <MeshViz/graph/PoGraphMaster.h>

#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFString.h>

/**
 * @DTEXT  Class for a 3D axes system.
 * 
 * @ingroup GraphAxis
 * 
 * @DESCRIPTION
 *    Class to build an axes system. It is composed of three vectors, each having a title 
 *    string at its extremity. A multiplicative factor translates each title string according 
 *    to each vector length and another one defines the arrow length of vectors relative 
 *    to the vector length.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoCoordinateSystemAxis {
 *    @TABLE_FILE_FORMAT
 *       @TR start @TD 0 0 0
 *       @TR end @TD 1 1 1
 *       @TR xTitle @TD "X"
 *       @TR yTitle @TD "Y"
 *       @TR zTitle @TD "Z"
 *       @TR arrowLengthFactor @TD 0.05
 *       @TR titleTranslationFactor @TD 0
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pocoordinatesystemaxis.cat.html
 * 
 * 
 */
class MESHVIZ_API PoCoordinateSystemAxis : public PoGraphMaster {
  
  SO_KIT_HEADER(PoCoordinateSystemAxis) ;
  
  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(xArrow) ;
  SO_KIT_CATALOG_ENTRY_HEADER(yArrow) ;
  SO_KIT_CATALOG_ENTRY_HEADER(zArrow) ;

  SO_KIT_CATALOG_ENTRY_HEADER(xTitleTextSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(xTitleTextApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(xTitleText)    ;

  SO_KIT_CATALOG_ENTRY_HEADER(yTitleTextSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(yTitleTextApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(yTitleText)    ;

  SO_KIT_CATALOG_ENTRY_HEADER(zTitleTextSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(zTitleTextApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(zTitleText)    ;


 public:

  /* Fields */

  /**
   * Start of the coordinate system.  (0,0,0) by default.
   */
  SoSFVec3f  start ; 

  /**
   * End of the coordinate system. (1,1,1) by default.
   */
  SoSFVec3f  end ;

  /**
   * String to be displayed at the end of the X coordinate vector. "X" by default.
   */
  SoSFString xTitle ;

  /**
   * String to be displayed at the end of the Y coordinate vector. "Y" by default.
   */
  SoSFString yTitle ;

  /**
   * String to be displayed at the end of the Z coordinate vector. "Z" by default.
   */
  SoSFString zTitle ;

  /**
   * Arrow length scale factor. This is the ratio between the length of the arrow and 
   * the length of one of the vectors. This value is normally less than 1. 0.05 by default. 
   */
  SoSFFloat  arrowLengthFactor ;

  /**
   * Translation factor of the titles (as function of the length of each vector). 0 by default. 
   */
  SoSFFloat  titleTranslationFactor ;



  /* Methods */

  /**
   * Default constructor.
   */
  PoCoordinateSystemAxis()
    { init(TRUE, SbVec3f(0.0, 0.0, 0.0), SbVec3f(1.0, 1.0, 1.0), NULL, NULL, NULL, 0.05F,
           0.0F) ; }

  /**
   * Constructor.
   */
  PoCoordinateSystemAxis(const SbVec3f &_start, const SbVec3f &_end, const char *_xTitle, 
                         const char *_yTitle, const char *_zTitle, float _arrowLengthFactor, 
                         float _titleTranslationFactor)
    { init(FALSE, _start, _end, _xTitle, _yTitle, _zTitle, _arrowLengthFactor, 
           _titleTranslationFactor) ; } 

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
  virtual ~PoCoordinateSystemAxis() ;
  virtual void   setDefaultOnNonWritingFields() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;

 private:
  // Init method
  void init(SbBool isDefault, const SbVec3f &_start, const SbVec3f &_end, 
            const char *_xTitle, const char *_yTitle, const char *_zTitle, 
            float _arrowLengthFactor, float _titleTranslationFactor) ;
  
  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;

} ;

/*----------------------------------------------------------------------------*/

#endif /*  _PO_COORDINATE_SYSTEM_AXIS_ */

