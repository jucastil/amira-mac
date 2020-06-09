/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MO_MESHCELLSHAPES_
#define  _MO_MESHCELLSHAPES_

#include <MeshVizInterface/MbVec3.h>

#include <MeshVizInterface/mapping/nodes/MoMeshRepresentation.h>

#include <Inventor/fields/SoMFInt32.h>
#include <MeshVizInterface/extractors/MiCellExtractIj.h>
#include <MeshVizInterface/extractors/MiCellExtractIjk.h>
#include <MeshVizInterface/mesh/cell/MiCellFilterI.h>
#include <MeshVizInterface/mesh/cell/MiCellFilterIj.h>
#include <MeshVizInterface/mesh/cell/MiCellFilterIjk.h>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

class MiLineMeshUnstructured;
class MiLineMeshCurvilinear;
class MiLineMeshRegular;
class MiVolumeMeshUnstructured;
class MiVolumeMeshUnstructuredIjk;
class MiVolumeMeshHexahedronIjk;
class MiVolumeMeshRegular;
class MiVolumeMeshRectilinear;
class MiVolumeMeshCurvilinear;
class MiCellExtractUnstructured;
class MiCellExtractUnstructuredIjk;

class MiTopologyI;
class MiVolumeTopologyExplicitIjk;
class MiGeometryI;

/**
 * @DTEXT  Rendering node that displays a set of cells of a mesh
 * 
 * @ingroup MeshIViz_Mapping_Representation
 * 
 * @DESCRIPTION
 *  This node renders an unstructured surface mesh defined by a set of cells in the original mesh.
 *  The set of cells to be rendered is specified by a list of cell indices. 
 *  The size of the rendered cells can be scaled up or down using the scaleFactor field and
 *  annotation of the cell and node names can optionally be displayed.
 *
 *  The cells can be colored using a scalar set defined in the colorScalarSetId inherited field.
 *  This is an index into the list of scalar sets existing in the traversal state
 *  (see the MoScalarSetxxx nodes). To disable coloring set this field to -1.
 *
 * @FILE_FORMAT_DEFAULT
 *    MeshCellShape {
 *    @TABLE_FILE_FORMAT
 *       @TR colorScalarSetId           @TD 0
 *       @TR parallel                   @TD TRUE
 *       @TR inclusiveList              @TD TRUE
 *       @TR cellIndices                @TD 0
 *       @TR scaleFactor                @TD 1.0
 *       @TR showCellName               @TD FALSE
 *       @TR showNodeName               @TD FALSE
 *    @TABLE_END
 *    }
 *
 * @SEE_ALSO
 *   MiCellExtractUnstructured, MiCellExtractUnstructuredIjk,
 *   MiCellExtractIjk, MiCellExtractIj
 * 
 */

class MESHIVIZDM_API MoMeshCellShape : public MoMeshRepresentation {

  SO_NODE_HEADER(MoMeshCellShape) ;

 public:

  /**
   * Constructor.
   */
  MoMeshCellShape() ;

  /**
  * When set to TRUE, the cellIndices field will represent the list of cells to display and
  * the list of cells to exclude otherwise. Default is TRUE. @n
  */
  SoSFBool inclusiveList;

  /**
  * Field representing the list of cells given by their index in the mesh.@n
  * If the mesh is unstructured, each value of cellIndices represents one cell.@n
  * If the mesh is a structured surface mesh, each cell is defined by a pair of indices (cellIndices(i),cellIndices(i+1)).@n
  * If the mesh is a structured volume mesh, each cell is defined by three indices (cellIndices(i),cellIndices(i+1),cellIndices(i+2)).@n
  * So, depending on the type of mesh, one, two or three indices are necessary to define each cell.
  * @note If the index list is empty, no cells are displayed when inclusiveList is set to TRUE and
  * all cells otherwise. Default is empty.
  */
  SoMFInt32  cellIndices;

  /**
  * Field representing the factor to resize extracted cells.@n
  * A factor lower than one will shrink cells, whereas a factor greater than one will expand cells.@n
  * Default is 1.0, which will not resize cells.
  */
  SoSFFloat factor;

  /**
  * When set to TRUE, the cell name is displayed near the cell. Default is FALSE. @n
  * The cell name is retrieved from the getCellName() method from the topology interface.@n
  * The default implementation returns the cell identifier.
  */
  SoSFBool showCellName;

  /**
  * When set to TRUE, the node names are displayed near the cell. Default is FALSE. @n
  * The node names are retrieved from the getNodeName() method from the topology interface.@n
  * The default implementation returns the node identifier.@n
  * @note For structured meshes, this field is not used since nodes are computed implicitly. 
  */
  SoSFBool showNodeName;

  /**
  * Field representing the distance to shift the display of node names away from the
  * node coordinates.@n
  * A negative offset will display node names inside the cell, whereas a positive offset 
  * will display them outside the cell.@n
  * @note The offset is relative to the cell's size if the relativeOffset field is set to TRUE.
  * Otherwise it represents an absolute distance.
  * Default is 0.1, which will slightly shift node names outside the cell.
  */
  SoSFFloat offset;

  /**
  * When set to TRUE, the distance between the node and the name to display is relative to 
  * the size of the cell@n
  * @note For unstructured meshes, the offset field is then multiplied by the getRelativeSize() method 
  * from the cell interface. A default implementation of getRelativeSize() returns 1 which will
  * leave the offset as an absolute distance. getRelativeSize() needs to be overloaded to activate
  * this feature for unstructured mesh (see class MiCell).
  * Default is FALSE.
  */
   SoSFBool relativeOffset;

  //@{
  /** 
  * Get extractor for reuse outside this node. 
  * @note The returned pointer may be null if a mesh has not been set in the scene graph 
  * or if no render action has traversed the scene graph. 
  * Use the method corresponding to the type of mesh stored in the scene graph. 
  * 
  */
  const MiCellExtractUnstructured*    getUnstructuredExtractor();
  const MiCellExtractUnstructuredIjk* getUnstructuredIjkExtractor();
  const MiCellExtractIjk*             getIjkExtractor();
  const MiCellExtractIj*              getIjExtractor();
  //@}

  /** 
  * @deprecated Use getIjkExtractor() instead.
  * @DEPRECATED_SINCE_OIV 8.5
  */
  const MiCellExtractIjk*             getRegularExtractor();

  /** 
  * @deprecated Use getIjExtractor() instead.
  * @DEPRECATED_SINCE_OIV 8.5
  */
  const MiCellExtractIj*              getSurfaceRegularExtractor();

  /*----------------------------------------------------------------------------*/
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 SoEXTENDER public:
  virtual void doExtract(SoAction *action);
  virtual const MiMesh* getExtractedMesh(MeshType& meshType);

  // computes the extract of the data set corresponding to the given index in the state list from the current representation's extractor.
  virtual const MiScalardSetI* extractScalarSetI(SoState * state,size_t scalarSetId) ;

  // computes the extract of the data set corresponding to the given index in the state list from the current representation's extractor.
  virtual const MiVec3dSetI* extractVec3SetI(SoState * state,size_t scalarSetId) ;


 protected:
  virtual ~MoMeshCellShape() ;  

  void clear();

  std::vector<size_t>& buildIndexListI();
  std::vector<size_t> m_indexListI;
  std::vector<MiCellExtractIj::couple>& buildIndexListIj();
  std::vector<MiCellExtractIj::couple> m_indexListIj;
  std::vector<MiCellExtractIjk::triplet>& buildIndexListIjk();
  std::vector<MiCellExtractIjk::triplet> m_indexListIjk;

  template<typename _MeshInterface, typename _Extractor, typename _ScalarSet, typename _CellFilter, typename _Tuple>
  void doExtract(SoState * state,const _MeshInterface* mesh, _Extractor** extractor,const _CellFilter *cellFilter, std::vector<_Tuple>& indexList);

  template<typename _Extractor, typename _ScalarSet, typename _CellFilter, typename _Tuple>
  void extract(SoState * state,_Extractor* extractor, const _ScalarSet* colorSet,const _CellFilter *cellFilter, std::vector<_Tuple>& indexList);

  // Extractors used internally
  MiCellExtractUnstructured*    m_cellExtractU;
  MiCellExtractUnstructuredIjk* m_cellExtractUIjk;
  MiCellExtractIjk*             m_cellExtractIjk;
  MiCellExtractIj*              m_cellExtractIj;

  class DisplayName
  {
  public:
    std::string m_name; // Name of the cell
    MbVec3d     m_pos;  // Where to display the name
    bool operator==(const DisplayName& c1) const {return m_name == c1.m_name && m_pos ==c1.m_pos;}
  };
  std::vector<DisplayName> m_cellNames;
  std::vector<DisplayName> m_nodeNames;

  template <typename _Iterator, typename _Topology, typename _Tuple>  
  void getDisplayCellList(const _Topology& topology, std::vector<_Tuple>& indexList, std::vector<_Tuple>& cellIds);

  void buildDisplayNamesListI(const MiMeshUnstructuredI& mesh, const MiCellFilterI* cellFilter);
  void buildDisplayNamesListIj(const MiTopologyIj& topology, const MiGeometryI& geometry, const MiCellFilterIj* cellFilter);
  void buildDisplayNamesListIjk(const MiVolumeTopologyExplicitIjk& topology, const MiGeometryI& geometry, 
                                const MiCellFilterIjk* cellFilter, bool displayNodes = true);

  void displayNames(std::vector<DisplayName>& newDisplayNames, std::vector<DisplayName>& currentDisplayNames, SoSeparator*& nameSep);

  SoSeparator* m_nodeNamesSep;
  SoSeparator* m_cellNamesSep;

  class CellFilter : public MiCellFilterI, public MiCellFilterIj, public MiCellFilterIjk
  { 
  public:
    CellFilter();
    bool acceptCell(size_t cellIndex) const;
    bool acceptCell(size_t i, size_t j) const;
    bool acceptCell(size_t i, size_t j, size_t k) const;
    size_t getTimeStamp() const;
    void set(std::vector<size_t>& exclusionListI, const MiCellFilterI* userCellFilter);
    void set(std::vector<MiCellExtractIj::couple>& exclusionListIj, const MiCellFilterIj* userCellFilter);
    void set(std::vector<MiCellExtractIjk::triplet>& exclusionListIjk, const MiCellFilterIjk* userCellFilter);
  private:
    template < typename _vectorT > void copy( _vectorT& exclusionListI, _vectorT& newListI);
    std::vector<size_t> m_exclusionListI;
    std::vector<MiCellExtractIj::couple> m_exclusionListIj;
    std::vector<MiCellExtractIjk::triplet> m_exclusionListIjk;
    const MiCellFilterI*   m_userCellFilterI;
    const MiCellFilterIj*  m_userCellFilterIj;
    const MiCellFilterIjk* m_userCellFilterIjk;
    const MiCellFilter*    m_currentCellFilter;
    mutable size_t m_userTS;
    mutable size_t m_timeStamp;
  };
  CellFilter m_excludedCellFilter;

} ;

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /* _MO_MESHCELLSHAPES_ */



