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
#ifndef LIB_HX_TREEVIEW_H
#define LIB_HX_TREEVIEW_H

#include <hxtreeview/hxtreeviewAPI.h>

//-----------------------------------------------//
//--------------- Enum Types used ---------------//
//-----------------------------------------------//

/// The different columns of the tree view.
typedef enum {ITEM_NAME_COLUMN = 0, PORT_VALUE_COLUMN = 1, COLORMAP_COLUMN = 2, TRANSFORM_COLUMN = 3, PATCH_COLUMN = 4} ColumnIndex;

/// The number of columns.
const int NUM_COLUMNS = 5;

/// The height (in pixels) of an item.
const int ITEM_HEIGHT = 22;


//-----------------------------------------------//
//----- Functions called in others packages -----//
//-----------------------------------------------//

extern "C"
{
    /// Creates the HxTreeViewGUI instance.
    extern int HXTREEVIEW_API createTreeViewGUIInstance();

    /// Disables the update of the tree when objects are created, renamed or deleted.
    extern int HXTREEVIEW_API disableAutoUpdate();

    /// Updates the checkbox of the current object according to its visibility.
    extern int HXTREEVIEW_API updateObjectVisibility(void * obj);

    /// Updates the checkboxes of all objects in the tree.
    extern int HXTREEVIEW_API updateAllObjectsVisibilities();

    /// Accepts a dataDirectory connection.
    extern int HXTREEVIEW_API acceptDataDirConnection(void * dataPtr, void * dSCPtr);

    /// To display the shortcut of an item.
    extern int HXTREEVIEW_API displayShortcutItem(void * resDataObj, void * masterModuleObj);

    /// To update the colormaps icons.
    extern int HXTREEVIEW_API updateColormapsIcons(void * colormapObj);

    /// To show the port value displayed in the tree view.
    extern int HXTREEVIEW_API showPortValueInTV(void * p);

    /// To show the port value displayed in the tree view.
    extern int HXTREEVIEW_API hidePortValueInTV(void * p);

    /// Editors icons management.
    extern int HXTREEVIEW_API showEditorBtn(void * edit, void * obj);
    extern int HXTREEVIEW_API hideEditorBtn(void * obj);

    /// notify TreeView of RemoteSynchronizer status changes.
    extern void HXTREEVIEW_API checkRemoteModeInTreeView();

    /**
     * To inhibit the creation of HxDataDirectory objects (used by TimeSeries).
     */
    extern void HXTREEVIEW_API disableDataDirCreation();

    /**
     * To allow the creation of HxDataDirectory objects (used by TimeSeries).
     */
    extern void HXTREEVIEW_API enableDataDirCreation();

    /** 
     * To be able to change a tree view accessible port.
     */
    extern void HXTREEVIEW_API treeViewAccessiblePortChanged(void* oldAccessiblePort, void* newAccessiblePort);

}

#endif

/// @}
