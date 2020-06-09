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
#ifndef HXSPATIALGRAPHINTERFACE_H
#define HXSPATIALGRAPHINTERFACE_H


#include "hxspatialgraphAPI.h"
#include "HxSpatialGraph.h"
#include <mclib/McVec3f.h>
#include <mclib/McInterface.h>

class HXSPATIALGRAPH_API HxSpatialGraphInterface : public McInterface {
    MC_INTERFACE(HxSpatialGraphInterface);
 public:
    /// vertex
    int getNumVertices() const {
        return doGetNumVertices();
    }
    McVec3f getVertexCoords(const int vertexNum) const {
        return doGetVertexCoords(vertexNum);
    }

    int   getNumVertexAttributes() const {
        return doGetNumVertexAttributes();
    }
    const EdgeVertexAttribute* getVertexAttribute(int iAttribute) const {
        return doGetVertexAttribute(iAttribute);
    }
    const EdgeVertexAttribute* findVertexAttribute(const char* attributeName) const {
        return doFindVertexAttribute(attributeName);
    }

    // edge
    int getNumEdges() const {
        return doGetNumEdges();
    }
    int getNumEdgePoints(const int edgeNum) const {
        return doGetNumEdgePoints(edgeNum);
    }
    int getEdgeSource(const int edgeNum) const {
        return doGetEdgeSource(edgeNum);
    }
    int getEdgeTarget(const int edgeNum) const {
        return doGetEdgeTarget(edgeNum);
    }

    int getNumEdgeAttributes() const {
        return doGetNumEdgeAttributes();
    }
    const EdgeVertexAttribute* getEdgeAttribute(int iAttribute) const {
        return doGetEdgeAttribute(iAttribute);
    }
    const EdgeVertexAttribute* findEdgeAttribute(const char* attributeName) const {
        return doFindEdgeAttribute(attributeName);
    }

    // edgePoints
    const McVec3f* getEdgePoints(const int edgeNum, int& numPoints) const {
        return doGetEdgePoints(edgeNum, numPoints);
    }
    McDArray<McVec3f> getEdgePoints(const int edgeNum) const {
        return doGetEdgePoints(edgeNum);
    }
    McVec3f getEdgePoint(const int edgeNum, const int pointNum) const {
        return doGetEdgePoint(edgeNum, pointNum);
    }
    int   getNumEdgePointAttributes() const {
        return doGetNumEdgePointAttributes();
    }
    const PointAttribute* getEdgePointAttribute(int iAttribute) const {
        return doGetEdgePointAttribute(iAttribute);
    }
    const PointAttribute* findEdgePointAttribute(const char* attributeName) const {
        return doFindEdgePointAttribute(attributeName);
    }

    /// labels
    bool hasLabel(const GraphAttribute *attrib) const {
        return doHasLabel(attrib);
    }
    int  getNumLabels(const GraphAttribute *attrib ) const {
        return doGetNumLabels(attrib);
    }
    bool getLabelName(const GraphAttribute *attrib, int value, McString &name) const {
        return doGetLabelName(attrib, value, name);
    }
    bool getLabelColor(const GraphAttribute *attrib, int value, SbColor &color) const {
        return doGetLabelColor(attrib, value, color);
    }
    int getMaxLabelId(const GraphAttribute* attrib) const {
        return doGetMaxLabelId(attrib);
    }
    int getLabelId(const GraphAttribute* attrib, const McString& labelName) const {
        return doGetLabelId(attrib, labelName);
    };

    ///
    const IncidenceList& getIncidentEdges(const int vertexNum) const {
        return doGetIncidentEdges(vertexNum);
    }

    bool isConsistent() const {
        return doIsConsistent();
    }

    SoTransform* getTransform() const {
        return doGetTransform();
    }
    void getTransform(SbMatrix& matrix) const {
        return doGetTransform(matrix);
    }

    SpatialGraphSelection getConnectedComponent(const int vertexNum) const {
        return doGetConnectedComponent(vertexNum);
    }

    void getBoundingBox(float bbox[6]) const {
        return doGetBoundingBox(bbox);
    }

 private:
    /// vertex
    virtual int doGetNumVertices() const = 0;
    virtual McVec3f doGetVertexCoords(const int vertexNum) const = 0;

    virtual int   doGetNumVertexAttributes() const = 0;
    virtual const EdgeVertexAttribute* doGetVertexAttribute(int iAttribute) const = 0;
    virtual const EdgeVertexAttribute* doFindVertexAttribute(const char* attributeName) const = 0;

    // edge
    virtual int doGetNumEdges() const = 0;
    virtual int doGetNumEdgePoints(const int edgeNum) const = 0;
    virtual int doGetEdgeSource(const int edgeNum) const = 0;
    virtual int doGetEdgeTarget(const int edgeNum) const = 0;

    virtual int doGetNumEdgeAttributes() const = 0;
    virtual const EdgeVertexAttribute* doGetEdgeAttribute(int iAttribute) const = 0;
    virtual const EdgeVertexAttribute* doFindEdgeAttribute(const char* attributeName) const = 0;

    // edgePoints
    virtual const McVec3f* doGetEdgePoints(const int edgeNum, int& numPoints) const = 0;
    virtual McDArray<McVec3f> doGetEdgePoints(const int edgeNum) const = 0;
    virtual McVec3f doGetEdgePoint(const int edgeNum, const int pointNum) const = 0;
    virtual int   doGetNumEdgePointAttributes() const = 0;
    virtual const PointAttribute* doGetEdgePointAttribute(int iAttribute) const = 0;
    virtual const PointAttribute* doFindEdgePointAttribute(const char* attributeName) const = 0;

    /// labels
    virtual bool doHasLabel(const GraphAttribute *attrib) const = 0;
    virtual int  doGetNumLabels(const GraphAttribute *attrib ) const = 0;
    virtual bool doGetLabelName(const GraphAttribute *attrib, int value, McString &name) const = 0;
    virtual bool doGetLabelColor(const GraphAttribute *attrib, int value, SbColor &color) const = 0;
    virtual int doGetMaxLabelId(const GraphAttribute* attrib) const = 0;
    virtual int doGetLabelId(const GraphAttribute* attrib, const McString& labelName) const = 0;

    ///
    virtual const IncidenceList& doGetIncidentEdges(const int vertexNum) const = 0;

    virtual bool doIsConsistent() const = 0;

    virtual SoTransform* doGetTransform() const = 0;
    virtual void doGetTransform(SbMatrix& matrix) const = 0;

    virtual SpatialGraphSelection doGetConnectedComponent(const int vertexNum) const = 0;

    virtual void doGetBoundingBox(float bbox[6]) const = 0;
};

// Implementation
class HxSpatialGraphInterfaceImpl : public HxSpatialGraphInterface {
    MC_ABSTRACT_HEADER(HxSpatialGraphInterfaceImpl);

 public:
    HxSpatialGraphInterfaceImpl(HxSpatialGraph *graph)
        : HxSpatialGraphInterface(graph->getOwner(), McInterfaceOwner::STATIC_IFACE),
          mGraph(graph) {}

 private:
    HxSpatialGraph *mGraph;

    virtual int doGetNumVertices() const {
        return mGraph->getNumVertices();
    }

    virtual McVec3f doGetVertexCoords(const int vertexNum) const {
        return mGraph->getVertexCoords(vertexNum);
    }

    virtual int doGetNumEdges() const {
        return mGraph->getNumEdges();
    }

    virtual int doGetNumEdgePoints(const int edgeNum) const {
        return mGraph->getNumEdgePoints(edgeNum);
    }

    virtual McVec3f doGetEdgePoint(const int edgeNum, const int pointNum) const {
        return mGraph->getEdgePoint(edgeNum, pointNum);
    }

    virtual int doGetEdgeSource(const int edgeNum) const {
        return mGraph->getEdgeSource(edgeNum);
    }

    virtual int doGetEdgeTarget(const int edgeNum) const {
        return mGraph->getEdgeTarget(edgeNum);
    }

    virtual McDArray<McVec3f> doGetEdgePoints(const int edgeNum) const {
        return mGraph->getEdgePoints(edgeNum);
    }

    virtual const McVec3f* doGetEdgePoints(const int edgeNum, int& numPoints) const {
        return mGraph->getEdgePoints(edgeNum, numPoints);
    }

    virtual const IncidenceList& doGetIncidentEdges(const int vertexNum) const {
        return mGraph->getIncidentEdges(vertexNum);
    }

    virtual bool doIsConsistent() const {
        return mGraph->isConsistent();
    }

    virtual SoTransform* doGetTransform() const {
        return mGraph->getTransform();
    }

    virtual void doGetTransform(SbMatrix& matrix) const {
        return mGraph->getTransform(matrix);
    }

    virtual SpatialGraphSelection doGetConnectedComponent(const int vertexNum) const {
        return mGraph->getConnectedComponent(vertexNum);
    }

    virtual void doGetBoundingBox(float bbox[6]) const {
        mGraph->getBoundingBox(bbox);
    }

    virtual int doGetNumVertexAttributes() const {
        return mGraph->numAttributes(HxSpatialGraph::VERTEX);
    }

    virtual int doGetNumEdgeAttributes() const {
        return mGraph->numAttributes(HxSpatialGraph::EDGE);
    }

    virtual int doGetNumEdgePointAttributes() const {
        return mGraph->numAttributes(HxSpatialGraph::POINT);
    }

    virtual const EdgeVertexAttribute* doGetVertexAttribute(int iAttribute) const {
        return dynamic_cast<const EdgeVertexAttribute*> (mGraph->attribute(HxSpatialGraph::VERTEX, iAttribute));
    }

    virtual const EdgeVertexAttribute* doGetEdgeAttribute(int iAttribute) const {
        return dynamic_cast<const EdgeVertexAttribute*> (mGraph->attribute(HxSpatialGraph::EDGE, iAttribute));
    }

    virtual const PointAttribute* doGetEdgePointAttribute(int iAttribute) const {
        return dynamic_cast<const PointAttribute*> (mGraph->attribute(HxSpatialGraph::POINT, iAttribute));
    }

    virtual const EdgeVertexAttribute* doFindVertexAttribute(const char* attributeName) const {
        return mGraph->findVertexAttribute(attributeName);
    }

    virtual const EdgeVertexAttribute* doFindEdgeAttribute(const char* attributeName) const {
        return mGraph->findEdgeAttribute(attributeName);
    }

    virtual const PointAttribute* doFindEdgePointAttribute(const char* attributeName) const {
        return mGraph->findEdgePointAttribute(attributeName);
    }

    virtual bool doHasLabel(const GraphAttribute *attrib) const {
        return mGraph->hasLabel(attrib);
    }

    virtual int  doGetNumLabels(const GraphAttribute *attrib ) const {
        return mGraph->getNumLabels(attrib);
    }

    virtual bool doGetLabelName(const GraphAttribute *attrib, int value, McString &name) const {
        return mGraph->getLabelName(attrib, value, name);
    }

    virtual bool doGetLabelColor(const GraphAttribute *attrib, int value, SbColor &color) const {
        return mGraph->getLabelColor(attrib, value, color);
    }

    virtual int doGetMaxLabelId(const GraphAttribute* attrib) const {
        return mGraph->getMaxLabelId(attrib);
    }

    virtual int doGetLabelId(const GraphAttribute* attrib, const McString& labelName) const {
        return mGraph->getLabelId(attrib, labelName);
    }
};

#endif

/// @}
