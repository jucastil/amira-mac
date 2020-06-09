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

/// @addtogroup hxsurface hxsurface
/// @{
#ifndef HX_VIEW_BASE_GROUPING_H
#define HX_VIEW_BASE_GROUPING_H

#include <hxcore/HxModule.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxSelectInterface.h>
#include <hxsurface/HxSurfaceWinDLLApi.h>

/** */
class HXSURFACE_API HxViewBaseGrouping : public HxModule {

  MC_HEADER(HxViewBaseGrouping);

  public:
    /// Constructor
    HxViewBaseGrouping();

    /// Menu with all the groups.
    HxPortMultiMenu portGroups;

    /// Action port: 0=Show, 1=Add, 2=Remove, 3=Nop
    HxPortRadioBox portAction;
    enum { ACTION_SHOW=0, ACTION_ADD=1, ACTION_REMOVE=2, ACTION_NOP };
    
    /// Text field which allows to change the name of a group.
    HxPortText portRename;

    /// Edit port: 0=New group, 1=Delete group
    HxPortButtonList portEdit;
    enum { EDIT_NEW=0, EDIT_DELETE=1, EDIT_REPLACE=2 };

    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Tcl-command interface.
    virtual int parse(Tcl_Interp* t, int argc, char** argv);

  protected:
    virtual ~HxViewBaseGrouping();
    virtual void savePorts(FILE* fp);

    void initGroups();
    void newGroupName(McString& name);
    void newGroup();
    void deleteGroup();
    void showGroup();
    void addGroup();
    void removeGroup();
    void highlightGroup();
    void renameGroup();
    void replaceGroup();
    void storeGroups();

    struct Group {
        McString name;
        McDArray<McBitfield> bits;
    };

    McDArray<Group> groups;
    McDArray<HxConnection*> connectionPorts;
};

#endif

/// @}
