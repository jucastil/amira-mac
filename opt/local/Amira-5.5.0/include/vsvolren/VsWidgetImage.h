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
#ifndef _VS_WIDGET_IMAGE_H_
#define _VS_WIDGET_IMAGE_H_


#include "Vs.h"
#include "VsWidget.h"
#include "VsMemoryData.h"

#include <mclib/McVec2i.h>
#include <mclib/McHandle.h>


// VS_RELAY_CLASS VsWidgetImage VsWidgetRelay


class VSVOLREN_API VsWidgetImage : public VsWidget
{
    VS_DECL_INTERFACE        ( VsWidgetImage )
    VS_DECL_INTERFACE_IMPL   ( VsWidgetImage )
    VS_DECL_INTERFACE_FACTORY( VsWidgetImage )
    VS_DECL_INTERFACE_RELAY  ( VsWidgetImage )
    
public:

    ////////////////////////////////////////
    // VsNode overrides
    ////////////////////////////////////////

    virtual VsRenderResult render();

    VSRESULT cleanup();


    ////////////////////////////////////////
    // VsWidget overrides
    ////////////////////////////////////////

    virtual void setGeometry( McVec2i & inUpperLeft, McVec2i & inSize );

    ////////////////////////////////////////
    // own methods
    ////////////////////////////////////////

    /** Set a new image.
        The image replaces the old image. 
        The node holds a reference to the VsMemoryData object. So if the data or dimension
        of the VsMemoryData object changes the image rendered on the screen changes too.
        Currently the only supported image format is RGBA8.
        \param [in] inImage
                Image data that is going to be displayed. The first slice is displayed.
                If zero, no image is displayed.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setImage( VsMemoryData * inImageLL );

    /** Get current image.
        \return 
                Handle to the current image. May be an empty handle.
    */
    McHandle<VsMemoryData> image();
};


#endif

/// @}
