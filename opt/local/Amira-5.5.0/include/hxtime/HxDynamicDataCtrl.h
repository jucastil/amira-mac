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
#ifndef HX_DYNAMIC_DATA_CTRL_H
#define HX_DYNAMIC_DATA_CTRL_H

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxtime/HxPortTime.h>

/** Base class for modules managing dynamic (time-dependent) data.
    Currently, in Amira there are no or not many classes which
    directly represent time-dependent data. As a workaround ordinary
    static data objects can be created. These objects can be updated
    in order to represent other time steps.

    To update static data objects it is most convenient to design a
    special-purpose compute module. The class @c HxDynamicDataCtrl
    is intended to be the base class of such modules. It provides
    a time port. Whenever the time changes one of the virtual methods
    newTimeStep respectively newPhysicalTime is called.
    Derived classes should overload these method. */

class HXTIME_API HxDynamicDataCtrl : public HxCompModule {

  HX_ABSTRACT_HEADER(HxDynamicDataCtrl);

  public:
    /// Constructor.
    HxDynamicDataCtrl();
    
    /// Info port displaying the total number of time steps.
    HxPortInfo portInfo;

    /// Specifies whether time port refers to time steps or physical time.
    HxPortRadioBox portMode;
    enum { MODE_TIME_STEP=0, MODE_PHYS_TIME=1 };

    /// Current time.
    HxPortTime portTime;

    /// Update method, configures user interface.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Sets allowed range of time steps.
    void setTimeStepRange(int firstTimeStep, int lastTimeStep);

    /// Sets allowed range of physical time.
    void setPhysicalTimeRange(float startTime, float stopTime);

    int getCurrentTimeStep(){return currentTimeStep;}

    /// Return corresponding time dependant data
    virtual HxData *getData(int timeStep,HxData *currentData);

    /// This is called when a new time is chosen in time step mode.
    virtual void newTimeStep(int timeStep);

    /// This is called when a new time is chosen in physical time mode.
    virtual void newPhysicalTime(float time);

    // Tcl-comand interface.
    // virtual int parse(Tcl_Interp* t, int argc, char **argv);

  protected:
    virtual ~HxDynamicDataCtrl();

    int currentMode;
    int currentTimeStep;
    float currentPhysicalTime;
    int timeStepRange[2];
    float physicalTimeRange[2];
};

#endif

/// @}
