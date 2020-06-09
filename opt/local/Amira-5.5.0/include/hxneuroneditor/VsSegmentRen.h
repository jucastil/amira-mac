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

/// @addtogroup hxneuroneditor hxneuroneditor
/// @{
#ifndef VS_SEGMENT_H
#define VS_SEGMENT_H

#include "VsSpatialGraphRen.h"

/**
  *
  * The VsSegmentRen handles and renders one segment.
  * The segment will be chosen based on the current selection
  * and rendered as a straight line whereas the length depends
  * on the distances between the given points.
  * Note: The padding offset must be set.
  *
 **/

class VsSegmentRen : public VsSpatialGraphRen
{
public:
    VsSegmentRen();
    ~VsSegmentRen();

    void setPaddingOffset(const float paddingOffset);

    /// Return the current visible edge index.
    int getVisibleSegment();

    /// Verify if current segment is up to date and compute
    /// the rendering points.
    /// The method returns true if the segment has changed.
    bool updateVisibleSegment();

    virtual VsRenderResult render();
    void raycastLine(float* slice, float* sliceHeight);
    void raycastNodes(float *slice, float *sliceHeight);
    void raycastHighlightedPoints(float *slice, float *sliceHeight);
    void raycastPoints(float *slice, float *sliceHeight);

private:
    struct SpatialGraphEdge
    {
        int edgeId;
        McVec3f edgeSourceCoord;
        McVec3f edgeTargetCoord;
    };

    void drawLine();
    void drawNodes();
    void drawPoints();
    void drawHighlightedPoints();

    void renderNodes();
    void renderPoints();
    void renderHighlightedPoints();

    /// Get the current segment.
    /// Note: If more then one edge are selected the current segment is invalid.
    SpatialGraphEdge getCurrentSegment();

    /// Verify if the current segment has changed and needs an update.
    bool segmentNeedsUpdate();

    /// Verify if a edge with the index \a edgeId or parts of it
    /// are in the current SpatialGraph selection.
    bool isEdgeInSelection(const int edgeId);

    SpatialGraphEdge mCurrentEdge;

    /// Computed points for rendering
    McDArray<McVec3f> mSegmentPoints;

    bool mDrawPoints;

    /// The padding offset defines the space between the border
    /// of the slice and the segment centered within it.
    float mPaddingOffset;
};


#endif

/// @}
