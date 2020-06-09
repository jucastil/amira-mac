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
#ifndef _VS_GROUP_IMPL_H
#define _VS_GROUP_IMPL_H

#include "VsGroup.h"

#include "VsNodeImpl.h"

#include <mclib/McDArray.h>
#include <mclib/McHandle.h>
#include <mclib/McMat4f.h>

////////////////////////////////////////////////////////////////////////////////
class VsGroupImpl : public VsNodeImpl
{
    VS_IMPLEMENTATION( VsGroupImpl, VsNodeImpl, VsGroup )
    
public:

    McDArray< McHandle<VsNode> > mNodes;

    
    bool    mTransformed;
    McMat4f mTransformation;


public:
    ////////////////////////////////////////
    // non-virtual interface methods
    ////////////////////////////////////////
    VSRESULT        removeAll();
    int             size() const;
    int             findNode( VsNode * shape, int inStartIndex ) const;
    VsNode        * node( int i ) const;
    VsNode        * nodeNoLock( int i ) const;
    VSRESULT        setTransformation( const McMat4f & inMatrix );
    VSRESULT        transformation( McMat4f & outMatrix ) const;
    bool            hasTransformation() const;
    static bool     containsNode( const VsNode * inRoot, const VsNode * inNode );

private:
    ////////////////////////////////////////
    // virtual interface methods
    ////////////////////////////////////////
    VsRenderResult vimpl_render();

    int         vimpl_addNode( VsNode * shape );
    int         vimpl_removeNode( VsNode * shape );
    int         vimpl_removeNode( int inIndex );
    int         vimpl_insertNode( int before, VsNode * shape );
    VSRESULT    vimpl_boundingBox( McBox3f & box ) const;
    void      * vimpl_extension( int inEnum, void * inData);
};

#endif


/// @}
