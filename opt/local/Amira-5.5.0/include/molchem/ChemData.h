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

/// @addtogroup molchem molchem
/// @{
#ifndef MOLCHEM_CHEMDATA_H
#define MOLCHEM_CHEMDATA_H

#include "MolChemWinDLLApi.h"

#include <mclib/McDArray.h>
#include <mclib/McString.h>
#include <mclib/McHandable.h>

namespace molchem {

    /** \brief Abstract Data Class. 
    
        ChemData can be used with smart pointers (HcHandle).
    */
    class MOLCHEM_API ChemData : public McHandable {
    public:
        virtual ~ChemData() {}
    };

    /** \brief Data Class containing one object. */
    template <class T> class MOLCHEM_API ChemSimpleData : public ChemData {
    public:
        ChemSimpleData() {};
        ChemSimpleData(T& t) { data = t;}
        T data;
    };
    
    /** \brief Data Class containing one owned pointer
    
         The pointer is owned by the instance of
         this object. This allows to supply non-smart pointers without having to create
         wrapper classes derived from McHandable. 
         The given data must be allocated on the heap. */
    template <class T> class MOLCHEM_API ChemOwnedPointer : public ChemSimpleData<T> {
    public:
        ChemOwnedPointer() { ChemOwnedPointer::data=0; }
        ChemOwnedPointer(T& t) { ChemOwnedPointer::data=t; }
        virtual ~ChemOwnedPointer() { if (ChemOwnedPointer::data) delete ChemOwnedPointer::data;}
    };

    /** \brief Data class containing multiple objects. */
    template <class T> class MOLCHEM_API ChemArrayData : public ChemData, public McDArray<T> {
    };

    /** \brief Data class containing a string. */
    class MOLCHEM_API ChemStringData : public ChemData, public McString {
    };
}
#endif


/// @}
