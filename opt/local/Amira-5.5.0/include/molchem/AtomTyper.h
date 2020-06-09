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
#ifndef MOLCHEM_ATOMTYPER_H
#define MOLCHEM_ATOMTYPER_H

#include "MolChemWinDLLApi.h"

class McBitfield;
template <class T> class McDArray;

namespace molchem {
    class Molecule;

    /** \brief Interface for an AtomType to contain the chemical type of an atom.
    *
    *   The type must be identifiably by an index and a string identifier.
    *   Atom Types are stored statically. Thus any instance must
    *   not be deleted.
    */

    class MOLCHEM_API AtomType {
    public:
        virtual ~AtomType() {}
        virtual int getIx() const = 0;
        virtual const char* getSymbol() const = 0;
    };

    /** \brief Interface of AtomTyper to assigns chemical types to atoms.
    *
    *   Usually the types will be defined via SMARTS strings in a file.
    *   Implementations of AtomTyper would read such files and
    *   store this information in a static array.
    * 
    *   Types are statically allocated internally. Do not delete a returned type.
    */

    class MOLCHEM_API AtomTyper {
    public:
        virtual ~AtomTyper() {}
        /** Computes atoms types
            
            \param[in] mol Molecule whose atoms will be processed
            \param[in] maks Filter bitfield defining which atoms will be processed.
                       All atoms, if null.
            \param[in|out] type Returns references to the atom types. If a filter is used
                       type may contain already computed atomtypes. The compute methods may
                       then use these atom types to derive the additional atomtypes.
                       This, however, depends on the implementation of the typer.
                       It must be either of size 0 or of size getNumAtoms() of the molcule.
            \return Number of atoms for which no atom type could be assigned 
            \exception molchem::Exception 
        */
        virtual int computeAtomTypes(Molecule* mol,McDArray<AtomType*>& type,const McBitfield* mask=0) const = 0;
        /** Return the number of atom types */
        virtual int getNumTypes() const = 0;
        /** Returns the ix'th type.*/
        virtual const molchem::AtomType* getType(int ix) const =0;
    };

}

#endif





/// @}
