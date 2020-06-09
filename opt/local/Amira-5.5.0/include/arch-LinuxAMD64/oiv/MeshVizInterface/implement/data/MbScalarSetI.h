/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _MBSCALARSETI_H
#define  _MBSCALARSETI_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/data/MiDataSetI.h>

#include <MeshVizInterface/implement/data/MbDataSet.h>
#include <MeshVizInterface/implement/MbMeshVizImpl.h>


#include <Inventor/STL/vector>
#include <Inventor/STL/iostream>
#include <Inventor/STL/sstream>
#include <Inventor/STL/algorithm>

/**
 * @DTEXT  Defines a set of scalars.
 * 
 * @ingroup MeshIViz_Implement_Data
 * 
 * @DESCRIPTION

 * 
 */
template <typename _T=double>
class MbScalarSetI : virtual public MiScalardSetI, public MbDataSet
{
public:
  /**
  * Constructor for an empty default dataset.
  * This dataset has a default name depending on the number of instances created.
  * Its binding is set to PER_NODE by default.
  */
  MbScalarSetI();

  /**
  * Defines a new dataset by copying the given data from the interval [begin,end[.
  * This dataset has a default name depending on the number of instances created.
  * Its binding is set to PER_NODE by default.
  * @param begin start iterator.
  * @param end end iterator.
  */
  template <typename _TIter>
  MbScalarSetI(_TIter begin, _TIter end);

  /**
  * Defines a new dataset by copying the given data from the interval [begin,end[.
  * Its binding is set to PER_NODE by default.
  * @param begin start iterator.
  * @param end end iterator.
  * @param name the name of this dataset.
  * @param binding the binding of this dataset.
  */
  template <typename _TIter>
  MbScalarSetI(_TIter begin, _TIter end, const std::string& name, DataBinding binding=PER_NODE);

  /**
  * Change the content of this dataset. Clears the current content and copy the 
  * data from the interval [begin,end[.
  * The timestamp of this dataset is incremented.
  * @param begin start iterator.
  * @param end end iterator.
 */
  template <typename _TIter>
  void assign(_TIter begin, _TIter end);

  /**
  * Returns the i-th value of this set.
  */
  virtual double get(size_t i) const;

  /**
  * Returns the number of values in this set.
  */
  virtual size_t getSize() const;

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
};


template <typename _T>
size_t MbScalarSetI<_T>::s_numInstance = 0;


//-----------------------------------------------------------------------------
template <typename _T>
inline 
MbScalarSetI<_T>::MbScalarSetI()
{
  std::ostringstream defName; 
  defName << "MbScalarSet_#" << s_numInstance++;
  m_name = defName.str();
}

//-----------------------------------------------------------------------------
template <typename _T>
template <typename _TIter>
inline 
MbScalarSetI<_T>::MbScalarSetI(_TIter beginCoord, _TIter endCoord) 
: m_scalars(beginCoord,endCoord)
{
  std::ostringstream defName; 
  defName << "MbScalarSet_#" << s_numInstance++;
  m_name = defName.str();
}

//-----------------------------------------------------------------------------
template <typename _T>
template <typename _TIter>
inline 
MbScalarSetI<_T>::MbScalarSetI(_TIter beginCoord, _TIter endCoord, 
                             const std::string& name,
                             DataBinding binding) 
: MbDataSet(name,binding), m_scalars(beginCoord,endCoord)
{
  s_numInstance++;
}

//-----------------------------------------------------------------------------
template <typename _T>
template <typename _TIter>
void
MbScalarSetI<_T>::assign(_TIter beginCoord, _TIter endCoord)
{
  m_scalars.assign(beginCoord,endCoord);
  m_timeStamp =  MxTimeStamp::getTimeStamp();
}


//-----------------------------------------------------------------------------
template <typename _T>
double
MbScalarSetI<_T>::get(size_t i) const
{
  return (double)m_scalars[i]; 
}

//-----------------------------------------------------------------------------
template <typename _T>
size_t
MbScalarSetI<_T>::getSize() const 
{
  return m_scalars.size();
}


//-----------------------------------------------------------------------------
template <typename _T>
double
MbScalarSetI<_T>::getMin() const
{
  typename std::vector<_T>::const_iterator itmin = std::min_element(m_scalars.begin(),m_scalars.end());
  return (double)(*itmin);
}


//-----------------------------------------------------------------------------
template <typename _T>
double
MbScalarSetI<_T>::getMax() const
{
  typename std::vector<_T>::const_iterator itmax = std::max_element(m_scalars.begin(),m_scalars.end());
  return (double)(*itmax);
}


//-----------------------------------------------------------------------------
template <typename _T>
std::ostream& 
MbScalarSetI<_T>::toStream(std::ostream& s) const
{
  s << "# scalarset name" << std::endl; 
  s << getName() << std::endl; 
  s << "# scalarset size" << std::endl;
  s << getSize() << std::endl;
  for (size_t i=0; i< m_scalars.size(); ++i)
     s << m_scalars[i] << std::endl; 

  return s;
}

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif








