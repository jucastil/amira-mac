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
#ifndef _VS_TEXTUREDPOLYGON_H_
#define _VS_TEXTUREDPOLYGON_H_

#include "Vs.h"

#include "VsNode.h"
#include "VsData.h"

#include <mclib/McVec3f.h>
#include <mclib/McVec2f.h>

#include <mcgl/mcgl.h>

/** This class implements a textured polygon.

    The purpose of this class is to allow the use of textures 
    with dimensions that exceed the limits of the graphics hardware.
    
    An application may register a large texuture with setImage()
    regardless of hardware restrictions. The texture occasionally
    gets split into multiple tiles and every polygon renderd by means
    of this class will be cut with respect to it's texture coordinates.

    The resulting sub-polygons will then be rendered with the right
    texture tile loaded to the graphics hardware resulting in a
    seamless rendering.

    Note that the implementation will not influence the any texture state
    except for the bound texture object. So be sure to set the right 
    texture stage, texture filtering parameters etc. before calling
    VsTexturedPolygon::render().
*/         
class VSVOLREN_API VsTexturedPolygon
:   public VsNode
{
    VS_DECL_INTERFACE        ( VsTexturedPolygon )
    VS_DECL_INTERFACE_IMPL   ( VsTexturedPolygon )
    VS_DECL_INTERFACE_FACTORY( VsTexturedPolygon )
//  VS_DECL_INTERFACE_RELAY  ( VsTexturedPolygon )

public:

    /// Notifications flags. See VsObject::TouchFlag for details.
    enum TouchFlag
    {
        /// Set if a new texture image was set or the texture image was changed.
        NEW_IMAGE       = 1<<1,
        /// Set if a new polygon was set.
        NEW_POLYGON     = 1<<2
    };

    /** Returns the 3D bounding box of the polygon.
        \param  box
                The 3D bounding box will be returned in this parameter.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT boundingBox( McBox3f & outBox ) const;

    /** Renders the object. 
        \return 
                See VsRenderResult.
    */
    virtual VsRenderResult render();

    /** Frees all OpenGL recources allocated during rendering. 
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT cleanup();

    /** Sets a new texture image to be applied to the rendered polygon.
        \param  inImage
                The new texture image.
        \param  inRgb
                If data is multi-channel image, true specified that the data
                come in RGB / RGBA format, else it is assumed to be BGR / BGRA
        \param  inFilter
                Specifying the texture filtering, e.g. GL_LINEAR or GL_NEAREST
        \param  inScale
                Specifies a scaling that should be applied during texture download
        \param  inBias
                Specifies a bias that should be applied during texture download
        \return
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT setImage(
        VsData      * inImage  = 0
    ,   bool          inRgb    = false
    ,   unsigned int  inFilter = GL_LINEAR
    ,   float         inScale  = 1.0f
    ,   float         inBias   = 0.0f 
    ,   int           inIndex  = 0
    );

    /**
        \param  inImageIndex
                
        \param  inUnit
                >= 0
                -1
                VS_USE_ACTIVE_UNIT
        \return
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    static const int VS_USE_ACTIVE_UNIT = 1000;
    void setTextureUnit( int inImageIndex, int inUnit );


    VsData * image( int inIndex  = 0 ) const;

    /** Sets a new polygon to be rendered with the registered image. The polygon
        may consist of an arbitrary list of vertices. However, currently only
        one polygon is supported.
        \param  inNumVertices
                Number of vertices, the polygon consists of. The arrays pointed
                by \c inVertices and \c inTexCoords are assumed to have 
                \c inNumVertices entries.
        \param  inVertices
                Array of vertex coordinates.
        \param  inTexCoords
                Array of texture coordinates.
        \param  inDims
                Specifies the texture dimension for which the texture coordinates
                in \c inTexCoords have been computed
        \return
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT setPolygon( int inNumVertices, const McVec3f * inVertices, 
                                 const McVec2f * inTexCoords, const int * inDims = 0 );

    /** Add a new polygon to the list of polygons to be rendered with the 
        registered image. The polygon may consist of an arbitrary list of vertices.
        \param  inNumVertices
                Number of vertices, the polygon consists of. The arrays pointed
                by \c inVertices and \c inTexCoords are assumed to have 
                \c inNumVertices entries.
        \param  inVertices
                Array of vertex coordinates.
        \param  inTexCoords
                Array of texture coordinates.
        \param  inDims
                Specifies the texture dimension for which the texture coordinates
                in \c inTexCoords have been computed
        \return
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT addPolygon( int inNumVertices, const McVec3f * inVertices,
                                 const McVec2f * inTexCoords, const int * inDims = 0 );

    /** Clear the list of polygons to be rendered with the registered image. */
    virtual void clearPolygons();

    void copy(const VsTexturedPolygon* other);
};

#endif

/// @}
