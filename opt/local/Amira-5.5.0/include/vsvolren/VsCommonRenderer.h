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
#ifndef VS_COMMON_RENDERER_H
#define VS_COMMON_RENDERER_H

#include "VsRenderer.h"
#include <mclib/McPrimType.h>

/** This class implements a real renderer. The renderer can either
    be used as an offscreen renderer (by not creating a window but just
    calling setOffscreenEnable()), or as a standard renderer for
    rendering into a window. The window is created via createWindow().
    Even in this case, an offscreen-render target can be activated.
    The final image will then be automatically copied from the offscreen
    buffer into the window. Using an offscreen render target has the
    advantage that possibly a device (graphics card) different from
    the one the output window is displayed on can be used for rendering
    (currently this is only supported on Linux/X11 by calling one of
    the setOffscreenDisplay() methods). Also, an offscreen render target
    allows high-dynamic range rendering, i.e., rendering into a 16-bit
    floating point RGBA render target.

    If the renderer is used as a pure offscreen renderer without a
    window, rendering should be started using startRenderingToBuffer().
    Otherwise, startRendering() should be called. In order to detect if
    rendering is completed, in both cases waitRendering() can be called.

    The constructor does not actually create a render target or a window. 
    After creating the renderer thus you should either call createWindow(), 
    attachWindow() and/or setOffscreenEnable().

    If an offscreen render target has been created, it will be deleted in the
    destructor. OpenGL resources of any nodes of the renderer's scene graph will 
    be cleaned up from inside the render thread in the destructor of VsRenderer.
    If multiple instances of VsCommonRenderer are created the OpenGL rendering
    contexts of all will be shared, provided this is possible, i.e., provided
    all render targets are created on the same graphics device.
*/

class VsTexturedPolygon;

class VSVOLREN_API VsCommonRenderer : public VsRenderer
{
    VS_DECL_INTERFACE        ( VsCommonRenderer )
    VS_DECL_INTERFACE_IMPL   ( VsCommonRenderer )
//  VS_DECL_INTERFACE_FACTORY( VsCommonRenderer )
//  VS_DECL_INTERFACE_RELAY  ( VsCommonRenderer ) 

public:

    /** Returns a pointer to the renderer's native window. The renderer's
        native window is the window attached via attachWindow() (Windows only)
        or the window created via createWindow().

        \return Pointer to the renderer's native window. On Windows the
            return value is of type \c HWND, on Linux it is of type \c Window.
    */
    VsVoidHandle window() const;

    /** Returns the size of the renderer's window. If the renderer has no
        window, for example because it is used as an offscreen renderer,
        McVec2i(0,0) is returned.

        \return Size of the renderer's window in pixels.
    */
    McVec2i windowSize() const;

    /** Sets the size of the offscreen buffer. This size is used if offscreen
        rendering is enabled via setOffscreenEnable(). If the offscreen size
        is McVec2i(-1,-1), windowSize() will be used for offscreen rendering.
        This is the default. Enabling offscreen rendering and choosing the
        size of the offscreen buffer to be smaller than the window size results
        in some viewport scaling. This might be useful to influence rendering
        performance.

        \param  inOffscreenSize New dimensions for offscreen buffer.
        \return 
	    If the method succeeds, the return value is #VS_OK. To get
	    extended error information, call Vs::lastError().
    */
    VSRESULT setOffscreenSize( const McVec2i & inOffscreenSize );

    /** Returns the size of the offscreen buffer.
    
        \return Size of the offscreen buffer as set with setOffscreenSize().
    */
    McVec2i offscreenSize() const;
    

    /** Returns the size of the render target which ist the window size on non-offscreen rendering
        and the offscreen size on offscreen rendering. If the offscreen size is bound to the window size
        by setting it to (-1,-1) the window size is also returned.
    
        \return Size of the offscreen buffer as set with setOffscreenSize().
    */
    McVec2i targetSize() const;


    /** Enable or disable offscreen rendering. If enabled, the renderer will
        render into an offscreen render target. If the renderer has a window
        (see attachWindow() and createWindow()), the rendered image will be
        automatically copied into that window. Using offscreen rendering has
        the advantage, that blending is done in high-resolution (16-bit),
        provided this is supported by the graphics board.

        \param  inFlag If \c True offscreen rendering is enabled.
        \return 
	    If the method succeeds, the return value is #VS_OK. To get
	    extended error information, call Vs::lastError().
    */
    VSRESULT setOffscreenEnable( bool inFlag );

    /** Returns true if the OpenGL driver supports offscreen rendering (i.e., 
        has PBuffer support. Else returns false, in case you can't enable
        offscreen rendering. The result of this function can only be trusted
        after you already have activated the context of the renderer once.
    */   
    virtual bool offscreenSupported();

    /** Checks if offscreen rendering is enabled or not.

        \return \c True if offscreen rendering has been enabled via
            setOffscreenEnable(), \c false otherwise.
    */
    bool offscreenEnabled() const;


#ifdef HX_OS_MACX
    /** Attaches an OpenGL graphics context to a existing widgets HIView (Mac version).
        
        \param  inWindow the HIViewRef which can be obtained by winId() of a QWidget.
        \param  Vs_OK on success else VS_FAILDED
    */
    VSRESULT attachWindow( VsVoidHandle inWindow );
	
    /** Returns the renderers context 
		
        \return Renderers own AGLContext
    */
    VsVoidHandle getContext();
#endif

#ifdef HX_HAS_X11
    /** Creates an OpenGL graphics window (Linux version). The window will
        be created using an RGBA double-buffered visual.
        
        \param inDisplay Display of the parent window.
        \param inParentWindow Parent window of the graphics window to be created.
        \return Pointer to the newly created window. This is of type \c Window.
    */
    VsVoidHandle createWindow( VsVoidHandle inDisplay, VsVoidHandle inParentWindow );

    /** Specifies the display used for offscreen rendering (Linux only). On
        default, an offscreen buffer will be opened on the same display
        as the renderer's native window, i.e., on the display specified
        in createWindow(). With this method it is possible to specify
        an alternative display for the offscreen buffer. For example, you
        may want to use the local hardware-accelerated display ":0.0"
        for (offscreen) rendering, while the actual window together with
        the rest of the application is displayed on a remote display.
        If a separate offscreen display is used, the OpenGL rendering
        context of the renderer will not be shared with rendering contexts
        of other renderers anymore.

        \param inDisplay Display used for the offscreen buffer, e.g., ":0.0".
        \return If the method succeeds, the return value is #VS_OK. If no
            connection to the specified device could be opened, the return
            value is #VS_FAILED.
    */
    VSRESULT setOffscreenDisplay(const char* inDisplay);

    /** Specifies the display used for offscreen rendering (Linux only). This
        method essentially behaves as the above method. The only difference
        is that a pointer to an already opened X11 connection is specified.
        The connection is left open if the renderer is deleted.

        \param inDisplay Pointer to an opened X11 display. Should be of type
            \c Display*.
        \param inScreen Screen number of the display to be used.
        \return If the method succeeds, the return value is #VS_OK.
            To get extended error information, call Vs::lastError().
    */
    VSRESULT setOffscreenDisplay(VsVoidHandle inDisplay, int inScreen);
#endif

#ifdef HX_OS_WIN
    /** Creates an OpenGL graphics window (Windows version). The window will
        be created using an RGBA double-buffered visual.
      
        \param inParentWindow Parent window of the graphics window to be created.
            If 0, the graphics window will be created as a top-level window.
        \return Pointer to the newly created window. This is of type \c HWND.
    */
    VsVoidHandle createWindow( VsVoidHandle inParentWindow=0 );
    
    /** Attaches the renderer to an existing window (Windows only). This
        method can be used if an existing window should be used for OpenGL
        rendering. The method will call SetPixelFormat() on the existing
        window, trying to activate an RGBA double-buffered visual. Depending
        on the particular GUI toolkit it might be easier or more efficient
        to attach the renderer to an existing window rather than creating
        a new window via createWindow().

        \param inWindow Window to be used as the renderer's native window.
            This should be of type \c HWND.
        \param inReplaceMsgProc If \c true, the windows message procedure
            will be replaced. The new message procedure will automatically
            delegate events to a VsInteractionManager, provided that the 
            renderer has been registered via VsInteractionManager::setRenderer().
        \param inUseOpenGL Indicates if OpenGL rendering should be used or not.
            If true, SetPixelFormat() will be called for the input window.
        \param inCreateOpenGLContext If set and if inUseOpenGL is set an OpenGL
            context will be created by this method. Otherwise the context
            will be created when the first image is rendered. Usually this
            happens not in the main thread but in a separate render thread.
            In this case context sharing might fail, see setContextForSharing().
        \return If the method succeeds, the return value is #VS_OK.
            To get extended error information, call Vs::lastError().
    */
    VSRESULT attachWindow( VsVoidHandle inWindow, bool inReplaceMsgProc=true,
        bool inUseOpenGL=true, bool inCreateOpenGLContext=false );

    /** Detaches the renderer from an existing window (Windows only). This
        method can be called to detach the renderer from a window which has
        been attached via attachWindow(). If the window's message procedure
        has been replaced in attachWindow(), the old procedure will be
        restored in detachWindow().

        \return If the method succeeds, the return value is #VS_OK.
            To get extended error information, call Vs::lastError().
    */
    VSRESULT detachWindow();
#endif

    /** Sets an OpenGL rendering context with which to share display lists. 
        If set all OpenGL contexts created in vsvolren will be shared with this
        context specified here. */
    static VSRESULT setContextForSharing(VsVoidHandle contextForSharing);

    /** Returns the OpenGL context with which to share display lists. The
        method returns 0 if no such context has been set. */
    static VsVoidHandle contextForSharing();

protected:


    virtual VSRESULT initialize();
    virtual VSRESULT deInitialize();

    virtual VSRESULT contextActivate();

    virtual VSRESULT renderFrameBegin();
    virtual VSRESULT renderFrameEnd( VsRenderResult inResultFromRender );

    // invoked from renderFrameBegin()
    virtual void renderBackgroundImage();
    virtual void updatePendingUpdateStatus(mcint64 frameId);
    virtual bool pendingUpdate() const;
    
    /** Called by VsRenderer before the render thread will be started. 
        This is the right place to implement things which should run in the same thread,
        before the rendering thread starts.
    */
    virtual VSRESULT renderPrepare();

    static void renderAspectCorrectedBackground(VsTexturedPolygon*, const McVec2i& viewportSize, const McVec2i& textureSize);

};

#endif

/// @}
