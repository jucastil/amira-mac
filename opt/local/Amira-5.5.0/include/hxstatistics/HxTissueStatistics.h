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
#ifndef HX_TISSUE_STATISTICS
#define HX_TISSUE_STATISTICS

#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxCompModule.h>

#include <hxfield/HxColorField3.h>
#include <hxfield/HxRegScalarField3.h>
#include <mclib/McData3D.h>
#include <mclib/McDArray.h>
#include <mclib/McFloodFill3D.h>
#include <hxcolor/HxPortColormap.h>
#include <hxstatistics/HxStatisticsWinDLLApi.h>
#include <mclib/McConnectedComponents.h>
#include <mclib/McVec3d.h>

/// Computes statistical quantities like volume, center, etc.
class HXSTATISTICS_API HxTissueStatistics : public HxCompModule
{
  HX_HEADER(HxTissueStatistics);

  public:
    /// Default constructor.
    HxTissueStatistics();

    /// Connection to associated scalar field.
    HxConnection portField;

    /// Label field describing VOI
    HxConnection portLabels;

    /// Select type of statistics:
    HxPortMultiMenu portSelect;
    enum {
        MODE_MATERIALS=0,
        MODE_REGIONS=1,
        MODE_PER_SLICE=2,
	    MODE_AREA_PER_SLICE=3,
        MODE_PER_VOI=4,
        MODE_LESION_COUNT=5,
        MODE_POLAR_MOMENT_OF_INERTIA=6
    };

    /// Per slice mode: ignore regions smaller than this.
    HxPortIntTextN portMinSize;

    /// Area moment of inertia center position
    HxPortToggleList portInertiaOptions;
    /// Area moment of inertia center position
    HxPortFloatTextN portInertiaCenter;

    /// Action port.
    HxPortDoIt portDoIt;

    /// Update method.
    void update();

    /// Compute method.
    void compute();

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

  protected:
    virtual ~HxTissueStatistics();

    struct Data {
        mculong count;		
        McVec3d center;
        double volume;
        double min;
        double max;
        double sum;
        double squareSum;
    } data[256];

    McDArray<Data> dataReg;
   
    void doStatistics();
    void doRegionsStatistics();
    void createResult();
    void createRegionsResult();
    void doPerSliceStatistics();
    void doPerSliceStatistics2();
	void doPolarMomentOfInertia();
    void doPerVOIStatistics();
    void doLesionCount();

    HxObject *fieldSource();

    virtual int canCreateData(HxData* data, McString& createCmd);

    int regions;
};

#endif

/// @}
