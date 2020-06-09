/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MITOPOLOGYIJ_H
#define _MITOPOLOGYIJ_H

#include <MeshVizInterface/mesh/topology/MiTopology.h>

#include <Inventor/STL/sstream>
//-----------------------------------------------------------------------------
/**
* @DTEXT List of structured surface cells interface.
* 
* @ingroup MeshIViz_Mesh_Topology
* 
* @DESCRIPTION
*    A generic abstract interface for a structured implicit surface mesh topology. 
*    Cells are all implicitely defined as quadrangles so there is no need for specifying 
*    a list of cells. The number of cells on each dimension defines completely the topology.
* 
*/
class MESHIVIZ_API MiTopologyIj : virtual public MiTopology
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
  * Returns true if the cell of index (i,j) should be ignored.
  * This value is ignored if the hasDeadCell() method returns false.
  * The default implementation returns always false.
  * @param (i,j) the index of the cell to check
  */ 
  virtual bool isDead(size_t UNREF_PARAM(i), size_t UNREF_PARAM(j)) const{ return false ;};

 /** 
  * Returns the name of the cell.
  * The default implementation returns the cell identifier as a string.
  * @param (i,j) the index of the cell 
  */ 
  virtual std::string getCellName(size_t i, size_t j) const { 
    std::ostringstream strstream;
    strstream << "(" << i << "," << j << ")" ;
    return strstream.str();
  }

 /** 
  * Returns the name of the node.
  * The default implementation returns the node identifier as a string.
  * @param (i,j) the index of the cell 
  */ 
  virtual std::string getNodeName(size_t i, size_t j) const { 
    std::ostringstream strstream;
    strstream << "(" << i << "," << j << ")" ;
    return strstream.str();
  }


protected://PROTECTED_TO_DOCUMENT
  /**
  * @copydoc MiMesh::toStream(std::ostream& s) const
  */ 
  virtual std::ostream& toStream(std::ostream& s) const
  { 
    s << "#Mesh topology Ij" << std::endl;
    s << "#Num Cells I" << std::endl;
    s << getNumCellsI() << std::endl;
    s << "#Num Cells J" << std::endl;
    s << getNumCellsJ() << std::endl;
    s << "#Has Dead Cells" << std::endl;
    s << hasDeadCells() << std::endl;
    if (hasDeadCells()) 
    {
      s << "#Dead Cells:" << std::endl;
      for (size_t i=0; i<getNumCellsI(); i++)
      {
        for (size_t j=0; j<getNumCellsJ(); j++)
        {
          if (isDead(i,j)) 
          {
            s << "deadCell " << i << " " << j << std::endl;
          }
        }
      }
    }

    return s;
  }

};


#endif

