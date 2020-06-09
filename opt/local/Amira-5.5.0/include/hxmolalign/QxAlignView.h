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
#ifndef QX_ALIGNVIEW_H
#define QX_ALIGNVIEW_H

#include <QScrollArea>
#include <QMouseEvent>

#include <mclib/McDArray.h>
#include <mclib/McString.h>
#include <mclib/McVec2i.h>
#include <mclib/McBitfield.h>

#include <hxcore/HxModule.h>

#include <hxmolalign/HxMolAlignWinDLLApi.h>

class QPainter;

// simple struct to store corresponding sequence letters
struct HXMOLALIGN_API Corr {
    signed char letter[2];
};

// simple struct to store selected sequence elements
struct Selection {
    int col;
    int alignNum; 
    signed char letter[2]; 
    signed char redraw; // 0 = no selection, 1 = draw selection 
    Selection() { redraw=0; }
};

class HXMOLALIGN_API QxAlignView : public QScrollArea
{
    Q_OBJECT
    
private:
    QWidget * parent;
    QFont *font;
    
    McDArray<signed char> seq[2]; // protein sequences
    McDArray<McDArray<Corr> > alignedSeq; // local alignments 
    McDArray<McVec2i> startPos; /* start positions of local alignments
                                   in protein sequences */
    McDArray<McVec2i> insertions; // number of insertions per alignment
    int width, height, longestSeq, firstColPos; // some globals
    int nameOffset, colonOffset, newWidth;
    int rowHeight, colWidth;
    int startRowRedraw, endRowRedraw, startColRedraw, endColRedraw;
    McString seqName[2]; // names of sequences
    bool seqIsNew; // flag which is set if sequence is new
    McBitfield isSelected; // which alignments are selected currently
    Selection selSeqEl; // stores a sequence selection
    char** alpha;
    int score; // score of alignment

public:
    QxAlignView(QWidget * parent=0);
    
    ~QxAlignView();
    
    void setSequences(McString name1, McString name2, 
                      McDArray<signed char> &seqA, 
                      McDArray<signed char> &seqB,
                      McDArray<McVec2i> &seqStartPos,
                      McDArray<McVec2i> &insertions,
                      McDArray<McDArray<Corr> > tracebackArr,
                      int score, int alphaId);

    McBitfield * getSelected() { return &isSelected; }

    void redraw();

protected:
    void paintEvent(QPaintEvent * event);
    void mousePressEvent(QMouseEvent * event);

private:
    void computeFontSpecificParameters(QFontMetrics & fm);
    void computeHeightAndWidthOfAlignViewWindow();
    void computeStartAndEndPositionForRedrawing(const int cx, const int cy,
                                                const int cw, const int ch);
    void drawAllSequenceAlignments(QPainter     * p,
                                   QFontMetrics & fm);
    int  drawSequenceAlignmentForOneMolecule(QPainter     * p,
                                             QFontMetrics & fm,
                                             const int      alignmentIdx,
                                             const int      molIdx,
                                             const int      maxStartPos,
                                             int            rowNum);
    void drawAlignmentLabelsAndGeneralInfo(QPainter     * p,
                                           QFontMetrics & fm,
                                           const int      alignmentIdx,
                                           const int      rowNum,
                                           const int      rowHeight);
    void drawMoleculeName(QPainter  * p,
                          const int   molIdx,
                          const int   rowNum,
                          const int   rowHeight);
    int  drawSpacesForMissingLetters(QPainter  * p,
                                     int         start,
                                     int         end,
                                     const int   rowNum,
                                     const int   rowHeight,
                                     int         colNum,
                                     const int   colWidth,
                                     const int   startColRedraw);
    int  drawUnalignedSequence(QPainter  * p,
                               const int   molIdx,
                               int         start,
                               int         end,
                               int         curLet,
                               const int   rowNum,
                               const int   rowHeight,
                               int         colNum,
                               const int   colWidth,
                               const int   startColRedraw);
    int  drawAlignedSequence(QPainter  * p,
                             const int   alignmentIdx,
                             const int   molIdx,
                             int         start,
                             int         end,
                             int         curLet,
                             const int   rowNum,
                             const int   rowHeight,
                             int         colNum,
                             const int   colWidth,
                             const int   startColRedraw);
    void drawSelectedSequenceElements(QPainter * p);
};

#endif

/// @}
