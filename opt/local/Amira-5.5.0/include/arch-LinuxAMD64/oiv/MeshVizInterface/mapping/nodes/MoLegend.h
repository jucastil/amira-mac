/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MoLegend_
#define  _MoLegend_

#include <MeshVizInterface/mapping/nodes/MoMeshBaseRepresentation.h>
#include <MeshVizInterface/implement/colormapping/MbLevelColorMapping.h>
#include <MeshVizInterface/implement/colormapping/MbLinearColorMapping.h>
#include <MeshVizInterface/implement/mesh/surfaces/MbSurfaceMeshRectilinear.h>

#include <Inventor/fields/SoSFDouble.h>
#include <Inventor/fields/SoSFVec2f.h>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

class SoState;
class MoScalarSetIj;
class MoMesh;
class MoMeshSurface;
class SbColorRGBA;
class MbPredefinedColorMapping;
class MxScalarSetIj;

/**
* @DTEXT  Rendering node that displays a legend.
* 
* @ingroup MeshIViz_Mapping_Representation
* 
* @DESCRIPTION
*  Displays a legend representing the current colormap.
*  A colormap is specified using the MoColorMapping derived nodes. 
*
* The legend is drawn in a rectangle defined by the bottomLeft and topRight 
* 2D points given in Normalized Device Coordinates [0..1].
* 
* @FILE_FORMAT_DEFAULT
*    Legend {
*    @TABLE_FILE_FORMAT
*       @TR bottomLeft        @TD SbVec3f(0,0)
*       @TR topRight          @TD SbVec3f(0,1)
*       @TR minValue          @TD 0
*       @TR maxValue          @TD 0
*       @TR vertical          @TD FALSE
*       @TR title             @TD ""
*       @TR titleFontSize     @TD 10
*       @TR titlePosition     @TD POS_BOTTOM
*       @TR displayValues     @TD FALSE
*       @TR valuesFontSize    @TD 10
*    @TABLE_END
*    }
*
* @SEE_ALSO
*  MoColorMapping
* 
*/

class MESHIVIZDM_API MoLegend : public MoMeshBaseRepresentation {

  SO_NODE_HEADER(MoLegend) ;

public:

  /**
  * Constructor.
  */
  MoLegend() ;

  /**
  * Bottom left corner of the rectangle in which the legend will be drawn.
  * In NDC units [0..1]. Default is (0,0).
  */
  SoSFVec2f bottomLeft;

  /**
  * Top-right corner of the rectangle in which the legend will be drawn.
  * In NDC units [0..1]. Default is (0,1).
  */
  SoSFVec2f topRight;

  /**
  * The minimum value defining the range of data to display in the legend.
  * Default 0.
  * @note If not set (minValue = maxValue = 0), the min and max values are retrieved from the colormap.
  */
  SoSFDouble minValue;

  /**
  * The maximum value defining the range of data to display in the legend.
  * Default 0.
  * @note If not set (minValue = maxValue = 0), the min and max values are retrieved from the colormap.
  */
  SoSFDouble maxValue;

  /**
  * If TRUE, the legend is vertical. Otherwise it is horizontal.
  * Default FALSE (horizontal)
  */
  SoSFBool vertical;

  /**
  * The title of the legend.
  */
  SoSFString title;

  /**
  * The size of the font for the title of the legend. Default 10 pixels.
  */
  SoSFFloat titleFontSize;

  /**
   *  Position of the title.
   */
  enum Position {   
    POS_BOTTOM,  /**< Bottom. */
    POS_TOP,     /**< Top.    */
    POS_RIGHT,   /**< Right.  */
    POS_LEFT     /**< Left.   */
  } ;

  /**
  * The position of the title relative to the legend box. 
  * Use enum #Position. Default is POS_BOTTOM.
  */
  SoSFEnum titlePosition;

  /**
  * If TRUE, display the minimal and maximal values of the colormap. 
  * Default FALSE.
  */
  SoSFBool displayValues;

 /**
  * The size of the font for the values of the legend. Default 10 pixels.
  */
  SoSFFloat valuesFontSize;


  /*----------------------------------------------------------------------------*/
  SoEXTENDER public:
  virtual void doAction(SoAction *action);

  SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

protected:
  virtual ~MoLegend() ;  

  bool haveValuesChanged(SoState* state);
  void fillLegend(SoState* state);
  void fillLevelCM(SoState* state, const MbLevelColorMapping<double,SbColorRGBA>* levelCM);
  void fillLinearCM(SoState* state, const MbLinearColorMapping<double,SbColorRGBA,float>* linearCM);
  void fillPredefCM(SoState* state, const MbPredefinedColorMapping* predefCM);
  void fillCustomCM(SoState* state, const MiColorMapping<double,SbColorRGBA>* customCM);
  void createMesh(SoState* state, int ind, std::vector<float>& coords0, std::vector<float> coords1, float xmin, float xmax, double vmin, double vmax);
  void getLegendRange(const MiColorMapping<double, SbColorRGBA>* cmap,double& vmin,double& vmax);

  void drawTitle(SoState* state);
  void drawValues(SoState* state,double vmin, double vmax);
  
  void clear();

  size_t m_colorMapTimeStamp;

  MoMesh*        m_mesh;
  MoScalarSetIj* m_scalarSetIj;
  MoMeshSurface* m_meshSurface;
  SoSeparator*   m_textGroup;
  SoSeparator*   m_valuesGroup;
  MbSurfaceMeshRectilinear<float,double,MbVec3f > * m_legendMesh;
  MxScalarSetIj* m_scalarSet;
} ;

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /* _MoLegend_ */



