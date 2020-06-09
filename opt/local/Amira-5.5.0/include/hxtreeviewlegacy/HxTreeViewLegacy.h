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

/// @addtogroup hxtreeviewlegacy hxtreeviewlegacy
/// @{
#ifndef HXTREEVIEWLEGACY
#define HXTREEVIEWLEGACY

#include <hxcore/HxObject.h>

/** Base class for dummy tree view (@see hxtreeview)
    directory objects, which are needed for script 
    compatibility if the tree view has been disabled.

    Once the tree view has been completly dismanteled 
    this class and all its derived classes can be 
    savely removed.
*/
class HxTreeViewDummyBase : public HxObject
{
  public:

    HxTreeViewDummyBase()
    {
        // Dummy directory objects need to be persistent
        // and thus shouldn't be removeable from the object pool,
        noRemoveAll = 1;
        noRemove    = 1;
        // nor be ever visible
        invisible   = 1;
        // nor be saveable in order to avoid pollution of future network scripts
        noSave      = 1;
    }

    // Empty parse method aeting up all tcl commands.
    int parse(Tcl_Interp* interpreter, int argc, char **argv)
    {
        return TCL_OK;
    }
};

class HxDataDirectory : public HxTreeViewDummyBase
{
    HX_HEADER(HxDataDirectory);
};

class HxDirectory : public HxTreeViewDummyBase
{
    HX_HEADER(HxDirectory);
};

class HxDirectoryData : public HxTreeViewDummyBase
{
    HX_HEADER(HxDirectoryData);
};

class HxDirectoryColormaps : public HxTreeViewDummyBase
{
    HX_HEADER(HxDirectoryColormaps);
};

#endif

/// @}
