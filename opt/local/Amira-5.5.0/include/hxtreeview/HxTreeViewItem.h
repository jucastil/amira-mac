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

/// @addtogroup hxtreeview hxtreeview
/// @{
#ifndef HX_TREE_VIEW_ITEM
#define HX_TREE_VIEW_ITEM

#include <hxcore/HxObject.h>
#include <hxcore/HxConnection.h>

#include <hxtreeview/hxtreeviewAPI.h>


class HXTREEVIEW_API HxTreeViewItem : public HxObject
{
    HX_ABSTRACT_HEADER(HxTreeViewItem);


public:

    /// The parent directory.
    HxConnection parentDirectory;

    /// Constructor.
    HxTreeViewItem();

    /// Destructor is virtual.
    virtual ~HxTreeViewItem();

    /// To set the connection types allowed.
    virtual void setConnectionTypes() = 0;

    /// Directories are metallicblue.
    virtual McColor getIconColor();

    /// To get the parent directory object.
    HxObject * getParentDirectoryObject() const;

    /// To know if a directory is different.
    bool directoriesAreDifferent(HxTreeViewItem * comparedDirectory);


protected:

    /// The connection is accepted if the parentDirectory connections are not crossed.
    virtual bool acceptConnect(HxConnection * downStreamConnection);
};

#endif

/// @}
