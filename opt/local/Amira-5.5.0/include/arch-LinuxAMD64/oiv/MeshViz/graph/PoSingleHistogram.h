/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_SINGLE_HISTOGRAM_
#define  _PO_SINGLE_HISTOGRAM_

#include <MeshViz/graph/PoHistogram.h>

#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoMFFloat.h>

/**
 * @DTEXT  Class to build a single histogram.
 * 
 * @ingroup GraphHistogram
 * 
 * @DESCRIPTION
 *    Class to build a single histogram in the plane XY. This histogram is based on 
 *    simple statistical data.
 * 
 *    Simple statistical data is composed of a list of names associated to a list 
 *    of values. The histogram bars are perpendicular to the X-axis or to the Y-axis
 *    (according to the field type). The statistic values correspond to the height 
 *    (or width) of the bars.
 * 
 *    The bars of the histogram can be colored using the fields color and coloring. If 
 *    the bars colors are defined by a list of colors (coloring = COLOR_LIST), 
 *    color.getNum() must be greater or equal to value.getNum(), otherwise all the bars 
 *    get the same color which is the inherited color.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoSingleHistogram {
 *    @TABLE_FILE_FORMAT
 *       @TR start @TD 0 0
 *       @TR end @TD 1
 *       @TR type @TD X
 *       @TR color @TD 0 0 0
 *       @TR coloring @TD COLOR_LIST
 *       @TR valueVisibility @TD VISIBILITY_ON
 *       @TR valuePosition @TD POS_DEPEND
 *       @TR valuePath @TD PATH_DEPEND  
 *       @TR valueFontSize @TD 0.0
 *       @TR valueFontName @TD ""
 *       @TR valueAddStringVisibility @TD FALSE  
 *       @TR valueAddString @TD ""
 *       @TR nameVisibility @TD VISIBILITY_ON
 *       @TR namePosition @TD POS_DEPEND
 *       @TR namePath @TD PATH_DEPEND
 *       @TR nameFontSize @TD 0.0
 *       @TR nameFontName @TD ""
 *       @TR barSpaceType @TD REL_SPACE
 *       @TR barSpaceValue @TD 0.25
 *       @TR value @TD 0
 *       @TR name @TD ""
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE posinglehistogram.cat.html
 * 
 * 
 */
class MESHVIZ_API PoSingleHistogram : public PoHistogram {

  SO_KIT_HEADER(PoSingleHistogram) ;


 public:

  /* Fields */

  /**
   * Values of each bars of the histogram. 
   */
  SoMFFloat   value ;

  /**
   * Names of each bars of the histogram. If name.getNum() != value.getNum()  
   * no name is associated to the bars.
   */
  SoMFString  name ;



  /* Methods */

  /**
   * Default constructor.
   */
  PoSingleHistogram()
    { init(TRUE, SbVec2f(0.,0.), 1., X, 0, NULL, NULL) ; }

  /**
   * Constructor.
   * [OIV-WRAPPER-ARG IN,IN,IN,NO_WRAP{_value->Length},ARRAY,ARRAY]
   */
  PoSingleHistogram(const SbVec2f &_start, float _end, PoHistogram::Type _type,
                    int numValues, const float *_value, const char **_name)
    { init(FALSE, _start, _end, _type, numValues, _value, _name) ; }

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void rebuild() ;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  // Destructor
  virtual ~PoSingleHistogram() ;
  virtual void   setDefaultOnNonWritingFields() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;

  // Color the bars
  void colorBars(SoGroup *group) ;

 private:
  // Init method
  void init(SbBool isDefault, const SbVec2f &_start, float _end, 
            Type _type, int numValues, const float *_value, const char **_name) ;

  // Build X or Y Histogram
  void buildXHistog() ;
  void buildYHistog() ;

  // Sensors
  FieldSensorList m_fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     m_fieldList ;

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_SINGLE_HISTOGRAM_ */

