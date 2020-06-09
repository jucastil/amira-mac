/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MIDATASET_H
#define _MIDATASET_H

#include <Inventor/STL/string>
#include <Inventor/STL/iostream>

#include <MeshVizInterface/MxMeshIViz.h>
#include <MeshVizInterface/MbVec3.h>

//-----------------------------------------------------------------------------
/**
* @DTEXT Generic data set interface.
* 
* @ingroup MeshIViz_Mesh_DataSets
* 
* @DESCRIPTION
*    A generic abstract interface for a data set usable in any extract of a mesh.
* 
*/
class MiDataSet
{
public:
  virtual ~MiDataSet() {}

  /**
  * Returns a time stamp on this data set. When the content of the dataset 
  * changes, the time stamp must increase. The time stamp allows MeshViz 
  * to be aware of any change to this dataset.
  */
  virtual size_t getTimeStamp() const = 0;

  /**
  * Returns the name of this data set.
  */
  virtual std::string getName() const = 0;

  /** Data binding */
  enum DataBinding {
    PER_CELL, /**< The data set contains one data value per cell. */
    PER_NODE  /**< The data set contains one data value per node. */
  };

  /**
  * Returns the data binding of this data set.
  */
  virtual DataBinding  getBinding() const = 0;

  /**
  * @copydoc MiMesh::operator <<()
  */
  friend std::ostream& operator << (std::ostream& s, const MiDataSet& dataset)
  {
    return dataset.toStream(s);
  }

protected: //PROTECTED_TO_DOCUMENT
  /**
  * @copydoc MiMesh::toStream(std::ostream& s) const
  */
  virtual std::ostream& toStream(std::ostream& s) const 
  {
    s << "# dataset name" << std::endl; 
    s << getName() << std::endl; 
    return s;
  }

};

#endif
