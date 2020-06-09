/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MITOPOLOGYIJK_H
#define _MITOPOLOGYIJK_H

#include <MeshVizInterface/mesh/topology/MiTopology.h>

#include <Inventor/STL/sstream>

//-----------------------------------------------------------------------------
/**
* @DTEXT List of volume cells interface.
* 
* @ingroup MeshIViz_Mesh_Topology
* 
* @DESCRIPTION
*    A generic abstract interface for a structured implicit volume mesh topology. 
*    Cells are all implicitly defined as hexahedron so there is no need for specifying 
*    a list of cells. The number of cells on each dimension defines completely the topology.
* 
*/
class MESHIVIZ_API MiTopologyIjk : virtual public MiTopology
{
public:

  /**
  * Returns the number of cells on the first logical axis.
  */
  virtual size_t getNumCellsI() const = 0;

  /**
  * Returns the number of cells on the second logical axis.
  */
  virtual size_t getNumCellsJ() const = 0;

  /**
  * Returns the number of cells on the third logical axis.
  */
  virtual size_t getNumCellsK() const = 0;

  /** 
  * Returns true if the cell of index (i,j,k) should be ignored.
  * This value is ignored if the hasDeadCell() method returns false.
  * The default implementation returns always false.
  * @param (i,j,k) the index of the cell to check
  */ 
  virtual bool isDead(size_t UNREF_PARAM(i), size_t UNREF_PARAM(j), size_t UNREF_PARAM(k)) const { return false; }

 /** 
  * Returns the name of the cell.
  * The default implementation returns the cell identifier as a string.
  * @param i,j,k the index of the cell 
  */ 
  virtual std::string getCellName(size_t i, size_t j, size_t k) const 
  { 
    std::ostringstream strstream;
    strstream << "(" << i << "," << j << "," << k << ")" ;
    return strstream.str();
  }

 /** 
  * Returns the name of the node.
  * The default implementation returns the node identifier as a string.
  * @param i,j,k the index of the node 
  */ 
  virtual std::string getNodeName(size_t i, size_t j, size_t k) const 
  { 
    std::ostringstream strstream;
    strstream << "(" << i << "," << j << "," << k << ")" ;
    return strstream.str();
  }

protected://PROTECTED_TO_DOCUMENT
  /**
  * @copydoc MiMesh::toStream(std::ostream& s) const
  */ 
  virtual std::ostream& toStream(std::ostream& s) const 
  { 
    s << "#mesh topology Ijk" << std::endl;
    s << "#numCellsI" << std::endl;
    s << getNumCellsI() << std::endl;
    s << "#numCellsJ" << std::endl;
    s << getNumCellsJ() << std::endl;
    s << "#numCellsK" << std::endl;
    s << getNumCellsK() << std::endl;
    s << "#hasDeadCells" << std::endl;
    s << hasDeadCells() << std::endl;
    if (hasDeadCells()) 
    {
      s << "#deadCells:" << std::endl;
      for (size_t i=0; i<getNumCellsI(); i++)
      {
        for (size_t j=0; j<getNumCellsJ(); j++)
        {
          for (size_t k=0; k<getNumCellsK(); k++)
          {
            if (isDead(i,j,k))
            {
              s << "#deadCell(" << i << "," << j << "," << k << ")" << std::endl;
            }
          }
        }
      }
    }
    return s;
  }

};


#endif
