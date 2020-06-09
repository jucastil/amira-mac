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
#ifndef HX_MOL_TRAJECTORY_BUNDLE_H
#define HX_MOL_TRAJECTORY_BUNDLE_H

#include <hxcore/HxData.h>

#include <molecule/MolTrajectory.h>

#include <hxmolecule/HxMoleculeWinDLLApi.h>
#include <hxmolecule/ComputeListenerHandler.h>

/** Amira wrapper for the @c MolTrajectorBundle class. */

class HXMOLECULE_API HxMolTrajectoryBundle : public HxData {
    HX_HEADER(HxMolTrajectoryBundle);

public:
    /// Handler that allows registering compute listeners
    ComputeListenerHandler computeListenerHandler;    
    
    /// Constructor.
    HxMolTrajectoryBundle();

    /// Set new bundle of trajectories.
    void setTrajectories(const McDArray<McHandle<MolTrajectory> > & trajs)
    { trajectories = trajs; }

    /// Return number of trajectories in bundle.
    int  getNumTrajectories() { return trajectories.size(); }
    /// Return number of trajectories in bundle.
    int  getNumTrajectories() const { return trajectories.size(); }

    /// Return reference to trajectories. 
    const McDArray<McHandle<MolTrajectory> > & getTrajectories() const
    { return trajectories; }
    /// Return reference to a single trajectory.
    McHandle<MolTrajectory> & getTrajectory(int ix) 
    { return trajectories[ix]; }
    /// Add trajectories to the bundle - usually called by reader.
    void addTrajectory(MolTrajectory * T);

    // Overloaded function - parse tcl commands.
    int parse(Tcl_Interp* t, int argc,char **argv);
    ///   Virtual function compute - called if the object has been touched and fired.
    virtual void compute();

    /** Loads data per trajectory (to be stored in data entries of topologies) from file.
        Data in file must be formatted as one entry per line (file must have the same number
        of lines as the number of trajectories in bundle). Individual entries must be white space delimited.
        \par[in] filename file from which data is imported
        \par[in] dataname will be the name of the created data entry in each moltrajectory
        \par[in] datatype defines the type as which the data is interpreted (must be "string", "float" or "int")
        \throws molchem::Exception
    */
    void readDataFromFile(const char* filename, const char* dataname, const char* datatype);

    /* Saves data to file. Data will be formatted as one data per line. Individual entries of one data element
       will be white space delimited.
        \par[out] filename filename to which data will be exported
        \par[out] dataname name of data that will be exported. An empty line will be written for each trajectory
                           that does not contain data of this name. 
        \throws molchem::Exception
    */
    void writeDataToFile(const char* filename, const char* dataname);
    /// Duplicates the current HxMolTrajectory object
    virtual HxData *duplicate() const;

    /// Returns index of trajectory with given name. -1 if not found
    int getTrajectoryIx(const char* name) const;
    /** Computes several statistical measure between two MolTopology::Data entries of type float. Returns success. */
    bool computeDataStatistics(const char* data1,const char* data2,float& correlation, float& covariance, float& mean1,float& mean2, float& variance1, float& variance2) const;
    /** Computes several statistical measure for one MolTopology::MolData entries of type float. Returns success. */
    bool computeDataStatistics(const char* data1,float& mean1,float& variance1) const;
    MolTrajectory* getTrajectoryByName(const char* name) const;
protected:
    /// Trajectories contained in bundle. 
    McDArray<McHandle<MolTrajectory> > trajectories;

    /// Prints some information in the work area.
    void info();
};

#endif

/// @}
