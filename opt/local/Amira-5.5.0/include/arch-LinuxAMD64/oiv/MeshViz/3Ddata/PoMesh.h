/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_MESH_
#define  _PO_MESH_

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoMaterialBinding.h>
#include <Inventor/nodes/SoNormal.h>
#include <Inventor/nodes/SoNormalBinding.h>
#include <Inventor/nodes/SoTextureCoordinateBinding.h>
#include <Inventor/nodes/SoTextureCoordinate2.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoShapeHints.h>
#include <Inventor/nodes/SoIndexedShape.h>

#include <MeshViz/3Ddata/Po3DdataMaster.h>
#include <MeshViz/misc/PbArrayOfLong.h>
#include <MeshViz/graph/PbLinearDataMapping.h>
#include <MeshViz/graph/PbIsovaluesList.h>

#include <Inventor/STL/vector>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

class PbMesh;
class PbDataMapping;
class PiContouringLines;
class PiContouringFilled;
class PiTextureContouring;
class PoCellFilter;

/**
 * @DTEXT  Base class for all mesh representations.
 * 
 * @ingroup MeshRepresentation
 * 
 * @DESCRIPTION
 *    A representation of a mesh may depend on other MeshViz objects : 
 *    The current mesh, the current data-mapping, the current module-data-mapping,
 *    the current isovalues list, the current domain, the current numeric display
 *    format and the current miscellaneous text attributes.
 * 
 *    If the method setMesh(mesh) is called with "mesh" derived from PbMesh, 
 *    the current mesh is "mesh". Otherwise the current mesh has a type 
 *    derived from PoMeshProperty and is inherited during the traversal. 
 *    If the setMesh method is not called and if there is not any node 
 *    PoMeshProperty before the PoMesh node in the scene graph, the 
 *    representation is empty.
 * 
 *    If the method setDataMapping(data_mapping) is called with "data_mapping"
 *    derived from PbDataMapping, the current data mapping is "data_mapping".
 *    Otherwise the current data-mapping has a type derived from PoDataMapping
 *    and is inherited during the traversal. The current data-mapping is not
 *    used if coloringType == COLOR_INHERITED, or if valuesIndex is not
 *    defined (i.e. < 0), or if the set of values refered by valuesIndex does
 *    not exist in the current mesh. If there is no current data-mapping
 *    (i.e setDataMapping not called and no PoDataMapping node before in the 
 *    scene graph), the inherited color is used for part of the representation.
 * 
 *    If the method setModuleDataMapping(mod_data_mapping) is called with
 *    "mod_data_mapping" derived from PbDataMapping, the current module
 *    data mapping is "mod_data_mapping". Otherwise if the field 
 *    moduleDataMapping contains a node of a type derived from PoDataMapping,
 *    the current module data-mapping is defined by this nod. Otherwise the 
 *    current module data-mapping has a type derived from PoDataMapping
 *    and is inherited during the traversal. The current module data mapping
 *    is used by PoMesh2DVec and PoMesh3DVec class.
 * 
 *    If the setIsovaluesList(isovalues_list) is called with "isovalues_list" 
 *    derived from PbIsovaluesList, the current isovalues list is 
 *    "isovalues_list".Otherwise the current isovalues list has a type 
 *    PoIsovaluesList and is inherited during the traversal. If the current
 *    isovalues list does not exist (i.e. setIsovaluesList not called and
 *    no PoIsovaluesList before in the scene graph), the PoMeshContouring
 *    make an empty representation, and the other representation classes work
 *    like if coloringType was equal COLOR_MAPPING.
 *    
 *    See PoBase for definition of the current domain.
 * 
 */
class MESHVIZ_API PoMesh : public Po3DdataMaster {

  SO_KIT_HEADER(PoMesh) ;

 public:

  /* Fields */

  /**
   * Defines the index of the set of values for the coloring. If valuesIndex = -1, (the 
   * valuesIndex is called undefined) a mesh representation is colored with only one 
   * color which is inherited. If valuesIndex >= 0, the representation is colored 
   * relating to each node value, and relating to the coloring method defined by the 
   * field coloringType.
   */
  SoSFInt32  valuesIndex;

  /**
   * Specifies the index of the set of values used to filter cells for this mesh
   * representation. The value of the cell is checked as follows:
   * 
   * If PoCellFilter::acceptCell(id,(getMesh()->getValuesSet(valuesIndexForCellFilter))[id]) 
   * returns FALSE, the cell is not taken into account by this representation. (id is the 
   * index of the cell to be checked.)
   * 
   * Warning: The values of the selected data set must be located at cells 
   * (see PoMeshProperty::addValuesSet(int,DataBinding,float *), use DataBinding::PER_CELL).
   */
  SoSFInt32  valuesIndexForCellFilter;

  /**
   * Defines the index of the set of vectors for all representations which need
   * a vector at each mesh node (PoBaseStreamLine, PoMesh2DVec,
   * PoMesh3DVec,...)
   */
  SoSFInt32  vecsIndex;

  /**
   *  Coloring type.
   */
  enum ColoringType {
    COLOR_INHERITED,
    COLOR_AVERAGE,
    COLOR_MAPPING,
    COLOR_CONTOURING,
    COLOR_TEXTURE_CONTOURING
  } ;



  /**
   * Defines the type of method used to color each mesh element, mesh edge or 
   * mesh contour line of a representation.
   *
   * #COLOR_INHERITED: Each element of a mesh representation is colored with 
   * the same inherited color, even if valuesIndex field is defined (valuesIndex >= 0).
   * 
   * #COLOR_AVERAGE: Each edge of a wireframe representation of the mesh 
   * (classes PoMeshLimit, PoMeshLines) is colored by a single color defined by 
   * the average value of its extremities mapped on a PbDataMapping object.
   * Each element of a solid surface representation of the mesh (classes 
   * PoMeshSides, PoMeshFilled) is colored by a single color defined by the 
   * average value of its nodes mapped on a PbDataMapping object.
   * However, an inherited coloring is done if the field valuesIndex is not defined 
   * or if there is no set of values of which the index is valuesIndex.
   *
   * #COLOR_MAPPING: Each mesh edge or mesh element of a representation is 
   * colored by using the "data mapping" method defined by a PbDataMapping 
   * object. The PbDataMapping object defines how the mesh values (referenced by 
   * valuesIndex field) are transformed into colors. 
   * However, an inherited coloring is done if the valuesIndex field is not defined 
   * or if there is no set of values of which index is valuesIndex.
   *
   * #COLOR_CONTOURING: Each mesh edge of a wireframe representation is 
   * colored relating to both of its extremity values v1 and v2,  to the isovalues 
   * between v1 and v2, and to the PbDataMapping object which defines the color 
   * associated to these values. If some isovalues of the PbIsovaluesList object exist 
   * between v1 and v2, the edge is cut into several segments. Each segment is 
   * colored with a single color.
   * Each mesh element of a filled representation is colored relating to its node 
   * values, to the isovalues between these values, and to the PbDataMapping 
   * object which defines the color associated to these values. If some isovalues of 
   * the PbIsovaluesList object exist between these values, the element is cut up 
   * into several small surfaces. Each small surface is colored with a single color. 
   * The boundary between 2 small surfaces is part of a contour line.
   * However, an inherited coloring is done if the valuesIndex field is not defined 
   * or if there is no set of values of which the index is valuesIndex.
   * 
   * #COLOR_TEXTURE_CONTOURING: Same as #COLOR_CONTOURING but a texture is used 
   * for creating contours. This method dramatically decreases the amount of
   * generated geometry 
   * and speeds up the computation time of filled representations relative to 
   * the #COLOR_CONTOURING method.
   * This mode should be used for all animations.
   *
   * The catalog part appearance.texture2 contains the contour texture and the catalog
   * part appearance.complexity.textureQuality is set to 0.1f to activate nearest 
   * (as opposed to linear) texture filtering.
   *
   * This method should not be used for wireframe representations because texturing
   * is not active in wireframe. Also, you may see some slight differences compared 
   * to #COLOR_CONTOURING for meshes with few cells.
   * Shapes or cells that contain an undefined value will @I not@i
   * be discarded. For example, cells that are more transparent than the value
   * specified by PoDataMapping::transparencyValueDeletedParts will not be
   * discarded when using this mode.
   *
   *
   */
  SoSFEnum   coloringType;

  /**
   * Field used to do coloring according the module of the vectors.
   * It is used only if setModuleDataMapping is not called and if the field
   * contains a node derived from PoDataMapping.
   */
  SoSFNode   moduleDataMapping;

  /**
  * If set to true and combined with COLOR_TEXTURE_CONTOURING coloring type, 
  * the texture used for coloring appears smoothed, since a linear interpolation is used 
  * instead of a nearest one.
  *  @FIELD_SINCE_OIV 8.1 
  */
  SoSFBool smoothTextureContouring;

  /**
   * Indicates the minimum angle (in radians) between two adjacent face normals
   * required to form a sharp crease at the edge when default normals are computed
   * and used. Default is 0. Default in Open Inventor 5.0 and earlier was 0.8.
   *
   * You can specify the default crease angle using the configuration parameter
   * OIV_3DDATA_CREASE_ANGLE. See SoPreferences for details.
   *
   * @FIELD_SINCE_OIV 6.0 
   */
  SoSFFloat  creaseAngle;


  /* Set Methods */

  /**
   * Sets a reference to a PbMesh object. 
   */
  void setMesh(PbMesh *mesh);

  /**
   * Sets a reference to a PbDataMapping object for the association color-value. 
   * The data mapping is not used if the field coloringType = COLOR_INHERITED
   */
  void setDataMapping( PbDataMapping *data_mapping);

  /**
   * Sets a reference to a PbDataMapping object for the association color-vectors 
   * module. 
   */
  void setModuleDataMapping( PbDataMapping *mod_data_mapping); 

  /**
   * Sets a reference to a PbIsovaluesList object to define a list of isovalues. 
   * The isovalues list is used by a PoMeshContouring object, and by the others
   * mesh representations objects when coloringType = COLOR_CONTOURING.
   */
  void setIsovaluesList(PbIsovaluesList *isovalues_list);



  /* Get Methods */

  /**
   * Gets the current PbMesh object. 
   */
  const PbMesh * getMesh() const;

  /**
   * Returns the current PbDataMapping object.
   */
  const PbDataMapping * getDataMapping() const;

  /**
   * Returns the current PbDataMapping object for the association color-vectors 
   * module.
   */
  const PbDataMapping * getModuleDataMapping() const;

  /**
   * Returns the current PbIsovaluesList object.
   */
  const PbIsovaluesList *getIsovaluesList() const;

  /*----------------------------------------------------------------------------*/


 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

  const PoCellFilter* getCellFilter() const;

  void push_back_value(float v) {
    if (m_numValues == m_allocPointValues) {
      m_allocPointValues *= 2;
      m_pointValues = (float *)realloc(m_pointValues, m_allocPointValues*sizeof(float));
    }
    m_pointValues[m_numValues] = v; 
    m_numValues++;
  }
  void push_back_coord_index(int32_t id) {
    m_coordIndexArray.push_back(id);
  }
  void push_back_cell_index(int32_t id) {
    m_cellIndexArray.push_back(id); //add(id);
  }

  void update_coord_index(SoIndexedShape *shape) {
    SoMFInt32 *coord_index = &(shape->coordIndex);
    if (m_coordIndexArray.size() == 0) 
      coord_index->setNum(0);
    else
      coord_index->setValuesPointer((int)m_coordIndexArray.size(),&*(m_coordIndexArray.begin()));
  }

  /**
   * Gets the number of bytes allocated by this instance
   */
  virtual size_t getMemorySize();

  /**
   * Gets the number of bytes allocated by this class
   */
  static size_t getClassMemorySize();
  

 protected:
  // Constructor
  PoMesh() ;
  // Destructor
  virtual ~PoMesh() ;  

  void clearOivNodes();
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void basicObjectChange(PbBase *basicObj);
  virtual void setDefaultOnNonWritingFields();
  virtual void addElementsAllCaches() ;
  virtual void preRebuild();
  virtual void postRebuild() ;
  virtual void insertDefaultShapeHints();

  // list of isovalues 
  int        TAllocAdjIsovalues;
  int        TAdjNumIsovalues;
  float      *TAdjIsovalues;
  int        TIsovalAdj; 

  void adjustIsovalList (int num_v0, const float* v0, 
                         int num_v1, const float* v1, 
                         int num_v2, const float* v2 );
  void adjustIsoval (int num_values, const float *values, float &iso_value);
  void adjustIsovalMultiple (int num_v0, const float* v0, 
                             int num_v1, const float* v1, 
                             int num_v2, const float* v2,
                             float &iso_value);


  SbVec3f *newSbVec3f(int numVec3f) ;

  // Coordinates
  SoCoordinate3               *meshCoordinates;

  // Material
  SoMaterial                  *meshMaterial;
  SoMaterialBinding           *m_materialBinding;
  SbBool                      m_meshMaterialJustAllocated;

  // shape
  SoShape                     *m_shape;

  // normals
  SoNormal                    *m_normal;
  SoNormalBinding             *m_normalBinding;

  // Textures data for texture contouring
  SoTextureCoordinate2        *m_meshTexCoordinates ;
  SbBool                      m_meshTexCoordinatesJustAllocated;
  SoTexture2                  *m_meshTexture ;
  SoTextureCoordinateBinding  *m_textureBinding;

  SoGroup                     *groupNode;
  SoShapeHints                *shapeHints;


  PiTextureContouring         *m_textureContouring ;
  PiContouringFilled          *contouringFilled;
  PiContouringLines           *contouringLines;

  // default dataMapping (linear)
  PbLinearDataMapping defDataMapping;

  static int   m_numPoints;
  static int   m_allocPoints;
  static float (*m_points)[3];
  static int   m_numValues;
  static int   m_allocPointValues;
  static float *m_pointValues;
 
  std::vector< int >  m_coordIndexArray;
  std::vector< int >  m_cellIndexArray;

  const PbDataMapping *dataMapping;          // data mapping used by rebuild()
  const PbDataMapping *m_moduleDataMapping;  // module data mapping used by rebuild()
  const PbIsovaluesList *isovaluesList;      // isovalues list used by rebuild()

  const PbMesh *m_mesh;                   // mesh used by derived Po classes
  ColoringType m_coloringType;            // coloringType used by derived Po classes
  SbBool       m_isVertexBinding;         // TRUE if PER_VERTEX, FALSE if PER_FACE binding
  const float *m_mappedValues;            // dataset used to map color onto shape
  std::vector< int > m_cellIds;                    // cell ids used for per_cell data

  void addDataMappingInCache();
  void addIsovaluesListInCache(SbBool alwaysAdd=FALSE);

  void mapColor(int num_val=0, const float *from_values=NULL, 
                SbBool newMat=TRUE);
  void computeNormal(SoIndexedShape *shape, SoCoordinate3 *coord);
  
  // some member giving info about the last built
  uint32_t m_geometryId;         // State of the geometry used by the last rebuilt
  uint32_t m_topologyId;         // State of the topology used by the last rebuilt
  int      m_mappedDataSetIndex; // index of data set used for color map at last built
  uint32_t m_mappedDataSetId;    // State of the data set used by the last rebuilt
  uint64_t m_cellFilterId;       // State of the filter used by the last rebuilt
  uint32_t m_dataFilterId;       // State of the data set used by the last cell filter
  uint32_t m_dataMappingId;      // State of the PoDataMapping used by the last rebuilt
  int      m_isoDataSetIndex;    // index of data set used for color map at last built
  uint32_t m_isoDataSetId;       // State of the data set used by the last rebuilt
  float    m_isovalueId;         // Last isovalue used by the last isosurf/cross section built
  ColoringType m_previousColoringType;   // coloringType used by the previous built

  /*----------------------------------------------------------------------------*/
 private:
  PbMesh          *m_meshSet;             // mesh set by the setMesh method
  PbDataMapping   *m_dataMappingSet;
  PbDataMapping   *m_moduleDataMappingSet;
  PbIsovaluesList *m_isovaluesListSet;

  // Sensors
  FieldSensorList m_fieldSensorList ;

  // List of fields defined in this class
  SoFieldList     m_fieldList ;

  // Array of Vec3f
  SbVec3f *arraySbVec3f;
  int     arrayLenSbVec3f;

  // default isovalues list
  PbIsovaluesList defIsovaluesList;
} ;

/*----------------------------------------------------------------------------*/
#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /* _PO_MESH_ */

