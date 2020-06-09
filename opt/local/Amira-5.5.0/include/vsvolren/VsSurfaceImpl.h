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
#ifndef _VS_SURFACE_IMPL_H
#define _VS_SURFACE_IMPL_H

#include "VsSurface.h"

#include "VsObjectImpl.h"

#include <mclib/McMat4f.h>


////////////////////////////////////////////////////////////////////////////////
class VsSurfaceImpl : public VsObjectImpl
{
    VS_IMPLEMENTATION( VsSurfaceImpl, VsObjectImpl, VsSurface )
  
public:

    /// Currently supported extension functions
    enum Extensions 
    {
        // Currently no extension is defined
        VS_EX_DUMMY = 0
    };

    // Transformation of the data domain
    McMat4f                         mTransformationMatrix;
    // Culling mode for that surface
    VsSurface::CullingMode          mCullingMode;

public:
    
    ////////////////////////////////////////
    // non-virtual interface methods
    ////////////////////////////////////////

    VSRESULT                        vimpl_boundingBox( McBox3f & outBox );
    VSRESULT                        setTransformationMatrix( const McMat4f & inMatrix );
    VSRESULT                        transformationMatrix( McMat4f & outMatrix ) const;
    VSRESULT                        setCullingMode( const VsSurface::CullingMode inCulling );
    VsSurface::CullingMode          cullingMode() const;


private:

    ////////////////////////////////////////
    // virtual interface methods
    ////////////////////////////////////////

    unsigned int                    vimpl_numPoints() const;
    const McVec3f *                 vimpl_points() const;
    unsigned int                    vimpl_numTriangles() const;
    const VsSurface::Triangle *     vimpl_triangles() const;
    VsSurface::NormalBinding        vimpl_normalBinding() const;
    unsigned int                    vimpl_numNormals() const;
    const McVec3f *                 vimpl_normals() const;
    VsSurface::ColorBinding         vimpl_colorBinding() const;
    unsigned int                    vimpl_numColors() const;
    const McVec4f *                 vimpl_colors() const;
    bool                            vimpl_isTransparent() const;

    void *                          vimpl_extension( int inEnum, void * inData);


private:

    ////////////////////////////////////////
    // local methods
    ////////////////////////////////////////
};

#endif

/// @}
