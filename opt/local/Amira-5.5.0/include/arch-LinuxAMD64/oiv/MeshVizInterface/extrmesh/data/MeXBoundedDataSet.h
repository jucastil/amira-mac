/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MeXBoundedDataSet_H
#define _MeXBoundedDataSet_H

#include <Inventor/STL/string>
#include <Inventor/STL/iostream>

#include <MeshVizInterface/mesh/data/MiBoundedDataSet.h>

//-----------------------------------------------------------------------------
/**
* @DTEXT Generic extracted data set interface.
* 
* @ingroup MeshIViz_ExtractedMesh_DataSets
* 
* @DESCRIPTION
*    A generic abstract template interface for an extracted data set with boundaries (min and max) returned by any extract of a mesh.
* 
*/
template <typename _T>
class MeXBoundedDataSet: virtual public MiBoundedDataSet<_T>
{
  /*
  * Returns the mean value of this set.
  */
  virtual _T getMean() const = 0;

  /*
  * Returns the standard deviation value of this set.
  */
  virtual _T getStandardDeviation() const = 0;


};

#endif
