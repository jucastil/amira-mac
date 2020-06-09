/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MBVEC3SETI_H
#define  _MBVEC3SETI_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/data/MiDataSetI.h>
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
class MbVec3SetI : virtual public MiVec3dSetI, public MbDataSet
{
public:
  /**
  * Constructor for an empty default dataset.
  * This dataset has a default name depending on the number of instances created.
  * Its binding is set to PER_NODE by default.
  */
  MbVec3SetI();

  /**
  * Defines a new dataset by copying the given data from the interval [begin,end[.
  * This dataset has a default name depending on the number of instances created.
  * Its binding is set to PER_NODE by default.
  * @param begin start iterator.
  * @param end end iterator.
  */
  template <typename _Vec3Iter>
  MbVec3SetI(_Vec3Iter begin, _Vec3Iter end);

  /**
  * Defines a new dataset by copying the given data from the interval [begin,end[.
  * Its binding is set to PER_NODE by default.
  * @param begin start iterator.
  * @param end end iterator.
  * @param name the name of this dataset.
  * @param binding the binding of this dataset.
  */
  template <typename _Vec3Iter>
  MbVec3SetI(_Vec3Iter begin, _Vec3Iter end, const std::string& name, DataBinding binding=PER_NODE);

  /**
  * Change the content of this dataset. Clears the current content and copy the 
  * data from the interval [begin,end[.
  * The timestamp of this dataset is incremented.
  * @param begin start iterator.
  * @param end end iterator.
  */
  template <typename _Vec3Iter>
  void assign(_Vec3Iter begin, _Vec3Iter end);

  /**
  * Returns the i-th value of this set.
  */
  virtual MbVec3d get(size_t i) const;

  /**
  * Returns the number of values in this set.
  */
  virtual size_t getSize() const;

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

};


template <typename _T>
size_t MbVec3SetI<_T>::s_numInstance = 0;


//-----------------------------------------------------------------------------
template <typename _Vec3T>
inline 
MbVec3SetI<_Vec3T>::MbVec3SetI()
{
  std::ostringstream defName; 
  defName << "MbVec3Set_#" << s_numInstance++;
  m_name = defName.str();
}

//-----------------------------------------------------------------------------
template <typename _Vec3T>
template <typename _Vec3Iter>
inline 
MbVec3SetI<_Vec3T>::MbVec3SetI(
  _Vec3Iter beginCoord, _Vec3Iter endCoord
  ) 
  : m_coords(beginCoord,endCoord)
{
  std::ostringstream defName; 
  defName << "MbVec3Set_#" << s_numInstance++;
  m_name = defName.str();
}

//-----------------------------------------------------------------------------
template <typename _Vec3T>
template <typename _Vec3Iter>
inline 
MbVec3SetI<_Vec3T>::MbVec3SetI(_Vec3Iter beginCoord, _Vec3Iter endCoord, 
                             const std::string& name,
                             DataBinding binding) 
: MbDataSet(name,binding), m_coords(beginCoord,endCoord)
{
  s_numInstance++;
}

//-----------------------------------------------------------------------------
template <typename _Vec3T>
template <typename _Vec3Iter>
inline void
MbVec3SetI<_Vec3T>::assign(_Vec3Iter beginCoord, _Vec3Iter endCoord)
{
  m_coords.assign(beginCoord,endCoord);
  m_timeStamp = MxTimeStamp::getTimeStamp();
}


//-----------------------------------------------------------------------------
template <typename _Vec3T>
inline MbVec3d
MbVec3SetI<_Vec3T>::get(size_t i) const
{
  return (MbVec3d)m_coords[i]; 
}

//-----------------------------------------------------------------------------
template <typename _Vec3T>
inline size_t
MbVec3SetI<_Vec3T>::getSize() const 
{
  return m_coords.size();
}


//-----------------------------------------------------------------------------
template <typename _Vec3T>
inline MbVec3d
MbVec3SetI<_Vec3T>::getMin() const
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
MbVec3SetI<_Vec3T>::getMax() const
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
MbVec3SetI<_Vec3T>::toStream(std::ostream& s) const
{
  s << "# vec3set name" << std::endl; 
  s << getName() << std::endl; 
  s << "# vec3set size" << std::endl;
  s << getSize() << std::endl;
  for (size_t i=0; i< m_coords.size(); ++i)
    s << m_coords[i] << std::endl; 

  return s;
}

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif








