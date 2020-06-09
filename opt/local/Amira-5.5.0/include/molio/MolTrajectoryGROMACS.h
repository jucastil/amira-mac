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
#ifndef MOL_TRAJECTORYGROMACS_H
#define MOL_TRAJECTORYGROMACS_H

#include "MolIOWinDLLApi.h"
#include <molecule/MolTrajectory.h>
#include <molio/GROMACSread.h>
#include <mclib/McDArray.h>
#include <mclib/McString.h>

class TrnHeader; 
/**
 * class reading a molecular trajectory from GROMACS files.
 */

class Molecule;

class MOLIO_API MolTrajectoryGROMACS : public MolTrajectory 
{
protected:    

    /// overwriting function that is not needed
    int nOffspringObservables() const { return 0; }

    /// overwriting function that is not needed
    const char * offspringObservableName(int index) const { return 0; }

    /// overwriting function that is not needed
    float offspringObservable(int ix, int step) const { return 0; }

    /// number of timesteps in the trajectory
    int timeSteps;

    int magic;

    /// name of the file, the trajectory coordinates are saved in
    McString trajfilename;

    /// name of the trajectory
    McString name;

    /// file where main informations (topology...) are saved in
    McString mainfilename;

    // actual Molecule 
    Molecule * M;
   
public: 

    McHandle<TrnHeader> header;

    /// main constructor
    MolTrajectoryGROMACS(Molecule * mol, const McString & trajfileName);

    /// Destructor
    ~MolTrajectoryGROMACS();    

    /// Number of configurations 
    int getNumTimeSteps() const;     

    /// Get configuration by index. Counted from 0.
    bool getTimeStep(int ix, Molecule * mol);

    /// reads the streampopsitions of the trajectory coordinates or velocities(currently not used)
    int setStreamPos();

    /// saves the streamposition of the trajectory coordinates for each timestep
    McDArray<long> trajstreamPos;
};

#endif 

/// @}
