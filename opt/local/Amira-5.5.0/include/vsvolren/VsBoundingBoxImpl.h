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
#ifndef _VS_BOUNDING_BOX_IMPL_H
#define _VS_BOUNDING_BOX_IMPL_H

#include "VsBoundingBox.h"
#include "VsNodeImpl.h"
#include "VsCropRegionImpl.h"
#include "VsCropBox.h"
#include "VsHandable.h"

#include <mclib/McBox3f.h>
#include <mclib/McHandle.h>
#include <mclib/McDArray.h>
#include <mclib/McHashTable.h>


class VsCropRegion;


////////////////////////////////////////////////////////////////////////////////
class VsBoundingBoxImpl : public VsNodeImpl
{
    VS_IMPLEMENTATION( VsBoundingBoxImpl, VsNodeImpl, VsBoundingBox )

public:

    McBox3f                             mBoundingBox;
    bool                                mBoundingBoxVisible;
    McHandle<VsCropBox>                 mCrop;  // crop region object that crops mBoundingBox 
    
    bool                                mLinesBoxValid;
    McDArray<McVec3f>                   mLinesBox[2];  // pingpong buffer for line segments at the box edges
    int                                 mLinesBoxCurr;

    // each associated crop region gets an entry
    class MyCropInfo
    :   public VsHandable
    {
    public:

        MyCropInfo()
        :   mVisible        (  true )
        ,   mLinesCropValid ( false )
        ,   mLinesCropCurr  (     0 )
        ,   mLinesBoundValid( false )
        ,   mLinesBoundCurr (     0 )
        {
        }

        McHandle<VsCropRegion>  mCropRegion;

        // visibility
        bool                    mVisible;

        // the lines of the crop region itself
        bool                    mLinesCropValid;
        McDArray<McVec3f>       mLinesCrop[2];  // pingpong buffer for inner line segments
        int                     mLinesCropCurr; // index of the current valid slot of the pingpong buffer

        // the lines on the bounding boxes surface
        bool                    mLinesBoundValid;
        McDArray<McVec3f>       mLinesBound[2];  // pingpong buffer for inner line segments
        int                     mLinesBoundCurr; // index of the current valid slot of the pingpong buffer
    };

    McHashTable< unsigned int, McHandle<MyCropInfo> > * mCropInfo;

    void update();

private:

    MyCropInfo & getInfoUnlocked( unsigned int inIndex );

public:
    ////////////////////////////////////////
    // non-virtual interface methods
    ////////////////////////////////////////
    VSRESULT  setBoundingBox( const McBox3f & box );
    VsCropRegion * cropRegion( unsigned int inIndex ) const;
    VSRESULT setCropRegion( VsCropRegion * cropRegion, unsigned int inIndex );

    VSRESULT setBoundingBoxVisible( bool inFlag );
    bool boundingBoxVisible();

    VSRESULT setRegionVisible( bool inFlag, unsigned int inIndex );
    bool regionVisible( unsigned int inIndex );


private:
    ////////////////////////////////////////
    // virtual interface methods
    ////////////////////////////////////////
    VSRESULT vimpl_observedObjectTouched( VsObject * inObject, unsigned int inMask );

    virtual VSRESULT        vimpl_boundingBox( McBox3f & box ) const;
    virtual VsRenderResult  vimpl_render();
    virtual VSRESULT        vimpl_cleanup();
};

#endif


/// @}
