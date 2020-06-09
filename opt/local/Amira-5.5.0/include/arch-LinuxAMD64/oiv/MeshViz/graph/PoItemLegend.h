/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_ITEM_LEGEND_
#define  _PO_ITEM_LEGEND_

#include <MeshViz/graph/PoLegend.h>

#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoMFColor.h>
#include <Inventor/fields/SoMFUShort.h>
#include <Inventor/fields/SoMFFloat.h>

class PiText ;

/**
 * @DTEXT  Class to build an items legend.
 * 
 * @ingroup GraphLegend
 * 
 * @DESCRIPTION
 *    This legend associates a string (this is the values of the legend) to a box 
 *    or/and a line or/and a marker. All the sizes cannot be controlled by the 
 *    application and depend on the dimensions of the legend. The font size F of
 *    strings is calculated as function of the rectangle delimiting the legend. 
 *    The size of the markers is equal to F. The height of the boxes is equal to 
 *    1.5 * F, and the width of the lines and of the boxes is equal to 
 *    1.5 * F * boxRatio.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoItemLegend {
 *    @TABLE_FILE_FORMAT
 *       @TR titleVisibility @TD VISIBILITY_OFF
 *       @TR titlePosition @TD POS_BOTTOM
 *       @TR titlePath @TD RIGHT_PATH
 *       @TR titleFontSize @TD 0
 *       @TR titleFontName @TD ""
 *       @TR titleString @TD ""
 *       @TR valueVisibility @TD VISIBILITY_ON
 *       @TR valuePosition @TD POS_RIGHT
 *       @TR valueFontName @TD ""
 *       @TR valueAddStringVisibility @TD FALSE
 *       @TR valueAddString @TD ""
 *       @TR marginType @TD REL_MARGIN
 *       @TR marginLeft @TD 0.05
 *       @TR marginRight @TD 0.05
 *       @TR marginBottom @TD 0.05
 *       @TR marginTop @TD 0.05
 *       @TR incrementType @TD VERTICAL_INCREMENT
 *       @TR numColumns @TD 1
 *       @TR boxRatio @TD 1
 *       @TR start @TD 0 0
 *       @TR end @TD 1 1
 *       @TR item @TD ""
 *       @TR boxVisibility @TD TRUE
 *       @TR boxColor @TD 0 0 0
 *       @TR lineVisibility @TD FALSE
 *       @TR lineColor @TD 0 0 0
 *       @TR lineSize @TD 0
 *       @TR linePattern @TD 0xFFFF
 *       @TR markerVisibility @TD FALSE
 *       @TR markerColor @TD 0 0 0
 *       @TR markerSize @TD 0
 *       @TR markerString @TD "."
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE poitemlegend.cat.html
 * 
 * 
 */
class MESHVIZ_API PoItemLegend : public PoLegend {

  SO_KIT_HEADER(PoItemLegend) ;

  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(lineSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(lineApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(line) ;

  SO_KIT_CATALOG_ENTRY_HEADER(markerSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(markerApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(marker) ;


 public:

  /* Fields */

  /**
   * First point of one of the diagonals of the rectangle delimiting the legend.
   */
  SoSFVec2f   start ;

  /**
   * Second point of the same diagonal.
   */
  SoSFVec2f   end ;

  /**
   * List of item names.
   */
  SoMFString  item ;



  /**
   * Visibility of the boxes.
   */
  SoSFBool    boxVisibility ;

  /**
   * List of colors for the boxes (boxColor.getNum() must be 
   * greater or equal to item.getNum(), otherwise all boxes get the 
   * same color which is the inherited color).
   */
  SoMFColor   boxColor ;



  /**
   * Visibility of the lines.
   */
  SoSFBool    lineVisibility ;

  /**
   * List of colors for lines.
   */
  SoMFColor   lineColor ;

  /**
   * List of sizes for lines.
   */
  SoMFFloat   lineSize ;

  /**
   * Be careful: (lineColor or lineSize or linePattern).getNum() must be greater or 
   * equal to item.getNum() in order to take into account one of these fields, 
   * otherwise the inherited attributes will be used.
   */
  SoMFUShort  linePattern ;



  /**
   * Visibility of the markers.
   */
  SoSFBool    markerVisibility ;

  /**
   * List of color for markers.
   * Be careful: markerColor.getNum() must be greater or equal to 
   * item.getNum() in order to take into account one of this field, otherwise the 
   * inherited attributes will be used.
   */
  SoMFColor   markerColor ;

  /**
   * List of sizes for markers.
   * Be careful: markerSize.getNum() must be greater or equal to 
   * item.getNum() in order to take into account one of this field, otherwise the 
   * inherited attributes will be used.
   */
  SoMFFloat   markerSize ;

  /**
   * The markers are defined by a list of strings. For each 
   * string of markerString equals to ".", the marker is an 
   * SoPointSet shape, otherwise an SoText2 shape. 
   * Futhermore, only the first character of each string of 
   * markerString is used. To change the font of the text 
   * markers, set catalog part markerApp.font.name. Be careful, in this version, 
   * text markers are not vertically aligned.
   */
  SoMFString  markerString ;



  /* Methods */

  /**
   * Default constructor.
   */
  PoItemLegend()
    { init(TRUE, SbVec2f(0.,0.), SbVec2f(1.,1.), 0, NULL, NULL) ; }

  /**
   * Constructor.
   * [OIV-WRAPPER-ARG IN,IN,NO_WRAP{_item->Length},ARRAY,ARRAY]
   */
  PoItemLegend(const SbVec2f &_start, const SbVec2f &_end, int _numItems, 
               const char** _item, const SbColor *_boxColor=NULL)
    { init(FALSE, _start, _end, _numItems, _item, _boxColor) ; }

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
  virtual void   setDefaultOnNonWritingFields() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  
  // Destructor
  virtual ~PoItemLegend() ;

  // Determines if the legend must be reverted or not.
  virtual void setRevertOrder(float startY, float endY) 
    { m_revertOrder =  (startY <= endY ? TRUE : FALSE) ; }

 private:
  // Init method
  void init(SbBool isDefault, const SbVec2f &_start, const SbVec2f &_end, 
            int _numItems, const char** _item, const SbColor *_boxColor) ;

  // Compute items font size
  void computeItemFontSize(float legend_width, float legend_height, int nb_lines, 
                           int nb_columns, float f0, float *maxTextSizePerCol, 
                           SbVec2f &space_box) ;
    
  // Draw a box with an interior color
  void drawBoxLegendBoxesA(SoGroup *boxBorderGroup, SoGroup *boxGroup,
                           const SbVec2f &topLeftCorner, float width, float height,
                           int repIndex) ;
  
  // Draw lines
  void drawLines(int nb_lines, int nb_columns, int numItems, 
                 const float *maxTextSizePerCol, const SbVec2f &space_box, 
                 const Plimit &current_limit) ;

  // Draw a horizontal line with color, pattern and size
  void drawHorLine(SoGroup *lineGroup, const SbVec2f &orig, float size, 
                   SbBool isColor, SbBool isSize, SbBool isPattern, int repIndex) ;

  // Draw markers
  void drawMarkers(int nb_lines, int nb_columns, int numItems, 
                   const float *maxTextSizePerCol, const SbVec2f &space_box, 
                   const Plimit &current_limit) ;

  // Draw a marker with color, type and size
  void drawMarker(SoGroup *markerGroup, const SbVec2f &orig, SbBool isColor, 
                  SbBool isSize, SbBool isType, int repIndex) ;

  // Compute graphic size use to draw values in  auto legend constitued 
  // of several boxes
  void computeGraphicSizeForValues(float &width, float &height, 
                                   float &text_space) ;

  // Sensors
  FieldSensorList m_fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     m_fieldList ;
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_ITEM_LEGEND_ */



