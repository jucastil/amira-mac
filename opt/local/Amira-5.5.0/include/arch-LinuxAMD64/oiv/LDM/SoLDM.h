/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
/*===============================================================================*/


#ifndef SO_LDM_H
#define SO_LDM_H

#include <LDM/SoLDMTileID.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/set>
#include <Inventor/STL/pair>

// On Windows the "comment" pragma will automatically add our LDM
//library to the application's link string.
#ifdef _WIN32
#  include <SoVersion.h>
#  if defined(_DEBUG)
#    define __LDMDLL "LDMD.dll"
#    define __LDMLIB "LDMD.lib"
#  else
#    define __LDMDLL "LDM.dll"
#    define __LDMLIB "LDM.lib"
#  endif
#  ifndef LDM_EXPORTS
#    ifndef OIV_DISABLE_AUTOLINK
#      pragma comment(lib,__LDMLIB)
#    endif
#  endif
#else
#  define  __LDMDLL "libLDM"
#endif // _WIN32

#include <Inventor/SoModule.h>
SO_MODULE_HEADER(SoLDM, __LDMDLL)

class SoDataSet;

namespace SoLDM
{
  /**
   * Vector of SoDataSet
   */
  typedef std::vector<SoDataSet*> DsVector;

  /**
   * Iterator for DsVector
   */
  typedef DsVector::iterator DsVectorIt;

  /**
   * Set of SoDataSet
   */
  typedef std::set<SoDataSet*> DsSet;

  /**
   * Pair containing an SoDataset and its dataSetId
   */
  typedef std::pair<SoDataSet*, int> DataSetIdPair;

  /**
   * List of DataSetIdPair
   */
  typedef std::vector<DataSetIdPair> DataSetIdPairList;

  /**
   * Vector of SoLDMTileID
   */
  typedef std::vector<SoLDMTileID> TileIdVector;
}

#endif // SO_LDM_H
