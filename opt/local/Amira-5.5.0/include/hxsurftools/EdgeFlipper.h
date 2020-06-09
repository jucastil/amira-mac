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

/// @addtogroup hxsurftools hxsurftools
/// @{
#ifndef EDGE_FLIPPER_H
#define EDGE_FLIPPER_H

#include <stdio.h>
#include <mclib/McBitfield.h>
#include <mclib/McMemArray.h>
#include <hxsurface/Surface.h>
#include <hxsurftools/HxSurfToolsWinDLLApi.h>

/// Edge flipper class.

class HXSURFTOOLS_API EdgeFlipper {

  public:
    /// Constructor.
    EdgeFlipper(Surface* surface=0);

    /// Computes edges per triangle.
    void initialize(Surface* surface=0);

    /// Destructor.
    ~EdgeFlipper();

    /** Flip all triangles with R/r bigger than given threshold.
        Returns number of edges which actually have been flipped. */
    int flipBadOnes(float radiusRatio, 
		    McBitfield* bitfield=0);

    /** Flip all triangles with R/r bigger than given threshold
	and crease angle smaller than given value.
        Returns number of edges which actually have been flipped. */
    int flipBadOnes(float radiusRatio, 
		    float creaseAngleRadian,
		    McBitfield* bitfield);

    /** Flip triangles considering connectivity. Try to create as
	much 6-triangle-stars as possible.
        Returns number of edges which actually have been flipped. */
    int flipConnectivity(float radiusRatio, 
			 float creaseAngleRadian=M_PI,
			 McBitfield* bitfield=0);

    /// Flip edge with given index (returns 1 on sucess, 0 otherwise).
    int flipEdge(int edge, float radiusRatio=1000.);

    /** Flip edge with given index, update trianglesPerPoint
        if requested. 
	Returns 1 on success, 0 otherwise. */
    int flipEdge(int edge, float radiusRatio,
		 int updateTrianglesPerPoint);

    /// Flip longest edge of given Triangle
    int flipLongestEdgeOfTriangle(int triangle);

  protected:

    Surface* surface;

    int nEdges;
    float triangleRadiusRatio(int t, float* edgeLengths);
    float triangleRadiusRatio(int p1, int p2, int p3);
    int intersectionTest(int p1, int p2, int p3, int p4);
    int triangleEdgeIntersection(int p1, int p2, int p3, McDArray<int>& );
    int checkConnectivity(int e);
    int coplanarTriangles(int p00, int p01, int p02, int p10, int p11, int p12);

  public:
    McMemArray<int[3]> edgesPerTriangle; 
};

#endif

/// @}
