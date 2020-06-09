/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _MBMESHIJ_H
#define  _MBMESHIJ_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/data/MiDataSetIj.h>
#include <MeshVizInterface/mesh/MiMeshIj.h>

#include <MeshVizInterface/implement/MbMeshVizImpl.h>
#include <MeshVizInterface/implement/topology/MbTopologyIj.h>
#include <MeshVizInterface/implement/data/MbVec3SetIj.h>
#include <MeshVizInterface/implement/data/MbScalarSetIj.h>
#include <MeshVizInterface/implement/MbDataSetComparator.h>

#include <Inventor/STL/set>
#include <Inventor/STL/algorithm>
#include <Inventor/STL/functional>
#include <Inventor/STL/iostream>

/**
 * @DTEXT Base class for all basic mesh implementation.
 * 
 * @ingroup MeshIViz_Implement_Mesh
 * 
 * @DESCRIPTION
 * 
 */
template <typename _ScalarT, typename _Vec3T>
class MbMeshIj: virtual public MiMeshIj
{
public:

  virtual const MiTopologyIj& getTopology() const;
  
  /**
  * Defines dead cells
  */
  void setDeadCell(size_t i, size_t j, bool isDead=true)
  {
    m_topology.setDeadFlag(i,j,isDead);
  }

  /**
  * Add the scalar data set to this mesh if a scalar data set with the same name
  * is not already stored in this mesh.
  * The dataset are stored in a alphabetical order according to their name.
  * @return false if the dataset is not added.
  */ 
  bool addScalarSet(const MbScalarSetIj<_ScalarT>* scalarSet);

  /**
  * Add the vector data set to this mesh if a vector data set with the same name
  * is not already stored in this mesh.
  * The dataset are stored in a alphabetical order according to their name.
  * @return false if the dataset is not added.
  */ 
  bool addVec3Set(const MbVec3SetIj<_Vec3T>* vectorSet);

  /**
  * Get a vector dataset according to its alphabetical ordering number.
  * For instance getVec3Set(0) returns the first dataset in the alphabetical order.
  * @return NULL if id >= getNumVec3Sets().
  */
  virtual const MiVec3dSetIj* getVec3Set(size_t id) const;

  /**
  * Get a vector dataset according to its name.
  * @return NULL if not found.
  */
  virtual const MiVec3dSetIj* getVec3Set(std::string name) const;

  /**
  * Get a scalar dataset according to its alphabetical ordering number.
  * For instance getScalarSet(0) returns the first dataset in the alphabetical order.
  * @return NULL if id >= getNumScalarSets().
  */
  virtual const MiScalardSetIj* getScalarSet(size_t id) const;

  /**
  * Get a scalar dataset according to its name.
  * @return NULL if not found.
  */
  virtual const MiScalardSetIj* getScalarSet(std::string name) const;

  //@{
  /** Get the size of data sets */
  virtual size_t getNumVec3Sets() const;
  virtual size_t getNumScalarSets() const;
  virtual size_t getNumMaterialSets() const;
  //@}

protected:
  virtual std::ostream& toStream(std::ostream& s) const;

  typedef std::set< const MbVec3SetIj<_Vec3T>*,  MbDataSetComparator<const MbVec3SetIj<_Vec3T>* > > SetOfVec3Set;
  typedef std::set< const MbScalarSetIj<_ScalarT>*, MbDataSetComparator<const MbScalarSetIj<_ScalarT>* > > SetOfScalarSet;

  // MbMeshIj is abstract
  MbMeshIj(size_t numCellI, size_t numCellJ);
  
  MbTopologyIj     m_topology;
  SetOfScalarSet m_scalarSets;
  SetOfVec3Set m_vec3Sets;
};

//-----------------------------------------------------------------------------
template <typename _ScalarT, typename _Vec3T>
inline const MiTopologyIj& 
MbMeshIj<_ScalarT,_Vec3T>::getTopology() const
{
    return m_topology;
}

//-----------------------------------------------------------------------------
template <typename _ScalarT, typename _Vec3T>
bool 
MbMeshIj<_ScalarT,_Vec3T>::addScalarSet(const MbScalarSetIj<_ScalarT>* scalarSet)
{
  std::pair<typename SetOfScalarSet::iterator,bool> ret = m_scalarSets.insert(scalarSet);
  return ret.second;
}

//-----------------------------------------------------------------------------
template <typename _ScalarT, typename _Vec3T>
bool 
MbMeshIj<_ScalarT,_Vec3T>::addVec3Set(const MbVec3SetIj<_Vec3T>* vectorSet)
{
  std::pair<typename SetOfVec3Set::iterator,bool> ret = m_vec3Sets.insert(vectorSet);
  return true;
}

//-----------------------------------------------------------------------------
template <typename _ScalarT, typename _Vec3T>
MbMeshIj<_ScalarT,_Vec3T>::MbMeshIj(size_t numCellI, size_t numCellJ):
   m_topology(numCellI,numCellJ)
{
}

//-----------------------------------------------------------------------------
template <typename _ScalarT, typename _Vec3T>
const MiVec3dSetIj*
MbMeshIj<_ScalarT,_Vec3T>::getVec3Set(size_t id) const
{
  typename SetOfVec3Set::const_iterator it=m_vec3Sets.begin();
  for (size_t i=0; i<id && it!=m_vec3Sets.end(); ++i,++it);
  if ( it!=m_vec3Sets.end() ) 
    return *it;
  else
    return NULL;
}

//-----------------------------------------------------------------------------
template <typename _ScalarT, typename _Vec3T>
const MiVec3dSetIj*
MbMeshIj<_ScalarT,_Vec3T>::getVec3Set(std::string name) const
{
  MbVec3SetIj<_Vec3T> tmp;
  tmp.setName(name);
  typename SetOfVec3Set::const_iterator it;
  it = m_vec3Sets.find(&tmp);
  if ( it!=m_vec3Sets.end() ) 
    return *it;
  else
    return NULL;
}

//-----------------------------------------------------------------------------
template <typename _ScalarT, typename _Vec3T>
const MiScalardSetIj*
MbMeshIj<_ScalarT,_Vec3T>::getScalarSet(size_t id) const
{
  typename SetOfScalarSet::const_iterator it=m_scalarSets.begin();
  for (size_t i=0; i<id && it!=m_scalarSets.end(); ++i,++it);
  if ( it!=m_scalarSets.end() ) 
    return *it;
  else
    return NULL;
}

//-----------------------------------------------------------------------------
template <typename _ScalarT, typename _Vec3T>
const MiScalardSetIj*
MbMeshIj<_ScalarT,_Vec3T>::getScalarSet(std::string name) const
{
  MbScalarSetIj<_ScalarT> tmp;
  tmp.setName(name);
  typename SetOfScalarSet::const_iterator it;
  it = m_scalarSets.find(&tmp);
  if ( it!=m_scalarSets.end() ) 
    return *it;
  else
    return NULL;
}

//-----------------------------------------------------------------------------
template <typename _ScalarT, typename _Vec3T>
size_t 
MbMeshIj<_ScalarT,_Vec3T>::getNumVec3Sets() const
{
  return m_vec3Sets.size();
}

//-----------------------------------------------------------------------------
template <typename _ScalarT, typename _Vec3T>
size_t 
MbMeshIj<_ScalarT,_Vec3T>::getNumScalarSets() const
{
  return m_scalarSets.size();
}

//-----------------------------------------------------------------------------
template <typename _ScalarT, typename _Vec3T>
size_t 
MbMeshIj<_ScalarT,_Vec3T>::getNumMaterialSets() const
{
  return 0;
}

//-----------------------------------------------------------------------------
template <typename _ScalarT, typename _Vec3T>
inline std::ostream& 
MbMeshIj<_ScalarT,_Vec3T>::toStream(std::ostream& s) const
{
  size_t i;
  // output the scalar set
  s << "# num scalar sets" << std::endl;
  s << getNumScalarSets() << std::endl;
  for ( i=0; i<getNumScalarSets(); ++i )
  {
    const MiScalardSetIj* dataSet = getScalarSet(i);
    s << "# scalar set : " << i << std::endl;
    s << *(dataSet);
  }

  s << "# num vector sets" << std::endl;
  s << getNumVec3Sets() << std::endl;
  for ( i=0; i<getNumVec3Sets(); ++i )
  {
    const MiVec3dSetIj* dataSet = getVec3Set(i);
    s << "# vector set : " << i << std::endl;
    s << *(dataSet);
  }

  return s;
}

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif 







