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
#ifndef HX_TRACKING_THREAD_H
#define HX_TRACKING_THREAD_H

#include <hxcore/HxThread.h>
#include <Inventor/SbLinear.h>
#include <hxtracking/hxtrackingAPI.h>

class HxVREvent;
struct HxTrackingThreadData;

typedef void HxVREventCB(void *userData, HxVREvent* event);

/** Low-level interface to the tracking system (HxTrackingSystem). This
    class manages a separate thread which continuously gets the current
    tracker and button state from the connected tracking system. The
    tracker coordinates are optionally transformed into a user-defined
    coordinate system (after calling the @c calibrate() method). Changes
    in button state are queued so that button events cannot be lost. 
    
    This class is a singleton. You can access it from outside via the
    global pointer @c theTrackingThread. You may register an event 
    callback with this class, thereby bypassing any high-level event
    handling provided by the HxTracking AmiraVR control modul. However,
    if you want to implement new interaction methods, the preferred
    way is to derive from HxVREventHandler and to register the new
    event handler with HxTracking. */

class HXTRACKING_API HxTrackingThread : public HxThread
{
  public:
    /// Returns pointer to global instance of the tracking thread.
    static HxTrackingThread* getGlobalInstance();
    
    /** Connects to a tracking system. The argument @c driver indicates
        the tracking driver to be used. For details see HxTrackingSystem.
        The method returns true if a connection to the tracking system
        could be established. If some error occurred false is returned. */
    bool startTracking(const char* driver);

    /// Disconnects from the tracking system.
    void stopTracking();

    /// Returns true if tracking is active.
    bool isTracking() const;

    /** Returns the name of the currently connected tracking driver. If
        tracking is not active NULL is returned. */
    const char* getTrackingDriver() const;
    
    /** Adds an event callback. If tracking is active the specified function
        is called repeatedly. It reports the current sensor positions as
        well as any queued button events to the client. */
    void addEventCallback(HxVREventCB* f, void* userData=NULL);

    /// Removes an event callback.
    void removeEventCallback(HxVREventCB* f, void* userData=NULL);

    /** Removes all queued events from the event queue. When calling this
        method all button events recorded since the last time the event
        callbacks were invoked are discarded. */
    void clearEventQueue();

    /** Returns the number of sensors attached to the tracking system.
        If no tracking driver is connected 0 is returned. */
    int getNumberOfSensors() const;

    /** Gets calibrated position of a tracker. The method asks the
        tracking system for the current position of the tracker and
        then transforms the result according to the current calibration
        settings. */
    void getSensorPosition(SbVec3f& position, int idx);

    /** Gets calibrated orientation of a tracker. The method asks the
        tracking system for the current orientation of the tracker and
        then transforms the result according to the current calibration
        settings. */
    void getSensorOrientation(SbRotation& rot, int idx);

    /** Returns the number of buttons attached to the tracking system.
        If no tracking system is connected 0 is returned. */
    int getNumberOfButtons() const;

    /** Returns the number of valuators attached to the tracking system.
        If no tracking system is connected 0 is returned. */
    int getNumberOfValuators() const;

    /** Returns the current button mask. The bits of the button mask
        indicate whether a button is pressed or not. For example, if
        button 0 is set, bit 0 of the mask is set. */
    unsigned int getButtonMask() const;

    /** Checks is a button is currently pressed. The method reports the
        current state of a button. */
    bool isButtonPressed(int k);
    
    /** Sets the doubleclick interval in milliseconds. In order to disable 
        doubleclick detection set the interval to 0. Any button press event
        occuring not later than @c msec milliseconds after the same button
        was pressed the last time is marked as a double click event. */
    unsigned int setDoubleClickInterval(unsigned int msec);

    
    /** Sets a transformation applied to the sensor positions. On default,
        sensor positions are reported in the native coordinate system of
        the tracking device. This method allows the user to specify a new
        customized coordinate system. @c orig, @c xVec and @c yVec must be
        given in native device coordinates. After this call all positions
        and are reported with respect to the new coordinate system.

        For example, it is often convenient to have the x-axis aligned
        with the lower side of the projection screen, and the y-axis
        aligned with the left side of the screen. This can be achieved by
        first determining the device coordinates of the upper left, lower
        left, and lower right corners of the screen, and then calling
        calibrate in the following way:

        @code
           theTrackingThread->resetCalibration(); 
           // Click in upper left, lower left, and lower right corner of screen...
           SbVec3f orig = lowerLeft;
           SbVec3f xVec = lowerRight - lowerLeft;
           SbVec3f yVec = upperLeft - lowerLeft;
           theTrackingThread->calibrate(orig, xVec, yVec);
        @endcode

        The routine automatically normalizes @c xVec and @c yVec. In order
        to change the scale of positional data you may use the optional
        argument @c scale. For example, if the tracking system reports
        coordinate data in inches, but you want to get centimeters, use a
        value of 2.54 for @c scale. */
    void calibrateSensorPositions(const SbVec3f& orig, const SbVec3f& xVec,
        const SbVec3f& yVec, float scale=1);

    /** Sets a transformation applied to a sensor orientations. On default,
        the orientation of a sensor depends on the specific tracking device
        being used. With this method a new reference for the orientation
        values reported by sensor @c idx can be set. */
    void calibrateSensorOrientation(int idx, const SbRotation& orientation);

    /** Resets any user-defined coordinate transformations. After calling this
        method sensor positions and sensor orientations are reported in the
        native coordinate system used by the current tracking device. */
    void resetCalibration();

    void emulateButton(bool b, int key);

  protected:
    // Constructor is protected because this is a singleton.
    HxTrackingThread();

    // Destructor.
    ~HxTrackingThread();

    // Continuously asks the tracking system for new data
    virtual void run();

    HxTrackingThreadData* d;

    static void doIdleTasks(void* userData);
};

#define theTrackingThread HxTrackingThread::getGlobalInstance()

#endif

/// @}
