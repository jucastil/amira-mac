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

/// @addtogroup hxcore hxcore
/// @{
#ifndef HX_PICK_CALLBACK_H
#define HX_PICK_CALLBACK_H

class McString;
class HxModule;

class SoPickedPoint;
class SoEvent;
class SoEventCallback;

#ifdef Button1
#undef Button1
#endif

#ifdef Button2
#undef Button2
#endif

#ifdef Button3
#undef Button3
#endif

#ifdef None
#undef None
#endif

/**
 * class with picking related enums and methods
 */
class HXCORE_API HxPickCallback {
  
public:

    /// modifier constants used in state mask.
    enum Modifier {
        ShiftButton     = 1<<0,
        ControlButton   = 1<<1,
        AltButton       = 1<<2,

        Button1         = 1<<3,
        Button2         = 1<<4,
        Button3         = 1<<5,

        VRButton0       = 1<<6,
        VRButton1       = 1<<7,
        VRButton2       = 1<<8,
        VRButton3       = 1<<9,
        VRButton4       = 1<<10,
        VRButton5       = 1<<11,
        VRButton6       = 1<<12,
        VRButton7       = 1<<13,
        VRButton8       = 1<<14,
        VRButton9       = 1<<15
    };

    /// EvenType constants
    enum EventType {
        None,

        MouseButtonPress,
        MouseButton1Press,
        MouseButton2Press,
        MouseButton3Press,

        MouseButtonRelease,
        MouseButton1Release,
        MouseButton2Release,
        MouseButton3Release,

        VRButtonPress,
        VRButton0Press,
        VRButton1Press,
        VRButton2Press,
        VRButton3Press,
        VRButton4Press,
        VRButton5Press,
        VRButton6Press,
        VRButton7Press,
        VRButton8Press,
        VRButton9Press,

        VRButtonRelease,
        VRButton0Release,
        VRButton1Release,
        VRButton2Release,
        VRButton3Release,
        VRButton4Release,
        VRButton5Release,
        VRButton6Release,
        VRButton7Release,
        VRButton8Release,
        VRButton9Release
    };

    /// Returns the EvenType value according to its name
    static EventType getEventTypeByName(const McString & name);

    /// Finds the module whose geometry has been picked
    static HxModule* getPickedModule(const SoPickedPoint*);

    /// Outputs an EventType and states corresponding to an Inventor event
    static void translate( const SoEvent* input, EventType&, int& stateBefore, int& stateAfter );

    /// Returns true if the input event matches with the filter
    static bool matches(const EventType& filter, const EventType& input);

    /// Generates the picking information and call the tcl callback cbProc with those arguments
    static void gatherPickInfo(SoEventCallback* node, 
                               McString& cbProc, 
                               EventType cbEventType, 
                               HxModule* pickedModule);
};

#endif

/// @}
