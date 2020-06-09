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
#ifndef PATHEDIT_ENTANGLE_PATH_SET2_H
#define PATHEDIT_ENTANGLE_PATH_SET2_H

#include <hxsurfacepathedit/hxsurfacepatheditAPI.h>
#include <hxsurfacepathedit/SinglePathOperation.h>
#include <mclib/McDArray.h>
#include <mclib/McHandle.h>
#include <mclib/McHandable.h>

/** This class implements path entangling.  This means, if two or more
    paths in a path set have common points, these common points will
    be replaced by a single point, thereby entangling the paths.  The
    inverse operation is implemented in PathEditUntangle.  */
class HXSURFACEPATHEDIT_API PathEditEntangle : public SinglePathOperation
{
    MC_ABSTRACT_HEADER(PathEditEntangle);

public:

    /// Constructor.
    PathEditEntangle(SurfacePathSet* pS, SelectionInfo* sel, float tolerance=1.e-3);

    /// Constructor.
    PathEditEntangle(SurfacePathSet* pS, SelectionInfo* sel, const McDArray<int>&selectedP, float tolerance=1.e-3);

    /// Destructor.
    virtual ~PathEditEntangle(void) {}

private:

    /// Tolerance distance within which two points are considered equal.
    float mTol;

    /// Selected paths that should be entangled.
    McDArray<int> selectedPaths;

    /** Update path set according to the operation that has been
        carried out.  Returns true. */
    virtual bool updatePathset();
};

#endif

/// @}
