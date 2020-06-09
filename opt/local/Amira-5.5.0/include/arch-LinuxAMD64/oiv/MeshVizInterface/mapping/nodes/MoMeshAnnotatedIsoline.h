/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MO_MESHANNOTATEDISOLINE_
#define  _MO_MESHANNOTATEDISOLINE_

#include <MeshVizInterface/MbVec3.h>
#include <MeshVizInterface/extractors/MiExtractorCallback.h>

#include <MeshVizInterface/mapping/nodes/MoMeshIsoline.h>

#include <Inventor/STL/vector>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

class MeXLineMeshUnstructured;
class MeXLineTopologyExplicitI;
class MiGeometryI;
class SoAnnoText3;
class SoText2;
class SoGroup;
class SoGetBoundingBoxAction;
class SoTextProperty;

class MxExtractorCallback;

/**
 * @DTEXT  Rendering node that displays annotated isolines.
 * 
 * @ingroup MeshIViz_Mapping_Representation
 * 
 * @DESCRIPTION
 *  This class is similar to MoMeshIsoline except that isolines can be annotated with their isovalue. @BR
 *
 *  Only major contour lines defined by the firstMajor and majorPeriod inherited fields can be annotated.
 *  The scalar set used to extract the isolines is defined by the inherited isoScalarSetId field. 
 *  This is an index into the list of scalar sets existing in the traversal state
 *  (see the MoScalarSetxxx nodes).  This scalar set must be defined per node to be valid.
 *
 *  The isolines can be colored using a scalar set defined in the colorScalarSetId inherited field.
 *  To disable coloring set this field to -1.
 *
 * @FILE_FORMAT_DEFAULT
 *    MeshIsoline {
 *    @TABLE_FILE_FORMAT
 *       @TR colorScalarSetId           @TD 0
 *       @TR parallel                   @TD TRUE
 *       @TR isovalues                  @TD 0.0
 *       @TR isoScalarSetId             @TD 0
 *       @TR majorPeriod                @TD 3
 *       @TR firstMajor                 @TD 0
 *       @TR majorLinePattern           @TD 0xFFFF
 *       @TR minorLinePattern           @TD 0xFFFF
 *       @TR isVisible        @TD TRUE
 *       @TR isText2D         @TD FALSE
 *       @TR path             @TD TANGENTIAL_PATH
 *       @TR upVector         @TD SbVec3f(0,1,0)
 *       @TR gap              @TD 0.0
 *       @TR fontSize         @TD 0.01
 *       @TR color            @TD SbColor(1,1,1)
 *       @TR isBackground     @TD FALSE
 *       @TR backgroundColor  @TD SbColor(0.3,0.3,0.3)
 *       @TR borderColor      @TD SbColor(1,1,1)
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *  MoMeshIsoline,
 *  MiIsolineExtractIj,
 *  MiIsolineExtractUnstructured
 *
 */

class MESHIVIZDM_API MoMeshAnnotatedIsoline : public MoMeshIsoline {

  SO_NODE_HEADER(MoMeshAnnotatedIsoline) ;

 public:

  /**
   * Constructor.
   */
  MoMeshAnnotatedIsoline() ;

  /**
   * Contour line annotation visibility.
   * Default is TRUE.
   */
  SoSFBool    isVisible ;

  /**
   * If TRUE, draw text using a SoText2D primitive (bitmapped text). 
   * Otherwise use a SoAnnoText3 (polygonal text).
   * Default is FALSE.
   * @note 2D text cannot have a background 
   */
  SoSFBool    isText2D ;

  /**
   *  Path of annotation text.
   */
  enum AnnotPath {
    TANGENTIAL_PATH, /**< Annotations are tangential to the contour lines.*/  
    HORIZONTAL_PATH, /**< Annotations are horizontal. */
    VERTICAL_PATH    /**< Annotations are vertical. */
         
  } ;

  /**
   * Annotation path. 
   *   - TANGENTIAL_PATH, annotations are tangential to the contour lines.
   *   - HORIZONTAL_PATH, annotations are horizontal.
   *   - VERTICAL_PATH,   annotations are vertical.
   *
   * Use enum #AnnotPath. Default is TANGENTIAL_PATH.
   */
  SoSFEnum    path ;

  /**
   * Annotation text up vector. This vector is used as the vertical axis of all annotations.
   * Default is (0,1,0).
   */
  SoSFVec3f    upVector ;

  /**
   * Curvilinear distance between two annotations of the same contour line. 
   * Default is 0 (a single annotation in the middle of the line).
   */
  SoSFFloat   gap ;

  /**
   * Font size of annotation text in mesh coordinates units.
   * When isText2D = FALSE, the real font size is a factor of this value and of the size of the mesh.
   * When isText2D = TRUE, the font size is given in points (same as SoText2D).
   * Default is 0.01 
   */
  SoSFFloat   fontSize ;

  /**
   * Color used for the annotation text 
   * Default is white = SbColor(1,1,1) 
   */
  SoSFColor   color ;
  
  /**
   * Defines if the annotations are framed by a background. Default is FALSE.
   * @note When isText2D = TRUE , isBackground has no effect.
   */
  SoSFBool    isBackground ;

  /**
   * Color used for the annotation background 
   * Default is gray = SbColor(0.3,0.3,0.3) 
   */
  SoSFColor   backgroundColor ;

  /**
   * Color used for the annotation background border.
   * Default is white = SbColor(1,1,1) 
   */
  SoSFColor   borderColor ;

  /**
  * Set the extraction callback which will be called each time an extraction is performed
  */
  void setExtractorCallback(MiExtractorCallback& extractorCallback);

  /*----------------------------------------------------------------------------*/
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 SoEXTENDER public:
  virtual void doExtract(SoAction * action);

 protected:
  virtual ~MoMeshAnnotatedIsoline() ;  
  void annotateLines(SoAction * action,const std::vector<const MeXLineMeshUnstructured*>& lines,double diag);

  MxExtractorCallback* m_redrawCallback;

  class ChordalDistance
  {
  public:
    std::vector< double > m_distances;
    SbBox3f m_bbox;
    size_t m_startCellIndex;
  };

  void computeChordalDistances(const MeXLineTopologyExplicitI& topo,const MiGeometryI& geom, std::vector< ChordalDistance >& chordalDistancesArray);
  template <typename _Mesh>
  double computeMeshDiagonalLength(_Mesh* mesh);
  void addAnnot(MbVec3d& pos, std::string& str, MbVec3d& baseVector, float width, float height);
  void getStringSize(SoAction * action, const std::string& str, float &width, float &height, SbBox3f& bbox);
  std::string computeString(SoAction * action,float isovalue,float& width,float& height,SbBox3f& annotBbox);
  std::vector<double>::iterator computeAnnotPos(ChordalDistance& chordalDistances, const std::vector<double>::iterator& beg, const std::vector<double>::iterator& end,
    double value,const MeXLineTopologyExplicitI& topo,const MiGeometryI& geom,MbVec3d& pos,MbVec3d& baseVector);
  void initSceneGraph(double diag);

  void clear();

  SoSeparator* m_sepAnnot;
  SoGroup* m_bboxGroup;
  SoAnnoText3* m_bboxText;
  SoText2* m_bboxText2;
  SoFont* m_font;
  SoGetBoundingBoxAction* m_bboxAction;
  SoTextProperty* m_textProp;
} ;

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /* _MO_MESHANNOTATEDISOLINE_ */



