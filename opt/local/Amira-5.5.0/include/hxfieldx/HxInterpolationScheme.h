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

/// @addtogroup hxfieldx hxfieldx
/// @{
#ifndef HX_INTERPOLATION_SCHEME_H
#define HX_INTERPOLATION_SCHEME_H

#include "HxFieldWinDLLApi.h"
#include <string.h>

template <class A, class B> class McHashTable;

/** \brief Class describing the interpolation schemes on fields.
            This class wraps the string into a persistent version 
            and provides some helper methods.
 */
class HXFIELDX_API HxInterpolationScheme {
    public:
        /** 
          */
        explicit HxInterpolationScheme (const char* name);

        /** Default interpolation.
         */
#undef None
        static const char* None;

        /** Default interpolation.
         */
        static const char* Default;

        /** Higher quality if possible. 
         */
        static const char* Quality;

        /** Interpolation by quadratic Supersplines. 
         */
        static const char * QuadSuperSplines;

        /** Trilinear Interpolation. 
         */
        static const char * Trilinear;

        /** Exact evaluation of e.g. an analytic expression.
          */
        static const char* Exact;

        /** Register interpolations schemes here.
         */

        /** equality op */
        bool operator== (const HxInterpolationScheme& other) const {
            return mName == other.mName || strcmp (mName, other.mName) == 0;
        }

        /** optimized equality op without constructing a HxFieldQuantity first */
        bool operator== (const char* other) const {
            return mName == other || strcmp (mName, other) == 0;
        }

        /** get the name of the type */
        const char* getName () const {
            return mName;
        }

        /** check if the type name is known. */
        static bool isKnown (const char* name);

    private:
        static McHashTable<const char*, const char*>& toPersistentMap ();

        const char* mName;
};

#endif

/// @}
