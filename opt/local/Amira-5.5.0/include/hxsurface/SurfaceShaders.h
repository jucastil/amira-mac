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
#ifndef _SurfaceShaders_H
#define _SurfaceShaders_H

#include <Inventor/fields/SoMFUInt32.h>
#include <hxsurface/HxSurfaceWinDLLApi.h>

class McShaderParametersMacros;
class McShaderProgram;
class McTexture;

class HXSURFACE_API SurfaceShaders
{
public:
    SurfaceShaders();
    ~SurfaceShaders();
    
    // Setter functions
    void setConfiguration(float vtransFactor, float vtransparency, bool vspecular, bool vfancyAlpha);
    inline void setBackFace(bool backFace) {mUseBackFace = backFace;}
   
    // Binding and unbinding the shaders
    void bindLines(unsigned int context);
    void bindVertex(unsigned int context);
    void bindPatch(unsigned int context);

    void bindVertexAlpha(unsigned int context);
    void bindVertexSimilar(unsigned int context);
    void bindVertexSimilarAlpha(unsigned int context);
    void bind1DTexture(bool discreteTexure, unsigned int context);

    void unBind();

    void setNormal(bool invert);    
    
    /// Texture related functions
    void createTexture(const SoMFUInt32 *colors);
    void destroyTexture();
    bool isTextureCreated();


protected:
    void bindPatchOpaque(unsigned int context);
    void bindPatchFancyAlpha(unsigned int context);

    void bindVertexOpaque(unsigned int context);
    void bindVertexFancyAlpha(unsigned int context);

    void bindVertexSimilarFancyAlpha(unsigned int context);
    void bindVertexSimilarOpaque(unsigned int context);

    void bindVertexAlphaOpaque(unsigned int context);
    void bindVertexAlphaFancyAlpha(unsigned int context);

    void bindVertexSimilarAlphaOpaque(unsigned int context);
    void bindVertexSimilarAlphaFancyAlpha(unsigned int context);

    void bind1DTextureOpaque(unsigned int context);
    void bind1DTextureFancyAlpha(unsigned int context);

    void applyTexture(bool discreteTexure, unsigned int context);

private:
    void createCommunParameters(McShaderParametersMacros *fragmentMacros, bool secondary);
    void enableVertexClip( McShaderParametersMacros* vertexMacros );
        
    // Color Shader
    McShaderProgram *mProgramLines;    
    // Lighting Shader
    McShaderProgram *mProgramSurface;
    
    // General selectors
    bool mFancyAlpha;
    bool mUseBackFace;

    // The Texture colormap
    McTexture *mTexture;
 
};
#endif //_SurfaceShaders_H

/// @}
