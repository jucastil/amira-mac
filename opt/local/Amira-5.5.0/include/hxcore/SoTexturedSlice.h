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

/// @addtogroup hxcore hxcore
/// @{
#ifndef SO_TEXTURED_SLICE
#define SO_TEXTURED_SLICE

#include <Inventor/nodes/SoShape.h>
#include <Inventor/SbBox.h>
#include <Inventor/fields/SoSFImage.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/fields/SoSFVec4f.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/elements/SoLazyElement.h>

#include <hxcore/HxAmiraWinDLLApi.h>

#include <mclib/McDArray.h>
#include <mclib/McList.h>
#include <mclib/McTypedData2D.h>
#include <mclib/McHashTable.h>

#include <hxcore/TextureShaders.h>

class SoTexturedSlicePrivate;
class HxPreferences;
class SoProjection;

#pragma warning(push)

// non  DLL-interface classkey 'identifier' used as base for DLL-interface classkey 'identifier'
#pragma warning(disable:4275)

/// Inventor node for drawing faces textured with a non power of 2 image
/// which may be bigger than max-texture-size.
class HXCORE_API SoTexturedSlice : public SoShape
{
    SO_NODE_HEADER( SoTexturedSlice );

public:

    /// Initializes the type
    static void initClass();

    /// Default constructor
    SoTexturedSlice();

    /// render function
    void GLRender( SoGLRenderAction * action );

    /// virtual from base class
    void computeBBox( SoAction * action, SbBox3f & box, SbVec3f & center );

    /// virtual from base class
    void generatePrimitives( SoAction * action );

    /// virtual from base class
    void notify( SoNotList * list );

protected:

    /// Return max texture length
    int getMaxTexLen( SoProjection* projNode );

    /// geometry computation steps (from old GLRender factorization)
    void computeGeometryStep0( SoAction * action, bool extendBound = false );
    
    /// return current grid. Cast to void * due to SoTexturedSlicePrivate
    void * computeGeometryStep1( SoAction * action, int texMaxLen );

public:

    enum ShapeMode
    {
        POLYGON,
        QUADSTRIP
    };

    enum TexFilter
    {
        NEAREST,
        LINEAR,
        MIPMAP
    };

    enum LightModel
    {
        BASE_COLOR = SoLazyElement::BASE_COLOR,
        PHONG      = SoLazyElement::PHONG,
        BUMP
    };

    enum TransparencyMode
    {
        TRANSPARENCY_NORMAL,
        TRANSPARENCY_BINARY
    };

    float bumpDepth;

    float mContrast;
    
    float mBrightness;

    SoMFVec3f   coords;

    SoMFVec2f   texCoords;

    SoSFEnum    shapeMode;

    SoSFEnum    texFilter;

    SoSFImage   image;

    SoSFEnum    lightModel;

    /// value of polygon offset 
    SoSFFloat   offset;

    /// Material property of the slice
    SoSFVec4f   ambientColor;

    /// Material property of the slice
    SoSFVec4f   diffuseColor;

    /// Material property of the slice
    SoSFVec4f   specularColor;

    /// Material property of the slice
    SoSFVec4f   emissiveColor;

    /**
        Choose transparency mode. In mode TRANSPARENCY_NORMAL, transparency is handled by framebuffer blending. In
        TRANSPARENCY_BINARY mode, transparency is handled by an alpha function, transparent fragments are discared, only fully opaque
        fragments get drawn. Default is TRANSPARENCY_NORMAL.
    */
    SoSFEnum transparencyMode;
private:

    /// Destructor
    virtual ~SoTexturedSlice();

    /// private data
    SoTexturedSlicePrivate    * mPrivate;

    /// bounding box
    SbBox3f                     mBound;

    TextureShaders mTextureShaders;

    bool mRequiredGLFeaturesAvailable;

};

#pragma warning(pop)

#endif

/// @}
