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
#ifndef MOLCHEM_MOLECULEBASE_H
#define MOLCHEM_MOLECULEBASE_H

#include "MolChemWinDLLApi.h"

#include <mclib/McString.h>
#include <mclib/McDArray.h>
#include <mclib/McHandable.h>
#include <mclib/McTuple.h>

#include "ChemObject.h"
#include "AtomContainer.h"
#include "BondContainer.h"

class McBitfield;
class MolTopology;
class McVec3f;
class McVec2f;
class McRotation;
class McMat4f;
class McBox3f;
class McBox2f;

template <class T> class McGeneralTree;
template <class T> class McDMatrix;

/** \namespace molchem
   \brief MolChem library

   In the following we will discuss some design considerations of this library

   Difference to amiraMol's molecule library:

   - data structure implementation offers much better performance when editing
   - specialized onto a few basic abstraction levels of the molecule and attributes thereof
     -> less flexible but more specialized functionality
   - data concept more based on chemical thinking than on visualization needs
   - data structure based on graph like concept. Easy implementation of graph theory algorithms

   Note for programmers changing this package:
   For the automatic update concept to work it is necessary to only manipulate the
   data structure via the designated functions
   low level function in atom/bond ... use assertion to guarantee that data structure is up to date
   (only checked for debug version)
   high level function (like assignCoordinates) use method assertFlags and thus throw an exception

*/

namespace molchem
{
    class Molecule;
    class Atom;
    class Bond;
    class Ring;
    class Residue;
    class Logger;
    class IPointSet2f;
    class IPointSet3f;
    class IGraph;
    template <class T> class IteratorBase;
    template <class T> class IteratorBaseGraphTraversal;

    typedef McTuple<int,2> IntPair;
    typedef McTuple<int,3> IntTri;
    typedef McTuple<int,4> IntQuad;

    typedef McTuple<Atom*,2> AtomPair;
    typedef McTuple<Atom*,3> AtomTri;
    typedef McTuple<Atom*,4> AtomQuad;

    typedef McTuple<Bond*,2> BondPair;

    /** Container of atoms and bonds and residues


    Iterators:
    IteratorBase allows iterating over all atoms and bonds. The IteratorBase should be
    stored in an Iterator, which implements a smart pointer. Usage would be like this:

    Iterator<Atom> atom;
    for (atom = mol->getAtomIterator(); atom ; ++atom)
        ...

    Why are iterators returned as IteratorBase pointers and not as McHandles immediately?
    To allow for polymorphy if the data class implementations are seperated form the other
    classes.

    Additionally atoms and bonds can be obtained via their index.

    Indices are unique and continuous. Indices stay constant, except if groups are removed.
    Adding groups does not invalidate indices.

    Why continuous indices?

    Has the disadvantage that removing groups invalidates all dependent data structures that use indices.
    But: Many algorithms can be programmed much more efficient when using continous indices.

    */

    class MOLCHEM_API Molecule :
        public ChemObject, public IAtomContainer, public IBondContainer,  public McHandable {
    public:
        /**
            ---- Which type of updating? ----

            We don't want to update everything for each change.
            A sequence of invalidating changes that don't require a certain up to date property
            should be possible without the need to update the property consecutively.
            => No automatic push updating (on invalidation)

            Still, the user should not need to guarantee that certain properties are up to date.
            Because of difficult dependencies of data this would make using this module very cumbersome indeed.
            => No manual updating

            => Automatic pull updating (on demand)
            Methods request certain properties to be up to date as a precondition. If not the
            properties are regenerated.

            ---- How is a property invalidated? ----

            Automatic up to date flagging of properties leads to a huge expense in all editing methods.
            (Example rings: For each change in a bond it needs to be checked whether it breaks
            a ring or potentially closes a new ring.)  Of course the flagging could be as conservative as
            possible (Example rings: Each bond change invalidates rings). However, this decreases efficiency,
            and even then each get set method need to still call touch methods.

            Thats why the user has to decide which info he invalidated.
            When only editing hydrogens for example he would know that HAS_RINGS does
            not need to be reset. Hints will be given in the description of the editing methods.

            ---- Implementation ----

            Flags that indicate state of molecule related information.
            Flags may be set by external methods that create the molecule.
            Flags will be set by methods that compute the flag related information
            (eg. findRings) and will be unset by methods that change the molcule.

            If in the description of a method a flag is mentioned as 'required' then this
            method will call assertFlags.

            assignStandardImplicitHNum()    HAS_IMPLCIT_HNUM
            assignImplicitHNum()            HAS_IMPLCIT_HNUM
            assignFormalCharges()           HAS_FORMAL_CHARGES
            assignRings()                   HAS_RINGS
            assignAromaticity()             HAS_AROMATICITY
            assignRings()                   HAS_RINGS
            assignAromaticity               HAS_AROMATICITY
            assignKekuleNonAromatic()       HAS_NRKEKULE
            assignKekule()                  HAS_NRKEKULE

        */
        enum HAS_FLAGS {
            /// are formal charges existant for all atoms and up to date ?
            HAS_FORMAL_CHARGES       = 0x00100000u,
            /// has the molcule up to date implicit hydroegns
            HAS_IMPLICIT_HNUM        = 0x00200000u,
            /// has the molcule up to date rings ?
            HAS_RINGS                = 0x01000000u,
            /// is aromaticity existant for all atoms and bonds and up to date ?
            HAS_AROMATICITY          = 0x02000000u,
            /// has the molcule an up to date non aromatic ring kekule structure ?
            HAS_KEKULE               = 0x04000000u,
            /// has the molcule an up to date non aromatic ring kekule structure ?
            HAS_NRKEKULE             = 0x08000000u,
            HAS_COORD3               = 0x40000000u,
            HAS_ALL                  = 0xFFF00000u,
            HAS_UPON_CONSTRUCTION    = HAS_FORMAL_CHARGES|HAS_COORD3

        };
        enum TOUCH_FLAGS {
            TOUCH_ATOM_CHANGE        = HAS_RINGS|HAS_NRKEKULE|HAS_AROMATICITY,
            TOUCH_ATOM_PROP          = HAS_NRKEKULE|HAS_AROMATICITY,
            TOUCH_BOND_CHANGE        = TOUCH_ATOM_CHANGE,
            TOUCH_BOND_PROP          = HAS_AROMATICITY|HAS_AROMATICITY|HAS_NRKEKULE
        };

        // -----------------------------------------------------------------------------
        //                    Atoms, Bonds, Rings, Residues
        // -----------------------------------------------------------------------------
        /** @name Groups */
        //@{

        /** Returns iterator over all rings (undefined order).

            requires assignRings()
        */
        IteratorBase<Ring>* getRingIterator() const;

        /** Return newly allocated atom with sepcific atomic number
        */
        Atom* newAtom(int atomicNumber);

        /** Return newly allocated bond connection atoms @c a1 and @c a2, and of specific bondorder
        */
        Bond* newBond(Atom* a1,Atom* a2,int bondOrder);

        /** Returns number of atoms
        */
        int getNumAtoms() const;
        /** Returns number of bonds
        */
        int getNumBonds() const;
        /** Returns number of rings

            Requires assigned rings.
        */
        int getNumRings() const;
        // returns number of rings of given size
        int getNumRings(int size) const;

        /** Delete atom and incident bonds. Iterators may loose validity */
        void deleteAtom(Atom*);

        /** Delete atoms and incident bonds. Iterators may loose validity.
            Faster than deleting atoms one by one.
            If your are using an AtomContainer that is not managed by molecule,
            the content will become invalid. */
        void deleteAtoms(const IAtomContainer& atoms);

        /** Delete all atoms. Iterators may loose validity */
        void clearAtoms();

        /** Delete bond. Iterators may loose validity */
        void deleteBond(Bond*);

        /** */
        void remaxAtoms(int max);

        /** */
        void remaxBonds(int max);

        /** Delete bond. Iterators may loose validity.
            Faster than deleting bonds one by one. */
        void deleteBonds(const IBondContainer& bonds);

        /** Delete all bonds. Iterators may loose validity. */
        void clearBonds();

        /** Deletes ring. Iterators may loose validity. */
        void deleteRings(const McDArray<Ring*>& );

        /** Delete all rings. Iterators may loose validity. */
        void clearRings();


        /** Returns the ix'th atom of molecule. */
        virtual Atom* getAtom(int ix) const;

        /** Returns the ix'th atom of molecule. */
        virtual Bond* getBond(int ix) const;

        /** Returns the ix'th ringm of molecule.

            Requires assigned ring.
        */
        Ring* getRing(int ix) const;

        /** Returns the ix'th ringm of molecule.

            Requires assigned ring.
        */
        void getRings(McDArray<Ring*>& rings) const;

        /** return the Bond which connects the aix1'th atom with the aix2'th
            Rerturns 0 If no such bond exists. */
        Bond* getBond(int aix1, int aix2) const;

        /** Deletes all atoms and bonds from molecule. Iterators may loose validity. */
        void clear();

        //@}

        // -----------------------------------------------------------------------------
        //                                  Graph
        // -----------------------------------------------------------------------------
        /** @name Graph */
        //@{

        /** Returns iterator which breadth-first traverses the container starting at at atom a
            If the graph has more than one connection component not all atoms will be visited  */
        virtual IteratorBaseGraphTraversal<Atom>* getAtomBreadthFirstIterator(const Atom* a) const;

        /** Same as above, but restricts iteration to atoms set in bf */
        virtual IteratorBaseGraphTraversal<Atom>* getAtomBreadthFirstIterator(const Atom* a,const McBitfield& bf) const;

        /** Returns iterator which depth-first traverses the container starting at at atom a
            If the graph has more than one connection component not all atoms will be visited */
        virtual IteratorBaseGraphTraversal<Atom>* getAtomDepthFirstIterator(const Atom* a) const;

        /** Same as above, but restricts iteration to atoms set in bf */
        virtual IteratorBaseGraphTraversal<Atom>* getAtomDepthFirstIterator(const Atom* a,const McBitfield& bf) const;

        /** Partitions the Molecule into systems of rings and chains

            Requires assigned rings */
        void partitionIntoRingSystemsAndChains(McDArray<McDArray<Ring*> >& rings,McDArray<AtomContainer >& chains) const;
        /** Returns the longest chain of mask. Masked part of molecule must not
            contain cycles but may consist of multiple connection components.*/
        void getLongestChain(const McBitfield& cc,AtomContainer& chain) const;
        /** Returns the longest chain of mask. Masked part of molecule must not
            contain cycles but may consist of multiple connection components.*/
        void getLongestChain(const Atom* startAtom,const McBitfield& cc,AtomContainer& chain) const;
        /** */
        void getShortestPath(const Atom* startAtom, const Atom* endAtom,const McBitfield& cc,AtomContainer& path) const;
        /** \exception Exception*/
        void getShortestPath(const Atom* startAtom, const Atom* endAtom,const McDArray<int>& shortestPathArray,AtomContainer& path) const;
        /** Returns all connection components- */
        void getConnectionComponents(McDArray<AtomContainer >& c) const;
        /** Same as above but resticts the search to atoms in bf */
        void getConnectionComponents(const McBitfield& bf,McDArray<AtomContainer >& c) const;
        /** Grows connection component starting at atom startAtom in direction of bond directionBond, which must be a
            bond incident to startAtoms. Elements will be appended to result, which will not be cleared.
            startAtom will be the first element appended element, the remaining elements are appended in breadth first order.

            \exception Exception
        */
        void growConnectionComponent(const Atom* startAtom, const Bond* directionBond,AtomContainer& result) const;

        /** Generates list containing which atoms are 1-2 bonded to each atom. Atom indices are sorted in ascending order. */
        void getCouple12(McDArray<McDArray<int> >& couple12) const;
        /** Generates list containing which atoms are 1-3 bonded to each atom. Atom indices are sorted in ascending order. */
        void getCouple13(const McDArray<McDArray<int> >& couple12,McDArray<McDArray<int> >& couple13) const;
        /** Generates list containing which atoms are 1-4 bonded to each atom. Atom indices are sorted in ascending order. */
        void getCouple14(const McDArray<McDArray<int> >& couple12,const McDArray<McDArray<int> >& couple13,McDArray<McDArray<int> >& couple14) const;

        //@}

        // -----------------------------------------------------------------------------
        //                                  Converstions
        // -----------------------------------------------------------------------------
        /** @name Group Sets - Operations and Conversions */
        //@{

        /** Converts bitfield mask of atoms into an array */
        void atomBitfieldToAtomArray(const McBitfield& bf,AtomContainer& a) const;
        void atomArrayToIndexArray(const IAtomContainer& a,McDArray<int>& array) const;
        /** Converts bitfield mask of bonds into an array */
        void bondBitfieldToBondArray(const McBitfield& bf,BondContainer& a) const;
        /** Converts bitfield mask of bonds into an array of atoms that
            are connected by these bonds (removes duplicates). */
        void bondBitfieldToAtomArray(const McBitfield& bf,AtomContainer& a) const;
        /** Converts an array of atoms to a bitfield mask */
        void atomArrayToAtomBitfield(const IAtomContainer& a,McBitfield& bf) const;
        /** Converts an array of bonds to a bitfield mask */
        void bondArrayToBondBitfield(const IBondContainer& a,McBitfield& bf) const;
        /** Converts an array of bonds to a bitfield mask of atoms connected by these bonds */
        void bondArrayToAtomBitfield(const IBondContainer& a,McBitfield& bf) const;
        /** Converts an array of array of atoms to a bitfield mask */
        void atomArrayToAtomBitfield(const McDArray<IAtomContainer*>& a,McBitfield& bf) const;
        /** Converts an array of array of atoms to an array of atoms (removes duplicates). */
        void atomArrayToAtomArray(const McDArray<IAtomContainer*>& a,AtomContainer& ac) const;
        /** Returns whether atoms in a2 are containes in a1. Computation includes conversion
            of ac1 into a bitfield. Use one of the other methods if you need to do multiple tests.*/
        bool doesAtomsetContain(const IAtomContainer& a1, const IAtomContainer& a2) const;
        /** Returns whether atom a2 is in a1.*/
        bool doesAtomsetContain(const IAtomContainer& a1, const Atom* a2) const;
        /** Returns whether atom a2 is in in atom mask a1. */
        bool doesAtomsetContain(const McBitfield& a1, const Atom* a) const;
        /** Returms whether atoms of a2 are in atom mask a1.*/
        bool doesAtomsetContain(const McBitfield& a1, const IAtomContainer& a2) const;
        /** Returns whether atoms in atom mask a2 are in a1.*/
        bool doesAtomsetContain(const McBitfield& a1, const McBitfield& a2) const;
        /** Returns atoms which are in both a1 and a2 in aResult. Computation includes conversion of a1
        into Bitfield. Use one of the other methods if you need to do multiple tests.*/
        void getAtomsetIntersection(const IAtomContainer& a1,const IAtomContainer& a2,AtomContainer& aResult) const;
        /** Returns atoms which are in both a1 and a2 in aResult.*/
        void getAtomsetIntersection(const McBitfield& a1,const IAtomContainer& a2,AtomContainer& aResult) const;
        /** Returns atoms which are in both a1 and a2 in aResult.*/
        void getAtomsetIntersection(const McBitfield& a1,const McBitfield& a2,McBitfield& aResult) const;
        /** Will generate set of Angles for all explicit atoms */
        void generateAngleSet(McDArray<AtomTri>& angles) const;
        /** Will generate set of out of plane dihedrals for all explicit atoms */
        void generateOOPDihedralSet(McDArray<AtomQuad>& angles) const;
        /** Will generate set of dihedrals for all explicit atoms */
        void generateDihedralSet(McDArray<AtomQuad>& angles) const;
        ///
        void atomPathToBondPath(const IAtomContainer& a, BondContainer& b) const;
        ///
        void bondPathToAtomPath(const IBondContainer& b, AtomContainer& a) const;
        //@}


        // -----------------------------------------------------------------------------
        //                                  Chemistry
        // -----------------------------------------------------------------------------
        /** @name Chemistry */
        //@{
        /// Returns number of heavy (non H) atoms
        int getNumHeavyAtoms() const;

        /** Molcule MUST be a connection component, this will only work satisfactory
            for small molecules (<30 atom)
            It is a good idea to make hydrogens implcit first and after coordinate assigment
            call makeHydrogensExplicit (saves a lot of computation) */
        bool assignCoordinates();
        ///
        ///void assignRings(const McBitfield& atoms);
        ///
        void assignRings();

        /** assign aromaticity to bonds, depending whether they are part of an aromatic ringsystem
            requires HAS_RINGS */
        void assignAromaticity();
        void assignAromaticity(const McBitfield& atoms);

        /* there are two states in which bonds are represented: Kekule and Aromatic */
        // changes aromatic bonds into double and single bonds
        void assignKekule();
        void assignKekule(const McBitfield& atoms);
        // will only kekulize bonds which don't belong to aromatic rings
        void assignKekuleNonAromatic();
        void assignKekuleNonAromatic(const McBitfield& atoms);
        /** will change bonds in aromatic rings to aromatic (O(#Rings))
            The function assignRingsAndAromaticity must have been called earlier */
        void dekekulize();
        void dekekulize(const McBitfield& atoms);


        // returns all atoms which are part of the aromatic system as set in visited
        void expandAromaticSystem (const Bond *bond,const McBitfield& mask, McBitfield &visited) const;

        void removeWater();

        int getTotalFormalCharge(const AtomContainer& a) const;

        /** Find all systems of rings, i.e. set of rings for which each element has a common
            bond with at least one other ring of the set.
            The function findRings must have been called earlier. */
        void getRingSystems(McDArray<McDArray<Ring*> >& systems) const;

        /* The function findRings and assignAromaticity must have been called earlier. */
        void getAromaticRingSystems(McDArray<McDArray<Ring*> >& systems) const;

        bool isHueckelRuleSystem(const McBitfield& atoms) const;
        // get the number of electrons each atom of an aromatic system  gives into the system
        // following the hückel rule. If hückel rule cannot be satisfied false is returned.
        bool getHueckelElectronStructure(const IAtomContainer& atom, McDArray<int>& electronsPerAtom) const;
        void getElectronStructure(const IAtomContainer& atom, McDArray<int>& electronsPerAtom) const;

        /** Parses SMARTS string and finds all matchings, if single is true only the first match will be returned.
            By supplying a bitfield the search can be limited to parts of the molecule.
            Throws molchem::Exception if parsing occurs.*/
        void matchSmarts(const char* str,McDArray<AtomContainer >& matching,bool single,McBitfield* atomBf=0) const;

        /** Makes implicit hydrogens of all selected heavy atoms explicit O(V). May invalidate iterators.
            See Atom::makeHydrogensExplicit() */
        void makeHydrogensExplicit();
        void makeHydrogensExplicit(const McBitfield& atoms);
        void makeHydrogensExplicit(const IAtomContainer& atoms);
        void makePolarHydrogensExplicit();
        void makePolarHydrogensExplicit(const McBitfield& atoms);

        /** Makes explicit hydrogens of all selected heavy atoms implicit O(V+E). May invalidate iterators.
            See Atom::makeHydrogensImplicit() */
        void makeHydrogensImplicit();
        void makeHydrogensImplicit(const IAtomContainer& atoms);
        void makeHydrogensImplicit(const McBitfield& atoms);
        void makeApolarHydrogensImplicit();
        void makeApolarHydrogensImplicit(const McBitfield& atoms);

        /** Assigns Formal Charges to all Atoms O(V+E).
            Requires number of implicit hydrogens to be correct. */
        void assignFormalCharges();
        void assignFormalCharges(const IAtomContainer& atoms);
        void assignFormalCharges(const McBitfield& atoms);

        /** Assigns implicit number of hydrogen to all atoms O(V+E).
            Requires formal charges to be correct.
        */
        void assignImplicitHNum();
        void assignImplicitHNum(const IAtomContainer& atoms);
        void assignImplicitHNum(const McBitfield& atoms);

        /** Assigns implicit number of hydrogen to all atoms O(V+E).
        */
        void assignStandardImplicitHNum();
        void assignStandardImplicitHNum(const IAtomContainer& atoms);
        void assignStandardImplicitHNum(const McBitfield& atoms);

        //@}
        // -----------------------------------------------------------------------------
        //                                  Editing
        // -----------------------------------------------------------------------------
        /** @name Editing
        */
        //@{
        //@}


        // -----------------------------------------------------------------------------
        //                                  Geometry
        // -----------------------------------------------------------------------------
        /** @name Geometry */
        //@{

        /// sets all atom coordinates
        void setCoordinates(const McDArray<McVec3d>& co);
        void getCoordinates(McDArray<McVec3d>& co) const;
        /** Calculates a rigid transformation that transforms the source
            atoms onto the target atoms optimally in the sense of mean
            squared distances.

            \param[in] sourceAtoms Set of atoms for which the transform will be computed
            \param[in] targetAtoms Set of atoms to that sourceAtoms will be optimally aligned
            \param[in] targetTransform Optional already existing transformation of target atoms
            \param[out] transform Computed tranformation which is optional for alignment
        */
        void computeAlignTransform(McMat4f & transform,
            const IAtomContainer & sourceAtoms,
            const IAtomContainer & targetAtoms,
            const McMat4f * targetTransform=0);
        /** Calculates a rigid transformation that transforms the atoms of *this
            onto the atoms of the target molcule. Optimally in the sense of mean
            squared distances.

            \param[in] target Molecule onto which this molecule will be aligned
            \param[in] targetTransform Optional already existing transformation of target molecule
            \param[out] transform Computed tranformation which is optional for alignment
        */
        void computeAlignTransform(McMat4f & transform,
            const Molecule * target,
            const McMat4f* targetTransform=0);

        /** Assign 2 dimensional Coordinates of atoms. Call generateCoordinates2D */
        bool assignCoordinates2D();

        /** Assign 2 dimensional Coordinates of atoms. Point set must be of size getNumAtoms()*/
        bool generateCoordinates2D(IPointSet2f& geom) const;

        /** will recompute all coordinates of all explicit hydrogens of the molecule. */
        void assignHydrogenCoordinates3D();

        /** will recompute  coordinates of given explicit hydrogens.
            A hydrogen coordinate will be computed if
            -it is contained in mask or if
            -the heavy atom it is connected to is contained in mask.
        */
        void assignHydrogenCoordinates3D(const McBitfield& mask);

        /** will switch the 3d position of the atoms connected by b1 and b2 to the chiral center centerAtom.
            If the substructures started by b1 and b2 are not trees nothing will be done and false will be returned.
        */
        bool switchChiralPosition(const Atom* centerAtom, const Bond* b1, const Bond* b2);
        //@}

        // -----------------------------------------------------------------------------
        //                Molecule
        // -----------------------------------------------------------------------------
        /** @name General */
        //@{

        /** Does a deep copy of molecule structure resulting in a completely identical
            Molecule with newly allocated atoms, bonds ... */
        Molecule* clone() const;

        Ring* isInRing(const IAtomContainer& a,int ringsize=0) const;
        Ring* getMostComplexRing(const McDArray<Ring*>& ringSet) const;
        void getConnectedRings(const Ring* r, McDArray<Ring*>& ringSet) const;

        /** will order the three connected atoms in a way that a1 is the center and
            a2 and a3 are neighbors of a1. If not possible false will be returned. */
        bool orderForCenterAtom(Atom*& a1,Atom*& a2, Atom*& a3) const;

        /** Adds content of another molecule */
        void addMolecule(const Molecule& m);

        /** Checks for given flags and tries to kick off neccessary
            computations if unset.
        */
        void assignFlags(unsigned int flags) const;

        /** Constructor for an empty Molecule */
        Molecule();

        /** Destructor */
        ~Molecule();

        /** Create Molecule from SMILES string.
            Automatically assign number of implicit hydrogens
        */
        bool fromSmiles(const McString& smilesStr);

        //@}

        void touch(unsigned int flags) {unsetFlags(flags);}

        /** Return the point set. */
        IPointSet3f* getPointSet() const { return pointSet;}
        IGraph* getGraph() const { return graph;}

        void relax(const McBitfield* bf=0);
        void initCoordinates(const McBitfield* bf=0);

        int getImplicitHNum() const;
        /** Determines how aromaticiy is assigned for ring systems.
            If false (default) they may contribute their lone pair to fill
            a pi electron gap between subrings. If true, they may do so only for their
            own subring */
        void setNoAromaticSystemLonePairs(bool b);

    protected:

        void getRingSystems(McDArray<McDArray<Ring*> >& systems,bool aromatic) const;
        void sweepAtomFragmentation();
        void sweepRingFragmentation();
        void sweepBondFragmentation();
        void sweepFragmentation();
        void startKekulize( const IAtomContainer & cycle, const McDArray<int> & electron);
        int expandKekulize(Atom *atom1, Atom *atom2, McBitfield& atomBF, McDArray<int>& bState, McDArray<int>& electron);
        /* find minimal cycles in graph and return them as lists of nodes
        (i.e. x(1) .... x(N) where x(i) is bonded to x(i+1) and x(N) to x(1))
        minimal cycles are all cycles that are not merges of two smaller cycles
        this method is used by assignRingsAndAromaticity
        The rings will be newly allocated on the heap and added to the array */
        void findRings(int maxSize=6);
        // asssign continuous indices to all atoms, bonds and residues O(V+E)
        void assignIndices();
        Ring* newRing();
        Atom* newAtom();
        Bond* newBond();
        McDArray<Atom*> atoms;
        McDArray<Bond*> bonds;
        McDArray<Ring*> rings;
        IPointSet3f* pointSet;
        IGraph* graph;
        static Logger* logger;
        // when assigning aromaticity, are we disallowing heteroatoms to contribute lone pairs to several rings?
        bool noAromaticSystemLonePairs;
    };
}

#endif

/// @}
