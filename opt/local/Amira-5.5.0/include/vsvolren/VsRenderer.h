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
#ifndef VS_RENDERER_H
#define VS_RENDERER_H

#include "Vs.h"
#include "VsObject.h"

#include <mclib/McPrimType.h>
#include <mclib/McVec2i.h>
#include <mclib/McColor.h>

class VsCamera;
class VsInteractionManager;
class VsMemoryData;
class VsNode;
class VsRenderQueue;
class VsRenderQueue2;
class VsScene;

/** Abstract base class for rendering scene graph nodes. This
    class provides the infrastructure for asynchronous rendering
    of a scene graph consisting of VsNode objects. Asynchronous
    rendering means, that the rendering operations are performed
    in a separate thread. Rendering is started by calling
    startRendering() or startRenderingToBuffer(). A common
    scenario is to start rendering in the GUI thread, and then
    to return into the main loop in order to be able to process
    further events. You can wait for the rendering to complete
    by calling waitRendering(). This method takes an optional
    timeout argument. You can interrupt an ongoing rendering
    operation by calling cancelRendering().

    A rendering operation can be automatically interrupted if
    the render time argument in startRendering() and
    startRenderingToBuffer() was set to zero, indicating
    high-resolution best-quality render settings. During rendering 
    the objects of the scene graph will always be read-locked.
    If the render time argument was zero, and if a write-lock is
    requested for any scene graph node while rendering is going
    on, the rendering operation will be canceled, if possible.
    This happens automatically if a node is modified via some
    set-method. The return value of waitRendering() tells you
    if the rendering operation was canceled or not.

    Instead of calling startRendering() or waitRendering()
    manually, the renderer can also be connected to a render queue
    (see VsRenderQueue). If this is the case, then an interactive
    rendering request will be automatically scheduled whenever a node
    in the scene graph is modified. This is achieved by the observer
    mechanism implemented in VsObject. Once an interactive request
    has been completed, a high-resolution rendering request will be
    automatically scheduled next.

    While this abstract renderer class provides the full
    infrastructure for asynchronous rendering and synchronization,
    it does not create any window, render target or OpenGL
    context. This is supposed to be done in derived classes,
    which must implement at least the methods windowSize(),
    contextActivate(), and renderFrameEnd(), and possibly also
    initialize() and deinitialize().
*/
class VSVOLREN_API VsRenderer : public VsObject
{
    VS_DECL_INTERFACE        ( VsRenderer )
    VS_DECL_INTERFACE_IMPL   ( VsRenderer )
//  VS_DECL_INTERFACE_FACTORY( VsRenderer )
//  VS_DECL_INTERFACE_RELAY  ( VsRenderer )

public:

    /** Notification flags. \sa VsObject::TouchFlag */
    enum TouchFlag {
        /// Indicates that a new background color was set. 
        NEW_BACKGROUND_COLOR = 1<<1
    };

    /** Notification flags used by renderingRequired(). */
    enum RequiredFlag {
        /** Indicates that the scene graph has been modified after the
            last low-res image has been rendered. */
        LOWRES_REQUIRED = 1<<1,
        /** Indicates that the scene graph has been modified after the
            last high-res image has been rendered. */
        HIGHRES_REQUIRED = 1<<2
    };

    /// Enumeration type returned by waitRendering().
    enum WaitResult {
        /// Rendering finished while waitRendering() was waiting.
        WAIT_OK,
        /// No rendering was going on when waitRendering() was called.
        WAIT_NOP,
        /// Time limit exceeded in waitRendering().
        WAIT_TIME_OUT
    };

    /** Returns the size of the render area in pixels. This method
        must be implemented by a derived window-system specific class. 

        \return 
                The current size of the render area.
    */
    virtual McVec2i windowSize() const = 0;

    /** Returns the interaction manager associated with the renderer.
        Derived renderer classes should pass events received from the
        window system to the interaction manager, i.e. they should call
        the methods
        \link VsInteractionManager::processMouseEvent() processMouseEvent() \endlink,
        \link VsInteractionManager::processKeyEvent() processKeyEvent() \endlink, and
        \link VsInteractionManager::processWheelEvent() processWheelEvent() \endlink
        of the interactionManager() object.

        \return 
            Pointer to the associated interaction manager, or zero if
            no interaction manager has been set.
        \sa VsInteractionManager::setRenderer()
    */
    VsInteractionManager * interactionManager() const;

    /** Sets the camera used for rendering. On default, the renderer
        creates its own camera, i.e., a camera need not to be part of
        the scene graph. You may call this method if you want to use
        a custom camera.

        \param  inCam
            The new camera, may be zero.
        \return 
            If the method succeeds, the return value is #VS_OK. To get 
            extended error information, call Vs::lastError().
    */
    virtual VSRESULT setCamera( VsCamera * inCam ); // TO_BE_REMOVED - is now in VsScene

    /** Retrieves the camera used for rendering. The method either
        returns the renderer's default camera or the camera specified
        via setCamera().

        \return 
            Pointer to the current camera, or zero.
    */
    virtual VsCamera * camera() const; // TO_BE_REMOVED - is now in VsScene

    /** Sets the scene graph root. Usually the scene graph is a
        VsGroup object with multiple childs. However, a single node
        like VsVolren or VsSlice can also be specified. Since the
        renderer creates its own camera it is not required that the
        scene graph contains a VsCamera object.

        \param  inScene
            Node to be rendered, or zero for an empty scene.
        \return 
            If the method succeeds, the return value is #VS_OK. To get 
            extended error information, call Vs::lastError().
    */
    virtual VSRESULT setScene( VsNode * inScene, int sceneIdx=1 ); // TO_BE_REMOVED - is now in VsScene

    /** Returns the scene graph root. 

        \return 
            Pointer to the node to be rendered, or zero.
    */
    virtual VsNode * scene(int sceneIdx=1) const; // TO_BE_REMOVED - is now in VsScene

    /** Sets the background color of the render area. The background
        will be cleared by calling glClearColor() and glClear() in
        renderFrameBegin().

        \param  inColor
                Background color.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */ 
    virtual VSRESULT setBackgroundColor( const McColor & inColor ); // TO_BE_REMOVED - is now in VsScene

    /** Returns the background color of the render area. 
        \return 
                Current background color.
    */
    McColor backgroundColor() const; // TO_BE_REMOVED - is now in VsScene

    
    virtual VSRESULT setSceneDescription( VsScene * inScene ); // TO_BE_REMOVED   startRendering()
    virtual VsScene * sceneDescription() const; // TO_BE_REMOVED

    /** Checks if interactive rendering is enabled. The method returns
        \c true if setRenderTime() was called with a non-zero argument.
        Otherwise it returns false. 

        \return 
            \c True if a render time limit was set, \c false otherwise.
    */
    bool isInteractive() const;

    /** Starts asynchronous rendering. Rendering will be performed in a
        separate thread. Thus the method returns immediately. You can check
        whether rendering was completed by calling waitRendering(). A
        (derived) renderer may display the rendered image directly in a
        window or copy it into some offscreen buffer.

        A render time limit can be specified via \c inMSec. If a non-zero
        render time limit is specified, scene graph nodes may reduce some
        quality settings in order to meet the specified time. If the render
        time limit is zero, a high-quality image will be rendered. In this
        case rendering will be automatically interrupted if a \link
        VsObject::lock() write-lock \endlink is requested for any node in
        the scene graph. This is not the case for interactive rendering,
        where a \link VsObject::lock() write-lock \endlink request just
        waits until the rendering operation finished.

        If the renderer is controlled by a render queue (see VsRenderQueue)
        then there is no need to call startRendering() manually. Instead,
        the render queue automatically calls startRendering() whenever a
        scene graph node was modified.

        \param  inMSec
                Render time limit in milliseconds. If zero, render time is
                not limited and a high-quality image is generated.
        \return 
                If the rendering operation was successfully started #VS_OK
                is returned, otherwise #VS_FAILED is returned. This might
                be the case if rendering is still going on when this method
                is called. Thus, this class does not queue rendering requests.
                To get extended error information, call Vs::lastError().
    */
    virtual VSRESULT startRendering( unsigned int inMSec=0 );
    virtual VSRESULT startRendering( VsScene * inScene, unsigned int inMSec = 0, mcint64 inFrameId = -1 );

    /** Starts asynchronous rendering into a buffer. The method is similar
        to startRendering(), except that the rendered image will not be
        displayed in the renderer's window but will be copied into the
        specified memory buffer. You may call waitRendering() in order to
        check whether rendering has been completed or not.

        \param  outData
                Gets initialized and filled with the rendered image. Only
                a single xy-slice will be used. If zero, the method returns
                immediately. If outData already has the correct
                size and format, it gets re-used.
        \param  inMSec
                Render time limit in milliseconds. If zero, render time is
                not limited and a high-quality image is generated.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT startRenderingToBuffer( VsMemoryData * outData, unsigned int inMSec = 0, mcint64 inFrameId = -1 );

    /** Determines if the rendering context used by this renderer supports the 
        functionality required by the library. In order to do that, before 
        actual testing initialize() (if not already performed) and 
        contextActivate() get invoked in the thread also used for rendering.
        The actual test is performed by calling Vs::checkGraphics().

        \return 
                #VS_OK if the OpenGL context used by this renderer provides all features
                required for using the library. #VS_FAILED if not. In the latter case
                more detailed information can be acquired via Vs::lastError().
    */
    virtual VSRESULT checkGraphics() const;

    /** Cancels the current rendering operation. The method blocks
        until rendering really has been terminated. If the method is
        called while no rendering is going on, false is returned.

        \return 
            \c True if rendering was canceled, \c false if
            no rendering operation was going on.
    */
    bool cancelRendering();

    /** Wait until rendering is done. The method waits until rendering
        was completed. Once this happened it returns WAIT_OK. If there was
        no rendering operation taking place when entering the method,
        WAIT_NOP is returned. If the timeout specified in \c inTimeOutMSec
        exceeded, WAIT_TIME_OUT is returned. In any case, the result of
        the last rendering operation is returned in \c outRenderResult. 

        \param outRenderResult
                Result of the last rendering operation as returned by
                render().
        \param inTimeOutMSec
                Time-out in milliseconds. -1 means wait for ever, 0
                means do not wait at all.
        \return 
                See #WaitResult.
    */
    WaitResult waitRendering( VsRenderResult& outRenderResult, int inTimeOutMSec=-1 );

    /** Wait until rendering is done. This is an overloaded member function,
        provided for convenience. It essentially behaves like the above method,
        but does not return the result of the last rendering operation.

        \param inTimeOutMSec
                Time-out in milliseconds. -1 means wait for ever, 0
                means do not wait at all.
        \return 
                See #WaitResult.
        */
    WaitResult waitRendering( int inTimeOutMSec=-1 );

    /** Marks the renderer as modified. The method calls VsObject::touch().
        If a render queue has been specified via setRenderQueue(), a new
        render request is submitted to that queue. The method will be called
        automatically via VsObject::observedObjectTouched() whenever a child
        node is modified.

        \param inMask
            Bitwise combination of touch flags.
        \return
            Always #VS_OK.
    */
    virtual VSRESULT touch( unsigned int inMask=NEW_UNSPECIFIED );

    /** This method returns true if a new image needs to be rendered. This is
        the case if the renderer or any object in the renderer's scene graph
        has been modified after the last image has been rendered. Such a
        modification is detected in the renderer's touch() method.

        The mask argument lets you specifically check if a new low-res or
        a new high-res rendering is required, by passing in either
        LOWRES_REQUIRED or HIGHRES_REQUIRED. The LOWRES_REQUIRED flag is reset
        after a low-res image has been rendered, while the HIGHRES_REQUIRED
        flag is reset after a high-res image has been rendered.

        Note, that this method is not interpreted by the renderer itself.
        In particular, calling startRendering() starts rendering even if this
        method returns false. You may call renderingRequired() when using a
        renderer with a render queue (see VsRenderQueue).
        
        \param mask
           Bitwise combination of LOWRES_REQUIRED and HIGHRES_REQUIRED.
        \return
           True is a new image needs to be rendered, otherwise false.
    */
    bool renderingRequired(unsigned int mask=0xffff) const;

    /** Sets the render queue managing this renderer. The render queue is
        responsible for queueing and executing concurrent render requests from
        multiple renderers. It automatically calls startRendering() whenever
        some node of the scene graph was modified. Usually, you will just
        use the global default render queue returned by VsRenderQueue::instance(),
        i.e. you will call
        \code
             renderer->setRenderQueue(VsRenderQueue::instance());
        \endcode
        Note, that you need to repeatedly call VsRenderQueue::processNext()
        in a timer callback or in a separate thread in order to run the
        queue, as illustrated in the examples.

        \param  inQueue
                Pointer to the queue, an extra render thread is created at the next render pass. 
                Zero to shutdown extra render thread.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT setRenderQueue2( VsRenderQueue2 * inQueue );

    /** Returns the render queue associated with this renderer. If a render
        queue has been specified, there is no need to call
        startRendering() and waitRendering() directly. Instead simply
        VsRenderQueue::processNext() should be called in a timer callback
        or in a separate thread, as illustrated in the examples.
        \return 
                If non-zero, pointer to the current render queue.
    */
    VsRenderQueue2 * renderQueue2() const;

    /** Frees all recources allocated by the given node. In particular, OpenGL
        resources such as buffers, texture objects or display lists allocated during
        previous rendering operations are freed. The method calls cleanUpNodeInternal()
        in the render thread and blocks the calling thread until the cleanup
        is performed.
        \param  ioNode
                Node to cleanup. If zero, the method returns immediately.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT cleanUpNode( VsNode * ioNode );

    /** Terminates rendering and frees all resources. Use this method for cleanup.
        The method waits for the current rendering operation to finish. It then
        calls deInitialize() in the thread that performes the rendering. Do not
        call this method if you just want to cancel the current rendering operation.
        Instead, use cancelRendering() then.
        \return 
            If the method succeeds, the return value is #VS_OK. To get 
            extended error information, call Vs::lastError().
    */
    VSRESULT terminateRendering();

    /** Activates or deactivates the renderer. If the renderer is deactivated,
        it will not render anything if startRendering() or startRenderingToBuffer()
        is called. Sometimes you might want to deactivate a derived renderer
        until all windows are properly initialized. On default, the renderer
        is activated.
        \param inValue
            Specifies whether to activate or deactivate the renderer.
    */
    void setActive(bool inValue);

    /** Returns whether the renderer is activated or not.
        \return \c True if the renderer is activated, \c false otherwise.
        \sa setActive
    */
    bool isActive() const;


    void setFrameId( mcint64 inFrameId );
    
    mcint64 frameId();


protected:
    
    /** Sets the requested render time. Derived classes may overload
        this method and adjust the parameters of the nodes to be
        rendered in order to meet the requested render time. A value
        of 0 for \c inMSec denotes non-interactive rendering. 

        \param  inMSec
                Render time limit in milliseconds, 0 for unlimited render time.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT setRenderTime( int inMSec );

    /** Checks if rendering is really required. Default implementation returns
        true.
        */
    virtual bool checkRenderingRequired();

    /** Sets the OpenGL rendering context. The method is called in the render
        thread before render() and cleanUpNodeInternal(). Derived class should
        implement this method in order to prepare for OpenGL rendering. Usually
        at least wglMakeCurrent() (on Windows) or glXMakeCurrent() (on Linux)
        will be called.

        \return 
                If the method succeeds, the return value is #VS_OK. If no OpenGL
                rendering context could be set, #VS_FAILED is returned. In this
                case render() or cleanUpNodeInternal() will not be called. To get 
                extended error information, call Vs::lastError().
    */
#ifdef HX_OS_MACX
    virtual VSRESULT contextActivate() {};
#else
	virtual VSRESULT contextActivate() = 0;
#endif
    /** This function can be overloaded by derived classes and used to perform
        pre-rendering tasks. The method gets executed in the same thread where 
        startRendering() or startRenderingToBuffer() is called from just before 
        the rendering process in the extra rendering thread begins.
        It's usually bad to perform state-changing operations in the render thread.
        If the applications render process requires such operations, this 
        method is a good place for it.
    */
    virtual VSRESULT renderPrepare();

    /** Called just before render() is called. If it returns not #VS_OK, the
        calls to render() and renderFrameEnd() are skipped. 

        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT renderFrameBegin();

    /** Renders the scene. The method is called in the render thread.
        Do not call this method directly to render the scene. Instead,
        use startRendering(), startRenderingToBuffer() or
        VsRenderQueue::processNext(), if a render queue has been set
        via setRenderQueue().

        This method is called after contextActivate() and after
        renderFrameBegin(). The method returns a VsRenderResult
        indicating the result of the rendering operation.

        \return 
            VS_RENDER_OK is returned if the \link VsNode::render()
            render() \endlink methods of all nodes in the scene
            graph returned VS_RENDER_OK.

            VS_RENDER_OK_LOW_QUALITY is returned if the \link
            VsNode::render() render() \endlink method of at least one
            node in the scene graph returned VS_RENDER_OK_LOW_QUALITY,
            while all other nodes either also returned
            VS_RENDER_OK_LOW_QUALITY or VS_RENDER_OK.

            VS_RENDER_CANCELED is returned if rendering was
            canceled via cancelRendering(). Note, that if rendering
            was started with a zero render time limit, cancelRendering()
            might be called automatically if a write-lock is requested
            for any VsNode object in the scene graph.

            VS_RENDER_FAILED is returned if the \link VsNode::render()
            render() \endlink method of any node in the scene graph
            returned VS_RENDER_FAILED.
    */
    virtual VsRenderResult render();

    /** Called just after render() was called. Derived classes must
        override this method in order to display the rendered image
        or to save it in an offscreen buffer. Usually SwapBuffers (on
        Windows) or glXSwapBuffers() (on Linux) will be called.
        
        \param  inResultFromRender
                Result returned by the preceeding render() call. The method
                will also be called if render() returned VS_RENDER_FAILED
                or VS_RENDER_CANCELED.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
#ifndef HX_OS_MACX
    virtual VSRESULT renderFrameEnd( VsRenderResult inResultFromRender ) = 0;
#else
    virtual VSRESULT renderFrameEnd( VsRenderResult inResultFromRender )  { return VS_OK; }
#endif
    /** Get the current snapshot buffer. If non-zero, the method startRenderingToBuffer() 
        was invoked and a snapshot needs to be taken.
        The snapshot buffer is set by calling startRenderingToBuffer().
        Call this method in the implementations of methods like contextActivate(), 
        renderFrameBegin(), renderFrameEnd() or render() 
        to ask if they are invoked for to-buffer rendering or not.

        \return 
                If non-zero, pointer to the VsMemoryData object that receives the snapshot.
    */
    VsMemoryData * snapshotBuffer();

    /** Set the number of data channels the application expects in a snapshot buffer
        if the snapshot is a color image. 
        Currently supported are 3 which means BGR data and 4 for BGRA data.

        \param  inNum
                Number of data channels in the snapshot for color images.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT setNumSnapshotChannelsColor(int inNum);

    /** Set the number of data channels the application expects in a snapshot buffer
        if the snapshot is a gray scale image. 
        Currently supported are 1 which means luminance data, 3 for BGR data and 4 for BGRA data.

        \param  inNum
                Number of data channels in the snapshot for grayscale images.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT setNumSnapshotChannelsGrayScale(int inNum);

    /** Get the number of expected data channels in the snapshots
        if the snapshot is a color image. 
        \return
                 Number of data channels.
    */
    int numSnapshotChannelsColor() const;

    /** Get the number of expected data channels in the snapshots
        if the snapshot is a gray scale image. 
        \return
                 Number of data channels.
    */
    int numSnapshotChannelsGrayScale() const;

    /** This method is called in the same thread in which the rendering
        will take place. It's called once before any rendering is performed and
        intended for initialization of the render context and any stuff
        that need to be initialized in the render thread. The default implementation
        does nothing.

        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT initialize();

    /** This method is called in the same thread in which the rendering took place. 
        It's called once when no further rendering is performed and the API dependent resources
        have to be released. This method is the counterpart of initialize(). The default 
        implementation calls contextActivate() and VsNode::cleanup() on all nodes of the scene.

        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT deInitialize();

    /** Automatically called in the render thread in order to call VsNode::cleanup() on the given node.
        contextActivate() is automatically called before.
        Derived classes may override this method to perform additional setup operation necessary
        to cleanup a node. The default implementation just calls VsNode::cleanup(). 

        \param  ioNode
                The node that needs to be cleaned up.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT cleanUpNodeInternal( VsNode * ioNode );

    /** This method is called when rendering of a frame is finished. Derived classes
        should implement this method and notify the main thread to call
        VsRenderQueue::processNext(). When this method is called and
        interactive rendering was enabled, a new request for non-interactive
        rendering has already been submitted to the render queue.

        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT renderFinished();

    void wakeCaller();
};

#endif

/// @}
