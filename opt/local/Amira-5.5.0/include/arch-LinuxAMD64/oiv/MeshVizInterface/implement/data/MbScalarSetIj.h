/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _MBSCALARSETIJ_H
#define  _MBSCALARSETIJ_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/data/MiDataSetIj.h>

#include <MeshVizInterface/implement/data/MbDataSet.h>
#include <MeshVizInterface/implement/MbIjToI.h>
#include <MeshVizInterface/implement/MbMeshVizImpl.h>


#include <Inventor/STL/vector>
#include <Inventor/STL/iostream>
#include <Inventor/STL/sstream>
#include <Inventor/STL/algorithm>

/**
 * @DTEXT  Defines a set of scalars for Ij surfaces.
 * 
 * @ingroup MeshIViz_Implement_Data
 * 
 * @DESCRIPTION

 * 
 */
template <typename _T=double>
class MbScalarSetIj : virtual public MiScalardSetIj, public MbDataSet, private MbIjToI
{
public:
  //@{
  /**
  * Constructor for an empty default dataset.
  * This dataset has a default name depending on the number of instances created.
  * Its binding is set to PER_NODE by default.
  */
  MbScalarSetIj();
  MbScalarSetIj(size_t numI, size_t numJ);

  MbScalarSetIj(size_t numI, size_t numJ, 
                 const std::string& name, DataBinding binding=PER_NODE);
  //@}

  /**
  * Returns the (i,j)-th value of this set.
  */
  double get(size_t i, size_t j) const;

  /**
  * Sets the (i,j)-th value of this set.
  */
  void set(size_t i, size_t j, const _T& data);

  //@{
  /**
  * Returns the number of values in this set.
  */
  virtual void getSize(size_t& sizeI, size_t& sizeJ) const;
  virtual void setSize(size_t sizeI, size_t sizeJ);
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

};


template <typename _T>
size_t MbScalarSetIj<_T>::s_numInstance = 0;

//-----------------------------------------------------------------------------
template <typename _T>
inline 
MbScalarSetIj<_T>::MbScalarSetIj():
  MbIjToI(0), m_numJ(0)
{
  std::ostringstream defName; 
  defName << "MbScalarSet_#" << s_numInstance++;
  m_name = defName.str();
}

//-----------------------------------------------------------------------------
template <typename _T>
inline 
MbScalarSetIj<_T>::MbScalarSetIj(size_t numI, size_t numJ):
  MbIjToI(numI), m_numJ(numJ)
{
  std::ostringstream defName; 
  defName << "MbScalarSet_#" << s_numInstance++;
  m_name = defName.str();
  m_scalars.resize(m_numI*m_numJ);
}

//-----------------------------------------------------------------------------
template <typename _T>
inline 
MbScalarSetIj<_T>::MbScalarSetIj(size_t numI, size_t numJ, 
                                   const std::string& name,
                                   DataBinding binding) 
: MbDataSet(name,binding), MbIjToI(numI), m_numJ(numJ)
{
  m_scalars.resize(m_numI*m_numJ);
  s_numInstance++;
}

//-----------------------------------------------------------------------------
template <typename _T>
double
MbScalarSetIj<_T>::get(size_t i, size_t j) const
{

  return (double)m_scalars[getI(i,j)]; 
}

template <typename _T>
void
MbScalarSetIj<_T>::set(size_t i, size_t j, const _T& data)
{
  if (i<m_numI && j<m_numJ) 
  {
    m_scalars[getI(i,j)] = data;
    m_timeStamp = MxTimeStamp::getTimeStamp();
  }
}

//-----------------------------------------------------------------------------
template <typename _T>
void
MbScalarSetIj<_T>::getSize(size_t& i, size_t& j) const 
{
  i = m_numI;
  j = m_numJ;
}

template <typename _T>
void
MbScalarSetIj<_T>::setSize(size_t i, size_t j) 
{
  m_numI = i;
  m_numJ = j;
  m_scalars.resize(m_numI*m_numJ);
  m_timeStamp = MxTimeStamp::getTimeStamp();
}

//-----------------------------------------------------------------------------
template <typename _T>
double
MbScalarSetIj<_T>::getMin() const
{
  typename std::vector<_T>::const_iterator itmin = std::min_element(m_scalars.begin(),m_scalars.end());
  return (double)(*itmin);
}


//-----------------------------------------------------------------------------
template <typename _T>
double
MbScalarSetIj<_T>::getMax() const
{
  typename std::vector<_T>::const_iterator itmax = std::max_element(m_scalars.begin(),m_scalars.end());
  return (double)(*itmax);
}


//-----------------------------------------------------------------------------
template <typename _T>
std::ostream& 
MbScalarSetIj<_T>::toStream(std::ostream& s) const
{
  s << "# scalarset name" << std::endl; 
  s << getName() << std::endl; 
  s << "# scalarset size" << std::endl;
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








