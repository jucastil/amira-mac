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

/// @addtogroup hxmolio hxmolio
/// @{
#ifndef HXMOLIOWIZARD_H
#define HXMOLIOWIZARD_H

#include <mclib/McHandle.h>

#include <molecule/MolTrajectory.h>

#include <hxmolio/HxMolIOWinDLLApi.h>

class Molecule;
class HxMolecule;
class HxMolTrajectory;
class HxMolTrajectoryBundle;

class HXMOLIO_API HxMolIOWizard {
    
public:
    //////////// AMBER
    static int loadAMBERHxMolTrajectory(const char * fileName); 
    static int loadAMBERHxMolecule(const char * fileName);

    //////////// GROMACS SINGLE & DOUBLE  (when loading, amira automaticly recorgnize the format)
    static int loadGROMACS(int n, const char ** fileName); 

    static int saveGROMACSHxMolecule(HxMolecule * hxtraj, const char * fileName);
    static int saveGROMACSHxMolTrajectory(HxMolTrajectory * hxtraj, const char * fileName);   

    static int saveGROMACS_SINGLEHxMolecule(HxMolecule * hxtraj, const char * fileName);
    static int saveGROMACS_SINGLEHxMolTrajectory(HxMolTrajectory * hxtraj, const char * fileName);

    //////////// PDB 
    static int loadPDB(const char * fileName);

    static int savePDBHxMolecule(HxMolecule * hxmol, const char* fileName);
    static int savePDBHxMolTrajectory(HxMolTrajectory* hxtraj, const char* fileName);

    /////////// UNIChem
    static int saveUniChemHxMolecule(HxMolecule * hxmol, const char * fileName);
    static int loadUniChemHxMolecule(const char * fileName);

    /////////// Tripos
    static int loadTripos(const char * fileName);
    static int saveTriposHxMolecule(HxMolecule * hxmol, const char * fileName);
    static int saveTriposHxMolTrajectoryBundle(HxMolTrajectoryBundle* hxtraj, const char* fileName);
    /////////// MolBundleIO
    //static int saveMolBundleIO(HxMolecule * hxmol, const char * fileName);    ???????
    static int loadMolTrajBundleIO(const char * fileName);

    /////////// XYZ
    static int loadXYZHxMolTrajectory(const char * fileName);

    /////////// VDE
    static int loadVDEHxMolTrajectory(int n, const char ** fileName);

    /////////// DCD
    static int loadDCDHxMolTrajectory(int n, const char ** fileName);

    //////////// MDL
    static int loadMDL(const char * fileName);

    static int saveMDLHxMolecule(HxMolecule * hxtraj, const char* fileName);
    static int saveMDLHxMolTrajectory(HxMolTrajectory* hxtraj, const char* fileName);
    static int saveMDLHxMolTrajectoryBundle(HxMolTrajectoryBundle* hxtraj, const char* fileName);

    /// Add bundle or trajectory or molecule to object pool.
    static int registerData(const char * fileName,
                            const McDArray<McHandle<MolTrajectory> > & bundle);
};

#endif

/// @}
