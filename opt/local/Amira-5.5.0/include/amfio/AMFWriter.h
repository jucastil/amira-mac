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

/// @addtogroup amfio amfio
/// @{
#ifndef AMFIO_AMFWRITER_H
#define AMFIO_AMFWRITER_H

#include "AMFIOWinDLLApi.h"

template <class T> class McDArray;
class MolTrajectory;
class MolTrajectoryMem;
class Molecule;
class MolTopology;
class McProgressInterface;
class AMFWriterInternal;
class RegularGrid3f1;

/** \brief Writer for AMF files
   
    AMFWriter wraps the functionality to write amf files.
    A filename must be supplied in the constructor and then
    all consecutive calls of save methods will write 
    data into this file */

class AMFIO_API AMFWriter {

public:

    /** Initilizes AMFWriter.
    	\exception AMFException
    	\param file Name of the file to be opened. 
    	\param p An optional interface to report progress events 
        \param compressionLevel can be an integer between 0 (no compression, fast) to 9(high compression,slow) 
    */
    AMFWriter(const char* file,McProgressInterface* p=0,int compressionLevel=7);
    
    /** \exception AMFException */
    ~AMFWriter();

    /** Saves a set of Trajectories as a TrajectoryBundle 
        \exception AMFException */
    void save(const McDArray<const MolTrajectory*>& M, const char* name);
    /** Saves a set of Trajectories as a TrajectoryBundle 
        \exception AMFException */
    void save(const McDArray<const MolTrajectoryMem*>& M, const char* name);
    /** Saves a set of Trajectories as a TrajectoryBundle 
        \exception AMFException */
    void save(const McDArray<MolTrajectory*>& M, const char* name);
    /** Saves a set of Trajectories as a TrajectoryBundle 
        \exception AMFException */
    void save(const McDArray<MolTrajectoryMem*>& M, const char* name);

    /** Saves a Moltrajectory
        \exception AMFException */
    void save(const MolTrajectory* M, const char* name);

    /** Saves a set of Molecule as a MoleculeBundle
        \exception AMFException */
    void save(const McDArray<const Molecule*>& M, const char* name);

    /** Saves a Molecule
        \exception AMFException */
    void save(const Molecule* M, const char* name);

    /** Saves a Molecule
        \exception AMFException */
    void save(const RegularGrid3f1* g, const char* name);

private:    
    AMFWriterInternal* aw;
};

	
#endif


/// @}
