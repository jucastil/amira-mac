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

/// @addtogroup hximproc hximproc
/// @{
#ifndef IM_FILTER_NON_LOCAL_MEANS_H
#define IM_FILTER_NON_LOCAL_MEANS_H

#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortInfo.h>

#include "ImFilter3D.h"

class McTypedData2D;
class McTypedData3D;
class HxEditor;
class HxImageVisionEditor;
class ImFilter3D;
class McVec3i;
struct cudaDeviceProp;

/** This filter implements the windowed non-local means algorithm for
    denoising scalar volume data.  The original non-local means
    algorithm did not use a search window, but compared each voxel
    with each other voxel.  This leads to very long running times
    which are unfeasible.  Hence, in general a windowed version of the
    non-local means algorithm, as implemented in this filter, is used.

    In order to determine the new value for the current voxel, the
    algorithm compares the neighborhoods of all voxels in a given
    search window with the neighborhood of the current voxel.  The
    similarity between the neighborhoods determines the weight with
    which the value of a voxel in the search window will influence the
    new value of the current voxel.  The final weights are determined
    by applying a Gauss kernel to the similarity values.

    The non-local means algorithm works most effectively if the noise
    present in the data set is white noise.  This is the assumption
    behind the algorithm.  If this can be assumed, the non-local means
    algorithm will naturally preserve most features present in the
    image, even small and thin ones.
*/
class HXIMPROC_API ImFilterNonLocalMeans : public ImFilter3D
{
    MC_HEADER(ImFilterNonLocalMeans);

public:

    /// Define the search window size
    HxPortIntTextN      portSearchWindow;

    /// Define the local neighborhod size
    HxPortIntTextN      portNeighborhood;

    /// Similarity parameter
    HxPortFloatTextN    portSimilarityValue;

    /// Adaptive Lambda
    HxPortRadioBox      portAdaptive;

    /// Device - GPU or CPU?
    HxPortRadioBox      portDevice;

    /// Choose graphics card for CUDA algorithm
    HxPortMultiMenu     portCUDADevice;

    /// Info-Label
    HxPortInfo          portInfo;

    /// Should the field partition size be automatically determined.
    HxPortToggleList    portOptions;

    /// Field partition size for GPU nlm computation.
    HxPortFloatTextN    portPartitionSize;

    /// Display info about available GPU memory.
    HxPortInfo          portGPUMemory;

    /// Display info about currently used block size.
    HxPortInfo          portMaxBlockSize;

    /// Constructor
    ImFilterNonLocalMeans(HxEditor * editor=0);
    
    /// Destructor
    ~ImFilterNonLocalMeans();

    /// applies the filter (see bases classes)
    void apply3D(McTypedData3D* source,
                 McTypedData3D* dest=0,
                 McProgressInterface* progress=0);

    void update();

    /// Sets the filters parameters if any
    void setParameters(const ImFilterParameters *param);

    /// Updates the filter parameters class
    void updateParameters(ImFilterParameters *param);
    
    static ImFilter3D* createFilter(HxEditor* e);

private:

    // Stores the valid cuda device ids.
    McDArray<int> m_cudaDeviceIds;

    McDArray<bool> m_cudaDeviceIsExecTimeoutEnabled;

    HxImageVisionEditor * m_hxImageVisionEditor;

    // Keep track whether the partition size needs an update.
    bool m_needsUpdateOfPartitionSize;

    void setNeedsUpdateOfPartitionSizeFlag();

    void displayGPUMemoryInfo();

    bool shouldDeterminePartitionSize();

    void determinePartitionSize(const McTypedData3D* const source,
                                const bool is2D);

    void increasePartitionSize(const float time,
                               const bool  is2D);

    float computeTimeNeededForSingleBlock(const McDArray<float> & inData,
                                          const McVec3i         & dims,
                                          const int               searchwindow,
                                          const int               neighbourhoodsize,
                                          const float             lambda,
                                          const bool              adaptive,
                                          const bool              is2D ) const;

    void setDefaultValueForPartitionSize(const int cudaDeviceId);

    void setCudaDeviceVariables();

    void nonLocalMeans_CPU(const McTypedData3D * source,
                           McTypedData3D       * dest,
                           const bool            is2D) const;

    void nonLocalMeans_GPU(const McTypedData3D * source,
                           McTypedData3D       * dest,
                           const bool            is2D) const;

    McVec3i getMaxBlockDims(const cudaDeviceProp & device_properties,
                            const bool             is2D) const;

    void getSettings(int   & searchSize,
                     int   & neighSize,
                     float & lambda,
                     bool  & isAdaptive) const;
};

#endif

/// @}
