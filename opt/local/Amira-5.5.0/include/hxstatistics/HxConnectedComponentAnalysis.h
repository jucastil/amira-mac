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

/// @addtogroup hxstatistics hxstatistics
/// @{
#ifndef HX_CONNECTED_COMPONENT_ANALYSIS_H
#define HX_CONNECTED_COMPONENT_ANALYSIS_H

#include <mclib/McVec3i.h>

#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxCompModule.h>

#include <hxfield/HxUniformLabelField3.h>
#include <hxfield/HxUniformColorField3.h>
#include <hxfield/HxLattice3.h>
#include <hxcolor/HxPortColormap.h>
#include <hxstatistics/HxStatisticsWinDLLApi.h>

/// Module for counting connected regions in a 3D image data set.
class HXSTATISTICS_API HxConnectedComponentAnalysis : public HxCompModule
{
  HX_HEADER(HxConnectedComponentAnalysis);

  public:
    struct Component {
        McString material;
        int label;
        McVec3i seed;
        McVec3f center;
        McVec3f bboxCenter;
        mculong numVoxels;
        float volume;
    };

    /// Default constructor.
    HxConnectedComponentAnalysis();

    /// Destructor.
    ~HxConnectedComponentAnalysis();

    /// Compute method.
    void compute();

    /// Update method.
    virtual void update();

    /// Displays number of regions found.
    HxPortInfo portInfo;

    /// Use thresholding or consider every voxel value as own set.
    HxPortRadioBox portHandleInputAs;

    /// Specifies intensity range of regions.
    HxPortIntTextN portIntensity;

    /// Specifies flood fill type
    HxPortMultiMenu portFillType;

    /// Minimal and maximal size of regions.
    HxPortIntTextN portSize;

    /// Output: 0=region field, 1=spreadsheet
    HxPortToggleList portOptions;

    /// Type of the output image:
    HxPortMultiMenu portOutputType;
    
    /// Don't relable exterior (value = 0) regions
    HxPortToggleList portPreserveExterior;

    /// Starts computation.
    HxPortDoIt portDoIt;
    
    /// Mode: Apply threshold / take input as labels
    HxUniformScalarField3* image;

    mculong minSize;
    mculong maxSize;
    float avgSize;
    McDArray<Component> components;

    template<class T, class S>
    void doStatistics(HxUniformScalarField3* image, HxUniformScalarField3* result, bool useThreshold);
    void createResult();
    void updateInfo();
    HxUniformScalarField3* updateResult(McPrimType outputType);

  protected:
    void createMaterials(HxParamBundle *materials, int numMaterials, bool mix);
    virtual int canCreateData(HxData* data, McString& createCmd);
    template <class S> 
    void doStatisticsWrapper();

    int exteriorRegions;
};

#endif

/// @}
