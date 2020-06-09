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

/// @addtogroup hximio hximio
/// @{
#ifndef HXIMSTKFORMAT_H
#define HXIMSTKFORMAT_H

#include "HxImFormatInterface.h"
#include <exlibtiff/tiff.h>

#define DIM_STK_AutoScale              0
#define DIM_STK_MinScale               1
#define DIM_STK_MaxScale               2
#define DIM_STK_SpatialCalibration     3
#define DIM_STK_XCalibration           4
#define DIM_STK_YCalibration           5
#define DIM_STK_CalibrationUnits       6
#define DIM_STK_Name                   7
#define DIM_STK_ThreshState            8
#define DIM_STK_ThreshStateRed         10
#define DIM_STK_ThreshStateGreen       11
#define DIM_STK_ThreshStateBlue        12
#define DIM_STK_ThreshStateLo          13
#define DIM_STK_ThreshStateHi          14
#define DIM_STK_Zoom                   15
#define DIM_STK_CreateTime             16
#define DIM_STK_LastSavedTime          17
#define DIM_STK_currentBuffer          18
#define DIM_STK_grayFit                19
#define DIM_STK_grayPointCount         20
#define DIM_STK_grayX                  21
#define DIM_STK_grayY                  22
#define DIM_STK_grayMin                23
#define DIM_STK_grayMax                24
#define DIM_STK_grayUnitName           25
#define DIM_STK_StandardLUT            26
#define DIM_STK_wavelength             27
#define DIM_STK_StagePosition          28
#define DIM_STK_CameraChipOffset       29
#define DIM_STK_OverlayMask            30
#define DIM_STK_OverlayCompress        31
#define DIM_STK_Overlay                32
#define DIM_STK_SpecialOverlayMask     33
#define DIM_STK_SpecialOverlayCompress 34
#define DIM_STK_SpecialOverlay         35
#define DIM_STK_ImageProperty          36 
#define DIM_STK_StageLabel             37
#define DIM_STK_AutoScaleLoInfo        38
#define DIM_STK_AutoScaleHiInfo        39
#define DIM_STK_AbsoluteZ              40
#define DIM_STK_AbsoluteZValid         41
#define DIM_STK_Gamma                  42
#define DIM_STK_GammaRed               43
#define DIM_STK_GammaGreen             44
#define DIM_STK_GammaBlue              45

static int stk_tag_sizes_long[46] = 
{ 
    1, 1, 1, 1,
    2, 2, 
    1, // contains the size of following string in bytes
    1, // contains the size of following string in bytes
    1, 1, 1, 1,
    1, 1, 1, 2,
    2, 1, 1, 1,
    2, 2, 2, 2,
    1, // contains the size of following string in bytes
    1, 1, 
    4, // 4*N longs
    4, // 4*N longs
    1, 1, 1, 1, 1, 1, 1,
    1, // N longs
    2, 2,
    2, // 2*N longs 
    1, // N longs
    1, 1, 1, 1
};

#define long DIM_LONG

typedef struct TDimStkRational
{
    long num;
    long den;
} TDimStkRational;

// each dynamic array here is f size N
typedef struct TDimStkMetaData
{
    long N;

    // UIC1 and UIC4
    long AutoScale;
    long MinScale;
    long MaxScale;
    long SpatialCalibration;
    long XCalibration[2];
    long YCalibration[2];
    char *CalibrationUnits;
    char *Name;
    long ThreshState;
    unsigned long ThreshStateRed;
    unsigned long ThreshStateGreen;
    unsigned long ThreshStateBlue;
    unsigned long ThreshStateLo;
    unsigned long ThreshStateHi;
    long Zoom;
    long CreateTime[2];
    long LastSavedTime[2];
    long currentBuffer;
    long grayFit;
    long grayPointCount;
    long grayX[2];
    long grayY[2];
    long grayMin[2];
    long grayMax[2];
    char *grayUnitName;
    long StandardLUT;
    //long wavelength; // discard it, don't read, the UIC3 value should be used

    // begin: Used internally by MetaMorph
    long OverlayMask;
    long OverlayCompress;
    long Overlay;
    long SpecialOverlayMask;
    long SpecialOverlayCompress;
    long SpecialOverlay;
    long ImageProperty;
    // end: Used internally by MetaMorph

    long AutoScaleLoInfo[2];
    long AutoScaleHiInfo[2];
    long Gamma; 
    long GammaRed; 
    long GammaGreen; 
    long GammaBlue; 

    // UIC3
    TDimStkRational *wavelength;

    // UIC2
    TDimStkRational *zDistance;
    long *creationDate;
    long *creationTime;
    long *modificationDate;
    long *modificationTime;

    //UIC4
    TDimStkRational *StagePositionX;
    TDimStkRational *StagePositionY;
    TDimStkRational *CameraChipOffsetX;
    TDimStkRational *CameraChipOffsetY;
    char *StageLabel; 
    TDimStkRational *AbsoluteZ; 
    TDimStkRational *AbsoluteZValid; 

} TDimStkMetaData;

#undef long

typedef struct TDimStkInfo
{
    uint32 strips_per_plane; // strips per plane
    uint32 *strip_offsets; // offsets of each strip
    TDimStkMetaData metaData;
    uint32 *strip_bytecounts; // offsets of each strip
} TDimStkInfo;

#endif // HXIMSTKFORMAT_H

/// @}
