/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MiPointProbeIj_h
#define  _MiPointProbeIj_h

#include <MeshVizInterface/mesh/data/MiDataSetIj.h>
#include <MeshVizInterface/mesh/cell/MiCell.h>

class MiCellFilterIj;
class MiSurfaceMeshRegular;
class MiSurfaceMeshRectilinear;
class MiSurfaceMeshCurvilinear;

/**
 * @DTEXT Probe at a given location in a structured surface mesh
 * 
 * @ingroup MeshIViz_Extract_Probe
 * 
 * @DESCRIPTION This class can be used to evaluate the value of a data set in the given mesh at any location.
 * 
 * 
 */
class MESHIVIZ_API MiPointProbeIj
{
public:
  virtual ~MiPointProbeIj() {}

  //@{
  /**
  * @copydoc MiInterpolatedLogicalSliceExtract::getNewInstance()
  */ 
  static MiPointProbeIj* getNewInstance(const MiSurfaceMeshRegular& mesh, bool parallel = true);
  static MiPointProbeIj* getNewInstance(const MiSurfaceMeshRectilinear& mesh, bool parallel = true);
  static MiPointProbeIj* getNewInstance(const MiSurfaceMeshCurvilinear& mesh, bool parallel = true);
  //@}

  /**
  * Sets the current probe location at the given point and looks for 
  * the cell containing this point. If the probe location is inside
  * a cell not accepted by the optional filter, this methods returns
  * false.
  * @param[in] point The destination point of the probe.   
  * @param[in] cellFilter The cell filter.   
  * @returns true if this location is inside the mesh, false otherwise.
  */
  virtual bool setLocation(const MbVec3d& point, const MiCellFilterIj* cellFilter=NULL) = 0;

  /**
  * Moves the current probe location at the given point. This method is 
  * similar and gives the same result as setLocation(). But, first it looks 
  * for the containing cell in the neighborhood of the cell having id
  * @I (cellIdI,cellIdJ)  @i.
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
  * @param[in] cellFilter The cell filter.   
  * @returns true if this location is inside the mesh, false otherwise.
  */
  virtual bool moveLocation(const MbVec3d& point, size_t cellIdI, size_t cellIdJ, 
                            const MiCellFilterIj* cellFilter=NULL) = 0;

  /**
  * @returns true if the current location of the probe is inside the mesh, 
  * false otherwise.
  */
  virtual bool isFound() const = 0;

  /**
  * Gets the value at the current probe location in the given dataset.
  * The returned value is meaningless if the probe location is outside the
  * mesh (when isFound() is false).
  */
  template <typename _T>
  _T getValue(const MiDataSetIj<_T>& dataset) const;

  /**
  * Gets the ids of the cell of the mesh containing the current location of the probe.
  * i and are set to UNDEFINED_ID if the current location of the probe is outside the mesh.
  * @param[out] i the first id of the cell. 
  * @param[out] j the second id of the cell.
  */
  virtual void getCellId(size_t &i, size_t &j) const = 0;

protected: //PROTECTED_TO_DOCUMENT
  /**
  * Gets the weights at the current probe location. This weights are used by getValue() 
  * to compute a value at the current probe location.
  */
  virtual void getWeight(std::vector<double>& weight) const = 0;
};

//-----------------------------------------------------------------------------
template <typename _T>
inline _T MiPointProbeIj::getValue(const MiDataSetIj<_T>& dataset) const
{
  _T val(0);
  if (isFound())
  {
    size_t icell,jcell;
    getCellId(icell,jcell);
    if(dataset.getBinding()==MiDataSetIj<_T>::PER_NODE)
    {
      std::vector<double> weight(4);
      getWeight(weight);
      val += weight[0]*dataset.get(icell,jcell);
      val += weight[1]*dataset.get(icell+1,jcell);
      val += weight[2]*dataset.get(icell+1,jcell+1);
      val += weight[3]*dataset.get(icell,jcell+1);
    }
    else 
      val = dataset.get(icell,jcell);
  }
  return val;
}



#endif


