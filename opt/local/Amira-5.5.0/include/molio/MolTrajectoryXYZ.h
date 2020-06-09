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
#ifndef MOL_TRAJECTORY_XYZ_H
#define MOL_TRAJECTORY_XYZ_H

#include "MolIOWinDLLApi.h"
#include "molecule/MolTrajectory.h"

#include <molio/AtomDataBase.h>

#ifdef NEWSTYLE_IOSTREAM
#include <iostream>
using std::istream;
using std::ios;
using std::streampos;
using std::ostream;
#else
#include <iostream.h>
#endif


/*
#ifdef __sun
#include <iosfwd>
using std::streampos;
#endif
*/
/** Molecule trajectory = topology + time steps.
    All the information in a trajectory file. */
class MOLIO_API MolTrajectoryXYZ : public MolTrajectory 
{
private:

    ostream * stream;

    ///
    McDArray<streampos> seekTable;

    ///
    istream * inStream;

    AtomDataBase * atomDB;

protected:
    ///
    int nOffspringObservables() const { return 0; }
    ///
    const char * offspringObservableName(int index) const { return 0; }
    ///
    float offspringObservable(int ix, int step) const { return 0; }
    
public:
    /// Create from data handle
    MolTrajectoryXYZ(ostream * str, AtomDataBase * atomDataB);

    /// Number of configurations
    int getNumTimeSteps() const;

    /// Get configuration by index. Counted from 0.
    bool getTimeStep(int ix, Molecule * mol);

    ///
    static int read(const char *fileName);

    MolTrajectoryXYZ * readXYZMolTrajectory(const char *filename);
};

#endif

/// @}