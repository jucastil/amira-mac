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

/// @addtogroup hxsurface hxsurface
/// @{
#ifndef _SURFACEVBO_H__
#define _SURFACEVBO_H__

#include <mclib/McVec3f.h>
#include <mclib/McVec4f.h>
#include <mclib/McDArray.h>
#include <mclib/McSmallArray.h>

#include <Inventor/fields/SoMFVec3i32.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFUInt32.h>
#include <Inventor/fields/SoMFFloat.h>

#include <Inventor/fields/SoSFEnum.h>
#include <hxsurface/HxSurfaceWinDLLApi.h>

class SurfaceTypeVBO;
class SurfaceShaders;

class HXSURFACE_API SurfaceVBO  {

public:
    enum colorType {VBO_CONSTANT, VBO_VECTOR, VBO_NOCOLOR, VBO_TEXTURE};
 
    SurfaceVBO();
    ~SurfaceVBO();
    
    // Surface pointers
    SoMFVec3f   *mSurfCoords;
    SoMFVec3i32 *mSurfTri;
    
    // Render functions
    void render(unsigned int context);
    void renderColorLines(unsigned int context);
    void renderSelection(unsigned int context);
    void renderTwoFaces(SurfaceShaders *shaders, unsigned int context);
       
    void BindVBO(unsigned int context);
    void unBindVBO();

    // Coloring type interogations
    inline bool isVectorRender()   {return mSurfaceColoring == VBO_VECTOR;}
    inline bool isTextureRender()  {return mSurfaceColoring == VBO_TEXTURE;}
    inline bool isNoColorRender()  {return mSurfaceColoring == VBO_NOCOLOR;}
    inline bool isConstantRender() {return mSurfaceColoring == VBO_CONSTANT;}

    inline void setWantedColoring(colorType color)  {mSurfaceWantedColoring = color;}

    // Other interogations
    bool isTwoSideColor(unsigned int context);
    bool isColorsBufferCreated(unsigned int context);

    // Set in SoTriSurface
    inline void setCulling(int c) {mCulling  = c;}
    
    void setElementsRender(McDArray<unsigned int> &coordSorting, unsigned int context);
    void setSelectionRender(McDArray<unsigned int> &coordSorting, unsigned int context);
        
    // Set in HxDisplaySurface
    inline void setTransparancy(float t) {mTransparency = t;}
    inline void setSpecular(bool toggle) {mSpecular = toggle;}
    
    // Setting the colors
    void setContantColor(unsigned int color);
    bool setColorVector(const SoMFUInt32 *colors, unsigned int context);    
    
    // The render mode set in draw style
    inline void setRenderMode(GLenum rMode) {mRenderMode = rMode;}

    // Set texture coordonates
    void set1DTextureCoord(const SoMFFloat *texu, bool indexed, unsigned int context);

    // Setting the normals
    bool setFlatNormals  (const SoMFVec3f *vertexNormals, const SoMFUInt32 *colors, unsigned int context);
    bool setVertexNormals(const SoMFVec3f *vertexNormals, const SoMFUInt32 *colors, unsigned int context);
    bool setDirectNormals(const SoMFVec3f *vertexNormals, const SoMFUInt32 *colors, unsigned int context);

    // Touch the buffers functions to be erased
    void newSelection();
    void newColors();
    void newSurface();
    void newElements();
    void newNormals();

    void updateBuffers(unsigned int context);
    
    bool isNewNormals(unsigned int context);
    bool isNewSurface(unsigned int context);
    
    inline bool  isSpecular()      {return mSpecular;}
    float getTransparency();

    bool existElements(unsigned int context);

    void ApplyConstantColor();

private:

    struct STypeSurface
    {
        STypeSurface();
        ~STypeSurface();

        SurfaceTypeVBO* surface;
        bool mNewSelection;
        bool mNewColors;
        bool mNewSurface;
        bool mNewElements;
        bool mNewNormals;
    };

    McDArray<SurfaceVBO::STypeSurface> mSurfaceIndexVBO;

    SurfaceVBO::STypeSurface* getSurfaceIndex( int context );
    void deleteSurfaceIndex( int context );
    
    float mTransparency;
    int   mCulling;
    bool  mSpecular;


    GLenum mRenderMode;
    colorType mSurfaceColoring;  
    colorType mSurfaceWantedColoring;  
    unsigned int mConstantColor;

    bool mVBOBind;
    
    // Helper functions
    void updateColoring(unsigned int context);
    void destroySurface();
 
    void ApplyVectorColor(unsigned int context);
    void ApplyTextureColor(unsigned int context);
};
#endif //_SURFACEVBO_H__

/// @}
