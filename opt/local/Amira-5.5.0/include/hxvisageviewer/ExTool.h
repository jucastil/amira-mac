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

/// @addtogroup hxvisageviewer hxvisageviewer
/// @{
#ifndef  EX_TOOL_H
#define  EX_TOOL_H

#include "ExBase.h"
#include "ExNotifiable.h"
#include "VisageViewerWinDLLApi.h"

class  McString;
class  ExBaseViewer;

/** Base class for all tools. A tool has a unique name returned by
    the identifier() method. It can be added to an ExBaseViewer or
    removed from it. There are two derived classes:

    \li Triggers (ExTrigger) perform some operation in a viewer once,
        see ExTrigger:process().
    \li Modal tools (ExModal) are permanently active in a viewer and
        interprete mouse, wheel, or keyboard events.
*/

class HXVISAGEVIEWER_API ExTool : public ExNotifiable
{
public:
    /// Constructor.
    ExTool();

    /** Returns true if a tool can be used with a viewer, else
        return false. */
    virtual bool supports(Ex::ViewerType) const;

    /** Returns true if tool can be used in a specific viewer. 
        By default this method calls supports(viewer->type()) */
    virtual bool supportsViewer(const ExBaseViewer* viewer);

    /** Indicates that this tool is a standard tool,
        which is present in a viewer permanently. */
    virtual bool isStandard() const { return false; }

    /** Returns a name for identifying the class in ExTools.
        Should be the class-name. */
    virtual const McString identifier() const = 0;

    /** Return the active state of the tool. The currentActiveFlag indicates the state of the tool represented by the ToolUI
        that owns the tool. The default behaviour is to return the currentActiveFlag unchanged, to notify the ToolUI that
        the tool doesn't implement a special activation. The returned flag has highest priority. */
//    virtual bool isActive(ExToolUI* ui = 0) const { return ui ? ui->isActive() : false; }

    /** This method is defined to make the class non-abstract. */
    virtual void notified( const ExNotification& notification );

//    void setUI( ExToolUI* ui );
//    const ExToolUI* getUI() const;
//    ExToolUI* getUI(); // non-const version

    /** Indicates that the tool needs an exclusive click to activate the viewer.
        The click into an activated viewer starts the processing of the tool.
        This is needed for modal tools basically. */
    virtual bool needsExclusiveClickForActivation() const { return false; }

    /** Indicates the mouse button state for activating the tool.
        This is needed for modal tools basically. */
    virtual int stateForUse() const { return 0; }


    bool enabled();
    virtual void setEnabled( bool inFlag );

protected:

    bool mEnabled;
//    ExToolUI* mUI;
};

#endif // EX_TOOL_H

/// @}
