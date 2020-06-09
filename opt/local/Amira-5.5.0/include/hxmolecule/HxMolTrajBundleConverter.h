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

/// @addtogroup hxmolecule hxmolecule
/// @{
#ifndef HxMolTrajBundleConverter_H
#define HxMolTrajBundleConverter_H

#include <mclib/McDArray.h>

#include <hxcore/HxCompModule.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortDoIt.h>

#include "HxMoleculeWinDLLApi.h"

class HxObject;
class MolTrajectory;
class MolTrajectoryMem;

/** This module takes a set of molecules, trajectories and bundles of
    trajectories and creates a new trajectory or a new bundle. All
    molecules and time steps will be copied to the new trajectory or
    bundle, respectively. */
class HXMOLECULE_API HxMolTrajBundleConverter : public HxCompModule
{
    HX_HEADER(HxMolTrajBundleConverter);

public:
    /// Create from data handle.
    HxMolTrajBundleConverter();
    /// Destructor.
    ~HxMolTrajBundleConverter();

    /// Update user interface.
    void update();

    /// Trigger computations.
    void compute();

    /// Further molecules.
    McDArray<HxConnection * > portInputs;
    /// Buttons to automatically connect objects from the object pool
    HxPortButtonList portAddInput;
    /// Specify whether a trajectory or a bundle should be created.
    HxPortRadioBox portResultType;
    /// Start computation.
    HxPortDoIt portAction;
    
protected:
    // Update dynamic ports.
    void updateConnections();
    // Return topology of input and set name to the name of input.
    MolTopology * getTopology(HxObject * input, const char * & name);
    // Compare the topologies topo and topo2. True is returned, if the
    // topologies are compatible, false otherwise.
    bool compareTopologies(MolTopology * topo, MolTopology * topo2,
                           const char * name, const char * name2);
    // Create a trajectory from molecules, trajectories and bundles.
    void mergeMoleculesIntoTrajectory(McDArray<HxObject *> & inputs, 
                                      const char * name);
    // Append all time steps of @c molTraj to @c molTrajMem.
    void appendTrajToMemTrajectory(MolTrajectoryMem * molTrajMem,
                                   MolTrajectory * molTraj);
    // Create a bundle from molecules, trajectories and bundles.
    void mergeMoleculesIntoBundle(McDArray<HxObject *> & inputs,
                                  const char * name);
    // Create a molecule from molecules, trajectories and bundles.
    void mergeMoleculesIntoMolecule(McDArray<HxObject *> & inputs,
                                  const char * name);
};

#endif

/// @}
