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
#ifndef GiADJUSTTOOL_H
#define GiADJUSTTOOL_H

#include "McVec2i.h"
#include "McVec2f.h"
#include "McDArray.h"
#include "McData2D.h"
#include <Gi.h>
#include <GiTool.h>
#include <IScissors.h>
#include <mclib/McIsoline2D.h>
#include <mclib/McBlowRegion.h>
#include <Contour2D.h>
#include <Snakes.h>
#include <GiSelection2D.h>

class GiViewer;
class GiFrameBuffer;

///
class GiAdjustTool : public GiTool {

  public:
    /** Constructor. */
    GiAdjustTool(Gi* theGi);

    /** Destructor. */
    ~GiAdjustTool();

    /** Draw this shape into the specified frame buffer. */
    void render(GiFrameBuffer* frameBuffer, const McBox2i& box);

    /** Draw this shape into the specified frame buffer.
        @return true if the event has been handled by this object */
    int handleEvent(GiFrameBuffer* frameBuffer,McEvent* event);

    /** Returns bounding box of shape. */
    McBox2i getBoundingBox();

    void adjustSelection(int doRender=0);

    void snakesInit();

    void snakesOneStep();

  protected:
    McBlowRegion* blower;
    McIsoline2D* isoLine;

    Snakes snakes;
    Contour2D contour2D;

    virtual void createWidget(Widget Parent);

    Widget _wTextF1;
    Widget _wTextF2;
    Widget _wTextF3;

    static void textF1CB(Widget, XtPointer, XtPointer);
    static void textF2CB(Widget, XtPointer, XtPointer);
    static void textF3CB(Widget, XtPointer, XtPointer);

    static void goCB(Widget, XtPointer, XtPointer);
    static void upCB(Widget, XtPointer, XtPointer);
    static void downCB(Widget, XtPointer, XtPointer);
    static void relaxCB(Widget, XtPointer, XtPointer);
    static void growCB(Widget, XtPointer, XtPointer);
    static void shrinkCB(Widget, XtPointer, XtPointer);
    static void resetCB(Widget, XtPointer, XtPointer);

    void textF1Changed(Widget);
    void textF2Changed(Widget);
    void textF3Changed(Widget);

    void undo();
    static void undoCB(Widget, XtPointer, XtPointer);
};

#endif

/// @}
