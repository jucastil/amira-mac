/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_LABEL_
#define  _PO_LABEL_

#include <MeshViz/graph/PoChart.h>

#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoSFFloat.h>

class SoCoordinate3 ;

/**
 * @DTEXT  Class to build a label field.
 * 
 * @ingroup GraphMisc
 * 
 * @DESCRIPTION
 *    Builds a 2D label field on 1D mesh (PoIrregularMesh1D or PoRegularMesh1D).
 *    The abscissas of the labels are given by the geometry of the current mesh 1D,
 *    and the ordinates are given by one of the value-set of the current mesh 1D 
 *    specified by the field yValuesIndex.
 *    Names attached to each label are given by one of the string-set of the 
 *    current mesh 1D specified by the field stringsIndex.
 * 
 *    The fields position, threshold and offset allows the user to set the label
 *    position and the field valueType set the values to display as labels.
 *    This class also takes into account of the current mesh 1D hints (PoMesh1DHints),
 *    and the current mesh 1D filter (PoMesh1DFilter) to filter the geometry
 *    of the current mesh 1D.
 *    The current label hints (PoLabelHints) is used to specify the appearance
 *    of labels. If the offset is different from null and, if the field isLabelLineVisible
 *    of the current label hints is set to TRUE then, a line representing the offset
 *    is drawn.
 *    All labels depend on the current miscellaneous text attributes which defines
 *    the font names, line length and so on (PoMiscTextAttr).
 *    All numerical values depend on the current numerical display format 
 *    (PoNumericDisplayFormat).
 * 
 *    The interpretation of colorBinding is the following :
 *      - INHERITED: All labels are colored with the same inherited color.
 *      - PER_PART, PER_VERTEX: A color is used for each label.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoLabel {
 *    @TABLE_FILE_FORMAT
 *       @TR colorBinding @TD INHERITED
 *       @TR yValuesIndex @TD -1
 *       @TR colorValuesIndex @TD 1
 *       @TR material @TD NULL
 *       @TR stringsIndex @TD 0
 *       @TR axis @TD X
 *       @TR valueType @TD VALUE
 *       @TR position @TD VALUE_POS
 *       @TR threshold @TD 0.
 *       @TR offset @TD 0. 0. 0.
 *       @TR fontSize @TD 0.0
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE polabel.cat.html
 * 
 */

class MESHVIZ_API PoLabel : public PoChart {
  
  SO_KIT_HEADER(PoLabel) ;

  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(label) ;
  SO_KIT_CATALOG_ENTRY_HEADER(labelLineSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(labelLineApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(labelLine) ;


 public:

  /**
   *  Type of value displayed by the labels.
   */
  enum ValueType {
    /**
     *  The values displayed correspond to the
     *  the ordinates (resp. abscissas) of the
     *  current mesh 1D geometry.
     */
    VALUE,        

    /**
     *  The values displayed correspond to the
     *  names associated to the strings-set 
     *  specified by the field stringsIndex.
     */
    NAME          
  } ;



  /**
   *  Position of the labels.
   */
  enum Position {
    /**
     *  The label position is the given by the current mesh geometry.
     */
    VALUE_POS,     

    /**
     *  The abscissas (resp ordinate) is given by the
     *  current mesh 1D geometry and the ordinate (resp. abscissas)
     *  is at the middle between the mesh ordinate (reps. abscissas)
     *  and the threshold field.
     */
    MIDDLE_POS,    

    /**
     *  The abscissas (resp ordinate) is given by the
     *  current mesh 1D geometry and the ordinate (resp. abscissas)
     *  is the threshold field.
     */
    THRESHOLD_POS  
                   
  } ;



  /**
   *  values computation.
   */
  enum Axis {
    /** X-Axis  */
    X,     

    /** Y-Axis */
    Y      
  } ;



  /* Fields */

  /**
   * Defines the index of the set of strings used for the names attached
   * to labels when valueType is equal to NAME. If the field value is 
   * negative, no names is attached to labels.
   */
  SoSFInt32    stringsIndex ;

  /**
   * Defines from which axis the position and type of displayed
   * values computation is done.
   * All values in brackets correspond to the Y-axis.
   */
  SoSFEnum     axis ;

  /**
   * Defines the type of values displayed by the labels.
   * There are two ways to display the labels :
   *    - VALUE: The values displayed correspond to the
   *            the ordinates (resp. abscissas) of the
   *            current mesh 1D geometry.
   *    - NAME:  The values displayed correspond to the
   *            names associated to the strings-set 
   *            specified by the field stringsIndex.
   *
   */
  SoSFBitMask  valueType ;

  /**
   * Defines the position of the labels.
   * There are three ways to define this position :
   *   - VALUE_POS:  The label position is the given by the current
   *                mesh geometry.
   *   - MIDDLE_POS: The abscissas (resp. ordinate) is given by the
   *                current mesh geometry and the ordinate (resp. abscissas)
   *                is at the middle between the mesh ordinate (reps. abscissas)
   *                and a threshold.
   *  - THRESHOLD_POS: The abscissas (resp. ordinate) is given by the
   *                  current mesh geometry and the ordinate (resp. abscissas)
   *                  is the threshold field.
   *
   */
  SoSFEnum     position ;

  /**
   * Defines the threshold used to the set position of the label.
   */
  SoSFFloat    threshold ;

  /**
   * Defines an offset applied to the label. This offset is combinated 
   * with the label position. If the number of offsets is inferior to the
   * number of labels, they are cyclically used.
   */
  SoMFVec3f    offset ;

  /**
   * Font size of labels. If this value is less or 
   * equal to 0, the font size is fixed at 0.04. 
   * This value is a percentage of the current domain 
   * (cf PoBase description).
   */
  SoSFFloat    fontSize ;

  /**
   * Constructor.
   */
  PoLabel() ;

  /*----------------------------------------------------------------------------*/


 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  virtual ~PoLabel() ;
  // Destructor.

  // Overloaded methods
  virtual void rebuild() ;
  virtual void addElementsAllCaches() ;
  virtual void preRebuild() ;

  // Methods
  virtual void   setDefaultOnNonWritingFields() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;

 private:
  void drawLabelLine(const SbBox2f &labelLimit, float labelDepth, const SbVec3f &origPos,
                     SoCoordinate3 *labelLineCoords) ;

  const SbString* retreiveValueName(float xValue, float yValue,
                                    int   size, const float *x,
                                    const float *y, const SbString *valuesNames) const ;

  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_LABEL_ */

