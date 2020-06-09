/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MBDATASET__H
#define _MBDATASET__H

#include <Inventor/STL/string>
#include <Inventor/STL/iostream>

#include <MeshVizInterface/mesh/data/MiDataSet.h>
#include <MeshVizInterface/implement/MbMeshVizImpl.h>
#include <MeshVizInterface/MbVec3.h>
#include <MeshVizInterface/MxTimeStamp.h>

//-----------------------------------------------------------------------------
/**
* @DTEXT Generic data set implementation.
* 
* @ingroup MeshIViz_Implement_Data
* 
* @DESCRIPTION
*    A generic abstract template interface for a data set usable in any extract or geometry of a mesh.
* 
*/

class MbDataSet: virtual public MiDataSet
{
public:
  /**
  * Constructor for an empty default dataset. @BR
  * Initializes name to empty string, data binding to PER_NODE and
  * timestamp to 1.
  */
  MbDataSet();

  /**
  * Constructor for dataset with specific name and
  * specific data binding. Initializes timestamp to 1.
  */
  MbDataSet(const std::string& name, DataBinding binding);

  /**
  * Returns the time stamp on this data set. When the content of the dataset 
  * changes, the time stamp must also change. The time stamp allows MeshViz 
  * to be aware of any change to this dataset.
  */
  virtual size_t getTimeStamp() const
  {
    return m_timeStamp;
  }

  /**
  * Returns the name of this dataset.
  */
  virtual std::string getName() const
  {
    return m_name;
  }

  /**
  * Define the name of this dataset (default is empty string).
  */
  virtual void setName(const std::string& name)
  {
    m_name = name;
  }

  /**
  * Returns the binding of this dataset.
  */
  virtual DataBinding  getBinding() const
  {
    return m_binding;
  }

  /**
  * Define the data binding of this dataset (default is PER_NODE).
  */
  virtual void  setBinding(DataBinding binding)
  {
    m_binding = binding;
  }

  /**
  * @internal
  * Simulate a modification to this dataset
  */
  void touch()
  {
    m_timeStamp = MxTimeStamp::getTimeStamp();
  }

protected:  
  /**
  * Defines a specialized output on stream for MbDataSet
  */
  virtual std::ostream& toStream(std::ostream& s) const;
 
  DataBinding      m_binding;
  std::string      m_name;
  size_t           m_timeStamp;

};

//-----------------------------------------------------------------------------
inline 
MbDataSet::MbDataSet() :
m_binding(PER_NODE),
m_timeStamp(MxTimeStamp::getTimeStamp()),
m_name("")
{
}

//-----------------------------------------------------------------------------
inline 
MbDataSet::MbDataSet(const std::string& name, MiDataSet::DataBinding binding):
  m_binding(binding),m_timeStamp(MxTimeStamp::getTimeStamp()),m_name(name)
{
}

//-----------------------------------------------------------------------------
inline std::ostream& 
MbDataSet::toStream(std::ostream& s) const
{
  s << "# dataset name" << std::endl; 
  s <<  m_name << std::endl;
  s << "# databinding" << std::endl; 
  if(m_binding ==  PER_NODE)
    s <<  "PER_NODE" << std::endl;
  else
    s <<  "PER_CELL" << std::endl;
  return s;
}

#endif
