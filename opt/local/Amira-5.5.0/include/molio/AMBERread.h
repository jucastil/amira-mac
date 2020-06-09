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
#ifndef AMBERREAD_H
#define AMBERREAD_H

#include <mclib/McDArray.h>
#include <mclib/McString.h>

#include <molio/readerBase.h>
#include <molio/writerBase.h>
#include <molio/MolTrajectoryAMBER.h>
#include "MolIOWinDLLApi.h"

#include <mclib/McProgressInterface.h>

#ifdef NEWSTYLE_IOSTREAM
#include <iostream>
using std::ostream;
#include <streambuf>
using std::streambuf;
#else
#include <iostream.h>
#endif

class MolTrajectoryAMBER;
class Molecule;
class MolTopology;
class MtIntraLevelRange;

/**
 * class for reading amber fileformats to be viewed as a Molecule.
 */

class MOLIO_API AMBERread
{
public:
    /// reads a non trajectory molecule
    Molecule * readAmberMolecule(const char *fileName);

    /// read the trajectory
    MolTrajectoryAMBER * readAmberMolTrajectory(const char *fileNameTRJ, const char * fileNameMOL, const char * fileNameVEL = 0);

    /// main constructor
    AMBERread(ostream * str = 0, McProgressInterface * wArea = 0);

    /// return name of file format
    const char * getName() const { return "Amber"; }
             
    ostream * stream;
    McProgressInterface * workArea;

    /// reads the trajectory coordinates in the Filename
    int readAmber_TrajCoords(McDArray<long> &stream, int nAtoms,  McString FileName);

    /// reads the velocities coordinates in the Filename
    int readAMBER_TrajVelocities(McDArray<long> &stream, int nAtoms, McString FileName);     
    
    /** reads the amber main file, as a Molecule or a MolTrajectoryAMBER and registers
     *  it in the ObjectPool */
    McHandle<Molecule> read(const char *fileName, int ix=0, 
                            McDArray<long> trajsp=McDArray<long>(0), 
                            McDArray<long> velsp=McDArray<long>(0));
    
    // reads the coordinates of the molecule from the coordinate file ending with .crd
    int readAmberCoords(Molecule* M, McString coordsFileName);
    
    /// the main filename ending with .top
    McString mainfilename;

    /** reading coordinates of the trajectory at the timestep ix, at the streamposition trajsp
         *  in the file FileName */
    int readCoordsAt(Molecule* M, int ix, McDArray<long> &trajsp, McString FileName);

    /// reading velocities of the trajectory at the timestep ix in the file FileName 
    int readVelAt(Molecule* M, int ix, McDArray<long> velsp);    
};

#endif

/// @}
