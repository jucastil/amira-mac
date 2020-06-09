/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _MBMESHIJK_H
#define  _MBMESHIJK_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>
#include <MeshVizInterface/mesh/MiMeshIjk.h>

#include <MeshVizInterface/implement/MbMeshVizImpl.h>
#include <MeshVizInterface/implement/topology/MbTopologyIjk.h>
#include <MeshVizInterface/implement/data/MbVec3SetIjk.h>
#include <MeshVizInterface/implement/data/MbScalarSetIjk.h>
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
class MbMeshIjk
{
public:

  /**
  * Add the scalar data set to this mesh if a scalar data set with the same name
  * is not already stored in this mesh.
  * The dataset are stored in a alphabetical order according to their name.
  * @return false if the dataset is not added.
  */ 
  bool addScalarSetIjk(const MbScalarSetIjk<_ScalarT>* scalarSet);

  /**
  * Add the vector data set to this mesh if a vector data set with the same name
  * is not already stored in this mesh.
  * The dataset are stored in a alphabetical order according to their name.
  * @return false if the dataset is not added.
  */ 
  bool addVec3SetIjk(const MbVec3SetIjk<_Vec3T>* vectorSet);

  /**
  * Get a vector dataset according to its alphabetical ordering number.
  * For instance getVec3SetIjk(0) returns the first dataset in the alphabetical order.
  * @return NULL if id >= getNumVec3SetsIjk().
  */
  virtual const MiVec3dSetIjk* getVec3SetIjk(size_t id) const;

  /**
  * Get a vector dataset according to its name.
  * @return NULL if not found.
  */
  virtual const MiVec3dSetIjk* getVec3SetIjk(std::string name) const;

  /**
  * Get a scalar dataset according to its alphabetical ordering number.
  * For instance getScalarSetIjk(0) returns the first dataset in the alphabetical order.
  * @return NULL if id >= getNumScalarSetsIjk().
  */
  virtual const MiScalardSetIjk* getScalarSetIjk(size_t id) const;

  /**
  * Get a scalar dataset according to its name.
  * @return NULL if not found.
  */
  virtual const MiScalardSetIjk* getScalarSetIjk(std::string name) const;

  //@{
  /** Get the size of data sets */
  virtual size_t getNumVec3SetsIjk() const;
  virtual size_t getNumScalarSetsIjk() const;
  //@}

protected:
  virtual std::ostream& toStream(std::ostream& s) const;

  typedef std::set< const MbVec3SetIjk<_Vec3T>*,  MbDataSetComparator<const MbVec3SetIjk<_Vec3T>* > > SetOfVec3Set;
  typedef std::set< const MbScalarSetIjk<_ScalarT>*, MbDataSetComparator<const MbScalarSetIjk<_ScalarT>* > > SetOfScalarSet;

  // MbMeshIjk is abstract
  MbMeshIjk();
  virtual ~MbMeshIjk(){};

  SetOfScalarSet m_scalarSets;
  SetOfVec3Set m_vec3Sets;
};

//-----------------------------------------------------------------------------
template <typename _ScalarT, typename _Vec3T>
bool 
MbMeshIjk<_ScalarT,_Vec3T>::addScalarSetIjk(const MbScalarSetIjk<_ScalarT>* scalarSet)
{
  std::pair<typename SetOfScalarSet::iterator,bool> ret = m_scalarSets.insert(scalarSet);
  return ret.second;
}

//-----------------------------------------------------------------------------
template <typename _ScalarT, typename _Vec3T>
bool 
MbMeshIjk<_ScalarT,_Vec3T>::addVec3SetIjk(const MbVec3SetIjk<_Vec3T>* vectorSet)
{
  std::pair<typename SetOfVec3Set::iterator,bool> ret = m_vec3Sets.insert(vectorSet);
  return true;
}

//-----------------------------------------------------------------------------
template <typename _ScalarT, typename _Vec3T>
MbMeshIjk<_ScalarT,_Vec3T>::MbMeshIjk()
{
}

//-----------------------------------------------------------------------------
template <typename _ScalarT, typename _Vec3T>
const MiVec3dSetIjk*
MbMeshIjk<_ScalarT,_Vec3T>::getVec3SetIjk(size_t id) const
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
const MiVec3dSetIjk*
MbMeshIjk<_ScalarT,_Vec3T>::getVec3SetIjk(std::string name) const
{
  MbVec3SetIjk<_Vec3T> tmp;
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
const MiScalardSetIjk*
MbMeshIjk<_ScalarT,_Vec3T>::getScalarSetIjk(size_t id) const
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
const MiScalardSetIjk*
MbMeshIjk<_ScalarT,_Vec3T>::getScalarSetIjk(std::string name) const
{
  MbScalarSetIjk<_ScalarT> tmp;
  tmp.setName(name);
  typename SetOfScalarSet::const_iterator it;
  it =  m_scalarSets.find(&tmp);
  if ( it!=m_scalarSets.end() ) 
    return *it;
  else
    return NULL;
}

//-----------------------------------------------------------------------------
template <typename _ScalarT, typename _Vec3T>
size_t 
MbMeshIjk<_ScalarT,_Vec3T>::getNumVec3SetsIjk() const
{
  return m_vec3Sets.size();
}

//-----------------------------------------------------------------------------
template <typename _ScalarT, typename _Vec3T>
size_t 
MbMeshIjk<_ScalarT,_Vec3T>::getNumScalarSetsIjk() const
{
  return m_scalarSets.size();
}

//-----------------------------------------------------------------------------
template <typename _ScalarT, typename _Vec3T>
inline std::ostream& 
MbMeshIjk<_ScalarT,_Vec3T>::toStream(std::ostream& s) const
{
  size_t i;
  // output the scalar set
  s << "# num scalar sets" << std::endl;
  s << getNumScalarSetsIjk() << std::endl;
  for ( i=0; i<getNumScalarSetsIjk(); ++i )
  {
    const MiScalardSetIjk* dataSet = getScalarSetIjk(i);
    s << "# scalar set : " << i << std::endl;
    s << *(dataSet);
  }

  s << "# num vector sets" << std::endl;
  s << getNumVec3SetsIjk() << std::endl;
  for ( i=0; i<getNumVec3SetsIjk(); ++i )
  {
    const MiVec3dSetIjk* dataSet = getVec3SetIjk(i);
    s << "# vector set : " << i << std::endl;
    s << *(dataSet);
  }

  return s;
}

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif 







