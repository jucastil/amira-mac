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

/// @addtogroup hxmolalign hxmolalign
/// @{
#ifndef HX_SEQALIGN_H
#define HX_SEQALIGN_H

#include <mclib/McHashTable.h>
#include <mclib/McString.h>
#include <mclib/McBitfield.h>

#include <hxcore/HxCompModule.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortIntSlider.h>

#include <hxmolecule/HxMolecule.h>
#include <hxmolalign/QxAlignViewDialog.h>
#include <hxmolalign/HxMolAlignWinDLLApi.h>

/** This class implements sequence alignment of two molecules. The
    alignment can be carried out for both rna/dna and proteins. Three
    alignment algorithms exist: local, semi-global and global with
    gaps, which are used for different purposes.  
    - The local and the semi-global algorithms are useful if you have
      molecules with different lengths. 
    - The local sequence alignment is especially useful if you want to
      identify similar subsequences in the molecules, or if you want to
      find one short sequence within a longer one.
    - Global alignment with gaps is normally used if you have two almost
      equally long sequences and you want to find small differences within 
      the molecule.
    - Semi-global alignment is similar to global alignment only that 
      mismatches at the beginning and at the end of the sequence are not
      penalized. 
*/
class HXMOLALIGN_API HxSeqAlign : public HxCompModule {
    HX_HEADER(HxSeqAlign);
    
public:
    /// Molecule that should be aligned to molecule A connected to portData.
    HxConnection portMoleculeB;
    /// Options (currently 'show alignment' only).
    HxPortToggleList portOptions;
    /** Which sequences are used as input: 
           0 = molecule A and molecule B
           1 = molecule A and some motif (short sequence)
           2 = molecule B and some motif */
    HxPortRadioBox portInput;
    /// Motif sequence.
    HxPortText  portMotif;
    /** Two menus specifying the align type. The first menu specifies
        whether proteins or rna/dna should be aligned. The second menu
        has three entries: 0 = local, 1 = semi-global, 2 = global with gaps. */
    HxPortMultiMenu portAlignType;
    /// Insertion/deletion value.
    HxPortIntSlider portIndel;
    /// Start sequence alignment.
    HxPortDoIt portAction;
    
public:    
    /// Constructor.
    HxSeqAlign(); 
    /// Destructor.
    ~HxSeqAlign(); 

    /// Update method.
    virtual void update();
    /// Compute method.
    virtual void compute();
    /// Parse method for tcl commands.
    int parse(Tcl_Interp* t, int argc, char **argv);

    // Add all alignment as new levels.
    void addAllNewLevels();
    // Add one alignment as new level.
    void addNewLevels(McBitfield *selected,const char* levNameBase=0);
    // Convert integer to ascii.
    static char* itoa2(int n);

    static char** getProteinOneLetterAlphabet();
    static char** getProteinThreeLetterAlphabet();
    static char** getRNAOneLetterAlphabet();
    
protected:
    // Hash table to match some amino acid to some integer value.
    McHashTable<McString, signed char> * aaId;
    // Hash table to match some nucleotide to some integer value.
    McHashTable<McString, signed char> * nId;
    // Input molecule A.
    HxMolecule *hxMolA;
    // Input molecule B.
    HxMolecule *hxMolB;
    // Match used sequences to complete sequence of molecule.
    McDArray<int> seqMaps[2];
    // Sequences.
    McDArray<signed char> seqs[3];
    // Similarity matrix.
    McDArray<McDArray<int> > S;
    // Stores information about the origin of some value in matrix @c S.
    McDArray<McDArray<int> > origin;
    // Array to store all alignments.
    McDArray<McDArray<Corr> > tracebackArr;
    // Stores number of current insertion in sequence 1 and 2, respectively.
    McVec2i curInsertions;
    // Insertions per alignment.
    McDArray<McVec2i> numInsertions;
    // Start positions per alignment. 
    McDArray<McVec2i> seqStartPos;

    // keep track of current number of alignments per starting max value
    int numAlignmentPerMaxValue;
    // maximal number of alignments per starting max value 
    int limit;
    // store old align type
    int oldAlignType:16;
    // sequence index of first sequence used for aligment
    int seqId1:8;
    // sequence index of first sequence used for aligment
    int seqId2:8;
    // window showing the alignment
    QxAlignViewDialog * alignViewDialog;

protected:    
    // update options port
    void updatePortOptions();
    // does the actual computation
    void doIt();
    // return index of character @c c within the alphabet
    // 0 is returned if @c c does not belong to alphabet
    int lookupValue(char c, bool isProtein);
    // initialize similarity matrix @c S for local and semi-global alignment
    void initSeqMatrix(int &max);
    // initialize similarity matrix @c S for global alignment
    void initSeqMatrixGlobWithGaps(int &max);
    // set letters of @c corr according to direction
    void setLetters(int direction, int i, int j, Corr &corr);
    // recursive function storing all sequence alignments in @c traceback
    void gettraceback(int i, int j, McDArray<Corr> &traceback);
};

#endif

/// @}
