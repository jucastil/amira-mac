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
#ifndef MOLECULE_H
#define MOLECULE_H

#ifdef NEWSTYLE_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif

#include <mclib/McVec3f.h>
#include <mclib/McHandable.h>
#include <mclib/McHandle.h>
template<class T> class McDArray;

#include "MtGroupRef.h"
#include "MoleculeWinDLLApi.h"
#include "MolObservables.h"
#include "MolTopology.h"
#include "MolObject.h"

class McMat4f;
class McVec3f;
class McVec3d;
class McBox3f;
class McBitfield;
class GroupRefTranslator;

/** A Molecule is the wrapper of the molecular data stucture.
    The Molecule and its substructure contain
    - Coordinates: (atom 3D positions)
    - Observables
    - Levels: Sets of groups of the same type and their attributes (e.g. bonds)
        A Molecule can contain an arbitrary number of levels.
    - Groups: Sets of groups (e.g. bond is group of 2 atoms, atom is empty group)
        A Level can consist of an arbitrary number of groups.
    - Attributes: (e.g. atomic_number is attribute of atoms)
        Each level can have an arbitrary number of attributes which will 
        contain values for each group of the level.

    A Molecule itself contains:
        - 1 MolObservables
        - 1 MolTopology
        - Coordinates

    The functionality is to be found as following:
    Molecule:         Accessing Coordinates
                      Getting MolTopology
    MolTopology:      Accessing Levels
                      Accessing Groups of levels
                      Getting Attributes
    MtGroupAttribute: Accessing attributes of groups


*/

class MOLECULE_API Molecule :  
    public McHandable , public MolObject {
public:
    
    /// Copy constructor 
    Molecule(Molecule & mol);
    
    /** Constructor, set Topology to T, if ownTopology is true, 
        topology will not be shared*/
    Molecule(MolTopology *T_ = new MolTopology(), bool ownTopology=false);
    
    /// Destructor
    ~Molecule();
    
    /// Returns exact copy of molecule including all data (cloning)
    Molecule * duplicate() const;

    /***********************************************************
                    Topology
     ***********************************************************/    

    /// Return pointer to associated topology.
    inline MolTopology * getTopology();
    inline const MolTopology * getTopology() const;

    /// Set topology. If ownTopology is true, the topology is not shared.
    void setTopology(MolTopology *T_, bool ownTopology=false);

    /// Ensure that the molecule references its own copy of the topology
    void makeOwnTopology();


    /***********************************************************
                    Observables
     ***********************************************************/    

    /// Get observables.
    inline MolObservables * getObservables();
    inline const MolObservables * getObservables() const;

    /// Set observables. 
    void setObservables(MolObservables * obs);

    /** Make own observables, i.e. copy observable values from
        observables of trajectory.*/
    void makeOwnObservables(int timeStep=-1);   

    /***********************************************************
                     Coordinates 
     ***********************************************************/

    /***********************************************************
        Access */

    /// Return number of coordinates
    inline int getNumCoordinates() const;

    /// Set number of coordinates to @c size
    inline void resizeCoordinates(int size);

    /// Get atom Coordinate 
    inline const McVec3f& getCoordinate(int atomIx) const;    

    /// Get atom Coordinates
    inline const McDArray<McVec3f>& getCoordinates() const;
    
    /// Set atom Coordinate of atom @c atomIx to vector @c co
    inline void setCoordinate(int atomIx,const McVec3f& co);

    /** Sets all atom 3D Coordinates. Internal coordinate array will be resized
        to @c num and as many vectors will be copied from memory @c mem */
    inline void setCoordinates(int num,const McVec3f* mem);

    /** Sets atom 3D Coordinates from atom @c startIx to atom @c startIx+length.
        No resize. Vectors will be copied from memory @c mem */
    inline void setCoordinates(int startIx,int length, const McVec3f* mem);

    /** Sets atom 3D Coordinates from atom @c startIx to atom @c startIx+length.
        No resize. Vectors will be copied from memory @c mem */
    inline void setCoordinates(int startIx,int length, const float* mem);
    
    /** set all atom 3D coordinates to @c co. 
        Internal coordinate array will be resized to the size of @c co */
    void setCoordinates(const McDArray<McVec3f>& co);

    /** Get coordinates as array of doubles. data will be copied to array.
        As coordinates are saved as floats internally data will be converted. */
    void getCoordinates(McDArray<McVec3d>& co) const;
    
    /** Set coordinates via array of doubles. 
        Internal coordinate array will be resized to the size of @c co.
        Coordinates will be transformed to floats internally */
    void setCoordinates(const McDArray<McVec3d>& co);


   
    /***********************************************************
        Measurements */
    
    /** Return bounding box of molecule
        bbox is saved internally */
    void getBbox(McBox3f& bbox);
    
    /** Compute @c bbox considering atoms set in @c useAtoms. */
    void getBbox(const McBitfield & useAtoms,McBox3f& bbox) const;

    /// Get distance between two atoms
    inline float getAtomDistance(int aix1,int aix2) const;
    
    /// Calculate a dihedral angle ix1-ix2-ix3-ix4
    float getDihedralAngle(const int ix[4]) const;
    
    /// Calculate bond angle of atomList[0]-atomList[1]-atomList[2].
    float getBondAngle(const McDArray<int>& atomList) const;
        
    /** Calculate the (arithmetic-mean) center of the molecule or groups.
        Result will be returned in cog */
    void computeCenterOfGravity(McVec3f& cog) const;
    void computeCenterOfGravity(const McDArray<int>& atoms,McVec3f & cog) const;
    void computeCenterOfGravity(const McBitfield& atoms,McVec3f & cog) const;
    void computeCenterOfGravity(int level,int groupIx,McVec3f & cog) const;

    
    /** Calculates a rigid transformation that transforms the source
        atoms onto the target atoms optimally in the sense of mean
        squared distances. */
    static void computeAlignTransform(McMat4f & transform,
                                   const Molecule * target, 
                                   const Molecule * source,
                                   const McDArray<int> & targetAtoms, 
                                   const McDArray<int> & sourceAtoms,
                                   const McMat4f * targetTransform=0);

    static void computeAlignTransform(McMat4f & transform,
                                   const Molecule * target, 
                                   const Molecule * source,
                                   const McMat4f * targetTransform=0);

    /** This function computes and returns the rmsd of the transformed 
        coordinates @c sourceAtoms of molecule @c source to the 
        coordinates @c targetAtoms of molecule @c target. The transformation
        is given by @c transform. */
    static float computeRMSD(const Molecule      * target, 
                             const Molecule      * source,
                             const McDArray<int> & targetAtoms, 
                             const McDArray<int> & sourceAtoms,
                             const McMat4f       & transform);

    /***********************************************************
        Transformation */
            
    /// Move molecule by vector trans
    void transform(const McVec3f& transf);
    
    /// Move atoms by vector trans
    inline void tranformAtom(int aIx,const McVec3f& transf);

    /// Move atoms by vector trans
    void tranformAtoms(const McDArray<int>& atoms,const McVec3f& transf);

    /// Move atoms by vector trans
    void tranformAtoms(const McBitfield& atoms,const McVec3f& transf);

    /// Tranforms the molecule by tranformation matrix
    void transform(const McMat4f & transf);
    
    /// Tranforms one atom by tranformation matrix
    inline void transformAtom(int aIx, const McMat4f & transf);    
    
    /// Tranforms array of atoms by tranformation matrix
    void transformAtoms(const McDArray<int>& atoms, const McMat4f & transf);        
    
    /// Tranforms all atoms marked in bitfield by tranformation matrix
    void transformAtoms(const McBitfield& atoms, const McMat4f & transf); 

    ///
    void addMolecule(const Molecule& m,const McBitfield& bf);
    void addMolecule(const Molecule& m);    

    int getNumTimeSteps() const { return 1;}
    void getCoordinate(int timeStep,int atomIx, McVec3f& v) const {assert(timeStep==0);v =thePositions[atomIx];}
    void setCoordinate(int timeStep,int atomIx, const McVec3f& v) {assert(timeStep==0);thePositions[atomIx]=v;}
private: 

    /// Reference to molecule topology
    McHandle<MolTopology> T;
    /** This flag indicates if T can be changed individually or if it
        is shared with other molecules and trajectories */
    bool ownTopologyFlag;

    /// The position matrix (nAtoms x 3)
    McDArray<McVec3f> thePositions;
    /// The bounding box
    float theBBox[6];
    
    McHandle<MolObservables> obs;










///###-{

/// ---------- legacy support, do not use any longer !!!


public:

    float *bbox();
    void bbox(float bbox[6], McBitfield & useAtoms);
    McDArray<McVec3f >& positions() { return thePositions; }
    const McDArray<McVec3f >& positions() const { return thePositions; }
    void untouch();

    /** Removes coordinates whose index is set in bitifield
        This method needs to be called after removing atoms with one of the methods in MolTopology. */
    void removeCoordinates(
        const McBitfield& bf);
    /** Removes coordinates for all atoms whose groupref index is -2 (i.e. deleted) in the translator. 
        This method needs to be called after removing atoms with one of the methods in MolTopology. */
    void removeCoordinates(
        const GroupRefTranslator& trans);
    /** Copies coordinates for all atoms whose groupref index is >=0 (i.e. added) in the translator. 
        This method needs to be called after copying atoms with one of the methods in MolTopology. */
    void copyCoordinates(
        const Molecule& sourceTop,
        const GroupRefTranslator& trans);

    /* method for debugging purposes
       writes molecule data to file fname */
#ifdef _DEBUG
    void printfMolecule(const char* fname);
#endif
///###-}
};

/***********************************************************
                    Topology
***********************************************************/    

MolTopology * Molecule::getTopology()
{
    return T;
}

const MolTopology * Molecule::getTopology() const
{
    return T;
}

/***********************************************************
                    Observables
***********************************************************/    

MolObservables* Molecule::getObservables() 
{
    return obs;
}

const MolObservables* Molecule::getObservables() const
{
    return obs;
}

/***********************************************************
                     Coordinates 
***********************************************************/

/***********************************************************
         Access 
*/

int Molecule::getNumCoordinates() const
{
    return thePositions.size();
}

void Molecule::resizeCoordinates(int size) {
    thePositions.resize(size);
}

const McVec3f& Molecule::getCoordinate(int atomIx) const
{
    return thePositions[atomIx];
}

const McDArray<McVec3f>& Molecule::getCoordinates() const
{
    return thePositions;
}

void Molecule::setCoordinate(int atomIx,const McVec3f& co) 
{
    thePositions[atomIx]=co;
}

void Molecule::setCoordinates(int num,const McVec3f* mem)
{
    if (num != getNumCoordinates())
        resizeCoordinates(num);
    memcpy(thePositions.dataPtr(),mem,num*sizeof(McVec3f));
}

void Molecule::setCoordinates(int startIx,int length, const McVec3f* mem)
{
    assert(startIx>=0 && startIx+length<thePositions.size());
    memcpy(thePositions.dataPtr()+startIx,mem,length*sizeof(McVec3f));
}

void Molecule::setCoordinates(int startIx,int length, const float* mem)
{
    assert(startIx>=0 && startIx+length<thePositions.size());
    memcpy(thePositions.dataPtr()+startIx,mem,3*length*sizeof(float));
}


#endif


/// @}
