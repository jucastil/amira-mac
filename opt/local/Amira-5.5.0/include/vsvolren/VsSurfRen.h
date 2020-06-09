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
#ifndef _VS_SURFREN_H
#define _VS_SURFREN_H

#include "Vs.h"

#include "VsSurface.h"
#include "VsNode.h"

#include <mclib/McColor.h>


// VS_RELAY_CLASS VsSurfRen VsNodeRelay


/** Implements rendering of a polygonal surface.

    In order to render a polygonal surface you need to create an instance
    of VsSurfRen, pass in your surface data via setSurface() and set 
    parameters such as color, material, texture etc. Afterwards you may 
    directly call the \link VsNode::render() render() \endlink method with 
    an existing OpenGL context, or you may create a renderer derived from
    VsRenderer and pass in the VsSurfRen node as part of a scene-graph.

    Multiple surfaces can be handled by a single instance of VsSurface.

\if UNDOCUMENTED
    TODO:
    =====
    (DONE) - multiple patches per surface (each with its own color)
    (DONE) - switch on/off patches
    (DONE) - transformation
    (DONE) - bounding box
    - transparent patches (later)
    - rendering: shaded with vertex normals and single INDIVIDUAL color per patch
    - load/save (only externally e.g. in Examine)
    - performance: VBO - strips
\endif
*/
class VSVOLREN_API VsSurfRen : public VsNode
{   
    VS_DECL_INTERFACE        ( VsSurfRen )
    VS_DECL_INTERFACE_IMPL   ( VsSurfRen )
    VS_DECL_INTERFACE_FACTORY( VsSurfRen )
    VS_DECL_INTERFACE_RELAY  ( VsSurfRen )
    
public:

    /// Notifications flags. See VsObject::TouchFlag for details.
    enum TouchFlag
    {
        /// Set if a new input surface was set or the input surface was changed.
        NEW_SURFACE     = 1<<1,
        /// Set if a new slave node is set or the slave node has changed
        NEW_SLAVENODE   = 1<<2
    };

    /// The order in which the slave node and the surface node are beeing composited
    enum SlaveSorting
    {
        /// The slave node is rendered after the surface node
        SURFACE_FIRST = 1,
        /// The slave node is rendered before the surface node
        SLAVE_FIRST   = 2,
        /// Slave node and surface are beeing intermixed to mimic depth correct alpha compositing
        COMPOSITE     = 3
    };

    ////////////////////////////////////////
    // own methods
    ////////////////////////////////////////

    /** Sets a surface to be rendered.
        \param  inSurface
                Surface to be rendered.
        \param  inIndex
                An index for the surface.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT setSurface( VsSurface * inSurface, int inIndex = 0 ); // VS_RELAY

    /** Returns the current suface.
        \param  inIndex
                The index of the surface.
        \return 
                Current surface. Null if there is none.
    */
    virtual VsSurface * surface( int inIndex = 0 ) const; // VS_LOCAL_GET

    /** Returns the number of attached surfaces
        \return
                Number of surfaces.
    */
    virtual int numSurfaces() const; // VS_LOCAL_GET

    /** Clears the list of attached surfaces.
        \return
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT clearSurfaces(); // VS_RELAY

    /** Show or hide a surface.
        With this method one can enable or disable rendering of a surface in 
        this VsSurfRen node.
        \param  inFlag
                Set to \c True to enable rendering for the surface indexed by
                \c inIndex.
        \param  inIndex
                Index of the surface for which the flag should be set.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT setSurfaceVisible( bool inFlag, int inIndex = 0 ); // VS_RELAY

    /** Get visibility status of a surface.
        With this method one can query if rendering of a surface is enabled.
        \param  inIndex
                Index of the surface the flag is queried from.
        \return 
                True if surface is visible, else False.
    */
    bool surfaceVisible( int inIndex = 0 ) const; // VS_LOCAL_GET

    /** Specify the number of peels for transparent surface rendering.
        This class provides an implementation of order-indepentent transparency
        rendering - also known as "depth peeling" 
        (see Everitt Order-Independent Transparency)
        With this method depth peeling can be parameterized. The parameter 
        \c inNumPeels specifies how many layers of the geometry from front to back
        are considered and correctly blended. Note that each layer requires an
        additional rendering pass for the geometry. If \c inNumPeels equals 0, depth
        peeling is switched off leading to possible erroneously rendered transparent
        surfaces.
        \param  inNumPeels
                The number of geometry layers to be blended correctly front to back.
                If equals 0, depth peeling is disabled.
        \return
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT setNumPeels( int inNumPeels ); // VS_RELAY

    /** Returns the number of geometry layers to be blended correctly front to
        back via depth peeling.
        \return
                The number of peeling layers or 0 if depth peeling is switched off.
    */
    int numPeels() const; // VS_LOCAL_GET

    /** Set a slave node that is beeing composited with the geometry.
        Note that multiple slave objects can be attached below a VsGroup that
        is beeing registered with the surface object.
        \param  inSlaveNode
                The slave node object.
        \return
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT setSlaveNode( VsNode * inSlaveNode ); // VS_RELAY

    /** Set the sorting between the slave node and the surface node.
       (see VsSurfRen::SlaveSorting for semantics of inSlaveOrder)
        \param  inSlaveSorting
                The new sorting between the slave node and the surface node.
        \return
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT setSlaveSorting( VsSurfRen::SlaveSorting inSlaveSorting ); // VS_RELAY

    /** Returns the current sorting between an attached slave node and the
        surface node. (see VsSurfRen::SlaveSorting for return value semantics)
        \return
                The current surface slave ordering.
    */
    SlaveSorting slaveSorting() const; // VS_LOCAL_GET

    ////////////////////////////////////////
    // overloaded methods from VsObject
    ////////////////////////////////////////

    virtual VSRESULT setOptioni( int inOption, int inValue ); // VS_RELAY
    virtual VSRESULT setOptiond( int inOption, double inValue ); // nothing to do. It can be a relay function if there is some source code.
    virtual VSRESULT optioni( int inOption, int & outValue ) const; // VS_LOCAL_GET
    virtual VSRESULT optiond( int inOption, double & outValue ) const; // VS_LOCAL_GET

//protected: // must be plublic. The Relay class need an access to the function observedObjectTouched()

    virtual VSRESULT observedObjectTouched( VsObject * inObject, unsigned int inMask ); // VS_RELAY

public:

    ////////////////////////////////////////
    // overloaded methods from VsNode
    ////////////////////////////////////////
    virtual VsRenderResult render();
    virtual VSRESULT cleanup();
    virtual VSRESULT boundingBox( McBox3f & outBox ) const; // VS_LOCAL_GET

    virtual void * extension( int, void * ); // ??? renderPendingLayer() => should be a relay function.
};

#endif

/// @}
