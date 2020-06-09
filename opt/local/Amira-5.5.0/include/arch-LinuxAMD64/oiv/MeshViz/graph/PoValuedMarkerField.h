/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_VALUED_MARKER_FIELD_
#define  _PO_VALUED_MARKER_FIELD_

#include <MeshViz/graph/PoGraphMaster.h>

#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/fields/SoSFString.h>

class PbDataMapping ;

/**
 * @DTEXT  Class for a valued markers field.
 * 
 * @ingroup GraphScatter
 * 
 * @DESCRIPTION
 *    Class to build a valued markers field in the plane XY. A valued markers field is a 
 *    list of markers which can be colored and can have different sizes. By default all 
 *    markers have the same size and the same color.
 * 
 *    Colors of the markers depend on the current data mapping. 
 *    If the method setDataMapping(dataMapping) is called, the 
 *    current data mapping is "dataMapping". Otherwise the current data mapping 
 *    is specified in the current inherited state (cf property node PoDataMapping 
 *    and its derived classes). If there is no current data-mapping
 *    (i.e setDataMapping() not called and no PoDataMapping node traversed before 
 *    in the scene graph), all markers get the same color which is the inherited color.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoValuedMarkerField {
 *    @TABLE_FILE_FORMAT
 *       @TR point @TD 0 0
 *       @TR value @TD 0
 *       @TR size @TD 0
 *       @TR markerString @TD "."
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE povaluedmarkerfield.cat.html
 * 
 * 
 */

class MESHVIZ_API PoValuedMarkerField : public PoGraphMaster {
  
  SO_KIT_HEADER(PoValuedMarkerField) ;
  
  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(valuedMarkerField) ;


 public:

  /* Fields */

  /**
   * List of coordinates for the markers.
   */
  SoMFVec2f  point ;

  /**
   * List of values used to color the markers. If the number of values is equal to 
   * number of points of point , marker have a color depending on the current 
   * data mapping (see description of PoValuedMarkerField), otherwise all 
   * the markers have the same color.
   */
  SoMFFloat  value ;

  /**
   * List of sizes used to calculate the marker sizes. If the number of sizes is equal 
   * to number of points of point , marker have a size depending on size, otherwise 
   * all the markers have the same size.
   */
  SoMFFloat  size ;

  /**
   * The markers are defined by a string. If this field is equal to ".", the markers are 
   * SoPointSet shapes, otherwise SoText2 shapes. To change the font of text 
   * markers, set the catalog part appearance.font.name . Be careful, for the 
   * moment, text markers are not vertically aligned.
   */
  SoSFString markerString ;



  /* Methods */

  /**
   * Default constructor.
   */
  PoValuedMarkerField()
    { init(TRUE) ; }

  /**
   * Constructor.
   * [OIV-WRAPPER-ARG NO_WRAP{_point->Length},ARRAY,ARRAY,ARRAY]
   */
  PoValuedMarkerField(int numPoints, const SbVec2f *_point, const float *_value,
                      const float *_size)
    { init(FALSE, numPoints, _point, _value, _size) ; } 

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void rebuild() ;

  /**
   * Sets a reference to a PbDataMapping object, used to the association value-
   * color. If this method is not called (or called passing NULL as argument), 
   * this is the data mapping defined in the current inherited state 
   * (defined with the property node PoDataMapping and its derived classes) 
   * which is used.
   */
  void setDataMapping(PbDataMapping *dataMapping) ;

  /**
   * Gets a reference to a PbDataMapping object, used to the association value-
   * color. 
   */
  const PbDataMapping *getDataMapping() const ;

  /*----------------------------------------------------------------------------*/


 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  // Methods
  // Destructor
  virtual ~PoValuedMarkerField() ;
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
            const float *_value=NULL, const float *_size=NULL) ;

  // Sensors
  FieldSensorList m_fieldSensorList ;

  // Data mapping
  PbDataMapping *m_dataMap ;
  
  // List of fields defined in this class
  SoFieldList     m_fieldList ;

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_VALUED_MARKER_FIELD_ */

