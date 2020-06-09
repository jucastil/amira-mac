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

/// @addtogroup vssegmentation vssegmentation
/// @{
#ifndef _VS_LABEL_STATS_H
#define _VS_LABEL_STATS_H

#include "VsSegmentationAPI.h"

#include <mclib/McVec3f.h>
#include <mclib/McBox3f.h>

#include <vsvolren/McVec3l.h>
#include <vsvolren/Vs.h>

class VsMsg;

////////////////////////////////////////////////////////////////////////////////
class VSSEGMENTATION_API VsLabelStats
{

public:
    VsLabelStats();
    VsLabelStats(const VsLabelStats &other);
    VsLabelStats& operator=(const VsLabelStats &other);
    ~VsLabelStats();

    enum StatType
    {
        STAT_LABEL = 1,
        STAT_CONTOUR_2D,
        STAT_CONTOUR_3D
   };


public:
    StatType    mType;

    /// number of voxels
    mcint64     mNumVoxels;

    /// labels bound minimum corner
    McVec3l     mBoundMin;

    /// labels bound maximum corner
    McVec3l     mBoundMax;

    /// labels bound dimension = mBoundMax-mBoundMin+[1,1,1]
    McVec3l     mBoundDim;

    /// labels bound size in mm
    McVec3f     mBoundSize;

    /// per axis number of voxel surfaces to the volumes bound
    McVec3l     mSurfNumOutside;

    /// voxel size
    McVec3f     mVoxelSize; // assumed to be in mm

    /// surface if only a single slice was labeled
    double      mSurf2D;

    /// surface orientation if only a single slice was labeled. 
    /// 0 for x, 1, for y, 2 for z. Not displayed, but used internally
    /// to determine which slice to annotate. 
    int         mSurf2DOrientation;

    // perimeter of mSurf2D area
    double      mPerimeter2D;

    /// surface of the 3d shape
    double      mSurf3D;

    /// volume in mm^3
    double      mVolume;

    /// mean intensity
    double      mIntensityMean;

    // Code review Detlev 27-Aug-2006: sum also has to be double, because
    // all values are in scaled (physical) units!
    /// sum intensity
    // mcint64     mIntensitySum;
    double      mIntensitySum;

    /// min intensity
    double      mIntensityMin;

    /// max intensity
    double      mIntensityMax;

    /// standard deviation = sqrt( 1/(N-1) * MSE )
    double      mStdDeviation;

    /// histogram, 256 entries for byte data - 65536 entries for short data
    mcuint64  * mHistogram;

    void init();
};

VSSEGMENTATION_API VsMsg& operator<<(VsMsg& msg, const VsLabelStats& str);
VSSEGMENTATION_API VsMsg& operator>>(VsMsg& msg,       VsLabelStats& str);

#endif

/// @}
