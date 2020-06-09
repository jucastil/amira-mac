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

/// @addtogroup hxsegeditor hxsegeditor
/// @{
#ifndef ISCISSOR_H
#define ISCISSOR_H

#include <mclib/McList.h>
#include <Inventor/SbLinear.h>

#ifdef _WIN32
    #include <crtdbg.h>
#endif

/// This class implements the intelligent scissors algorithm.

class IScissors {

  public:
    enum CostType {
        COSTS_AS_IS=0,
        COSTS_GRADIENT=1,
        COSTS_STANDARD=2,
        COSTS_INVERSE=3
    };

    /// Constructor.
    IScissors();

    /// Destructor.
    ~IScissors();

    /// Allocs memory and computes edge costs from node cost differences.
    void init(int width, int height, unsigned char* image, CostType costType);

    /// Start auto tracing.
    int start(int seedX, int seedY);

    /// Restart auto tracing (seed should be part of previous path).
    int restart(int seedX, int seedY);

    /// Indicates that dynamic path integration is completed.
    void stop() { minAccum = -1; }

    /// This method returns 1 between start() and stop().
    int isActive() const { return (minAccum != -1); }

    /// Method returns 1 if path from (x,y) to current seed can be computed.
    int isValid(int x, int y);

    /** This methods proceeds one step towards the current seed point. If
        the current point (x,y) is identical to the seed point or if there
        exists no path from (x,y) to the seed point 0 is returned and (x,y)
        remains unchanged. Otherwise, (x,y) are updated and 1 is returned.
    */
    int next(int& x, int& y);

    /// Returns the seed point set by last call to start().
    void getSeed(int& x, int& y) const { x=seed%width; y=seed/width; }

    /** Increase hit count for path from x,y to current seed point. The
        method also returns the coordinates of the last point for which
        markPath() was called as well as the coordinates of the point
        where the old path (from the last point to the seed point) and
        the current path (from x,y to the seed point) join. Initially
        the last point is equal to the seed point.
    */
    int markPath(int x, int y, int& lastX, int& lastY, int& joinX, int& joinY);

    /// Get nearest point with at least @c nHits hits
    int getPoint(int nHits, int& x, int& y) const;

    int getCost(const int& ip, const int& iq, const int& orientation);

    struct Node : public McLink {
        int next, accum;
        void clear() { next=-1; accum=0; }
        void markAsProcessed() { accum=-1; }
        int isProcessed() const { return accum<0; }
        int isNotProcessed() const { return accum>=0; }
    };

  protected:
    /// Dimensions of the image
    int width, height;

    CostType costType;
    unsigned char* image;
    unsigned char* gradMag;
    signed char* gradX;
    signed char* gradY;
    signed char* laplacian;

    /// Node array (one per pixel)
    Node* nodes;

    /// This is the length of the cyclic array
    enum { pqLen = 512 };

    /// Index of minimal element in cyclic array
    int minAccum;

    /// This is used as a cyclic array of node lists.
    McList<Node> pq[pqLen];

    /// Contains hit counts for current path
    unsigned char* mPath;

    int last;
    int seed;

    /// Get topmost pixel from priority queue
    Node* nextMin();

    /// Insert pixel @c m into priority queue
    void insert(int m, int n, int accum);

    /// Update priority for pixel @c m
    void decrease(int m, int n, int accum);

    /// Update neighbouring pixel
    inline void update(const int&, const int&, const int&, const int&);

    /// Compute shortest paths (Dijkstra's algorithm)
    int reallyCompute(int n);
};

#endif

/// @}
