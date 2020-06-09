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
#ifndef MOLCHEM_REACTION_H
#define MOLCHEM_REACTION_H

#include "MolChemWinDLLApi.h"

class McBitfield;
class McString;

template <class T> class McDArray;

namespace molchem {
    class ReactionInternal;
    class Molecule;
    class Logger;

    /* \brief Represents a molecular reaction. 
    
        Rreaction represents inter or intramolecular reaction
        and applies them to instances of molchem::Molecule.
    */

    class MOLCHEM_API Reaction {
    public:    
        ///
        Reaction();
        ///
        virtual ~Reaction();
        /* Initializes the reaction with a MSMIRKS string.
        
            \param[in] smirks The reaction specification.
            \return Success.
        */
        bool initMSmirks(const char* smirks);
        /** Applies reaction to next match. 
        
            \param[in] mol Molecule to which reaction will be applied
            \param[out] found Returns whether any match was found 
            \return Success.
        */
        bool apply(Molecule* mol,bool* found=0);
        /** Applies reaction to a certain matching

            \param[in] Molecule to which reaction will be applied.
            \param[in] Matching that specifies where to apply.
            \return Success.
        */
        bool apply(Molecule* mol,const McDArray<int>& match);
        /// Adds readable version of reaction content to string. For debugging.
        void print(McString& str) const;
        /** Returns all matches of reactant side in given molecule. 
        
            \param[in] mol Molecule that will be matched.
            \param[out] matches Found matchings
        */
        void getMatches(const Molecule* mol,McDArray<McDArray<int> > & matches) const;
        /// Transforms a pattern matching into a map of binding indices. Returns success.
        bool match2BindingMap(const McDArray<int>& match,McDArray<int>& map) const;
    private:
        // private implementation
        ReactionInternal* pimpl;
    };
};

#endif

/// @}
