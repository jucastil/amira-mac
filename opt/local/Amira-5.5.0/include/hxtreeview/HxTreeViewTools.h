#ifndef HX_TREE_VIEW_TOOLS_H
#define HX_TREE_VIEW_TOOLS_H

//                                                                             |
// Copyright Notice                                                            |
//      THIS SOURCE IS PROPRIETARY TO VISUALIZATION SCIENCES GROUP S.A.S.,     |
//      COPYRIGHT (C) BY VISUALIZATION SCIENCES GROUP S.A.S.                   |
//      ALL RIGHTS RESERVED                                                    |
//                                                                             |

#include <hxtreeview/hxtreeviewAPI.h>
#include <mclib/McDArray.h>

class HxObject;
class HxData;
class HxColormap;
class HxPortColormap;
class HxEditor;
class QTreeWidgetItem;
class QxTreeViewItem;

/**
 * This class implements tools provided for tree view classes.
 * Copyright (C) by VISUALIZATION SCIENCES GROUP S.A.S.
 */

class HXTREEVIEW_API HxTreeViewTools
{

public:

    /** 
    * To get the parent data of a data.
    */
    static HxObject* theParentData(const HxData* data);

    /**
    * To get the data directory of a data.
    */
    static HxObject* theDataDirectory(const HxData* data);

    /** 
    * To get the first connected object of another.
    */
    static HxObject* theFirstConnectedObject(const HxObject* object);

    /** 
    * To get the Master module of an object.
    */
    static HxObject* theMasterModule(const HxObject* object);

    /** 
    * To get the connected colormap of an object.
    */
    static HxColormap* theConnectedColormap(const HxObject* object);

    /**
    * To get the port colormap of an object.
    */
    static HxPortColormap* thePortColormap(const HxObject* object);

    /** 
    * To get the attached editor of an object.
    */
    static HxEditor* theAttachedEditor(HxObject* object);

    /** 
    * To disconnect all the connections of an object.
    */
    static void disconnectAllConnections(HxObject* object);

    /** 
    * To know if the tree view is displayed.
    */
    static bool treeViewIsDisplayed(); 
};

#endif //HX_TREE_VIEW_TOOLS_H

