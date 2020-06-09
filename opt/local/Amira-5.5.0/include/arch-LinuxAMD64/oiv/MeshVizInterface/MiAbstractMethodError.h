/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MIABSTRACTMETHODERROR_H
#define _MIABSTRACTMETHODERROR_H

#include <Inventor/STL/iostream>
#include <Inventor/STL/sstream>
#include <Inventor/STL/string>

/**
 * @DTEXT Exception handler for MeshViz Interface. 
 * 
 * @ingroup MeshIViz
 * 
 * @DESCRIPTION This class is used when throwing exceptions in methods that were not
 *              (but should have been) overloaded by the application. 
 *
 */
class MiAbstractMethodError 
{
public:
  /**
  * Constructor
  */
  MiAbstractMethodError(std::string methodName)
  {
    std::stringstream errorStream;
    errorStream << "method " << methodName << " is not implemented !";
    m_error = errorStream.str();
  };

  /**
  * Returns the error string containing the name of the method which is not overlaoded.
  */
  std::string getError() { return m_error;}; 

protected: 
  std::string m_error;
 
};

#endif
