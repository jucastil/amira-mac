/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MiPointProbeUnstructured_h
#define  _MiPointProbeUnstructured_h

#include <MeshVizInterface/mesh/data/MiDataSetI.h>
#include <MeshVizInterface/mesh/cell/MiCell.h>
#include <MeshVizInterface/mesh/data/MiDataSet.h>

class MiCellFilterI;
class MiVolumeMeshUnstructured;
class MiSurfaceMeshUnstructured;


/**
 * @DTEXT Probe at a given location in an unstructured mesh
 * 
 * @ingroup MeshIViz_Extract_Probe
 * 
 * @DESCRIPTION This class can be used to evaluate the value of a data set in the given mesh at any location.
 * The probe is internally building an octree onto volume meshes. This octree can be optimized by setting three 
 * environment variables (see SoPreferences).
 * 
 * MESHVIZ_OCTREE_CACHE_CELLBBOX allows to cache cell boundingboxes in order to speed up the search for cells in
 * the octree, thus probing faster.
 * The default is 0 (not cached)
 * 
 * MESHVIZ_OCTREE_MAX_CELL_PER_TILE specifies the maximum number of cells that can belong to a tile in the octree.
 * Note that only leaves can contain cells. Hence, this is the breaking criteria to split up a leaf and
 * distribute its cells into the new-born children. The smaller this number, the deeper the octree, which will speed up
 * probing but slow down the initialization stage.
 * The default is 40.
 *
 * MESHVIZ_OCTREE_MAX_DEPTH specifies the depth limit of the octree to prevent from using too much memory. 
 * Note that when reaching the depth limit, tiles at this level can exceed the number of cells allowed.
 * The default is 6.
 *
 */
class MESHIVIZ_API MiPointProbeUnstructured 
{
public:
  virtual ~MiPointProbeUnstructured() {}

  //@{
  /**
  * @copydoc MiInterpolatedLogicalSliceExtract::getNewInstance()
  */ 
  static MiPointProbeUnstructured* getNewInstance(const MiVolumeMeshUnstructured& mesh, bool parallel = true);
  static MiPointProbeUnstructured* getNewInstance(const MiSurfaceMeshUnstructured& mesh, bool parallel = true);
  //@}

  /**
  * @copydoc MiPointProbeIj::setLocation()
  */ 
  virtual bool setLocation(const MbVec3d& point, const MiCellFilterI* cellFilter=NULL) = 0;

  /**
  * Moves the current probe location at the given point. This method is 
  * similar and gives the same result as setLocation(). But, first it looks 
  * for the containing cell in the neighborhood of the cell having id @I cellId @i.
  * Then, if the neighborhood of this given cell does not contain the  
  * given point this method searches in the whole mesh like the method
  * setLocation().
  *
  * For instance, moveLocation() could be used instead of setLocation() when
  * the cell containing the point is already known, or when the displacement 
  * of the probe is not too large compared to the cell's size at the previous 
  * location of the probe. In this case, use getCellId() as input @I cellId @i 
  * argument.
  *
  * @param[in] point The destination point of the probe.   
  * @param[in] cellId input cell used as initial search criteria. If UNDEFINED_ID, 
  * this method is equivalent to setLocation().
  * @param[in] cellFilter The cell filter.   
  * @returns true if this location is inside the mesh, false otherwise.
  */
  virtual bool moveLocation(const MbVec3d& point, size_t cellId, const MiCellFilterI* cellFilter=NULL) = 0;

  /**
  * @copydoc MiPointProbeIj::isFound()
  */ 
  virtual bool isFound() const = 0;

  /**
  * @copydoc MiPointProbeIj::getValue()
  */ 
  template <typename _T>
  _T getValue(const MiDataSetI<_T>& dataset) const;

  /**
  * Gets the id of the cell of the mesh containing the current location of the probe.
  * @returns UNDEFINED_ID if the current location of the probe is outside the mesh.
  */
  virtual size_t getCellId() const = 0;

  /**
  * Gets the coordinates of the current location of the probe.
  */
  virtual const MbVec3d& getCoord() const = 0;

protected://PROTECTED_TO_DOCUMENT
  /**
  * Gets the weights at the current probe location. This weights are used by getValue() 
  * to compute a value at the current probe location.
  */
  virtual void getWeight(std::vector<double>& weight) const = 0;

  /**
  * Gets the cell of the mesh containing the current location of the probe.
  * This method is protected to have a public api the most similar to 
  * the MiPointProbeIjk.
  * 
  * @returns NULL if the current location of the probe is outside the mesh.
  */
  virtual const MiCell* getCell() const = 0;


};


//-----------------------------------------------------------------------------
template <typename _T>
inline _T MiPointProbeUnstructured::getValue(const MiDataSetI<_T>& dataset) const
{
  _T val(0);
  if (isFound())
  {
    if(dataset.getBinding()==MiDataSetI<_T>::PER_NODE)
    {
      const MiCell *cell = getCell();
      std::vector<double> weight(cell->getNumNodes());
      getWeight(weight);
      for (size_t i=0; i<cell->getNumNodes(); ++i)
        val += weight[i]*dataset.get(cell->getNodeIndex(i));
    }
    else
      val = dataset.get(getCellId());
  }
  return val;
}


#endif


