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

/// @addtogroup hxlatticexbase hxlatticexbase
/// @{
#ifndef HX_LATTICE_TYPE_H
#define HX_LATTICE_TYPE_H

#include "HxLatticeXBaseWinDLLApi.h"
#include <hxfield/HxCoordType.h> // this is ok, it doesn't introduce a dependency on amira, HxCoordType.h only defines an enum
#include <string.h>

template <class A, class B> class McHashTable;

/** A HxLatticeType is described by a string. 
    This class wraps the string into a persistent version 
    and provides some helper methods.
 */
class HXLATTICEXBASE_API HxLatticeType {
    public:
        /** names might vanish. Therefore, we use a persistent version of the string.
          */
        HxLatticeType (const char* name); // TODO: add explicit

        /** Construct from a HxCoordType.
          */
        HxLatticeType (HxCoordType cty);// TODO: add explicit


        /** legacy types from HxCoordType. Statically assign. 
         */
        static const char* c_undefined;

        /** legacy types from HxCoordType. Statically assign. 
         */
        static const char* c_uniform;

        /** legacy types from HxCoordType. Statically assign. 
         */
        static const char* c_stacked;

        /** legacy types from HxCoordType. Statically assign. 
         */
        static const char* c_rectilinear;

        /** legacy types from HxCoordType. Statically assign. 
         */
        static const char* c_uniform_oblique;

        /** legacy types from HxCoordType. Statically assign. 
         */
        static const char* c_stacked_oblique;

        /** legacy types from HxCoordType. Statically assign. 
         */
        static const char* c_rectilinear_oblique;

        /** legacy types from HxCoordType. Statically assign. 
         */
        static const char* c_curvilinear;


        /** check if this HxLatticeType is a HxCoordType */
        bool isHxCoordType() const;

        /** Return a HxCoordType */
        HxCoordType asHxCoordType () const;

        /** equality op */
        bool operator== (const HxLatticeType& other) {
            return mName == other.mName || strcmp (mName, other.mName) == 0;
        }

        /** optimized equality op without constructing a HxLatticeType first */
        bool operator== (const char* other) {
            return mName == other || strcmp (mName, other) == 0;
        }

        /** get the name of the type */
        const char* getName () const {
            return mName;
        }

        /** check if the type name is known. */
        static bool isKnown (const char* name);

    private:
        static McHashTable<const char*, HxCoordType>& toCoordTypeMap ();
        static McHashTable<const char*, const char*>& toPersistentMap ();

        const char* mName;
};

#endif

/// @}
