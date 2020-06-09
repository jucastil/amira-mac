/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MITOPOLOGYI_H
#define _MITOPOLOGYI_H

#include <MeshVizInterface/mesh/topology/MiTopology.h>

#include <Inventor/STL/sstream>

//-----------------------------------------------------------------------------
/**
* @DTEXT List of cells interface.
* 
* @ingroup MeshIViz_Mesh_Topology
* 
* @DESCRIPTION
*    A generic abstract interface for an implicit mesh topology. 
* 
*/
class MESHIVIZ_API MiTopologyI : virtual public MiTopology
{
public:
  /**
  * Returns the number of cells.
  */
  virtual size_t getNumCells() const = 0;

 /** 
  * Returns true if the cell of index i should be ignored.
  * This value is ignored if the hasDeadCell() method returns false.
  * The default implementation returns always false.
  * @param i the index of the cell to check
  */ 
  virtual bool isDead(size_t UNREF_PARAM(i)) const { return false ;}

 /** 
  * Returns the name of the cell.
  * The default implementation returns the cell identifier as a string.
  * @param i the index of the cell 
  */ 
  virtual std::string getCellName(size_t i) const { 
    std::ostringstream strstream;
    strstream << i ;
    return strstream.str();
  }

 /** 
  * Returns the name of the node.
  * The default implementation returns the node identifier as a string.
  * @param i the index of the node 
  */ 
  virtual std::string getNodeName(size_t i) const { 
    std::ostringstream strstream;
    strstream << i ;
    return strstream.str();
  }

protected:
  /**
  * Defines a specialized output on stream 
  */
  virtual std::ostream& toStream(std::ostream& s) const
  { 
    s << "#mesh topology" << std::endl;
    s << "#numCells" << std::endl;
    s << getNumCells() << std::endl;
    s << "#hasDeadCells" << std::endl;
    s << hasDeadCells() << std::endl;
    return s;
  }
};


#endif
