/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MiBoundedDataSet_H
#define _MiBoundedDataSet_H

#include <Inventor/STL/string>
#include <Inventor/STL/iostream>

#include <MeshVizInterface/MxMeshIViz.h>
#include <MeshVizInterface/mesh/data/MiDataSet.h>
#include <MeshVizInterface/MbVec3.h>

//-----------------------------------------------------------------------------
/**
* @DTEXT Generic data set interface.
* 
* @ingroup MeshIViz_Mesh_DataSets
* 
* @DESCRIPTION
*    A generic abstract template interface for a data set with boundaries (min and max) usable in any extract of a mesh.
* 
*/
template <typename _T>
class MiBoundedDataSet: virtual public MiDataSet
{
public:
  virtual ~MiBoundedDataSet() {}

  /**
  * Returns the minimum value of this set.
  */
  virtual _T getMin() const = 0;
  
  /**
  * Returns the maximum value of this set.
  */
  virtual _T getMax() const = 0;

protected: //PROTECTED_TO_DOCUMENT
  /**
  * @copydoc MiMesh::toStream(std::ostream& s) const
  */
  virtual std::ostream& toStream(std::ostream& s) const 
  {
    MiDataSet::toStream(s);
    s << "# min " << std::endl;
    s << getMin() << std::endl;
    s << "# max " << std::endl;
    s << getMax() << std::endl;
    return s;
  }

};

#endif
