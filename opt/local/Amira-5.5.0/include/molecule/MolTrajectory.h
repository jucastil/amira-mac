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
#ifndef MOL_TRAJECTORY_H
#define MOL_TRAJECTORY_H

#include <mclib/McHandable.h>
#include <mclib/McHandle.h>
#include <mclib/McString.h>

#include "MoleculeWinDLLApi.h"
#include "MolTopology.h"
#include "MolObservables.h"
#include "Molecule.h"

class HxLattice3;

/** Molecule trajectory = topology + time steps.
    All the information in a trajectory file. */
class MOLECULE_API MolTrajectory : virtual public McHandable 
{

public:
    /// Create from data handle
    MolTrajectory();

    /// Number of configurations
    virtual int getNumTimeSteps() const = 0;

    /// Get configuration by index. Counted from 0.
    virtual bool getTimeStep(int ix, Molecule * mol) = 0;

    ///
    virtual int getNumFields(int timestep=0) const;
    ///
    virtual int getFieldDims(int fieldId, int ixconf, int *dims) const;
    /// 
    virtual int getFieldData(int fieldId, int ixconf, float *data) const;
    ///
    virtual int getFieldBbox(int fieldId, int ixconf, float * bb) const;
    ///
    virtual void getFieldNames(char** names) const;

    /// Get topology.
    virtual MolTopology* getTopology() { return T; }
    /// Get topology.
    virtual const MolTopology * getTopology() const { return T; }
    /// Get observables.
    MolObservables * getObservables() { return obs; }

    /// sets value of the 'name' data entry in the MolTopology
    void setName(const char * name) { getTopology()->setName(name); }
    
    /// returns value of 'name' data entry in the MolTopology. "" if it does not exist.
    const char *getName() const { return getTopology()->getName(); }

    ///
    virtual const char *getInfoText() const { return 0; }

    /// Topology object
    McHandle<MolTopology> T;
    /// Observable object
    McHandle<MolObservables> obs;
};

#endif

/// @}
