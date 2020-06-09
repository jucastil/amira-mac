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
#ifndef _VS_VIEW_MANAGER_H_
#define _VS_VIEW_MANAGER_H_

#include "Vs.h"

#include "VsInteractionManager.h"

#include <mclib/McVec3f.h>


class VsCamera;


/** Provides viewer navigation via a virtual trackball.

    This class implements an arc-ball navigation similar to the
    Open Inventor SoExaminerViewer. In order to do so the view
    manager analyzes the events that are delivered by the various event processing
    methods and manipulates the camera of a connected VsRenderer object.
    A fixed input layout is used. This can be changed by overriding the 
    event processing methods.
    If there is no VsRenderer connected or the connected renderer has no camera,
    a separate instance of VsCamera is created and used. If the connected
    VsRenderer object gets a new camera by calling VsRenderer::setCamera()
    the class switches to this new camera object.
*/
class VSVOLREN_API VsViewManager : public VsInteractionManager
{
    VS_DECL_INTERFACE        ( VsViewManager )
    VS_DECL_INTERFACE_IMPL   ( VsViewManager )
//    VS_DECL_INTERFACE_FACTORY( VsViewManager )
//  VS_DECL_INTERFACE_RELAY  ( VsViewManager )

public:

    /** Standard camera transformation flags.
    */
    enum View 
    {
        /// Along the positive X-axis, Z is up
        VIEW_ZY             = 0,
        /// Along the positive Y-axis, X is up
        VIEW_XZ             = 1,
        /// Along the positive Z-axis, X is up
        VIEW_XY             = 2,
        /// Along the positive X-axis, Y is up
        VIEW_YZ             = 3,
        /// Along the negative X-axis, Y is up
        VIEW_YZ_FROM_BACK   = 4,
        /// Along the negative Y-axis, X is up
        VIEW_XZ_FROM_BACK   = 5,
        /// Along the negative Z-axis, X is up
        VIEW_XY_FROM_BACK   = 6
    };

    /** Moving the mouse may lead to one of this actions.
        Subclasses may define additional modes.
    */
    enum MouseMode
    {
        /// no mouse interaction mode active
        MM_NONE   = 0,
        /// move the object that it follows the mouse cursor
        MM_PAN    = 1,
        /// zoom the object by moving the mouse
        MM_DOLLY  = 2,
        /// rotate the object by moving the mouse
        MM_SPIN   = 3,
    };


public:

    /** Registers a VsRenderer with this view manager.
        The view manager always manipulates the renderers current camera
        even if it's set to another camera. If the renderer has no camera, 
        the view manager sets a new camera to the renderer.
        \param inRenderer The renderer to be controlled by the view manager.
        \return If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT setRenderer( VsRenderer * inRenderer );

    /** Enable/Disable rotation of the virtual trackball.
        The ability to rotate is sometimes not wanted. For example
        when rendering single volume slices that should always be aligned
        orthogonal to the view direction.
        \param  inFlag
                \c True to enable, \c False to disable.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT enableRotate( bool inFlag );

    /** Get current state of the rotation enabled switch.
        \return 
                \c True if enabled, \c False if disabled.
    */
    bool isRotateEnabled() const;

    /** Reset camera transformation to a predefined value.
        \param  inView
                One of the predefined camera transformation flags. 
                See VsViewManager::View for valid values.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT resetView( View inView );

    /** The preferred view is the view which has been specified with
        the last call of resetView().
        \return 
                One of the predefined camera transformation flags. 
                See VsViewManager::View for valid values.
                Default value is VsViewManager::VIEW_XY.
    */
    View preferredView() const;

    /** Up-direction of the current preferred view.
        \return 
                Up-direction.
    */
    McVec3f preferredUpDirection() const;

    /** Set camera that the current renderer's scene fits completely in the viewport 
        window from the current position. VsCamera::viewBoundingBox() is called from 
        within this method.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT viewAll();

    /** In case of orthogonal projections this sets the height of the view frustrum in a way
        that each rendered pixel spans a specific distance in object space.
        A result of this is that objects shown in the viewer do not shrink if 
        the viewer window is made smaller. Of course, as a compensation 
        the visible section of the object will get smaller.
        VsCamera::setHeight() gets called from inside this method.
        \param  inPixelHeight
                Distance in object space that gets covered by one pixel in vertical direction.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT setTrueScale( float inPixelHeight );

    /* Inherited from VsInteractionManager.
    */
    virtual bool processMouseEvent( Vs::MouseEvent inEvent, int inX, int inY, Vs::ButtonState inState );

protected:

    /** Moves the camera in the plane defined by the camera's forward vector
        and focal point. The camera will, thus, follow the new mouse location.

        \param  inX
                New horizontal mouse position in window coordinates.
        \param  inY
                New vertical mouse position in window coordinates.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT panCamera( int inX, int inY );

    /** Rotates the camera using the sheet sphere projector, given the new
        mouse location.

        \param  inX
                New horizontal mouse position in window coordinates.
        \param  inY
                New vertical mouse position in window coordinates.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT spinCamera( int inX, int inY );

    /** Moves the camera forward/backward based on the new mouse potion.
        This applies to a perspective camera only. In case of an orthographic
        camera, instead the camera height is changed leading to the same 
        visual effect.

        \param  inX
                New horizontal mouse position in window coordinates.
        \param  inY
                New vertical mouse position in window coordinates.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT dollyCamera( int inX, int inY );

    /** Get the current mouse mode.

        \return 
                Current mouse mode. See #MouseMode for valid values.
    */
    int mouseMode();

    /** Switch to the specified mouse mode.

        \param  inMode
                New mouse mode. See #MouseMode for valid values.
        \param  inX
                New horizontal mouse position in window coordinates.
        \param  inY
                New vertical mouse position in window coordinates.
    */
    virtual void switchMouseMode( int inMode, int inX, int inY );
};

#endif

/// @}
