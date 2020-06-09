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

/// @addtogroup hxpathconnectors hxpathconnectors
/// @{
#ifndef DEBUG_GEODESIC_CONNECTOR_H
#define DEBUG_GEODESIC_CONNECTOR_H

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortToggleList.h>
#include <hxsurfacepath/HxSurfacePathSet.h>

class DebugGeodesicConnector : public HxCompModule
{
    HX_HEADER(DebugGeodesicConnector);

public:

    //
    enum {TRIANGLE_MIDDLE=0,VERTICES,INTERVAL_ENDS};

    //
    enum {LINE_SET=0,SURFACE_PATH_SET};

    //
    enum {GEODESIC=0,APPROXIMATE};

    //
    DebugGeodesicConnector();

    //
    ~DebugGeodesicConnector(void);

    //
    virtual void doIt();

    //
    virtual void update();

private:
    // determines whether the user wants to see paths from the middle of the
    // triangles, from the vertices...
    HxPortRadioBox* portFromWhere;

    // which edge to start with, default 0
    HxPortText* portFromEdge;

    // where to end, default surfacePath->surface->edges.size()
    HxPortText* portToEdge;

    // LineSet or SurfaePath
    HxPortRadioBox* portKindOf;

    // Approximate or true Geodesic?
    HxPortRadioBox* portConnectorType;

    // LineSet or SurfaePath
    HxPortButtonList* portDoIt;

    // LineSet or SurfaePath
    HxPortToggleList* portPrintWindowStatistics;

    // LineSet or SurfaePath
    HxPortToggleList* portPrintDetailedStatistics;

    // LineSet or SurfaePath
    HxPortToggleList* portRemoveEpsilonWindows;

    // LineSet or SurfaePath
    HxPortToggleList* portCompareMapWithArray;

    //
    HxSurfacePathSet* pathSet;
};
#endif

/// @}
