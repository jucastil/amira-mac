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

/// @addtogroup vsvolren vsvolren
/// @{
#ifndef VS_BSP_DEBUGGER_H
#define VS_BSP_DEBUGGER_H


#ifdef HX_OS_WIN

#include "Vs.h"

#include <windows.h>

#include "VsViewManager.h"
#include "VsCommonRenderer.h"
#include "VsGroup.h"
#include "VsNode.h"
#include "VsHeadUpDisplay.h"

#include <mclib/McBox3f.h>
#include <mclib/McMat4f.h>
#include <mclib/McPlane.h>
#include <mclib/McVec3f.h>
#include <mclibthreaded/McThread.h>

class VsBSPDebugger
:   public VsViewManager
,   public VsCommonRenderer
,   public McThread
{
public:

    VsBSPDebugger();
   ~VsBSPDebugger();

    ////////////////////////////////////////
    // override McThread
    ////////////////////////////////////////

    void run();

    ////////////////////////////////////////
    // override VsCommonRenderer
    ////////////////////////////////////////
    
    VSRESULT renderFrameBegin();

    ////////////////////////////////////////

    void clear();
    void wait();




    char              * mBSP;
    char              * mCell;
    McPlane             mPlane;
    McVec3f           * mRoi;
    int                 mRoiNumPoints;

    McBox3f             mIntersectionROI;

    int                 mCellID[3];

    McBox3f             mVolumeBound[2];
    McMat4f             mVolumeTransObj2World[2];

    McVec3f             mSphereCenter;
    float               mSphereRadius;


    HWND                mHWnd;

    McHandle<VsGroup>           mScene;
    McHandle<VsNode>            mNode;
    McHandle<VsHeadUpDisplay>   mHUD;
};


extern McHandle<VsBSPDebugger>  gBSPDebugger;

#endif

extern bool                     gBSPDebuggerStep;

#endif




/// @}
