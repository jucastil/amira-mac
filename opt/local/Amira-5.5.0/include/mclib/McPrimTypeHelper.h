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

/// @addtogroup mclib mclib
/// @{
#ifndef MC_PRIMTYPE_HELPER_H
#define MC_PRIMTYPE_HELPER_H

#include "McPrimType.h"
#include "McAssert.h"

/** This macros can be useful to instantiate templates for
 *  more than one McPrimType at once.
 */
#define SWITCH_PRIM_TYPE_START(type) \
    { \
        int primtypeswitch_myint = int(type);    \
        mcdebug (MCDL_DEBUG, "switch_prim_type_start, type 0x%x", primtypeswitch_myint); \
        if (0) { \
            ; \
        }

#define INTEGER_PRIM_TYPES(operation, dat) \
          else if (primtypeswitch_myint == McPrimType::mc_uint8) { \
            operation<unsigned char> dat; \
        } else if (primtypeswitch_myint == McPrimType::mc_int16) { \
            operation<short> dat; \
        } else if (primtypeswitch_myint == McPrimType::mc_uint16) { \
            operation<unsigned short> dat; \
        } else if (primtypeswitch_myint == McPrimType::mc_int32) { \
            operation<int> dat; \
        }

#define FLOAT_PRIM_TYPES(operation, dat) \
          else if (primtypeswitch_myint == McPrimType::mc_float) { \
            operation<float> dat; \
        } else if (primtypeswitch_myint == McPrimType::mc_double) { \
            operation<double> dat; \
        }

#define COMPLEX_PRIM_TYPES(operation, dat) \
          else if (primtypeswitch_myint == McPrimType::mc_complex) { \
            operation<complex<float> > dat; \
        }

/*
    #define USERTYPE(type) \
          else if (primtypeswitch_myint == type)
*/

#define SWITCH_PRIM_TYPE_END \
          else { \
            mcdebug (MCDL_ERR, "Internal Error: unknown type (0x%x) can't be processed\n", primtypeswitch_myint);\
        } \
    }

#define INTEGER_PRIM_TYPES_1(operation, TYPE, dat) \
          else if (primtypeswitch_myint == McPrimType::mc_uint8) { \
            operation<TYPE, unsigned char> dat; \
        } else if (primtypeswitch_myint == McPrimType::mc_int16) { \
            operation<TYPE, short> dat; \
        } else if (primtypeswitch_myint == McPrimType::mc_uint16) { \
            operation<TYPE, unsigned short> dat; \
        } else if (primtypeswitch_myint == McPrimType::mc_int32) { \
            operation<TYPE, int> dat; \
        }

#define FLOAT_PRIM_TYPES_1(operation, TYPE, dat) \
          else if (primtypeswitch_myint == McPrimType::mc_float) { \
            operation<TYPE, float> dat; \
        } else if (primtypeswitch_myint == McPrimType::mc_double) { \
            operation<TYPE, double> dat; \
        }

#define COMPLEX_PRIM_TYPES_1(operation, TYPE, dat) \
          else if (primtypeswitch_myint == McPrimType::mc_complex) { \
            operation<TYPE, complex<float> > dat; \
        }


#endif

/// @}
