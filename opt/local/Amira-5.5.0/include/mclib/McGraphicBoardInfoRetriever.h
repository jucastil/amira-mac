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

/// @addtogroup mclib mclib
/// @{
#ifndef _MC_GRAPHICBOARDINFORETRIEVER_H
#define _MC_GRAPHICBOARDINFORETRIEVER_H

#include "McString.h"

/**
 *  Virtual class in charge of retrieving various info about the graphic board capabilities.
 */

class McGraphicBoardInfoRetriever
{
public:

    /**
     *  Constructor.
     */
    McGraphicBoardInfoRetriever();

    /**
     *  Returns the total amount of video memory, in megabytes.
     *  Alternatively, you can force to use a certain amount of video
     *  memory in megabytes by setting the AMIRA_USER_VIDEO_MEM_AMOUNT.
     *  @param defaultValue The value returned in case of error.
     *  @param ok Set to false in case of error.
     */
    int videoMemoryAmount(int defaultValue = 128, bool* ok = 0);

    /**
     *  Returns the driver version.
     *  @param defaultValue The value returned in case of error.
     *  @param ok Set to false in case of error.
     */
    McString driverVersion(const McString& defaultValue = "Unknown", bool* ok = 0);

protected:

    /**
     *  Cached value of the total amount of video memory.
     *  Default values is -1. It indicates that this value isn't cached yet.
     */
    int m_memoryAmount;

    /**
     *  Cached value of the driver version.
     *  Default values is "NOT_CACHED". It indicates that this value isn't cached yet.
     */
    McString m_driverVersion;

    /**
     *  OS dependent implementation in charge of retrieving the video memory amount.
     *  This method must set @c m_memoryAmount.
     *  Return false on error.
     */
    bool retrieveVideoMemoryAmount();

    /**
     *  OS dependent implementation in charge of retrieving the driver version.
     *  This method must set @c m_driverVersion.
     *  Return false on error.
     */
    bool retrieveDriverVersion();
};

#endif

/// @}
