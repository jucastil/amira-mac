/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_PIE_CHART_REP_
#define  _PO_PIE_CHART_REP_

#include <MeshViz/graph/PoChart.h>

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFShort.h>
#include <Inventor/fields/SoSFString.h>

class SoTranslation ;
class PbMesh1D ;

/**
 * @DTEXT  Class to build a 3D pie chart.
 * 
 * @ingroup GraphPie
 * 
 * @DESCRIPTION
 *    Builds a 3D pie chart on 1D mesh (PoIrregularMesh1D or PoRegularMesh1D).
 *    The size (angle) of each slice is given by the geometry of the 
 *    current mesh 1D, and the height of each slice is given by one of the 
 *    value-set of the current mesh 1D specified by the field yValuesIndex.
 *    Names attached to each slice are given by one of the string-set of the 
 *    current mesh 1D specified by the field stringsIndex.
 *    With this mecanism all slices have not necessary the same height. On contrary,
 *    if all slices must have the same height, set the field yValuesIndex to -1 and
 *    set the field height to the desired height.
 *    The pie chart origin is at (0,0,0) after applying the current transformation.
 * 
 *    The current label hints (PoLabelHints) is used to specify the appearance
 *    of annotations for each slice.
 *    All annotations depend on the current miscellaneous text attributes which 
 *    defines the font names, line length and so on (PoMiscTextAttr).
 *    All numerical values depend on the current numerical display format 
 *    (PoNumericDisplayFormat).
 *    Each slice can be beveled thanks to the current beveled edge values 
 *    (PoBevelEdge).
 *    The current complexity (SoComplexity) is used to determine the tessellation
 *    of slices.
 * 
 *    The interpretation of colorBinding is the following :
 * 
 *    - INHERITED: All slices are colored with the same inherited color.
 * 
 *    - PER_PART, PER_VERTEX: A color is used for each slice.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoPieChartRep {
 *    @TABLE_FILE_FORMAT
 *       @TR colorBinding @TD INHERITED
 *       @TR yValuesIndex @TD -1
 *       @TR colorValuesIndex @TD 1
 *       @TR material @TD NULL
 *       @TR stringsIndex @TD 0
 *       @TR radiusMin @TD 0.0
 *       @TR radiusMax @TD 1.0
 *       @TR sliceToTranslateNumber @TD 0
 *       @TR sliceToTranslateRadius @TD 0.0
 *       @TR height @TD 0.3
 *       @TR isNameVisible @TD FALSE
 *       @TR isValueVisible @TD FALSE
 *       @TR isPercentageVisible @TD TRUE
 *       @TR annoDistToCenter @TD 0.5
 *       @TR annoHeightFromSlice @TD 0.2
 *       @TR isAnnoSliceColor @TD TRUE
 *       @TR annoFontSize @TD 0.1
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE popiechartrep.cat.html
 * 
 * 
 */

class MESHVIZ_API PoPieChartRep : public PoChart {
  
  SO_KIT_HEADER(PoPieChartRep) ;

  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(sliceSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(sliceApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(slice) ;

  SO_KIT_CATALOG_ENTRY_HEADER(annotationSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(annotationApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(annotation) ;

  SO_KIT_CATALOG_ENTRY_HEADER(annotationLineSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(annotationLineApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(annotationLine) ;


 public:

  /* Fields */

  /**
   * Defines the index of the set of strings used for the names attached
   * to slices. If the field value is negative, no names is attached to 
   * slices.
   */
  SoSFInt32    stringsIndex ;

  /**
   * Defines the mininum radius of the pie chart. If this value is
   * equal to zero, then we obtain sectors otherwise we obtain rings.
   */
  SoSFFloat    radiusMin ;

  /**
   * Defines the maximum radius of the pie chart.
   */
  SoSFFloat    radiusMax ;

  /**
   * Numbers (slice numbers begin at 0) of the slices to translate.
   * sliceToTranslateNumber[i] is the number of the i-th slice to translate.
   */
  SoMFShort    sliceToTranslateNumber ;

  /**
   * Translation values along the bisectors of the slices.
   * sliceToTranslateRadius[i] is the translate value along the bisector 
   * of the i-th slice. 
   */
  SoMFFloat    sliceToTranslateRadius ;

  /**
   * Defines the height of the pie chart if the field yValuesIndex is different
   * from -1.
   */
  SoSFFloat    height ;

  /**
   * Defines if the name of each slice is visible.
   * Slice names are given by the set of strings defined by the field
   * stringsIndex.
   */
  SoSFBool     isNameVisible ;

  /**
   * Defines if the value of each slice is visible.
   */
  SoSFBool     isValueVisible ;

  /**
   * Defines if the percentage of each slice is visible.
   */
  SoSFBool     isPercentageVisible ;

  /**
   * Defines the distance from the pie chart center of the displayed
   * annotations (name/value/percentage).
   */
  SoSFFloat    annoDistToCenter ;

  /**
   * Defines the height of the displayed annotations (name/value/percentage) 
   * from the top of each slice.
   */
  SoSFFloat    annoHeightFromSlice ;

  /**
   * Define the font size of the annotation.
   */
  SoSFFloat    annoFontSize ;

  /**
   * Determines if the color of for annotation is the same as slices.
   */
  SoSFBool     isAnnoSliceColor ;

  /**
   * Constructor.
   */
  PoPieChartRep() ;

  /**
   * Allow the user to retreive the slice number (sliceNumber argument) which has 
   * been picked from a picked path (path argument) (cf SoSelection node for more 
   * information about picking). Return FALSE, if the picked path does not 
   * correspond to a slice of the pie chart (sliceNumber is not significative), TRUE 
   * otherwise.
   * [OIVJAVA-WRAPPER-RETURN-TYPE SUCCESS_FLAG{throw new UnsupportedOperationException()}]
   */
  SbBool getPickedSliceNumber(const SoPath *path, int &sliceNumber) const ;

#ifdef OIV_NET_DOC
  /**
  * Convenience methods to set the fields sliceToTranslateNumber and 
  * sliceToTranslateRadius.  
  */

#else
  /**
  * Convenience methods to set the fields sliceToTranslateNumber and 
  * sliceToTranslateRadius. 
  * <PRE> 
  * 0 <= i <= sliceToTranslateNumber.getNum() - 1,
  * if sliceNumber == sliceToTranslateNumber[i] 
  *    sliceToTranslateRadius[i] = radius, 
  * else
  *    sliceToTranslateRadius[sliceToTranslateNumber.getNum()] = radius, 
  *}
  */

#endif //OIV_NET_DOC
  void  setSliceToTranslate(int sliceNumber, float radius) ;

  /**
   * Gets the current translation of a slice.
   * Returns 0 if sliceNumber slice does not exist or 
   * sliceNumber slice is not translated, the translation radius otherwise.
   */
  float getSliceToTranslate(int sliceNumber) const ;

  /*----------------------------------------------------------------------------*/


 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  struct SliceAttr {
    float         startAngle ;
    float         endAngle ;
    float         value ;
    float         height ;
    SbString      nameStr ;
    SbString      percentageStr ;
    SbString      valueStr ;
    SoMaterial    *material ;
    SoTranslation *translation ;
  } ;

  virtual ~PoPieChartRep() ;
  // Destructor.

  // Overloaded methods
  virtual void rebuild() ;
  virtual void addElementsAllCaches() ;
  virtual void preRebuild() ;

  // Methods
  virtual void   setDefaultOnNonWritingFields() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;

 private:
  inline SbBool isAnnoText() const ;
  void eraseAllParts() ;
  void buildSliceAttrList(const PbMesh1D *mesh1D, float &maxSliceHeight,
                          SbBool &isConstantHeight) ;
  void buildSliceText(int sliceIndex, float maxSliceHeight, SoGroup *annoGroup, 
                      SoGroup *annoLineGroup) ;

  // Data
  SliceAttr *m_sliceAttrList ;
  int       m_numSliceAttr ;

  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_PIE_CHART_REP_ */

