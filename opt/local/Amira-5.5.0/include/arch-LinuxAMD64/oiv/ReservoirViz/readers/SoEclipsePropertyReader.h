/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  SoEclipsePropertyReader_H
#define  SoEclipsePropertyReader_H

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

#include <ReservoirViz/readers/SoEclipseBaseReader.h>
#include <ReservoirViz/readers/SoEclipsePropertyHints.h>
#include <Inventor/STL/vector>
#include <Inventor/STL/string>

class SoEclipseRecord;

/**
 * @RVEXT Generic reader of Eclipse property files.
 * 
 * @DESCRIPTION
 * 
 * Generic reader of Eclipse property files.
 *
 * 
 */
class RESERVOIRVIZ_API SoEclipsePropertyReader :
  public
  SoEclipseBaseReader
{
  SO_FIELDCONTAINER_HEADER(SoEclipsePropertyReader);

  // ----------------------- Public usage --------------------------------------
public:

    /**
    * Constructor.
    */
  SoEclipsePropertyReader();

  ////for volume having a series of data per datum
  ////used by ReservoirViz. The converter asks the eclipse reader for the datum.
  ////not used in vviz which uses getDataChar(...type...). (must keep for compatibility reasons).
  //virtual ReadError getDataChar( SbBox3f &size, std::vector<SoDataSet::DatumElement>& datum, SbVec3i32 &dim );

  /**
   * Returns the characteristics of the init or restart data set. 
   */
  virtual ReadError getDataChar( SbBox3f& size, SoDataSet::DataType& type, SbVec3i32& dim );
  
  /**
   * Extracts a subslice of one property in the INIT or RESTART file. The property to read is defined 
   * by #setPropertyToRead().
   */
  virtual void getSubSlice( const SbBox2i32& subSlice, int sliceNumber, void* data );

  /**
   * Specifies the name of the property data to be read in the INIT or RESTART file by #getSubSlice().
   */
  void setPropertyToRead(std::string propertyName);

  /**
  * Specifies the property data to be read in the INIT or RESTART file by #getSubSlice().
  */
  void setPropertyToRead(const SoEclipsePropertyHints& propertyToRead);

  /**
  * Returns the property hints found in the property file.
  */
  virtual const std::vector<SoEclipsePropertyHints>& getPropertyHints();

  /**
  * Outputs to a C++ stream the contents of the property read from the file.
  */
  friend std::ostream& operator <<(std::ostream& os, const SoEclipsePropertyReader& _this);

SoINTERNAL public:

  // ----------------------- Protected usage -------------------------------------
protected:
  /**
  * Destructor.
  */
  virtual ~SoEclipsePropertyReader();

  /*
   * Returns the delta between the first time step and the current time step.
   * Returns 0 for file that do not contains multiple time steps.
   */
  virtual int64_t getDeltaPos();

  mutable SoEclipseRecord* m_record;

  std::vector<SoEclipsePropertyHints> m_propertiesHints;
  SoEclipsePropertyHints m_propertyToRead;

};


// ----------------------- inline definitions -------------------------------- 
inline const std::vector<SoEclipsePropertyHints>& 
SoEclipsePropertyReader::getPropertyHints()
 {
   return m_propertiesHints;
 }

// ----------------------- inline definitions -------------------------------- 
inline void
SoEclipsePropertyReader::setPropertyToRead(const SoEclipsePropertyHints& propertyToRead) 
{
  m_propertyToRead = propertyToRead;
}

inline int64_t
SoEclipsePropertyReader::getDeltaPos()
{
  return 0;
}

inline std::ostream& 
operator <<(std::ostream& os, const SoEclipsePropertyReader& _this)
{
  return _this.operator_out(os); 
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // SoEclipsePropertyReader_H
