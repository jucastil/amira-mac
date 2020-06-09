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

/// @addtogroup hxvisageviewer hxvisageviewer
/// @{
#ifndef  EX_WINDOWLEVELTOOL_H
#define  EX_WINDOWLEVELTOOL_H

#include "ExModal.h"
#include "ExBase.h"
#include "VisageViewerWinDLLApi.h"

//#ifdef CusorShape
  //  #undef CusorShape
//#endif

class HXVISAGEVIEWER_API ExWindowLevelTool : public ExModal 
{
public:
    ExWindowLevelTool(int /* Vs::ButtonState */ activeState = Vs::BS_LeftButton);
    ~ExWindowLevelTool();

    virtual bool supports(Ex::ViewerType) const;
    
    virtual bool isStandard() const { return true; }

    static void setWindowLevel(ExBaseViewer* viewer, float vmin, float vmax, int idx, bool updateOtherViewers = true);
    static bool getWindowLevel(ExBaseViewer* viewer, float* vmin, float* vmax, int idx);

    void startWindowLeveling(ExBaseViewer* viewer, int x, int y);
    void stopWindowLeveling();
    bool windowLeveling() const;
    VSRESULT updateWindowLevel(ExBaseViewer* viewer, int x, int y);

    virtual bool processMouseEvent(ExBaseViewer* viewer, Vs::MouseEvent inEvent, int inX, int inY, 
        Vs::ButtonState inState, Ex::CursorShape& outCursor);
    virtual bool processKeyEvent(ExBaseViewer* viewer, Vs::KeyEvent inEvent, Vs::Key inKey, Vs::ButtonState inState);
    virtual bool processWheelEvent(ExBaseViewer* viewer, int inX, int inY, int inDelta);

    virtual const McString identifier() const;

private:
    bool    mWindowLeveling;
    int     mLastPos[2];
    float   mRange;
    int     mDataIdx;
};

#endif // EX_WINDOWLEVELTOOL_H


/// @}
