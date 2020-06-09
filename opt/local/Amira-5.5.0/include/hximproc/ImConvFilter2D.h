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
#ifndef Hx_ConvFilter2D_H
#define Hx_ConvFilter2D_H

#include <hximproc/HxImprocWinDLLApi.h>
#include <hximproc/ImFilter2D.h>


/** Base class for 2D  convolution filters. 
  This implementation  of the convolution is considerably 
  slower than the one available for separable filter kernels. 
  Such filters should be implemented using ImSepConvFilter2D. */
class HXIMPROC_API ImConvFilter2D : public ImFilter2D
{
    MC_ABSTRACT_HEADER(ImConvFilter2D);
    
public:
    /// Constructor must be called by child class.
    ImConvFilter2D();
    
    /// Destructor.
    ~ImConvFilter2D();
    
    /**Convolves image data using kernel given as parameter.
    Such a kernel might be defined as 
    static float ky[3][3] = 
    {
	{  1,  2,  1 },
	{  0,  0,  0 },
	{ -1, -2, -1 }
    };
    and passed as (float *) ky, for example.
    Convolution at the edges is done by periodic extrapolation. */
    virtual void convolve(class McTypedData2D* src, class McTypedData2D* dst, float
		             *kernel, int kernelSizeX=3, int kernelSizeY=3);
};

#endif

/// @}
