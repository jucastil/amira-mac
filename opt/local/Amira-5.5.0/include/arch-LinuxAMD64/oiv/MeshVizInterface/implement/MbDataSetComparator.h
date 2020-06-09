/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MBDATASETCOMPARATOR_H
#define _MBDATASETCOMPARATOR_H

/**
* @DTEXT Data set comparator.
* 
* @ingroup MeshIViz_Implement
*/
template <typename _DataSetT>
class MbDataSetComparator
{
public:
  /** Comparator (compares data set name). */
  bool operator()(_DataSetT ds1, _DataSetT ds2) const
  {
    return (ds1->getName().compare(ds2->getName()) < 0);
  }
};



#endif
