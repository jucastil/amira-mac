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
#ifndef SURF_EDIT_PICK_TOOL_H
#define SURF_EDIT_PICK_TOOL_H

#include "SurfEditMouseTool.h"
#include "BufferUndo.h"
#include <hxcore/HxController.h>

class HxViewer;

/// Tool for picking triangles.
class SurfEditPickTool : public SurfEditMouseTool {

  public:
    /// Constructor.
    SurfEditPickTool(HxSurfEdit* surfEdit);

    /// Destructor.
    ~SurfEditPickTool();

    /// Checks if trianglesPerPoint is ok.
    virtual void activate(int);

    /// unregister event listener
    void deactivate();

    /// Checks if trianglesPerPoint is ok.
    virtual void surfaceChanged();

    /// Event handler.
    virtual void mouseClick(SoEventCallback *eventCB);

  protected:
    /// Event handler.
    virtual bool mouseMove(const SoEvent *, HxViewer *);
    static SbBool eventCallback (const SoEvent *, HxViewer *, void *owner);

  private:
    void  registerEventCallback (void);
    void  unregisterEventCallback (void);

    // mouse movement during selection
    bool  eventCallbackRegistered;
    bool  dragSelection;

    // array of selected triangles
    McDArray<int>  tIndex;

    // line width, line color and point list for triangle selection
    int  lineWidth;
    float  lineColor[3];
    McDArray<SbVec2s>  selPoints;

    // Open GL stuff for drawing lines (very preliminary)
    SbVec2s  windowSize;
    void  drawLine (void);

    /// the implementation of undoable
    BufferUndo* bufferUndo;
};

#endif

/// @}
