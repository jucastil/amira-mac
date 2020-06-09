/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MiPointProbeVolumeUnstructuredIjk_h
#define _MiPointProbeVolumeUnstructuredIjk_h

#include <MeshVizInterface/extractors/MiPointProbeIjk.h>
#include <MeshVizInterface/mesh/MiVolumeMeshUnstructuredIjk.h>
#include <MeshVizInterface/mesh/MiVolumeMeshHexahedronIjk.h>


#include<Inventor/STL/cassert>

/**
 * @DTEXT Probe at a given location in an unstructured IJK volume mesh
 * 
 * @ingroup MeshIViz_Extract_Probe
 * 
 * @DESCRIPTION This class can be used to evaluate the value of a data set in the given mesh at any location.
 * The probe is internally building an octree onto the mesh. This octree can be optimized by setting three 
 * environment variables (see MiPointProbeUnstructured and SoPreferences). 
 * 
 */
class MESHIVIZ_API MiPointProbeUnstructuredIjk : virtual public MiPointProbeIjk
{
public:
  //@{
  /**
  * @copydoc MiInterpolatedLogicalSliceExtract::getNewInstance()
  */ 
  static MiPointProbeUnstructuredIjk* getNewInstance(const MiVolumeMeshUnstructuredIjk& mesh, bool parallel = true);
  static MiPointProbeUnstructuredIjk* getNewInstance(const MiVolumeMeshHexahedronIjk& mesh, bool parallel = true);
  //@}

  /**
  * Gets the value at the current probe location in the given PER_NODE dataset.
  * The returned value is meaningless if the probe location is outside the
  * mesh (when isFound() is false).
  */
  template <typename _T>
  _T getValue(const MiDataSetI<_T>& dataset) const;

  /**
  * Gets the value at the current probe location in the given PER_CELL dataset.
  * The returned value is meaningless if the probe location is outside the
  * mesh (when isFound() is false).
  */
  template <typename _T>
  _T getValue(const MiDataSetIjk<_T>& dataset) const;

protected://PROTECTED_TO_DOCUMENT
  /**
  * Gets the cell of the mesh containing the current location of the probe.
  * This method is protected to have a public api the most similar to 
  * the MiPointProbeIjk.
  * 
  * @returns NULL if the current location of the probe is outside the mesh.
  */
  virtual const MiVolumeCell* getCell() const = 0;

};

//-----------------------------------------------------------------------------
template <typename _T>
inline _T MiPointProbeUnstructuredIjk::getValue(const MiDataSetI<_T>& dataset) const
{
  _T val(0);
  if (isFound())
  {
    assert(dataset.getBinding()==MiDataSetI<_T>::PER_NODE);
    const MiCell *cell = getCell();
    std::vector<double> weight(cell->getNumNodes());
    getWeight(weight);
    for (size_t i=0; i<cell->getNumNodes(); ++i)
      val += weight[i]*dataset.get(cell->getNodeIndex(i));
  }
  return val;
}

//-----------------------------------------------------------------------------
template <typename _T>
inline _T MiPointProbeUnstructuredIjk::getValue(const MiDataSetIjk<_T>& dataset) const
{
  _T val(0);
  if (isFound())
  {
    assert(dataset.getBinding()==MiDataSetIjk<_T>::PER_CELL);
    size_t icell,jcell,kcell;
    getCellId(icell,jcell,kcell);
    val = dataset.get(icell,jcell,kcell);
  }
  return val;
}

#endif


