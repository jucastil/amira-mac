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

/// @addtogroup vsvolren vsvolren
/// @{
#ifndef VS_TASK_CONTROL_H
#define VS_TASK_CONTROL_H

#include "Vs.h"
#include "VsInterface.h"

#include <mclib/McProgressInterface.h>

class VsBackgroundWorker;

// VS_RELAY_CLASS VsTaskControl VsRelay

class VSVOLREN_API VsTaskControl
:   public VsInterface
,   virtual public McProgressInterface
{
    VS_DECL_INTERFACE        ( VsTaskControl )
    VS_DECL_INTERFACE_FACTORY( VsTaskControl )
    VS_DECL_INTERFACE_RELAY  ( VsTaskControl )

public:

    VsTaskControl( VsMeta * inMeta = 0 );

    void reset(); // VS_RELAY VS_NODELAY

    void cancel(); // VS_RELAY VS_NODELAY

    bool canceled() { return mCanceled; } // LOCAL_GET

    virtual int wasInterrupted(bool sync = true); // LOCAL_GET

    virtual void setCompleted(McResult inResult); // VS_RELAY VS_NODELAY

    bool running() const { return mRunning; } // LOCAL_GET

    virtual void setRunning(bool running); // VS_RELAY VS_NODELAY

    virtual void setProgressValueGlobal(float howMuch); // VS_RELAY VS_NODELAY

    virtual void setProgressText(const char* text); // VS_RELAY VS_NODELAY

    // the roc couldn't relay functions with parameters like these: "(const char* format, ...)"
    virtual void startWorking(const char* format, ...); // => startWorking_relayable

    virtual void startWorking_relayable(const char* text); // VS_RELAY VS_NODELAY

    virtual void startWorkingCall(const char* text);

    // the roc couldn't relay functions with parameters like these: "(const char* format, ...)"
    virtual void startWorkingNoStop(const char* format, ...); // => startWorkingNoStop_relayable

    virtual void startWorkingNoStop_relayable(const char* text); // VS_RELAY VS_NODELAY

    virtual void subdivide(int ranges); // VS_RELAY VS_NODELAY

    virtual void undivide(); // VS_RELAY VS_NODELAY

    virtual void stopWorking(); // VS_RELAY VS_NODELAY

private:

    bool mCanceled;
    bool mRunning;

protected:

    friend class VsBackgroundWorker;
};

#endif // VS_TASK_CONTROL_H

/// @}
