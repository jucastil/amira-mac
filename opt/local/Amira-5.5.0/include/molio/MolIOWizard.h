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

/// @addtogroup molio molio
/// @{
#ifndef MOLIOWIZARD_H
#define MOLIOWIZARD_H

#include <mclib/McDArray.h>
#include <mclib/McHandle.h>

#include <molio/MolIOWinDLLApi.h>

class Molecule;
class MolTrajectory;

namespace MolIOWizard {

    enum ReadMolecules {
        AMBER_RMOL,
        GROMACS_RMOL,
        GROMACS_SINGLE_RMOL,
        MDL_RMOL,
        PDB_RMOL,
        TRIPOS_RMOL,
        UNICHEM_RMOL,
        ZMF_RMOL,
        UNKNOWN_FORMAT_RMOL,
    };

    enum WriteMolecules {        
        GROMACS_WMOL,
        GROMACS_SINGLE_WMOL,
        MDL_WMOL,
        PDB_WMOL,
        TRIPOS_WMOL,
        UNICHEM_WMOL,
        ZMF_WMOL,
    };

    enum ReadTrajectories {        
        AMBER_RTRJ,
        DCD_RTRJ,
        GROMACS_RTRJ,
        GROMACS_SINGLE_RTRJ,
        MDL_RTRJ,
        PDB_RTRJ,
        VDE_RTRJ,
        XYZ_RTRJ,
        ZMF_RTRJ,
        UNKNOWN_FORMAT_RTRJ,
    };

    enum WriteTrajectories {        
        GROMACS_WTRJ,
        GROMACS_SINGLE_WTRJ,
        MDL_WTRJ,   
        PDB_WTRJ,        
        ZMF_WTRJ,        
    };

    enum WriteBundles {
        GENERIC_WBUN,   // All Molecules will be saved as ZMF Molecules
        PDB_WBUN,
        ZMF_WBUN,
        TRIPOS_WBUN
        
    };

    enum ReadBundles {
        GENERIC_RBUN,   // allowing all kinds of bundles, this should be used as MoleculeBundle files
        PDB_RBUN,
        ZMF_RBUN,
        TRIPOS_RBUN,
        UNKNOWN_FORMAT_RBUN,
    };



    MOLIO_API int writeMolecule(const char * fileName, Molecule * m, MolIOWizard::WriteMolecules type = MolIOWizard::ZMF_WMOL);        
    MOLIO_API int writeMolTrajectory(const char * fileName, MolTrajectory * tr, MolIOWizard::WriteTrajectories type=MolIOWizard::ZMF_WTRJ);
    MOLIO_API int writeBundle(const char * fileName, McDArray<McHandle <MolTrajectory> > bundle, MolIOWizard::WriteBundles type=MolIOWizard::ZMF_WBUN);                  
                
    MOLIO_API Molecule *     readMolecule(const char * fileName, MolIOWizard::ReadMolecules type=MolIOWizard::UNKNOWN_FORMAT_RMOL, const char * fileName2 = 0);                                
    MOLIO_API MolTrajectory * readMolTrajectory(const char * fileName, MolIOWizard::ReadTrajectories type=MolIOWizard::UNKNOWN_FORMAT_RTRJ, const char * fileName2 = 0, const char * fileName3 = 0);
    MOLIO_API McDArray<McHandle <MolTrajectory> > readBundle(const char * fileName, MolIOWizard::ReadBundles type=MolIOWizard::UNKNOWN_FORMAT_RBUN);              

    // Test functions    
    MOLIO_API void readTestMolecule();    
    MOLIO_API void readTestMolTrajectory();

    MOLIO_API void writeTestMolecule(Molecule *m);
    MOLIO_API void writeTestMolTrajectory(MolTrajectory *tr);
}

#endif

/// @}
