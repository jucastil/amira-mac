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

/// @addtogroup hxvisageviewer hxvisageviewer
/// @{
#ifndef EXBASEVIEWERGROUP_H
#define EXBASEVIEWERGROUP_H


#include "ExBase.h"

class ExBaseViewer;

////////////////////////////////////////////////////////////////////////////////
/// Helper class for getting groups of viewers
class ExBaseViewerGroup : public McDArray<ExBaseViewer *>
{
public:
    /* TODO: For logical and consistency reasons it would be better to use
             _PLUS_LINKED instead of _AND_LINKED. Moreover "linked" is not
             the correct term, it rather should say "synched".
    */

    /// Enumeration type for different groups
    enum GroupType
    {
        /// only the viewer given as first argument
        ONE_VIEWER,
        /// only the viewer and linked viewer with same modality
        ONE_VIEWER_PLUS_LINKED_WITH_SAME_MODALITY,
        /// All MPR viewers linked by scoutlines, orientented orthogonally in HP
        MPR_CROSSHAIR_GROUP,
        /// MPR viewer
        MPR_CROSSHAIR_GROUP_PLUS_LINKED,
        /// All MPR viewers linked by scoutlines.
        SCOUTLINE_GROUP,
        /// All MPR viewers linked by scoutlines and linked viewers
        SCOUTLINE_GROUP_PLUS_LINKED,
        /// Viewers of the same viewer type
        SAME_VIEWER_TYPE,
        /// Viewers of possibly different types showing the same image set
        SAME_IMAGESET,
        /// Viewers of possibly different types showing the same image set, and linked viewers
        SAME_IMAGESET_PLUS_LINKED,
        /// Viewers showing the same series or co-registered series and linked viewers
        SAME_SERIES_OR_COSERIES_MPR_CROSSHAIR_GROUP,
        /// Viewers of the same viewer type and linked viewer with same modality
        SAME_VIEWER_TYPE_AND_SERIES_PLUS_LINKED_WITH_SAME_MODALITY,
        /// All linked viewers
        LINKED_VIEWERS,
        /// Linked viewers with the same image set
        LINKED_AND_SAME_IMAGESET,
        /// All viewers. The parameter viewer is ignored. 
        ALL_VIEWERS,
        /// Only 3DMPR viewer xor connected "flat" MPR viewers
        MPR_CROSSHAIR_GROUP_SEPARATED_3D_MPR
    };

    /// Default constructor, creates an empty group.
    ExBaseViewerGroup() { }

    /** Get a group of viewers - potentially restricted to some viewer type
        TODO: not implemented for all group types - please check before using
              the type filter.
    */    
    ExBaseViewerGroup(const ExBaseViewer* viewer, 
                            GroupType groupType,
                      const Ex::ViewerType type = Ex::VT_UNDEFINED);

    bool contains(const ExBaseViewer* viewer) const;
};




#endif

/// @}
