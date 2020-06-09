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

/// @addtogroup hxsurfedit hxsurfedit
/// @{
#ifndef SURF_EDIT_MOUSE_TOOL_H
#define SURF_EDIT_MOUSE_TOOL_H

#include "SurfEditTool.h"

class QxToolButton;

/** Base class for mouse tools. Mouse tools provide a mouseClick
    method which allows the tool to handle mouse events. Only one
    mouse tool can be active at each time. When mouse tool gets
    active the activate method defined in SurfEditTool
    is called. Before another mouse tool is activated deactivate
    is called. This allows mouse tools displaying a config dialog
    to close the dialog window.

    Mouse tools should define the xpm variable, so that a button
    in the tool bar will be created. In contrast to ordinary tools the
    tool button for mouse tools will be a toggle button indicating
    whether the tool is active or not. */

class SurfEditMouseTool : public SurfEditTool {

  public:
    /// Constructor.
    SurfEditMouseTool(HxSurfEdit* surfEdit);

    /// Destructor.
    ~SurfEditMouseTool();

    /// Interpretes mouse events.
    virtual void mouseClick(SoEventCallback *eventCB);

    /// Called before another mouse tool is activated.
    virtual void deactivate();

    virtual bool isExclusive(){ return true; }
};

#endif

/// @}
