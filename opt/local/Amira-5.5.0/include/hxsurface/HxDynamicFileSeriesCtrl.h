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

/// @addtogroup hxsurface hxsurface
/// @{
#ifndef HX_DYNAMIC_FILE_SERIES_CTRL_H
#define HX_DYNAMIC_FILE_SERIES_CTRL_H

#include <mclib/McList.h>
#include <hxcore/HxCompModule.h>
#include <hxcore/HxFileFormat.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortToggleList.h>
#include <hxtime/HxPortTime.h>
#include <hxsurface/HxSurfaceWinDLLApi.h>

/** Manages dynamic data stored as a series of static data files.
    This class can be used whenever time-dependent data is stored
    as a series of files in any format supported by Amira. Since
    the files are read using Amira's standard read routines, the
    type of the data objects stored in the file series doesn't
    matter.

    Initially this class simply tries to load the first file of
    the series. If a new time step is chosen all modules connected
    to data objects loaded in the previous step will be disconnected.
    Then the previously loaded objects will be deleted and the
    new time step will be loaded. Finally, the connections to the
    downstream modules will be restablished as far as possible and
    the data objects will be fired.
    
    Optionally, a user-defined number of time steps can be cached
    instead of reloading the corresponding file each time. */

class HXSURFACE_API HxDynamicFileSeriesCtrl : public HxCompModule {

  HX_HEADER(HxDynamicFileSeriesCtrl);

  public:
    /// Constructor.
    HxDynamicFileSeriesCtrl();
    
    /// Info port displaying the total number of time steps.
    HxPortInfo portInfo;

    /// Cache options:
    HxPortIntTextN portCache;

    /// Options: 0=interpolate between frames, 1=physical time
    HxPortToggleList portOptions;

    /// Current time.
    HxPortTime portTime;

    /// Compute method
    virtual void compute();

    /// Initializes the module with a set of file names.
    void initFiles(int nFiles, const char* const* files, HxFileFormat**);

    /// Tcl-comand interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Saves state of module as a script.
    virtual void savePorts(FILE* fp);

    /// Check if pack&go option was requested.
    virtual int saveCreation(FILE* fp, const char* dataDir, int saveFlags);

    /// Checks if result can be recomputed.
    virtual int canCreateData(HxData*, McString &createCmd);

    /// Returns 0, thus preventing that a result can be connected by hand.
    virtual int checkResult(int& id, HxData* result);

  protected:
    virtual ~HxDynamicFileSeriesCtrl();

    struct TimeStep : public McHandable, public McLink {
        int cannotInterpolate;
        int hasPhysicalTime;
        float physicalTime;
        McString filename;
        HxFileFormat* format;
        McDArray< McHandle<HxObject> > objects;
        void disconnectObjects();
    };

    struct ObjectInfo {
        int x, y;
        McDArray<HxConnection*> connections;
        McDArray< McHandle<HxObject> > upstreamConnectionObjects;
    };

    McList<TimeStep> cache;
    int nCachedObjects;
    int hasPhysicalTime;
    int useInterpolation;
    int usePhysicalTime;
    int currentTimeStep;
    int currentK;
    float currentU;
    float currentPhysicalTime;
    McDArray< McHandle<HxObject> > interpolatedObjects;

    int useLoadCmd;
    McString loadCmd;

    McString fileFormat;
    McDArray< ObjectInfo > objectInfo;
    McDArray< McHandle<TimeStep> > timeSteps;

    void updateInfoPort();
    void disconnect(McDArray< McHandle<HxObject> >&);
    void reconnect(McDArray< McHandle<HxObject> >&);
    void disconnect(int t);
    void reconnect(int t);
    void removeTimeStep(int t);
    void loadTimeStep(int t);
    void interpolate(int k, float u);
};

#endif

/// @}
