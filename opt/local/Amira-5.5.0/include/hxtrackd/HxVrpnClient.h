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

/// @addtogroup hxtrackd hxtrackd
/// @{
#ifndef HXVRPNCLIENT_H
#define HXVRPNCLIENT_H

#include <hxtrackd/HxTrackingSystem.h>

#include <mclib/McString.h>
#include <mclib/McVec3f.h>
#include <mclib/McRotation.h>

#include <vrpn/vrpn_Tracker.h>
#include <vrpn/vrpn_Button.h>


#define VRPN_CLIENT_NUMBER_OF_BUTTONS 3
#define VRPN_CLIENT_NUMBER_OF_SENSORS 2


class HxVrpnClient : public HxTrackingSystem
{
  public:
    //// Opens two connections to a VRPN tracker and VRPN button button device.
    ///  @param trackingDeviceName A VRPN device name like configured in the vrpn.cfg conf file (e.g. Tracker0@localhost:3883).
    ///  @param buttonDeviceName A VRPN name like configured in the vrpn.cfg conf file (e.g. Wanda@localhost:3883)
    HxVrpnClient(const McString& trackingDeviceName, const McString& buttonDeviceName);

    /// Closes connection to the tracking system and frees all resources.
    virtual ~HxVrpnClient();

    /// Returns true if the VRPN client has successfully connected to the server
    /// Note: VRPN doesn't provide an API to check if the connection to the tracker
    /// or the button device has been successfully established, thus this function will
    /// alays return true.
    virtual bool isConnected();

    /// Returns the number of sensors of the current tracking system configuration.
    /// Note: VRPN doesn't provide an API to query the number of sensors,
    /// thus we pretend that always two sensors are available even thought
    /// the current tracker device is configured for only one senors.
    virtual int getNumberOfSensors();

    /// Gets the position values for sensor[id].
    virtual void getPosition(int id, float* pos);

    /// Gets the transformation matrix for sensor[id].
    virtual void getMatrix(int id, float mat[4][4]);

    /// Returns the number of buttons of the current tracking system configuration.
    /// Note: VRPN doesn't provide an API to query the number of buttons,
    /// thus we pretend that always three buttons are available even thought
    /// the current button device is configured for less buttons.
    virtual int getNumberOfButtons();

    /// Returns the value of button[id] from the tracker daemon.
    /// Note: Returns always 0 if the button id is not supported by the VRPN button device.
    virtual int getButton(int id);

  private:
    static void handle_tracker (void*, const vrpn_TRACKERCB t);
    static void handle_button (void*, const vrpn_BUTTONCB t);

    vrpn_Tracker_Remote *vrpnTracker;
    vrpn_Button_Remote  *vrpnButton;

    static McVec3f    sPos[VRPN_CLIENT_NUMBER_OF_SENSORS];
    static McRotation sOri[VRPN_CLIENT_NUMBER_OF_SENSORS];
    static int        sButtonState[VRPN_CLIENT_NUMBER_OF_BUTTONS];
};

#endif // HXVRPNCLIENT_H

/// @}
