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

/// @addtogroup hxcore hxcore
/// @{
#if !defined(HX_OS_IRIX) && !defined (HX_OS_MACX)

    #define ffloor(a)   ((float) floor((float)(a)))
    #define fceil(a)    ((float) ceil((float)(a)))
    #define facos(a)    ((float) acos((float)(a)))
    #define fasin(a)    ((float) asin((float)(a)))
    #define fcos(a)     ((float) cos((float)(a)))
    #define fsin(a)     ((float) sin((float)(a)))
    #define fsqrt(a)    ((float)sqrt((float)(a)))
    #define fatan2(a,b) ((float)atan2((float)(a),(float)(b)))
    #define fatan(a)    ((float)atan((float)(a)))

    #if !defined(HX_OS_LINUX) && !defined(HX_OS_WIN) && !defined(HX_OS_MACX)
        #define floorf(a)   ((float) floor((float)(a)))
        #define ceilf(a)    ((float) ceil((float)(a)))
    #endif

    // HP-UX has powf() and log10f() !!
    #if defined(HX_OS_SUNOS) || defined (HX_OS_MACX)
        #define powf(a,b)   ((float)pow((float)(a),(float)(b)))
        #define log10f(a)   ((float)log10((float)(a)))
        #define atan2f(a,b)   ((float)atan2((float)(a),(float)(b)))
    #endif

#endif

/// @}
