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

/// @addtogroup hxneuroneditor hxneuroneditor
/// @{
#ifndef HX_SEGMENT_MPR_VIEWER_H
#define HX_SEGMENT_MPR_VIEWER_H

#include "HxMPRViewer.h"
#include "hxneuroneditorAPI.h"

/**
  *
  * The Segment MPR-Viewer computes and renders a curved slice
  * along given segment points.
  * Note: The padding offset must be set.
  *
 **/

class HXNEURONEDITOR_API HxSegmentMPRViewer : public HxMPRViewer
{
public:
    HxSegmentMPRViewer(QxViewerPanel* panel);

    void setPaddingOffset(const float paddingOffset);

    /// Set sample and render geometry of the curved slice to NULL.
    void initCurvedSlice();

    /**
      * Compute and set the sample and render geometry of the curved slice
      * for the segment given by \a segmentPoints.
      * The number of the "vertical" vertices of the quad mesh that defines
      * the curved slice is always three. The height of the mesh is twice the
      * padding offset and the segment is centrally located referred
      * to the height. The number of the "horizontal" vertices depends
      * on the number of segment points. The distances between adjacent
      * segment points and twice the padding offset determine the width
      * of the quad mesh.
      **/
    void unrollSegment(const McDArray<McVec3f>& segmentPoints);

    /// Reimplemented from HxViewerBase
    void setActiveTool(ExModal *tool);

    /// Reimplemented from ExViewerBase
    /// Setting the type is necessary for activating/deactivating the tools
    /// that can respectively cannot operate with a curved slice.
    virtual Ex::ViewerType type() const;

private:
    /// The padding offset defines the space between the border
    /// of the slice and the segment centered within it.
    float mPaddingOffset;
};

#endif


/// @}
