/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : M. Bonaventure (Nov 2010)
**=======================================================================*/
#ifndef _MeXTopologyI_H
#define _MeXTopologyI_H

#include <MeshVizInterface/mesh/topology/MiTopologyI.h>

//-----------------------------------------------------------------------------
/**
* @DTEXT List of extracted cells interface.
* 
* @ingroup MeshIViz_ExtractedMesh_Topology
* 
* @DESCRIPTION
*    A generic abstract interface for an extracted implicit mesh topology. 
* 
*/
class MESHIVIZ_API MeXTopologyI : virtual public MiTopologyI
{
public:

  /**
  * Returns true if the input cell mapping is available.
  * If false, the getInputCellId() methods will return UNDEFINED_ID.
  */
  virtual bool hasInputCellMapping() const = 0;

  //@{
  /**
  * Returns cell indices (I/J/K) of the input cell containing the extracted cell with the given id.
  * This defines a mapping between extracted cells and input cells if the hasInputCellMapping() method
  * returns true, otherwise these methods return UNDEFINED_ID.
  * @param id the index of the cell to check
  *
  * @note  When dealing with a structured mesh as an input, the J/K indices may be UNDEFINED_ID. This is 
  *        a temporary limitation. In that case, the I index is a flat index combining the 3 indices and 
  *        must be unflatten using the input topology dimensions as follow:
  * @verbatim
  size_t numCellsI = inputTopology.getNumCellsI();
  size_t numCellsJ = inputTopology.getNumCellsJ();
  size_t flatId = topology.getInputCellIdI(id);
  size_t inputIdK = flatId / (numCellsI * numCellsJ);
  size_t IJ = flatId % (numCellsI * numCellsJ);
  size_t inputIdJ = IJ / numCellsI;
  size_t inputIdI = IJ % numCellsI;
  @endverbatim
  */ 
  virtual size_t getInputCellIdI( size_t UNREF_PARAM(id) ) const { return UNDEFINED_ID; }
  virtual size_t getInputCellIdJ( size_t UNREF_PARAM(id) ) const { return UNDEFINED_ID; }
  virtual size_t getInputCellIdK( size_t UNREF_PARAM(id) ) const { return UNDEFINED_ID; } 
  //@}
};


#endif
