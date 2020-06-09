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
#ifndef MOLCHEM_GEOMETRYGENERATOR2D_H
#define MOLCHEM_GEOMETRYGENERATOR2D_H

#include "MolChemWinDLLApi.h"
#include "Molecule.h"

#include <mclib/McDArray.h>
#include <mclib/McBitfield.h>

class McVec2f;
class McVec3f;

namespace molchem
{
    class Atom;
    class Bond;
    class Ring;
    class Molecule;
    class IAtomContainer;
    class AtomContainer;
    class IBondContainer;
    class BondContainer;
    class Logger;
    class PointSet2f;
    class IPointSet2f;

    /** \brief Geometry Generation
    */
    class MOLCHEM_API GeometryGenerator
    {
    public:
        /**
        *  Assings a molecule to be layed out. Call generateCoordinates() to do the
        *  actual layout.
        *
        *@param  mol    the molecule for which coordinates are to be generated.
        *@param  clone  Should the whole process be performed with a cloned copy?
        */
        void setMolecule(Molecule* mol);

        /**
        *  Returns an AtomContainer with all the unplaced atoms connected to a given
        *  atom
        *
        *@param  atom  The Atom whose unplaced bonding partners are to be returned
        *@return       an AtomContainer with all the unplaced atoms connected to a
        *      given atom
        */
        void getUnplacedAtoms(const Atom* atom,AtomContainer& unplacedAtoms);

        /**
        * Walks throught the atoms of each ring in a ring set and marks
        * a ring as PLACED if all of its atoms have been placed.
        *
        * @param   rs  The ringset to be checked
        */
        void checkAndMarkPlaced(const McDArray<Ring*>& rs);

        /**
        *  Returns an AtomContainer with all the placed atoms connected to a given
        *  atom
        *
        *@param  atom  The Atom whose placed bonding partners are to be returned
        *@return       an AtomContainer with all the placed atoms connected to a given
        *      atom
        */
        void getPlacedAtoms(const Atom* atom,AtomContainer& placedAtoms);

        /**
        *  Returns the next atom with unplaced aliphatic neighbors
        *
        *@return    the next atom with unplaced aliphatic neighbors
        */
        Atom* getNextAtomWithAliphaticUnplacedNeigbors();

        /**
        *  Returns the next bond with an unplaced ring atom
        *
        *@return    the next bond with an unplaced ring atom
        */
        Bond* getNextBondWithUnplacedRingAtom();

        /**
        *  Are all rings in the Vector placed?
        *
        *@param  rings  The Vector to be checked
        *@return        Description of the Return Value
        */
        bool allPlaced(const McDArray<Ring*>& rings);

        /**
        *  Get the unplaced ring atom in this bond
        *
        *@param  bond  the bond to be search for the unplaced ring atom
        *@return       the unplaced ring atom in this bond
        */
        Atom* getRingAtom(const Bond* bond);

        /**
        *  Get the ring system of which the given atom is part of
        *
        *@param  ringSystems  A Vector of ring systems to be searched
        *@param  ringAtom     The ring atom to be search in the ring system.
        *@return              the ring system of which the given atom is part of
        */
        void getRingSystemOfAtom(const McDArray<McDArray<Ring*> >& ringSystems, const Atom* ringAtom,McDArray<Ring*>& ringSet);

        /**
        * Returns the ring radius of a perfect polygons of size ring->getNumAtoms()
        * The ring radius is the distance of each atom to the ringcenter.
        *
        * @param   ring  The ring for which the radius is to calculated
        * @param   bondLength  The bond length for each bond in the ring
        * @return  The radius of the ring->
        */
        float getNativeRingRadius(const Ring* ring, float bondLength);

        /**
        *  Set all the atoms in unplaced rings to be unplaced
        */
        void resetUnplacedRings();

        /**
        * Returns the bridge atoms, that is the outermost atoms in
        * the chain of more than two atoms which are shared by two rings
        *
        * @param   sharedAtoms  The atoms (n > 2) which are shared by two rings
        * @return  The bridge atoms, i.e. the outermost atoms in the chain of more than two atoms which are shared by two rings
        */
        void getBridgeAtoms(const AtomContainer& sharedAtoms,AtomContainer& bridgeAtoms);

        /**
        * Partition the bonding partners of a given atom into ring atoms and non-ring atoms
        *
        * @param   atom  The atom whose bonding partners are to be partitioned
        * @param   ring  The ring against which the bonding partners are checked
        * @param   ringAtoms  An AtomContainer to store the ring bonding partners
        * @param   nonRingAtoms  An AtomContainer to store the non-ring bonding partners
        */
        void partitionNonRingPartners(const Atom* atom, const Ring* ring, AtomContainer& ringAtoms, AtomContainer& nonRingAtoms);

        /**
        *  Partition the bonding partners of a given atom into placed (coordinates
        *  assinged) and not placed.
        *
        *@param  atom              The atom whose bonding partners are to be
        *      partitioned
        *@param  unplacedPartners  A vector for the unplaced bonding partners to go in
        *@param  placedPartners    A vector for the placed bonding partners to go in
        */
        void partitionPartners(const Atom* atom, AtomContainer& unplacedPartners, AtomContainer& placedPartners);

        /**
        *  Search an aliphatic molecule for the longest chain. This is the method to
        *  be used if there are no rings in the molecule and you want to layout the
        *  longest chain in the molecule as a starting point of the structure diagram
        *  generation.
        *
        *@param  molecule                                               The molecule
        *      to be search for the longest unplaced chain
        *@return                                                        An
        *      AtomContainer holding the longest chain.
        *@exception  exception.NoSuchAtomException  Description of
        *      the Exception
        */
        void getInitialLongestChain(McBitfield* bf,AtomContainer& path);

        /**
        *  Search a molecule for the longest unplaced, aliphatic chain in it. If an
        *  aliphatic chain encounters an unplaced ring atom, the ring atom is also
        *  appended to allow for it to be laid out. This gives us a vector for
        *  attaching the unplaced ring later.
        *
        *@param  molecule                                        The molecule to be
        *      search for the longest unplaced chain
        *@param  startAtom                                       A start atom from
        *      which the chain search starts
        *@return                                                 An AtomContainer
        *      holding the longest unplaced chain.
        *@exception  exception.Exception  Description of the
        *      Exception
        */
        void getLongestUnplacedChain(const Atom* startAtom,AtomContainer& a );

        /**
        *  Performs a breadthFirstSearch in an AtomContainer starting with a
        *  particular sphere, which usually consists of one start atom, and searches
        *  for the longest aliphatic chain which is yet unplaced. If the search
        *  encounters an unplaced ring atom, it is also appended to the chain so that
        *  this last bond of the chain can also be laid out. This gives us the
        *  orientation for the attachment of the ring system.
        *
        *@param  ac                                              The AtomContainer to
        *      be searched
        *@param  sphere                                          A sphere of atoms to
        *      start the search with
        *@param  pathes                                          A vector of N pathes
        *      (N = no of heavy atoms).
        *@exception  exception.Exception  Description of the
        *      Exception
        */
        void breadthFirstSearch(const IAtomContainer& ac, const AtomContainer& sphere, McDArray<AtomContainer>& pathes);

        /**
        *  True is all the atoms in the given AtomContainer have been placed
        *
        *@param  ac  The AtomContainer to be searched
        *@return     True is all the atoms in the given AtomContainer have been placed
        */
        bool allPlaced(const IAtomContainer& ac);

        /**
        *  Marks all the atoms in the given AtomContainer as not placed
        *
        *@param  ac  The AtomContainer whose atoms are to be marked
        */
        void markNotPlaced(const IAtomContainer& ac);

        /**
        *  Marks all the atoms in the given AtomContainer as placed
        *
        *@param  ac  The AtomContainer whose atoms are to be marked
        */

        void markPlaced(const IAtomContainer& ac);

        /**
        *  Get all the placed atoms in an AtomContainer
        *
        *@param  ac  The AtomContainer to be searched for placed atoms
        *@return     An AtomContainer containing all the placed atoms
        */
        void getPlacedAtoms(const IAtomContainer& ac,AtomContainer& ret);

        /**
        *  Makes an array containing morgan-number-like number for an atomContainer.
        *
        *@param  atomContainer  The atomContainer to analyse.
        *@return                The morgan numbers value.
        */
        void getWeightNumbers(const AtomContainer& atomContainer,McDArray<int>& tempMorganMatrix );

        /**
        */
        bool shouldBeLinear(const Atom* atom);

        enum RINGTYPE {
            FUSED = 0,
            BRIDGED = 1,
            SPIRO = 2
        };

    protected:

        McBitfield isAtomH;
        McBitfield isAtomVisited;
        McBitfield isAtomPlaced;
        McBitfield isRingPlaced;
        Molecule* molecule;
        McDArray<Ring*> sssr;
        float bondLength;
        McDArray<McDArray<Ring*> > ringSystems;
        bool useTemplates;
        //        TemplateHandler templateHandler;

        static Logger* logger;
    };

    /** \brief 2D Geometry Generation

    Generates 2D coordinates for unknown geometries
    (usually works well for small molecules - up to 30 heavy atoms)
    */
    class MOLCHEM_API GeometryGenerator2D : public GeometryGenerator
    {
    public:

        IPointSet2f* pos;

        /**
        *  Creates an instance of this class while assigning a molecule to be layed
        *  out.
        *
        *@param  molecule  The molecule to be layed out.
        */
        GeometryGenerator2D(Molecule* molecule);

        /**
        *  This method uses generateCoordinates, but it removes the hydrogens first,
        *  lays out the structuren and then adds them again.
        *
        *@exception  java.lang.Exception  Description of the Exception
        *@see                             #generateCoordinates
        */
        void generateExperimentalCoordinates();

        /**
        *  The main method of this StructurDiagramGenerator. Assign a molecule to the
        *  StructurDiagramGenerator, call the generateCoordinates() method and get
        *  your molecule back.
        *
        *@exception  java.lang.Exception  Description of the Exception
        */
        void generateCoordinates(IPointSet2f& pos);

    private:

        /**
        * Generates 2D coordinates on the non-hydrogen skeleton, after which
        * coordinates for the hydrogens are calculated.
        */
        void generateExperimentalCoordinates(const McVec2f& firstBondVector);

        /**
        *  The main method of this StructurDiagramGenerator. Assign a molecule to the
        *  StructurDiagramGenerator, call the generateCoordinates() method and get
        *  your molecule back.
        *
        *@param  firstBondVector          Description of the Parameter
        *@exception  java.lang.Exception  Description of the Exception
        */
        void generateCoordinates(const McVec2f& firstBondVector);

        /**
        *  Does a layout of all the rings in a given connected RingSet
        *
        *@param  firstBondVector  A vector giving the placement for the first bond
        *@param  rs               The connected RingSet for which the layout is to be
        *      done
        */
        void layoutRingSet(const McVec2f& firstBondVector,const  McDArray<Ring*>& rs);

        /**
        *  Does a layout of all aliphatic parts connected to the parts of the molecule
        *  that have already been laid out.
        *
        *@exception  exception.Exception  Description of the
        *      Exception
        */
        void handleAliphatics();

        /**
        *  Does the layout for the next RingSystem that is connected to those parts of
        *  the molecule that have already been laid out.
        */
        void layoutNextRingSystem(const McVec2f& firstBondVector);

        /**
        *  Places the first bond of the first ring such that one atom is at (0,0) and
        *  the other one at the position given by bondVector
        *
        *@param  bondVector  A 2D vector to point to the position of the second bond
        *      atom
        *@param  bond        Description of the Parameter
        *@return             Description of the Return Value
        */
        void placeFirstBond(const Bond* bond, const McVec2f& bondVector,AtomContainer& sharedAtoms);

        /**
        * Generated coordinates for a given ring-> Multiplexes to special handlers
        * for the different possible situations (spiro-, fusion-, bridged attachement)
        *
        * @param   ring  The ring to be placed
        * @param   sharedAtoms  The atoms of this ring, also members of another ring, which are already placed
        * @param   sharedAtomsCenter  The geometric center of these atoms
        * @param   ringCenterVector  A vector pointing the the center of the ring
        * @param   bondLength  The standard bondlength
        */
        void placeRing(const Ring* ring, const AtomContainer& sharedAtoms, const McVec2f& sharedAtomsCenter, McVec2f& ringCenterVector, float bondLength);

        /**
        * Positions the aliphatic substituents of a ring system
        *
        * @param   rs The RingSystem for which the substituents are to be laid out
        * @param treatedAtoms  A list of atoms that where laid out
        */
        void placeRingSubstituents(const McDArray<Ring*>& rs, float bondLength,AtomContainer& treatedAtoms);

        /**
        * Generated coordinates for a given ring, which is connected to another ring a bridged ring,
        * i.e. it shares more than two atoms with another ring->
        *
        * @param   ring  The ring to be placed
        * @param   sharedAtoms  The atoms of this ring, also members of another ring, which are already placed
        * @param   sharedAtomsCenter  The geometric center of these atoms
        * @param   ringCenterVector  A vector pointing the the center of the ring
        * @param   bondLength  The standard bondlength
        */
        void placeBridgedRing(const Ring* ring, const AtomContainer& sharedAtoms, const McVec2f& sharedAtomsCenter, McVec2f ringCenterVector, float bondLength );

        /**
        * Generated coordinates for a given ring, which is connected to a spiro ring->
        * The rings share exactly one atom->
        *
        * @param   ring  The ring to be placed
        * @param   sharedAtoms  The atoms of this ring, also members of another ring, which are already placed
        * @param   sharedAtomsCenter  The geometric center of these atoms
        * @param   ringCenterVector  A vector pointing the the center of the ring
        * @param   bondLength  The standard bondlength
        */
        void placeSpiroRing(const Ring* ring, const AtomContainer& sharedAtoms, const McVec2f& sharedAtomsCenter, McVec2f ringCenterVector, float bondLength);

        /**
        * Generated coordinates for a given ring, which is fused to another ring->
        * The rings share exactly one bond->
        *
        * @param   ring  The ring to be placed
        * @param   sharedAtoms  The atoms of this ring, also members of another ring, which are already placed
        * @param   sharedAtomsCenter  The geometric center of these atoms
        * @param   ringCenterVector  A vector pointing the the center of the ring
        * @param   bondLength  The standard bondlength
        */
        void placeFusedRing(const Ring* ring, const AtomContainer& sharedAtoms, const McVec2f& sharedAtomsCenter, McVec2f ringCenterVector, float bondLength );

        /**
        * Calculated the center for the first ring so that it can
        * layed out. Only then, all other rings can be assigned
        * coordinates relative to it.
        *
        * @param   ring  The ring for which the center is to be calculated
        * @return  A McVec2f pointing to the ringcenter
        */
        McVec2f getRingCenterOfFirstRing(const Ring* ring, const McVec2f& bondVector, float bondLength);

        /**
        * Layout all rings in the given RingSet that are connected to a given Ring
        *
        * @param   rs  The RingSet to be searched for rings connected to Ring
        * @param   ring  The Ring for which all connected rings in RingSet are to be layed out.
        */
        void placeConnectedRings(const McDArray<Ring*>& rs, const Ring* ring, int handleType, float bondLength);

        /**
        *  Distribute the bonded atoms (neighbours) of an atom such that they fill the
        *  remaining space around an atom in a geometrically nice way.
        *  IMPORTANT: This method is not supposed to handle the
        *  case of one or no place neighbor. In the case of
        *  one placed neigbor, the chain placement methods
        *  should be used.
        *
        *@param  atom                The atom whose partners are to be placed
        *@param  placedNeighbours    The atoms which are already placed
        *@param  unplacedNeighbours  The partners to be placed
        *@param  bondLength          The standared bond length for the newly placed
        *      Atoms
        *@param  sharedAtomsCenter   The 2D centre of the placed Atoms
        */
        void distributePartners(const Atom* atom, const AtomContainer& placedNeighbours, const McVec2f& sharedAtomsCenter,
            const AtomContainer& unplacedNeighbours, float bondLength);

        /**
        *  Places the atoms in a linear chain. Expects the first atom to be placed and
        *  places the next atom according to initialBondVector. The rest of the chain
        *  is placed such that it is as linear as possible (in the overall result, the
        *  angles in the chain are set to 120 Deg.)
        *
        *@param  ac                 The AtomContainer containing the chain atom to be
        *      placed
        *@param  initialBondVector  The Vector indicating the direction of the first
        *      bond
        *@param  bondLength         Description of the Parameter
        */
        void placeLinearChain(const AtomContainer& ac, const McVec2f& initialBondVector, float bondLength);

        /**
        *  Returns the next bond vector needed for drawing an extended linear chain of
        *  atoms. It assumes an angle of 120 deg for a nice chain layout and
        *  calculates the two possible placments for the next atom-> It returns the
        *  vector pointing farmost away from a given start atom->
        *
        *@param  atom             An atom for which the vector to the next atom to
        *      draw is calculated
        *@param  previousAtom     The preceding atom for angle calculation
        *@param  distanceMeasure  A point from which the next atom is to be farmost
        *      away
        *@return                  A vector pointing to the location of the next atom
        *      to draw
        */
        void getNextBondVector(const Atom* atom, const Atom* previousAtom, const McVec2f& distanceMeasure, bool trans,McVec2f& v );

        /**
        *  Populates the corners of a polygon with atoms. Used to place atoms in a
        *  geometrically regular way around a ring center or another atom-> If this is
        *  used to place the bonding partner of an atom (and not to draw a ring) we
        *  want to place the atoms such that those with highest "weight" are placed
        *  farmost away from the rest of the molecules. The "weight" mentioned here is
        *  calculated by a modified morgan number algorithm.
        *
        *@param  atomsToDraw     All the atoms to draw
        *@param  startAngle      A start angle, giving the angle of the most clockwise
        *      atom which has already been placed
        *@param  addAngle        An angle to be added to startAngle for each atom from
        *      atomsToDraw
        *@param  rotationCenter  The center of a ring, or an atom for which the
        *      partners are to be placed
        *@param  radius          The radius of the polygon to be populated: bond
        *      length or ring radius
        */
        void populatePolygonCorners(const AtomContainer& atomsToDraw, const McVec2f& rotationCenter, float startAngle, float addAngle, float radius);

        void placeHydrogens(IAtomContainer& atomContainer);

        void placeHydrogens(const McBitfield& mask, Atom* atom);

        /**
        * Main method to be called to resolve overlap situations.
        *
        * @param  ac    The atomcontainer in which the atom or bond overlap exists
        * @param  sssr  A ring set for this atom container if one exists, otherwhise NULL
        */
        float resolveOverlap(const McDArray<Ring*>& sssr);

        /**
        *  Makes a small displacement to some atoms or rings in the given
        *  atomcontainer.
        *
        *@param  ac                The AtomContainer to work on
        *@param  overlappingAtoms  Description of the Parameter
        *@param  overlappingBonds  Description of the Parameter
        */
        float displace(McDArray<AtomPair>& overlappingAtoms, McDArray<BondPair>& overlappingBonds);

        /**
        *  Calculates a score based on the overlap of atoms and intersection of bonds.
        *  The overlap is calculated by summing up the distances between all pairs of
        *  atoms, if they are less than half the standard bondlength apart.
        *
        *@param  ac                The Atomcontainer to work on
        *@param  overlappingAtoms  Description of the Parameter
        *@param  overlappingBonds  Description of the Parameter
        *@return                   The overlapScore value
        */
        float getOverlapScore(McDArray<AtomPair>& overlappingAtoms, McDArray<BondPair>& overlappingBonds);

        /**
        *  Calculates a score based on the overlap of atoms.
        *  The overlap is calculated by summing up the distances between all pairs of
        *  atoms, if they are less than half the standard bondlength apart.
        *
        *@param  ac                The Atomcontainer to work on
        *@param  overlappingAtoms  Description of the Parameter
        *@return                   The overlapScore value
        */
        float getAtomOverlapScore(McDArray<AtomPair>& overlappingAtoms);

        /**
        *  Calculates a score based on the intersection of bonds.
        *
        *@param  ac                The Atomcontainer to work on
        *@param  overlappingBonds  Description of the Parameter
        *@return                   The overlapScore value
        */
        float getBondOverlapScore(McDArray<BondPair>& overlappingBonds);

        /**
        *  Checks if two bonds cross each other.
        *
        *@param  bond1  Description of the Parameter
        *@param  bond2  Description of the Parameter
        *@return        Description of the Return Value
        */
        bool areIntersected(Bond* bond1, Bond* bond2);
    };
}

#endif

/// @}
