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
#ifndef HXCOMPUTEDISTANCETOPOINT_H
#define HXCOMPUTEDISTANCETOPOINT_H

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortGeneric.h>

#include <mclib/McVec3f.h>

#include <Inventor/SbLinear.h>

#include <hxspatialgraph/hxspatialgraphAPI.h>

class HxSpatialGraph;

/** This module computes the distance of an abitrary given spatialgraph edge point to each 
    edge point on the input spatialgraph. 
    The result will be stored in a point attribute of type float within the result spatialgraph, 
    which is a copy of the input spatialgraph.
  */
class HXSPATIALGRAPH_API HxComputeDistanceToPoint : public HxCompModule {

    HX_HEADER(HxComputeDistanceToPoint);

public:
    HxComputeDistanceToPoint();

    ~HxComputeDistanceToPoint();

    /// shows reference point information 
    HxPortInfo        portInfo;

    // enter some coordinates and find the closest spatialgraph point
    HxPortGeneric     portSetCoordinates;

    // button to start/stop picking 
    HxPortButtonList  portPickCoordinates;

    // start distance computation
    HxPortDoIt        portAction;

    virtual void compute();

    virtual void update();

    ///
    void savePorts(FILE* fp);

protected:

    virtual int canCreateData(HxData* data, McString& createCmd);
    virtual int parse( Tcl_Interp * t, int argc, char ** argv );

private:

    /** Returns the closest spatialgraph edge point for 
        a given point.

        @param data Input spatialgraph
        @param pos Specified point in world coordinates
        @param minEdge Edge index of the closest edge point
        @param minEdgePoint Edge point index of the closest edge point
    */
    float findClosestPoint(const HxSpatialGraph* data, const McVec3f& pos, int &minEdge, int &minEdgePoint);

    // picking stuff
    bool pickCallbackRegistered;
    static void pickCallbackCB(void *userData, SoEventCallback* node);
    void pickCallback(SoEventCallback* node);
    
    void addCallback(); // if called the callback is active (needs selected this)

    /// spatialgraph segment (edge) index 
    int mRootEdge;
    /// spatialgraph segment edge point index
    int mRootEdgePoint;
};

#endif

/// @}
