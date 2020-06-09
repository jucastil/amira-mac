/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _MBSCALARSETIJK_H
#define  _MBSCALARSETIJK_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>

#include <MeshVizInterface/implement/data/MbDataSet.h>
#include <MeshVizInterface/implement/MbIjkToI.h>
#include <MeshVizInterface/implement/MbMeshVizImpl.h>


#include <Inventor/STL/vector>
#include <Inventor/STL/iostream>
#include <Inventor/STL/sstream>
#include <Inventor/STL/algorithm>

/**
 * @DTEXT  Defines a set of scalars for Ijk volumes.
 * 
 * @ingroup MeshIViz_Implement_Data
 * 
 * @DESCRIPTION

 * 
 */
template <typename _T=double>
class MbScalarSetIjk : virtual public MiScalardSetIjk, public MbDataSet, private MbIjkToI
{
public:
  //@{
  /**
  * Constructor for an empty default dataset.
  * This dataset has a default name depending on the number of instances created.
  * Its binding is set to PER_NODE by default.
  */
  MbScalarSetIjk();
  MbScalarSetIjk(size_t numI, size_t numJ, size_t numK);

  MbScalarSetIjk(size_t numI, size_t numJ, size_t numK, 
                 const std::string& name, DataBinding binding=PER_NODE);
  //@}

  /**
  * Returns the (i,j,k)-th value of this set.
  */
  double get(size_t i, size_t j, size_t k) const;

  /**
  * Sets the (i,j,k)-th value of this set.
  */
  void set(size_t i, size_t j, size_t k, const _T& data);

  //@{
  /**
  * Returns the number of values in this set.
  */
  virtual void getSize(size_t& sizeI, size_t& sizeJ, size_t& sizeK) const;
  virtual void setSize(size_t sizeI, size_t sizeJ, size_t sizeK);
  //@}

  /**
  * Returns the min of this set.
  */
  virtual double getMin() const;
  /**
  * Returns the max of this set.
  */
  virtual double getMax() const;

protected:
  /**
  * Defines a specialized output on stream for MbScalarSet
  */
  virtual std::ostream& toStream(std::ostream& s) const;

  std::vector<_T> m_scalars;

  static size_t s_numInstance;

  size_t m_numJ;
  size_t m_numK;

};


template <typename _T>
size_t MbScalarSetIjk<_T>::s_numInstance = 0;

//-----------------------------------------------------------------------------
template <typename _T>
inline 
MbScalarSetIjk<_T>::MbScalarSetIjk() :
  MbIjkToI(0,0), m_numJ(0), m_numK(0) 
{
  std::ostringstream defName; 
  defName << "MbScalarSet_#" << s_numInstance++;
  m_name = defName.str();
}

//-----------------------------------------------------------------------------
template <typename _T>
inline 
MbScalarSetIjk<_T>::MbScalarSetIjk(size_t numI, size_t numJ, size_t numK) :
  MbIjkToI(numI,numJ), m_numJ(numJ), m_numK(numK) 
{
  std::ostringstream defName; 
  defName << "MbScalarSet_#" << s_numInstance++;
  m_name = defName.str();
  m_scalars.resize(m_numIxJ*m_numK);
}

//-----------------------------------------------------------------------------
template <typename _T>
inline 
MbScalarSetIjk<_T>::MbScalarSetIjk(size_t numI, size_t numJ, size_t numK, 
                                   const std::string& name,
                                   DataBinding binding) 
: MbDataSet(name,binding), MbIjkToI(numI,numJ), m_numJ(numJ), m_numK(numK)
{
  m_scalars.resize(m_numIxJ*m_numK);
  s_numInstance++;
}

//-----------------------------------------------------------------------------
template <typename _T>
double
MbScalarSetIjk<_T>::get(size_t i, size_t j, size_t k) const
{
  return (double)m_scalars[getI(i,j,k)]; 
}

template <typename _T>
void
MbScalarSetIjk<_T>::set(size_t i, size_t j, size_t k, const _T& data)
{
  if (i<m_numI && j<m_numJ && k<m_numK) 
  {
    m_scalars[getI(i,j,k)] = data;
    m_timeStamp = MxTimeStamp::getTimeStamp();
  }
}

//-----------------------------------------------------------------------------
template <typename _T>
void
MbScalarSetIjk<_T>::getSize(size_t& i, size_t& j, size_t& k) const 
{
  i = m_numI;
  j = m_numJ;
  k = m_numK;
}

template <typename _T>
void
MbScalarSetIjk<_T>::setSize(size_t i, size_t j, size_t k) 
{
  m_numI = i;
  m_numJ = j;
  m_numK = k;
  m_numIxJ = i*j;
  m_scalars.resize(m_numIxJ*m_numK);
  m_timeStamp = MxTimeStamp::getTimeStamp();
}

//-----------------------------------------------------------------------------
template <typename _T>
double
MbScalarSetIjk<_T>::getMin() const
{
  typename std::vector<_T>::const_iterator itmin = std::min_element(m_scalars.begin(),m_scalars.end());
  return (double)(*itmin);
}


//-----------------------------------------------------------------------------
template <typename _T>
double
MbScalarSetIjk<_T>::getMax() const
{
  typename std::vector<_T>::const_iterator itmax = std::max_element(m_scalars.begin(),m_scalars.end());
  return (double)(*itmax);
}


//-----------------------------------------------------------------------------
template <typename _T>
std::ostream& 
MbScalarSetIjk<_T>::toStream(std::ostream& s) const
{
  s << "# scalarset name" << std::endl; 
  s << getName() << std::endl; 
  s << "# scalarset size" << std::endl;
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








