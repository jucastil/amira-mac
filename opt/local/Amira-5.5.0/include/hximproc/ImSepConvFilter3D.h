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
#ifndef IM_SEPConvFilter_H
#define IM_SEPConvFilter_H

#include <hximproc/HxImprocWinDLLApi.h>
#include <hximproc/ImFilter3D.h>

/** Base class for convolution filters with seperable 3D filter kernels,
    i.e., filter kernels which can be written as C(x,y,z) = f(x)*g(y)*h(z).
    The convolution integral INT{ C(x',y',z')*picture(x-x',y-y',z-z') d3x }
    can then be decomposed into three one-dimenisonal integrals.
*/

class HXIMPROC_API ImSepConvFilter3D : public ImFilter3D
{
    MC_ABSTRACT_HEADER( ImSepConvFilter3D);

public:
    /// Constructor.
    ImSepConvFilter3D(); 

    /// Destructor.
    ~ImSepConvFilter3D();

    /// Specifies one filter kernel for all directions.
    void setKernel(int n, float kernel[]);

    /// Specifies separate filter kernels for x, y, and z direction.
    void setKernel(int n[3], float kernel[][3]);

    /// Used in Lanczos filter in order to avoid redundant set-ups.
    int kernelIsSet() { return kernIsSet; }

    /// Clears "is set" flag.
    void unsetKernel() { kernIsSet = 0; }

protected:
    void convolve( class McProgressInterface* progress, class McTypedData3D *src, class McTypedData3D *dst=NULL);

private:
    int diffrentKernelsXYZ;
    float* _kernel[3];
    int _n[3];
    int nKernels;
    int kernIsSet;
};

#endif

/// @}
