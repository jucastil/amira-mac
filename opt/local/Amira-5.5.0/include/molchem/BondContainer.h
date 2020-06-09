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
#ifndef MOLCHEM_BONDCONTAINER_H
#define MOLCHEM_BONDCONTAINER_H

#include "MolChemWinDLLApi.h"

#include <mclib/McDArray.h>
class McString;

namespace molchem {

    class Bond;
    class Molecule;
    class BondContainer;
    template <class T> class IteratorBase;

    /** \brief Interface for structures containing a set of bonds 
    */
    class MOLCHEM_API IBondContainer {
    public:
        virtual ~IBondContainer() {}
        /** Returns the number of atoms that belong to this residue */
        virtual int getNumBonds() const = 0;
        /** Returns the ix'th atom */
        virtual Bond* getBond(int ix) const = 0;
        /** Return the index of the bond in the container. */
        virtual int getBondIx(const Bond* b) const;
        /** Return all Bond in an BondContainer */
        virtual void getBonds(BondContainer& a) const;
        /** Returns iterator over all atoms (undefined order) */
        virtual IteratorBase<Bond>* getBondIterator() const;
        /* Returns a string of all atom indices. Mainly for debugging.*/
        McString getBondIndexString() const;
    };

    /** \brief Implementation of IBondContainer as a McDArray.
    */
    class MOLCHEM_API BondContainer : public IBondContainer {
    public:
        /** Contructror */
        BondContainer() {};
        /** Copy Constructor */
        BondContainer(const McDArray<Bond*>& c) : bonds(c) {};
        /** Copy Constructor */
        BondContainer(const IBondContainer& c) {(*this)=c;}
        /** */
        virtual ~BondContainer() {}
        /** Copy Operator */
        BondContainer& operator=(const IBondContainer& c);
        /** Returns the number of atoms. */
        virtual int getNumBonds() const { return size();}
        /** Returns the ix'th atom. */
        virtual Bond* getBond(int ix) const { return bonds[ix];}
        /** */
        int size() const {return bonds.size();}
        /** */
        inline void append(const Bond* a) {bonds.append((Bond*)a);}
        /** */
        void append(const IBondContainer& a);
        /** */
        void resize(int size) {bonds.resize(size);}
        /** */
        Bond*& operator[](int i) const {return (Bond*&)bonds[i];}
        /** */
        void set(int ix, const Bond* b) {bonds[ix]=(Bond*)b;}
        /** */
        Bond*& last() const {return (Bond*&)bonds.last();}
        /** */
        void removeLast(int ix=1) {bonds.removeLast(ix);}
        /** */
        void clear() {bonds.clear();}
    protected:
        McDArray<Bond*> bonds;
    };
}

#endif




/// @}
