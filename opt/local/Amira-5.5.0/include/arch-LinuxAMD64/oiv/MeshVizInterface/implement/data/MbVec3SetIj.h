/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _MBVEC3SETIJ_H
#define  _MBVEC3SETIJ_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/data/MiDataSetIj.h>
#include <MeshVizInterface/implement/MbIjToI.h>
#include <MeshVizInterface/MbVec3.h>

#include <MeshVizInterface/implement/data/MbDataSet.h>
#include <MeshVizInterface/implement/MbMeshVizImpl.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/iostream>
#include <Inventor/STL/sstream> 

/**
 * @DTEXT  Defines a set of 3D vectors.
 * 
 * @ingroup MeshIViz_Implement_Data
 * 
 * @DESCRIPTION

 * 
 */
template <typename _Vec3T=MbVec3d>
class MbVec3SetIj : virtual public MiVec3dSetIj, public MbDataSet, private MbIjToI
{
public:
  //@{
  /**
  * Constructor for an empty default dataset.
  * This dataset has a default name depending on the number of instances created.
  * Its binding is set to PER_NODE by default.
  */
  MbVec3SetIj();
  MbVec3SetIj(size_t numI, size_t numJ);

  MbVec3SetIj(size_t numI, size_t numJ, 
              const std::string& name, DataBinding binding=PER_NODE);
  //@}

  /**
  * Returns the (i,j)-th value of this set.
  */
  MbVec3d get(size_t i, size_t j) const;

  /**
  * Sets the (i,j)-th value of this set.
  */
  void set(size_t i, size_t j, const _Vec3T& data);

  /**
  * Returns the number of values in this set.
  */
  virtual void getSize(size_t& sizeI, size_t& sizeJ) const;
  /**
  * Sets the number of values in this set.
  */
  virtual void setSize(size_t sizeI, size_t sizeJ);

  /**
  * Returns the min of this set.
  */
  virtual MbVec3d getMin() const;
  /**
  * Returns the max of this set.
  */
  virtual MbVec3d getMax() const;

protected:
  /**
  * Defines a specialized output on stream for MbVec3Set
  */
  virtual std::ostream& toStream(std::ostream& s) const;

  std::vector<_Vec3T> m_coords;

  static size_t s_numInstance;
  
  size_t m_numJ;

};


template <typename _T>
size_t MbVec3SetIj<_T>::s_numInstance = 0;

//-----------------------------------------------------------------------------
template <typename _Vec3T>
inline 
MbVec3SetIj<_Vec3T>::MbVec3SetIj():
  MbIjToI(0), m_numJ(0)
{
  std::ostringstream defName; 
  defName << "MbVec3Set_#" << s_numInstance++;
  m_name = defName.str();
}

//-----------------------------------------------------------------------------
template <typename _Vec3T>
inline 
MbVec3SetIj<_Vec3T>::MbVec3SetIj(size_t numI, size_t numJ):
  MbIjToI(numI), m_numJ(numJ)
{
  std::ostringstream defName; 
  defName << "MbVec3Set_#" << s_numInstance++;
  m_name = defName.str();
  m_coords.resize(m_numI*m_numJ);
}

//-----------------------------------------------------------------------------
template <typename _Vec3T>
inline 
MbVec3SetIj<_Vec3T>::MbVec3SetIj(size_t numI, size_t numJ, 
                             const std::string& name,
                             DataBinding binding) 
: MbDataSet(name,binding), MbIjToI(numI), m_numJ(numJ)
{
  m_coords.resize(m_numI*m_numJ);
  s_numInstance++;
}

template <typename _Vec3T>
MbVec3d
MbVec3SetIj<_Vec3T>::get(size_t i, size_t j) const
{
  return (MbVec3d)m_coords[getI(i,j)]; 
}

template <typename _Vec3T>
void
MbVec3SetIj<_Vec3T>::set(size_t i, size_t j, const _Vec3T& data)
{
  if (i<m_numI && j<m_numJ) 
  {
    m_coords[getI(i,j)] = data;
    m_timeStamp = MxTimeStamp::getTimeStamp();
  }
}

//-----------------------------------------------------------------------------
template <typename _Vec3T>
void
MbVec3SetIj<_Vec3T>::getSize(size_t& i, size_t& j) const 
{
  i = m_numI;
  j = m_numJ;
}

template <typename _Vec3T>
void
MbVec3SetIj<_Vec3T>::setSize(size_t i, size_t j) 
{
  m_numI = i;
  m_numJ = j;
  m_coords.resize(m_numI*m_numJ);
  m_timeStamp = MxTimeStamp::getTimeStamp();
}


//-----------------------------------------------------------------------------
template <typename _Vec3T>
inline MbVec3d
MbVec3SetIj<_Vec3T>::getMin() const
{
  size_t minvecId = 0;
  double minvecLn = m_coords[0].length();

  for (size_t i=1; i<m_coords.size(); ++i)
  {
    double vecLn = m_coords[i].length();
    if (vecLn < minvecLn)
    {
      minvecLn = vecLn;
      minvecId = i;
    }
  }
  return (MbVec3d)m_coords[minvecId];
}


//-----------------------------------------------------------------------------
template <typename _Vec3T>
inline MbVec3d
MbVec3SetIj<_Vec3T>::getMax() const
{
  size_t maxvecId = 0;
  double maxvecLn = m_coords[0].length();

  for (size_t i=1; i<m_coords.size(); ++i)
  {
    double vecLn = m_coords[i].length();
    if (vecLn > maxvecLn)
    {
      maxvecLn = vecLn;
      maxvecId = i;
    }
  }
  return (MbVec3d)m_coords[maxvecId];
}

//-----------------------------------------------------------------------------
template <typename _Vec3T>
inline std::ostream& 
MbVec3SetIj<_Vec3T>::toStream(std::ostream& s) const
{
  s << "# vec3set name" << std::endl; 
  s << getName() << std::endl; 
  s << "# vec3set size" << std::endl;
  s << m_numI << "," << m_numJ << std::endl;
  for (size_t i=0; i< m_numI; ++i) 
    for (size_t j=0; j< m_numJ; ++j)
        s << "value(" << i << "," << j << ")=" << get(i,j) << std::endl;

  return s;
}

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif








