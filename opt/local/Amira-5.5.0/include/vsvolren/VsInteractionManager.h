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
#ifndef _VS_INTERACTION_MANAGER_H_
#define _VS_INTERACTION_MANAGER_H_

#include "Vs.h"

#include "VsObject.h"

#include <mclib/McVec2i.h>

#if defined(WIN32) || defined(WIN64)
#include <windows.h>
#endif

class VsCamera;
class VsRenderer;

#ifdef CursorShape
#undef CursorShape
#endif


/** Base class for handling user interaction. An instance of
    VsInteractionManager is registered with a VsRenderer
    object. The render area manages the graphics window and
    receives events from the window system. The events are
    forwarded to the interaction manager. The interaction manager
    interpretes the events and updates the nodes of the renderer.
    In order to do so, the interaction manager usually
    requires that the renderer's scene graph has a certain layout,
    i.e., it must know the nodes which can be manipulated
    interactively.
*/
class VSVOLREN_API VsInteractionManager : public VsObject
{
    VS_DECL_INTERFACE        ( VsInteractionManager )
    VS_DECL_INTERFACE_IMPL   ( VsInteractionManager )
//    VS_DECL_INTERFACE_FACTORY( VsInteractionManager )
//    VS_DECL_INTERFACE_RELAY  ( VsInteractionManager )
    
public:

    /// Available cursor shapes.
    enum CursorShape
    {
        /// Arrow cursor
        ArrowCursor,
        /// Forbidden cursor
        ForbiddenCursor,
        /// Wait cursor
        WaitCursor,
        /// Cursor for horizontal resize
        SizeHorCursor,
        /// Cursor for vertical resize
        SizeVerCursor,
        /// Cursor for resize in either direction
        SizeAllCursor,
        /// Seek cursor
        SeekCursor,
        /// Rotate cursor
        RotateCursor,
        /// Cursor showing a curved hand
        CurvedHandCursor,
        /// Cursor showing a flat hand
        FlatHandCursor,
        /// Cursor showing a pointing hand
        PointingHandCursor,
        /// Cross cursor
        CrossCursor,
        /// Cursor for measuring
        MeasureCursor,
        /// Cursor for contrast modification
        ContrastCursor,
        /// Cursor showing a camera
        CameraCursor,
        /// Cursor used for scrolling
        ScrollCursor,
        /// Cursor used for annotation
        AnnotationCursor,
        /// Cursor for magic wand tool
        MagicWandCursor,
        /// Cursor showing a pencil
        PencilCursor,
        /// Delete cursor
        DeleteCursor
    };

    /** Registers a VsRenderer with this interaction manager.
        A previously registered VsRenderer gets disconnected.
        \param  inRenderer
                Pointer to the renderer to associate with this interaction manager. 
                Zero to disconnect old renderer only.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT setRenderer( VsRenderer * inRenderer );

    /** Returns the renderer the interaction manager is attached
        to. In order to attach the interaction manager to a
        particular renderer call the setRenderer() method.
        \return 
                If non-zero, currently attached VsRenderer object.
                Zero if no VsRenderer is attached yet.
    */
    VsRenderer * renderer() const;

    /** Get the current camera.
        If a VsRenderer was set by calling setRenderer(), this is the same camera that 
        is returned by VsRenderer::camera(). If the connected renderer has no camera, 
        the view manager creates one and sets it on the VsRenderer. If there is no 
        VsRenderer connected the interaction manager also creates a camera inside this
        method.
        \return 
                The current camera. Always non-zero.
    */
    VsCamera * camera();

    /** Called by the renderer when the window size changes. Also updates the 
        aspect ratio of the camera. 
        \param  inWindowSize
                New viewport size.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    virtual VSRESULT setWindowSize( const McVec2i & inWindowSize );

    /** Get current window size. 
        \return 
                Current viewport size.
                Default value is 0,0.
    */
    McVec2i windowSize() const;

    /** Called by the renderer when the window size changes. 
        \param  inScreenSize
                New screen size.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    virtual VSRESULT setScreenSize( const McVec2i & inScreenSize );

    /** Get current screen size. 
        \return 
                Current screen size.
                Default value is 0,0.
    */
    McVec2i screenSize() const;

    /** Set new cursor shape. 
        \param  inShape
                New cursor shape. See VsInteractionManager::CursorShape
                for valid values.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    virtual VSRESULT setCursorShape( CursorShape inShape );

    /** Get current cursor shape. 
        \return 
                See VsInteractionManager::CursorShape for valid values.
                Default value is VsInteractionManager::ArrowCursor.
    */
    CursorShape cursorShape();

    /** Interpretes mouse events and performs some action based
        on it. This method can be overloaded by derived classes.
        The default implementation does nothing.

        \param  inEvent
                See Vs::MouseEvent for valid values.
        \param  inX
                Current mouse cursor horizontal position in viewport coordinates.
        \param  inY
                Current mouse cursor vertical position in viewport coordinates.
        \param  inState
                Bitfield with the current state of the modifier buttons. See Vs::ButtonState for valid values.
        \return
                \c True if the event was handled by this method, \c false if not.
    */
    virtual bool processMouseEvent( Vs::MouseEvent inEvent, int inX, int inY, Vs::ButtonState inState );

    /** Interpretes mouse events and performs some action based
        on it. This method can be overloaded by derived classes.
        The default implementation does nothing.

        \param  inEvent
                What happened with the key. See Vs::KeyEvent for valid values.
        \param  inKey
                Key that triggered the event. See Vs::Key for valid values.
        \param  inState
                Bitfield with the current state of the modifier buttons. See Vs::ButtonState for valid values.
        \return
                \c True if the event was handled by this method, \c false if not.
    */
    virtual bool processKeyEvent( Vs::KeyEvent inEvent, Vs::Key inKey, Vs::ButtonState inState );

    /** Interpretes mouse wheel events and performs some action based
        on it. This method can be overloaded by derived classes.
        The default implementation does nothing.

        \param  inX
                Current mouse cursor horizontal position in viewport coordinates.
        \param  inY
                Current mouse cursor vertical position in viewport coordinates.
        \param  inDelta
                The distance that the wheel is rotated expressed in multiples or 
                divisions of 120. A positive value indicates that the wheel was 
                rotated forwards away from the user, a negative value indicates 
                that the wheel was rotated backwards toward the user.
        \param  inState
                Bitfield with the current state of the modifier buttons. See Vs::ButtonState for valid values.
        \return
                \c True if the event was handled by this method, \c false if not.
    */
    virtual bool processWheelEvent( int inX, int inY, int inDelta, Vs::ButtonState inState );

#if defined(WIN32) || defined(WIN64)

    /** Convenience method for event processing (Windows only). This
        method takes a raw Windows message, converts it's and calls
        one of the methods processMouseEvent(), processKeyEvent(), or
        processWheelEvent() defined above.

        \param  inHwnd
                Handle to the window. 
        \param  inUMsg
                Specifies the message. 
        \param  inWParam
                Specifies additional message information. The contents of this parameter depend on the value of the inUMsg parameter. 
        \param  inLParam
                Specifies additional message information. The contents of this parameter depend on the value of the inUMsg parameter. 
        \return
            Result of the message processing. Depending on the message sent.
    */
    LRESULT processEvent( HWND inHwnd, UINT inUMsg, WPARAM inWParam, LPARAM inLParam );

#endif

};


#endif

/// @}
