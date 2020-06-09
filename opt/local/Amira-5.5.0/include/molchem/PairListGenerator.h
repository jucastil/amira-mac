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
#ifndef MOLCHEM_PAIRLISTGENERATOR_H
#define MOLCHEM_PAIRLISTGENERATOR_H

#include "MolChemWinDLLApi.h"

#include <mclib/McBitfield.h>
#include <mclib/McHandle.h>
#include <mclib/McDArray.h>

class McVec2i;

namespace molchem {
    
    class Molecule;

    /** \brief Generator for molecular nonbonded pair lists.

        Will generate a list of all pairs that are closer than a certain cutoff.
    */

    class MOLCHEM_API PairListGenerator {
    protected:
        /** Optional restriction of pairs. This function may be overridden to exclude 
            pairs which are bonded etc. */ 
        virtual bool isPair(int ix1,int ix2) const { return true;}
    public:
        virtual ~PairListGenerator() {}
        virtual void getPairList(double cutoff,const double * const co,int num,McDArray<McVec2i>& pairList) const;
        virtual void getPairList(int num,McDArray<McVec2i>& pairList) const;
        // To use group based cutoff, use these arrays. This is needed to not seperate neutral charge groups through cutoff.
        McDArray<int> switchingAtom; // index of switching atom of each group
        McDArray<int> group; // index of group that each atom belongs to. -1 for none
    };
    
    /** \brief Generator for molecular nonbonded pair lists which allows several restrictions.
    */
    
    class MOLCHEM_API PairListGeneratorRestricted : public PairListGenerator {
    protected:
        virtual bool isPair(int ix1,int ix2) const;
    public:
        PairListGeneratorRestricted() : PairListGenerator() {mol=0;noBonds=false;noAngles=false;}
        virtual ~PairListGeneratorRestricted() {}        
        // Will pairs of atoms that are part of a bond angle not be included ?
        bool noAngles;
        // Will pairs of atoms that are part of a bond not be included ?
        bool noBonds;
        // Molecule, must be set, if noAngles or noBonds is true
        Molecule* mol;
        // Optional mask. Only pairs for which at least one atom is set will be used. Not used if empty.
        McBitfield atomOneMask;
        // Optional mask. Only pairs for which both atoms are set will be used. Not used if empty.
        McBitfield atomBothMask;
    };
}

#endif


/// @}
