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

/// @addtogroup vsvolren vsvolren
/// @{
#ifndef _VS_VOLREN_API_H
#define _VS_VOLREN_API_H

////////////////////////////////////////
// version
////////////////////////////////////////

/** Indicates the version of the library.
    You can use this symbol in order to check which version
    of the library your application is compiling against.
    The symbol combines the major and minor version in a
    four-digit number.
    \sa Vs::version() 
*/
#define VS_VOLREN_VERSION 1200

////////////////////////////////////////
// export/import declaration macro
////////////////////////////////////////

#if defined(_WIN32) && !defined(_LIB)
#  ifdef VSVOLREN_EXPORTS
#     define VSVOLREN_API  __declspec(dllexport)
#     define VSVOLREN_IMPL __declspec(dllexport)
#  else
#     define VSVOLREN_API  __declspec(dllimport)
#     define VSVOLREN_IMPL __declspec(dllimport)
#  endif
#elif defined(__GNUC__) && (__GNUC__ >= 4 )
#     define VSVOLREN_API __attribute__ ((visibility("default")))
#     define VSVOLREN_IMPL __attribute__ ((visibility("default")))
#elif defined(__GNUC__) && defined (__GNUC_MINOR__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) && !defined(VS_MEDTRONIC_VISAGE_WS_DTI)
#     define VSVOLREN_API __attribute__ ((visibility("default")))
#     define VSVOLREN_IMPL __attribute__ ((visibility("default")))
#else
#   define VSVOLREN_API 
#   define VSVOLREN_IMPL
#endif


#endif

/// @}
