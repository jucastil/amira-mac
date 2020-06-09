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
#ifndef MOLCHEM_ELEMENTTABLE_H
#define MOLCHEM_ELEMENTTABLE_H

#include "MolChemWinDLLApi.h"

namespace molchem {
    class Element;
    class ElementTablePIMPL;    
    
    /** Accessor to chemical elements.

    ElementTable can be used as an interface to the information
    in  the file elements.cfg. It offers methods to
    look up instances of elements by element name or atomic number.

    Design Pattern: Singleton. Elements as Flyweight.

    */

    class MOLCHEM_API ElementTable {
    public:
        /// Returns the static instance of ElementTable
        static const ElementTable* getElementTable() {
            if (!singletonObject)
                singletonObject = new ElementTable();
            return singletonObject;
        }
        
        /** Returns element entry with attribute @c atomicNumber.
        If there is no such element in database ::getDefaultElement() will be returned */
        const Element* getElement(int atomicNumber) const;
        
        /** Returns element entry with attribute @c symbol. Lookup is case-unsensitive.
        If there is no such element in database ::getDefaultElement() will be returned */
        const Element* getElement(const char* symbol,bool caseSensitiv=false) const;

        /** Returns a default element with atomic number 0. This element is returned whenever
            one of the get methods with a specific attribute couldn't find the element */
        const Element* getDefaultElement() const;

        /// Returns the maximal atomic number.
        int getMaxAtomicNumber() const;

    protected:
        static ElementTable* singletonObject;
        ElementTable();
        ~ElementTable();
        ElementTablePIMPL* pimpl;
    };
}

/// macro for static instance of ElementTable
#define theElementTable molchem::ElementTable::getElementTable()

#endif



/// @}
