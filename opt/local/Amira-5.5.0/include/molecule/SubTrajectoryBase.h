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

/// @addtogroup molecule molecule
/// @{
#ifndef SUB_TRAJECTORY_BASE_H
#define SUB_TRAJECTORY_BASE_H

#include <mclib/McHandle.h>

#include "MoleculeWinDLLApi.h"
#include "MolTrajectory.h"

/** Sub trajectory = topology + time steps.
    All the information in a trajectory file. */
class MOLECULE_API SubTrajectoryBase : public MolTrajectory
{
public:
    /// Create from data handle
    SubTrajectoryBase(MolTrajectory * t);

    /// Destructor.
    ~SubTrajectoryBase();
    
    /// Fill array with selected time steps.
    virtual void getSubTrajTimeSteps(McDArray<int> & timeSteps)=0;
    /// Number of configurations
    virtual int getNumTimeSteps() const = 0;
    /// Get configuration by index. Counted from 0.
    virtual bool getTimeStep(int ix, Molecule * mol)=0;
    /// Return true if subtrajectory contains this time step of main
    /// trajectory, false otherwise.
    virtual bool contains(int index)=0;
    /// Returns index of time step in main trajectory.
    virtual int mapTimeStep(int idx)=0;

    ///
    virtual int nFields(int timestep=0);
    ///
    virtual int getFieldDims(int fieldId, int ixconf, int *dims);
    /// 
    virtual int getFieldData(int fieldId, int ixconf, float *data);
    ///
    virtual int getFieldBbox(int fieldId, int ixconf, float * bb);
    ///
    virtual void getFieldNames(char** names);

protected:
    /// Pointer to full trajectory.
    McHandle<MolTrajectory> mainTrajectory;
};

#endif

/// @}
