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

/// @addtogroup hxsurfedit hxsurfedit
/// @{
#ifndef BUFFER_UNDO_H
#define BUFFER_UNDO_H

#include "Undoable.h"
#include "HxSurfEdit.h"
#include <mclib/McDArray.h>

/// implements Undoable for Surfaces
class BufferUndo : public Undoable {

public:

    /// Constructor
    BufferUndo(HxSurfEdit* parent);

    virtual ~BufferUndo(){
        for (int i=0; i<undoStack.size(); i++)
            delete undoStack[i];
    }

    struct BufferUndoEntry {
        int selectionStart;
        int highlightStart;
        int selectionStop;
        int highlightStop;
        unsigned int* selectionData;
        unsigned int* highlightData;

        BufferUndoEntry() {
            selectionData = 0;
            highlightData = 0;
        }

        ~BufferUndoEntry() {
            if (selectionData) free(selectionData);
            if (highlightData) free(highlightData);
        }
    };

    //undoStack:
    McDArray< BufferUndoEntry * > undoStack;

    HxSurfEdit * surfEdit;

    McBitfield undoHighlightSave;
    McBitfield undoSelectionSave;

    /// undo the last surfaceAction in undoStack
    void undo();

    /** Used to implement undo of buffer changes. Before the selection
    buffer of the highlight buffer is modified by a mouse tool or
    a selector this method should be called. The mode
    parameter determines whether only the highlight buffer (bit 1)
    or only the selection buffer (bit 2) or both buffers (bits 1 and
    2, value 3) should be saved. The default is to save the highligt
    buffer only. */
    void undoBufferBegin(int mode=1);

    /** Actually stores an undo entry. The method should be called after
    undoBufferBegin
    !!! undoBufferEnd even announce this undoable action in HxSurfEdit. You Don`t have to do it!!! */
    void undoBufferEnd();
};

#endif

/// @}
