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
#ifndef  EX_TOOLS_H
#define  EX_TOOLS_H

#include "ExNotification.h"

#include <mclib/McString.h>

class ExNotifiable;
class ExToolsPrivate;
class ExTool;

/// Maintains a list of ExNotifiable objects, i.e., objects
/// that implement the notified-method. This is a singleton class.
class ExTools {

    friend class ExNotifiable;

private:
    /// Called from the constructor of ExNotifiable to insert itself to the list.
    void append( ExNotifiable * notifiable );
    /// Called from the destructor of ExNotifiable to remove itself from the list.
    void remove( ExNotifiable * notifiable );
public:

    static ExTools & getInstance();

    void deleteAllTools();

    /// Returns a tool by its identifier id. This is very expensive 
    /// and should only used situtations that are not time-critical.
    ExTool* getTool( const McString& id ) const;

    /// Moves the ExNotifiable to the end of the list. This allows
    /// to a small extent to control the order of ExNotifiable objects
    /// in in case of a notification.
    void moveToLast( ExNotifiable* notifiable );

    /// Forwards notification to each ExNotifiable in the list, i.e.,
    /// invokes the notified() method of them. ExNotifiable objects
    /// that have been inserted first are notified first.
    virtual void notify( const ExNotification& notification );

protected:

    ExTools();
    virtual ~ExTools();

private:
    ExToolsPrivate *d;
};

#endif // EX_TOOLFACTORY_H


/// @}
