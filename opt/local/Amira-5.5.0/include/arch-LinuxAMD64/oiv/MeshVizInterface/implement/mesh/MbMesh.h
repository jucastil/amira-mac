/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _MBMESH_H
#define  _MBMESH_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/MiMeshUnstructured.h>
#include <MeshVizInterface/mesh/data/MiDataSetI.h>

#include <MeshVizInterface/implement/MbMeshVizImpl.h>
#include <MeshVizInterface/implement/data/MbVec3SetI.h>
#include <MeshVizInterface/implement/data/MbScalarSetI.h>
#include <MeshVizInterface/implement/MbDataSetComparator.h>
#include <MeshVizInterface/implement/geometry/MbMeshGeometry.h>

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
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
class MbMesh : virtual public MiMeshUnstructured
{
public:
  
  virtual const MbMeshGeometry<_CoordT>& getGeometry() const;
  MbMeshGeometry<_CoordT>& getGeometry();

  /**
   * Sets a new geometry
   */
  template <typename _CoordIter>
  void setGeometry(_CoordIter beginCoord, _CoordIter endCoord);

  /**
  * Add the scalar data set to this mesh if a scalar data set with the same name
  * is not already stored in this mesh.
  * The dataset are stored in a alphabetical order according to their name.
  * @return false if the dataset is not added.
  */ 
  bool addScalarSet(const MbScalarSetI<_ScalarT>* scalarSet);

  /**
  * Add the vector data set to this mesh if a vector data set with the same name
  * is not already stored in this mesh.
  * The dataset are stored in a alphabetical order according to their name.
  * @return false if the dataset is not added.
  */ 
  bool addVec3Set(const MbVec3SetI<_Vec3T>* vectorSet);

  /**
  * Get a vector dataset according to its alphabetical ordering number.
  * For instance getVec3Set(0) returns the first dataset in the alphabetical order.
  * @return NULL if id >= getNumVec3Sets().
  */
  virtual const MiVec3dSetI* getVec3Set(size_t id) const;

  /**
  * Get a vector dataset according to its name.
  * @return NULL if not found.
  */
  virtual const MiVec3dSetI* getVec3Set(std::string name) const;

  /**
  * Get a scalar dataset according to its alphabetical ordering number.
  * For instance getScalarSet(0) returns the first dataset in the alphabetical order.
  * @return NULL if id >= getNumScalarSets().
  */
  virtual const MiScalardSetI* getScalarSet(size_t id) const;

  /**
  * Get a scalar dataset according to its name.
  * @return NULL if not found.
  */
  virtual const MiScalardSetI* getScalarSet(std::string name) const;

  //@{
  /**
  * Gets the size of data sets
  */
  virtual size_t getNumVec3Sets() const;
  virtual size_t getNumScalarSets() const;
  virtual size_t getNumMaterialSets() const;
  //@}

protected:
  virtual std::ostream& toStream(std::ostream& s) const;

  typedef std::set< const MbVec3SetI<_Vec3T>*,  MbDataSetComparator<const MbVec3SetI<_Vec3T>* > > SetOfVec3Set;
  typedef std::set< const MbScalarSetI<_ScalarT>*, MbDataSetComparator<const MbScalarSetI<_ScalarT>* > > SetOfScalarSet;

  // MbMesh is abstract
  MbMesh();
  template <typename _CoordIter>
  MbMesh(_CoordIter beginCoord, _CoordIter endCoord);
  
  MbMeshGeometry<_CoordT> m_geometry;
  SetOfScalarSet m_scalarSets;
  SetOfVec3Set m_vec3Sets;
};

//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
bool 
MbMesh<_CoordT,_ScalarT,_Vec3T>::addScalarSet(const MbScalarSetI<_ScalarT>* scalarSet)
{
  std::pair<typename SetOfScalarSet::iterator,bool> ret = m_scalarSets.insert(scalarSet);
  return ret.second;
}

//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
bool 
MbMesh<_CoordT,_ScalarT,_Vec3T>::addVec3Set(const MbVec3SetI<_Vec3T>* vectorSet)
{
  std::pair<typename SetOfVec3Set::iterator,bool> ret = m_vec3Sets.insert(vectorSet);
  return ret.second;
}

//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
MbMesh<_CoordT,_ScalarT,_Vec3T>::MbMesh()
{
}

//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
template <typename _CoordIter>
MbMesh<_CoordT,_ScalarT,_Vec3T>::MbMesh(_CoordIter beginCoord, _CoordIter endCoord):
  m_geometry(beginCoord,endCoord)
{
}

//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
template <typename _CoordIter>
inline void 
MbMesh<_CoordT,_ScalarT,_Vec3T>::setGeometry(_CoordIter beginCoord, _CoordIter endCoord)
{
  m_geometry.assign( beginCoord,endCoord );
}

//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
inline const MbMeshGeometry<_CoordT>&
MbMesh<_CoordT,_ScalarT,_Vec3T>::getGeometry() const
{
  return m_geometry;
}

//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
inline MbMeshGeometry<_CoordT>&
MbMesh<_CoordT,_ScalarT,_Vec3T>::getGeometry()
{
  return m_geometry;
}

//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
const MiVec3dSetI*
MbMesh<_CoordT,_ScalarT,_Vec3T>::getVec3Set(size_t id) const
{
  typename SetOfVec3Set::const_iterator it = m_vec3Sets.begin();
  for (size_t i=0; i<id && it!=m_vec3Sets.end(); ++i,++it);
  if ( it!=m_vec3Sets.end() ) 
    return *it;
  else
    return NULL;
}

//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
const MiVec3dSetI*
MbMesh<_CoordT,_ScalarT,_Vec3T>::getVec3Set(std::string name) const
{
  MbVec3SetI<_Vec3T> tmp;
  tmp.setName(name);
  typename SetOfVec3Set::const_iterator it;
  it = m_vec3Sets.find(&tmp);
  if ( it!=m_vec3Sets.end() ) 
    return *it;
  else
    return NULL;
}

//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
const MiScalardSetI*
MbMesh<_CoordT,_ScalarT,_Vec3T>::getScalarSet(size_t id) const
{
  typename SetOfScalarSet::const_iterator it = m_scalarSets.begin();
  for (size_t i=0; i<id && it!=m_scalarSets.end(); ++i,++it);
  if ( it!=m_scalarSets.end() ) 
    return *it;
  else
    return NULL;
}

//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
const MiScalardSetI*
MbMesh<_CoordT,_ScalarT,_Vec3T>::getScalarSet(std::string name) const
{
  MbScalarSetI<_ScalarT> tmp;
  tmp.setName(name);
  typename SetOfScalarSet::const_iterator it;
  it = m_scalarSets.find(&tmp);
  if ( it!=m_scalarSets.end() ) 
    return *it;
  else
    return NULL;
}

//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
size_t 
MbMesh<_CoordT,_ScalarT,_Vec3T>::getNumVec3Sets() const
{
  return m_vec3Sets.size();
}

//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
size_t 
MbMesh<_CoordT,_ScalarT,_Vec3T>::getNumScalarSets() const
{
  return m_scalarSets.size();
}

//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
size_t 
MbMesh<_CoordT,_ScalarT,_Vec3T>::getNumMaterialSets() const
{
  return 0;
}

//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
inline std::ostream& 
MbMesh<_CoordT,_ScalarT,_Vec3T>::toStream(std::ostream& s) const
{
  size_t i;
  // output the scalar set
  s << "# num scalar sets" << std::endl;
  s << getNumScalarSets() << std::endl;
  for ( i=0; i<getNumScalarSets(); ++i )
  {
    const MiScalardSetI* dataSet = getScalarSet(i);
    s << "# scalar set : " << i << std::endl;
    s << *(dataSet);
  }

  s << "# num vector sets" << std::endl;
  s << getNumVec3Sets() << std::endl;
  for ( i=0; i<getNumVec3Sets(); ++i )
  {
    const MiVec3dSetI* dataSet = getVec3Set(i);
    s << "# vector set : " << i << std::endl;
    s << *(dataSet);
  }

  return s;
}

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif 







