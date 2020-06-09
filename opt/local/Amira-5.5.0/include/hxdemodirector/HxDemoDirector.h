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

/// @addtogroup hxdemodirector hxdemodirector
/// @{
#ifndef HXDEMODIRECTOR_H
#define HXDEMODIRECTOR_H

#include <tcl.h>
#include "hxdemodirector/HxDemoDirectorWinDLLApi.h"
#include "hxdemodirector/QxTimelineWidget.h"

#include <hxcore/HxMain.h>

class QxDemoDirectorNotifier;

/**
The DemoDirector is a new GUI for creating Demos with the Demo Maker. The class
HxDemoDirector provides a Tcl interface for the communication between the GUI 
(which is implemented in \see{timeline::TimelineWidget}) and the Demo Maker. 
Furthermore it has a helper class \see{QxDemoDirectorNotifier} which is connected
with some signals from the pool in order to notify the Demo Maker about pool changes.
*/
class HXDEMODIRECTOR_API HxDemoDirector
{
    HxDemoDirector();
    ~HxDemoDirector();
public:
    /// Get the DemoDirector instance (which is a singleton).
    static HxDemoDirector * getTheDemoDirector();
    /// Parses a Tcl command and calls the appropriate method in \see{timeline::TimelineWidget}.
    static int staticParse(ClientData, Tcl_Interp* t, int argc, char** argv);
    /// Parses a Tcl command and calls the appropriate method in \see{timeline::TimelineWidget}.
    int parse(Tcl_Interp* t, int argc, char** argv);

    /// Sends a command to theInterpreter.
    const char* sendCmd(char *string, bool setDirtyFlag);
    /// Marks the event template list stored in the GUI as invalid. 
    void invalidateEventTemplateList();
    /// Prompts the Demo Maker to recreate the available events list and send it to the DemoDirector.
    void initiateEventTemplateListUpdate();
    
    void removeGUIItems();

    void setNetworkDirtyFlag();
protected:
    /// The GUI widget.
    hxdemodirector::QxTimelineWidget *mTimelineWidget;

    /// The Tcl name of the currently associated Demo Maker.
    McString mDemoMaker;
    /// The helper class for retrieving signals.
    QxDemoDirectorNotifier *mNotifier;
};

#define theDemoDirector HxDemoDirector::getTheDemoDirector()

#endif //HXDEMODIRECTOR_H

/// @}
