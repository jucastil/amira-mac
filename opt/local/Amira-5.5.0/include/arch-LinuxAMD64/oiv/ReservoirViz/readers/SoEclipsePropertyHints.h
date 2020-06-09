/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  SOECLIPSEPROPERTYHINTS_H
#define  SOECLIPSEPROPERTYHINTS_H

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

#include <ReservoirViz/readers/SoEclipseBaseReader.h>

#include <Inventor/STL/iostream>
#include <Inventor/STL/string>

/**
* @RVEXT Eclipse property hints.
* 
* @DESCRIPTION
* 
*   This class describes an Eclipse property by giving some hints of this property.
*   For instance 
*    - Eclipe file name containing the property.
*    - data type.
*    - list of time steps.
*    - position of the first byte of the property in the file.
*
*   These hints are obtained by reading some few records of an init or restart Eclipse 
*   file. An instance of this class is associated to one property of an init file
*   or a restart file.
*
*   The method SoEclipsePropertyReader#getPropertyHints must be called to get
*   all the available instances of this class associated to an init file or a
*   restart file. 
*   
*   An instance of this class is given as input argument of the method
*   SoEclipsePropertyReader::setPropertyToRead. Thus, this methods defines
*   which property will be read by the next converter step.
* 
*/
class RESERVOIRVIZ_API SoEclipsePropertyHints
{
  // ----------------------- Public usage --------------------------------------
public:
  /** Constructor */
  SoEclipsePropertyHints();

  /**
  * Returns the id of this property in the Eclipse file.
  */
  int32_t getId() const;

  /**
   * Returns the Eclipse filename containing this property
   */
  SbString getFileName() const;

  /**
   * Returns the name of this Eclipse property. This name is 
   * defined in the Eclipse file containing this property.
   */
  SbString getName() const;

  /**
   * Returns the type of data contained in this Eclipse property. 
   */
  SoEclipseBaseReader::DataType getType() const;

  /**
  * Returns the dimension of the mesh associated to this property.
  */ 
  const SbVec3i32& getDim() const;

  /**
  *  Returns the number of active cells about this property.
  */
  int32_t getNumActiveCells() const;

  /**
  * Returns the list of time steps for this property.
  */ 
  const std::vector<SbVec3i32>& getTimeSteps() const;

  /**
  * Position in the Eclipse file of the first byte of this property.
  */
  int64_t getPos() const;

  /**
  * Distance in the Eclipse file between 2 time steps of this property.
  */
  int64_t getDeltaPos() const;

  /**
  * Output the property hints to a stream.
  */
  friend std::ostream& operator <<(std::ostream& os, const SoEclipsePropertyHints& _this);

  /**
  * Input the property hints from a stream.
  */
  friend std::istream& operator >>(std::istream& is, SoEclipsePropertyHints& _this);

SoINTERNAL public:

  SoEclipsePropertyHints(
    int32_t id,
    const SbString& name,
    SoEclipseBaseReader::DataType type,
    const SbVec3i32& dim,
    int32_t numActiveCells,
    int64_t pos,
    int64_t deltaPos,
    const SbVec3i32& timeStep,
    const SbString& fileName
  );

  void addTimeStep(SbVec3i32 timeStep);
  void setDeltaPos(int64_t deltaPos);
  void setId(int32_t id);

protected:
  // num order of the property in the file
  int32_t                       m_id;
  SbString                      m_fileName;
  SbString                      m_name;
  SoEclipseBaseReader::DataType m_type;
  SbVec3i32                     m_dim;
  int32_t                       m_numActiveCells;
  std::vector<SbVec3i32>        m_timeSteps;
  // position of the first occurrence of this property in the init or unrst file
  int64_t                       m_pos;
  // distance between 2 occurrences of this property in the init or unrst file. 
  // Actually this is the size (in byte) of one time step (sum of all record's size
  // contained in one time step). The size of a time step is supposed constant.
  int64_t                       m_deltaPos;
};


//------------------------------------------------------------------------------
inline
SoEclipsePropertyHints::SoEclipsePropertyHints() :
  m_name("Undefined property"),
  m_numActiveCells(0),
  m_pos(-1),
  m_deltaPos(-1)
{
}


//------------------------------------------------------------------------------
inline 
SoEclipsePropertyHints::SoEclipsePropertyHints(
  int32_t id,
  const SbString& name,
  SoEclipseBaseReader::DataType type,
  const SbVec3i32& dim,
  int32_t numActiveCells,
  int64_t pos,
  int64_t deltaPos,
  const SbVec3i32& timeStep,
  const SbString& fileName
  ) :
m_id(id),
m_name(name),
m_type(type),
m_dim(dim),
m_numActiveCells(numActiveCells),
m_pos(pos),
m_deltaPos(deltaPos)
{
  m_fileName = fileName;
  m_timeSteps.push_back(timeStep);
}

//------------------------------------------------------------------------------
inline int32_t 
SoEclipsePropertyHints::getId() const
{
  return m_id;
}

//------------------------------------------------------------------------------
inline SbString
SoEclipsePropertyHints::getFileName() const
{
  return m_fileName;
}

//------------------------------------------------------------------------------
inline SbString 
SoEclipsePropertyHints::getName() const
{
  return m_name;
}

//------------------------------------------------------------------------------
inline SoEclipseBaseReader::DataType 
SoEclipsePropertyHints::getType() const
{
  return m_type;
}

//------------------------------------------------------------------------------
inline const SbVec3i32& 
SoEclipsePropertyHints::getDim() const
{
  return m_dim;
}

//------------------------------------------------------------------------------
inline int32_t 
SoEclipsePropertyHints::getNumActiveCells() const
{
  return m_numActiveCells;
}

//------------------------------------------------------------------------------
inline const std::vector<SbVec3i32>& 
SoEclipsePropertyHints::getTimeSteps() const
{
  return m_timeSteps;
}

//------------------------------------------------------------------------------
inline int64_t 
SoEclipsePropertyHints::getPos() const
{
  return m_pos;
}

//------------------------------------------------------------------------------
inline int64_t 
SoEclipsePropertyHints::getDeltaPos() const
{
  return m_deltaPos;
}

//------------------------------------------------------------------------------
inline void
SoEclipsePropertyHints::setDeltaPos(int64_t deltaPos)
{
  m_deltaPos = deltaPos;
}

//------------------------------------------------------------------------------
inline void 
SoEclipsePropertyHints::addTimeStep(SbVec3i32 timeStep)
{
  m_timeSteps.push_back(timeStep);
}

//------------------------------------------------------------------------------
inline void
SoEclipsePropertyHints::setId(int32_t id)
{
  m_id = id;
}


//------------------------------------------------------------------------------
inline std::ostream& operator <<(std::ostream& os, const SoEclipsePropertyHints& _this)
{
  SbVec3i32 dim = _this.getDim();
  std::vector<SbVec3i32> times = _this.getTimeSteps();
  size_t numTimeSteps = times.size();

  os << _this.getId();
  os << " " << _this.getName();
  os << " " << int(_this.getType());
  os << " (" << dim[0] << " " << dim[1] << " " << dim[2] << ") ";
  os << " " << _this.getNumActiveCells();
  os << " " << _this.getPos();
  os << " " << _this.getDeltaPos();
  os << " " << numTimeSteps;
  os << " [";
  for (size_t t=0; t<numTimeSteps; ++t) 
  {
    SbVec3i32 ts = times[t];
    os << " " << ts[0] << "/" << ts[1] << "/" << ts[2];
  }
  os << " ]";
  os << " " << _this.getFileName().toStdString();

  return os;
}


//------------------------------------------------------------------------------
inline std::istream& operator >>(std::istream& is, SoEclipsePropertyHints& _this)
{
  int type, dx,dy,dz, numTimeSteps, t;
  char sepChar = ' ';
  std::vector<SbVec3i32> timeSteps;

  std::string name;

  is >> _this.m_id;
  is >> name;

  _this.m_name = SbString( name.c_str() );

  is >> type;
  _this.m_type = (SoEclipseBaseReader::DataType)type;

  do { is >> sepChar; } while (sepChar != '(');
  is >> dx >> dy >> dz;  
  _this.m_dim = SbVec3i32(dx,dy,dz);
  do 
  { 
	is >> sepChar; 
  } 
  while (sepChar != ')'); 

  is >> _this.m_numActiveCells;
  is >> _this.m_pos;
  is >> _this.m_deltaPos;
  is >> numTimeSteps;
  do { is >> sepChar; } while (sepChar != '['); 
  _this.m_timeSteps.clear();
  for (t=0; t<numTimeSteps; ++t) 
  {
    SbVec3i32 ts;
    is >> ts[0] >> sepChar >> ts[1] >> sepChar >> ts[2];
    _this.m_timeSteps.push_back(ts);
  }
  do 
  { 
	  is >> sepChar; 
  } 
  while (sepChar != ']');

  std::string filename;

  is >> filename;

  _this.m_fileName = filename.c_str();

  return is;
}


#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // SOECLIPSEPROPERTYHINTS_H
