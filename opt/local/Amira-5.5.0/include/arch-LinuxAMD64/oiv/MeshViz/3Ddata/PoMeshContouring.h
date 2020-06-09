/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_MESHCONTOURING_
#define  _PO_MESHCONTOURING_

#include <MeshViz/3Ddata/PoMesh2D.h>
#include <MeshViz/graph/PbNumericDisplayFormat.h>
#include <MeshViz/graph/PbMiscTextAttr.h>

#include <Inventor/projection/SbProjection.h>

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFUShort.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoMFVec2f.h>

/**
 * @DTEXT  Class to build contour lines on a 2D mesh.
 * 
 * @ingroup MeshRepresentation
 * 
 * @DESCRIPTION
 *     Builds contour lines on a 2D mesh. These contour lines are computed from 
 *     a level values list and the nodes scalar values of the  mesh. The level 
 *     value list is defined by the PoMesh::setIsovaluesList() method or by the 
 *     current PoIsovaluesList node during the traversal.
 * 
 *     All contour lines can have the same color (PoMesh::coloringType = COLOR_INHERITED) 
 *     or can have a color depending on the values of the contouring lines 
 *     (PoMesh::coloringType != COLOR_INHERITED).
 * 
 *     Contour lines are separated into 2 groups: major contour lines which can be 
 *     annotated by their value, and minor contour lines which cannot be annotated. 
 *     Major contour line are defined by the value of fields majorPeriod and 
 *     firstMajor. They are annotated only if the field annotIsVisible is TRUE.
 *     The way of putting annotations along contour lines is defined by the value
 *     of the fields annotPath, annotCrossStatus, annotGap and annotClippingPolygon.
 * 
 *     When the annotation are visible, the way of drawing the text of the level values 
 *     depends on the current numeric display format and also on the current miscellaneous 
 *     text attributes. If the method setFormat(format) is called, the current numerical 
 *     display format is "format". Otherwise the current numerical display format is 
 *     specified in the current inherited state (cf property node PoNumericDisplayFormat). 
 *     If the method setMiscTextAttr(textAttr) is called, the current miscellaneous text 
 *     attributes are defined by "textAttr". Otherwise the current miscellaneous text 
 *     attributes are specified in the current inherited state (cf property node 
 *     PoMiscTextAttr).
 *
 *     @B Note: @b Contour line annotations are not displayed if the mesh is not
 *     defined in the XY plane. For example, if a 2D mesh is defined as follows:
 *     X coordinates are constant, Y coordinates vary, and Z coordinates vary, 
 *     (and zValuesIndex set with a value different from -1), the contour lines 
 *     will be not annotated.
 *     In order to annotate contour lines for a mesh not defined in the XY plane, 
 *     define it in the XY plane and apply a rotation.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoMeshContouring {
 *    @TABLE_FILE_FORMAT
 *       @TR valuesIndex @TD -1
 *       @TR coloringType @TD COLOR_INHERITED
 *       @TR zValuesIndex @TD -1
 *       @TR vecsIndex @TD -1
 *       @TR valuesIndexForCellFilter  @TD -1
 *       @TR moduleDataMapping @TD NULL
 *       @TR majorPeriod @TD 3
 *       @TR firstMajor @TD 1
 *       @TR annotIsVisible @TD FALSE
 *       @TR annotPath @TD TANGENTIAL_PATH
 *       @TR annotCrossStatus @TD CROSS_CONTOUR
 *       @TR annotIsBackground @TD FALSE
 *       @TR annotIsContourClip @TD FALSE
 *       @TR annotGap @TD 1
 *       @TR annotClippingPolygon @TD 0 0
 *       @TR annotFontSize @TD 0
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pomeshcontouring.cat.html
 * 
 * 
 */

class MESHVIZ_API PoMeshContouring : public PoMesh2D {

  SO_KIT_HEADER(PoMeshContouring) ;

  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(transform) ;

  SO_KIT_CATALOG_ENTRY_HEADER(majorContourLineSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(majorContourLineApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(majorContourLine) ;

  SO_KIT_CATALOG_ENTRY_HEADER(minorContourLineSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(minorContourLineApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(minorContourLine) ;

  SO_KIT_CATALOG_ENTRY_HEADER(annotBackgroundSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(annotBackgroundApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(annotBackground) ;

  SO_KIT_CATALOG_ENTRY_HEADER(annotBackgroundBorderSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(annotBackgroundBorderApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(annotBackgroundBorder) ;

  SO_KIT_CATALOG_ENTRY_HEADER(annotTextSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(annotTextApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(annotText) ;


 public:

  /**
   * Constructor
   */
  PoMeshContouring() ;

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void   rebuild() ;

  /**
   *  Type of annotations path
   */
  enum AnnotPath {
    /**
     *  Annotations are tangential to the contour lines.
     */
    TANGENTIAL_PATH,  
    /**
     *  Annotations are horizontal.
     */
    HORIZONTAL_PATH,  
    /**
     *  Annotations are vertical.
     */
    VERTICAL_PATH     
  } ;

  

  /**
   *  Controls the annotations of contour lines 
   */
  enum AnnotCrossStatus {
    /**
     *  Annotations may cross contour lines.
     */
    CROSS_CONTOUR,         
    /**
     *  Annotations may cross only minor contour lines (but not major contour lines).
     */
    CROSS_MINOR_CONTOUR,   
    /**
     *  Annotations do not cross any contour lines.
     */
    DONT_CROSS_CONTOUR     
  } ;



  /**
   * Defines the major and the minor contour lines. majorPeriod is the period of 
   * major contour lines. Only major contour lines can be annotated. See also firstMajor.
   * By default, majorPeriod = 3.
   */
  SoSFUShort  majorPeriod ;

  /**
   * Defines the first major contour lines. See also majorPeriod.
   * By default, firstMajor = 1.
   */
  SoSFUShort  firstMajor ;

  /**
   * Contour lines annotations visibility.
   * By default, annotIsVisible = FALSE
   */
  SoSFBool    annotIsVisible ;

  /**
   * Annotations path. 
   *   - TANGENTIAL_PATH, annotations are tangential to the contour lines.
   *   - HORIZONTAL_PATH, annotations are horizontal.
   *   - VERTICAL_PATH,   annotations are vertical.
   *
   * By default, annotPath = TANGENTIAL_PATH.
   */
  SoSFEnum    annotPath ;

  /**
   * Controls the annotations and contour lines crossing. 
   *   - CROSS_CONTOUR,         annotations may cross contour lines.
   *   - CROSS_MINOR_CONTOUR,   annotations may cross only minor contour lines (but not major contour lines).
   *   - DONT_CROSS_CONTOUR     annotations do not cross any contour lines.
   *
   * By default, annotCrossStatus = CROSS_CONTOUR.
   *
   * Note that annotations may always cross the annotated contour line, however this
   * field prevents annotations from crossing other contour lines.
   */
  SoSFEnum    annotCrossStatus ;

  /**
   * Defines if the annotations are framed by a background. By default, annotIsBackground = FALSE
   */
  SoSFBool    annotIsBackground ;

  /**
   * Defines if the contour lines are clipped by the annotations.
   * By default, annotIsContourClip = FALSE
   */
  SoSFBool    annotIsContourClip ;

  /**
   * Curvilinear distance between two annotations of a 
   * same contour line. It is a multiplicative factor of 
   * the domain size or of the clipping polygon size (if 
   * it is defined). The distance used is equal to 
   * annotGap * Ds, where Ds is the max of the width 
   * and the height of the domain or of the polygon.
   * By default, annotGap = 1.
   */
  SoSFFloat   annotGap ;

  /**
   * This is a polygon where no annotations are 
   * present outside it. If the point list is empty, the 
   * mesh limits will be used instead.
   * By default, annotClippingPolygon = (0,0)
   */
  SoMFVec2f   annotClippingPolygon ;

  /**
   * Font size of annotations of contour lines. This 
   * value is a multiplicative factor of the domain size 
   * or of the clipping polygon size (if it is defined). 
   * The font size used is equal to annotFontSize * Ds, 
   * where Ds is the max of the width and the height 
   * of the domain or of the clipping polygon. If this 
   * value is <= 0, the annotations font size is fixed at 
   * 0.04. By default, annotFontSize = 0.
   */
  SoSFFloat   annotFontSize ;

  /**
  * Font size factor of annotations of contour lines. This
  * field is only interpreted when an SoProjection node is 
  * applicable to contouring.
  * By default, annotFontFactor = 1.
  */
  SoSFFloat   annotFontFactor;

  /**
   * Sets a reference to a PbNumericDisplayFormat object for the numerical 
   * display format for annotations of contour lines. If this method is not called the 
   * format used is the one of the default constructor of PbNumericDisplayFormat.
   */
  void setFormat(PbNumericDisplayFormat *format) ;

  /**
   * Gets the reference to a PbNumericDisplayFormat. See setFormat.
   */
  const PbNumericDisplayFormat *getFormat() const;

  /**
   * Sets a reference to PbMiscTextAttr object for miscellaneous text attributes 
   * of annotations of contour lines. If this method is not called the text attributes 
   * used are those of the default constructor of PbMiscTextAttr.
   */
  void setMiscTextAttr(PbMiscTextAttr *textAttr) ;

  /**
   * Gets a reference to PbMiscTextAttr object. See setMiscTextAttr.
   */
  const PbMiscTextAttr* getMiscTextAttr() const;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  struct Parallelogram3 { Ppoint3 points[5] ; } ;

  static void initClass() ;
	static void exitClass() ;

 protected:
  // Methods

  // Destructor
  virtual ~PoMeshContouring() ;  
  virtual void   basicObjectChange(PbBase *basicObj) ;
  virtual void   setDefaultOnNonWritingFields();
  virtual void   addElementsAllCaches() ;
  virtual void   preRebuild();
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;

  const PbMiscTextAttr           *m_miscTextAttr;
  const PbNumericDisplayFormat   *m_format;

  // Projection to apply
  SbProjection					 *m_projection, m_defaultProjection;

  /**
  * Gets a reference to an SbProjection object used to define the data projection
  */
  const SbProjection* getProjection() const ;

  /*----------------------------------------------------------------------------*/
 private:
  struct StoreAnnotSpace {
    Parallelogram3 space ;     // Coords of the annotation
    float          isovalue ;  // Value of the annotation
    Plimit         bbox ;   // Bounding box of the annotation
  } ;

  // Sensors
  FieldSensorList m_fieldSensorList ;

  SoMFVec2f m_annotClippingPolygon ;

  // List of fields defined in this class
  SoFieldList     m_fieldList ;

  PbMiscTextAttr           *m_miscTextAttrSet, m_defaultMiscTextAttr ;
  PbNumericDisplayFormat   *m_formatSet, m_defaultFormat ;

  void getMeshLimit(Ppoint_list_list3 &limit);
  void freeMeshLimit(Ppoint_list_list3 &limit);

  //**************************************************************************
  //* All following methods are used to build annotations of contour lines   *
  //**************************************************************************

  // Determine if the place (annot_space) of the annotation is available.
  SbBool isAvailableAnnotArea(const StoreAnnotSpace *occuped_annot_space, 
                              int nb_annot, const Plimit *annot_space) ;

  // Compute the coordinates of the parallelogram of an annotation
  void calculateAnnotBox(const Ppoint3 *p_center, const Ppoint3 *pt_inter_circle1, 
                         const Ppoint3 *pt_inter_circle2, float annot_width, 
                         float annot_height, Ppoint *annot_space, 
                         Ppoint *annot_space_with_margin) ;

  // Generate shapes to draw the annotations
  void drawAnnotation(const char *annot_str, const Ppoint3 *annot_pos, 
                      const Ppoint3 *annot_space, SoCoordinate3 *backgroundCoords, 
                      SoCoordinate3 *backgroundBorderCoords) ;

  // Determine if an annotation intersects other contour lines
  SbBool isIntersAnnotContourLines(const Tisoline_list *contourLinesList, 
                                   const Ppoint_list3 *currentContourLine, 
                                   const Plimit *annotBBox,
                                   const Ppoint *annot_space, float isovalue) ;

  // Determine undefined values inferior and superior.
  void searchUpperLowerIsoval(const Tisoline_list *contourLineList, SbBool isMinThreshold, 
                              SbBool isMaxThreshold) ;

  // Clip contour lines by annotations
  void clipContourLinesByAnnot(SbBool isMajor, SbBool is3DContourLines, 
                               const Tisoline_list *contourLineList,
                               const StoreAnnotSpace *occuped_annot_space, 
                               int nb_annot) ;

  // Determine if an annotation is within polygon of annotation 
  SbBool annotWithinClipPolygon(const Ppoint *annot_space, const Plimit *annotBBox, 
                                const Plimit *clipPolygBBox) ;

  // Main method to generate the annotations of contour lines
  void computeContourLineAnnot(const Tisoline_list *majorContourLineList, 
                               const Tisoline_list *minorContourLineList, 
                               const Tisoline_list *allContourLineList, 
                               const Ppoint_list_list3 *mesh_contour, 
                               SbBool is3DContourLines, SbBool work_in_wc_flag) ;
  
  // Draw contour lines
  void drawContourLines(Tisoline_list *contourLinesList, 
                        const Ppoint_list_list3 *meshLimit) ;
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_MESHCONTOURING_ */

