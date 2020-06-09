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
#ifndef MMFF94_PARAMETERROWS_H
#define MMFF94_PARAMETERROWS_H

#include "MolChemWinDLLApi.h"

namespace mmff94 {
    /** Container for atom type information of one detailed type */
    struct MMFF94_AtomTypeRow {
        /// detailed mmff type index
        unsigned char symbolIx;        
        /// mmff94 symbol
        char* symbol;  
        /// index of amira type index that is bonded to this type
        unsigned char H_amtype;
        /// mmff simple atom type index
        unsigned char aType;
        /// formal charge
        float q0;
        ///
        char* text;
    };
    /** Container for atom type parameter of one simple type */
    struct MOLCHEM_API MMFF94_AtomParameterRow {
        // atom type index
        unsigned char aType; 
        char * symbol;
        unsigned char defType1; 
        unsigned char defType2; 
        unsigned char defType3; 
        unsigned char defType4; 
        unsigned char defType5; 
        unsigned char aspec;
        unsigned char crd;
        unsigned char val;
        unsigned char pilp;
        unsigned char mltb;
        unsigned char arom;
        unsigned char lin;
        unsigned char sbmb;
        float alpha;
        float N;
        float A;
        float G;
        char DA;
        float pcbi; // fractional charge adjustment
        float theta; // partial bond charge parameter
    };
    /** Container for bond charge increment parameters */
    struct MOLCHEM_API MMFF94_BondChargeIncrementRow {
        unsigned char bType; 
        // atom type index
        unsigned char aType1;
        // atom type index
        unsigned char aType2;
        float bci;
    };
    /** Container for bond stretching parameters */
    struct MOLCHEM_API MMFF94_BondStretchingParameterRow {
        unsigned char bType;
        unsigned char aType1;
        unsigned char aType2;
        float kb;
        float r0;
    };
    /** Container for default bond stretching parameters */
    struct MOLCHEM_API MMFF94_DefaultBondStretchingParameterRow {
        unsigned char aSpecies1;
        unsigned char aSpecies2;
        float r0;
        float kb;
    };
    /** Container for stretch bend parameters */
    struct MOLCHEM_API MMFF94_StretchBendParameterRow {
        unsigned char bType;
        unsigned char aType1;
        unsigned char aType2;
        unsigned char aType3;
        float kba_ijk;
        float kba_kji;
    };
    /** Container for default stretch bend parameters */
    struct MOLCHEM_API MMFF94_DefaultStretchBendParameterRow {
        unsigned char aRow1;
        unsigned char aRow2;
        unsigned char aRow3;
        float kba_ijk;
        float kba_kji;
    };
    /** Container for angle bending parameters */
    struct MOLCHEM_API MMFF94_AngleBendingParameterRow {
        unsigned char bType;
        unsigned char aType1;
        unsigned char aType2;
        unsigned char aType3;
        float ka;
        float theta0;
    };
    /** Container for out of plane bending parameters */
    struct MOLCHEM_API MMFF94_OutOfPlaneBendingParameterRow {
        unsigned char aType1;
        unsigned char aType2;
        unsigned char aType3;
        unsigned char aType4;
        float koop;
        float koop_s;//MMFF94s version
    };
    /** Container for torsion parameters */
    struct MOLCHEM_API MMFF94_TorsionParameterRow {
        unsigned char bType;
        unsigned char aType1;
        unsigned char aType2;
        unsigned char aType3;
        unsigned char aType4;
        float V1;
        float V2;
        float V3;
        float V1_s;//MMFF94s version
        float V2_s;//MMFF94s version
        float V3_s;//MMFF94s version
    };
    /* This is a container for a conversion from a detailed mmff type to other atom types */
    struct MMFF94_AtomTypeTranslationRow {
        /// detailed mmff atom type index
        unsigned char symbolIx;        
        /// mmff94 symbol
        char* symbol;  
        unsigned char type;
        char * charmmType;
        char* mol2Type;
        char* description;
    };
}

#endif





/// @}
