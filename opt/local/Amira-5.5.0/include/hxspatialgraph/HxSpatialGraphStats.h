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

/// @addtogroup hxspatialgraph hxspatialgraph
/// @{
#ifndef HX_SPATIAL_GRAPH_STATS_H
#define HX_SPATIAL_GRAPH_STATS_H

#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxCompModule.h>


#include "hxspatialgraphAPI.h"

class HxSpatialGraph;

class HXSPATIALGRAPH_API HxSpatialGraphStats : public HxCompModule
{
    MC_HEADER(HxSpatialGraphStats);

private:

    struct SegmentMetrics {
        float length;
        float meanThickness;
        float volume;
    };

    struct SegmentGroupMetrics {
        SegmentGroupMetrics()
            : meanLength(0.f),
              meanThickness(0.f),
              totalLength(0.f),
              totalVolume(0.f),
              numSegments(0) {}

        float meanLength;
        float meanThickness;
        float totalLength;
        float totalVolume;
        int numSegments;
    };

public:

// Construction / Deconstruction
public:
    HxSpatialGraphStats();
    virtual ~HxSpatialGraphStats();

    /// Constrain statistics computation to an existing SpatialGraph highlight selection   
    HxConnection portSelection;

    HxPortDoIt portAction;
    /// Our main computation function.
    virtual void compute();
    /// Updates the UI.
    virtual void update();

protected:
    virtual int canCreateData(HxData* data, McString& createCmd);
    virtual int parse( Tcl_Interp * t, int argc, char ** argv );

private:
    void calcSegmentMetrics(const HxSpatialGraph* graph, int iEdge, SegmentMetrics& segMetrics);

};

#endif // end HX_SPATIAL_GRAPH_STATS_H

/// @}
