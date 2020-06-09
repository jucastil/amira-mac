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

/// @addtogroup hxsurfacepathedit hxsurfacepathedit
/// @{
#ifndef _PATH_EDIT_CLICK_INFO_H_
#define _PATH_EDIT_CLICK_INFO_H_

#include <mclib/McVec3f.h>

class PathEditClickInfo
{
public:

    /// Type of geometry for mouse clicks.
    enum CLICKGEOM {NONE=-1, SURFACE, PATH, CONTROLPOINT };

    /// 3d-coordinate of the mouseclick.
    McVec3f* point;

    /// The triangle of the surface that was clicked.
    int clickedFace;

    /// Control point that was clicked.
    int clickedCP;

    /// Path that was clicked.
    int clickedPath;

    /// If a path was clicked and is primaryGeom, index is the part of
    /// the path that was clicked.
    int indexInPath;

    /** The first geometry, that was clicked.  If a CP was clicked, we
        can determine a corresponding path and face-ID, but the
        important geometry is the CP value corresponding to the
        CLICKGEOM enum. */
    int primaryGeometry;
    
    /// The mousebutton that was pressed.
    int pressedMouseButton;
    
    /// Constructor.
    PathEditClickInfo()
    {
        point=new McVec3f();
        clickedFace=-1;
        clickedCP=-1;
        clickedPath=-1;
        indexInPath=-1;
        primaryGeometry=-1;
        pressedMouseButton=-1;
    }
};

#endif

/// @}
