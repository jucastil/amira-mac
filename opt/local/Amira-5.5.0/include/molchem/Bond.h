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
#ifndef MOLCHEM_BONDBASE_H
#define MOLCHEM_BONDBASE_H

#include "MolChemWinDLLApi.h"

#include "DataContainer.h"
#include "FlagContainer.h"
#include "ChemObject.h"
#include "IGraph.h"

#include <mclib/McDArray.h>

namespace molchem {
    
    class Atom;
    class Molecule;
    class Ring;
    template <class T> class IteratorBase;
  
    /** Bond contains all fixed properties related to a single bond
        including the connected atoms  */

    class MOLCHEM_API Bond : public ChemObject, public IEdge {
        friend class Molecule;
    public:
        // do not use these flags!
        enum FLAGS {
            VISITED      =  0x10000000,
            ISPLACED     =  0x20000000,
            UP           =  0x01000000,
            DOWN         =  0x02000000
        };

        /** Possible bond orders.*/
        enum BondOrder {
            BO_undefined=0,
            BO_single=1,
            BO_double=2,
            BO_triple=3,
            BO_aromatic=4
        };

        /** Returns the neighbour of Atom a that is connected via this bond.
            0 if there is none. */
        Atom* getNeighbor(const Atom* a) const;

        /** Returns perceived aromaticity as calculated by Molecule::assignAromaticity() */
        bool isAromaticPerceived() const;
        
        /** Return fixed aromaticity (i.e. is the bond order aromatic)
            If the molecule is assigned a Kekule structure this will return false, even if
            the bond is part of an aromatic ring system. 
            To get ring aromaticity use the function isAromaticPerceived().
        */
        bool isAromatic() const;

        /** Is a single bond? */
        bool isSingle() const;

        /** Is a double bond? */
        bool isDouble() const;

        /** Is a triple bond? */
        bool isTriple() const;

        /** Returns the bond order symbol. \see BondTable::getBondSymbol.*/
        char getBondOrderSymbol() const;
        
        /** Returns the bond string. \see BondTable::getBondString.*/
        void getBondString(McString& str) const;

        /** Returns iterator over all rings which contain this bond.*/
        IteratorBase<Ring>* getRingIterator() const;
        /** Returns iterator over all bonds directly connected to this bond.*/
        IteratorBase<Bond>* getBondIterator() const;

        /** Returns the first atom connected by the bond. Order is undefined.*/
        Atom* getAtom1() const;

        /** Returns the second atom connected by the bond. Order is undefined.*/
        Atom* getAtom2() const;

        /** Returns the give atom. Index must be either 0 or 1.*/
        Atom* getAtom(int ix) const;

        /** Returns the order of the bond.*/
        int getBondOrder() const;

        /** Sets the order of the bond. */
        void setBondOrder(int bondOrder);
        /** Returns true if bonds have (at least) one common atom. */
        Atom* isConnected(Bond* b) const;
        /** Return whether bond is in a ring of a certain size
            If size argument is omitted, arbitrary sizes will be allowed. */
        bool isInRing(int size=0) const;
        /** Return whether bond is in an aromatic ring of a certain size
            If size argument is omitted, arbitrary sizes will be allowed.  */
        bool isInAromaticRing(int size=0) const;
        /** return whether bond is in a non-aromatic ring of a certain size.
            If size argument is omitted, arbitrary sizes will be allowed. */
        bool isInNonAromaticRing(int size=0) const;
        /** Returns parent molecule of bond.*/
        Molecule* getParent() const;
        /** Returns index of bonds in molecule.*/
        int getIx() const;
        /** Returns external index of bond.*/
        int getEIx() const;
        /** Sets external index which can be used to associate bond with bonds in external
            data structures. -1 if not explicitly set.*/
        void setEIx(int eix);
        virtual INode* getNode1() const;
        virtual INode* getNode2() const;

        bool isUp() const { return getFlag(UP);}
        bool isDown() const { return getFlag(DOWN);}
        void setUp() { setFlags(UP);}
        void setDown() { setFlags(DOWN);}

    private:
        // ---- methods
        Bond* cloneShallow() const;
        /* the function will automatically deregister the bond from the old atom (if one existed) 
           an set and register the new one. 0 may be used to just deregister it */
        void setAtom1(Atom*);
        void setAtom2(Atom*);
        void addRing(const Ring* r);
        void removeRing(const Ring* r);
        Bond(Molecule*);
        // automatically deregisters itself from the atoms it connects
        virtual ~Bond();
        // ---- member variables 
        int ix:30; 
        int eix:30;
        Molecule* mol;
        Atom* a1; 
        Atom* a2;
        int bondOrder:4;
        McDArray<Ring*> rings;
    };

}

#endif













/// @}
