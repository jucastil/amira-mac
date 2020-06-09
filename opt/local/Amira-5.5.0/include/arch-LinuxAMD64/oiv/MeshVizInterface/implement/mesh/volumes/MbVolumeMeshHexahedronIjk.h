/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MBVOLUMEMESHHEXAHEDRONIJK_H
#define  _MBVOLUMEMESHHEXAHEDRONIJK_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/implement/mesh/volumes/MbVolumeMeshUnstructuredIjk.h>
#include <MeshVizInterface/implement/topology/MbHexahedronCellsSetIjk.h>
#include <MeshVizInterface/MbVec3.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/iostream>

/**
 * @DTEXT  Defines a meshIjk of hexahedrons.
 * 
 * @ingroup MeshIViz_Implement_Mesh
 * 
 * @DESCRIPTION

 * 
 */
template <typename _CoordT=MbVec3d, typename _ScalarT=double, typename _Vec3T=MbVec3d>
class MbVolumeMeshHexahedronIjk : public MbVolumeMeshUnstructuredIjk<_CoordT,_ScalarT,_Vec3T>
{

public:

  /**
  * Constructor of an empty mesh. 
  */
  MbVolumeMeshHexahedronIjk(size_t numCellI, size_t numCellJ, size_t numCellK)
  {
    this->m_topology = new MbHexahedronCellsSetIjk(numCellI,numCellJ,numCellK); 
  }
  /**
   * Constructor of a volume mesh. 
   */
  template <typename _Vec3Iter>
  MbVolumeMeshHexahedronIjk(size_t numCellI, size_t numCellJ, size_t numCellK,
                            _Vec3Iter beginCoord, _Vec3Iter endCoord);
  
  /** Copy constructor */
  MbVolumeMeshHexahedronIjk(const MbVolumeMeshHexahedronIjk& mesh)
  {
    this->m_topology = new MbHexahedronCellsSetIjk(mesh.m_topology);
  }
  
  ~MbVolumeMeshHexahedronIjk() 
  { 
    delete this->m_topology; 
  }

protected:
  virtual std::ostream& toStream(std::ostream& s) const;

};


//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
template <typename _Vec3Iter>
inline MbVolumeMeshHexahedronIjk<_CoordT,_ScalarT,_Vec3T>::MbVolumeMeshHexahedronIjk(
  size_t numCellI, size_t numCellJ, size_t numCellK,
  _Vec3Iter beginCoord, _Vec3Iter endCoord
  ) :
   MbVolumeMeshUnstructuredIjk<_CoordT,_ScalarT,_Vec3T>(beginCoord,endCoord)
{
  this->m_topology = new MbHexahedronCellsSetIjk(numCellI,numCellJ,numCellK);
}

//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
inline std::ostream& 
MbVolumeMeshHexahedronIjk<_CoordT,_ScalarT,_Vec3T>::toStream(std::ostream& s) const
{
  s << "# MbVolumeMeshHexahedronIjk" << std::endl;
  // output the inherited geometry and dataset
  MbVolumeMeshUnstructuredIjk<_CoordT,_ScalarT,_Vec3T>::toStream(s);

  return s;
}

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif







