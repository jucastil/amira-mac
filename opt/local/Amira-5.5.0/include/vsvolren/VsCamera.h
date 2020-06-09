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
#ifndef _VS_CAMERA_H_
#define _VS_CAMERA_H_

#include "Vs.h"

#include "VsNode.h"

#include <mclib/McHandle.h>
#include <mclib/McVec3f.h>
#include <mclib/McMat4f.h>
#include <mclib/McRotation.h>

class McBox3f;

// VS_RELAY_CLASS VsCamera VsNodeRelay

/** This node represents a camera in 3D space.
    When a camera gets rendered it sets the view transformation and 
    projection transformation that is used for the rendering the 
    following nodes. 
*/
class VSVOLREN_API VsCamera : public VsNode
{
    VS_DECL_INTERFACE        ( VsCamera )
    VS_DECL_INTERFACE_IMPL   ( VsCamera )
    VS_DECL_INTERFACE_FACTORY( VsCamera )
    VS_DECL_INTERFACE_RELAY  ( VsCamera )

public:

    /** Enumeration for projection types. */
    enum ProjectionType
    {
        /// Orthographic projection
        ORTHOGRAPHIC,
        /// Perspective projection
        PERSPECTIVE
    };

    /** Enumeration for viewBoundingBox() function. */
    enum FitMode
    {
        /** Fitting is calculated only with respect to the object space bounding box
            disregarding the camera orientation. This is the default behavior,
            but typically space is wasted with this setting. */
        ORIENTATION_INDEPENDENT,
        /// Bounding box must fit both in horizontal and vertical direction
        ALL,
        /// Bounding box must fit only in horizontal direction
        WIDTH,
        /// Bounding box must fit only in vertical direction
        HEIGHT
    };


    ////////////////////////////////////////
    // override VsObject
    ////////////////////////////////////////

    /**
    */
    virtual VSRESULT touch( unsigned int inMask=NEW_ALL );


    ////////////////////////////////////////
    // override VsNode
    ////////////////////////////////////////

    virtual bool renderStateSupported();

    virtual VSRESULT renderStateCreate( McHandle<VsNodeState> & outState );

    /**
    */
    virtual VsRenderResult render();


    /** Retrieve camera type.
        \return 
                See VsCamera::ProjectionType for possible values.
    */
    VsCamera::ProjectionType cameraType() const; // LOCAL_GET

    /** Set camera type.
        \param  inType
                The Camera's new projection type.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setCameraType( VsCamera::ProjectionType inType ); // VS_RELAY

    /** Get current position of the camera.
        \return 
                Current camera position in object space.
    */
    McVec3f position() const; // LOCAL_GET
 
    /** Set current position of the camera.
        \param  inPosition
                New spacial position of the camera in object space.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setPosition( const McVec3f & inPosition ); // VS_RELAY

    /** Get current orientation of the camera.
        \return 
                Current rotation of the camera.
    */
    McRotation orientation() const; // LOCAL_GET

    /** Set current orientation of the camera.
        \param  inOrientation
                New rotation of the camera.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setOrientation( const McRotation & inOrientation ); // VS_RELAY

    /** Get current aspect ratio.
        \return 
                Current aspect ratio of the camera. 
    */
    float aspectRatio() const; // LOCAL_GET

    /** Set aspect ratio.
        \param  inRatio
                New aspect ratio.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setAspectRatio( float inRatio ); // VS_RELAY

    /** Get distance of the near clipping plane from the camera position.
        \return 
                Current near plane distance.
    */
    float nearDistance() const; // LOCAL_GET

    /** Set distance of the near clipping plane from the camera position.
        \param  inDistance
                New distance.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setNearDistance( float inDistance ); // VS_RELAY

    /** Get distance of the far clipping plane from the camera position.
        \return 
                Distance of the far plane.
    */
    float farDistance() const; // LOCAL_GET

    /** Set distance of the far clipping plane from the camera position.
        \param  inDistance
                New distance.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setFarDistance( float inDistance ); // VS_RELAY

    /** Get distance to the position of interest. The point the camera focuses to.
        \return 
                Distance to the focal point.
    */
    float focalDistance() const; // LOCAL_GET

    /** Set distance to the position of interest. The point the camera focuses to.
        \param  inDistance
                New focal distance.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setFocalDistance( float inDistance ); // VS_RELAY

    /** Get height of the box-shaped view frustrum in case of orthogonal projection.
        \return 
                Height value. 
    */
    float height() const; // LOCAL_GET

    /** Set height of the box-shaped view frustrum in case of orthogonal projection.
        \param  inHeight
                new Height value.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setHeight( float inHeight ); // VS_RELAY

    /** The field of view angle, in degrees, in the y-direction when camera is in perspective mode.
        \return 
                The current angle.
    */
    float heightAngle() const; // LOCAL_GET

    /** Set the field of view angle, in degrees, in the y-direction when camera is in perspective mode.
        \param  inAngle
                The new angle.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setHeightAngle( float inAngle ); // VS_RELAY

    /** Position of interest. The point the camera focuses to.
        \return 
                Focal position in object space.
    */
    McVec3f focalPoint() const; // LOCAL_GET

    /** Set the orientation of the camera that it looks to the given point
        \param  inAimPoint
                Point the camrera is set to look to.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT lookAt( const McVec3f & inAimPoint );

    /** Up direction for camera
        \return 
                Up direction in object space.
    */
    McVec3f upDir() const; // LOCAL_GET

    /** View direction for camera
         \return
                 View direction in object space.
    */
    McVec3f viewDir() const; // LOCAL_GET

    /** Set the camera position and orientation.
        \param  inPosition
                New position.
        \param  inAimPoint
                New point the camrera is set to look to.
        \param  inUpDir
                New up direction.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT set( const McVec3f & inPosition, const McVec3f & inAimPoint, const McVec3f & inUpDir ); // VS_RELAY

    /** Retrieve the current view matrix that transforms from object space to camera space.
        \return 
                Current view matrix. 
    */
    McMat4f viewMatrix() const; // LOCAL_GET

    /** Retrieve the current projection matrix that transforms from camera space to clip space.
        \return 
                Current projection matrix.
    */
    McMat4f projectionMatrix() const; // LOCAL_GET

    /** Sets the view matrix directly that transforms from object space to camera space.
        \param  inViewMatrix
                The new view matrix.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setViewMatrix( const McMat4f & inViewMatrix ); // VS_RELAY

    /** Sets the projection matrix directly that transforms from camera space to clip space.
        \param  inProjectionMatrix
                The new projection matrix.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setProjectionMatrix( const McMat4f & inProjectionMatrix ); // VS_RELAY

    /** Set camera that the box fits completely in the viewport window from the current position.
        \param  inBox
                Bounding box that should fit. Sequence is x-min, x-max, y-min, y-max, z-min, z-max.
        \param  inFitMode
                Directions in which the bounding box must fit. Also see FitMode.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT viewBoundingBox( const McBox3f& inBox, VsCamera::FitMode inFitMode = VsCamera::ORIENTATION_INDEPENDENT ); // VS_RELAY

    /** Set near and far clipping plane that the box fits completely between them.
        \param  inBox
                Bounding box that should fit. Sequence is x-min, x-max, y-min, y-max, z-min, z-max.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT adjustClippingPlanes( const McBox3f& inBox );

    /** Returns the view volume corresponding to the current view frustum.
        \return 
                The view volume. 
    */
    const class McViewVolume & viewVolume() const; // LOCAL_GET

    /** Transform the camera according to inMat
        \param  inMat
                the transformation matrix
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT transform( const McMat4f & inMat ); // VS_RELAY

    /**
    */
    virtual void * extension( int, void * );
};


#endif


/// @}
