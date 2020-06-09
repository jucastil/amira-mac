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
#ifndef VS_SPATIALGRAPH_H
#define VS_SPATIALGRAPH_H

#include "vsvolren/Vs.h"
#include "vsvolren/VsNode.h"
#include "vsvolren/VsSlice.h"

#include "NxGLShader.h"

#include "hxspatialgraph/SpatialGraphSelection.h"

#include <mclib/McColor.h>
#include <mclib/McString.h>

class HxSpatialGraph;
class EdgeVertexAttribute;

class VsSpatialGraphRen : public VsNode
{
public:
    VsSpatialGraphRen();
    ~VsSpatialGraphRen();
    
    void setSlice(VsSlice *slice) { mSlice = slice;}
    void setSpatialGraph(HxSpatialGraph* graph);

    void setSegmentColorAttribute(const char* attributeName);
    void setNodeColorAttribute(const char* attributeName);
    
    void setHighlightedElements(const SpatialGraphSelection& highElm) { mHighlightedElements = highElm; }
    //void setVisibleElements(const SpatialGraphSelection &visElm);

    void setNodeSize(float size);
    void setRayCastingScaleFactor(float size);
    void setLineWidth(float size);

    /// overloaded functions from VsNode
    virtual VsRenderResult render();
    virtual VSRESULT cleanup();
    //virtual VSRESULT observedObjectTouched( VsObject * inObject, unsigned int inMask );
    bool canRaycast();

protected:

    void drawNodes();
    void drawLines();
    void drawPoints();

    void drawHighlightedPoints();
    
    void raycastLines(float* slice, float* sliceHeight);
    void raycastNodes(float* slice, float* sliceHeight);
    void raycastHighlightedPoints(float *slice, float *sliceHeight);

    bool initGL();

    McColor getLineColor(int line) const;
    McColor getNodeColor(int nodeNum) const;
    McColor getAttributedSegmentColor(int segmentNum) const;
    McColor getAttributedNodeColor(int nodNum) const;

    HxSpatialGraph *mGraph;
    VsSlice *mSlice;
    SpatialGraphSelection mHighlightedElements;

    float mNodeSize;
    float mLineWidth;
    float mRayCastingScaleFactor;

    static const McColor sDefaultSegmentColor;
    static const McColor sDefaultNodeColor;
    static const McColor sDefaultPointColor;
    static const McColor sDefaultHighlightColor;

    bool mUseRaycasting;
    bool mGLInitialized;

    NxGLShader mLineShader;
    NxGLShader mSphereShader;

private:
    EdgeVertexAttribute* mSegmentColorAttribute;
    EdgeVertexAttribute* mNodeColorAttribute;
};


#endif

/// @}
