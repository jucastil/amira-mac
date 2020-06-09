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
#ifndef MC_KEYBOARD_EVENT_H
#define MC_KEYBOARD_EVENT_H

#include "McEvent.h"
#include "HxGiWinDLLApi.h"

/// Represents a keyboard event.
class HXSEGEDITOR_API McKeyboardEvent : public McEvent {

  public:

    enum Key {
        // Special constant for any key
        ANY = 0,

        // Modifiers
        LEFT_SHIFT = 0xffe1,
        RIGHT_SHIFT = 0xffe2,
        LEFT_CONTROL = 0xffe3,
        RIGHT_CONTROL = 0xffe4,
        LEFT_ALT = 0xffe9,
        RIGHT_ALT = 0xffea,

        // Numbers
        NUMBER_0 = 0x030,
        NUMBER_1 = 0x031,
        NUMBER_2 = 0x032,
        NUMBER_3 = 0x033,
        NUMBER_4 = 0x034,
        NUMBER_5 = 0x035,
        NUMBER_6 = 0x036,
        NUMBER_7 = 0x037,
        NUMBER_8 = 0x038,
        NUMBER_9 = 0x039,

        // Letters
        A = 0x061,
        B = 0x062,
        C = 0x063,
        D = 0x064,
        E = 0x065,
        F = 0x066,
        G = 0x067,
        H = 0x068,
        I = 0x069,
        J = 0x06a,
        K = 0x06b,
        L = 0x06c,
        M = 0x06d,
        N = 0x06e,
        O = 0x06f,
        P = 0x070,
        Q = 0x071,
        R = 0x072,
        S = 0x073,
        T = 0x074,
        U = 0x075,
        V = 0x076,
        W = 0x077,
        X = 0x078,
        Y = 0x079,
        Z = 0x07a,

        // Cursor control & motion
        HOME = 0xff50,
        LEFT_ARROW = 0xff51,
        UP_ARROW = 0xff52,
        RIGHT_ARROW = 0xff53,
        DOWN_ARROW = 0xff54,
        PAGE_UP = 0xff55,
        PAGE_DOWN = 0xff56,
        PRIOR = 0xff55,
        NEXT = 0xff56,
        END = 0xff57,

        // Keypad Functions
        PAD_ENTER = 0xff8d,
        PAD_F1 = 0xff91,
        PAD_F2 = 0xff92,
        PAD_F3 = 0xff93,
        PAD_F4 = 0xff94,

        PAD_0 = 0xff9e,
        PAD_1 = 0xff9c,
        PAD_2 = 0xff99,
        PAD_3 = 0xff9b,
        PAD_4 = 0xff96,
        PAD_5 = 0xff9d,
        PAD_6 = 0xff98,
        PAD_7 = 0xff95,
        PAD_8 = 0xff97,
        PAD_9 = 0xff9a,

        PAD_ADD = 0xffab,
        PAD_SUBTRACT = 0xffad,
        PAD_MULTIPLY = 0xffaa,
        PAD_DIVIDE = 0xffaf,

        PAD_SPACE = 0xff8d,
        PAD_TAB = 0xff89,
        PAD_INSERT = 0xff9e,
        PAD_DELETE = 0xff9f,
        PAD_PERIOD = 0xff9f,

        // Function keys
        F1 = 0xffbe,
        F2 = 0xffbf,
        F3 = 0xffc0,
        F4 = 0xffc1,
        F5 = 0xffc2,
        F6 = 0xffc3,
        F7 = 0xffc4,
        F8 = 0xffc5,
        F9 = 0xffc6,
        F10 = 0xffc7,
        F11 = 0xffc8,
        F12 = 0xffc9,

        // Misc Functions
        BACKSPACE = 0xff08,
        TAB = 0xff09,
        RETURN = 0xff0d,
        ENTER = 0xff0d,
        PAUSE = 0xff13,
        SCROLL_LOCK = 0xff14,
        KEY_ESCAPE = 0xff1b,
        KEY_DELETE = 0xffff,
        PRINT = 0xff61,
        INSERT = 0xff63,
        NUM_LOCK = 0xff7f,
        CAPS_LOCK = 0xffe5,
        SHIFT_LOCK = 0xffe6,

        SPACE = 0x020,
        APOSTROPHE = 0x027,
        CTRL_PLUS = 0x01d,
        PLUS = 0x02b,
        COMMA = 0x02c,
        MINUS = 0x02d,
        PERIOD = 0x02e,
        SLASH = 0x02f,

        SEMICOLON = 0x03b,
        EQUAL = 0x03d,

        BRACKETLEFT = 0x05b,
        BACKSLASH = 0x05c,
        BRACKETRIGHT = 0x05d,
        GRAVE = 0x060
    };

    enum State { PRESS=0, RELEASE } state;

    /// Constructor.
    McKeyboardEvent() { count=1; keyState = PRESS; autoRepeat = false;}

    /// Destructor.
    virtual ~McKeyboardEvent() {}

    /// Returns type of McKeyboardEvent class.
    static McEventType getClassTypeId() { return &classTypeId; }

    /// Returns TRUE if event is of given type or is derived from it.
    virtual int isOfType(McEventType type) const {
        return (type==&classTypeId) || McEvent::isOfType(type);
    }

    /// Set key (e.g. McKeyboardEvent::A)
    void setKey(McKeyboardEvent::Key whichKey) { key = whichKey; }
    
    void setAutoRepeat(bool inFlag) { autoRepeat = inFlag; }

    /// Get key.
    int getKey() { return key; }

    int isKeyPressEvent() { return keyState==PRESS; };
    int isKeyReleaseEvent() { return keyState==RELEASE; };
    int isKeyAutoRepeat() { return autoRepeat; }

    void setKeyPress() { keyState=PRESS;};
    void setKeyRelease() { keyState=RELEASE;};

    int count;

  private:
    int  key;
    int  keyState;
    bool autoRepeat;
    static int classTypeId;
};

#endif

/// @}
