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
#ifndef _VS_GL_VIEW_STATE_
#define _VS_GL_VIEW_STATE_

#include "Vs.h"

#include "VsViewState.h"

#include <mcgl/mcgl.h>

/** \if UNDOCUMENTED A class to save part of the openGL rendering state.
    This one saves the model and projection matrix and the viewport to 
    provide a mapping between world and screen coordinates.
    Note that for valid transfomation with the methods 
    mapWorldToScreen/mapScreenToWorld you need to save the current rendering
    state with the help of save().

    It is a concrete implementation of a VsViewState class for rendering with OpenGL.
    It implements the specific save/restore methods.

    (The class is for internal use only and will not be exported. Therefore it
     does not hide any implementation detail. Instead methods are implemented inline
     for efficiency reasons and for reducing the number of files.)
  */
class VsGLViewState : public VsViewState
{
public:
    
    ///
    VsGLViewState () {};
    ///
    virtual ~VsGLViewState () {};
    
    /** Save the actual GL state. This method MUST NOT be called without
        a valid rendering context!! */
    virtual void save ()
    {
        glGetIntegerv (GL_VIEWPORT, (GLint*)mViewPort);
    
        glGetFloatv (GL_PROJECTION_MATRIX, &mProj[0][0]); 
        glGetFloatv (GL_MODELVIEW_MATRIX, &mModel[0][0]); 
        mProjMatrix = mProj;
        mProjMatrix.multLeft(mModel);

        mInvProjMatrix = mProjMatrix.inverse ();
    };

    /** Restore GL to the saved state. This method MUST NOT be called without
        a valid rendering context!! */
    virtual void restore ()
    {
        glViewport (mViewPort[0], mViewPort[1], mViewPort[2], mViewPort[3]); 
        glMatrixMode (GL_MODELVIEW);
        glLoadMatrixf (&mModel[0][0]);
        glMatrixMode (GL_PROJECTION);
        glLoadMatrixf (&mProj[0][0]);
    }
};

/// \endif

#endif

/// @}
