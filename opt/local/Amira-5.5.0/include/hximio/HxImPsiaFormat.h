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
#ifndef HXIMPSIAFORMAT_H
#define HXIMPSIAFORMAT_H

#include "HxImFormatInterface.h"

#define DIM_PSIA_OFFSET_SOURCENAME   4
#define DIM_PSIA_OFFSET_IMAGEMODE    68
#define DIM_PSIA_OFFSET_LPFSSTRENGTH 84
#define DIM_PSIA_OFFSET_AUTOFLATTEN  92
#define DIM_PSIA_OFFSET_ACTRACK      96

#define DIM_PSIA_OFFSET_WIDTH        100
#define DIM_PSIA_OFFSET_HEIGHT       104

#define DIM_PSIA_OFFSET_ANGLE        108
#define DIM_PSIA_OFFSET_SINESCAN     116
#define DIM_PSIA_OFFSET_OVERSCAN     120
#define DIM_PSIA_OFFSET_FASTSCANDIR  128
#define DIM_PSIA_OFFSET_SLOWSCANDIR  132
#define DIM_PSIA_OFFSET_XYSWAP       136

#define DIM_PSIA_OFFSET_XSCANSIZE    140
#define DIM_PSIA_OFFSET_YSCANSIZE    148

#define DIM_PSIA_OFFSET_XOFFSET      156
#define DIM_PSIA_OFFSET_YOFFSET      164

#define DIM_PSIA_OFFSET_SCANRATE     172

#define DIM_PSIA_OFFSET_SETPOINT     180
#define DIM_PSIA_OFFSET_SETPOINTUNIT 188
#define DIM_PSIA_OFFSET_TIPBIAS      204
#define DIM_PSIA_OFFSET_SAMPLEBIAS   212
#define DIM_PSIA_OFFSET_DATAGAIN     220
#define DIM_PSIA_OFFSET_ZSCALE       228
#define DIM_PSIA_OFFSET_ZOFFSET      236
#define DIM_PSIA_OFFSET_UNIT         244
#define DIM_PSIA_OFFSET_DATAMIN      260
#define DIM_PSIA_OFFSET_DATAMAX      264
#define DIM_PSIA_OFFSET_DATAAVG      268
#define DIM_PSIA_OFFSET_NCOMPRESSION 272

#define int DIM_INT32
#define double DIM_DOUBLE

// Here is how it's declared in manual
#pragma pack(push, 1)
typedef struct psiaImageHeader
{
    int nImageType; // 0 = 2d mapped image, 1 = line profile image
    wchar_t szSourceNameW[32]; // Topography, ZDetector etc.
    wchar_t szImageModeW[8]; //AFM, NCM etc.
    double dfLPFStrength;//double dfLPFStrength; // LowPass filter strength.
    int bAutoFlatten;// Automatic flatten after imaging.
    int bACTrack;// AC Track
    int nWidth; // Image size: nWidth: Number of Columns
    int nHeight;//Image size: nHeight: Number of Rows.
    double dfAngle; //Angle of Fast direction about positive x-axis.
    int bSineScan; // Sine Scan
    double dfOverScan; // Overscan rate
    int bFastScanDir;//non-zero when scan up, 0 for scan down.
    int bSlowScanDir;//non-zero for forward, 0 for backward.
    int bXYSwap;//Swap fast-slow scanning dirctions.
    double dfXScanSize; //X, Y Scan size in um.
    double dfYScanSize;
    double dfXOffset;// X,Y offset in microns.
    double dfYOffset;
    double dfScanRate;// Scan speed in rows per second.
    double dfSetPoint;// Error signal set point.
    wchar_t szSetPointUnitW[8];
    double dtTipBias;// Tip Bias Voltage
    double dfSampleBias;// Sample Bias Voltage
    // Data=DataGain*( dfScale*nData+dfOffset )
    double dfDataGain;// Data Gain
    double dfZScale;// Scale , now it is always 1.
    double dfZOffset;// Z Offset in step, now it is always 0.

    wchar_t szUnitW[8];
    int nDataMin;
    int nDataMax;
    int nDataAvg;
    int ncompression;
    int ReservedForlmage[8*10-4];
} psiaImageHeader;
#pragma pack(pop)

typedef struct psiaInfoHeader
{
    char   szSourceNameW[32]; // Topography, ZDetector etc.
    char   szImageModeW[8];   //AFM, NCM etc.
    double dfLPFStrength;     //double dfLPFStrength; // LowPass filter strength.
    int    bAutoFlatten;      // Automatic flatten after imaging.
    int    bACTrack;          // AC Track
    int    nWidth;            // Image size: nWidth: Number of Columns
    int    nHeight;           //Image size: nHeight: Number of Rows.
    double dfAngle;           //Angle of Fast direction about positive x-axis.
    int    bSineScan;         // Sine Scan
    double dfOverScan;        // Overscan rate
    int    bFastScanDir;      //non-zero when scan up, 0 for scan down.
    int    bSlowScanDir;      //non-zero for forward, 0 for backward.
    int    bXYSwap;           //Swap fast-slow scanning dirctions.
    double dfXScanSize;       //X, Y Scan size in um.
    double dfYScanSize;
    double dfXOffset;         // X,Y offset in microns.
    double dfYOffset;
    double dfScanRate;        // Scan speed in rows per second.
    double dfSetPoint;        // Error signal set point.
    char   szSetPointUnitW[8];
    double dtTipBias;         // Tip Bias Voltage
    double dfSampleBias;      // Sample Bias Voltage
    double dfDataGain;        // Data Gain
    double dfZScale;          // Scale , now it is always 1.
    double dfZOffset;         // Z Offset in step, now it is always 0.
    char   szUnitW[8];
    int    nDataMin;
    int    nDataMax;
    int    nDataAvg;
    int    ncompression;
} psiaInfoHeader;

#undef int
#undef double

#endif //HXIMPSIAFORMAT_H

/// @}
