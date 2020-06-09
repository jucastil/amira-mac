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
#ifndef DISTANCE_MAP_CONNECTOR_H
#define DISTANCE_MAP_CONNECTOR_H

#include <hxpathconnectors/hxpathconnectorsAPI.h>

#include <hxsurfacepath/PathConnector.h>
#include <hxsurfacepath/SurfaceNode.h>
#include <hxsurfacepath/SurfacePathSet.h>
#include <mclib/McBitfield.h>

class Surface;
class HxSurfacePathSet;

class HXPATHCONNECTORS_API DistanceMapConnector : public PathConnector
{

    MC_HEADER(DistanceMapConnector);

public:
    /// Default constructor
    DistanceMapConnector() : mSurface(0), mAllowedPoints(0), mdepthRegion(5) {}//TODO set mAllowedPoints

    /// Initialize computation
    virtual void init(Surface* surface, McProgressInterface* progress = 0);

    /// Compute intermediate nodes between startNode and endNode
    virtual bool computeConnection(SurfaceNode* startNode,
                                   SurfaceNode* endNode,
                                   McDArray<McHandle<SurfaceNode> >& intermediate,
                                   McProgressInterface* progress = 0);

    /// Set pointer to allowed surface vertices
    void setAllowedPoints(McBitfield* allowed)
    {
        mAllowedPoints = allowed;
    }

    /// Set pointer to seeds, for example points on vertex path
    void setSeeds(const McDArray<int>& seeds)
    {
        mSeeds = seeds;
    }

    /// set nodes of path as seeds, if they are vertex-nodes
    void setSeeds(const SurfacePathSet* vertexSurfPath)
    {
        mFlagSearchForPathAsSeeds = false;
        setSeedsForDistanceMap(vertexSurfPath);
    }

    /// sets the deap for searching for points around seeds to compute invDistanceField
    void setDepthRegion(int depth)
    {
        mdepthRegion = depth;
    }

private:

    /// Pointer to surface
    Surface* mSurface;

    /// Holds edge weights (default edge length)
    McDArray<float> mEdgeWeights;

    /// holds inverse distance edges
    McDArray<float> mInvDistanceWeights;

    McDArray<int> mSeeds;

    bool mFlagSearchForPathAsSeeds;
    McBitfield* mAllowedPoints;

    /// depth for points around a seed, only for theis points the inverseDistance is computetd
    int mdepthRegion;

    /// Calculate path from @c startNode to @c endNode via
    /// @c intermediate nodes.
    float calculatePathLength(SurfaceNode* startNode,
                              SurfaceNode* endNode,
                              McDArray<int> intermediate);

    float* computeWeightsWithDistanceMap(McBitfield* allowed, float* weights, SurfaceNode* notConsiderEndNode, McDArray<float>& invDistancePoints);

    /// inverse distance is computeted for points/edges of surf around the seeds
    /// how many points are condsidered are defined by mdepthRegion
    void computeInverseDistanceMap(const McDArray<int>& seeds,
                                   McDArray<float>& invDistance,
                                   McDArray<float>& invDistancePoints,
                                   McBitfield* allowed,
                                   float* weights,
                                   SurfaceNode* notConsiderEndNode);

    void computeRegionPointsOfSeed(const McDArray<int>& seeds, McDArray< McDArray<int> >& pointsPerSeed);

    HxSurfacePathSet* getSurfacePath();

    void setSeedsForDistanceMap(const SurfacePathSet* vertexSurfPath)
    {
        if ( !vertexSurfPath )
            return;

        int numPathNodes =  vertexSurfPath->nodes.size();
        mSeeds.resize(numPathNodes);
        int count = 0;

        for ( int i=0; i<numPathNodes; i++ )
        {
            int vertex =  vertexSurfPath->nodes[i]->vertex();
            if ( vertex > -1 )
            {
                mSeeds[count] = vertex;
                count++;
            }
        }
        mSeeds.resize(count);
    }

    /// Compute edge weight field and return the pointer to it. 
    float* getWeightField();
};
#endif

/// @}
