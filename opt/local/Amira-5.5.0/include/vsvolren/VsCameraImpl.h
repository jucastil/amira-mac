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
#ifndef _VS_CAMERA_IMPL_H
#define _VS_CAMERA_IMPL_H

#include "VsCamera.h"

#include "VsNodeImpl.h"

#include "McViewVolume.h"

#include <mclibthreaded/McMutex.h>

#include <mclib/McHandle.h>
#include <mclib/McBox3f.h>
#include <mclib/McVec3f.h>
#include <mclib/McRotation.h>
#include <mclib/McMat4f.h>



////////////////////////////////////////////////////////////////////////////////
class VsCameraImpl : public VsNodeImpl
{
    VS_IMPLEMENTATION( VsCameraImpl, VsNodeImpl, VsCamera )

public:

    class VsCameraState
    :   public VsNodeState
    {
    public:

        VsCameraState();

    public:

        VsCamera::ProjectionType  mCameraType;

        McVec3f         mPosition;
        McRotation      mOrientation;
        float           mAspectRatio;
        float           mNearDistance;
        float           mFarDistance;
        float           mFocalDistance;
        float           mHeight;
        float           mHeightAngle;
        
        bool            mMatricesUpToDate;
    //    bool            mUseManualViewMatrix;
        McMat4f         mViewMatrix;
        McMat4f         mProjectionMatrix;
        McViewVolume    mViewVolume;
        unsigned int    mViewVolumeOK:1;
    };


    McHandle<VsCameraState> mState;
    McHandle<VsCameraState> mStateToRender;

    unsigned long           mRenderThread;

    VsCameraState & state() const;

    McBox3f                 mRenderObjectBox;

    McMutex               * mMutex;

public:
    ////////////////////////////////////////
    // internal methods
    ////////////////////////////////////////
    virtual void computeView();


public:
    ////////////////////////////////////////
    // non-virtual interface methods
    ////////////////////////////////////////
    VsCamera::ProjectionType  cameraType() const;
    VSRESULT    setCameraType( VsCamera::ProjectionType );
    McVec3f     position() const;
    McRotation  orientation() const;
    float       aspectRatio() const;
    float       nearDistance() const;
    float       farDistance() const;
    float       focalDistance() const;
    float       height() const;
    float       heightAngle() const;
    VSRESULT    setPosition( const McVec3f & );
    VSRESULT    setOrientation( const McRotation & );
    VSRESULT    setAspectRatio( float );
    VSRESULT    setNearDistance( float );
    VSRESULT    setFarDistance( float );
    VSRESULT    setFocalDistance( float );
    VSRESULT    setHeight( float );
    VSRESULT    setHeightAngle( float );
    McVec3f     focalPoint() const;
    VSRESULT    lookAt(const McVec3f & center);
    McVec3f     upDir() const;
    McVec3f     viewDir() const;
    VSRESULT    viewBoundingBox(const McBox3f& bBox, VsCamera::FitMode inFitMode);
    VSRESULT    adjustClippingPlanes(const McBox3f& bBox);
    VSRESULT    transform( const McMat4f & inMat );
    VSRESULT    viewVolume( McViewVolume & viewVolume ) const;
    VSRESULT    setViewMatrix( const McMat4f & inViewMatrix );
    VSRESULT    setProjectionMatrix( const McMat4f & inProjectionMatrix );
    McMat4f     viewMatrix() const;
    McMat4f     projectionMatrix() const;
    const McViewVolume & viewVolume() const;
    VSRESULT    set( const McVec3f & inPosition, const McVec3f & inAimPoint, const McVec3f & inUpDir );

private:
    ////////////////////////////////////////
    // virtual interface methods
    ////////////////////////////////////////
    VSRESULT vimpl_touch( unsigned int mask=VsObject::NEW_ALL );
    void *   vimpl_extension( int inEnum, void * inData);
    bool     vimpl_renderStateSupported();
    VSRESULT vimpl_renderStateCreate( McHandle<VsNodeState> & outState );
    virtual VsRenderResult vimpl_render()
    {
        return VS_RENDER_OK;
    }
};

#endif


/// @}
