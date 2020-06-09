/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _MBVEC3SETIJK_H
#define  _MBVEC3SETIJK_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>
#include <MeshVizInterface/MbVec3.h>

#include <MeshVizInterface/implement/data/MbDataSet.h>
#include <MeshVizInterface/implement/MbIjkToI.h>
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
class MbVec3SetIjk : virtual public MiVec3dSetIjk, public MbDataSet, private MbIjkToI
{
public:
  //@{
  /**
  * Constructor for an empty default dataset.
  * This dataset has a default name depending on the number of instances created.
  * Its binding is set to PER_NODE by default.
  */
  MbVec3SetIjk();
  MbVec3SetIjk(size_t numI, size_t numJ, size_t numK);

  MbVec3SetIjk(size_t numI, size_t numJ, size_t numK, 
                 const std::string& name, DataBinding binding=PER_NODE);
  //@}
 
  /**
  * Returns the (i,j)-th value of this set.
  */
  MbVec3d get(size_t i, size_t j, size_t k) const;

  /**
  * Sets the (i,j)-th value of this set.
  */
  void set(size_t i, size_t j, size_t k, const _Vec3T& data);

  /**
  * Returns the number of values in this set.
  */
  virtual void getSize(size_t& sizeI, size_t& sizeJ, size_t& sizeK) const;
  /**
  * Sets the number of values in this set.
  */
  virtual void setSize(size_t sizeI, size_t sizeJ, size_t sizeK);

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
  size_t m_numK;

};


template <typename _Vec3T>
size_t MbVec3SetIjk<_Vec3T>::s_numInstance = 0;

//-----------------------------------------------------------------------------
template <typename _Vec3T>
inline 
MbVec3SetIjk<_Vec3T>::MbVec3SetIjk():
  MbIjkToI(0,0), m_numJ(0), m_numK(0) 
{
  std::ostringstream defName; 
  defName << "MbVec3Set_#" << s_numInstance++;
  m_name = defName.str();
}

//-----------------------------------------------------------------------------
template <typename _Vec3T>
inline 
MbVec3SetIjk<_Vec3T>::MbVec3SetIjk(size_t numI, size_t numJ, size_t numK):
  MbIjkToI(numI,numJ), m_numJ(numJ), m_numK(numK) 
{
  std::ostringstream defName; 
  defName << "MbVec3Set_#" << s_numInstance++;
  m_name = defName.str();
  m_coords.resize(m_numIxJ*m_numK);
}

//-----------------------------------------------------------------------------
template <typename _T>
inline 
MbVec3SetIjk<_T>::MbVec3SetIjk(size_t numI, size_t numJ, size_t numK, 
                                   const std::string& name,
                                   DataBinding binding) 
: MbDataSet(name,binding), MbIjkToI(numI,numJ), m_numJ(numJ), m_numK(numK)
{
  m_coords.resize(m_numIxJ*m_numK);
  s_numInstance++;
}


template <typename _Vec3T>
MbVec3d
MbVec3SetIjk<_Vec3T>::get(size_t i, size_t j, size_t k) const
{
  return (MbVec3d)m_coords[getI(i,j,k)]; 
}

template <typename _Vec3T>
void
MbVec3SetIjk<_Vec3T>::set(size_t i, size_t j, size_t k, const _Vec3T& data)
{
  if (i<m_numI && j<m_numJ && k<m_numK) 
  {
    m_coords[getI(i,j,k)] = data;
    m_timeStamp = MxTimeStamp::getTimeStamp();
  }
}

//-----------------------------------------------------------------------------
template <typename _Vec3T>
void
MbVec3SetIjk<_Vec3T>::getSize(size_t& i, size_t& j, size_t& k) const 
{
  i = m_numI;
  j = m_numJ;
  k = m_numK;
}

template <typename _Vec3T>
void
MbVec3SetIjk<_Vec3T>::setSize(size_t i, size_t j, size_t k) 
{
  m_numI = i;
  m_numJ = j;
  m_numK = k;
  m_numIxJ = i*j;
  m_coords.resize(m_numIxJ*m_numK);
  m_timeStamp = MxTimeStamp::getTimeStamp();
}

//-----------------------------------------------------------------------------
template <typename _Vec3T>
inline MbVec3d
MbVec3SetIjk<_Vec3T>::getMin() const
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
MbVec3SetIjk<_Vec3T>::getMax() const
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
MbVec3SetIjk<_Vec3T>::toStream(std::ostream& s) const
{
  s << "# vec3set name" << std::endl; 
  s << getName() << std::endl; 
  s << "# vec3set size" << std::endl;
  s << m_numI << "," << m_numJ << "," << m_numK << std::endl;
  for (size_t i=0; i< m_numI; ++i) 
    for (size_t j=0; j< m_numJ; ++j)
      for (size_t k=0; k< m_numK; ++k)
        s << "value(" << i << "," << j << "," << k << ")=" << get(i,j,k) << std::endl;

  return s;
}

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif








