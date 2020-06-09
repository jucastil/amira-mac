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

/// @addtogroup hxsegeditor hxsegeditor
/// @{
#ifndef  Mc_EVENT_H
#define  Mc_EVENT_H

#include <mclib/McVec2i.h>
#include "HxGiWinDLLApi.h"

/// This identifies event types.
typedef int* McEventType;

/// Base class for all GI events.
class HXSEGEDITOR_API McEvent {

  public:
    /// Constructor.
    McEvent() {};

    /// Destructor.
    virtual ~McEvent() {};

    /// Returns type of McEvent class.
    static McEventType getClassTypeId() { return &classTypeId; }

    /// Returns TRUE if event is of given type or is derived from it.
    virtual int isOfType(McEventType type) const { return type==&classTypeId; }

    /// Set window position (relative to origin of viewport).
    void setPosition(const McVec2i &p) { position = p; }

    /// Get window position.
    const McVec2i& getPosition() const { return position; }

    /// Set state of buttons and modifier keys.
    void setShiftDown(int isDown) { shiftDown = isDown; }
    void setCtrlDown(int isDown) { ctrlDown = isDown; }
    void setAltDown(int isDown) { altDown = isDown; }
    void setButton1Down(int isDown) { button1down = isDown; }
    void setButton2Down(int isDown) { button2down = isDown; }
    void setButton3Down(int isDown) { button3down = isDown; }

    /// Return state of buttons and modifier keys.
    int wasShiftDown() const { return shiftDown; }
    int wasCtrlDown() const { return ctrlDown; }
    int wasAltDown() const { return altDown; }
    int wasButton1Down() const { return button1down; }
    int wasButton2Down() const { return button2down; }
    int wasButton3Down() const { return button3down; }

  private:
    // All of these are set according to when the event occurred
    int shiftDown;
    int ctrlDown;
    int altDown;
    int button1down;
    int button2down;
    int button3down;

    McVec2i position;

    static int classTypeId;
};

#endif

/// @}
