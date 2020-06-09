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

/// @addtogroup hxtracking hxtracking
/// @{
#ifndef HX_TRACKING_EVENT_H
#define HX_TRACKING_EVENT_H

#include <mclib/McDArray.h>
#include <Inventor/SbLinear.h>
#include <hxtracking/hxtrackingAPI.h>

/** Represents a VR tracking event. */

class HXTRACKING_API HxVREvent
{
  public:
    /** Event type. If the event type is one of the three
        button event types, a HxVREvent pointer an safely be
        downcasted to a HxVRButtonEvent pointer. */
    enum Type {
        /// Unknown event.
        NoEvent = 0,
        /// Indicates that a 3D mouse button has been pressed.
        ButtonPressEvent = 1,
        /// Indicates that a 3D mouse button has been released.
        ButtonReleaseEvent = 2,
        /** Indicates that a 3D mouse button has been double-clicked.
            The first click of a button click event will always be
            reported as a standard button press event. */
        ButtonDoubleClickEvent = 3,
        /** The sensor positions have changed. A motion-notify event
            is not associated with a particular sensor. Instead the
            current positions of all attached sensors are reported
            simulataneously. */
        MotionNotifyEvent = 4
    };

    /// Constructor creates a NoEvent type event.
    HxVREvent() { 
        m_pickingDisabled = false;
        m_viewingDisabled = false;
        eventType=NoEvent; 
    }

    /// Copy constructor.
    HxVREvent(const HxVREvent& other);
    
    /// Destructor.
    ~HxVREvent() { }

    /// Assignment operator.
    HxVREvent& operator=(const HxVREvent& other);

    /// Returns the event type.
    Type type() const { return eventType; }

    /// Sets the event type.
    void setType(Type type) { eventType=type; }

    /// Returns the number of buttons of the tracking system.
    int getNumberOfButtons() const { return numButtons; }

    /** Returns the button mask. The button mask is a bitmask indicating
        which button is currently hold down. */
    unsigned int getButtonMask() const { return buttonMask; }

    /// Returns the number of sensors of the tracking system.
    int getNumberOfSensors() const { return sensorInfo.size(); }

    /// Returns the position of sensor k.
    const SbVec3f& getSensorPosition(int k) const { return sensorInfo[k].position; }

    /// Non-const version of getSensorPosition().
    SbVec3f& getSensorPosition(int k) { return sensorInfo[k].position; }

    /// Returns the orientation of sensor k.
    const SbRotation& getSensorOrientation(int k) const { return sensorInfo[k].orientation; }

    /// Non-const version of getSensorOrientation().
    SbRotation& getSensorOrientation(int k) { return sensorInfo[k].orientation; }

    /// Returns the number of valuators of the tracking system.
    int getNumberOfValuators() const { return valuatorInfo.size(); }

    /// Returns the value of valuator k.
    float getValuator(int k) const { return valuatorInfo[k]; }

    /// Sets the number of buttons of the event structure.
    void setNumberOfButtons(unsigned int num) { numButtons=num; }

    /// Sets the button mask.
    void setButtonMask(unsigned int mask) { buttonMask=mask; }

    /// Sets the number of sensors.
    void setNumberOfSensors(int n) { sensorInfo.resize(n); }

    /// Sets a sensor position.
    void setSensorPosition(int k, const SbVec3f& pos) { sensorInfo[k].position = pos; }

    /// Sets a sensor orientation.
    void setSensorOrientation(int k, const SbRotation& ori) { sensorInfo[k].orientation = ori; }

    /// Sets the number of valuators.
    void setNumberOfValuators(int n) { valuatorInfo.resize(n); }

    /// Sets a valuator value.
    void setValuator(int k, float value) { valuatorInfo[k] = value; }

    bool isPickingDisabled() const { return m_pickingDisabled; }
    void setPickingDisabled(bool b) { m_pickingDisabled = b; }

    bool isViewingDisabled() const { return m_viewingDisabled; }
    void setViewingDisabled(bool b) { m_viewingDisabled = b; }

  protected:

    bool m_pickingDisabled;
    bool m_viewingDisabled;
    Type eventType;
    unsigned int buttonMask;
    unsigned int numButtons:8;

    struct SensorInfo {
        SbVec3f position;
        SbRotation orientation;
    };

    McDArray<SensorInfo> sensorInfo;

    McDArray<float> valuatorInfo;
};

#endif

/// @}
