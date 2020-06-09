/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  SoEclipseRestartReader_H
#define  SoEclipseRestartReader_H

#include <ReservoirViz/readers/SoEclipsePropertyReader.h>

/**
 * @RVEXT Eclipse RESTART file reader.
 * 
 * @DESCRIPTION
 * 
 * This reader reads Eclipse RESTART files (extension .unrst, meaning "unified restart file").
 *
 * 
 */
class RESERVOIRVIZ_API SoEclipseRestartReader : public SoEclipsePropertyReader
{
  SO_FIELDCONTAINER_HEADER(SoEclipseRestartReader);

  // ----------------------- Public usage --------------------------------------
public:

  /** Constructor. */
  SoEclipseRestartReader();

  /**
  * Returns the property hints found in the UNRST file.
  */
  virtual const std::vector<SoEclipsePropertyHints>& getPropertyHints();

  /**
  * Returns the number of time steps.
  */
  virtual int getNumTimeSteps();

  // ----------------------- Protected usage -------------------------------------
protected:
  /*
  * Returns the delta between the first time step and the current time step.
  * Returns 0 for file that do not contains multiple time steps.
  */
  virtual int64_t getDeltaPos();

};


#endif // SoEclipseRestartReader_H
