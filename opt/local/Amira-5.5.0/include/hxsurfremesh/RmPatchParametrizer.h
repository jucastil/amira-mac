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

/// @addtogroup hxsurfremesh hxsurfremesh
/// @{
#ifndef _RmPatchParametrizer_h_
#define _RmPatchParametrizer_h_

#include "RmSurfaceChart.h"
#include "hxsurfremeshAPI.h"

#include <hxcore/HxMessage.h>

#include <float.h>

class RmUnitCircle;
class McProgressInterface;

/** Parametrize a patch given by a set of triangles and the surrounding nodes
    in clockwise manner. Choose the base domain and supply boundary lengths. 
    A patch must be homeomorphic to a disk. It may touch itself, if it is cut 
    along the touching line, i.e. boundary nodes may appear multiple times. 
*/

class HXSURFREMESH_API RmPatchParametrizer {

public:

    /// Parameters for patch parametrizer
    class Details;
    
    /// Default constructor.
    /// Note that setting the @c ignoreDiscAssumption argument to true
    /// might not produce correct results, but it will prevent a crash
    /// if the generated patch is not disc-like.
    RmPatchParametrizer(Surface* surf, bool ignoreDiscAssumption=false);
    
    /// Set new triangles and boundary
    void setPatch(McDArray<int>* tList, McDArray<McDArray<int> >* bndrs);

    /// parametrize patch
    bool compute(RmSurfaceChart* chart,
                 const Details& details,
                 RmSurfaceChart::ChartType type=RmSurfaceChart::MAIN_CHART,
                 RmUnitCircle* shape=0,
                 McProgressInterface* progress=0);
            
    /// Destructor
    ~RmPatchParametrizer() {}

    /** Determine the amount of console output.  A value of 0 will
        suppress the most amount of output. */
    void setVerbosity( const int verbosity );

protected:

    /// surface the patch belongs to
    Surface* surface;

    /// If this flag is true, the assumption that the created patch
    /// will be disc-like will be ignored.
    bool m_ignoreDiscAssumption;
    
    /// triangle indices of the patch
    McDArray<int>* triangleList;
    
    /// point indices of the boundary of the patch
    McDArray<McDArray<int> >* boundaries;
    
    /// number of points on boundary
    int nbndpnts;

    ///
    enum { NO_INIT=0, INIT_FAILED, INIT_OK };
    
    /// Keeps track of initialization
    unsigned char initFlag;
    
    /// keeps track of inner points
    McBitfield isInnerPoint;

    /// keeps track of inner points
    McDArray<int> innerPoints;
    
    /// keeps track of border edges
    McBitfield isBorderEdge;
    
    /// keeps track of boundary points
    McBitfield isOnBoundary;
    
    /// keeps track of patch triangles
    McBitfield considerTriangles;

    /// initialization of patch
    void init();

    /// Finds all triangles inside a patch, along a given border.
    int getTrianglesAlongBorder(McDArray<Surface::Triangle>& paramTriangles,
                                McDArray<int>& originalTriangles,
                                McBitfield& visitedTriangles);

    ///
    bool computePointsFixedBoundary(RmSurfaceChart* chart,
                                    RmUnitCircle* shape,
                                    const Details& details,
                                    McProgressInterface* progress);
        
    /// Floater, CAGD, 1997
    int setShapePreservingWeights(int pp, McDArray<double>& w, McDArray<McVec2f>& p, 
                                  const McSmallArray<int,6>& neighbours);

    /// Simple barycentric weights
    int setBarycentricWeights(int pp, McDArray<double>& w);
    
    /// Floater, CAGD, 2003
    int setMeanValueWeights(int pp, McDArray<double>& w);
        
    ///
    int getParamIdx(int pp, int k);

    /// Output lineset consisting of multiple lines
    static void outputLineset(
        Surface* surface, 
        const McDArray<McDArray<int> >& nodes,
        const char* label="SurfacePath");

    /** Find triangles along given border and from a set of given triangles
        around v1 with given orientation (orient==1 is clockwise) */
    static int getBorderNodeNeighbourhood(
        Surface* surface,
        const McBitfield& isBorderEdge,
        const McBitfield& considerTriangles, 
        int orient, int node, int prevNode,
        McDArray<int>& nodes, McDArray<int>& tris);

private:
    // This variable determines the amount of console output.
    int m_verbosity;

    int findEdge(int p1, int p2);

    // Stores the machine's actual precision.
    double m_machineEps;
};

//--------------------------------------------------------------------

/** Class for passing parameters about parametrization solver */
class RmPatchParametrizer::Details
{
public:
    /// parametrization algorithms
    enum { SHAPE_PRESERVING=0, 
           BARYCENTRIC, 
           MEAN_VALUE,
           NUM_PARAM_ALGORITHMS 
    };
    /// Default constructor
    Details()
    {
        algorithm = SHAPE_PRESERVING;
        maxIter = 5000;
        tol = 1.e-6;
        relaxFact = 0.8;
    }
    /// Constructor with values
    Details(int a, int b, double c, double d)
    {
        algorithm = a;
        maxIter = b;
        tol = c;
        relaxFact = d;
    }
    /// computation of linear system
    int algorithm;
    /// maximum number of iterations for linear system solver
    int maxIter;
    /// tolerance for solving linear system
    double tol;
    /// relaxation factor for linear system solver
    double relaxFact;
    ///
    void print()
    {
        theMsg->printf("algorithm = %d", algorithm);
        theMsg->printf("maxIter = %d", maxIter);
        theMsg->printf("tol = %g", tol);
        theMsg->printf("relaxFact = %g", relaxFact);
    }
};

#endif

/// @}
