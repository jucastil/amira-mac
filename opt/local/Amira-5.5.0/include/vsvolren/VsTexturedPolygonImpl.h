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
#ifndef _VS_TEXTUREDPOLYGON_IMPL_H
#define _VS_TEXTUREDPOLYGON_IMPL_H

#include "VsNodeImpl.h"

#include "VsTexturedPolygon.h"

#include <mclib/McDArray.h>

////////////////////////////////////////////////////////////////////////////////
class VsTexturedPolygonImpl : public VsNodeImpl
{
    VS_IMPLEMENTATION( VsTexturedPolygonImpl, VsNodeImpl, VsTexturedPolygon )

public:

    // Data structure for a single texture tile
    struct Tile {
        int                 mStart[2];  // The start index within the large image
        int                 mDims[2];   // The size of the texture tile

        McDArray<McVec3f>   mVertices;  // Vertices of the corresponding sub-polygon
        McDArray<McVec3f>   mTexCoords; // Texture coordinates of the corresponding sub-polygons
        McDArray<int>       mPolyStart; // List of first vertices of all sub-polygons.
        McDArray<int>       mPolyLength;// The list of the lengths of all sub-polygons.
    };

    class Image
    :   public VsHandable
    {
    public:

        McHandle<VsData>  mImage;       // The image to be used as texture
        bool              mRgb;         // RGB(A) or BGR(A) format
        unsigned int      mFilter;      // The texture filtering, to be used
        float             mScale;       // A scale to be applied during texture download
        float             mBias;        // A bias to be applies during texture download
        int               mTextureUnit;

        bool              mIsDirty;     // Does the textures need reload

        int               mGLIntFormat;
        int               mGLExtFormat;
        int               mGLExtType;

        McDArray< unsigned int > mTextureID;

        Image()
        :   mRgb            ( true )
        ,   mFilter         ( GL_LINEAR )
        ,   mScale          ( 1.0 )
        ,   mBias           ( 0.0 )
        ,   mTextureUnit    ( VsTexturedPolygon::VS_USE_ACTIVE_UNIT )
        ,   mIsDirty        ( false )
        ,   mGLIntFormat    ( 0 )
        ,   mGLExtFormat    ( 0 )
        ,   mGLExtType      ( 0 )
        {
        }
    };

    McDArray< McHandle<Image> > mImages;

    McDArray< Tile >            mTiles;       // The list of texture tiles.

    int                         mTileDims[2]; // The resolution for which the tiles were created

    bool                        mUseTexture;  // Set if we render with textures - default true

    McDArray<unsigned int>      mCleanupResources; // The texture ids, that need to be cleant up

    McDArray<McVec3f>           mVertices;    // List of vertices for the registerd polygons
    McDArray<McVec3f>           mTexCoords;   // List of texcoords for the registered polygons
                                              //      texture coordinates stored here are assumed to be
                                              //      in the range 0 ... mImage.dims()
    McDArray<int>               mPolyStart;   // The list of indices pointing to the first vertex of 
                                              //      each polygon in mVertices/mTexCoords.
    McDArray<int>               mPolyLength;  // The list of the lengths of all registers polygons.


public:
    ////////////////////////////////////////
    // non-virtual interface methods
    ////////////////////////////////////////

    void copy(const VsTexturedPolygonImpl* other);

private:
    ////////////////////////////////////////
    // virtual interface methods
    ////////////////////////////////////////
    VSRESULT         vimpl_boundingBox( McBox3f & box ) const;
    VsRenderResult   vimpl_render();
    VSRESULT         vimpl_cleanup();
    VSRESULT         vimpl_setImage( VsData * inImage, bool inRgb, unsigned int inFilter,
                                     float inScale, float inBias, int inIndex );
    VSRESULT         vimpl_setPolygon( int inNumVertices, const McVec3f * inVertices, 
                                       const McVec2f * inTexCoords, const int * inTexDims );
    VSRESULT         vimpl_addPolygon( int inNumVertices, const McVec3f * inVertices, 
                                       const McVec2f * inTexCoords, const int * inTexDims );
    void             vimpl_clearPolygons();

    void             setTextureUnit(int inImageIndex, int inUnit);
};

#endif


/// @}
