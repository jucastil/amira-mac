/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_AUTO_VALUE_LEGEND_
#define  _PO_AUTO_VALUE_LEGEND_

#include <MeshViz/graph/PoValueLegend.h>

#include <Inventor/fields/SoSFVec2f.h>

/**
 * @DTEXT  Abstract class for automatic value legend.
 * 
 * @ingroup GraphLegend
 * 
 * @DESCRIPTION
 *    This class represents a value legend delimited by a rectangle defined by 
 *    the points start and end. Values of the legend are drawn from the start point 
 *    to the end point, so reversing their two points reverses also the value order. 
 * 
 *    The distribution of the color boxes is handled automatically according to 
 *    the number of values and the geometry of the rectangle delimiting the legend. 
 *    The box sizes and the font size are calculated so that the boxes occupy the 
 *  entire space inside the legend rectangle.
 * 
 */
class MESHVIZ_API PoAutoValueLegend : public PoValueLegend {

  SO_KIT_HEADER(PoAutoValueLegend) ;


 public:

  /* Fields */

  /**
   * First point of one of the diagonals of the rectangle delimiting the legend.
   * Values of the legend are drawn from the start point to the end point, 
   * so reversing their two points reverses also the values order.
   * For instance if start = SbVec2f(0,0) and end = SbVec2f(0.5, 1), values
   * are drawn from the down to the up.
   */
  SoSFVec2f  start ;

  /**
   * Second point of the same diagonal.
   */
  SoSFVec2f  end ;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  // Constructor
  PoAutoValueLegend()
    { init(SbVec2f(0., 0.), SbVec2f(1., 1.)) ; }

  PoAutoValueLegend(const SbVec2f &_start, const SbVec2f &_end)
    { init(_start, _end) ; }

  // Methods
  virtual void   setDefaultOnNonWritingFields() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  
  // Destructor
  virtual ~PoAutoValueLegend() ;

  // Draw multiplicative factor
  void drawMultFactor(MultFactorPosition position, Plimit &limit) ;

  /***********  Methods for legend constitued of several boxes ****************/

  // Compute strings font size
  void computeStrFtSizeLegendBoxes(float legend_width, float legend_height, int nb_lines, 
                                   int nb_columns, float f0, float *maxTextSizePerCol, 
                                   SbVec2f &space_box) ;

  // Compute graphic size use to draw values in  auto legend constitued 
  // of several boxes
  void computeGraphicSizeForValues(float &width, float &height, float &text_space) ;
  
  // Draw the legend
  void drawBoxesLegend(int numStrings, const SbString *strings) ;

  // Draw a box with an interior colors computed though BoxRepresentation
  void drawBoxLegendBoxesA(SoGroup *boxBorderGroup, SoGroup *boxGroup,
                           const SbVec2f &topLeftCorner, float width, float height,
                           int repIndex) ;

  /************ Methods for legend constitued of one box *********************/

  enum ValDistrib {
    ALL_VAL,
    LINEAR_VAL,
    MIN_MAX_VAL
  } ;
  
  // Draw the legend 
  void drawOneBoxLegend(ValDistrib val_distrib, SbBool isLinear, SbBool isLowerUpperBoxes) ;

  // Compute size for undef boxes (if they exists) and
  // update size of the legend
  void computeUndefBoxOneBoxLegend(float &legend_width, float &legend_height,
                                   float &undef_box_width, float &undef_box_height,
                                   float &undef_box_space) ;

  // Draw rectangle which represents values
  void drawValuesRectOneBoxLegend(float val_rect_height, float val_rect_width,
                                  int lower_undef_index, const float *val_rect_dist, 
                                  const Plimit &limit) ;

  // Draw undefined boxes and associated texts
  void drawUndefBoxesOneBoxLegend(float text_offset, float undef_box_height, 
                                  float undef_box_width, float undef_box_space, 
                                  int lower_undef_index, int upper_undef_index, 
                                  Plimit &limit) ;

  // Draw values text
  void drawValuesOneBoxLegend(float val_rect_width, float val_rect_height,
                              float text_offset, const float *val_dist,
                              SbString *val_str, int num_val, const Plimit &limit) ;

  // Compute font size of values
  void computeValFtSizeOneBoxLegend(ValDistrib val_distrib, float legend_width, float legend_height,
                                    int lower_undef_index, int upper_undef_index,
                                    float undef_box_width, float undef_box_height,
                                    const float *val_rect_dist, int &num_val_to_display,
                                    SbString **val_str, float **val_dist, float &val_width,
                                    float &val_height) ;

  float m_maxValueSize ;

 private:
  // Init Method
  void init(const SbVec2f &_start, const SbVec2f &_end) ;

  // Sensors
  FieldSensorList m_fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     m_fieldList ;

  // Indicates if a lower box and a upper box should be drawn.
  SbBool m_isLowerUpperBoxes ;
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_AUTO_VALUE_LEGEND_ */



