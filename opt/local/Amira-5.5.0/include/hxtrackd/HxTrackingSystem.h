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
#ifndef HXTRACKING_SYSTEM_H
#define HXTRACKING_SYSTEM_H

#include <hxtrackd/hxtrackd.h>

/** Abstract base class for a tracking system with 3d sensors, buttons, and
    valuators. Currently in Amira two different tracking system interfaces
    are supported, namely VRCO's trackAPI and SpacePad server.
    Both interfaces can be accessed in the same way via this class. */

class HXTRACKD_API HxTrackingSystem
{
  public:
    /** Initializes the Amira tracking library and returns a pointer
        to a tracking system class. Depending on the value of @c data
        different tracking system drivers are used.

        In order to access a running trackd server, the data string should
        be <tt> contrKey:trackKey</tt> (e.g., <tt> 4147:4148</tt>), where <tt>
        contrKey</tt> specifies the shared memory area where controller data is
        stored (buttons and valuators), and <tt> trackKey</tt> specifies the
        shared memory area where tracker data is stored (3d sensors).

        In order to access a running SpacePad server, the data
        string should be <tt> host:port</tt> (e.g., <tt> tracker:7200</tt>), where
        <tt> host</tt> specifies the computer where the SpacePad server is
        running on, and <tt> port</tt> specifies the port number of the server.
    */
    static HxTrackingSystem* create(const char* data);

    /// Close connection to the tracking system and frees all resources.
    virtual ~HxTrackingSystem();

    /// Returns true if tracking system was sucessfully connected.
    virtual bool isConnected();

    /// Returns the number sensors the tracker daemon is storing.
    virtual int getNumberOfSensors();

    /// Gets the position values for sensor[id].
    virtual void getPosition(int id, float* pos);

    /// Gets the transformation matrix for sensor[id].
    virtual void getMatrix(int id, float mat[4][4]);

    /// Returns the number of valuators the tracker daemon is storing.
    virtual int getNumberOfValuators();

    /// Returns the number of buttons the tracker daemon is storing.
    virtual int getNumberOfButtons();

    /// Returns value of valuator[id] from the tracker daemon.
    virtual float getValuator(int id);

    /// Returns the value of button[id] from the tracker daemon.
    virtual int getButton(int id);

  protected:
    HxTrackingSystem();
};

#endif

/// @}
