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
#ifndef  EX_SLICERENDERMODETOOL_H
#define  EX_SLICERENDERMODETOOL_H

#include "ExTrigger.h"
#include <mclib/McDArray.h>

class ExBaseViewer;

/** Tool class for setting various slice rendering settings */
class ExSliceRenderModeTool : public ExTrigger
{
public:
    virtual bool process(ExBaseViewer* viewer, bool set);

    static void setRenderMode(const ExBaseViewer* viewer, Ex::SliceRenderMode mode, bool inverse, bool updateLinkedViewers = true);
    static bool getRenderMode(const ExBaseViewer* viewer, Ex::SliceRenderMode* mode, bool* inverse);

    /// Sets the thickness of the slice to the value provided by the thickness parameter.
    /// The thickness parameter is clamped to the maximum of the bounding box diagonal
    /// of all affected slices. If, on the other hand, the thickness parameter is smaller
    /// than the voxel size of a slice, the internal thickness of the slice is set to 0,
    /// i.e., thin slice extraction. 
    static void setThickness(const ExBaseViewer* viewer, float thickness, bool updateLinkedViewers = true);
    static bool getThickness(const ExBaseViewer* viewer, float* thickness, float* rawThickness);
    /// Convenience function. Returns true if viewer displays thin slice or false otherwise or if error.
    static bool isThinSlice(const ExBaseViewer* viewer);
    static bool getDICOMSliceThickness(const ExBaseViewer* viewer, float* thickness);
    
    static void setROIFilled(const ExBaseViewer* viewer, bool status, bool updateLinkedViewers = true);
    static bool getROIFilled(const ExBaseViewer* viewer, bool *status);

    static void setROIOutlined(const ExBaseViewer* viewer, bool status, bool updateLinkedViewers = true);
    static bool getROIOutlined(const ExBaseViewer* viewer, bool *status);

    virtual const McString identifier() const;
    virtual void notified(const ExNotification& notification);
    virtual bool supports(Ex::ViewerType) const;

private:
    static McDArray<float> mOldThickness;
};

#endif // EX_SLICERENDERMODETOOL_H


/// @}
