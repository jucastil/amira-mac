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
#ifndef MOL_MDLIO_H
#define MOL_MDLIO_H

#include <molio/MolIOWinDLLApi.h>

#include <molio/readerBase.h>
#include <molio/writerBase.h>

#include <mclib/McProgressInterface.h>
#include <mclib/McHandle.h>

#ifdef NEWSTYLE_IOSTREAM
#include <iostream>
using std::ostream;
#include <streambuf>
using std::streambuf;
#else
#include <iostream.h>
#endif

class Molecule;
class MolTopology;
class MolTrajectory;
class MolTrajectoryMem;


/** reader and writer for mdl sdf files */

class MOLIO_API MDLIO {

    ostream * stream;
    McProgressInterface * workArea;

public:

    int checkNumAtomsBonds(const MolTopology* M);

    /// should be removed in future
    int writeMDLMolecule(Molecule* M, const char* filename, writer & w) ;

    int readMolecule(Molecule * M, MolTopology * T, 
                            lengthizer & t, const char *filename);

    McDArray<McHandle<MolTrajectory> > readMDLMolTrajectoryBundle(const char* filename);

    MolTrajectory * readMDLMolTrajectory(const char* filename);

    int writeMDLMolecule(Molecule* M, const char* filename) ;

    // should be removed in future / renamed / reorganized
    int writeMDLMolTrajectory(MolTrajectory* moltraj, const char* filename) ;
    int writeMDLMolTrajectoryBundle(const McDArray<MolTrajectory*> moltraj, const char* filename) ;

    MDLIO(ostream * str = 0, McProgressInterface * wArea = 0);

    /// return name of file format
    const char * getName() const { return "MDL ISIS sdf";}
};

#endif




/// @}
