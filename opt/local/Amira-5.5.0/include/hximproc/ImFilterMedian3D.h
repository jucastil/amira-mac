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

/// @addtogroup hximproc hximproc
/// @{
#ifndef IM_FILTER_MEDIAN_3D_H
#define IM_FILTER_MEDIAN_3D_H

#include <hximproc/HxImprocWinDLLApi.h>
#include <hximproc/ImFilter3D.h>

#include <hxcore/HxPortFloatTextN.h>

/** The median filter works by sorting pixels covered by
    a NxN mask according to their grey value. The center pixel is then
    replaced by the median of these pixels. The size of the pixel mask 
    may be adjusted via the text field labeled kernel size */
class HXIMPROC_API ImFilterMedian3D : public ImFilter3D {
    
  MC_HEADER( ImFilterMedian3D);
public:
    ///Constructor
    ImFilterMedian3D(HxEditor* editor=0);
    
    ///Destructor 
    ~ImFilterMedian3D();
 
    ///holds the filter algorithm 
    void apply3D(class McTypedData3D* src, 
		class McTypedData3D* dst=NULL, McProgressInterface* progress=NULL);

    HxPortFloatTextN portKernelSize;

    void setKernelSize(float val);
  
    float getKernelSize() { return 3; }

    static ImFilter3D* createFilter(HxEditor* e) {
      return new ImFilterMedian3D(e); }

};
#endif

/// @}