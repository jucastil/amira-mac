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
#ifndef HX_CLAHE_3D
#define HX_CLAHE_3D

#include <hximproc/HxImprocWinDLLApi.h>


class McProgressInterface;

/** Contrast limited adaptive histogram equalization.
	This class provides a single static function implementing so-called
    contrast limited adaptive histogram equalization. This is a method for
    mapping 12-bit image data to 12-bit grey values in such a way that as
    much detail becomes visible as possible. The method is used in Amira
    e.g. by the OrthoSlice or the ObliqueSlice modules. The algorithm has
    been originally developed by Karel Zuiderveld (karel@cv.ruu.nl).

    The main routine CLAHE expects an input image that is stored
    contiguously in memory. The CLAHE output image overwrites the original
    input image and has the same minimum and maximum values (which must be
    provided by the user). This implementation assumes that the x and y
    image resolutions are an integer multiple of the x- and y sizes of the
    so-called contextual regions. For each contextual region a separate
    histogram is computed. A check on various other error conditions is
    performed.  
 */

class HXIMPROC_API HxCLAHE3D  {

  public:
    /** The number of <em> effective</em> greylevels in the output image is set
        by @c uiNrBins. Selecting a small value (e.g. 128) speeds up
        processing and still produce an output image of good quality. The
        output image will have the same minimum and maximum value as the
        input image. A clip limit smaller than 1 results in standard
        (non-contrast limited) adaptive histogram equalization.

        @param image Pointer to the input image
        @param resX Image resolution in the x direction
        @param resY Image resolution in the y direction
        @param min Minimum grey value of input image
        @param max Maximum grey value of input image
        @param nRegionsX Number of contextual regions in x (min 2, max 16)
        @param nRegionsY Number of contextual regions in y (min 2, max 16)
        @param nBins Number of grey bins for histogram ("dynamic range")
        @param clipLimit Normalized cliplimit (the higher the more contrast)
        @param progres The progress bar
    */
    static int CLAHE3D (unsigned short* image,
			const int dims[3],
			unsigned short min, unsigned short max,
			unsigned int nRegionsX, unsigned int nRegionsY, unsigned int nRegionsZ,
			unsigned int nBins, float clipLimit,
			McProgressInterface* progres, float totalProgressCount);


};
#endif

/// @}
