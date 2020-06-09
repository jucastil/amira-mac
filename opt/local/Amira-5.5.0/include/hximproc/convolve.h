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
#ifndef CONVOLVE_H
#define CONVOLVE_H

#include <stdio.h>
#include <stdlib.h>

#include "HxImprocWinDLLApi.h"

/*
 * C code from the article
 * "Fast Convolution with Packed Lookup Tables"
 * by George Wolberg and Henry Massalin,
 * (wolcc@cunyvm.cuny.edu and qua@microunity.com)
 * in "Graphics Gems IV", Academic Press, 1994
 *
 */


typedef unsigned char	uchar;



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * initPackedLuts:
 *
 * Initialize scaled and packed lookup tables in lut.
 * Permit up to 3 cascaded stages for the following kernel sizes:
 *	stage 0:  5-point kernel
 *	stage 1: 11-point kernel
 *	stage 2: 17-point kernel
 * lut->lut0 <== packed entries (i*k2, i*k1, .5*i*k0), for i in [0, 255]
 * lut->lut1 <== packed entries (i*k5, i*k4,	i*k3), for i in [0, 255]
 * lut->lut2 <== packed entries (i*k8, i*k7,	i*k6), for i in [0, 255]
 * where k0,...k8 are taken in sequence from kernel[].
 *
 * Note that in lut0, k0 is halved since it corresponds to the center
 * pixel's kernel value and it appears in both fwd0 and rev0 (see gem).
 */
void HXIMPROC_API initPackedLuts(float *kernel, int n);



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * fastconv:
 *
 * Fast 1D convolver.
 * Convolve len input samples in src with a symmetric kernel packed in luts,
 * a lookup table that is created by initPackedLuts() from kernel values.
 * The output goes into dst.
 */
void HXIMPROC_API fastconv(uchar *src, int len, int  offst, uchar *dst);

#endif

/// @}
