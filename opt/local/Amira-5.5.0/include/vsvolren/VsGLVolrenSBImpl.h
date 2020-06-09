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
#ifndef _VS_GL_VOLREN_SB_IMPL_H
#define _VS_GL_VOLREN_SB_IMPL_H

#include "VsVolrenSBImpl.h"

#include "VsMemoryData.h"
#include "VsTechnique2.h"
#include "VsRenderTexture.h"

#include <mclib/McHandle.h>


/// OpenGL slice based volume rendering class.
class VsGLVolrenSBImpl : public VsVolrenSBImpl
{
    VS_IMPLEMENTATION( VsGLVolrenSBImpl, VsVolrenSBImpl, VsVolren )

private:

    unsigned int    mTransferFuncsTexId1D[2];
    unsigned int    mTransferFuncsTexId2D[2];

    
    
    McHandle<VsTechnique2>          mZBufTech;
    McHandle<VsTechnique2::Params2> mZBufParams;
    unsigned int                    mZBufTex;

    // jitter texture stuff
    unsigned char * mJitterData;
    unsigned int    mJitterTex;
    int             mJitterSize;

    // render target stuff
    int              mOffScreenBufferUse;   // true if offscreen buffer is used as render target
    int              mOffScreenBufferDepth;
    int              mOffScreenBufferDepthDefault;
    VsRenderTexture* mRenderTexture;

protected:

    // virtual from base class
    virtual VsRenderResult vimpl_render();
    virtual VSRESULT    vimpl_cleanup();

    virtual bool    vimpl_supported() const;
    virtual VSRESULT    vimpl_setOptioni( int inOption, int inValue );
    virtual VSRESULT    vimpl_setOptiond( int inOption, double inValue );
    virtual VSRESULT    vimpl_optioni( int inOption, int & outValue ) const;
    virtual VSRESULT    vimpl_optiond( int inOption, double & outValue ) const;


public:

    // virtual from base class
    McResult renderClear( McVec4f & inRGBA );
    McResult renderSlices( McDArray<int> & inOffsets, McDArray<int> & inLengths, McDArray<McVec3f> * inAttribs1, McDArray<McVec3f> * inAttribs2, McDArray<McVec3f> * inAttribs3 );
    McResult renderSlices( McDArray<float> & inGeometry );
    McResult colorMapSet( int inVolumeIndex, int inUnit, int * inDims, int inNumChans, int inNumBytesPerChan, int inFilter );
    McResult colorMapBind(int inVolumeIndex, int inUnit, int inNumDims );
    McResult jitterMapBind(int inUnit);
    McResult renderTargetCreate();
    McResult renderTargetRelease();
    bool     renderTargetSupportsZBuffer();
    McResult renderPresent();
    McResult clipPlanesAdd( McDArray< McVec4f > & inClipPlanesO, McDArray< McVec4f > & inClipPlanesW, McDArray< McVec4f > & inClipPlanesC );
    McResult clipPlanesAdd( McHandle<VsCropRegion> inCrop );
    McResult clipPlanesDisable();


    McResult            setTechniqueAPI( Vs::TechniqueAPI inApi );
    Vs::TechniqueAPI    techniqueAPI();

    McResult presentGL();


private:

    /// returns the number of bits per channel for the current device context
    int currChannelBits();
};


#endif


/// @}
