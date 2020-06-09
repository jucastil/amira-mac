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
#ifndef _VS_NODE_IMPL_H
#define _VS_NODE_IMPL_H

#include "VsNode.h"

#include "VsObjectImpl.h"

#include <mclib/McHandle.h>
#include <mclib/McList.h>


////////////////////////////////////////////////////////////////////////////////
class VsNodeImpl
:   public VsObjectImpl
{
    VS_IMPLEMENTATION( VsNodeImpl, VsObjectImpl, VsNode )

public:

    int     mRenderTime;
    bool    mVisible;

    static bool                           sIsGrayScale;
    static mcint64                        sFrameIdToRender;
    static mcint64                        sFrameIdToSave;


    ////////////////////////////////////////
    // render state cache
    ////////////////////////////////////////

    McList<VsNodeState>     mRenderStates;
    McMutex               * mRenderStatesMutex; // might be unnecessary if rendering is serialized, but let's make it safe
    
    McHandle<VsNodeState> stateLookupByFrameId( mcint64 inFrameId );
    McHandle<VsNodeState> stateLookupByTouchNumber( unsigned int inTouchNumber );


public:


    ////////////////////////////////////////
    // non-virtual interface methods
    ////////////////////////////////////////
    VSRESULT    setVisible( bool inFlag );
    bool        visible() const;
    VSRESULT    collectNodes( McDArray< McHandle<VsNode> > & ioArray, bool inLockNodes, bool inCancelCurrentOperation, VsJobControl * inLocker, bool inWriteLock );
    bool        transformation( VsNode * inNode, McMat4f & outMatrix );

    VSRESULT    renderState( McHandle<VsNodeState> & outStateToRender, mcint64 inFrameIdToSave = -1, mcint64 inFrameIdToRender = -1 );
    VSRESULT    deleteState( mcint64 inFrameIdToDelete = -1 );

    static mcint64 frameIdToSave();
    static void    frameIdToSaveSet( mcint64 inId );

    static mcint64 frameIdToRender();
    static void    frameIdToRenderSet( mcint64 inId );


private:

    ////////////////////////////////////////
    // virtual interface methods
    ////////////////////////////////////////
    VsRenderResult vimpl_render();

    VSRESULT    vimpl_boundingBox( McBox3f & box ) const;
    VSRESULT    vimpl_setRenderTime( int msec );
    int         vimpl_renderTime();
    VSRESULT    vimpl_cleanup();
    VSRESULT    vimpl_renderStateCreate( McHandle<VsNodeState> & outState );
    bool        vimpl_renderStateSupported();
    bool        vimpl_sharedStateSupported();

    void      * vimpl_extension( int inEnum, void * ioData );
};

#endif


/// @}
