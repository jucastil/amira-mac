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

/// @addtogroup molchem molchem
/// @{
#ifndef MOLEDITTOOLS_FRAGMENTDATABASE_H
#define MOLEDITTOOLS_FRAGMENTDATABASE_H

#include "MolChemWinDLLApi.h"
#include <mclib/McDArray.h>
#include <mclib/McHashTable.h>
#include <mclib/McString.h>
#include <molecule/MolTrajectory.h>

class MolTopology;
namespace molchem {
    class Logger;
}

/************************************************************************
 
 FragmentDataBase allow easy access to MolTopologies in the Amira Molecular 
 Fragment database.

************************************************************************/

class MOLCHEM_API FragmentDataBase {

public:

    FragmentDataBase();
    ~FragmentDataBase();

    /// return fragment topology of index @c ix
    const McHandle<MolTopology> getTopology(int ix) const;
    const McHandle<MolTrajectory> getTrajectory(int ix) const;
	void getTopologies(const McDArray<McString>& name, McDArray<McHandle<MolTopology> >& top) const;

    /// return fragment name of index @c ix
    const char* getName(int ix) const;

    /// return number of fragments in database
    int getSize() const;

    /** return index of fragment of name @c name.
        uses hashing to speed up search */
    int getIx(const char* name) const; 

    /** return indices of fragments whose name 
        matches the search pattern @c pattern.
        matchFunction has to be a user supplied
        function that returns 1 if name matches pattern
        and 0 otherwise. For an example @see mcWildMatch. */
    void getIx(const char* pattern,
        int(*matchFunction)(const char* name,const char* pattern),
        McDArray<int>& ix) const;

	/** adds molecules of file filename (which needs to be in amf format) to database.
	    Returns whether successful.*/
    bool add(const char* filename);

protected:

    void clear();

    static McHashTable<McString,int> name2Ix;
    static McDArray<McString> name;
    static McDArray<McHandle<MolTrajectory> > traj;
    static molchem::Logger* logger;

};

#endif

/// @}
