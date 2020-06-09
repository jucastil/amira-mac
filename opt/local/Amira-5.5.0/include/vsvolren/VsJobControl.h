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
#ifndef _VS_JOB_CONTROL_H_
#define _VS_JOB_CONTROL_H_


#include "Vs.h"

#include "VsInterface.h"
#include "VsHandable.h"

// XX_RELAY_CLASS VsJobControl VsRelay

/** Interface class to control time-consuming operations.

    The aim of this class is to be able to interrupt certain time-consuming
    operations within the library. A time-consuming operation which is 
    parameterized with a VsJobControl object is supposed to call canceled()
    from time to time, in order to determine, whether someone requested
    the interruption of that operation. If canceled() returns true, the
    method performing the time-consuming operation is expected to return
    immediately (as fast as possible). The canellation state can be set
    by invoking VsJobControl::cancel().

    Moreover a time-consuming operation can inform the VsJobControl about
    the progress of the operation. Progress is reported by calling 
    progress() with a floating-point value between 0 and 1. An application
    must derive a class from VsJobControl in order to route the progress
    to some progress bar or similar.

    One example for using VsJobControl is the interruption of high-res
    renderings in the render thread.

    For example, the class VsJobControl is the base class for objects
    used to control a render-job performed on multiple VsObject instances.
    Before performing a render-job a renderer locks all VsNode objects and 
    hooks the same instance of this class to each of these objects. If another 
    thread wants to lock a hooked object, it will eventually invoke 
    VsJobControl::cancel() and the render job gets canceled. 
    The other thread gets the lock as fast as the renderer and its nodes
    cancel the current operation.
*/
class VSVOLREN_API VsJobControl 
:   public VsInterface
{
    VS_DECL_INTERFACE        ( VsJobControl )
    VS_DECL_INTERFACE_IMPL   ( VsJobControl )
//  VS_DECL_INTERFACE_FACTORY( VsJobControl )
//  VS_DECL_INTERFACE_RELAY  ( VsJobControl )

public:

    /** Cancels the current job.
    */
    virtual void cancel() = 0;

    /** Check if the current job was canceled.

        \return 
                \c True if cancel() was called, \c False if not.
    */
    virtual bool canceled() = 0;

    /** Report the progress of the current job. Progress is considered
        as floating point number in the range 0...1. Note that the method
        can also be used for checking, whether the job has been canceled.
        There is no need to call canceled() AND progress().
 
        \param  inProgress
                0...1
        \return 
                \c True if cancel() was called, \c False if not.
    */
    virtual bool progress( float inProgress )
    { 
        return canceled(); 
    }
};


#endif

/// @}
