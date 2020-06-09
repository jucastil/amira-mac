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

/// @addtogroup molio molio
/// @{
#ifndef PDBREAD_H
#define PDBREAD_H

#include <molio/MolIOWinDLLApi.h>

#include <mclib/McProgressInterface.h>
#include <mclib/McHandle.h>

#include <molecule/MolTrajectory.h>

#ifdef NEWSTYLE_IOSTREAM
#include <iostream>
using std::ostream;
#include <streambuf>
using std::streambuf;
#else
#include <iostream.h>
#endif

class molInfo;
class lengthizer;
class Molecule;
class MolTopology;
class MtIntraLevelRange;
class MolTrajectoryPDB;

/** class for importing molecules from pdb files **/

class MOLIO_API PDBread {
public:
        // constructor
    PDBread(ostream * str = 0, McProgressInterface * wArea = 0);

    // reads a Molecule and returns it whithout registration in the Object Pool
    /** !! Attention: Standalone-usage requires setting the config-file path 
        via function MolToolsResource::extendPath() before calling readPDBMolecule() !!
    */
    McHandle<Molecule> readPDBMolecule(const char * fileName);

    // when not knowing of which kind the pdb file is, you may want to use this load function
    int readPDBMolTrajectoryBundle(const char * fileName, McDArray<McHandle<MolTrajectory> > & bundle);    



     /** searches all chains for a residue with the index resIx
        and returns its chain index, if there is no such chain
        -1 will be returned **/
    static int getChainIxOfRes(const molInfo& m,int resIx);
    
    /** searches all residues for an atom with the index atomIx
        and returns its residue index, if there is no such residue
        -1 will be returned **/
    static int getResIxOfAtom(const molInfo& m,int atomIx);
    
    /// return name of file format
    const char * getName() const { return "ProteinDataBase"; }

    /** class for storing the stream positions inside the PDB file
        streamPositions are saved for every MODEL entry **/
    class streamPositions {
    public:
        long firstAtom,lastAtom;
        long firstConnect,lastConnect;
        long firstBond,lastBond;
        long firstSecStruct,lastSecStruct;
        streamPositions() {
            firstAtom=-1;lastAtom=-1;
            firstConnect=-1,lastConnect=-1;
            firstBond=-1,lastBond=-1;
            firstSecStruct=-1,lastSecStruct=-1;
        }
        
    };  

    ostream * stream;
    McProgressInterface * workArea;
    
    
    
    /* read the MODEL with the index index as well as topology and HETATMs
    if index is 0 ATOM records will be read from the first record 
    to the first ENDMDL record */
    bool readMolecule(
        Molecule * m,
        const char *fileName,
        const streamPositions& sp,
        int index=0);

    /* same as readMolecule but will only read in the coordinates of each atom
    record (used for trajectories where the topology remains unchanged) */
    bool readCoordinates(
        Molecule* m,
        const char *fileName,
        const streamPositions& sp,
        int index=0);
    
    private:
        
        
    /** will return false if there is a secStruct which overlaps with @c firstRes-@c lastRes
        adjusts @c firstRes and @c lastRes if so
        @c adjustPossible will be set to false if adjustment failed
        index of secstructure which overlaps will be returned in @c structIx**/
    bool checkSecStructUniqueness(
            const molInfo& m,
            int& firstRes, int& lastRes, 
            int& structIx, 
            bool& adjustPossible) const;
        
    /** adjusts @c firstRes and @c lastRes if secStruct overlaps with them
        returns whether adjustment was necessary or not
        adjustPossible will return if adjustment was possible **/
    bool checkSecStructOverlap(
            const molInfo& m,
            const MtIntraLevelRange* secStruct, 
            int& firstRes, int& lastRes,
            bool& adjustPossible) const;
        
    void parseTurnRecord( lengthizer& t, MolTopology* T, molInfo& m);
    void parseHelixRecord(lengthizer& t, MolTopology* T, molInfo& m);
    void parseSheetRecord(lengthizer& t, MolTopology* T, molInfo& m);
    void parseSiteRecord( lengthizer& t, MolTopology* T, molInfo& m);
        
    /** converts the @c chainID as read in from the file to the convention
        as saved in the chain "name" attribute 
        @c isHetATM must be set if the corresponding atoms is a HETATM
        result will replace chainID **/
    void chainIDConversion(char* chainID,bool isHetATM) const;
    
    /** same as above but 
        result will be written into @c result **/
    void chainIDConversion(const char* chainID, char* result,bool isHetATM) const;
    
    /** converts @c chainID, @c resNum and @c resInsCode as read in from the file 
        to the convention as saved in the chain "name" attribute 
        result will be written to @c result **/
    void resIDConversion(const char* chainID,int resNum,const char* resInsCode, char* result,bool isHetATM) const;       
};

#endif

/// @}
