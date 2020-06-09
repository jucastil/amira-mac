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
#ifndef HXSOBELFILTER3D_H
#define HXSOBELFILTER3D_H

#include <hximproc/HxImprocWinDLLApi.h>
#include <hximproc/ImFilter3D.h>
#include <mclib/McTypedData3D.h>


/**The Sobel-Filter is a rotation variant edge detection filter.
   It convolutes the image with 2 different filter kernels representing
   horizontal and vertical orientations. Each kernel
   is constituted of a combination of gaussian smoothing and 
   the differentiation in the proper orientation.*/
class HXIMPROC_API ImSobelFilter3D : public ImFilter3D
{
    MC_HEADER( ImSobelFilter3D);

public:
    /// Constructor.
    ImSobelFilter3D(HxEditor* editor=0);

    /// Destructor.
    ~ImSobelFilter3D();


    /*The algorithm calculates four temporary images using each of the kernels 
      as parameter to ImConvFilter3D::convolve(class McTypedData3D*,
      class McTypedData3D*, float *kernel, int, int).
      Afterwards the result is calculated taking the maximum of the absolute
      values of each temporary image.*/
    void apply3D( class McTypedData3D* src,
		  class McTypedData3D* dst=NULL,
		  class McProgressInterface* progress=NULL);

    static ImFilter3D* createFilter(HxEditor* e) {
	return new ImSobelFilter3D(e); }
    
protected:
private:
    McTypedData3D *dstBuffer;
};

#endif

/// @}
