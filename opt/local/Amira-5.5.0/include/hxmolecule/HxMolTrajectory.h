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
#ifndef HX_MOL_TRAJECTORY_H
#define HX_MOL_TRAJECTORY_H

#include <mclib/McHandle.h>

#include <hxcore/HxData.h>
#include <hxcore/HxPortMultiMenu.h>

#include <molecule/MolTrajectory.h>

#include <hxmolecule/HxMoleculeWinDLLApi.h>
#include <hxmolecule/ComputeListenerHandler.h>

class Molecule;
class MolAlignment;

/** Amira wrapper for the @c MolTrajectory class. */

class HXMOLECULE_API HxMolTrajectory : public HxData {
    HX_HEADER(HxMolTrajectory);

public:    
    /// Handler that allows registering compute listeners
    ComputeListenerHandler computeListenerHandler;    

    /// Connection to @c HxMolTrajectoryBundle.
    HxConnection portBundle;

    /// Menu showing all trajectories contained in trajectory bundle.
    HxPortMultiMenu portTrajectory;

    ///
    int lockCount;

protected:
    // Current trajectory.
    McHandle<MolTrajectory> traj;
    
public:
    /// Constructor.
    HxMolTrajectory(MolTrajectory *T=0);
    
    /// Return current trajectory.
    MolTrajectory * getTrajectory() { return traj; }
    ///
    void setTrajectory(MolTrajectory * t);
    /// Returns number of time steps.
    int getNumTimeSteps() { return traj->getNumTimeSteps(); }
    /// Return the molecule with time step @c ts.
    bool getTimeStep(int _timeStep, Molecule * mol);

    /// Compute for each time step the rmsd value w.r.t. the alignment object. 
    /// The rmsd values are stored in @c values. If @c flag is set
    /// to 0 or 1, only the minimum or maximum value will be saved,
    /// respectively. In this case, the index of the respective time
    /// step will be returned. 
    /// If a @c selectionBf is given, only the atoms for which the bit is set 
    /// in @c selectionBf are considered in the computation of the rmsd. This 
    /// bitfield has no effect on the alignment!!!
    int  computeRMSD(MolAlignment     * alignment, 
                     McDArray<float>  & values, 
                     const int          flag = 2,
                     const McBitfield * selectionBf = 0);

    /// Same as above but with two different selections for master and
    /// slave.  This allows computing the alignment and rmsd for
    /// different molecules.
    int  computeRMSD(MolAlignment     * alignment, 
                     McDArray<float>  & values, 
                     const int          flag,
                     const McBitfield * masterSelectionBf,
                     const McBitfield * slaveSelectionBf);

    /// Overloaded method.
    void info();
    /// Overloaded method.
    void update();
    /// Overloaded method - connect @c portBundle to an @c
    /// HxMolTrajectoryBundle.
    int autoConnect(HxObject* primary);
    /// Overloaded method - write load or create command to script. 
    int saveCreation(FILE* fp, const char* dataDir, int savingFlags);
    /// Overloaded method - write ports to script. 
    void savePorts(FILE* fp);
    ///
    void lock(bool lockFlag);
    /// Duplicates the current HxMolTrajectory object
    virtual HxData *duplicate() const;
    // Overloaded function - parse tcl commands.
    int parse(Tcl_Interp* t, int argc,char **argv);
    ///   Virtual function compute - called if the object has been touched and fired.
    virtual void compute();
    /** version of fire which ensures that if the trajectory is part of a
        bundle, the bundle is fired instead (fire cascade is
        initiated in the upstream object). This command must be called
        instead of fire whenever an edit of the trajectory affects the bundle.*/
    void fireUpstream();

};

#endif

/// @}
