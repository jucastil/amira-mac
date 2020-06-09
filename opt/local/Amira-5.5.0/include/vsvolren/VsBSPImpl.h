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

/// @addtogroup vsvolren vsvolren
/// @{
#ifndef VS_BSP_H
#define VS_BSP_H

#include <mclib/McPlane.h>
#include <mclib/McDArray.h>
#include <mclib/McVec4f.h>
#include <mclib/McBox3f.h>

#include "McTable.h"

#include "Vs.h"


class VSVOLREN_API VsBSP
{
public:

     VsBSP( bool inComputeSurfacesOnlyOnFirstPlane = false );
     VsBSP( VsBSP & inBsp );
    ~VsBSP();

    // inCenter : center of the sphere inside which intersections of three planes are accepted. 
    //            If an intersection of three planes is found outside this sphere, it is ignored.
    // inRadius : radius of this sphere
    VSRESULT setIntersectionROI( McVec3f inCenter, float inRadius );

    // merge a plane into the BSP
    // inPlane : plane to split with
    // inROI : If nonzero and inRoiNumPoints is nenzero, this is an array of points that define a point cloud.
    //         Only these parts of the BSP get sut by inPlane that have at least one point of the cloud in its half space.
    // inRoiNumPoints : number of elements in array inROI.
    // inMask : the bits of that mask describe the planes status of being a volume-to-outside plane (see below)
    VSRESULT mergePlane( McPlane const & inPlane, McVec3f * inROI=0, int inRoiNumPoints=0, int inMask=0 );
    
    VSRESULT init();

    VSRESULT traverse( McDArray<char*> & outCells, McVec3f inCam, bool inIsOrtho );

    //  Checks if an Edge is closed, i.e. it has a starting point and an end point.
    //  inEdge    : The Edge that will me tested
    //  outCenter : If nonzero and the edge is closed, this is set to the point in the middle between the Edges start- and end-point.
    //  return    : TRUE if the Edge is closed, else FALSE.
    bool    isClosedEdge   ( char * inEdge,     McVec3f * outCenter = 0 );

    //  Checks if a Surface is closed, i.e. all its Edges are closed and there is at least one edge.
    //  inSurface : The Surface that will me tested
    //  outCenter : If nonzero and the Surface is closed, this is set to the average point of the center points of all Edges.
    //  inOffSurfCenter : if nonzero, offset of a McVec3f field in the surface table that recieves the surfaces center point
    //  return    : TRUE if the Surface is closed, else FALSE.
    bool    isClosedSurface( char * inSurface,  McVec3f * outCenter = 0, int inOffSurfCenter = 0 );

    //  Checks if a Cell is closed, i.e. all its Surfaces are closed and has at least one Surface.
    //  inCell    : The Cell that will me tested
    //  outCenter : If nonzero and the Cell is closed, this is set to the average point of the center points of all Surfaces.
    //  inOffSurfCenter : if nonzero, offset of a McVec3f field in the surface table that recieves the surfaces center point
    //  return    : TRUE if the Cell is closed, else FALSE.
    bool    isClosedCell   ( char * inCell,     McVec3f * outCenter = 0, int inOffSurfCenter = 0 );


public:

    McDataBase  mDB;

    McTable   * mCell;
    McTable   * mSurface;
    McTable   * mEdge;
    McTable   * mPlane;
    McTable   * mVertex;

    // observed pointer to the root split of the BSP
    char      * mRoot;

    int         mNextCellId;

    bool        mComputeSurfacesOnlyOnFirstPlane;
    char      * mFirstPlane;

public: // temporary stuff

    McTable   * mStack;
    McTable   * mStack2;

    McDArray<char*> mCellPlanes;
    McDArray<int>   mCellPlanesSigns;

    ////////////////////////////////////////
    // intersection ROI
    ////////////////////////////////////////

    float       mCurrentPlaneIntersectionROIRadius; // center and ..
    McVec3f     mCurrentPlaneIntersectionROICenter; // .. radius of a sphere that each initial edge (intersection os two planes) 
                                                    // is cut with in a way that each new edge always has an initial start and 
                                                    // endpoint (on the spheres surface);
                                                    // edges that do not hit the sphere are ignored
    McBox3f     mCurrentPlaneIntersectionROIBox;    // a cube enclosing the sphere; intersection points outside this cube are not 
                                                    // stored in order to prevent rounding issues; cut planes that do not hit the 
                                                    // edge inside this cube do either remove the edge completely or are just ignored
                                                    // depending on which side of the cut plane the edge points are

public:

    void    markPlanesWithNumPointsInFront( McVec3f * inROI, int inRoiNumPoints );
    bool    addPlaneToSurface( char ** inPlanes, int * inPlanesSigns, int inPlanesNum, char * inSurface, char * inPlane, int inSign, int & ioNumCutsOutside );
    bool    addPlaneToEdge( char * inSurface, char * inEdge, char * inPlane, int inSign );
    char  * cloneSurface( char * inSurface );

    void    removeDoubleEdges( char * inSurface );

public:

    VSRESULT draw();
    VSRESULT drawCell( char * rCellCurr );
    VSRESULT drawLine( McPlane * p0, McPlane * p1, McVec4f & color );
    VSRESULT drawPlane( McPlane * plane, int sign, McVec4f & colorF, McVec4f & colorB );
};


// Vertex
extern int o_vert_pos;

// Plane
extern int o_plane_plane;
extern int o_plane_num0;
extern int o_plane_mask; // the bits of that mask describe the planes status of being a volume-to-outside plane
                         // bits 0-3 : if bit N is set, this plane separates volume N from the outside
                         // bit  4-7 : if bit N is set, this plane comes from a clip SOP that affects volume N-4


// Edge
extern int o_edge_pos0;
extern int o_edge_pos1;
extern int o_edge_plane;
extern int o_edge_sign;
extern int o_edge_dir;

// Surface
extern int o_surf_plane;
extern int o_surf_sign;
extern int o_surf_edges;

// Cell
extern int o_cell_plane;
extern int o_cell_cell0;
extern int o_cell_cell1;
extern int o_cell_surfs;
extern int o_cell_id;

// Stack
extern int  o_stack_cell;

// Stack
extern int  o_stack2_cell;

#endif // VS_BSP_H


/// @}
