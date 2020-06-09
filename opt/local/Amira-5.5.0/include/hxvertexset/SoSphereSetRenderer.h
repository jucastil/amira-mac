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

/// @addtogroup hxvertexset hxvertexset
/// @{
#ifndef SO_SPHERE_SET_RENDERER_H
#define SO_SPHERE_SET_RENDERER_H

#include <mclib/McList.h>
#include <mclib/McVec3i.h>
#include <mclib/McVec3f.h>
#include <mclib/McDArray.h>
#include <mclib/McBitfield.h>
#include <mclib/McHashTable.h>
#include <mclib/McHashTableDouble.h>

#include <Inventor/SbColor.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFUInt32.h>

#include <hxsurface/RefField.h>
#include <hxvertexset/SoSphereDetail.h>
#include <hxvertexset/HxVertexsetWinDLLApi.h>
#include <hxvertexset/TessSphere.h>

#include <hxcore/HxThread.h>
#include <hxcore/hxgl.h>

class SoState;
class SoOutput;
class SoWriteAction;
class SoMaterialBundle;
class SoCoordinateElement;

class SoSphereSet;

class SoSphereSetRenderer {

public:

    // Default color - used if no color is specified.
    static const SbColor defaultColor;

    // Default radius - used if no radius is specified.
    static const float defaultRadius;

    /** Several render functions: PLATES,
        TESSELATED (spheres with phong shading), POINTS. */
    enum RenderFunction{PLATES, TESSELATED, POINTS};
    
    /// Defines which render function is used.
    SoSFEnum renderFunction;

private:
    /// Coordinates of spheres (required).
    RefField<SoMFVec3f, SbVec3f> coords;
    
    /// Selection state (1 bit per sphere, not required).
    RefField<SoMFUInt32, unsigned int> selected;

    /// Highlight state (1 bit per sphere, not required).
    RefField<SoMFUInt32, unsigned int> highlighted;

    // Number of spheres in sphere set.
    int nSpheres;

    // Array of radii - one per sphere.
    McDArray<float> sphereRadii;

    // Color indices are stored in hash table.
    McHashTableDouble<McVec3i, int> colorTable;

    // Indices to color (per sphere).
    McDArray<int> sphereColors;

    // Array of colors.
    McDArray<SbColor> colors;

    // Highlight color
    SbColor highlightColor;

    // Opacity.
    float opacity;

    /* Complexity refers to both the complexity of textures
       in PLATES and DEPTH_BUFFER mode and the complexity 
       of the spheres in TESSELATED mode. */
    float complexity;

    // Point size for rendering spheres as points.
    float pointSize;

    //
    int highlightWidth;

    // owner
    SoSphereSet* m_sphereSet;

    // Geometric information about triangulated spheres.
    McDArray<McDArray<int> > triStrips;
    McDArray<McDArray<int> > triFans;
    McDArray<SbVec3f> vertexNormals;
    McDArray<McDArray<SbVec3f> > coordsPerSp;

    // Struct for texture management in multi-thread mode
    struct TexturesCreateStruct {
        // Indicates if texture objects exit
	int isInitialized;
        // Must be set before accessing this struct
	HxMutex contextMutex;
	// IDs for standard textures.
	McDArray<GLuint> textureNames;
	// IDs for highlight textures.
	McDArray<GLuint> highlightTextureNames;
	// Texture name for highlight color.
	GLuint highlightTextureName;
    };

    // Dictionary storing one texture struct per shared context ID.
    McHashTable<int,TexturesCreateStruct*> texturesCreated;
    // Must be set before accessing texturesCreated.
    HxMutex instanceMutex;

    void setTexturesInternal(unsigned int context);

    // Image for highlight color (texture).
    unsigned char * highlightImage; 

    // List of images (textures).
    McDArray<unsigned char *> images; 

    // List of highlight images (textures).
    McDArray<unsigned char *> highlightImages; 

    // List of free images.
    McDArray<int> freeImages; 
    
    /* There is only one depth image for all images - 
       depth image is scaled appropriately. */
    float *depthImage;
    
    // Sphere struct - _pre and _suc are needed for McList.
    struct Sphere {
        void *_pre;
        void *_suc;
        int id;
        // if _suc == _mcListNullPtr_ then item not in list
        Sphere() { _suc = _mcListNullPtr_; }
    };

    // Each sphere is stored once in the spheres array.
    McDArray<Sphere> spheres;
    /* All spheres of a certain color belong to the list 
       of the corresponding color */
    McDArray<McList<Sphere> > perColorSpheres;
    
    // Keeps track of number of highlighted spheres.
    int nHighlighted;
    // Keeps track of number of selected spheres.
    int nSelected;
    
    // Image size depending on complexity.
    int imageSize;

    // Number of coords.
    int nCoords;

    unsigned int initText:1;
    unsigned int initTess:1;
    unsigned int updateText:1;
    unsigned int updateTess:1;
    unsigned int colorsChanged:1;
    unsigned int sameRadiusForAllSpheres:1;
    unsigned int antiAlias:1;
    unsigned int setInitStateTexturesCreateStruct:1;
    unsigned int linearTextureInterpolation:1;

    /** Modes for unsetting, setting, and toggling selected 
        or highlighted bits. */
    enum BitMode {
        /// Bit should be unset.
        UNSET  = 0,
        /// Bit should be set.
        SET    = 1,
        /// Bit should be toggled.
        TOGGLE = 2
    };

    TessSphere tessSphere;

public:

    /// Constructor.
    SoSphereSetRenderer(SoSphereSet* sphereSet); 
    ~SoSphereSetRenderer();

    void GLRender(SoGLRenderAction *action);
    void computeBBox(SoAction*, SbBox3f &box, SbVec3f &center);
    void generatePrimitives(SoAction *action);
    SoDetail* createTriangleDetail(SoRayPickAction *action,
                                   const SoPrimitiveVertex *v1,
                                   const SoPrimitiveVertex *v2,
                                   const SoPrimitiveVertex *v3,
                                   SoPickedPoint *pp);
    SoDetail* createPointDetail(SoRayPickAction *action,
                                const SoPrimitiveVertex *v1,
                                SoPickedPoint *pp);
    
    /// Set highlight color (default exists).
    void setHighlightColor(SbColor color);
    /// Set number of spheres (required).
    void setNumSpheres(int _nSpheres); 
    /// return the number of spheres.
    int getNumSpheres() const {return coords.getNum();}
    /** Coords can be set by either using the function setCoords
        or directly setting the coords with coords.init(n, dataPtr). */
    void setCoords(int first, int n, const SbVec3f * _coords); 
    /** Set complexity (default exists) (needs to be followed by
        an update()-call. */
    void setComplexity(float comp); 
    /** Set transparency (default is non-transparent). */ 
    void setTransparency(float trans);
    /** Set color for a single sphere (needs to be followed by
        an updata()-call. For each sphere a color must be set 
        by either of the following setColor(s) functions. */
    void setColor(int sphereIdx, SbColor color); 
    /// Set radius for a single sphere (default exists; update() needed).
    void setRadius(int sphereIdx, float radius);
    /// Set point size.
    void setPointSize(float pSize) { pointSize = pSize; }
    /// Enable/disable antialiasing of sphere textures.
    void setAntiAlias(bool onOff);
    /// Enable/disable linear texture interpolation.
    void setLinearTextureInterpolation(bool onOff);
    /// (Un)highlight sphere with given index.
    void highlightSphere(int sphere, int mode);
    /// Select sphere with given index.
    void selectSphere(int sphere, int mode);

    /** Apply changes that have been made, e.g. new colors,
        new complexity, etc. . */
    void update(bool recomputeTextures=false);

    // Sets the line width of the highlighting box (default is 3)
    void setHighlightWidth(int w);

private:

    /// (Un)highlight all spheres.
    void highlightAllSpheres(int mode);
    /// Select all spheres with given indices.
    void selectAllSpheres(int mode);

    /// Return color of sphere.
    SbColor getColor(int i) { return colors[sphereColors[i]]; }

    /** Needs to be called explicitely, if directional 
        has changed. */
    void updateTextures();
    /// Initialization for PLATES and DEPTH_BUFFER rendering.
    void initTextures(SoState *state);
    /// Initialization for TESSELATED rendering.
    void initTessSpheres(SoState *state);
    /// Compute size of texture according to complexity.
    int computeImageSize();
    /// Do what all setColor routines have as first step.
    int preSetColor(SbColor color);
    /// Create new color and return index.
    int getColorIdx(SbColor color);
    /// Returns index of textures.
    int getTexture(SbColor color, int newTexture=0);
    /** Remove texture if last sphere with corresponding color
        has been removed. */
    void removeTexture(int spIdx);
    /// Compute texture for given color.
    unsigned char *computeSphereTextureAntiAliased(SbColor color);
    /// Compute texture for given color.
    unsigned char *computeSphereTexture(SbColor color, int imageSize);
    /// Compute tesselated spheres.
    void computeSpheres();
    /// Change a single sphere.
    void recomputeSphere(int idx);
    /// Remove old textures and compute new ones.
    void recomputeTextures();

    // Rendering routines.
    void GLRenderPlates(SoState *state, unsigned int context); 
    void renderRectangle(int spIdx, SbVec3f &vecX, SbVec3f &vecY);
    //     void GLRenderDepthbuffer(SoState *state);
    void GLRenderTesselated(SoState *state, unsigned int context);
    void renderCube(int spIdx);
    void GLRenderPoints(SoState *state);
    void GLRenderPointsSlow(SoState *state);
    void renderPoint(int spIdx, const SbVec3f* coordsPtr); 

    void generatePlatesPrimitives(SoAction *action,
                                  int spIdx, 
                                  SoSphereDetail &sphereDetail,
                                  SoPrimitiveVertex &pv1,
                                  SbVec3f &vecX, SbVec3f &vecY);
    void generateSpheresPrimitives(SoAction *action,
                                   int spIdx, 
                                   SoSphereDetail &sphereDetail,
                                   SoPrimitiveVertex &pv1);
};

#endif 

/// @}
