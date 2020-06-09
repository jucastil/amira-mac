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
#ifndef ATOMTYPER_H
#define ATOMTYPER_H

#include "MolChemWinDLLApi.h"

#include "AtomTyper.h"

class McBitfield;
namespace molchem {
    class Molecule;
    class Logger;
}

namespace mmff94 {
    /** \brief AtomTyper for the mmff94 force field. 

        This atom typer computers the 99 atom types as defined in
        the MMFF94_AtomParameterRows. 
        It uses the MMFF94_AtomSubTyper and then maps the subtypes to the 99 main types. 
    */
    class MOLCHEM_API MMFF94_AtomTyper : public molchem::AtomTyper {
    public:
        MMFF94_AtomTyper();
        virtual ~MMFF94_AtomTyper() {}
        /** Computes atoms types

            \param[in] mol Molecule whose atoms will be processed. Must contain
                correct number of implicit hydrogens, formal charges, kekule structure
            \param[in] mask Filter bitfield defining which atoms will be processed.
                       All atoms, if null.
            \param[in|out] type Returns references to the atom types. If a filter is used
                       type may contain already computed atomtypes. The compute methods will
                       then use these atom types to derive the additional atomtypes.
                       It must be either of size 0 or of size getNumAtoms() of the molcule.
            \return Number of atoms for which no atom type could be assigned 
            \exception molchem::Exception 
        */
        int computeAtomTypes(molchem::Molecule* mol,McDArray<molchem::AtomType*>& type,const McBitfield* mask=0) const;
        const molchem::AtomType* getType(int ix) const;
        int getNumTypes() const;
        static molchem::Logger* logger;
    };

    /** \brief AtomTyper for the MMFF94 force field. 
    
        This atom typer computes the ~200 sub atom types
        as defined in the MMFF94_AtomTypeRows. See file parameters/MMFF94_AtomType.txt. 
    */
    class MOLCHEM_API MMFF94_AtomSubTyper : public molchem::AtomTyper {
    public:
        MMFF94_AtomSubTyper();
        virtual ~MMFF94_AtomSubTyper() {}
        /** Computes atoms types
            
            \param[in] mol Molecule whose atoms will be processed. Must contain
                correct number of implicit hydrogens, formal charges
            \param[in] mask Filter bitfield defining which atoms will be processed.
                       All atoms, if null.
            \param[in|out] type Returns references to the atom types. If a filter is used
                       type may contain already computed atomtypes. The compute methods will
                       then use these atom types to derive the additional atomtypes.
                       It must be either of size 0 or of size getNumAtoms() of the molcule.
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
