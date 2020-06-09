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
#ifndef LEVELDEPENDANCE_H
#define LEVELDEPENDANCE_H

#include "MoleculeWinDLLApi.h"

#include <mclib/McDArray.h>
#include "MtGroupRef.h"
//#include "MolTopology.h"

class MolTopology;

/** class MtLevelDependance contains information about the transitive form
    of the relation "level x does contain groups of level y" (level x depends on y)
   the relation must be irefelxive and the respective graph acyclic
**/
class MOLECULE_API MtLevelDependance {

    // outer list over levels, inner list contains
    // all sucessors and predecessors of that level 
    McDArray<McDArray<int> > successors;
    McDArray<McDArray<int> > predecessors;
    MolTopology* T;

public:
    MtLevelDependance(MolTopology* molTop);

    /** when the level structure of T has changed 
        the dependance can be recalculated with this function **/
    void update();

    /** returns list of level indices that suffices the following demands:
        -list will begin with level @c startLevel
        -list will contain all levels that depend on @c startLevel
        -if ix2>ix1 in list then there is no path from lev(ix1) to lev(ix2)
        (i.e. each lev does only depend on levels left of it in the list) **/
    McDArray<int> getHierachyList(int startLevel = MtGroupRef::atomLevel) const;

    /** returns list of all direct successors of @c level i.e. all levels whose
        groups are contained by groups of @c level, note: this
        is not identical with dependance (becaue dependance is the transitive
        hull of the successor relation)**/
    McDArray<int> getSuccessors(int level) const;

    /** returns list of all direct predecessors of @c level i.e. all levels which
        contain groups of @c level **/
    McDArray<int> getPredecessors(int level) const;

#ifdef _DEBUG
    // outputs information for debugging purposes
    void print() const;
#endif

protected:
   
    // updates the list entry successors[levelIx]
    void findSuccessors(int levelIx);

};

#endif


/// @}
