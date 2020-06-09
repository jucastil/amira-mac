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
#ifndef VS_COMMON_RENDERER_IMPL_H
#define VS_COMMON_RENDERER_IMPL_H

#ifdef HX_OS_WIN
#include <Windows.h>
#endif

#include <mcgl/mcgl.h>
#include <mcgl/McGLText.h>
#include <mclib/McHandle.h>
#include <mclib/McHashTable.h>

#include "VsImpl.h"
#include "VsPBuffer.h"
#include "VsRenderQueue2.h"
#include "VsCommonRenderer.h"
#include "VsRendererImpl.h"
#include "VsInteractionManager.h"
#include "VsNode.h"
#include "VsMemoryData.h"
#include "VsDataAccess.h"
#include "VsTexturedPolygon.h"

#ifdef HX_OS_MACX
#include <AGL/agl.h>
#endif

class VsCommonRendererImpl :  public VsRendererImpl
{
    VS_IMPLEMENTATION( VsCommonRendererImpl, VsRendererImpl, VsCommonRenderer )

public:

    class VsPBufferPrivate : public VsPBuffer {
        friend class VsCommonRenderer;
    };

    VsPBufferPrivate*   mPBuffer;               // P-buffer used for offscreen rendering
    McVec2i             mOffscreenSize;         // Size of the offscreen buffer used for rendering
    bool                mOffscreen;
    static bool         mOffscreenSupported;

    McHandle<VsTexturedPolygon> mBackgroundTexture;    
    mcint64                     mBackgroundTextureTouchNum;


    static McHashTable< VsVoidHandle, VsCommonRenderer* > mAttached; // maps HWND -> renderer
    static McDArray< VsCommonRenderer* > mInstances;

    VsRenderResult      mRenderFrameBeginResult;
    bool                mLossyCompressed;

#ifdef HX_OS_MACX
    HIViewRef           mHIView;
	WindowRef			mWindow;
	AGLContext			mWindowContext;
    AGLContext          mOffscreenContext;
	CGDirectDisplayID	mWindowDisplay;
	CGDirectDisplayID	mOffscreenDisplay;
#endif


#ifdef HX_HAS_X11
    Window              mWindow;                // window for displaying
    XVisualInfo*        mVisualInfo;            // visual info of mWindow
    Display*            mWindowDisplay;         // display of mWindow
    GLXContext          mWindowContext;         // OpenGL rendering context for mWindow
    Display*            mOffscreenDisplay;      // display connection for pbuffer
    int                 mOffscreenScreen;       // screen for pbuffer
    GLXContext          mOffscreenContext;      // OpenGL rendering context for pbuffer
    bool                mOwnsOffscreenDisplay;  // True if display was opened here
#endif

#ifdef HX_OS_WIN
    HWND                mWindow;                // window for displaying
    WNDPROC             mDefWndProc;            // original message handler of the window
    HDC                 mDeviceContext;         // device context of mWindow
    VsVoidHandle        mWindowDisplay;
    HGLRC               mWindowContext;         // OpenGL rendering context for mWindow
    VsVoidHandle        mOffscreenDisplay;
    HGLRC               mOffscreenContext;      // OpenGL rendering context for pbuffer

    VSRESULT handleSizeChange();
    VSRESULT releaseWindow();
    static LRESULT CALLBACK MsgProc(HWND,UINT,WPARAM,LPARAM); // our message handler for the window
#endif

    VSRESULT windowContextCreate();
    VSRESULT windowContextDelete();
    VSRESULT offscreenContextUpdate();
};

#endif

/// @}
