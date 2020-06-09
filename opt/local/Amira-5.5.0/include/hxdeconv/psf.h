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

/// @addtogroup hxdeconv hxdeconv
/// @{
#ifndef PSF_H
#define PSF_H


/* this routine was written and generously supplied by Peter Verveer at EMBL in Heidelberg
	 Two modifications were made to it
	 1) The J0 and J1 functions of the Unix environment were changed to _J0 and_J1 becuase the pinheads at 
	 microsoft have a different definition than the rest of the world.
	 2) a header file was created and added as an include.

prototype of the PSF generator. The parameters are:

out        : pointer to the output data. You must allocate the data 
             before calling the routine.
x          : X-size of the PSF
y          : y-size of the PSF
z          : z-size of the PSF
sx         : sampling of the psf in x-direction (nm)
sy         : sampling of the psf in y-direction (nm)
sz         : sampling of the psf in z-direciton (nm)
l          : wavelength (nm)
na         : numerical aperture
ri         : refractive index 
pr         : precision, defaults to 0.01 if smaller than or equal to 0.0

The generated PSF is centered in the middle of the image. If you need only 
the in-focus PSF, set z=1. The PSF is rotationally symmetric, therefore
setting x = 1 or y = 1, gives you basically all you need if you don't want
the whole 3D PSF. (Actually the PSF is generated as a XZ slice and then
rotated to get the 3D PSF.)

Note1: the return value is an error indicator. It is zero if all is ok. 
       If it is one, something went wrong. The only error condition
       is if you run out of memory.

Note2: Currently the generated PSF is in single precision. You can change that
       to double precision by changing the typdef on the top of the psf.c 
       file, and changing the float in the prototype below to double.
       This only affects the precision in which the result is stored.
       Internally all calculations are in double precision.

Note3: You need zero order and first order bessel functions. They may not be 
       standard on all platforms. Look in the psf.c file for j0() and j1() if
       you have bessel functions with a different name. (They are in the math
       library on most unices, and you don't need to provide your own. Maybe
       it is different on Windows.)
*/



int WidefieldPSF(float *out, int x, int y, int z, double sx, 
		 double sy, double sz, double l, double na, 
		 double ri, double pr);

#endif


/// @}
