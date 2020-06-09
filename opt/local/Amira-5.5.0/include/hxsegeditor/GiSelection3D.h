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
#ifndef GiSELECTION3D_H
#define GiSELECTION3D_H

#include "HxGiWinDLLApi.h"
#include <mclib/McDArray.h>
#include <mclib/McHandable.h>
#include <mclib/McVec2f.h>
#include <mclib/McBox2i.h>
#include <mclib/McData2D.h>
#include <mclib/McData3D.h>
#include <mclib/McTypedData3D.h>
#include <mclib/McBitfield.h>

class GiFrameBuffer;
class GiEvent;
class GiSelection2D;

/** Represents a selection of parts of the image. Internally
  the selection is represented by a McBitfield.
  */

class HXSEGEDITOR_API GiSelection3D : public McHandable {

  public:
    /// Modes for setTissue() (ADD, SUBTRACT, REPLACE).
    enum SelectMode { ADD, SUBTRACT, REPLACE };

    /// Constructor.
    GiSelection3D(int nx,int ny,int nz);

    /// Constructor.
    GiSelection3D();

    /// Destructor.
    ~GiSelection3D();

    /// Resize buffer for selection. All data is erased.
    void resize(mculong width, mculong height, mculong nz);

    /// Clears whole selection.
    void clear();

    /// Inverts whole selection.
    void invert();

    /// Selects all pixels with label @c type.
    void setTissue(unsigned char* label, int type, SelectMode mode=REPLACE);

    /// Returns reference(!) to selection slice in given orientation.
    GiSelection2D getSlice(int n, int orientation);

    /// Copy selection from one slice to another.
    void copy(int to, int from, int orientation);

    ///
    int isEmpty(int slice, int orientation);

    ///
    int getWidth(int orientation=2);

    ///
    int getHeight(int orientation=2);

    ///
    int getNumSlices(int orientation=2);

    ///
    enum {INTERPOLATED_SELECTION = 1, SNAKES_GENERATED_SELECTION=2};

    ///
    McDArray<int> sliceFlags[3];

    ///
    void set(int i, int j, int k);

    ///
    void unset(int i, int j, int k);

    ///
    void set(mculong idx);

    ///
    void unset(mculong idx);

    ///
    //void set(int xstart, int xstop, int j, int k, int value);

    ///
    int get(int i, int j, int k) const;

    ///
    unsigned int getWord(mculong idx) const;

    ///
    int isSet(mculong idx) const;

    /// returns true if any bit of the selection is set
    bool isSet(void) const;

    ///
    void getSlice(GiSelection2D* sel2D, int orientation, int sliceNumber);

    ///
    void setSlice(GiSelection2D* sel2D, int orientation, int sliceNumber);

    ///
    void getDims(int dims[3], int orientation) const;

    /// Returns x dimension of array.
    int sizeX() const { return mDims[0]; }

    /// Returns y dimension of array.
    int sizeY() const { return mDims[1]; }

    /// Returns z dimension of array.
    int sizeZ() const { return mDims[2]; }

    /// Returns pointer to internal bitfield
    McBitfield& bitfield() { return mBitfield; }

    ///Copy the GiSelection3D's McBitfield into a McBitfield
    void copyTo(McBitfield& other);

    ///Copy from another McBitfield into the GiSelection3D's bitfield.
    void copyFrom(McBitfield& other);

    /// fills the whole in a selection.
    void fillHoles();

protected:
    mculong mDims[3];
    McBitfield mBitfield;

    void freeSlices();
};

#endif

/// @}
