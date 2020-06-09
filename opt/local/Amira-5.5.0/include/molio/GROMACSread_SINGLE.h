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
#ifndef GROMACSREAD_SINGLE_H
#define GROMACSREAD_SINGLE_H

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

#include <mclib/McHandable.h>
#include <mclib/McDArray.h>
#include <mclib/McString.h>

#include <molio/readerBase.h>
#include <molio/writerBase.h>

class MolTrajectoryGROMACS_SINGLE;
class Molecule;
class MolTopology;
class MtIntraLevelRange;

/** This struct describes the order and the sizes of the structs in a
    trjfile, sizes are given in bytes. This struct was implemented 
    with help of the gromacs file format*/
class TrnHeader_SINGLE : public McHandable 
{
public: 

    TrnHeader_SINGLE();
    
    int   ir_size;        /* Backward compatibility                       */
    int   e_size;         /* Backward compatibility                       */
    int   box_size;       /* Non zero if a box is present                 */
    int   vir_size;       /* Backward compatibility                       */
    int   pres_size;      /* Backward compatibility                       */
    int   top_size;       /* Backward compatibility                       */
    int   sym_size;       /* Backward compatibility                       */
    int   x_size;         /* Non zero if coordinates are present          */
    int   v_size;         /* Non zero if velocities are present           */
    int   f_size;         /* Non zero if forces are present               */

    int   natoms;         /* The total number of atoms                    */
    int   step;           /* Current step number                          */
    int   nre;            /* Backward compatibility                       */
    float        t;      /* Current time                                 */
    float        lambda; /* Current value of lambda                      */

    int timeSteps;
    int magic;
    int strLen;
    unsigned char* string;
};

/** class for reading GROMACS fileformats to be viewed as a Molecule.
 */

class MOLIO_API GROMACSread_SINGLE
{
public:          
    /// main constructor
    GROMACSread_SINGLE(ostream * str = 0, McProgressInterface * wArea = 0);

    // return a READ Trajectory    
    MolTrajectoryGROMACS_SINGLE * readGROMACS_SINGLEMolTrajectory(const char * fileNameTRJ, const char * fileNameGRO, const char * fileNameTOP = 0);
    
    /// reads a non trajectory molecule
    Molecule * readGROMACS_SINGLEMolecule(const char *fileNameGRO, const char *fileNameTOP=0);  

    /// return name of file format
    const char * getName() const { return "GROMACS Single Precision"; }

    /** reading coordinates of the trajectory at the timestep ix, at
        the streamposition trajsp in the file FileName */
    TrnHeader_SINGLE * readCoordsAt(Molecule* M, long trajPos, McString FileName);

    ostream * stream;
    McProgressInterface * workArea;   

    /// reads the trajectory coordinates in the Filename
    int readGROMACS_TrajCoords(McString FileName, int * bytes);
    
    // reads the structure of a gromacs gro file
    Molecule* readGRO(const char *fileName);

    // read the topology of a gromacs top file
    int readTOP(const char *fileName, Molecule * M);

    // reads the trajectory of a gromacs trr file
    int readTrajectory(const char *fileName, Molecule * M);           
    
    /// the main filename ending with .top
    McString mainfilename;
};

#endif

/// @}
