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

/// @addtogroup hxtime hxtime
/// @{
#ifndef HX_DYNAMIC_SERIES_CTRL_H
#define HX_DYNAMIC_SERIES_CTRL_H

#include <mclib/McList.h>
#include <hxcore/HxFileFormat.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxtime/HxDynamicDataCtrl.h>

/** Manages dynamic data stored as a series of HxObject.

    Initially this class simply adds all objects of the first time step
    to the object pool. If a new time step is chosen all modules connected
    to data objects of the previous step will be disconnected.
    Then the previous objects will be removed from the object pool
    and the new time step is loaded. Finally, the connections to the
    downstream modules will be reestablished as far as possible and
    the data objects will be fired.
*/

class HXTIME_API HxDynamicSeriesCtrl : public HxDynamicDataCtrl 
{

    HX_HEADER(HxDynamicSeriesCtrl);
    
public:

    class TimeStep
    {
    public:
        McDArray< McHandle<HxObject> > objects;
        void disconnectObjects();
    };

    /// Constructor.
    HxDynamicSeriesCtrl();
    
    /// Overloaded method which adds the objects of the choosen time step to the objectpool.
    void newTimeStep(int timeStep);

    /// Initializes the module with a set of objects for each time step.
    void init(const McDArray<TimeStep>& timeSteps );

    /// Tcl-comand interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Save sequence of commands which recreate this object
    virtual int saveCreation(FILE* fp, const char* dataDir, int saveFlags);

    /// Saves state of module as a script.
    virtual void savePorts(FILE* fp);

    /// Checks if result can be recomputed.
    virtual int canCreateData(HxData*, McString &createCmd);

    /// Returns 0, thus preventing that a result can be connected by hand.
    virtual int checkResult(int& id, HxData* result);

    /** Sets custom load command which recreates this object. This 
        method can be called in a read routine where a HxDynamicSeriesCtrl
        class is used to handle time-dependent data. */
    void setLoadCmd(const char* cmd);


protected:

    virtual ~HxDynamicSeriesCtrl();


    struct ObjectInfo 
    {
        int                     x;
        int                     y;
        int                     selected;
        McDArray<HxConnection*> connections;
        McDArray<HxObject*>     upstreamConnectionObjects;
    };

    McDArray<ObjectInfo>        objectInfo;
    McDArray<TimeStep>          timeSteps;
    McString                    loadCmd;

    void disconnect(int t);
    void disconnect(McDArray< McHandle<HxObject> >&);
    void reconnect(int t);
    void reconnect(McDArray< McHandle<HxObject> >&);
    void removeTimeStep(int t);
};

#endif

/// @}
