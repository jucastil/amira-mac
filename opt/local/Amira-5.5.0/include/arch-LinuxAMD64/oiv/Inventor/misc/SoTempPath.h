/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/



#ifndef  _SO_TEMP_PATH_
#define  _SO_TEMP_PATH_

#include <Inventor/SoPath.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTempPath
//
//  This class is internal to Inventor. It allows "temporary" paths to
//  be created - these paths do not support the same notification
//  behavior as SoPaths, and are therefore faster to construct and
//  modify. They are used during traversal to maintain the current
//  path through a graph. Since such paths are short-lived, there is
//  no reason to pay the price of the auditor overhead.
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class INVENTOR_API SoTempPath : public SoFullPath {
 public:
  // Constructor given approximate number of nodes in chain
  SoTempPath(int approxLength);
  virtual ~SoTempPath();
};

#endif /* _SO_TEMP_PATH_ */
