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
#ifndef MMFF94_HELPERS_H
#define MMFF94_HELPERS_H

#include "MolChemWinDLLApi.h"

class MolTrajectoryMem;
class MolTrajectory;
class Molecule;
class MolObject;

#include <mclib/McBitfield.h>

namespace molchem {
    class GradientFunctionFixed;
}

namespace mmff94 {
    class MMFF94_ForceField;
    
    /** will minimize molobject in the field of complex.
    \param[in] cutoff Cutoff value for nonboned interactions
    \param[in] maxSteps Maximal steps for minimization. If 0 it there will be no minimization and only the energy is evaluated.
    \param[in] flexHydCutoff Cutoff value for flexible protein hydrogens.
        Algorithm will find the minimum distance between ligand and protein atoms and
        select all protein hydrogens within this minmal distance + flexHydCutoff from any protein atoms as flexible. 
        0 for no flexible protein hydrogens.
    \param[in] minTraj Optional bundle of trajectories which contains the minimization steps for each timestep of the input trajectory
    */
    void MOLCHEM_API minimizeComplex(MolObject& ligandTraj,Molecule& complex, float cutoff,int maxSteps,float flexHydCutoff,McDArray<MolTrajectoryMem*>* minTraj=0);
    void MOLCHEM_API minimize(MolObject& ligandTraj, float cutoff,int maxSteps,McDArray<MolTrajectoryMem*>* minTraj=0);
    
    /** This class allows to compute and minimize the MMFF94 energy for a protein ligand interaction.
        During minimization the protein is fixed in space, but target atoms can be defined as flexible.
        Non structure specific force field parameters are set directly via the force field methods.
    */

    class MOLCHEM_API ProteinLigandInteraction {
    public:
        ProteinLigandInteraction();
        ~ProteinLigandInteraction();
        void setProtein(Molecule& protein);
        void setLigand(MolObject& ligand);
        /** Minimizes the ligand in the field of the protein
        \param[in] maxSteps Maximal steps for minimization. If 0 it there will be no minimization and only the energy is evaluated.
        \param[in] flexHydCutoff Cutoff value for flexible protein hydrogens.
            Algorithm will find the minimum distance between ligand and protein atoms and
            select all protein hydrogens within this minmal distance + flexHydCutoff from any protein atoms as flexible. 
            0 for no flexible protein hydrogens.
        \param[in] minTraj Optional bundle of trajectories which contains the minimization steps for each timestep of the input trajectory
        */
        void minimizeComplex(int maxSteps,McDArray<MolTrajectoryMem*>* minTraj=0, bool writeBack=true, float flexHydCutoff=0);
        /// Compute interaction energy for the whole complex (overall energy - ligand self energy - protein self energy)
        void computeComplex();
        /// Computes internal energy for ligand and protein
        void computeProteinSelfEnergy();
        /// Computes internal energy for ligand only
        void computeLigandSelfEnergy();
        /** Returns the field. This can be used both before the computations, to specify non structure specific force field parameters,
            like the selection of force field components and the cutoff, and after the computation, to access the result struct containing
            the energies in the force field */
        MMFF94_ForceField& getField();
    protected:
        Molecule* target;
        MolObject* ligand;
        // --
        mmff94::MMFF94_ForceField* field;
    };
}

#endif

/// @}
