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
#ifndef VS_THIN_VESSEL_SEGMENTATION_H
#define VS_THIN_VESSEL_SEGMENTATION_H

#include "VsSegmentationAPI.h"
#include "VsVesselSegmentation.h"

#include <vsvolren/Vs.h>
#include <vsvolren/VsInterface.h>
#include <vsvolren/VsRelay.h>
#include <vsvolren/VsData.h>
#include <vsvolren/VsMemoryData.h>
#include <vsvolren/VsTaskControl.h>
#include <mclib/McProgressInterface.h>
#include "VsSparseData.h"
#include "VsSparseBitData.h"

// VS_RELAY_CLASS VsThinVesselSegmentation VsVesselSegmentationRelay

class VsBlockData : public VsMemoryData {
	public:
		McDArray<bool> blockIndex;
		int numBlocks[3];

		VsBlockData() { }

		void setBlockIndex(int idx, bool val){ blockIndex[idx]=val; }
		bool getBlockIndex(int idx) { 
            return blockIndex[idx]; 
        }
};

class VSSEGMENTATION_API VsThinVesselSegmentation : public VsVesselSegmentation
{

    VS_DECL_INTERFACE        ( VsThinVesselSegmentation )
    VS_DECL_INTERFACE_FACTORY( VsThinVesselSegmentation )
    VS_DECL_INTERFACE_RELAY  ( VsThinVesselSegmentation )

public:

    VsThinVesselSegmentation( VsMeta * inMeta = 0 );
    virtual ~VsThinVesselSegmentation();

    void setDataWindow(int vmin, int vmax); // VS_RELAY
    int dataWindowMin() const; // LOCAL_GET
    int dataWindowMax() const; // LOCAL_GET
    virtual VSRESULT setVolume(VsVolume *vol); // VS_RELAY
    virtual VSRESULT compute(int inNumberOfPoints, const McVec3f* inPoints, VsTaskControl* progress); // VS_SYNC_CALL
    virtual VSRESULT getResult(VsVolume* volume, McBox3i& box, int materialIdx); // VS_SYNC_CALL
    
private:

    void computeLabels(McDArray<float>& radii);
    void computeDF(mculong& maxidx, McDArray<mculong> *fronts);
    int dist(int di,int dj,int dk) {
        int d = (di!=0) + (dj!=0) + (dk!=0) + 2; // 3,4,5 norm
        return d;
    }

    //bool usePrecomputedSegmentation(VsVolume* volume, const McDArray<McVec3f>& dataPoints, McDArray<McVec3f>& centerline);

    // initalize bricked data structur for a smoothed representation of the volume
    McHandle<VsBlockData> initSmoothDataStructur(VsData* srcData);

    // data window min max
    int mVMin;
    int mVMax;
    
    VsSparseData<unsigned int> *mSdf; // the sparse distance field
    VsSparseBitData *mSbd; // the sparse bit data label field

    
};

#endif


/// @}
