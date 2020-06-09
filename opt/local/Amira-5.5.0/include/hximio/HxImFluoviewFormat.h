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
#ifndef HXIMFLUOVIEWFORMAT_H
#define HXIMFLUOVIEWFORMAT_H

#include <vector>
#include <string>

#include "HxImFormatInterface.h"

//----------------------------------------------------------------------------
// Internal Fluoview Structures
//----------------------------------------------------------------------------

#define MMHEADER  34361

#define IMAGE_NAME_LENGTH   256
#define SPATIAL_DIMENSION   10
#define DIMNAME_LENGTH      16
#define UNITS_LENGTH        64

typedef DIM_UINT32 MM_HANDLE;      // Size (bytes):     4

#pragma pack(push, 1)
typedef struct MM_DIM_INFO
{
    DIM_CHAR      Name[DIMNAME_LENGTH]; //Dimension name e.g. Width   16
    DIM_UINT32    Size;                 //Image width etc              4
    DIM_DOUBLE    Origin;               //Origin                       8
    DIM_DOUBLE    Resolution;           //Image resolution             8
    DIM_CHAR      Units[UNITS_LENGTH];  //Image calibration units     64
} MM_DIM_INFO;                          // Total Size (bytes):       100

typedef struct MM_HEAD
{
    DIM_INT16     HeaderFlag;                 //Size of header structure             2
    DIM_UCHAR     ImageType;                  //Image Type                           1
    DIM_CHAR      Name[IMAGE_NAME_LENGTH];    //Image name                         256
    DIM_UCHAR     Status;                     //image status                         1
    DIM_UINT32    Data;                       //Handle to the data field             4
    DIM_UINT32    NumberOfColors;             //Number of colors in palette          4
    DIM_UINT32    MM_256_Colors;              //handle to the palette field          4
    DIM_UINT32    MM_All_Colors;              //handle to the palette field          4
    DIM_UINT32    CommentSize;                //Size of comments field               4
    DIM_UINT32    Comment;                    //handle to the comment field          4
    MM_DIM_INFO   DimInfo[SPATIAL_DIMENSION]; //Dimension Info                    1000
    DIM_UINT32    SpatialPosition;            //obsolete???????????                  4
    DIM_INT16     MapType;                    //Display mapping type                 2
    //short         reserved;                   //Display mapping type                 2
    DIM_DOUBLE    MapMin;                     //Display mapping minimum              8
    DIM_DOUBLE    MapMax;                     //Display mapping maximum              8
    DIM_DOUBLE    MinValue;                   //Image histogram minimum              8
    DIM_DOUBLE    MaxValue;                   //Image histogram maximum              8
    MM_HANDLE     Map;                        //Handle to gray level mapping array   4
    DIM_DOUBLE    Gamma;                      //Image gray level correction factor   8
    DIM_DOUBLE    Offset;                     //Image gray level correction offset   8
    MM_DIM_INFO   Gray;                       //                                   100
    MM_HANDLE     ThumbNail;                  //handle to the ThumbNail field        4
    DIM_UINT32    UserFieldSize;              //Size of Voice field                  4
    MM_HANDLE     UserFieldHandle;            //handle to the Voice field            4
} MM_HEAD;                                    // Total Size (bytes):              1456
#pragma pack(pop)

//----------------------------------------------------------------------------
// TIFF Codec-wise Fluoview Structure
//----------------------------------------------------------------------------
typedef struct TDimFluoviewInfo
{
    int ch;       // number of channels in each image of the sequence
    int z_slices; // number of Z slices for each time instance
    int t_frames; // number of time frames in the sequence
    int pages;    // the value of consequtive images generated by driver
    double xR, yR, zR; // pixel resolution for XYZ
    MM_HEAD head; // actual header structure retreived form the image

    //internal
    int pages_tiff;
    std::vector<std::string> sample_names;
    std::vector<int> display_lut; // rgb -> chan numbers
} TDimFluoviewInfo;


#endif // HXIMFLUOVIEWFORMAT_H

/// @}
