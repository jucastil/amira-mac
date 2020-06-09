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
#ifndef MOLCHEM_ATOM_H
#define MOLCHEM_ATOM_H

#include "MolChemWinDLLApi.h"

class McVec3f;
class McMat4f;
template <class T> class McDArray;
class McBitfield;

#include "IGraph.h"
#include "DataContainer.h"
#include "ChemObject.h"
#include <mclib/McDArray.h>
#include <mclib/McVec3f.h>
#include <mclib/McVec2f.h>

namespace molchem {

    class Element;
    class Molecule;
    class Bond;
    class AtomContainer;
    class BondContainer;
    class Ring;
    class Logger;
    template <class T> class IteratorBase;
    
 
    /** Container of properties for one Atom.
    
        Atom contains properties of a single atom of a molecule
        like formal charge and incident bonds. 
    */

    class MOLCHEM_API Atom : public ChemObject, public INode {
        friend class Molecule;
        friend class Bond;
    public:
        // do not use these flags!
        enum FLAGS {
            FLAG_ISINRING     =  0x00010000,
            FLAG_ISALIPATHIC  =  0x00020000,
            FLAG_VISITED      =  0x10000000,
            FLAG_ISPLACED     =  0x20000000
        };

        /** Possible hybridization states.*/
        enum HybridizationState {
            HS_UNKNOWN,
            HS_sp,
            HS_sp2,
            HS_sp3,
            HS_sp3d,
            HS_sp3d2,
            HS_sp3d3,
            HS_sp3d4
        };
        virtual int getNumEdges() const;
        /// explicit + implicit degree
        int getDegree() const;
        /** Returns atomic number */
        int getAtomicNumber() const;

        /** Returns explicit valency.*/
        int getExplicitValence() const;

        /** Returns valency.*/
        int getValence() const;

        /** Returns valency to heavy atoms.*/
        int getHeavyValence() const;

        /** Returns whether atom has an odd number of aromatic bonds, which is invalid.*/
        bool hasIncorectAromaticity() const;

        /** Returns whether atom has an incident double bond.*/
        bool hasDoubleBond() const;
        /** Returns whether atom has an incident single bond.*/
        bool hasSingleBond() const;
        /** Returns whether atom has an incident triple bond.*/
        bool hasTripleBond() const;
        /** Returns whether atom has an incident aromatic bond.*/
        bool hasAromaticBond() const;

        /** Is a dummy atom - i.e. has default element with atomic number 0 ? */
        bool isDummy() const;

        /** Is a carbon ? */
        bool isC() const;

        /** Is a nitrogen ? */
        bool isN() const;

        /** Is an oxygen ?*/
        bool isO() const;

        /** Is a hydrogen ?*/
        bool isH() const;

        /** Is a polar hydrogen ?*/
        bool isPolarH() const;

        /** Is an apolar hydrogen ?*/
        bool isApolarH() const;

        /** Is a sulphur ?*/
        bool isS() const;

        /** Is a phosphorus ?*/
        bool isP() const;

        /** Returns number of lone electron pairs in the outer shell.*/
        int getNumLoneElectronPairs() const;
        
        /** Returns whether atom has a lone electron pair in the outer shell which takes part in
            an aromatic bond.*/
        bool hasLonePiElectronPair() const;

        /** Returns wether atom is a radical, i.e. whether it possesses an 
            unpaired unbonded electron.*/
        bool hasUnpairedElectron() const;

        /** same as hasUnpairedElectron */
        bool isRadical() const;

        /** Returns oxidation state. */
        int getOxidationState() const;

        /** Returns hybridization state. */
        HybridizationState getHybridization() const;
        
        /** Returns hybridization label (sp,sp2,sp3,sp3d...). */
        const char* getHybridizationLabel() const;
        
        /** Returns the edge which connects *this atom with atom n.
            If n is no neighbor 0 will be returned. */
        Bond* isNeighbor(const Atom* n) const;
        
        /** Same as isNeighbor(). */
        Bond* getBond(const Atom* n) const {
            return isNeighbor(n);
        }
        
        /** Returns number of neighbors. Same as getNumBonds(). */
        int getNumNeighbors() const;

        /** Returns number of neighbors which are set in mask. */
        int getNumNeighbors(const McBitfield& mask) const;
        
        /** Returns the i'th neighbor.*/
        Atom* getNeighbor(int i) const;
        
        /** Returns number of explicit incident bonds.*/
        int getNumBonds() const;

        /** Returns number of explicit incident bonds of given type.*/
        int getNumBonds(int t) const;
        
        /** Returns number of explicit incident bonds which are connection to an atom set in mask.*/
        int getNumBonds(const McBitfield& mask) const;

        /** Returns number of explicit incident bonds which are connection to an atom set in mask.*/
        int getDegree(const McBitfield& mask) const;

        /** Returns number of explicit bonds to hydrogen atoms.*/
        int getNumHBonds() const;

        /** Returns number of bonds to hydorgen atoms. Includes bonds to implicit hydrogens */
        int getHDegree() const;

        /** Returns number of bonds to heavy atoms. */
        int getNumHeavyBonds() const;
        
        /** Returns number of bonds of given bond order. Includes bonds to implicit hydrogens.*/
        int getDegree(int bondOrder) const;
        int getDegree(const McBitfield& abf,int bondOrder) const;

        /** Returns number of explicit bonds to atoms of given atomic-number.*/
        int getNumBondsToAtomicNumber(int atomicNumber) const;

        /** Returns number of explicit bonds to atoms of given atomic-number.*/
        int getNumBondsToAtomicNumber(int atomicNumber,int bondorder) const;
        
        /** Returns number of explicit bonds to atoms of given atomic-number.*/
        int getDegreeToAtomicNumber(int atomicNumber) const;

        /** Returns number of explicit bonds of an atomicNumber which are neighbors of this node 
        where bond has to be of bondOrder */
        int getDegreeToAtomicNumber(int atomicNumber,int bondOrder) const;

        /** get the number neighbors of a certain atomic number 
        each entry ix of array will contain number of such neighbors of atomic number ix
        the array will be resized to MAX_ATOMICNUMBER+1 and filled with 0 by this method
        if bondOrder>0 only bonds of the given bond Order will be considered */
        void getDegreePerAtomicNumber(McDArray<int>& bondNumberPerAtomicNumber, int bondOrder=0) const;
        
        /** get the difference to standard valency. This is  (explicit valence + implicit valence - formal charge) - standard_valency 
        */
        int getDifferenceToStandardValency() const;

        /** Returns i'th bond.*/
        Bond* getBond(int i) const;

        /** Returns whether atom is neighbor of an atom with the given atomic-number.
            If such an atom exists, the pointer will be returned.*/
        Atom* isBondedToAtomicNumber(int atomicNumber) const;

        /** Returns whether atom is neighbor of an atom with the atomicNumber 
            connected by a bond of the given bond-order. 
            If such an atom exists, the pointer will be returned.*/
        Atom* isBondedToAtomicNumber(int atomicNumber,int bondOrder) const;

        /** Returns all atoms of an atomicNumber which are neighbors of this atom. */
        void getNeighborsOfAtomicNumber(int atomicNumber,AtomContainer& neighbors) const;

        /** Returns all nodes of an atomicNumber which are neighbors of this node  
            where the connecting bond has to be of bondOrder. */
        void getNeighborsOfAtomicNumber(int atomicNumber,int bondOrder,
            AtomContainer& neighbors) const;

        /** Returns all bonds to atoms of an atomicNumber which are neighbors of this atom.*/
        void getBondsToAtomicNumber(int atomicNumber,BondContainer& bc) const;

        /** Returns all bonds to atoms of an atomicNumber which are neighbors of this atom 
            and which have the given bond-order. */
        void getBondsToAtomicNumber(int atomicNumber,int bondOrder,
            BondContainer& bc) const;


        /** Return a new valid bond vector for the first implicit hydrogen.
        If no implicit hydrogen exists false will be returned and
        the returned bond vector will be of valid length toward a
        direction which has most space. */
        bool getImplicitHydrogenBondVectors(McDArray<McVec3f>& vec) const;
        bool getBondVectors(BondContainer& b, McDArray<McVec3f>& vec) const;
        /** Same as getBondVectors, but sort them according to distance towards a neighbor A1 if
            a connected chain is A1-A2-(this). Therefore the first vec will be cis like, while
            the last one will be trans like.*/
        bool getBondVectorsSorted(BondContainer& b, McDArray<McVec3f>& vec) const;
        /** Returns element. */
        const Element* getElement() const;
        /** Returns symbol of the element. */
        const char* getElementSymbol() const;
        /** Returns formal charge. */
        int getFormalCharge() const;
        /** Sets the formal charge.*/
        void setFormalCharge(int c);
        /** Return number of implicit hydrogen atoms. */
        int getImplicitHNum() const;
        /** Sets the number of implicit hydrogens. */
        void setImplicitHNum(int hNum);
        /** Return the 3D coordinate. */
        McVec3f& getPos() const;
        /** Sets the 3D coordinate. */
        void setPos(const McVec3f& co);
        void setPos(const McVec3d& co);
        /** Returns number of SSSR rings that atom is part of.*/
        int getNumRings(int size=0) const;
        /** Returns whether atom is part of a ring.*/
        bool isInRing(int size=0) const;
        /** Returns whether atom is part of an aromatic ring.*/
        bool isInAromaticRing(int size=0) const;
        /** Returns whether atom is part of a non-aromatic ring.*/
        bool isInNonAromaticRing(int size=0) const;
        /** Returns mass of atom. */
        float getMass() const;
        /** Returns whether atom has at least two aromatic bonds.*/
        bool isAromatic() const;
        /** Returns whether atom is aromatic as perceived by AssignAromaticity. */
        bool isAromaticPerceived() const;
        /** Returns index of atoms in molecule. */
        int getIx() const;
        /** Returns external index.*/
        int getEIx() const;
        /** Sets external index which can be used to associate atom with 
            external datastructures. External index is -1 if not explicitly set.*/
        void setEIx(int eix);
        /** Returns iterator over all explicit bonds.*/
        IteratorBase<Bond>* getBondIterator() const;
        /** Returns container with all explicit bonds.*/
        void getBonds(BondContainer& bonds) const;
        /** Returns container with all explicit bonds which connect to an atom set in the mask.*/
        void getBonds(BondContainer& bonds,const McBitfield& mask) const;
        /** Returns container with all explicit neighbors.*/
        void getNeighbors(AtomContainer& atoms) const;
        /** Returns container with all explicit neighbors which are in the given atom mask.*/
        void getNeighbors(AtomContainer& atoms,const McBitfield& mask) const;
        /** Returns iterator over all explicit neighbors.*/
        IteratorBase<Atom>* getNeighborIterator() const;
        /** Returns iterator over all rings that the atoms is part of.*/
        IteratorBase<Ring>* getRingIterator() const;
        /** Returns the parent molecule of the atoms.*/
        Molecule* getParent() const;
        /** Returns the distance towards a second atom.*/
        float getDistance(const Atom* a) const;
        /** Returns distance between two atoms.*/
        float static getDistance(const Atom* a1,const Atom* a2);
        /** Returns angle between 3 atoms a1-a2-a3 in degrees.*/
        float static getAngle(const Atom* a1, const Atom* a2, const Atom* a3);
        /** Returns torsion between 4 atoms a1-a2-a3 in degrees.*/
        float static getDihedral(const Atom* a1,const Atom* a2,const Atom* a3,const Atom* a4);
        
        /** Return whether atom is a chiral centre.*/
        bool isChiral() const;
        /** Returns number of pi bonds that this atom forms.*/
        int getNumPiBonds() const;
        /** Returns number of sigma bonds that this atom forms.*/
        int getNumSigmaBonds() const;
        /** Sets the element.*/
        void setElement(const Element* e);
        /** Sets the atomic number.*/
        void setAtomicNum(int n);

        virtual IEdge* getEdge(int i) const;
    private:
        // ---- methods
        Atom* getSecondOrderNeighbor(const BondContainer& b) const;
        // will get the direction vector of a pi bond pi orbital. Returns false if none found.
        bool getPiVector(McVec3f& pi) const;
        Atom* cloneShallow() const;
        int getBondIx(Bond* b) const;
        bool setHybridization(HybridizationState s);

        // ---- member variables 
        McDArray<molchem::Bond*> bonds;
        int formalCharge:16;// default 0
        int implicitHNum:16;// default 0
        const Element* e;
        int ix;
        int eix;
        McVec3f pos3;
        Molecule* mol;
        Atom(Molecule* m);
        virtual ~Atom() {}
        static Logger* logger;
    };
}

#endif

















/// @}
