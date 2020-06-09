/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MxTimeStamp_h
#define _MxTimeStamp_h

#include <MeshVizInterface/MxMeshIViz.h>

/**
* @DTEXT Manages an identifier that can be used as a time stamp.
* 
* @ingroup MeshIViz
* 
* @DESCRIPTION
* This static class can be used to get a new value for a time stamp.
* Each call to getTimeStamp() modifies the time stamp. 
* So every call to getTimeStamp() will return a new value.
* This class is useful (but only one possible way) to implement the
* getTimeStamp method of a MeshIViz interface class.
* @note This class is not thread safe and should not be used in a 
*       multi-threaded application.
*
*/
class MESHIVIZ_API MxTimeStamp
{
public:
  static size_t getTimeStamp() 
  {
    return m_timeStamp++;
  }

private:
  static size_t m_timeStamp;
};


#endif
