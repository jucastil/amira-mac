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
#ifndef _VS_WIDGET_IMPL_H
#define _VS_WIDGET_IMPL_H

#include "VsWidget.h"

#include "VsNodeImpl.h"


////////////////////////////////////////////////////////////////////////////////
class VsWidgetImpl : public VsNodeImpl
{
    VS_IMPLEMENTATION( VsWidgetImpl, VsNodeImpl, VsWidget )
    
public:
    McVec2i mPosition;
    McVec2i mSize;
    McVec2i mSizeHint;

public:
    ////////////////////////////////////////
    // non-virtual interface methods
    ////////////////////////////////////////
    void geometry( McVec2i & outUpperLeft, McVec2i & outSize );
    void setSizeHint( McVec2i & inSize );
    void sizeHint( McVec2i & outSizeHint );

protected:
    ////////////////////////////////////////
    // virtual interface methods
    ////////////////////////////////////////
    void vimpl_setGeometry( McVec2i & inUpperLeft, McVec2i & inSize );
    VsRenderResult vimpl_render();
    void * vimpl_extension( int inEnum, void * inData );
};

#endif


/// @}
