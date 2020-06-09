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

/// @addtogroup hxfield hxfield
/// @{
#ifndef HX_PORT_MULTI_CHANNEL_H
#define HX_PORT_MULTI_CHANNEL_H

#include <mclib/McColor.h>
#include <hxcore/HxPortToggleList.h>
#include <hxfield/HxMultiChannelField3.h>

class HxMultiChannel;

/** This port is used to toggle channels of a HxMultiChannelField3 on
    or off. The port is supposed to be used by display modules working on
    multi-channel data, such as HxOrthoSlice or HxProjectionView.
    It simply provides a toggle list with one toggle for each channel of
    a multi-channel field. If a toggle is turned off the particular channel
    should be ignored during rendering. Note, that the display module itself
    is responsible for interpreting the toggle states. */

class HXFIELD_API HxPortMultiChannel : public HxPortToggleList {

  MC_ABSTRACT_HEADER(HxPortMultiChannel);

  public:
    /// Constructor.
    HxPortMultiChannel(HxObject *obj, const char* name);

    /// Destructor.
    virtual ~HxPortMultiChannel();

    /* Automatically configures the port. This method should be called in
       the update routine of a display module. As an argument simply
       @c portData.source() can be used. If the argument is null or if it is
       not of type HxMultiChannelField3, the port automatically hides
       itself and returns false. Otherwise, it adjusts the number of toggles
       to be displayed as well as the corresponding channel colors and
       and returns true. */
    bool update(HxObject* data);

    HxMultiChannelField* getMultiChannel() const{ return m_multiChannel; }
private:
    HxMultiChannelField* m_multiChannel;
};

#endif

/// @}
