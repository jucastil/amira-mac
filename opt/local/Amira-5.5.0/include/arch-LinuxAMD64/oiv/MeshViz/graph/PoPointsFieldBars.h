/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_POINTS_FIELD_BARS_
#define  _PO_POINTS_FIELD_BARS_

#include <MeshViz/graph/PoGraphMaster.h>

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFVec3f.h>

class PbDataMapping ;

/**
 * @DTEXT  Class to build a points field bars.
 * 
 * @ingroup GraphHistogramScatter
 * 
 * @DESCRIPTION
 *    Class to build parallelepipeds based on a point field. This class generates a set of 
 *    parallelepipeds where the bases are on the plane XY and the heights are given by 
 *    the altitude for each point on the point field. The parallelepipeds are colored as a 
 *    function of values for each point.
 * 
 *    Colors of the bars depend on the current data mapping. 
 *    If the method setDataMapping(dataMapping) is called, the 
 *    current data mapping is "dataMapping". Otherwise the current data mapping 
 *    is specified in the current inherited state (cf property node PoDataMapping 
 *    and its derived classes). If there is no current data-mapping
 *    (i.e setDataMapping() not called and no PoDataMapping node traversed before 
 *    in the scene graph), all bars get the same color which is the inherited color.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoPointsFieldBars {
 *    @TABLE_FILE_FORMAT
 *       @TR point @TD 0 0 0
 *       @TR value @TD 0.0
 *       @TR width @TD 1.0
 *       @TR height @TD 1.0
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE popointsfieldbars.cat.html
 * 
 * 
 */
class MESHVIZ_API PoPointsFieldBars : public PoGraphMaster {
  
  SO_KIT_HEADER(PoPointsFieldBars) ;
  
  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(pointsFieldBars)    ;


 public:

  /* Fields */

  /**
   * List of points for parallelepipeds. point[i][2] is the altitude of the i-th 
   * parallelepiped.
   */
  SoMFVec3f point;

  /**
   * Values for each point. If value.getNum() != point.getNum(), the 
   * parallelepipeds have all the same color, that is the inherited color.
   */
  SoMFFloat value ;

  /**
   * Width of parallelepipeds.
   */
  SoSFFloat width ;

  /**
   * Height of parallelepipeds.
   */
  SoSFFloat height ;

  /* Methods */

  /**
   * Default constructor.
   */
  PoPointsFieldBars()
    { init(TRUE) ; }

  /**
   * Constructor.
   * [OIV-WRAPPER-ARG NO_WRAP{_point->Length},ARRAY,ARRAY,IN,IN]
   */
  PoPointsFieldBars(int numPoints, const SbVec3f *_point, const float *_value,
                    float _width, float _height)
    { init(FALSE, numPoints, _point, _value, _width, _height) ; } 

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void rebuild() ;

  /**
   * Sets a reference to a PbDataMapping object to the association color-value.
   * If this method is not called (or called passing NULL as argument), 
   * this is the data mapping defined in the current inherited state 
   * (defined with the property node PoDataMapping and its derived classes) which 
   * is used.
   */
  void setDataMapping(PbDataMapping *dataMapping) ;

  /**
   * Gets a reference to a PbDataMapping object to the association color-value.
   */
  const PbDataMapping* getDataMapping() const ;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  // Methods
  // Destructor
  virtual ~PoPointsFieldBars() ;
  virtual void   setDefaultOnNonWritingFields() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;

  // Manage the connection with PbBase objects
  virtual void basicObjectChange(PbBase *basicObj) ;

  // Overloaded methods
  virtual void addElementsAllCaches() ;
  virtual void preRebuild() ;
  
 private:
  // Init method
  void init(SbBool isDefault, int numPoints=0, const SbVec3f *_point=NULL, 
            const float *_value=NULL, float _width=1.0, float _height=1.0) ;


  // Data Mapping
  PbDataMapping *m_dataMap ;
  
  // Sensors
  FieldSensorList m_fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     m_fieldList ;

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_POINTS_FIELD_BARS_ */

