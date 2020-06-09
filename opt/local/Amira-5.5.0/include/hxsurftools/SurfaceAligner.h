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

/// @addtogroup hxsurftools hxsurftools
/// @{
#ifndef _SurfaceAligner_H
#define _SurfaceAligner_H

#include <hxsurftools/HxSurfToolsWinDLLApi.h>
#include <mclib/McBox3f.h>

class HxController;
class HxSurface;
class McProgressInterface;

/** This class computes the alignment of two surfaces by the ICP algorithm. */

class HXSURFTOOLS_API SurfaceAligner {

  public:

    /// Default constructor.
    SurfaceAligner() { roi.makeEmpty(); };

    /** Surface distance can be evaluated within a region of interest.
        Setting the ROI with an emptyBox disables ROI checking */
    void setRoi (McBox3f  roiBox) {roi = roiBox;};

    /// Compute trafo of alignment
    void compute(HxSurface* surfToBeAligned, HxSurface* reference,
                 int trafoType=0, 
                 int maxIter=1, 
                 float minChange=0, 
                 HxController* controller=NULL, 
                 McProgressInterface* progress=NULL,
                 float* weights=NULL);

    ~SurfaceAligner() {};

  protected:

    McBox3f roi;
};

#endif

/// @}
