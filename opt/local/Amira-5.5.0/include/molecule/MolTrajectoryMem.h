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
#ifndef MOL_TRAJECTORY_MEM_H
#define MOL_TRAJECTORY_MEM_H

#include <mclib/McVec3f.h>

#include "Molecule.h"
#include "MolTrajectory.h" 
#include "MoleculeWinDLLApi.h"

class McBox3f;


/** This class allows to keep a whole molecular trajectory in
    memory. You can iteratively add new timesteps, whereby it is
    assumed that the topology is the same as for the rest of the
    trajectory. */

class MOLECULE_API MolTrajectoryMem : public MolTrajectory , public MolObject{
public: 
    /// Default constructor.
    MolTrajectoryMem();
    /// Construtor taking the first timestep and the anticipated size
    /// of the trajectory.
    MolTrajectoryMem(Molecule * mol, int size);
    ///
    MolTrajectoryMem(MolTrajectory* traj);
    /// Destructor.
    ~MolTrajectoryMem(); 

    /// Set the topology explicitly.  The topology will not be
    /// duplicated, hence, you should ensure that the topology will
    /// not be changed unwanted.
    void setTopology(MolTopology * topo) { T=topo; }
    /// Returns the number of timesteps.
    int getNumTimeSteps() const;
    /// Resizes the number of timesteps the trajectory should contain.
    /// Before this function can be called, the topology must be set
    /// either by using setTopology(..) or by constructing the object
    /// using one of the non-default constructors.
    void resize(int j);
    /// If ix is out of range, the size will be automatically
    /// adjusted.  Furthermore, this function also sets the topology
    /// if none has been set before.
    void setTimeStep(int ix, Molecule * mol);
    /// If ix is out of range, the size will be automatically adjusted.
    void setTimeStep(int ix, McDArray<McVec3f> & coords);
    /// Copies timestep with index @c ix to @c mol.
    bool getTimeStep(int ix, Molecule * mol);

    /// Returns an info text for this trajectory.
    const char * getInfoText();
    /** Returns pointer to coordinates. May be edited directly, instead of setTimeStep.
        Pointer will point to memory array of size nAtoms*sizeof(McVec3f)*/
    McVec3f* getCoordinates(int step) const { return (McVec3f*)(mCoords[step].dataPtr()); } 
    // Append coordinates & observables. Returns 0 if topology &
    // observables matches and negative values otherwise.
    int append(MolTrajectoryMem * traj); 
    /// Resize each timestep. If the newSize increases, the coordinates will be initialized with 0.
    void resizeCoordinates(int newSize);
    /** removes all timesteps set in bitfield (ie. timesteps in coordinates and observables)
    Currently works only if traj has float or int observables only */
    void removeTimesteps(const McBitfield& bf);
    enum BB_RESTRICTION_MODE {
        BB_INSIDE, // all atoms of timesteps must be inside of bounding box
        BB_INTERSECT // at least one atom of timesteps must be inside of bounding box
    };
    /** restricts trajectory to timesteps which are inside of bounding box region, as defined by the mode. All other timesteps are removed.
        Currently works only if traj has float or int observables only */
    void restrictTimesteps(const McBox3f&,BB_RESTRICTION_MODE m);
    /** Reorders timesteps according to index in array, i.e. the new 0'th timestep will be the old index[0]'th timestep and so on.
    */
    void reorderTimesteps(const McDArray<int>& index);

    void transform(const McMat4f&);

    virtual void getCoordinate(int step,int ix,McVec3f& c) const;
    virtual void setCoordinate(int step,int ix,const McVec3f& c);
    virtual int getNumCoordinates() const;
    MolTopology* getTopology() { return MolTrajectory::getTopology();}
    const MolTopology* getTopology() const { return MolTrajectory::getTopology();}

private:
    ///    
    const McVec3f * coords(int step) const;

    ///
    void setCoords(int step, const McVec3f * coords);
    
    // Coordinates of all timesteps.
    McDArray< McDArray <McVec3f> > mCoords;
    
};

#endif

/// @}
