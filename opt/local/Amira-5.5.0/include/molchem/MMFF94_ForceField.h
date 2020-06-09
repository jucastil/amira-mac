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
#ifndef MMFF94FORCEFIELD_H
#define MMFF94FORCEFIELD_H

#include "MolChemWinDLLApi.h"

namespace molchem {
    class Molecule;
    class Logger;
}

#include "MMFF94_Molecule.h"

#include "mclib/McVec3d.h"
#include "mclib/McVec2i.h"
#include "mclib/McDArray.h"
#include "mclib/McBitfield.h"
#include "ForceField.h"

namespace mmff94 {

    /** Force Field Components. 
        MMFF94_SOLVATION is switched off by default. Use setComponentActive to activate.
    */
    enum MMFF94_Component {
        MMFF94_COULOMB         = 0,
        MMFF94_VDW             = 1,
        MMFF94_BONDSTRETCHING  = 2,
        MMFF94_ANGLEBENDING    = 3,
        MMFF94_STRETCHBEND     = 4,
        MMFF94_OOPBENDING      = 5,
        MMFF94_TORSION         = 6,
        MMFF94_SOLVATION       = 7
    };

#define MMFF94_NUM_COMPONENTS 8
    
    /** \brief MMFF94 Force field implementation 
    
        \section overview Overview:

        Features of the force field include:

        - Neighbor lists for noncovalent interactions based on cutoff and switching atoms with grid based 
          neighbor search
        - Automatic generation of a neighbor list whenever coordinates change too much between
          two consecutive computations.
        - Switching on/off of components.
        - Scaling of components.
        - Definition of parts as fixed in space.
        - Definition of parts as rigid.
        - Results as energy, energy per components, gradient, gradient per component, and energy per
          interaction.

        The force field takes groups and parameters from an MMFF94_Molecule which is a public member and can be
        directly set. And alternative is using the setMolecule function which will automatically do the conversion
        and parameterization from a molchem::Molecule to the MMFF94_Molecule. All conditions applying to atom typing
        and parameterization however must be met, i.e. defined formal charges, bond orders, and explicit hydrogens.

        For optimization purposes the information in the mol member has to be preprocessed.
        This happens when the method setup is called and intermediate data is stored in a set of arrays. 
        This means that whenever either mol or any other of the force field parameters change, setup needs to be 
        called again. The only change for which setup does not need to be called is a change of coordinates.

        \section cutoff Cutoff: 
        
        If cutoffs are used, updateNeighborList needs to be called and the setup method needs to be called
        with the current coordinates which will be used to decide which atoms are within the cutoff.
        If cutoffs are disabled, the setup method without parameters may be used.

        Also, the neighbor list needs to be regenerated when coordinates change too much between two consecutive calls.
        The user can either do this manually by calling updateNeighborList. A hint can be obtained by
        calling checkUpdateNeighborList. Alternatively automatic updating can be enabled with
        setAutoUpdateNeighborList.

        For correct results with cutoffs it is neccessary to define neutral groups in order to not disrupt dipoles [1].
        The cutoff condition is then tested between switching atoms between these two groups.
        For this, the array groups must be filled. Also the array switching atoms must be filled, except if 
        switchingAtomsCenter is set to true, for which the switching atom will be generated automatically as
        the atom closest to the groups center.

        \section components Components:

        By default all standard MMFF components (i.e everything except solvation) are enables.
        This can be changed with the method setComponentActive.

        \section fixed-rigid Fixed / Rigid Groups:

        Groups of atoms may be defined as rigid by giving them the same index with the setRigidParts method.
        A part index of 0 means that the atom does not belong to a rigid part.
        For rigid parts, no intramolecular interaction will be calculated 
        This method is primarily of use for the RigidBodyDynamic Wrapper.

        Atoms can be defined as fixed in space with the method setFixedPart. 
        Fixed parts will be considered as rigid, i.e. no inter atom interactions. Additionally the gradient on them will
        be set to 0. 

        \section units Units:

            - Input coordinates: Angstroem
            - Output energy: kJ/mol.
            - Output gradient: kJ/(mol*Angstroem) which is 1E-10*kN/mol.

        \section example Example:

        Setting up the forcefield:

        \code
            using namespace mmff94;
            MMFF94_ForceField field;
            if (!field.setMolecule(molecule)) {
                printf("Parameterization of molecule Failed.\n");
                exit(0);
            }
            field.setCutoff(true,20);
            field.setComponentActive(MMFF94_SOLVATION,true);
            field.setup(coordinates);
        \endcode

        Computing energies per component:

        \code
            field.result.computeWhat = ForceField::Result::ENERGY_PER_COMPONENT;
            field.compute(coordinates);
            for (i=0;i<field.getNumComponents();i++)
                printf("Component %s has energy %fkJ/mol\n",field.getComponentName(i),field.result.energyPerComponent[i]);
        \endcode

        Energy minimization:

        \code 
            molchem::OptimizerCG optimizer;
            optimizer.setTerminationMaxSteps(100);
            field.setAutoUpdateNeighborList(true);
            optimizer.setFunction(field);
            optimizer.optimize(coordinates);
        \endcode

        \section references References:

        - [1] Leach: Molecular Modelling

    */

    class MOLCHEM_API MMFF94_ForceField : public molchem::ForceField {

    public:
        // Return string containing the number of interactions for each component
        void getInteractionCount(McString& str) const;
        /// Constructor.
        MMFF94_ForceField();
        /// Destructor.
        ~MMFF94_ForceField();

        /// Name of the force field
        const char* getName() const;
        /// Number of components
        int getNumComponents() const;
        /// Name of component by index
        const char* getComponentName(int componentIx) const;
        /** Sets the molecule and does parameterization. 
            The data will be stored in an internal molecular structure, so the supplied object does not need
            to remain valid */
        bool setMolecule(molchem::Molecule* m);

        /****************************************************************************
        Configuration
        ***************************************************************************/    

        /** Set Noncovalent cutoff. Only interaction between atoms whose distance < cutoff will be considered. 
        Cutoff groups, with switching atoms may be used (see groups). The interaction which need
        to be computed will be stored in a neighbor list. The neighbor list can be updated automatically (see setAutoUpdateNeighborList).*/
        void setCutoff(bool active, double cutoff=20);

        /****************************************************************************
        Computation
        ***************************************************************************/

        /** Does the force field computation for the given set of coordinates. To determine what will be computed, you need to change the computeWhat flags in
            the Result structure. The results of the computation will be stored in this Result structure, which will be valid until compute is called the next time.
            */
        virtual bool compute(const McDArray<McVec3d>&);


        /****************************************************************************
        Setup
        ***************************************************************************/

        /** Computes lists of atom coupled by 1-2 or 1-3 interactions and calls all setup methods and updateNeighborList. */
        void setup(const McDArray<McVec3d>& co);
        void setup();
        void setupNoncovalent();
        void setupBondStretching();
        void setupAngleBending();
        void setupOutOfPlane();
        void setupStretchBend();
        void setupTorsion();
        void setupGBSAStill();
        /** Returns whether the neighbor list should be updated. 
            This is the case if any atom moves more than half the cutoff length from its position when the list was updated last. */
        virtual bool checkUpdateNeighborList(const McDArray<McVec3d>& co);
        //// update the neighbor list manually. This method is also called automatically if the automatic update is enabled.
        void updateNeighborList(const McDArray<McVec3d>& co);
        /** If set to true, the method checkUpdateNeighborList is called before each evaluation and if it returns true the 
            neighbor list will be updated. Without this being enabled, the user has to call updateNeighborList explicitly.
        */
        void setAutoUpdateNeighborList(bool b);
        // ----------------------------------------------
        //              MMFF Parameters

        /** 
            The molecular data structure and MMFF94 Parameters. This contains all information of the molecular structure needed by the force field
            including the parameterization. This is usually set by the force field by using
            the setMolecule method, but can also be set directly. Currently, some constants are precalculated when using the
            setup method, so that they don't have to be repeatedly computed for each consecutive evaluation. This means that changing
            force constants by directly editing this structure won't work, unless you explicitly call setup which is however
            inefficient. A way for more efficient change of parameters for thermodynamic integration and similar computations 
            may be added in the future.
            */
        MMFF94_Molecule mol;
        /**
           Groups arrays, containing the atom indices of each groups. 
           This is used for determining group baes cutoffs by calculating the distance between switching atoms of the group.

           Each group must contain at least one atom index. Each atom index may be contained only once. If an atom index 
           does not appear it is treated as a switching atom of a group with one atom.
           This array must be set explicitly by the user.
           By default, the switching atom will be the one closest to the center of gravity of the group.
           If you want to define the switching atoms yourself, you can disable the switchingAtomCenter option.
           The field then uses the first atom in each group array as switching atom.
           */
        McDArray<McDArray<int> > groups;
        /// Switch for method of switching atom determination. See groups.
        bool switchingAtomCenter;

        /// Clears all structure dependant information, like molecule, flexible atom bitifield, groups ...
        void clearStructure();
        /// clear all informatio that is generated by setup
        void clearDerived();

        public:

        // ----------------------------------------------
        //       Internally Used Parameters and Lists

        McDArray<McDArray<int> > atomBondList;
        McDArray<McVec2i> bondIndicesPerAngle;

        /** Group information. Used for determining which groups may not be partitioned by cutoff based neighbor list generation */
        // index of switching atom of each group
        McDArray<int> switchingAtom; 
        // index of group that each atom belongs to. -1 for none
        McDArray<int> group; 
        // turns nonbonded cutoff on or off
        bool useCutoff;
        // cutoff for nonbonded interaction
        double cutoffMax;
        // determines whether the check for updating the neighbor list is automatically done for each call of compute
        bool autoUpdateNeighborList;
        /* coordinates at last neighbor list update. Used to determine when neighbor list needs a new update. 
           This is the case if any atom moved more than half the cutoff.*/
        McDArray<McVec3d> lastNeighborListUpdateCo; 

        /** list of atom indices that are flexible or fixed. We use these at several positions to avoid
            having to use iterate over all atoms while using fixedParts as a condition */
        McDArray<int> nonFixedAtoms;
        McDArray<int> fixedAtoms;
        // Nonbonded information
        struct pairs{
            int ix0;
            int ix1;
            double g_rrr;
            double g_rrr_7;
            double g_epps;
            double coulombfactor;
        };

        // Array of noncolvalent pairs that need to be computed. This array will be initialized by the updateNeighborList method
        McDArray<pairs> noncov_pairs; 
        // Array of indices of bonds that need to be computed
        McDArray<int> bonds;
        // Array of indices of angles that need to be computed
        McDArray<int> angles_b;
        // Array of indices of angles that need to be computed
        McDArray<int> angles_sb;
        // Array of indices of oop dihedrals that need to be computed
        McDArray<int> oopdihedrals;
        // Array of indices of dihedrals that need to be computed
        McDArray<int> dihedrals;
        // pairs of atoms used for GB calculation, coupled and with both atoms charged
        McDArray<McVec2i> pairsGB; 
        // atoms used for SA and GB atom self elec calculation
        McDArray<int> atomsGB;

        // all energies in kJ/mol, all forces in kN/mol

        // methods will update the following result entries:
        // energyPerItemPerComponent / gradientPerComponent
        // all other result entries are evaluated from these
        // entries as neccessary
        // ----------------------------------------------
        //             NonCovalent

        void computeNoncovalentEnergyAndGradient(
            const McDArray<McVec3d>& coordinates);

        void computeNoncovalentEnergy(
            const McDArray<McVec3d>& coordinates);

        void computeNoncovalentGradient(
            const McDArray<McVec3d>& coordinates);


        // ----------------------------------------------
        //              Bond Stretching

        void computeBondStretchingEnergy(
            const McDArray<McVec3d>& coordinates);

        void computeBondStretchingEnergyAndGradient(
            const McDArray<McVec3d>& coordinates);


        // ----------------------------------------------
        //              Angle Bending

        void computeAngleBendingEnergyAndGradient(
            const McDArray<McVec3d>& co);

        void computeAngleBendingEnergy(
            const McDArray<McVec3d>& co);


        // ----------------------------------------------
        //              Stretch Bend

        void computeStretchBendEnergyAndGradient(
            const McDArray<McVec3d>& coordinates);

        void computeStretchBendEnergy(
            const McDArray<McVec3d>& coordinates);


        // ----------------------------------------------
        //              Out of Plane

        void computeOutOfPlaneEnergyAndGradient(
            const McDArray<McVec3d>& coordinates);

        void computeOutOfPlaneEnergy(
            const McDArray<McVec3d>& coordinates);

  
        // ----------------------------------------------
        //              Torsion

        void computeTorsionEnergyAndGradient(
            const McDArray<McVec3d>& co);

        void computeTorsionEnergy(
            const McDArray<McVec3d>& co);


        
        // ----------------------------------------------
        //              Still GBSA

        void computeGBSAStillEnergyAndGradient(
            const McDArray<McVec3d>& co);

        struct GBSA {
            McDArray<double> soluteXrsolv,soluteXasolv,soluteXvsolv,soluteXgpol,charge;
            McDArray<McDArray<int> > coupleXi12,coupleXi13,coupleXi14;
            // p1 p2 and p3 is only needed for initalization
            double soluteXp4,soluteXp5,soluteXGBscale;
            // Uncoupled pairs.(no 1-2 or 1-3 interaction) 
            // These are used in the loop which computes born radii
            // i.e. the last term of the Gipol equations while the 1-2 and 1-3 interactions
            // are computed in the second and third term
            McDArray<McVec2i> pairsUncoupled;
            // pairs (may be 1-2 or 1-3 pairs) of which both atoms are charges
            // which are used in the main GBSA loop are stored in the pairsGB variable
        } gbsa;
        static molchem::Logger* logger;     
    };
}

#endif

/// @}
