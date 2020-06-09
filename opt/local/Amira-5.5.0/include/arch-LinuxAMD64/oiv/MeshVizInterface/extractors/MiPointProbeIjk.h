/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MiPointProbeIjk_h
#define  _MiPointProbeIjk_h

#include <MeshVizInterface/extractors/MiPointProbeUnstructured.h>

#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>
#include <MeshVizInterface/mesh/cell/MiCell.h>

class MiCellFilterIjk;
class MiVolumeMeshRegular;
class MiVolumeMeshRectilinear;
class MiVolumeMeshCurvilinear;
class MiVolumeMeshUnstructuredIjk;

/**
 * @DTEXT Probe at a given location in a structured volume mesh
 * 
 * @ingroup MeshIViz_Extract_Probe
 * 
 * @DESCRIPTION This class can be used to evaluate the value of a data set in the given mesh at any location.
 * The probe is internally building an octree onto the curvilinear meshes. This octree can be optimized by setting three 
 * environment variables (see MiPointProbeUnstructured and SoPreferences).
 * 
 * 
 */
class MESHIVIZ_API MiPointProbeIjk 
{
public:
  virtual ~MiPointProbeIjk() {}

  //@{
  /**
  * @copydoc MiInterpolatedLogicalSliceExtract::getNewInstance()
  */ 
  static MiPointProbeIjk* getNewInstance(const MiVolumeMeshRegular& mesh, bool parallel = true);
  static MiPointProbeIjk* getNewInstance(const MiVolumeMeshRectilinear& mesh, bool parallel = true);
  static MiPointProbeIjk* getNewInstance(const MiVolumeMeshCurvilinear& mesh, bool parallel = true);
  static MiPointProbeIjk* getNewInstance(const MiVolumeMeshUnstructuredIjk& mesh, bool parallel = true);
  //@}

  /**
  * @copydoc MiPointProbeIj::setLocation()
  */ 
  virtual bool setLocation(const MbVec3d& point, const MiCellFilterIjk* cellFilter=NULL) = 0;

  /**
  * Moves the current probe location at the given point. This method is 
  * similar and gives the same result as setLocation(). But, first it looks 
  * for the containing cell in the neighborhood of the cell having id
  * @I (cellIdI,cellIdJ,cellIdK)  @i.
  * Then, if the neighborhood of this given cell does not contain the  
  * given point this method searches in the whole mesh like the method
  * setLocation().
  *
  * For instance, moveLocation() could be used instead of setLocation() when
  * the cell containing the point is already known, or when the displacement 
  * of the probe is not too large compared to the cell's size at the previous 
  * location of the probe. In this case, use getCellId() to retrieve the cells indices.
  *
  * @param[in] point The destination point of the probe.   
  * @param[in] cellIdI input cell I index used as initial search criteria. If UNDEFINED_ID, 
  * this method is equivalent to setLocation().
  * @param[in] cellIdJ input cell J index used as initial search criteria. If UNDEFINED_ID, 
  * this method is equivalent to setLocation().
  * @param[in] cellIdK input cell K index used as initial search criteria. If UNDEFINED_ID, 
  * this method is equivalent to setLocation().
  * @param[in] cellFilter The cell filter.   
  * @returns true if this location is inside the mesh, false otherwise.
  */
  virtual bool moveLocation(const MbVec3d& point, size_t cellIdI, size_t cellIdJ, size_t cellIdK, 
                            const MiCellFilterIjk* cellFilter=NULL) = 0;

  /**
  * @copydoc MiPointProbeIj::isFound()
  */ 
  virtual bool isFound() const = 0;

  /**
  * @copydoc MiPointProbeIj::getValue()
  */ 
  template <typename _T>
  _T getValue(const MiDataSetIjk<_T>& dataset) const;

  /**
  * Gets the ids of the cell of the mesh containing the current location of the probe.
  * i, j and k are set to UNDEFINED_ID if the current location of the probe is outside the mesh.
  * @param[out] i the first id of the cell. 
  * @param[out] j the second id of the cell.
  * @param[out] k the last id of the cell.
  */
  virtual void getCellId(size_t &i, size_t &j, size_t& k) const = 0;

protected: //PROTECTED_TO_DOCUMENT
  /**
  * Gets the weights at the current probe location. This weights are used by getValue() 
  * to compute a value at the current probe location.
  */
  virtual void getWeight(std::vector<double>& weight) const = 0;
};

//-----------------------------------------------------------------------------
template <typename _T>
inline _T MiPointProbeIjk::getValue(const MiDataSetIjk<_T>& dataset) const
{
  _T val(0);
  if (isFound())
  {
    size_t icell,jcell,kcell;
    getCellId(icell,jcell,kcell);
    if(dataset.getBinding()==MiDataSetIjk<_T>::PER_NODE)
    {
      std::vector<double> weight(8);
      getWeight(weight);
      val += weight[0]*dataset.get(icell,jcell,kcell);
      val += weight[1]*dataset.get(icell+1,jcell,kcell);
      val += weight[2]*dataset.get(icell+1,jcell+1,kcell);
      val += weight[3]*dataset.get(icell,jcell+1,kcell);
      val += weight[4]*dataset.get(icell,jcell,kcell+1);
      val += weight[5]*dataset.get(icell+1,jcell,kcell+1);
      val += weight[6]*dataset.get(icell+1,jcell+1,kcell+1);
      val += weight[7]*dataset.get(icell,jcell+1,kcell+1);
    }
    else 
      val = dataset.get(icell,jcell,kcell);
  }
  return val;
}



#endif


