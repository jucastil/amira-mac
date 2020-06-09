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
#ifndef PDBWRITE_H
#define PDBWRITE_H

#include <molio/MolIOWinDLLApi.h>

#include <molecule/MtGroupRef.h>

#include <mclib/McProgressInterface.h>
#include <mclib/McFilename.h>

#ifdef NEWSTYLE_IOSTREAM
#include <iostream>
using std::ostream;
#include <streambuf>
using std::streambuf;
#else
#include <iostream.h>
#endif


class MolTrajectory;
class Molecule;
class MolTopology;
class McVec3f;
class molInfo;
class writer;

/** class for exporting molecules to pdb files **/

class MOLIO_API PDBwrite {

    class secRef {
    public:
        // index of this secStructure in the secRefs List
        int secIx;
        // number of strand (applies only if secType=SHEET)
        int strandNum;
        
        secRef() {secIx=-1;strandNum=-1;}
        secRef(int r,int sn=0) {
            secIx=r;strandNum=sn;}
        bool operator==(secRef& r) {
            return ((r.secIx==secIx) && (r.strandNum==strandNum));
        }
        bool operator!=(secRef& r) {
            return !(*this==r);
        }
    };

    class secInfo {
    public:
        MtGroupRef ref;
        McDArray<int> firstRes;
        McDArray<int> lastRes;
        McDArray<int> residues;
        secInfo(){}
    };

public:
    PDBwrite(McFilename fn, ostream * str = 0, McProgressInterface * wArea = 0);

    /// writes molecule M as pdb file with the filename filename
    bool writePDBMolecule(Molecule* mol, const char* filename, bool pdbq=false);

    bool writePDBMolTrajectory(MolTrajectory* traj, const char* filename, bool bdpq=false);    

private:

    McFilename datafilename;

    ostream * stream;
    McProgressInterface * workArea;
    Molecule* mol;

    // the following methods will write certain parts of the pdb entry to
    // the file, they require various information which has to be generated
    // from the original molecule by the generate*Data() methods
    void writeHeaderRecords(
        writer& w);
    void writeSeqResRecords(
        writer& w,
        const molInfo& m,
        const McBitfield& isResHetGroup,
        int& seqResRecords);
    void writeSecStructRecords(
        writer& w,
        const molInfo& m,
        const McDArray<McDArray<secInfo> >& secInfos,
        const McDArray<int>& serNumOfResIx,
        const McDArray<int>& chainIxOfRes,
        int& helixRecords,
        int& sheetRecords,
        int& turnRecords);
    void writeSiteRecords(
        writer& w,
        const molInfo& m,
        const McDArray<int>& serNumOfResIx,
        const McDArray<int>& chainIxOfRes,
        int& siteRecords);
    void writeConectRecords(
        writer& w,
        const McDArray<int>& serNumOfAtomIx,
        const McDArray <McDArray <int> >& bondList,
        int& conectRecords);
    void writeAtomRecords(
        writer& w,
        const molInfo& m,
        const McVec3f * coord,
        const McBitfield& isAtomInChain,
        const McBitfield& isResHetGroup,
        const McDArray<int>& atomSequence,
        const McDArray<int>& resIxOfAtom,
        McDArray<int>& serNumOfAtomIx,
        const McDArray<int>& serNumOfResIx,
        const McDArray<int>& chainIxOfRes,
        int& atomRecords,
        int& terRecords,
        bool pdbq);
    void writeSSBondRecords(
        writer& w,
        const molInfo& m,
        const McDArray<int>& bondIndices,
        const McDArray<int>& resIxOfAtom,
        const McDArray<int>& chainIxOfRes,
        const McDArray<int>& serNumOfResIx,
        int& ssbondRecords);
    void writeMasterRecord(
        writer& w,
        int helixRecords,
        int sheetRecords,
        int turnRecords,
        int siteRecords,
        int atomRecords,
        int terRecords,
        int conectRecords,
        int seqresRecords);

    // following methods generate some modified 
    // information that is needed to write pdb
    // entries from the original molecule data in amira
    void generateResidueData1(   const molInfo& m,
                                 McBitfield& isResHetGroup);
    void generateResidueData2(   const molInfo& m,
                                 const MolTopology* T,
                                 McDArray<int>& resSequence,
                                 McDArray<int>& serNumOfResIx,
                                 McDArray<int>& chainIxOfRes,
                                 McDArray<McDArray<secInfo> >& secInfos);
    void generateAtomData1(      const molInfo& m,
                                 const McDArray<int>& resSequence,
                                 McDArray<int>& atomSequence,                                 
                                 McDArray<int>& serNumOfAtomIx,
                                 McDArray<int>& resIxOfAtom);
    void generateAtomData2(      const molInfo&m,
                                 McBitfield& isAtomInChain);
    void generateBondData(       const molInfo& m,
                                 const McDArray<int>& resIxOfAtom,
                                 const McBitfield& isResHetGroup,
                                 McDArray<McDArray<int> >& bondList,
                                 McDArray<int>& ssbonds);


    /* converts the chainId of chain chainIx from the Amira convention to
        the form as used in pdb files
        returns whether chain chainIx was the HET chain */
    bool chainIdConversion(const molInfo &m,int chainIx,char* chainId) const;
    bool areResiduesBonded(const molInfo &m,int resIx1,int resIx2) const;
    int getCAtomOfResidue(const molInfo &m,int resIx) const;
    int getNAtomOfResidue(const molInfo &m,int resIx) const; 
};

#endif


/// @}
