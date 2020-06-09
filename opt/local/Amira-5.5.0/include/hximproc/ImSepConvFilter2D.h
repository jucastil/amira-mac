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
#ifndef IM_SEPConvFilter2D_H
#define IM_SEPConvFilter2D_H

#include <hximproc/HxImprocWinDLLApi.h>
#include <hximproc/ImConvFilter2D.h>
#include <mclib/McDMatrix.h>
#include <mclib/McDArray.h>

/** Base class for convolution filters with seperable 2D filter kernels,
    i.e., filter kernels which can be written as C(x,y) = f(x)*g(y).
    The convolution integral INT{ C(x',y')*picture(x-x',y-y') d2x }
    can then be decomposed into two one-dimenisonal integrals.
*/

class HXIMPROC_API ImSepConvFilter2D : public ImConvFilter2D
{
    MC_HEADER(ImSepConvFilter2D);

public:
    /// Constructor.
    ImSepConvFilter2D(); 

    /// Destructor.
    ~ImSepConvFilter2D();

    /// Specifies one filter kernel for all directions.
    void setKernel(int n, float kernel[]);

    /// Specifies separate filter kernels for x and y direction.
    void setKernel(int n[2], float kernel[][2]);

    // Erase the current Kernel
    void freeKernel();

	/// tries to generate a separable filter kernel from the given
	/// 3d filter
    bool setKernel(int n[2],  McDMatrix<double> kernel);

    /// May be used in derived classes to avoid redundant set-ups.
    int kernelIsSet() { return kernIsSet; }

    /// Clears "is set" flag.
    void unsetKernel() { kernIsSet = 0; }

    virtual void apply2D(McTypedData2D* src, McTypedData2D* dst=NULL);

protected:
    void convolve(class McTypedData2D *src, class McTypedData2D *dst=NULL);

private:
    int diffrentKernelsXY;
    float* _kernel[2];
    int _n[2];
    int kernIsSet;
	void sortSVD(McDArray<double> &evals,McDMatrix<double> &evects);
};

#endif

/// @}
