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

/// @addtogroup hxsurface hxsurface
/// @{
#ifndef HX_FRAME_INTERPOLATOR_H
#define HX_FRAME_INTERPOLATOR_H

#include <hxcore/HxData.h>
#include <hxcore/HxCompModule.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortToggleList.h>
#include <hxtime/HxPortTime.h>
#include <hxsurface/HxSurfaceWinDLLApi.h>

typedef bool (*CanInterpolatePtr)(HxData* a, HxData* b, HxData* result);
typedef bool (*InterpolatePtr)(HxData* a, HxData* b, HxData* result, float u);

/// Interpolates between different data sets of the same type.

class HXSURFACE_API HxFrameInterpolator : public HxCompModule {
    
  HX_HEADER(HxFrameInterpolator);

  public:
    /// Constructor.
    HxFrameInterpolator();

    /// Update method (port interface)
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Info port, displays number of inputs.
    HxPortInfo portInfo;

    /// Options port: 0=interpolate grid or data fields
    HxPortToggleList portOptions;

    /// Interpolation parameter 0..n
    HxPortTime portTime;

    static bool canInterpolate(HxData* a, HxData* b, HxData* result=0);

    static HxData* interpolate(HxData* a, HxData* b, float u);

    static int interpolate(HxData* a, HxData* b, HxData* res, float u, int more);

    static void registerType(const McTypeInfo* t, CanInterpolatePtr, InterpolatePtr);

  protected:
    ~HxFrameInterpolator();

    enum { DO_NONE=0, DO_GRID=1, DO_DATA_FIELDS=2 };
    int doOption;
    int iStart, iStop;
    HxData* downStreamResult;

    int hasTimes;
    McDArray<float> times;
    McDArray<HxConnection*> inputs;
    virtual int canCreateData(HxData* data, McString& createCmd);
    static int sourceCheck(void* userData, HxObject* src);
};

#endif

/// @}
