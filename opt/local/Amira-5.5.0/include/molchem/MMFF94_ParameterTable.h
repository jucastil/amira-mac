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
#ifndef MMFF94_PARAMETERTABLE_H
#define MMFF94_PARAMETERTABLE_H

template<class T> class McDArray;
template <class Key, class Value> class McHashTable;
class McString;
class McVec2i;
class McVec3i;
class McVec4i;

#include "MolChemWinDLLApi.h"
#include "MMFF94_ParameterRows.h"

#pragma warning( disable : 4251)

namespace mmff94 {

    /* \brief Container for MMFF94 Parameters

    The MMFF94 Parameters are stored in static arrays. The data is stored in the file MMFF94_ParameterRows.cpp
    which is generated automatically from a tcl script.

    */
    class MOLCHEM_API MMFF94_ParameterTable {
    public:

        /* Constructor will read files containing parameter tables into static arrays,
        if this has not already been done earlier.
        Error should be always checked after object was constructed. */
        /* set output stream and verbosity bits (see enum MMFF94_LOG_VERBOSITY) */
        MMFF94_ParameterTable();

        /* return mmff atom type index (1-99) for a specific type index 
        NULL if none found */
        const MMFF94_AtomTypeRow* getAtomTypeRow(int amiraType) const;

        /* return atom parameters for specific mmff atom type index
        NULL if none found */
        const MMFF94_AtomParameterRow* getAtomParameterRow(int aType) const;

        const MMFF94_BondChargeIncrementRow* getBondChargeIncrementRow(
            int aType1,int aType2,int bType) const;

        const MMFF94_BondStretchingParameterRow* getBondStretchingParameterRow(
            int aType1,int aType2,int bType) const;
        int getBondStretchingParameterRowIx(
            int aType1,int aType2,int bType) const;
        const MMFF94_BondStretchingParameterRow* getBondStretchingParameterRow(
            int ix) const;

        const MMFF94_DefaultBondStretchingParameterRow* getDefaultBondStretchingParameterRow(
            int aType1,int aType2) const;
        int getDefaultBondStretchingParameterRowIx(
            int aType1,int aType2) const;
        const MMFF94_DefaultBondStretchingParameterRow* getDefaultBondStretchingParameterRow(
            int ix) const;

        const MMFF94_AngleBendingParameterRow* getAngleBendingParameterRow(
            int aType1,int aType2,int aType3,int bType) const;
        int getAngleBendingParameterRowIx(
            int aType1,int aType2,int aType3,int bType) const;
        const MMFF94_AngleBendingParameterRow* getAngleBendingParameterRow(
            int ix) const;

        const MMFF94_TorsionParameterRow* getTorsionParameterRow(
            int aType1,int aType2,int aType3, int aType4, int bType) const;
        int getTorsionParameterRowIx(
            int aType1,int aType2,int aType3, int aType4, int bType) const;
        const MMFF94_TorsionParameterRow* getTorsionParameterRow(
            int ix) const;

        const MMFF94_StretchBendParameterRow* getStretchBendParameterRow(
            int aType1,int aType2,int aType3,int bType) const;
        int getStretchBendParameterRowIx(
            int aType1,int aType2,int aType3,int bType) const;
        const MMFF94_StretchBendParameterRow* getStretchBendParameterRow(
            int ix) const;

        const MMFF94_DefaultStretchBendParameterRow* getDefaultStretchBendParameterRow(
            int aType1,int aType2,int aType3) const;
        int getDefaultStretchBendParameterRowIx(
            int aType1,int aType2,int aType3) const;
        const MMFF94_DefaultStretchBendParameterRow* getDefaultStretchBendParameterRow(
            int ix) const;
        bool getStretchBendParameters(int aType1,int aType2, int aType3,int bType,double& kij,double& ijk);

        const MMFF94_OutOfPlaneBendingParameterRow* getOutOfPlaneBendingParameterRow(
            int aType1,int aType2,int aType3, int aType4) const;
        int getOutOfPlaneBendingParameterRowIx(
            int aType1,int aType2,int aType3, int aType4) const;
        const MMFF94_OutOfPlaneBendingParameterRow* getOutOfPlaneBendingParameterRow(
            int ix) const;

        const MMFF94_AtomTypeTranslationRow* getAtomTypeTranslationRow(int aType) const;
        int getNumAtomTypeTranslationRow() { return dataAtomTypeTranslationMax;}
    protected:

        void convertAngleStageTypes(int defStage,int& aType1,int& aType2,int& aType3) const;
        void convertTorsionStageTypes(int defStage,int& aType1,int& aType2,int& aType3,int& aType4) const;
        void convertOOPStageTypes(int defStage,int& aType1,int& aType2,int& aType3,int& aType4) const;
        int getPeriodicTableRow(int aType) const;

        // data tables
        static MMFF94_AtomTypeRow dataAtomType[];
        static MMFF94_AtomParameterRow dataAtomParameter[];
        static MMFF94_BondChargeIncrementRow dataBondChargeIncrement[];
        static MMFF94_BondStretchingParameterRow dataBondStretchingParameter[];
        static MMFF94_DefaultBondStretchingParameterRow dataDefaultBondStretchingParameter[];
        static MMFF94_AngleBendingParameterRow dataAngleBendingParameter[];
        static MMFF94_OutOfPlaneBendingParameterRow dataOutOfPlaneBendingParameter[];
        static MMFF94_StretchBendParameterRow dataStretchBendParameter[];
        static MMFF94_DefaultStretchBendParameterRow dataDefaultStretchBendParameter[];
        static MMFF94_TorsionParameterRow dataTorsionParameter[];
        static MMFF94_AtomTypeTranslationRow dataAtomTypeTranslation[];

        static int dataAtomTypeMax;
        static int dataAtomParameterMax;
        static int dataBondChargeIncrementMax;
        static int dataBondStretchingParameterMax;
        static int dataDefaultBondStretchingParameterMax;
        static int dataAngleBendingParameterMax;
        static int dataOutOfPlaneBendingParameterMax;
        static int dataStretchBendParameterMax;
        static int dataDefaultStretchBendParameterMax;
        static int dataTorsionParameterMax;
        static int dataAtomTypeTranslationMax;

        static bool constructorCalledBefore;

        // data lookup tables
        static McHashTable<McVec3i,int> hashBondChargeIncrement;
        static McHashTable<McVec3i,int> hashBondStretchingParameter;
        static McHashTable<McVec2i,int> hashDefaultBondStretchingParameter;
        static McHashTable<McVec4i,int> hashAngleBendingParameter;
        static McHashTable<McVec4i,int> hashOutOfPlaneBendingParameter;
        static McHashTable<McVec4i,int> hashStretchBendParameter;
        static McHashTable<McVec4i,int> hashTorsionParameter;

    };
}
#endif




/// @}
