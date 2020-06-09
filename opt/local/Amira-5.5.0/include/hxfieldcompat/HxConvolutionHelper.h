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

/// @addtogroup hxfieldcompat hxfieldcompat
/// @{
#ifndef HX_CONVOLUTION_HELPER_H
#define HX_CONVOLUTION_HELPER_H

#include <math.h>

#include <mclib/McStdlib.h>

/*
 * Author: Jens Kasten
 *
 * This class implements some helper functions for deriving scalar field
 * in three dimensions. These functions were proposed by Deriche (Fast
 * Algorithms for Low Level Vision, IEEE Trans. Pattern Anal.. Mach. Intell. 1989)
 * and used by Monga and Benayoun (Using Partial Derivatives of 3D Images to
 * Extract Typical Surface Features, Computer Vision and Image Understanding,
 * Vol. 61, No. 2, March, pp. 171-189, 1995).
 * The first three functions are implemented. This enables the first two
 * derivatives (Gradient + Hessian).
 * If you want to use these functions, a good choice for alpha is necessary.
 * Use 1 for first-order and 0.7 for second-order derivatives.
 */
class HxConvolutionHelper {

private:
    static double c_0(double alpha) {
        return powl(1-exp(-1*alpha),2)/(1+2*exp(-1*alpha)*alpha-exp(-2*alpha));
    }

    static double c_1(double alpha) {
        return -1*powl(1-exp(-1*alpha),3)/(2*powl(alpha,2)*exp(-1*alpha)*(1+exp(-1*alpha)));
    }

    static double c_2(double alpha) {
        return -2*powl(1-exp(-1*alpha),4)/(1+2*exp(-1*alpha)-2*exp(-3*alpha)-exp(-4*alpha));
    }

    static double c_3(double alpha) {
        return (1-exp(-2*alpha))/(2*alpha*exp(-1*alpha));
    }

public:
    //smoothing operator
    static double f_0(double x, double alpha) {
        return c_0(alpha)*(1+alpha * fabs(x))*exp(-1*alpha*fabs(x));
    }

    //first derivative operator
    static double f_1(double x, double alpha) {
        return c_1(alpha)*x*powl(alpha,2)*exp(-1*alpha*fabs(x));
    }

    //second derivative operator
    static double f_2(double x, double alpha) {
        return c_2(alpha)*(1-c_3(alpha)*alpha*fabs(x))*exp(-1*alpha*fabs(x));
    }
};

/*
 * Author: Jens Kasten
 *
 * This class implements come helper functions for deriving scalar field
 * in three dimensions. The convolutions are based on the Gauss kernel.
 */
class HxConvolutionHelperGauss {
public:
    //smoothing operator
    static double f_0(double x, double sigma) {
        return 1/(sqrt(2*M_PI)*sigma) * exp(-1*powl(x,2)/(2.0*powl(sigma,2)));
    }

    //first derivative operator
    static double f_1(double x, double sigma) {
        return -1.0/(sqrt(2*M_PI)*powl(sigma,2)) *x*exp(-1.0*powl(x,2)/(2.0*powl(sigma,2)));
    }

    //second derivative operator
    static double f_2(double x, double sigma) {
        return -1.0/(sqrt(2*M_PI)*powl(sigma,3)) *exp(-1.0*powl(x,2)/(2.0*powl(sigma,2))) +
        1.0/(sqrt(2*M_PI)*powl(sigma,5)) * powl(x,2) *exp(-1.0*powl(x,2)/(2.0*powl(sigma,2)));
    }
};
#endif

/// @}
