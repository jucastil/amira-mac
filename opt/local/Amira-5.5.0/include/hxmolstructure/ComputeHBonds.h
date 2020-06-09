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

/// @addtogroup hxmolstructure hxmolstructure
/// @{
#ifndef COMPUTEHBONDS_H
#define COMPUTEHBONDS_H

#include <mclib/McDMatrix.h>

#include <hxcore/HxCompModule.h>

#include <molecule/AuxGrid.h>
#include <hxmolecule/MolFilter.h>

#include "HxMolStructureWinDLLApi.h"

class MtBond;
class Molecule;
class McVec3f;
class McBitfield;
class MolTopology;
class MtGroupRef;
class ComputeSecStructures;

/*
 * Using various different also heuristic methods for hydrogen bond
 * detection, this class returns a molecule filled with a new level,
 * the hydrogen bond level, and possibly found hydrogen
 * bonds. Distance, angle, atomic numbers and others informations may
 * decide wheater or not between two atoms a hydrogen bond exist.
 * Chemistry only allowing hydrogen bonds between Oxigene and
 * Nitrogene closer then 3.5 Angstrom to eachother. Hydrogen Bonds
 * calculation represents the base for further algorithms such as the
 * secondary structure detection. Further informations:
 * ->ComputeSecondaryStructures.h
 */

class HXMOLSTRUCTURE_API ComputeHBonds  {

    friend class ComputeSecStructures;

public:

    ///
    ComputeHBonds();

    
    ~ComputeHBonds();

    
    McDArray<MtBond *> computeHBonds(HxMolecule * molecule, MolFilter * molF, 
                       float minAngle, int flag, bool bbe, int maxNumber, bool forbidInnerRes=true);

    /// inserts into molecule new computed hydrogene bonds and the hydrogene binds level
    // molFilter - which atoms/residues are selected
    // minAngle - minimum angle allowed for the hbond (mostly the angle between C-O-C and C-N-C
    // flag - which residue groups should be excluded (1 H20 and HYD excluded; 2 HET excluded; 3 HET, H2o and HYD excluded, else none)
    // bbe - should only the backbone enriched atoms be considered
    // maxNumbe - how many hbonds are allowed at most for a single atom (usually 1)
    // forbidInnerRes - should hbonds between 2 atoms of a single residue be forbidden (mostly yes)
    void GenerateAndInsertHBonds(HxMolecule * molecule, MolFilter * molFilter, 
                                  float minAngle, int flag, bool bbe, int maxNumber, bool forbidInnerRes);

private:

    bool ForbidInnerResidual;
    ///
    HxMolecule * mA;        
    
    /// coords
    McDArray<McVec3f>  coords;    
    
    ///
    McBitfield isDonOrAccep;

    ///
    McDArray<McBitfield > forbiddenAtoms;    

    ///
    McBitfield mBit;    

    ///
    McDArray<McVec3i> location;

    ///
    McDArray<McDArray<McVec3f > > hBondPairs;

    ///
    int nResidues;

    ///
    McDArray<McBitfield > hasHBondWith;

    ///
    McDArray<McDArray<McVec2i > > connectedResidues;    

    ///
    int residueLevel;

    ///
    int strandLevel;    

    ///
    int secondaryStrucLevel;

    ///
    McDArray<int > strandOfAtom;

    ///
    McDMatrix<double > connectivity;

    ///
    AuxGrid<int> gridField;

    ///
    McDArray<McDArray<int > > residueHBondNeighbors;    

    ///
    int nAtoms;

    ///
    MtGroupRef gr;        

    ///
    McDArray<int> residueOfAtoms;
       
    /// 
    void computeForbiddegetNumCoordinates();        
    
    ///
    void getForbiddenAtoms(McBitfield &visited, McDArray<int> &visitedArray,
                           McBitfield &forbidden, McDArray<int> &neighs, 
                           McDArray<McDArray< int > > &bondsNeighbors, 
                           int curDe);
};

#endif

/// @}
