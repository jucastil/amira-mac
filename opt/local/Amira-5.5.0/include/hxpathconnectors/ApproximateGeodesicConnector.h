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
#ifndef APPROXIMATE_GEODESIC_CONNECTOR_2
#define APPROXIMATE_GEODESIC_CONNECTOR_2

#include <hxpathconnectors/GeodesicConnector.h>
#include <hxpathconnectors/hxpathconnectorsAPI.h>
#include <mclib/McVec2f.h>


/** Computes an approximation for a shortest geodesic on a mesh.  The
    error is not bound, so on big surfaces the error will be greater
    than on small surfaces.  For an approximate geodesic you should
    use the TriangleStripConnector.  This connector is used for the
    P2PGeodesicConnector.
*/
class HXPATHCONNECTORS_API ApproximateGeodesicConnector : public GeodesicConnector
{

    MC_HEADER(ApproximateGeodesicConnector);

  public:
    /// Constructor.
    ApproximateGeodesicConnector(void);

    /// Destructor.
    virtual ~ApproximateGeodesicConnector(void);

 private:
    /// tries to create a new EdgeWindow that approxiamtes interval1 and interval2
    void mergeIntervals(McHandle<EdgeWindow> interval1, McHandle<EdgeWindow> interval2, EdgeWindow* merged);

    /// debug
    int countIntervalMerge;

    /// returns the EdgeWindow that lies left(interval->b0 is greater
    /// than the left interval) of interval on edge if there is any
    EdgeWindow* getLeftInterval(McHandle<EdgeWindow> interval);

    /// returns the EdgeWindow that lies right of interval on edge if there is any
    EdgeWindow* getRightInterval(McHandle<EdgeWindow> interval);

    /// propagates a window on the surface
    virtual void propagate(EdgeWindow* window, McFHeap<EdgeWindow>& heap);

    /// inserts window on edge (into windowsPerEdge)
    virtual bool insertOnEdge(McHandle<EdgeWindow> window);

    /// computes all values necessary for merging two EdgeWindows
    class WindowMerger
    {
        ///
        float A,B,C,D0,D1,alpha,beta,b0_,b1_;

        ///
        float lower_bound,upper_bound, tolerance;

        ///
        McVec2f s0,s1,b0,b1;

        ///
        bool isLeftOfLine(const McVec2f& straightLineStart,
                                               const McVec2f& straightLineEnd,
                                               const McVec2f& point);

        ///
        bool isRightOfLine(const McVec2f& straightLineStart,
                                               const McVec2f& straightLineEnd,
                                               const McVec2f& point);

        ///
        void initialiseConicCurve(EdgeWindow* window1,EdgeWindow* window2);

      public:
        ///
        WindowMerger(EdgeWindow* window1,EdgeWindow* window2, float tolerance=1.e-4);

        ///
        bool computeY(float x, float* y);

        ///
        float computeSigma(float x);

        ///
        float getLowerBound();

        ///
        float getUpperBound();

        ///
        float getB0();

        ///
        float getB1();

        ///
        float getA();

        ///
        float getB();


        ///
        float getC();

        ///
        McVec2f getS0();

        ///
        McVec2f getS1();
    };

    bool tryOtherX(float x, float* sigma_, float* sx_, float* sy_, WindowMerger merger);
};
#endif

/// @}
