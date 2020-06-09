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
#ifndef _VS_NODE_H_
#define _VS_NODE_H_


#include "Vs.h"

#include "VsObject.h"
#include "VsNodeState.h"

#include <mclib/McHandle.h>

class McBox3f;
class McMat4f;
template<typename T> class McDArray;

// VS_RELAY_CLASS VsNode VsObjectRelay
// VS_RELAY_EXPORT_CLASS VsNode VSVOLREN_API

/** Base class for nodes which can be rendered.

    All nodes derived from VsNode provide a render() method
    which assumes that an OpenGL context is active and which
    renders the object using OpenGL. The render() method of a
    VsNode object should completely restore the initial OpenGL
    state before it returns, except for the render target
    (color buffer, depth buffer, etc.) or the projection and
    model-view matrix in case of VsCamera.
    
    Each VsNode also provides a cleanup() method which is
    called in order to release all OpenGL resources like
    textures, buffer objects, or display lists. Like with
    render() the correct OpenGL context must be active for
    calling cleanup().

    It is not allowed to render a node into different OpenGL
    contexts, unless these contexts are shared or unless
    cleanup() has been called in-between.

    If you want to integrate a VsNode object in an existing
    OpenGL application, you probably want to call render()
    and cleanup() directly. Otherwise, you may want to group
    multiple nodes in a scene graph (see VsGroup) and render
    them using a VsRenderer object.
*/         
class VSVOLREN_API VsNode : public VsObject
{
    VS_DECL_INTERFACE        ( VsNode )
    VS_DECL_INTERFACE_IMPL   ( VsNode )
    VS_DECL_INTERFACE_FACTORY( VsNode )
    VS_DECL_INTERFACE_RELAY  ( VsNode )

public:

    /** Returns the 3D bounding box of the node. The default
        implementation returns an empty box by calling McBox3f::makeEmpty()
        on \c outBox. 
        \param  outBox
                The 3D bounding box will be returned in this parameter.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT boundingBox( McBox3f & outBox ) const; // LOCAL_GET

    /** Renders the object. The default implementation does nothing.
        Derived objects should implement rendering in OpenGL. When this
        method is called, a valid OpenGL rendering context must have been
        set and mcglSetContext() or mcglInitContext() must have been
        called. The render() method of a derived class must leave the
        OpenGL state unchanged, except for the render target (color buffer,
        depth buffer, etc.) or the projection and model-view matrix
        in case of VsCamera. The method returns a VsRenderResult. 

        In the render() method of derived objects canceled() should be
        called from time to time. If canceled() returns \c True, rendering
        should be stopped prematurely and RENDER_CANCELED should be returned.
        \return 
                See VsRenderResult.
    */
    virtual VsRenderResult render();

    /** Specifies the amount of time the node is allowed to consume 
        for rendering. The node is expected to return from the render()
        method within \c msec milliseconds. A render time of 0 indicates
        that the node should render with best-quality settings. Otherwise,
        it may reduce some quality settings in order to match the given
        time limit. Depending on whether the quality settings were
        reduced or not, the render() method should return
        RENDER_OK_LOW_QUALITY or just RENDER_OK.
        \param  msec
                Render time limit in milliseconds. If zero, there is no
                time limit.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
        \sa renderTime()
    */
    virtual VSRESULT setRenderTime( int msec ); // VS_RELAY

    /** Returns the current render time limit of this node.
        \return 
                Current render time limit in milliseconds. A value of zero
                indicates that there is no time limit.
        \sa setRenderTime()
    */
    virtual int renderTime(); // LOCAL_GET

    /** Frees all OpenGL recources allocated during rendering. When this
        method is called, the same OpenGL rendering context as for
        render() must have been set (or a shared one) and mcglSetContext()
        or mcglInitContext() must have been called. The default implementation
        does nothing. Derived objects should implement cleanup() in order
        to free resources acquired in render() and not released yet. 
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT cleanup();

    /** Sets the visibilty status of the node. With this method it
        is possible show or hide the node. If set to \c False, the
        render() method returns immediately without actually rendering.
        \param  inFlag
                If \c True, the node should be rendered. If \c False,
                it should not.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
        \sa visible()
    */
    VSRESULT setVisible( bool inFlag ); // VS_RELAY

    /** Returns the visibility status of the node.
        \return 
                \c True, if the node should be rendered, \c False if not.
        \sa setVisible()
    */
    bool visible() const; // LOCAL_GET

    /** \if UNDOCUMENTED
        Inserts handles to @c inScene and all subnodes into \c ioArray. 
        They are inserted in depth first order. 
        \param  ioArray
                
        \param  inLockNodes
        \param  inCancelCurrentOperation
        \param  VsJobControl
        \param  inWriteLock
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
        \endif
    */
    VSRESULT collectNodes( McDArray< McHandle<VsNode> > & ioArray, bool inLockNodes = false, bool inCancelCurrentOperation = true, VsJobControl * inLocker = 0, bool inWriteLock = true );

#ifndef HIDDEN_FROM_DOC
    /** Depricated: will be removed
   
        Returns the transformation of a scenes sub-node.
        The VsNode object the method is invoked on is considered as root 
        node of a scene graph. The method searches the VsNode object \c inNode 
        in that scene. If it is in the scene, the method computes the overall
        transformation from \c inNode to the scene's root node, which might
        involve the multiplication of several transformation matrices (one
        for each VsGroup along the path from \c inNode to the root node). 
        \param  inNode
                Node to search. If zero the method returns false.
        \param  outMatrix
                If the method returns \c True, the transformation gets stored in the
                referenced matrix object.
        \return 
                \c True, if the scene contains the node and the transformation is valid, \c False if not.
    */
    bool transformation( VsNode * inNode, McMat4f & outMatrix ); // LOCAL_GET
#endif

    /*
    */
    virtual void * extension( int, void * ); // ???



    /*  
    Some nodes can save their current state into a VsNodeState object.
    Internally rendering is then performed using those VsNodeState objects as input.

    By setting a toSave-FrameId to other than -1, one can trigger the node to safe its current 
    state into a cache with the frameID as a key when its render()-method is called.

    By setting a toRender-FrameId to other than -1, one can trigger the node to use the cached
    VsNodeState for that frameID for rendering.
    */
    static mcint64 frameIdToSave();
    static void    frameIdToSaveSet( mcint64 inId );

    static mcint64 frameIdToRender();
    static void    frameIdToRenderSet( mcint64 inId );

    VSRESULT         renderState( McHandle<VsNodeState> & outState, mcint64 inFrameIdToSave = -1, mcint64 inFrameIdToRender = -1 );
    VSRESULT         deleteState( mcint64 inFrameIdToDelete = -1 );
    virtual bool     renderStateSupported();
    virtual bool     sharedStateSupported(); // allows to share a state over consecutive frame ids, if they have the same touch number. 
                                             // should be disabled for nodes that are in the same time contained in different scenes. 
    virtual VSRESULT renderStateCreate( McHandle<VsNodeState> & outStateToRender );
};


#endif

/// @}
