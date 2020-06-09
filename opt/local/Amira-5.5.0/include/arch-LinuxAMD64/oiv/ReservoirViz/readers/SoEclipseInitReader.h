/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  SoEclipseInitReader_H
#define  SoEclipseInitReader_H

#include <ReservoirViz/readers/SoEclipsePropertyReader.h>
#include <ReservoirViz/readers/SoEclipsePropertyHints.h>
#include <Inventor/STL/vector>

class SoEclipseRecord;

/**
 * @RVEXT Eclipse INIT file reader.
 * 
 * @DESCRIPTION
 * 
 * This reader reads Eclipse INIT files (extension .init, meaning "initial file").
 *
 * 
 */
class RESERVOIRVIZ_API SoEclipseInitReader : public SoEclipsePropertyReader
{
  SO_FIELDCONTAINER_HEADER(SoEclipseInitReader);

  // ----------------------- Public usage --------------------------------------
public:

  /** Default constructor */
  SoEclipseInitReader();

  /**
   * Returns the property hints found in the INIT file.
   */
  virtual const std::vector<SoEclipsePropertyHints>& getPropertyHints();

};

#endif // SoEclipseInitReader_H
