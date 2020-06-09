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
#ifndef _VS_CROB_REGION_IMPL_H
#define _VS_CROB_REGION_IMPL_H

#include "VsCropRegion.h"

#include "VsObjectImpl.h"
#include "VsBSPImpl.h"

#include <mclib/McVec3f.h>
#include <mclib/McVec4f.h>
#include <mclib/McDArray.h>

#include <mclibthreaded/McMutex.h>


////////////////////////////////////////////////////////////////////////////////
class VSVOLREN_API VsCropRegionImpl : public VsObjectImpl
{
    VS_IMPLEMENTATION( VsCropRegionImpl, VsObjectImpl, VsCropRegion )
    
public:
    ////////////////////////////////////////
    // own methods
    ////////////////////////////////////////

    void cutLines( McDArray<McVec3f> ioLinesPingPong[2], int & ioIndex, float inEPS = 0.0f );

    void updateSOPObject();
    void updateSOPVoxel();

    void cameraUpdate( VsCamera const * inCamera );

    void shape( 
        McPlane const           * inBasePlane
    ,   McDArray<McPlane> const * inROIPlanes
    ,   McBox3f const           & inROIBox
    ,   McDArray<McVec3f>       * outBorderLines            = 0
    ,   McDArray<McVec3f>       * outOutsideTriangles       = 0
    ,   McDArray<int>           * outBorderLinesSOPAddress  = 0
    );


    void planesTransformed( McDArray<McPlane> & outPlanes );


public:
    ////////////////////////////////////////
    // non-virtual interface methods
    ////////////////////////////////////////

    bool     inside( const McVec3f & inPos, float inEpsilon ) const;
    bool     insideUnlocked( const McVec3f & inPos, float inEpsilon ) const;
    VSRESULT setTransformationVoxelToWorld( VsData * inData );
    bool     inside( const McVec3i & inPos, float inEpsilon ) const;
    bool     insideUnlocked( const McVec3i & inPos, float inEpsilon ) const;
    VSRESULT transformationLocalToObject( McMat4f & outTransCropToParent ) const;
    VSRESULT setTransformationLocalToObject( const McMat4f & inTransCropToParent );
    VSRESULT transformationObjectToWorld( McMat4f & outTransCropToParent ) const;
    VSRESULT setTransformationObjectToWorld( const McMat4f & inTransCropToParent );
    VsCamera * camera() const;
    VSRESULT setCamera( const VsCamera * inCamera );
    VSRESULT planeSOP( McDArray< McDArray<McPlane> > & outSOP ) const;
    VSRESULT planeSOPTransformed( McDArray< McDArray<McPlane> > & outSOP ) const;
    VSRESULT setPlaneSOP( const McDArray< McDArray<McPlane> > & inSOP );
    VSRESULT planeTransformed( McPlane & outPlane, unsigned int inIdxProduct, unsigned int inIdxPlane ) const;
    VSRESULT setPlaneTransformed( McPlane const & inPlane, unsigned int inIdxProduct, unsigned int inIdxPlane );
    VSRESULT plane( McPlane & outPlane, unsigned int inIdxProduct, unsigned int inIdxPlane ) const;
    McColor  color() const;
    VSRESULT setColor( const McColor & inColor );
    McColor  color2() const;
    VSRESULT setColor2( const McColor & inColor );
    McBox3f  boundingBoxOfBoxClip( McBox3f const & inBoxObject, McMat4f const & inObjectToResultBoxSpace );


    ////////////////////////////////////////
    // virtual interface methods
    ////////////////////////////////////////
    virtual VSRESULT vimpl_observedObjectRemoved( VsObject * inObject );
    virtual VSRESULT vimpl_observedObjectTouched( VsObject * inObject, unsigned int inMask );
    virtual VSRESULT vimpl_setPlane( McPlane const & inPlane, unsigned int inIdxProduct, unsigned int inIdxPlane );


private:


private:

    McMutex                       * mSOPMutex;
    McDArray< McDArray<McPlane> >   mSOPLocal;
    McDArray< McDArray<McPlane> >   mSOPObject;
    McDArray< McDArray<McPlane> >   mSOPVoxel;


    bool                            mSOPObjectValid;
    bool                            mSOPVoxelValid;

    McMat4f                         mTransLocalToObject;
    McMat4f                         mTransVoxelToObject;
    McMat4f                         mTransObjectToWorld;

    VsCamera                      * mCamera;

    McMat4f                         mTransLocalToObject_0;
    McMat4f                         mTransWorldToCamera_0;



    McMutex                         mShapeMutex;
    VsBSP                         * mBSP2D;
    McDArray<McPlane>               mBSPUniquePlanes;

    McColor                         mColor1;
    McColor                         mColor2;
};

#endif


/// @}
