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
#ifndef _VS_GL_TECHNIQUE2_H
#define _VS_GL_TECHNIQUE2_H

#include <mcgl/mcgl.h>

#ifdef HX_HAS_X11
#ifdef Status
#undef Status
#endif
#endif

#include "VsTechnique2.h"


class VSVOLREN_API VsTechniqueGLSL2 : public VsTechnique2
{
private:

    VsTechniqueGLSL2() : VsTechnique2(""){}

public:
             VsTechniqueGLSL2( const char * inName, int inShaderFlags = VsTechnique2::F_ALL );
    virtual ~VsTechniqueGLSL2();

    // virtuals from base class
    virtual VSRESULT internalRelease();
    virtual VSRESULT internalUpdateParam( int inParamId, int intVolumeIndex );
    virtual VSRESULT internalActiveSet( bool inActive );
    virtual VSRESULT internalMakeReady();
    virtual int      internalTexUnit( int inParamId, int intVolumeIndex );

    virtual bool paramPresent( int inParamId, int intVolumeIndex );

    // checks for GLSL support
    static bool supported();


private:

    GLhandleARB         mShaderVertex;
    GLhandleARB         mShaderFragment;
    GLhandleARB         mProgram;

    struct UniformInfo
    {
        GLint   mLocation;
        int     mTexUnit;
    };

    // [shader slot][uniform info]
    McDArray< McDArray<UniformInfo> >  mLocations;

    void updateLocationsSize();
};

#endif

/// @}