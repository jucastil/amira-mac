/*
Copyright 1999-2013 Visualization Sciences Group, SAS
Copyright 1995-2013, ZIB Berlin
ALL RIGHTS RESERVED.

amira(R) is a registered trademark of ZIB.

amira(R) is being jointly developed by Zuse Institute Berlin and
Visualization Sciences Group, SAS.
Avizo® is a registered trademark of Visualization Sciences Group, SAS
HardCopy, MeshViz, VolumeViz, TerrainViz are marks of Visualization
Sciences Group, SAS 
Visualization Sciences Group, SAS is a source licensee of OpenGL®, Open Inventor® 
from Silicon Graphics, Inc. OpenGL® and Open Inventor® are 
registered trademark of Silicon Graphics, Inc. All other products and 
company names are trademarks or registered trademarks of 
their respective companies. 

FEI Visualization Sciences Group accepts no liability to any 
party for loss or damage caused by errors or omissions or by 
statements of any kind in this publication, whether such errors 
result from accident, negligence or any other cause. FEI Visualization
Sciences Group assumes  no liability for incidental or consequential
damages arising from the use of information in this publication.
FEI Visualization Sciences Group provides no 
warranties regarding the information contained in this 
publication, whether expressed, implied, or statutory, including 
implied warranties of merchantability or fitness for a 
particular purpose. 

FEI Visualization Sciences Group also does not assume any liability
for links from this publication to publications from other companies,
organizations or individuals. FEI Visualization Sciences Group does not
imply endorsement of any specific  company, organization or individual
through offering links to this content.
All information provided within this publication 
is subject to change at any time and is provided for 
informational purposes only by FEI Visualization Sciences Group.
Copyright 1994-2012 by Visualization Sciences Group, SAS Merignac, France.

*/

/// @addtogroup hxskeleton hxskeleton
/// @{
#ifndef CHAMFERMAP_H
#define CHAMFERMAP_H



#ifdef _YAV_ // namespace for INIRA
#include "ChamferMask.h"
namespace yav {
#define HXSKELETON_API 
#else
#include "hxskeleton/ChamferMask.h"
#include "hxskeleton/HxSkeletonWinDLLApi.h"
#endif

  enum { // Initialization flags :  
    // used for chamfer map initialization on Large Data (LDA in Amira)
    _DistanceMap_NI,    // normal initialization
    
    // keep the old values of the image's border during initialization, for :
    _DistanceMap_FS,   // the first Slices
    _DistanceMap_FL,   // the first Lines
    _DistanceMap_FC,   // first Columns
    _DistanceMap_FSL,  // both the first Slices and fisrt Lines
    _DistanceMap_FSC,  // both the first Slices and first Columns
    _DistanceMap_FLC,  // both the first Lines  and first Columns
    _DistanceMap_FSLC, // the first Slices and the first Lines and the first Columns

    _DistanceMap_LS,   // the last Slices
    _DistanceMap_LL,   // the last Lines
    _DistanceMap_LC,   // the last Columns
    _DistanceMap_LSL,  // both the last Slices and last Lines
    _DistanceMap_LSC,  // both the last Slices and last Columns
    _DistanceMap_LLC,  // both the last Lines  and last Columns
    _DistanceMap_LSLC // the last Slices and the last Lines and the last Columns

  };

/* class ChamferMap : template class to compute distance/norme map on a buffer */

template <class DATATYPE>
class HXSKELETON_API ChamferMap
{
public :
  /* Constructors */
  //
  ChamferMap(DATATYPE infinity, int maskSize = 3, int maskDim = 3, float voxelSize = 1.0);

  //
  ChamferMap(DATATYPE infinity, float dy, float dz, float voxelSize = 1.0);

  /* Destructor */
  //
  ~ChamferMap();

  /* Accessors */
  int getIBegin();
  int getJBegin();
  int getKBegin();


  /* Public methods */
  //
  void computeChamferMap(DATATYPE * buffer, const int * dims);
  //
  void computeChamferMapOut(DATATYPE * buffer, const int * dims);
  //
  void computeChamferMapInOut(DATATYPE * buffer, const int * dims);
  //
  void initMasksOffsets(const int * dims);
  //
  float getExactValue(DATATYPE * buffer, int pos);
  //
  float * getExactMap(DATATYPE * buffer, const int * dims);
  // 
  float getScaleFactor();
  //
  float getMaxRelativeError();

  void changeSign(DATATYPE * buffer, const int * dims);

  /* Methods for the inside of the object */
  //
  void initBoundaries(DATATYPE * buffer, const int * dims, int flag = _DistanceMap_NI);
  //
  void forwardRun(DATATYPE * buffer, const int * dims);
  //

  void backwardRun(DATATYPE * buffer, const int * dims);
  /* Methods for the outside of the object */
  //
  void initBoundariesOut(DATATYPE * buffer, const int * dims, int flag = _DistanceMap_NI);
  //
  void forwardRunOut(DATATYPE * buffer, const int * dims);
  //
  void backwardRunOut(DATATYPE * buffer, const int * dims);
  /* Methods for both the inside and the outside of the object */
  //
  void initBoundariesInOut(DATATYPE * buffer, const int * dims, int flag = _DistanceMap_NI);
  //
  void forwardRunInOut(DATATYPE * buffer, const int * dims);
  //
  void backwardRunInOut(DATATYPE * buffer, const int * dims);


protected :
  /* Protected methods */

  /* Methods for the inside of the object */
  //
  void _initFirstSlices (DATATYPE ** buffer, const int * dims, int flag);
  //
  void _initLastSlices  (DATATYPE ** buffer, const int * dims, int flag);
  //
  void _initFirstLines  (DATATYPE ** buffer, const int * dims, int flag);
  //
  void _initLastLines   (DATATYPE ** buffer, const int * dims, int flag);
  //
  void _initFirstColumns(DATATYPE ** buffer, const int * dims, int flag);
  //
  void _initLastColumns (DATATYPE ** buffer, const int * dims, int flag);

  //
  void _forwardRunFirstSlices (DATATYPE ** buffer, const int * dims);
  //
  void _forwardRunFirstLines  (DATATYPE ** buffer, const int * dims);
  //
  void _forwardRunLastLines   (DATATYPE ** buffer, const int * dims);
  //
  void _forwardRunFirstColumns(DATATYPE ** buffer, const int * dims);
  //
  void _forwardRunLastColumns (DATATYPE ** buffer, const int * dims);

  //
  void _backwardRunLastSlices  (DATATYPE ** buffer, const int * dims);
  //
  void _backwardRunLastLines   (DATATYPE ** buffer, const int * dims);
  //
  void _backwardRunFirstLines  (DATATYPE ** buffer, const int * dims);
  //
  void _backwardRunLastColumns (DATATYPE ** buffer, const int * dims);
  //
  void _backwardRunFirstColumns(DATATYPE ** buffer, const int * dims);

  /* Methods for the outside of the object */
  //
  void _initFirstSlicesOut (DATATYPE ** buffer, const int * dims, int flag);
  //
  void _initLastSlicesOut  (DATATYPE ** buffer, const int * dims, int flag);
  //
  void _initFirstLinesOut  (DATATYPE ** buffer, const int * dims, int flag);
  //
  void _initLastLinesOut   (DATATYPE ** buffer, const int * dims, int flag);
  //
  void _initFirstColumnsOut(DATATYPE ** buffer, const int * dims, int flag);
  //
  void _initLastColumnsOut (DATATYPE ** buffer, const int * dims, int flag);

  //
  void _forwardRunFirstSlicesOut (DATATYPE ** buffer, const int * dims);
  //
  void _forwardRunFirstLinesOut  (DATATYPE ** buffer, const int * dims);
  //
  void _forwardRunLastLinesOut   (DATATYPE ** buffer, const int * dims);
  //
  void _forwardRunFirstColumnsOut(DATATYPE ** buffer, const int * dims);
  //
  void _forwardRunLastColumnsOut (DATATYPE ** buffer, const int * dims);

  //
  void _backwardRunLastSlicesOut  (DATATYPE ** buffer, const int * dims);
  //
  void _backwardRunLastLinesOut   (DATATYPE ** buffer, const int * dims);
  //
  void _backwardRunFirstLinesOut  (DATATYPE ** buffer, const int * dims);
  //
  void _backwardRunLastColumnsOut (DATATYPE ** buffer, const int * dims);
  //
  void _backwardRunFirstColumnsOut(DATATYPE ** buffer, const int * dims);


  /* Methods for both the inside and the outside of the object */
  //
  void _initFirstSlicesInOut (DATATYPE ** buffer, const int * dims, int flag);
  //
  void _initLastSlicesInOut  (DATATYPE ** buffer, const int * dims, int flag);
  //
  void _initFirstLinesInOut  (DATATYPE ** buffer, const int * dims, int flag);
  //
  void _initLastLinesInOut   (DATATYPE ** buffer, const int * dims, int flag);
  //
  void _initFirstColumnsInOut(DATATYPE ** buffer, const int * dims, int flag);
  //
  void _initLastColumnsInOut  (DATATYPE ** buffer, const int * dims, int flag);

  //
  void _forwardRunFirstSlicesInOut (DATATYPE ** buffer, const int * dims);
  //
  void _forwardRunFirstLinesInOut  (DATATYPE ** buffer, const int * dims);
  //
  void _forwardRunLastLinesInOut   (DATATYPE ** buffer, const int * dims);
  //
  void _forwardRunFirstColumnsInOut(DATATYPE ** buffer, const int * dims);
  //
  void _forwardRunLastColumnsInOut (DATATYPE ** buffer, const int * dims);

  //
  void _backwardRunLastSlicesInOut  (DATATYPE ** buffer, const int * dims);
  //
  void _backwardRunLastLinesInOut   (DATATYPE ** buffer, const int * dims);
  //
  void _backwardRunFirstLinesInOut  (DATATYPE ** buffer, const int * dims);
  //
  void _backwardRunLastColumnsInOut (DATATYPE ** buffer, const int * dims);
  //
  void _backwardRunFirstColumnsInOut(DATATYPE ** buffer, const int * dims);


  /* Fields */
  //
  ChamferMask * mask;
  //
  ChamferMask * maskInit;
  //
  DATATYPE _infinity;
  //
  float voxelSize;

#ifdef _YAV_
#include "ChamferMapOpt.h"
#endif

};

#ifdef _YAV_
} // namespace yav
#endif

#include "ChamferMapImpl.h"

#ifdef _YAV_
#include "ChamferMapOpt.cpp"
#endif

#endif //CHAMFERMAP_H



/// @}
