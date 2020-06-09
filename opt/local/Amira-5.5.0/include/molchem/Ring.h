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
#ifndef MOLCHEM_RINGBASE_H
#define MOLCHEM_RINGBASE_H

#include "MolChemWinDLLApi.h"

#include <mclib/McDArray.h>

#include "ChemObject.h"
#include "AtomContainer.h"
#include "BondContainer.h"

namespace molchem {

    class Atom;
    class Bond;
    class Logger;
    template <class T> class IteratorBase;

    /** \brief Abstract Group representing a molecular ring
    */

    class MOLCHEM_API Ring : public ChemObject, public IAtomContainer, public IBondContainer {
        friend class Molecule;
    public:
        // do not use these flags!
        enum FLAGS {
            FLAG_ISAROMATIC   =  0x00010000u,
            FLAG_VISITED      =  0x10000000u,
            FLAG_ISPLACED     =  0x20000000u
        };
        /// Return size of ring
        int getSize() const;
        /// Return index of ring in molecule
        int getIx() const;
        /// return whether ring is aromatic
        bool isAromatic() const;
        /** Returns the number of atoms that belong to this residue */
        int getNumBonds() const;
        /** Returns the ix'th atom */
        Bond* getBond(int ix) const;
        /** Returns the number of atoms that belong to this residue */
        int getNumAtoms() const;
        /** Returns the ix'th atom */
        Atom* getAtom(int ix) const;
        /** Returns whether all bonds of ring are single */
        bool isSaturated() const;
        /** Return a common bond */
        Bond* getCommonBond(const Ring* r) const;
        void getConnectedBonds(const Atom* startAtom, BondContainer& bonds) const;
        Bond* getNextBond(const Bond* b,const Atom* a) const;
        
        void getIupacEnumeration(McDArray<int>& order) const;

    protected:
        Ring* cloneShallow() const;
        Molecule* mol;
        void addAtom(Atom* a);
        void addBond(Bond* a);
        McDArray<Atom*> atoms;
        McDArray<Bond*> bonds;
        void setAromatic(bool);
        int ix;
    private:
        Ring(Molecule*);
        virtual ~Ring() {}
        static Logger* logger;
    };
}


#endif







/// @}
