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

/// @addtogroup hxsegeditor hxsegeditor
/// @{
#ifndef GI_SELECTION2D_H
#define GI_SELECTION2D_H

#include <mclib/McHandable.h>
#include <mclib/McVec2f.h>
#include <mclib/McBox2i.h>
#include <mclib/McData2D.h>
#include <mclib/McPrimType.h>
#include <mclib/McBitfield.h>
#include "HxGiWinDLLApi.h"

class GiFrameBuffer;
class GiEvent;

/** Represents a 2D image selection.

    The selection may allocate its own memory. However, usually external
    memory is used, e.g. a particular slice of a 3D selection.
*/
class HXSEGEDITOR_API GiSelection2D : public McHandable {
  public:

    /// Constructor.
    GiSelection2D();

    /// Destructor.
    ~GiSelection2D();

    /// Copy constructor.
    GiSelection2D(const GiSelection2D& other);

    ///
    int get(int i, int j) const {
        mculong idx = mBitsOffset + mBitsPerLine*j + mBitsPerPixel*i;
        return mBitfield->operator []( idx );
    }

    /// Returns size of selection.
    McVec2i getSize() { return McVec2i(sizeX(),sizeY()); }

    /// Returns pointer to selection array.
    //unsigned char* getMemory() { return (unsigned char*)dataPtr(); }

    /// Resizes the selection, local memory will be allocated.
    void resize(int nx, int ny);

    /** Initializes selection with an external memory reference.
        @c mem isn't freed later on. */
    //void setMemory(int width, int height, unsigned char* mem);

    /** Initializes selection with an external memory reference.
        @c mem isn't freed later on. */
    // void setMemory(int width, int height, int bytesPerPixel,
    //          int bytesPerLine, unsigned char* mem);
    void setBitfield(McBitfield* bitfield3D,
            mculong width, mculong height, mculong bitsOffset, mculong bitsPerPixel, mculong bitsPerLine);

    /// Clear selection.
    void clear();

    /// Fill holes in selection (slice).
    void fillSelection(int sx=-1,int sy=-1, int clear=0);

    /** Fill wholes in selection. Operates only inside selection box,
        i.e., the selection box must be valid.
        See computeSelectionBox(), setSelectionBox() */
    void fillSelectionInBox();

    /// Invert selection.
    void invert();

    /** Clear selection. If the selection wasn't empty, the return value
        of the method is 1 and the parameter @c box is set to the
        bounding box of the selection area. If the selection was empty,
        0 is returned and @c box isn't changed. */
    int clear(McBox2i& box);

    /// The selection box specifies the area of non-zero pixels.
    McBox2i& getSelectionBox() { return selectionBox; }

    /// Check if selection box is empty.
    int isEmpty() { return selectionBox.isEmpty(); }

    /** Updates the selection box. This method should be called whenever
        the selection has been edited by accessing getMemory(). */
    void computeSelectionBox();

    /** Updates(extends) the selection box by checking only a subregion.*/
    void updateSelectionBox(McBox2i updateRegion);

    /// Extends the selection box.
    void extendSelectionBox(const McBox2i& other);

    /// Sets the selection box.
    void setSelectionBox(const McBox2i& box);

    ///
    enum SelectMode { ADD, SUBTRACT, REPLACE };

    ///
    void setSelection(int n, const McVec2f *vertices, SelectMode mode=REPLACE);

    ///
    void setSelection(int n, const McVec2f *vertices, SelectMode mode, const McBitfield& mask);

    /// Selects all pixels with label @c type.
    void setTissue(unsigned char* label, int type, SelectMode mode=REPLACE);

    ///
    enum RenderMode { MASKED, ANTLINES };

    ///
    void setRenderMode(RenderMode m) { renderMode=m; }

    RenderMode getRenderMode() const {  return renderMode; }
    ///
    void touch() {
        modified = 1;
    }

    ///
    void untouch() {
        modified = 0;
    }

    ///
    int wasModified() {
        return modified;
    }

    ///
    void set(int i, int j);

    ///
    void unset(int i, int j);

    ///
    void set(mculong idx);

    ///
    void unset(mculong idx);

    ///
    //void set(int xstart, int xstop, int j, int value);

    ///
    int isSet(int i, int j) const;

    ///
    int isSet(mculong idx) const;

    ///
    bool copyData(GiSelection2D& src);

    ///
    int sizeX() const { return mDims[0]; }

    ///
    int sizeY() const { return mDims[1]; }

    ///
    void computeBoundingBox(McBox2i& box);

    ///
    void makeLocal();

protected:
    int modified;
    McBox2i selectionBox;
    RenderMode renderMode;

    static void fillPixel(void* userData,
          int x0, int x1, int y, unsigned char* alphaValues);
    static void clearPixel(void* userData,
          int x0, int x1, int y, unsigned char* alphaValues);
    static void maskPixel(void* userData,
          int x0, int x1, int y, unsigned char* alphaValues);

    mculong mDims[2];
    mculong mBitsPerLine;
    mculong mBitsPerPixel;
    mculong mBitsOffset;
    McBitfield mLocalBitfield;
    McBitfield* mBitfield;
    const McBitfield* mMask;
};

#endif

/// @}
