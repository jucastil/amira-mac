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

/// @addtogroup hxshapes hxshapes
/// @{
#ifndef MINIMIZATION_H
#define MINIMIZATION_H

#include <hxshapes/HxShapesWinDLLApi.h>

#include <mclib/McDArray.h>
#include <mclib/McMath.h>

#define GOLD 1.618034
#define GLIMIT 100.0
#define TINY 1.0e-20
#define ITMAX 100
#define CGOLD 0.3819660
#define ZEPS 1.0e-10
#define TOL 2.0e-4
#define EPS 1.0e-10
#define SHFT(a,b,c,d) (a)=(b);(b)=(c);(c)=(d);
#define SIGN(a,b) ((b) >= 0.0 ? fabs(a) : -fabs(a))

// -----------------------------------------------------------------------------------
//   BRACKETING    OF  A   MINIMUM    OF  1 DIM    FUNCTION
// starting from points x1 and x2 run downhill the funtion func until
//   f starts to grow  (see numerical recipes p.296)
// -> Returns a bracket (interval [x1,x2] and a staring value x3
//   in the intervall) around the minimum
void HXSHAPES_API getMinBracket(float& x1, 
                   float& x2, 
                   float& x3,
                   float (*func)(float));

// -----------------------------------------------------------------------------------
//  BRENT'S  MINIMIZATION   OF  1  DIM   FUNCTION
// Starting with bracket (ax,bx,cx) fit parabel into the bracket
//   and use the values of f at minimum of parabel to set new bracket 
//   (Brent's method, see numerical recipes p.299)
//   with tol is maximal error tolerance 
// -> returns xmin as minmimum of f in the original bracket 
float HXSHAPES_API brentMin(float& ax, 
               float& bx, 
               float& cx, 
               float (*f)(float), 
               float tol,
               float& xmin);

// -----------------------------------------------------------------------------------
// 1 dimensional function represented by the n-dim function 
// funccom and the line given by the root vector pcom and direction vector xcom
// -> returns value of nrfunc at vector pcom+x*xicom

float HXSHAPES_API f1dim(float x);

// -----------------------------------------------------------------------------------
// linear minimization of n-dim function func along the line given by the foot p and
// the direction xi
// -> vector giving minimum will be returned in p
void HXSHAPES_API linmin(McDArray<float>& p, 
            McDArray<float>& xi,
            float (*func)(const McDArray<float>&),
            float tolerance);

// --------------------------------------------------------------------------------------
//     CONJUGATE    GRADIENT   MINIMIZATION    OF  N DIM   SCALAR   FUNCTION
// starting with point p search the minimum of the n-dim function f with tolerance 
// ftol and using the gradient of the function df by succesive linear minimization 
// along conjugated gradients (conjugated gradient method, see numerical recipes p. 317)
// df must be of type df(point,result)
// -> returns minimum of f in p
void HXSHAPES_API cgMin(McDArray<float>& p,
           float ftol, 
           float (*f)(const McDArray<float>&), 
           void (*df)(const McDArray <float>&, McDArray <float>&));


#endif

/// @}
