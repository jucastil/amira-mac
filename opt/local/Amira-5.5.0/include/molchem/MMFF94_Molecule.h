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
#ifndef MMFF94_MOLECULE_H
#define MMFF94_MOLECULE_H

#include "MolChemWinDLLApi.h"
#include <mclib/McDArray.h>

class McString;
class MolTopology;


namespace molchem {
    class Molecule;
}
/** \brief MMFF94 Force-Field 
    
    \section overview Overview:

    The namespace mmff94 contains the MMFF94 forcefield [1] with and addition for solvation [2-3].
    It consists of datastructures, the parameterization module, and
    the actual force-field. 

    For using mmff94 you need as input data a molchem::Molecule.
    
    - MMFF94_AtomTyper does the atom typing.
    - MMFF94_Parameterization does the parameterization of the molecule (incl. atom 
    typing). The result of the parameterization is a MMFF94_Molecule.
    - MMFF94_Molecule contains all force field parameters.
    - MMFF94_ForceField is the force field wrapping all the energy computation.

    \section atomtyping AtomTyping:

    MMFF94 has two sets of atom types. 1st The detailed types which comprise more than 200 functional groups.
    Additionally there is the simple atom type which comprises 99 different type indices.
    For the force field, only the simple atom types are needed.

    - MMFF94_AtomSubTyper does the typing of the detailed types.
    - MMFF94_AtomTyper does the typing of the simple types by calling MMFF94_AtomSubTyper and then mapping to the simple types.

    For atom typing, correct bond orders, formal charges and implicit hydrogens must be assigned.
    When using implicit hydrogens, atom typing will be correct for the heavy atoms.
    However, implicit hydrogens will lead to all sorts of parameterization problems, thus they should only
    be used if the AtomTyping is used in a non MMFF context. If the Parameterization and ForceField are used,
    all hydrogens have to be explicit.

    \section testing Testing:

    The force field is highly optimized and is thus sensitive to changes (i.e. 
    bugs are easily introduced). A unit test module for all components of this namespace can be found in
    hxtimm2/TestMMFF. After applying changes, be sure to check the results of the tests.

    \section references References:
        - [1] Journal of Computational Chemistry, Vol. 17, Nos. 5&6, 490-519 (1996)
              Merck Molecular Force Field. I-V
              THOMAS A. HALGREN
        - [2] Still approximation for GB term:
            J. Phys. Chem. A 1997, 101, 3005-3014
            The GB/SA Continuum Model for Solvation. A Fast Analytical Method for the Calculation
            of Approximate Born Radii 
            Di Qiu, Peter S. Shenkin, Frank P. Hollinger, and W. Clark Still
        - [3] ACE Approximation to SA term:
            J. Mol. Biol. (1998) 284, 835±848
            Solution Conformations and Thermodynamics of
            Structured Peptides: Molecular Dynamics Simulation
            with an Implicit Solvation Model
            MichaelSchaefer,ChristianBartels and MartinKarplus

    \authors
        tbaumeister

*/
namespace mmff94 {
    /** \brief Stores atom related parameterization data for the MMFF94 Force-Field */
    struct MMFF94_Atom 
    {
        // coulomb
        double q;
        // VDW Parameters
        int atomicNumber;
        int type;
        double alpha;
        double N; 
        double A;
        double g;
        char DA;
    };
    /** \brief Stores bond related parameterization data for the MMFF94 Force-Field */
    struct MMFF94_Bond {
        int atom[2];
        // Bond Stretching
        double kb;
        double r0;
        int BT;
    };    
    /** \brief Stores angle related parameterization data for the MMFF94 Force-Field */
    struct MMFF94_Angle {
        int atom[3];
        bool linear;
        // Stretch Bend Parameters
        double kba_ijk;
        double kba_kji;
        // Angle Bending Parameters
        double ka;
        double theta0;
        int AT;
        int SBT;
    };
    /** \brief Stores out-of-plane dihedral related parameterization data for the MMFF94 Force-Field */
    struct MMFF94_OOPDihedral {    
        // the second atom is the central atom
        int atom[4];
        // OOP Parameters
        double koop;
    };
    /** \brief Stores dihedral related parameterization data for the MMFF94 Force-Field */
    struct MMFF94_Dihedral {
        int atom[4];
        // Torsion parameters
        double V1;
        double V2;
        double V3;
        int TT;
    };
    /** \brief Stores all parameterization data of a molecule for the MMFF94 Force-Field. 

    */
    class MOLCHEM_API MMFF94_Molecule {
    public:
        /** Clears all arrays. Molecule will be empty. */
        void clear();
        /** Adds a second molecule with all parameterization to this one. All groups of the second molecule
            are added behind the existing groups. Group indices of the added groups are adjusted accordingly. */
        void add(const MMFF94_Molecule& m);
        /** Creates MMFF molecule structure from a molchem::Molecule. The parameters are initialized with 0. */
        void from(const molchem::Molecule* m);
        /** Create MMFF molecule structure from a MolTopology. Parameters are will with the attribute values.
            \exception molchem::Exception
        */
        void from(const MolTopology* m);
        /* Write data to a MolTopology. The MolTopology must have the same number of atoms and bonds as this MMFF molecule.
           Angle, oop and dihedral level are removed and created anew. All Parameters are written as attributes.
           \exception molchem::Exception
        */
        void to(MolTopology* m) const;
        /** Prints all groups into a string. For debugging output. */
        void print(McString& s);
        /// returns index of bond between these atoms. Checks for different order. -1 if not found.
        int getBond(int ix1, int ix2) const;
        /// returns index of angle between these atoms. Checks for different order. -1 if not found.
        int getAngle(int ix1,int ix2,int ix3) const;
        /// returns index of dihedral between these atoms. Checks for different order. -1 if not found.
        int getDihedral(int ix1,int ix2,int ix3,int ix4) const;
        /// returns index of out of plane dihedral between these atoms. Checks for different order. -1 if not found.
        int getOOPDihedral(int ix1,int ix2,int ix3,int ix4) const;
        ///
        McDArray<MMFF94_Atom> atoms;
        ///
        McDArray<MMFF94_Bond> bonds;
        ///
        McDArray<MMFF94_Angle> angles;
        ///
        McDArray<MMFF94_OOPDihedral> oopdihedrals;
        ///
        McDArray<MMFF94_Dihedral> dihedrals;
    };
    
}

#endif






/// @}
