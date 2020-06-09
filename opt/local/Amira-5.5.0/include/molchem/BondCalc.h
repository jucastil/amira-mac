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
#ifndef MOLEDITTOOLS_BONDCALC_H
#define MOLEDITTOOLS_BONDCALC_H

#include "MolChemWinDLLApi.h"

class MolObject;
class McBitfield;

namespace molchem {
    class Logger;
};

class MOLCHEM_API BondCalc  {
   
public:

    /**  ----- connection ------ 
    the following methods will change the
    connectivity of the atoms of the molecule, each method uses
    a bitfield sel to determine which atoms to handle */

    /** add bonds between selected atoms which are not away further
      than the cutoff dist */
    static bool autoConnectSelection(
        MolObject* mol,
        const McBitfield& sel,
        float cutOffDist);

    /// add bonds between all selected atoms 
    static bool allConnectSelection(
        MolObject* mol,
        const McBitfield& sel);

    /// removes all bonds between selected atoms
    static bool removeBondsInSelection(
        MolObject* mol,
        const McBitfield& sel);

    /// removes all bonds between seleted atoms which violate cutoff distance
    static bool removeUnfitBondsInSelection(
        MolObject* mol,
        const McBitfield& sel,
        float cutOffDist);

    /// removes all bonds between selected and unselcted atoms
    static bool removeExternalBondsInSelection(
        MolObject* mol,
        const McBitfield& sel);

    /// add bonds between selected atoms using standard residue database
    static bool standardConnectSelection(
        MolObject* mol,
        const McBitfield& sel);

    /// add bonds between selected atoms using bond length table
    static bool bondLengthConnectSelection(
        MolObject* mol,
        const McBitfield& sel);
    
    /** does some chemical checks */
    static bool fixBonds(MolObject* mol,
        const McBitfield& sel);

    static molchem::Logger* logger;
};

#endif

/// @}
