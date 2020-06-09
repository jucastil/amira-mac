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
#ifndef  EX_NOTIFIABLE_H
#define  EX_NOTIFIABLE_H

#include "ExNotification.h"
#include <vsvolren/VsHandable.h>
#include "VisageViewerWinDLLApi.h"

/** Base class for objects receiving notification events. This
    class defines a pure virtual method notified() which needs
    to be implemented by derived classes. Notification events
    can be sent via notify(). This is a static method that calls
    notified() for all currently existing ExNotifiable objects. */

class HXVISAGEVIEWER_API ExNotifiable : public virtual VsHandable {

public:
    /// Constructor.
    ExNotifiable();

    /// Destructor.
    virtual ~ExNotifiable();

    /** Traverses the list of ExNotifiable objects and calls
        notified() of each of them. */
    static void notify(const ExNotification& notification);

    /** Alternative method. Essentially behaves as the method
        above. Internally an ExNotification object with the viewer,
        tool, and data memebers set to null will be created. */
    static void notify(ExNotification::Type notificationType);

    /** This method is called whenever some notification event
        is sent. Derived classes need to implement this method
        in order to react on such events. */
    virtual void notified(const ExNotification& notification) = 0;
};

#endif // EX_NOTIFIABLE_H


/// @}
