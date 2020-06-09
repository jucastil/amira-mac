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
#ifndef MOL_OBJECT_H
#define MOL_OBJECT_H

#include "MoleculeWinDLLApi.h"

class McMat4f;
class McVec3f;
class McVec3d;
class McBox3f;
class MolTopology;
class McBitfield;
template <class T> class McDArray;


/** This interface provides common functionality between Molecule and MolTrajectoryMem

    Ideally the trajectory and molecule classes would be joined in a single data structure
    which is however a lot of work to change. This interface is an adjustment to the current system, 
    allowing unified handling of the two data classes.

*/

class MOLECULE_API MolObject {
public: 
    /// Returns the topology. The topology is guaranteed to not be a null pointer.
    virtual MolTopology* getTopology() =0;
    virtual ~MolObject() {}
    /// Returns the topology. The topology is guaranteed to not be a null pointer.
    virtual const MolTopology* getTopology() const =0;
    /// Returns the number of timesteps
    virtual int getNumTimeSteps() const =0 ;
    /// Returns the coordinate of the ix'th atom in the step'th timestep in c
    virtual void getCoordinate(int step,int ix,McVec3f& c) const =0;
    /// Sets the coordinate of the ix'th atom in the step'th timestep to c
    virtual void setCoordinate(int step,int ix,const McVec3f& c) =0;
    /// Returns the coordinate of the ix'th atom in the step'th timestep in c. Coordinate is converted from McVec3f
    virtual void getCoordinate(int step,int ix,McVec3d& c) const;
    /// Sets the coordinate of the ix'th atom in the step'th timestep to c. Coordinate is converted to McVec3f
    virtual void setCoordinate(int step,int ix,const McVec3d& c);
    /// Returns the coordinates the step'th timestep in c. Coordinates are converted from McVec3f
    virtual void getCoordinates(int step,McDArray<McVec3d>& c) const;
    /// Returns the coordinates the step'th timestep in c.
    virtual void getCoordinates(int step,McDArray<McVec3f>& c) const;
    /// Sets the coordinate of the step'th timestep to c. 
    virtual void setCoordinates(int step,const McDArray<McVec3f>& c);
    /// Sets the coordinate of the step'th timestep to c. Coordinates are converted to McVec3f
    virtual void setCoordinates(int step,const McDArray<McVec3d>& c);
    /** Removes all groups of given level whose index is set in bitfield.
        If atom level it also removes the coordinates */
    virtual void removeGroups(int levelIx,const McBitfield& bf);
    /** Moves group groupIx to index newGroupIx. Indices of level and of dependant level will be updated.
        If level is atoms, coordinates will be copied too */
    virtual void moveGroup(int levelIx,int groupIx, int newGroupIx);
    /// Resizes the coordinates for all timesteps. No initialization.
    virtual void resizeCoordinates(int size) =0;
    /// Removes coodinates in all timestep of all atoms set in the bitfield
    virtual void removeCoordinates(const McBitfield& atoms);
    /// Transforms atoms set in bitfield in all timesteps
    virtual void transform(const McMat4f&,const McBitfield* atoms=0);
    /// Transforms atoms set in bitfield in the given timestep
    virtual void transform(int timeStep,const McMat4f&,const McBitfield* atoms=0);
    /// Returns number of coordinates (i.e. number of atoms in the molecule)
    virtual int getNumCoordinates() const =0;
    /** Return bounding box of the step'th timestep */
    virtual void computeBoundingBox(int step,McBox3f& bbox) const;
    /// Returns overall bounding box (of all timesteps)
    virtual void computeBoundingBox(McBox3f& bbox) const;
    /** Return bounding box of the step'th timestep */
    virtual void computeBoundingBox(int step,const McDArray<int>& atoms,McBox3f& bbox) const;
    /// Returns overall bounding box (of all timesteps)
    virtual void computeBoundingBox(const McDArray<int>& atoms,McBox3f& bbox) const;
    /** Return bounding box of the step'th timestep */
    virtual void computeBoundingBox(int step,const McBitfield& atoms,McBox3f& bbox) const;
    /// Returns overall bounding box (of all timesteps)
    virtual void computeBoundingBox(const McBitfield& atoms,McBox3f& bbox) const;
    /// Compute center of gravity for the step'th timestep
    virtual void computeCenterOfGravity(int step,McVec3f& cog) const;
    /// Compute center of gravity for the step'th timestep
    virtual void computeCenterOfGravity(int step,const McDArray<int>& atoms,McVec3f & cog) const;
    /// Compute center of gravity for the step'th timestep
    virtual void computeCenterOfGravity(int step,const McBitfield& atoms,McVec3f & cog) const;
};

#endif

/// @}
