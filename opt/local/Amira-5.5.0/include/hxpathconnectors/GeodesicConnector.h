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
#ifndef GEODESIC_CONNECTOR2_H
#define GEODESIC_CONNECTOR2_H

#include <hxpathconnectors/EdgeWindow.h>
#include <hxpathconnectors/hxpathconnectorsAPI.h>

#include <hxsurfacepath/PathConnector.h>
#include <hxsurface/Surface.h>

#include <mclib/McHandle.h>
#include <mclib/McTypedObject.h>
#include <map>

class McProgressInterface;

/** Class that computes shortest geodesics between two points on
    surfaces.  This class implements the algorithm proposed in "Fast
    approximate and exact geodesics on meshes", Hoppe et al., SIGGRAPH
    2005. */
class HXPATHCONNECTORS_API GeodesicConnector : public PathConnector
{

    MC_HEADER(GeodesicConnector);

public:

    /// Default constructor.
    GeodesicConnector();

    /// Destructor.
    ~GeodesicConnector();

    /// Initialize computation.
    virtual void init(Surface* surface, McProgressInterface* progress = 0);

    /** Compute intermediate nodes between startNode and endNode.
        Returns true if algorithm terminates correctly, else false. */
    virtual bool computeConnection(SurfaceNode* startNode,
                                   SurfaceNode* endNode,
                                   McDArray<McHandle<SurfaceNode> >& intermediate,
                                   McProgressInterface* progress = 0);
    /// Compute distance map based on edge windows.
    virtual void computeDistanceMap(SurfaceNode* startNode,SurfaceNode* endNode);

    /// Return distancemap.
    McDArray<McDArray<McHandle<EdgeWindow> > >  getDistanceMap() { return windowsPerEdge; }

    /// Return pointer to edgeLength data.
    float* getEdgeLength() { return edgeLengths.dataPtr(); }

    /// Return pointer to surface.
    Surface* getSurface() { return surface; }

    /// Is vertex a saddleVertex or not?
    McDArray<bool> saddleVertices;

    /// For debugging.
    void setUseArray(bool useArray) { this->use_array = useArray; }

protected:

    /// Checks which of the windows has the smaller b0-value.
    static int compareOnEdge(const McHandle<EdgeWindow>& win1,
                             const McHandle<EdgeWindow>& win2);

    /// Edge lenghts of surface.
    McDArray<float> edgeLengths;

    /// Pointer to surface.
    Surface* surface;

    /// Bool for statistics.
    bool use_array;

    /// Windows per edge: edgeWindows[i][j] is j-th window on edge i.
    McDArray< McDArray<McHandle<EdgeWindow> > > windowsPerEdge;

    /** Same as windowsPerEdge, but in a binary tree. The algorithm
        uses either windowsPerEdge or edgeTrees, depending on whether
        use_array is set to true or false. */
    McDArray<std::map< float,McHandle<EdgeWindow> > >  edgeTrees;

    /// Initialize heap.
    bool initHeap(SurfaceNode* startNode, McFHeap<EdgeWindow>& heap);

    /// Propagate window, and update heap.
    virtual void propagate(EdgeWindow* window, McFHeap<EdgeWindow>& heap);

    /// Takes the newly computed windows and tries to put them on the
    /// edge, they belong to.
    void insertNewWindows(EdgeWindow windows[],
                          McFHeap<EdgeWindow>& heap);

    /// Debug.
    int numEdgeWindows();

public:
    /// Debug function.
    void printWindowStatistics();

    /// Debug function.
    static int showWindows(McDArray<EdgeWindow*> windows, Surface* surface, int which=0, char* label=0);

    /// Debug function.
    void showFromTrianglesToSource(SurfaceNode* startNode ,int from=-1,int to=-1);

    /// Debug function.
    void showFromWindowsToSource(SurfaceNode* startNode, int startEdge=-1,int endEdge=-1);

    /// Debug function.
    void showFromVerticesToSource(SurfaceNode* startNode, int from, int to);

    /// Debug function.
    int removeEpsilonWindows(void);

    /// Debug function.
    int removeInvalidWindows(void);

    /// Debug function.
    void printInconsistencies(void);

    /// Debug function.
    void printGaps(void);

protected:

    /// inserts a new window in either windowsPeredge, or an edgeTree
    virtual bool insertOnEdge(McHandle<EdgeWindow> window);

    /// removes a new window from either windowsPerEdge, or an edgeTree
    int removeFromEdge(McHandle<EdgeWindow> window);

    /// gets all windows on an edge that overlap window
    int getAllIntersecting(McDArray<McHandle<EdgeWindow> >& result, EdgeWindow* window);

    /// if use_array is not set, this method transforms the binary trees into arrays after computing the
    /// distance map
    void prepareWindowsPerEdge(void);

    static float cTime;

    /// creates a new window without initialising it
    McHandle<EdgeWindow> getNewWindow(GeodesicConnector* gc);

    McDArray<EdgeWindow*> newWindows;
    long numWindows;

    /// creates a new window and initialises it with the values in win
    McHandle<EdgeWindow> getNewWindow(EdgeWindow* win);

    /// initializes all windows with default values
    void initWinArray(EdgeWindow* windows, int length);

    /// checks whether all adjacent distancefuntions to this vertes have the vertex as pseudo-source
    bool isVertexSink(long vertex);

    /// stack that saves unused old windows for recycling
    McDArray<McHandle<EdgeWindow> > windowStack;

    /// stackpointer
    int topOfStack;
    int stackFull;
    int stackEmpty;
    int newCounter;
    int notNewCounter;

    /// debug
    void checkForSinkVertices(void);

    /// debug
    bool identifyPossibleSinkVertices(McDArray<int>& pSV);
};

#endif

/// @}
