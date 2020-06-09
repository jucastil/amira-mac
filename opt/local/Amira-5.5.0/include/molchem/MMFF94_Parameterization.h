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
#ifndef MMFF94_PARAMETERIZATION_H
#define MMFF94_PARAMETERIZATION_H

#include "MolChemWinDLLApi.h"

namespace molchem {
    class Molecule;
};

namespace mmff94 {
    class MMFF94_ParameterTable;
    class MMFF94_Molecule;
    class MMFF94_ParameterizationPimpl;

    /** \brief MMFF94 Parameterizer 
    
        The parameterizer takes a molchem::Molecule as input and outputs a 
        MMFF94_Molecule with atom typing and parameters.

    */

    class MOLCHEM_API MMFF94_Parameterization {
    public:
        ///
        MMFF94_Parameterization();
        ///
        ~MMFF94_Parameterization();
        /** Sets the molecule to be processed. 
            The Molecule must have correct bond orders, formal charges and
            explicit hydrogens assigned.
        */
        void setMolecule(molchem::Molecule* m);
        /** Sets which components will be parameterized.
        One bit for each component. See enum Components. */
        void setWhichComponents(int components=C_ALL);
        /** Determines which parameter version is used.
        */
        void setVersion(int version = V_STANDARD);

        /**  Does paramterization and outputs it into the given MMFF94_Molecule
            \exception molchem::Exception
        */
        bool parameterize(MMFF94_Molecule& m,bool tolerant=false);

        enum Version {
            V_STANDARD        = 0, // default MMFF94 parameterization(for md)
            V_S               = 1 // MMFF94s version (for minimization)
        };

        /// Bits representing components for parameterization
        enum Components {
            C_COULOMB         = 0x02,
            C_VDW             = 0x04,
            C_BONDSTRETCHING  = 0x08,
            C_ANGLEBENDING    = 0x10,
            C_STRETCHBEND     = 0x20,
            C_OOPBENDING      = 0x40,
            C_TORSION         = 0x80,
            C_ALL             = 0xff
        };
    private:
        MMFF94_ParameterizationPimpl* pimpl;
    };
}
#endif





/// @}
