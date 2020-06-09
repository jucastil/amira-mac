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
#ifndef MOLCHEM_ELEMENT_H
#define MOLCHEM_ELEMENT_H

#include "MolChemWinDLLApi.h"

#include <mclib/McDArray.h>
#include <mclib/McString.h>

namespace molchem {
    /** \brief Container of properties of a chemical element.
    
    Element contains properties of a chemical element. 
    Static instances of Element can be obtained by the molchem::ElementTable.

    Design Pattern: Flyweight

    */
    class MOLCHEM_API Element {
        friend class ElementTablePIMPL;
    public:
        /// returns atomic number (0 if default element)
        int getAtomicNumber() const;
        /// returns radius [Angstroem]
        float getRadius() const;
        /// returns short name
        const char* getSymbol() const;
        /// return full name
        const char* getName() const;
        /// return masss of the most stable or common isotope
        float getMass() const;
        /// return orbital configuration string
        const char* getConfiguration() const;
        ///
        int getStandardValency() const;
        bool hasOddStandardValency() const;
        ///
        float getPaulingElectroNegativity() const;
        /// get group number in periodic table (1...18)
        int getGroup() const;
        /// get period number in periodic table (1...7)
        int getPeriod() const;
        /// Different Specifications of element in periodic table
        bool isDummy() const;
        bool isAlkaliMetal() const;
        bool isAlkalineEarthMetal() const;
        bool isTransitionMetal() const;
        bool isMetalloid() const;
        bool isPoorMetal() const;
        bool isHalogen() const;
        bool isNobleGas() const;
        bool isLanthanide() const;
        bool isActinide() const;
        bool isMetal() const;
        bool isNonMetal() const;

        /// Number of electrons in the outer valence shell
        int getNumOuterShellElectrons() const;
        /// Number of missing electrons to fill up outer valence shell
        int getNumMissingOuterShellElectrons() const;

        const McDArray<int>& getValencies() const;
        
    protected:
        Element();
        ~Element();
        McString symbol; 
        McString name;
        int atomicNumber;
        float radius;
        int group;
        McString configuration;
        int standardValency;
        McDArray<int> valencies;
        float mass;
        float paulingElectroNegativity;
    };
}


#endif




/// @}
