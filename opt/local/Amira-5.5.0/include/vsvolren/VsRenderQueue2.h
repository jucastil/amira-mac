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
#ifndef _VS_RENDER_QUEUE2_H_
#define _VS_RENDER_QUEUE2_H_

#include "Vs.h"

#include "VsInterface.h"
#include "VsHandable.h"

#include <mclib/McPrimType.h>

class VsRenderer;
class VsScene;

/** Controller class responsible for managing redraw requests.

    The class VsRenderQueue2 processes multiple render requests one
    after another. There should be one render queue per GPU on a system. 
    Multiple renderers should not use the same GPU simultaneously in order
    to avoid texture trashing. Instead, render requests should be submitted 
    to a render queue. There are two types of requests, interactive
    and non-interactive ones. Interactive request have priority,
    i.e. if an interactive request is submitted while a non-interactive
    render request is being processed, the non-interactive job is 
    suspended and the interactive job is executed instead. The
    non-interactive job is resumed later.
*/

class VSVOLREN_API VsRenderQueue2
:   public VsInterface
{
    VS_DECL_INTERFACE        ( VsRenderQueue2 )
    VS_DECL_INTERFACE_IMPL   ( VsRenderQueue2 )
    // VS_DECL_INTERFACE_FACTORY( VsRenderQueue2 )

public:

    /** Submits a render request to the queue. The parameter \c inInteractive
        indicates whether this is an interative request or not. The method
        is thread-safe. It may be called from any thread at any time. It
        just adds the request to the queue and removes any previous requests
        for the same renderer from the queue. It does not block or cancel
        the current request or execute the next request. Instead,
        this is triggered by calling processNext(). 
        \param  inRenderer
                Renderer that is requested to re-render.
        \param  inInteractive
                If \c True, the render request is marked as interactive for 
                generating higher framerates with less respect to quality.
                If \c False, the render request is non-interactive for 
                generating high quality images.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT submitRequest( VsScene * inScene, bool inInteractive = true, mcint64 inFrameId = -1, int inUserData = 0 );

    VSRESULT removeRequests( VsScene * inScene );
    VSRESULT removeRequests( VsRenderer * inRenderer );

    /** Sets a preferred renderer. If an interactive job for this renderer
        is in the queue, and since the last time the renderer was invoked more
        than 200ms have elapsed, this job is chosen.
        \param  inRenderer
                Renderer that is the preferred renderer. May be 0, in case
                no preferred renderer is used.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT setPreferredRenderer( VsRenderer * inRenderer );

    /** Returns the preferred renderer.
        \return 
            Pointer to the preferred render, or zero if no preferred renderer
            has been set.
    */
    VsRenderer * preferredRenderer() const;

    /** Processes the next request for all render queues. This method must
        only be called from the main thread. It checks if a render request
        is pending. If this is the case and if no render request is currently
        being processed, rendering is started. If a non-interactive rendering
        is currently being processed and if there is an interactive request
        in the queue, the non-interactive job is suspended and the interactive
        job is started. 
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    static VSRESULT processNext();
    
    /*  Process all requests with the given frameId.
        Render all of them.
        The function blocks until all requests are rendered.
    */
    static VSRESULT processFrame( mcint64 inFrameId );


    /** Returns a pointer to a render queue associated whith a particular
        GPU. It is assumed that the GPUs are identified by a uniqe device id.
        The render queue does not actually communicate with the hardware. 
        \param  inDeviceId
                Identifier of the requested queue.
        \return 
                Pointer to the requested queue instance. Zero on failure.
                To get extended error information, call Vs::lastError().
    */
    static VsRenderQueue2 * instance( int inDeviceId = 0 );

    /** Terminates the render queue. Running rendering activities will 
        be canceled. No further render requests are accepted.
        This method should be called on program end. The method does not
        trigger any cleanup calls to any VsRenderer object. VsRenderer objects
        must be terminated separately.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT terminate();

    /** Returns the number of pending requests. The request currently
        being rendered is not counted. */
    int numPendingRequests() const;

    /** Processes all interactive jobs in the render queue. 
        The thread will be blocked until not contains interactive jobs any more. 
    */
    VSRESULT processAllInteractive();


    void print();
};



#endif

/// @}
