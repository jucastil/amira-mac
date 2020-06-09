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
#ifndef ATOMTYPER_CHARMM_H
#define ATOMTYPER_CHARMM_H

#include "MolChemWinDLLApi.h"

#include "AtomTyper.h"

class McBitfield;
namespace molchem {
    class Molecule;
    class Logger;
}

namespace molchem {
    /** \brief AtomTyper for CHARMM atom types
    
    It internally uses the MMFF04_AtomSubTyper and then maps the subtypes to the CHARMM types,
    using some additional rules to distinguish situation where one MMFF subtype
    matches several CHARMM types.
    
    */
    class MOLCHEM_API AtomTyper_CHARMM : public molchem::AtomTyper {
    public:
        AtomTyper_CHARMM();
        virtual ~AtomTyper_CHARMM() {}
        /** Computes atoms types

            \param[in] mol Molecule whose atoms will be processed. Must contain
                correct number of implicit hydrogens, formal charges
            \param[in] mask Filter bitfield defining which atoms will be processed.
                       All atoms, if null.
            \param[out] type Returns references to the atom types.
            \return Number of atoms for which no atom type could be assigned 
            \exception molchem::Exception 
        */
        int computeAtomTypes(molchem::Molecule* mol,McDArray<molchem::AtomType*>& type,const McBitfield* mask=0) const;
        const molchem::AtomType* getType(int ix) const;
        int getNumTypes() const;
        static molchem::Logger* logger;
    };
}

#endif


/// @}
