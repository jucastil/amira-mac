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
#ifndef COMPUTESECSTRUCTURES_H
#define COMPUTESECSTRUCTURES_H

#include <mclib/McList.h>

#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxCompModule.h>
#include <molecule/AuxGrid.h>
#include <mclib/McDMatrix.h>

#include "ComputeHBonds.h"

#include <molecule/AuxGrid.h>
#include "hxmolecule/MolFilter.h"
#include "hxmolecule/HxMolecule.h"

class Molecule;
class McVec3f;
class McBitfield;
class MolTopology;
class MtGroupRef;

/*
 * Using the Kabsch-Sander algorithm to detect secondary structures,
 * this class returns a new molecule filled with generated hydrogen
 * bonds and possibly found secondary structures, such as helices,
 * strands and turns.  Chains are not beeing detected. This module
 * registers itself in the selection browser of its connected
 * molecule, so that changes to the wertebreich of the algorithm may
 * be done by the user.
 */

class ComputeSecStructures  
{
public:

    /// 
    ComputeSecStructures();

    /// 
    virtual ~ComputeSecStructures();

    /// will maybe implemented in future 
    // void ClusterMatrixSearch();

    /// the main search algorithm of Kabsch and Sander for secondary
    /// structures
    void KabschSanderSearch(HxMolecule *, MolFilter *, 
                            float minAngle, bool bbe, int writeHBonds, int max);

private:

    /// every generated information from the hydrogen bond calculation
    /// is beeing saved
    void copyAll(ComputeHBonds * comHB);

    /// all coords of every atom of the molecule
    McDArray<McVec3f>  coords;    
    
    ///
    McBitfield isDonOrAccep;

    ///
    McBitfield mBit;        

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
    int nAtoms;

    ///
    MtGroupRef gr;        

    ///
    MolTopology * topo;

    ///
    McDArray<int> residueOfAtoms;    
};    

/* 
 * Help-classes to temporarly save secondary structures
 */
class strandHB : public McLink {
public:    
    McDArray<int > connectedWith;   

    int firstRes;
    int lastRes;
    
    int index;

    int sheet;

    strandHB() {
        lastRes=-1;
        firstRes=-1;
        index=-1;
        sheet=-1;

        _suc=_mcListNullPtr_;
        _pre=_mcListNullPtr_;
    }

    void append(int newRes) {        
        if(lastRes==-1 && firstRes==-1) {
            firstRes=newRes;            
            lastRes=newRes;
        }
        else {
            if(newRes>lastRes) {                
                lastRes=newRes;
            }
            else if(newRes<firstRes) {
                firstRes=newRes;
            }
        }
    }

    void melt(strandHB * s) {        
        if(lastRes>s->firstRes) {
            s->melt(this);
            return;
        }

        int i=0;
        for(i=lastRes;i<s->lastRes;i++) {
            append(i);
        }

    }
};

/* 
 * Help-classes to temporarly save secondary structures
 */
class sheetHB {
public:   
    int firstStr;
    int lastStr;
    
    int index;    

    sheetHB() {
        lastStr=-1;
        firstStr=-1;
        index=-1;        
    }

    void append(int newStr) {        
        if(lastStr==-1 && firstStr==-1) {
            firstStr=newStr;            
            lastStr=newStr;
        }
        else {
            if(newStr>lastStr) {                
                lastStr=newStr;
            }
            else if(newStr<firstStr) {
                firstStr=newStr;
            }
        }
    }
};

/* 
 * Help-classes to temporarly save secondary structures
 */
class heliceHB {
public:
    int firstRes;
    int lastRes;
    
    int index;

    heliceHB() {
        lastRes=-1;
        firstRes=-1;
        index=-1;
    }

    void append(int newRes) {
        if(lastRes==-1 && firstRes==-1) {
            firstRes=newRes;            
            lastRes=newRes;
        }
        else {
            if(newRes>lastRes) {                
                lastRes=newRes;
            }
            else if(newRes<firstRes) {
                firstRes=newRes;
            }
        }
    }

    void melt(heliceHB * s) {        
        if(lastRes>s->firstRes) {
            s->melt(this);
            return;
        }

        int i=0;
        for(i=lastRes;i<s->lastRes;i++) {
            append(i);
        }

    }
};

#endif 

/// @}
