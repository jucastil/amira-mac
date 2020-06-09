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
#ifndef VS_BSP2_H
#define VS_BSP2_H

#include <mclib/McPlane.h>
#include <mclib/McDArray.h>
#include <mclib/McVec4f.h>
#include <mclib/McBox3f.h>

#include "McTable.h"

#include "Vs.h"


class VSVOLREN_API VsBSP2
{
public:

     VsBSP2();
    ~VsBSP2();

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


public:

    McDataBase  mDB;

    McTable   * mPlane;
    McTable   * mSide;
    McTable   * mCorner;
    McTable   * mCell;

    // observed pointer to the root split of the BSP
    char      * mRoot;

    int         mNextCellId;


public: // temporary stuff

    McTable   * mStack;

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
};


// Plane
extern int o2_plane_plane;
extern int o2_plane_num0;
extern int o2_plane_mask; // the bits of that mask describe the planes status of being a volume-to-outside plane
                          // bits 0-3 : if bit N is set, this plane separates volume N from the outside
                          // bit  4-7 : if bit N is set, this plane comes from a clip SOP that affects volume N-4
// Side
extern int o2_side_sign;
extern int o2_side_plane;

// Corner
extern int o2_corner_pos;
extern int o2_corner_sides;

// Cell
extern int o2_cell_plane;
extern int o2_cell_cell0;
extern int o2_cell_cell1;
extern int o2_cell_corners;
extern int o2_cell_id;

// Stack
extern int o2_stack_cell;


#endif


/// @}
