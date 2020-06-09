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
#ifndef GiPICKREGION_H
#define GiPICKREGION_H

#include <mclib/McBox2i.h>
#include <mclib/McData2D.h>
#include <mclib/McData3D.h>
#include <mclib/McBitfield.h>
#include <mclib/McDArray.h>

#include "Gi.h"
#include "GiTool.h"
//Added by qt3to4:
#include <QPixmap>

class QPixmap;
class QCheckBox;
class GiFrameBuffer;

/** Implements 2D region growing. */

class GiPickRegion : public GiTool {

  public:
    /// Constructor.
    GiPickRegion(Gi* theGi);

    /// Destructor.
    ~GiPickRegion();

    virtual const char* getIconName() const{ return "SegPickRegionIcon.png"; }

    /// Event handler.
    int handleEvent(GiFrameBuffer* frameBuffer, McEvent* event);

    void resetTranslationVec();
    SbVec3f getTranslationVec();

  protected:
    enum { PICK_MODE=0, TRANSLATE_MODE=1, ROTATE_MODE=2 };

    QCheckBox* _w3DMode;
    QCheckBox* _wSelectAll;
    unsigned int cursorMode:2;
    unsigned int eventMode:2;
    unsigned int saveUndoNeeded:1;
    McVec2i currentBoxOrigin;
    McVec2i translateOrigin;
    McBox2i selectionBox;
    float phi;
    QPixmap* pixmap;
    McDArray<unsigned char> selectionSave;

    McVec3i sourcePos, targetPos;
    SbVec3f translationVec3f;

    int is3D();
    void rotate3d(GiFrameBuffer* fb);
    void translate3d(GiFrameBuffer* fb);
    virtual void createWidget(QWidget* parent);
    void setCursor(unsigned int mode, GiFrameBuffer* fb);
    void checkCursor(GiFrameBuffer* frameBuffer, McEvent* event);
    int handleEventRotate(GiFrameBuffer* frameBuffer, McEvent* event);
    int handleEventTranslate(GiFrameBuffer* frameBuffer, McEvent* event);

    void copyBuffer3D(GiSelection3D*, McBitfield& bits,int bb[6],
        unsigned char val);
    void copyBuffer2D(GiSelection3D*, McBitfield& bits,
        int bb[4], unsigned char val);
    void selectAll(const McData2D<unsigned char>& labels,
        unsigned int material, McBitfield& selected, int* bb2);
    void selectAll(const McData3D<unsigned char>& labels,
        unsigned int material, McBitfield& selected, int* bb3);
};

#endif

/// @}
