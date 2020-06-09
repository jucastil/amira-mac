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
#ifndef VS_CALCIUM_SCORING_H
#define VS_CALCIUM_SCORING_H

#include "VsSegmentationAPI.h"

#include <vsvolren/Vs.h>
#include <vsvolren/VsInterface.h>
#include <vsvolren/VsRelay.h>
#include <vsvolren/VsTaskControl.h>

#include <mclib/McPrimType.h>
#include <mclib/McProgressInterface.h>

class McVec3f;
class VsVolume;

// VS_RELAY_CLASS VsCalciumScoring VsRelay

class VSSEGMENTATION_API VsAgatstonScore
{
public:
    int     mSliceIdx;      // slice index for the lesion the agatston score has been determined
    mcint64 mSeedpoint;     // actually this is the point of highest intensity (if several exist, the first one)
                            // if no such point is found, contains -1. mScores is empty then. 
    double  mLesionArea;    // 2d area of the lesion in mm*mm
    double  mAgatstonScore; // agatston score, dimensionless
};


VsMsg& operator<<(VsMsg& msg,          const VsAgatstonScore   & );
VsMsg& operator>>(VsMsg& msg,                VsAgatstonScore   & );
VsMsg& operator<<(VsMsg& msg, const McDArray<VsAgatstonScore>  & );
VsMsg& operator>>(VsMsg& msg,       McDArray<VsAgatstonScore>  & );

class VSSEGMENTATION_API VsCalciumScoring : public VsInterface
{
    VS_DECL_INTERFACE        ( VsCalciumScoring )
    VS_DECL_INTERFACE_FACTORY( VsCalciumScoring )
    VS_DECL_INTERFACE_RELAY  ( VsCalciumScoring )

public:
    VsCalciumScoring( VsMeta * inMeta = 0 );
    ~VsCalciumScoring();

    /** Sets calcium threshold. Values above the threshold are
        selected.
        The threshold is specified in Hounsfield units. It will
        be automatically converted into the data set's raw unit
        using the DICOM rescale slope and intercept values. On
        default, a threshold value of 130 is used. */
    void setThreshold(float value); // VS_RELAY

    /// Returns calcium threshold.
    float threshold() const; // LOCAL_GET

    /// Sets the slice thickness. In case it is larger than the slice
    /// distance, slices overlap and we correct the results by the
    /// factor thickness / distance
    void setSliceThickness(float value); // VS_RELAY

    /// Returns the slice thickness
    float sliceThickness() const; // LOCAL_GET

    /** Sets the minimum number of voxels that must be set in order
        for a lesion to be identified. The default is 3 voxels. */
    void setMinPixels(mcint64 value); // VS_RELAY

    /// Returns minimum number of voxels threshold
    mcint64 minPixels() const; // LOCAL_GET

    void setSeedPoints(
        const McDArray<McVec3f>    & inSeedPoints
    ); // VS_RELAY

    void computeSeedPoints(
        const McDArray<McVec3f>    & in3DContour,
        VsVolume                   * inVolume
    ); // VS_RELAY

    VSRESULT setLesion(
        VsVolume                   * inVolume,
        int                          inLabelIdx,
        bool                         in3D,
        McDArray<VsAgatstonScore>  & outAgatstonScores // results that must be added to lesion list on the client
    ); // VS_SYNC_CALL

    VSRESULT unsetLesion(
        VsVolume                   * inVolume,
        const McDArray<int>        & inLabelIdxs,
        bool                         in3D,
        McDArray<VsAgatstonScore>  & outAgatstonScores // results that must be removed from lesion list on the client
    ); // VS_SYNC_CALL

    VSRESULT unsetAll(
        VsVolume            * inVolume,
        const McDArray<int> & inLabelIdxs
    ); // VS_SYNC_CALL

protected:
    static void spanCB(void* userData, int x0, int x1, int y, unsigned char*);

private:

    class VsCalciumScoringPrivate * d;
};

#endif // VS_CALCIUM_SCORING_H

/// @}
