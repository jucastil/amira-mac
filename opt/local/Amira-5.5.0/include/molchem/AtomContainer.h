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
#ifndef MOLCHEM_ATOMCONTAINER_H
#define MOLCHEM_ATOMCONTAINER_H

#include "MolChemWinDLLApi.h"

#include <mclib/McDArray.h>
#include "Atom.h"
class McString;

namespace molchem {

    class Bond;
    class Molecule;
    class AtomContainer;
    class BondContainer;
    template <class T> class IteratorBase;

    /** \brief Interface for structures containing a set of atoms 
    */
    class MOLCHEM_API IAtomContainer {
    public:
        virtual ~IAtomContainer() {}
        /** Returns the number of atoms that belong to this residue */
        virtual int getNumAtoms() const = 0;
        /** Returns the ix'th atom */
        virtual Atom* getAtom(int ix) const = 0;
        /** Returns iterator over all atoms (starting from atom of index start in 
            direction dir (true is incresing index, false is decreasing index) */
        virtual IteratorBase<Atom>* getAtomIterator(int start, bool dir) const;
        /** Returns iterator over all atoms (undefined order) */
        virtual IteratorBase<Atom>* getAtomIterator() const;
        /** Return all Atoms in an AtomContainer */
        virtual void getAtoms(AtomContainer& a) const;
        /** Returns index of atom in container. -1 if not found. */
        virtual int getAtomIx(const Atom* a) const;
        /* Returns a string of all atom indices. Mainly for debugging.*/
        McString getAtomIndexString() const;
    };

    /** \brief Implementation of IAtomContainer as a McDArray */
    class MOLCHEM_API AtomContainer : public IAtomContainer, public McDArray<Atom*> {
    public:
        /** Contructror */
        AtomContainer() {}
        /** Copy Constructor */
        AtomContainer(const McDArray<Atom*>& c) : McDArray<Atom*>(c) {}
        /** Copy Constructor */
        AtomContainer(const IAtomContainer& c) {(*this)=c;}
        /** */
        virtual ~AtomContainer() {}
        /** Copy Operator */
        AtomContainer& operator=(const IAtomContainer& c);
        /** Returns the number of atoms. */
        virtual int getNumAtoms() const { return this->size();}
        /** Returns the ix'th atom. */
        virtual Atom* getAtom(int ix) const { return (*this)[ix];}
        /** */
        void append(const IAtomContainer& a);
        /** */
        void append(const Atom* a) { McDArray<Atom*>::append((Atom*)a);}
        /** */
        void set(int i, const Atom* a) {(*this)[i]=(Atom*)a;}
        //void sortByIx
    };

}

#endif




/// @}
