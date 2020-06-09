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

/// @addtogroup zmf zmf
/// @{
#ifndef MOL_TRAJECTORY_ZIB_H 
#define MOL_TRAJECTORY_ZIB_H 

#include "ZMFWinDLLApi.h"
#include "molecule/MolObservable.h"
#include "molecule/MolTrajectory.h"
#include "molecule/MtSelfSubstitutingAttribute.h"
#include "StreamData.h"
#include "StreamData.h"

class ZIBMolFileWriter;
class McProgressInterface;
class MolObservables;

class ZMF_API ZMFGroupAttributeProvider : public MtGroupAttributeProvider
{
    ///
    McHandle<StreamData> Dmolecule, Dtypbase;

public:
    ///
    ZMFGroupAttributeProvider(StreamData * mol, StreamData * typbase) 
        : Dmolecule(mol), Dtypbase(typbase) {}; 
    
    ///
    virtual MtGroupAttribute * getGroupAttribute(const char * name, 
                                                 const char * iName, 
                                                 const char * levelName,
                                                 MtIntegerAttribute * typeId);
};

/** Molecule trajectory = topology + time steps.
    All the information in a trajectory file. */
class ZMF_API MolTrajectoryZIB : public MolTrajectory
{
public:
    /// Data structure on disk
    McHandle<StreamData> Dinput, Dtimesteps, Dmolbase, 
        Dtypbase, Dmolecule, Ddihedral_timesteps;
    
private:
    ///
    McHandle<ZMFGroupAttributeProvider> attProv;

    /// Load positions from data file
    bool loadPositions(Molecule* M, StreamData * D);

    /// Load topology from data file
    bool loadTopo(MolTopology* T, StreamData * D);

    // typedef map<int, MtGroupRef> MapType;
    struct IdToRefRecord {
        int id;
        MtGroupRef ref;
        
        friend bool operator <(const IdToRefRecord& rec1,
                               const IdToRefRecord& rec2)
        {
            return rec1.id < rec2.id;
        }
    };
    
    ///
    McDArray<IdToRefRecord> idToRefTable;
    
    ///
    MtGroupRef idToRef(int id);
    ///
    void defineID(int id, MtGroupRef ref);
        
    ///
    bool readAtomTypes(MolTopology * T, StreamData * atom_types, 
                       int & acOffset);

public:
    ///
    McHandle<StreamData> getMolecule();
    /// Load cartesian trajectory observables from file.
    void loadCartesianTrajectoryObservables(
                      McDArray<McHandle<MolObservable> > & observables);
    /// Load cartesian trajectory observables from file.
    void loadDihedralTrajectoryObservables(
                      McDArray<McHandle<MolObservable> > & observables,
                      const McDArray<McString> & observableNames);
    
private:
    ///
    bool readAtoms(MolTopology * T, StreamData * DAtoms,
                   StreamData * atom_types);
    ///
    bool readBonds(MolTopology * T, StreamData * DBonds);
    ///
    bool readComponentsGrouping(MolTopology * T, StreamData * Dlevel, 
                                const char * groupingName);
    ///
    bool readFromToGrouping(MolTopology * T, StreamData * Dlevel, 
                            const char * groupingName);
    
    ///
    void loadObservables();

    ///
    void load();

    ///
    bool loaded;

    ///
    int formatVersion;

public:
    /// Create from data handle 
    MolTrajectoryZIB(StreamData * D_, StreamData * molecule=0,
                     StreamData * typbase = 0, StreamData * molbase = 0);

    /// Destructor
    ~MolTrajectoryZIB();

    /// Number of configurations
    int getNumTimeSteps() const;

    /// Get the number of boxes in which the angle range ist divided into
    int getQuantization();

#if 0
    // TODO-DANIEL: remove !!!
    /// Get the weights for the trajectory
    void getWeights(McDArray<float>& weight_up, McDArray<float>& weight_down);
#endif

    /// Get number of relevant dihedral angles
    int getNumDihedralIDs();
                        
    /// Get the IDs of relevant dihedral angles
    bool getDihedralIDs(McDArray<int> & dihedralIDs);

    /// Get dihedrals by index. Counted from 0.
    bool getDihedralTrajectoryStep(int ix, McDArray<signed char> & dihedrals, 
                                   float & weight_up, float & weight_down);

    /// Get dihedrals by index. Counted from 0.
    bool getDihedralTrajectoryStep(int ix, McDArray<int> & dihedrals, 
                                   float & weight_up, float & weight_down);

    /// Get configuration by index. Counted from 0.
    bool getTimeStep(int ix, Molecule * mol);

    ///
    MolTopology * getTopology();
    ///
    const MolTopology * getTopology() const;

    ///
    int getNumFields(int timestep=0) const;

    ///
    void getFieldNames(char** names) const;

private:
    ///
    McHandle<StreamData> getFieldHandle(int fieldId, int ixconf) const;

public:
    ///
    int getFieldDims(int fieldId, int ixconf, int *dims) const;
    /// 
    int getFieldData(int fieldId, int ixconf, float *data) const;
    ///
    int getFieldBbox(int fieldId, int ixconf, float * bb) const;

    ///
    static void readBundle(const char *filename, 
                           McDArray<McHandle<MolTrajectory> >& bundle);
    
    ///
    const char * getInfoText() { return info_text; }

    ///
    static McProgressInterface * theProgressInterface;

    struct TBTreeNode : public McHandable {
        int which;
        McDArray<McHandle<TBTreeNode> > childs;
    
        TBTreeNode() {
            which = -1;
        }
    
        static int compare(McHandle<TBTreeNode> const & t1, McHandle<TBTreeNode> const & t2)
        {
            if (t1->which<t2->which) return -1;
            if (t2->which<t1->which) return 1;
            return 0;
        }
    };

    ///
    static void buildTBTrees(const MolTopology * topo, 
                             McDArray<McHandle<TBTreeNode> > & tbTrees,
                             McDArray<int> & numTypes, 
                             McDArray<McDArray<const MtGroupAttribute*> > & dirAtts,
                             McDArray<McDArray<const MtGroupAttribute*> > & typAtts,
                             bool & mmffFlag);

    struct FieldRecord {
        McString name;
        const float*  bbox;
        const int*    dims;
        const float*  data;
    };

    /// method used for convention expected by molio/MolIOWizard
    static int writeZMFMolecule(Molecule * mol, const char * fileName);

    /// method used for convention expected by molio/MolIOWizard
    static int writeZMFMolTrajectory(MolTrajectory * traj, const char * fileName);


    ///
    static int saveMolecule(Molecule * , const char * mol_name, 
                            const char * filename,    
                            McDArray<FieldRecord> & fields);    

    
    /// Save coordinates only 
    static int saveTrajectory(MolTrajectory * , 
                              const char * filename);    

    
    ///
    static McHandle<SomeType> getTopologyObsDataType(MolTopology * topo, MolObservables * obs, const char * name);
    
    static bool getOfficialName(const char * levelName, 
                                const char * internalName,
                                const char * & officialName);

    static bool getInternalName(const char * levelName, 
                                const char * officialName,
                                const char * & internalName);
                         

    void readAttributes(MolTopology * T, const char * levelName, 
                        int levelIndex,
                        StreamData * Dgroups,
                        StreamData * Dtypbase);
       
private:        
    ///
    McString info_text;
};

#endif

/// @}
