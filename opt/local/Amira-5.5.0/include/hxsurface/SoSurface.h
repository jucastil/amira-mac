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
#ifndef SO_SURFACE_H
#define SO_SURFACE_H

#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFUInt32.h>
#include <Inventor/fields/SoMFFloat.h>
#include <hxcore/hxgl.h>

#ifdef NEWSTYLE_IOSTREAM
#include <iostream>
using std::ostream;
#include <streambuf>
using std::streambuf;
#else
#include <iostream.h>
#endif

#include <mclib/McVec3f.h>
#include <mclib/McDArray.h>
#include <mclib/McBitfield.h>
#include <mclibthreaded/McThreadLocalStorage.h>
#include <hxsurface/HxSurfaceWinDLLApi.h>

#ifdef HX_LITTLE_ENDIAN
    #define AIDX 0
#else
    #define AIDX 3
#endif

class SoGLRenderAction;
class SoProjection;
class SoFieldSensor;

/** All-in-one surface node. This Inventor node can be used to display an
    arbitrary set of indexed triangles, i.e., triangles defined by three
    indices into an array of vertices. In contrast to an ordinary
    SoIndexedFaceSet this class provides the following features:

    @li data like vertex coordinates, normals, vertex indices, or colors
        need not to be copied but can be referenced from an existing
        memory location by means of RefField template classes, which
        are derived from Inventor's original SoMField classes

    @li triangle outlines can be drawn accurately using OpenGL's polygon
        offset extension

    @li a subset of all triangles can be rendered easily by providing a
        bitfield indicating which triangles are currently selected

    @li triangles can also be highlighted, i.e., drawn in red outlines,
        by providing a second bitfield

    @li either back-face culling or front-face culling can be enabled,
        or culling can be disabled completely

    @li a number of different color modes are supported, e.g. constant
        overall color, different colors for front and back faces,
        per-triangles colors, per-vertex color, and direct colors (i.e.,
        three independent colors per triangle, one for each vertex)

    @li the surface may be colorized using a 1d-texture map (useful
        for high-quality pseudo-color displays: function values are
        interpolated inside a triangle, not colors)

    @li a simple but efficient depth-sorting strategy is provided for
        more accurate display of transparent triangles

    @li more realistic display of transparent surface using a fancy alpha
        mode, causing the transparency of a single triangle to be adjusted
        according to its orientation with respect to the view direction

    @li support of user-defined rendering techniques by means of a
        flexible callback mechanism

    In principle, this class can be written into an Inventor file and read
    back again. However, currently this may not work properly if the
    RefField members reference external memory or if user-defined
    render callback are being used.

    This class doesn't use Open Inventor's caching mechanism, i.e., it
    never generates OpenGL display lists. Therefore copying of data is
    avoided and even large surfaces can be displayed. The performance
    penalty turned out not to exceed 10 percent in common cases. For large
    surfaces it can be neglected completely.

*/

#pragma warning(push)

// non  DLL-interface classkey 'identifier' used as base for DLL-interface classkey 'identifier'
#pragma warning(disable:4275)

class HXSURFACE_API SoSurface : public SoShape {

    SO_NODE_HEADER(SoSurface);

  public:
    /// Normal bindings.
    enum NormalBinding {
        /// One normal per triangle.
        TRIANGLE_NORMALS=0,
        /// One normal per indexed vertex.
        VERTEX_NORMALS=1,
        /// Three times as many normals as triangles.
        DIRECT_NORMALS=2
    };

    /** Color bindings. The color binding defines how colors contained in
        the colors field are interpreted. For example, if the color
        binding is TRIANGLE_COLORS it is assumed, that colors
        contains exactly one color for each triangle. If the color binding
        is VERTEX_COLORS, colors must contain one color for each
        vertex defined in coords.

        The bindings VERTEX_INDICES and DIRECT_INDICES are special. In this
        case colors must contain a colormap consisting of exactly 256
        colors. Normalized indices into this colormap (ranging between
        0...1) must be specified in texu, either one for each vertex
        or three for each triangle.

        Another speciality has to be obeyed for TWOSIDED_TRIANGLE_COLORS.
        In this case colors must contain the front color followed by
        the back color for each triangle. In total twice as many colors as
        triangles are expected. If external memory is referenced in
        colors, it is assumed that there is no byte offset between
        the front color and the back color of a single triangle. The byte
        offset between the front color of one triangle with respect to the
        front color of the next one is supposed to be twice the byte offset
        specified in RefFiled::init(int n, T* elements, size_t offset).
        For example, consider the follwoing struct:

        @code
            class Triangle {
                ...
                unsigned int frontColor;
                unsigned int backColor;
                ...
            };
        @endcode

        Then you have to initialize colors using

        @code
            color.init(nTriangles, triangles, sizeof(Triangle)/2);
        @endcode

    */
    enum ColorBinding {
        /// Constant color.
        CONSTANT_COLOR=0,
        /// Constant front and back colors.
        TWOSIDED_CONSTANT_COLOR=1,
        /// One color per triangle.
        TRIANGLE_COLORS=2,
        /// One color per indexed vertex.
        VERTEX_COLORS=3,
        /// Three colors per triangle.
        DIRECT_COLORS=4,
        /// Vertex indices (requires colormap with 256 entries).
        VERTEX_INDICES=5,
        /// Direct indices (requires colormap with 256 entries).
        DIRECT_INDICES=6,
        /// Two colors per triangle.
        TWOSIDED_TRIANGLE_COLORS=7
    };

    /// Alpha modes.
    enum AlphaMode {
        /// Whole surface is opaque.
        OPAQUE_ALPHA=1,
        /// Constant alpha.
        CONSTANT_ALPHA=2,
        /// View-dependent alpha.
        FANCY_ALPHA=3
    };

    /// Depth sorting modes.
    enum SortingMode {
        /// No sorting.
        NO_SORTING=0,
        /// Depth sorting along major axes.
        AXIS_SORTING=1
    };

    /// Culling modes.
    enum CullingMode {
        /// No culling (render both faces).
        NO_CULLING=0,
        /// Cull back faces.
        BACK_FACE=1,
        /// Cull front faces.
        FRONT_FACE=2
    };

    /// Polygon offset modes
    enum PolygonOffsetMode {
        /// Chooses mode automatically
        POLYGON_OFFSET_MODE_AUTO = 0,
        /// Forces a polygon offset
        POLYGON_OFFSET_MODE_ON = 1,
        /// Forbids polygon offset
        POLYGON_OFFSET_MODE_OFF = 2
    };

    /// Coordinates of surface vertices (required).
    SoMFVec3f coords;

    /// Selection state (1 bit per triangle, not required).
    SoMFUInt32 selection;

    /// Highlight state (1 bit per triangle, not required).
    SoMFUInt32 highlight;

    /// In region of interest state (1 bit per triangle, not required).
    SoMFUInt32 inRoi;

    /// Normal vectors (not required).
    SoMFVec3f normals;

    /// Color information (required).
    SoMFUInt32 colors;

    /// Color indices (1d-texture coordinates, required for indexed color modes).
    SoMFFloat texu;

    /// Normal binding.
    SoSFEnum normalBinding;

    /// Color binding;
    SoSFEnum colorBinding;

    /// Defines how transparent triangles are drawn.
    SoSFEnum alphaMode;

    /// Exaggerates view dependence of transparency (currently ignored).
    SoSFFloat alphaFactor;

    /// Specifies sorting mode.
    SoSFEnum sortingMode;

    /// Indicates whether edges should be drawn or not.
    SoSFBool outline;

    /// Edge color.
    SoSFColor outlineColor;

    /// Highlight color.
    SoSFColor highlightColor;

    /// Culling mode.
    SoSFEnum cullingMode;

    /// Enable or disable lighting.
    SoSFBool lighting;

    /// interpolateTexture ? GL_LINEAR : GL_NEAREST
    SoSFBool interpolateTexture;

    /// set to FALSE to prevent caching.
    SoSFBool useDisplayLists;

    /// Polygon offset mode
    SoSFEnum polygonOffsetMode;

    /// Constructor.
    SoSurface();

    /// Modes for unsetting, setting, and toggling selection or highlight bits.
    enum BitMode {
        /// Bit should be unset.
        UNSET_BIT=0,
        /// Bit should be set.
        SET_BIT=1,
        /// Bit should be toggled.
        TOGGLE_BIT=2
    };

    /** Enables the bounding box cache. If @c numberOfTimes is non-zero
        the last bounding box will be used in the Open Inventor method
        computeBBox() and the internal @c numberOfTimes variable will be
        decremented by one. If this variable is zero, the bounding box
        will be computed by looking at the vertices of all selected and
        highlighted faces. This is the default. */
    void enableBBoxCache(int numberOfTimes);

    /// Returns the number of elements (triangles or quads).
    virtual int getNumElements() const { return 0; }

    /// Check whether element i is selected (default is true).
    int isSelected(int i) const {
        return !selection.getNum() || (selection[i/32] & (1<<(i%32)));
    }

    /// Check whether element i is highlighted (default is false).
    int isHighlighted(int i) const {
        return highlight.getNum() && (highlight[i/32] & (1<<(i%32)));
    }

    /// Check whether element i is in ROI (default is true).
    int isInRoi(int i) const {
        return !inRoi.getNum() || (inRoi[i/32] & (1<<(i%32)));
    }

    /// Change selection bit of element i (allocates bitfield if necessary).
    void selectElement(int i, int mode = SET_BIT);
    
    /// Change selection bit of all elements according to selectedElements bitfield (allocates bitfield if necessary).
    void selectElements(const McBitfield &selectedElements); 

    /// Change selection bit of all elements (allocates bitfield if necessary).
    void selectAllElements(int mode = SET_BIT);

    /// Change highlight bit of elements i (allocates bitfield if necessary).
    void highlightElement(int i, int mode = SET_BIT);
    
    /// Change highlight bit of all elements according to highlightedElements bitfield (allocates bitfield if necessary).
    void highlightElements(const McBitfield &highlightedElements);

    /// Change highlight bit of all elements (allocates bitfield if necessary).
    void highlightAllElements(int mode = SET_BIT);

#ifndef NOAMIRA
    /// Returns selected elements in byte stream.
    void getSelectedElements(ostream& out);
#endif

    /// Returns selected elements in bitfield.
    void getSelectedElements(McBitfield& bitfield);

    bool isProjectionActive(){return projectionActive;}

    SoProjection *getCurrentProjection(){return m_lastProjection;}

    /**@name Interface for user-defined rendering techniques. */
    //@{

    /** Render settings. This struct is passed as an argument to the
        actual core rendering function (see below). It stores part
        of the current OpenGL state as well as the triangle to be
        rendered. One instance of the Settings struct will be created
        per thread. */

    struct Settings {
        /// Front color, used to suppress redundant glMaterial() commands.
        unsigned int frontColor;

        /// Back color, used to suppress redundant glMaterial() commands.
        unsigned int backColor;

        /// Factor for fancy transparency (read only).
        float transFactor;

        /// View direction (read only).
        McVec3f viewDir;

        /// Render method used by this thread.
        void (*render)(Settings* s);

        /// User data as provided in setRenderTemplate().
        void* userData;

        /// Index of triangle/quad to be drawn.
        int i;

        /// Stores base transparencies in fancy alpha textured mode.
        float transTable[256];

        /// Stores fancy transparency values.
        unsigned int alphaTable[128];

        /// Texture name to be used for 1d textures.
        GLuint textureName;

        /// discreteTexture ? GL_NEAREST : GL_LINEAR
        bool discreteTexture;

        /// Computes the dot product of a normal vector and the view direction.
        inline float fancyDot(const float* n) {
            float nv = n[0]*viewDir.x + n[1]*viewDir.y + n[2]*viewDir.z;
            if (nv < 0) nv = -nv;
            if (nv > 1) nv = 1;
            return nv;
        }

        /// Computes a fancy alpha value given a dot product and a color.
        inline unsigned int fancyAlpha(const float& dot, unsigned int color) {
            unsigned char* rgba = (unsigned char*) &color;
            if (dot == 0) {
                rgba[AIDX] = 255; // completely opaque
            } else {
                float baseTrans = (255-rgba[AIDX])/255.;
                if (transFactor==1)
                    rgba[AIDX] = (unsigned char) ( 255.*(1-MC_powf(baseTrans,1./dot)) );
                else {
                    float alpha = 1-MC_powf((float)((1-baseTrans)/transFactor),(float)(1./dot))*transFactor;
                    if (alpha>=1)
                        rgba[AIDX] = 255;
                    else if (alpha<=0)
                        rgba[AIDX] = 255;
                    else rgba[AIDX] = (unsigned char) ( 255.*alpha);
                }
            }
            return color;
        }

        /// Computes a fancy alpha value given a normal and a color.
        inline unsigned int fancyAlpha(const float* normal, const unsigned int& color) {
            return fancyAlpha(fancyDot(normal),color);
        }

        /// Looks up a fancy alpha value from the alpha table.
        inline void fancyAlphaTable(const float* normal, const unsigned int& color) {
            const float nv = 127.f*(normal[0]*viewDir.x + normal[1]*viewDir.y + normal[2]*viewDir.z);
            unsigned int i = (unsigned int) fabs(nv);
            if (i>127) i = 127;
            glColor4ub(color>>24,color>>16,color>>8,alphaTable[i]);
        }

        /// Fancy alpha method for used in texture mode.
        inline void fancyAlpha2(const float& cos, const float& baseTrans) {
            if (cos==0)
                glColor4f(1.f,1.f,1.f,1.f);
            else glColor4f(1.f,1.f,1.f,1.f-MC_powf(baseTrans,1.f/cos));
        }

        /// Fancy alpha method for used in texture mode.
        inline void fancyAlpha2(const float* normal, const float& baseTrans) {
            fancyAlpha2(fancyDot(normal),baseTrans);
        }

        /// Bitwise AND of selection and inRoi flags.
        McDArray<unsigned int> selectionAndRoi;

        /// Bitfield pointer (selection, inRoi, selectionAndRoi, or NULL)
        const unsigned int* actualSelection;
    };

    /// This struct defines a specific render mode.
    struct RenderTemplate {

        /// Indicates whether @c glShadeModel(GL_SMOOTH) should be used.
        unsigned int smoothShading;

        /// Indicates whether GL_COLOR_MATERIAL should be used or not.
        unsigned int colorMaterial;

        /** Temporarily activates back-face culling. This flag should be
            set a single triangle has different colors on its front and
            back side and if drawing the front and the back side separately
            is cheaper than disabling GL_COLOR_MATERIAL and changing the
            front and back material parameters explicitely. For the main
            pass back-face culling will be enabled, while for the outlines
            cullingMode will be used. */
        unsigned int twoPassCulling;

        /// Callback used to render triangle i.
        void (*render)(Settings* s);

        /// Called once before rendering the first triangle (may be null).
        void (*renderStart)(Settings* s);

        /// Called once after rendering the last triangle (may be null).
        void (*renderFinish)(Settings* s);

        /// Called to force normal generation (may be null).
        void (*computeNormalsCB)(Settings* s);
    };

    /// Set user-supplied render template.
    void setRenderTemplate(RenderTemplate* renderTemplate, void* userData);

    /** Set render select callback. The render select callback is an
        additional callback which may be defined by the user. It is called
        prior to any OpenGL mode change. In the callback certain certain
        fields of the @c SoSurface class may be evaluated and a proper
        user-defined render template may be specified.
    */
    void setRenderSelectCB(void (*cb)(void*), void* userData);

    /** Set user-defined callback which is invoked after everything else
        has been rendered. The post-render callback is used for example in
        HxDisplaySurface where additional edges, points, and textual
        information has to be displayed. Rendering these things from within
        a callback is convenient because the polygon offset extension is
        active here. */
    void setPostRenderCB(void (*cb)(void*), void* userData);

    /// Set normals flag (eg. when correct normals were set from outside).
    void setNormalsComputed(bool computed);

    //@}

  SoINTERNAL public:
    static void initClass();

  protected:
    // Called when the "normals" field changed
    static void normalFieldChanged(void *, SoSensor *);

    // Detects when the field "normals" changed.
    SoFieldSensor *m_normalSensor;

    virtual ~SoSurface();

    // Generates triangles representing faces
    virtual void generatePrimitives(SoAction *action);

    // Handles bounding box computation
    virtual void computeBBox(SoAction*, SbBox3f &box, SbVec3f &center);

    // Create detailed pick info
    virtual SoDetail* createTriangleDetail(SoRayPickAction *action,
                                           const SoPrimitiveVertex *v1,
                                           const SoPrimitiveVertex *v2,
                                           const SoPrimitiveVertex *v3,
                                           SoPickedPoint *pp);
    
    bool m_normalComputed;

    McDArray<int> sortedIdx[3];
    int doSorted();
    int getRenderIndex();
    const unsigned int* checkSelection(int n, McDArray<unsigned int>& selectionAndRoi);

    // User-defined callbacks and render template.
    void* getCoordsData;
    void* renderSelectData;
    void (*renderSelect)(void* userData);
    void* postRenderData;
    void (*postRender)(void* userData);
    void* userRenderData;
    RenderTemplate* userRenderTemplate;

    // Update OIV correct transparency flag (m_isOivCorrectTransparency)
    void updateOivCorrectTransparencyFlag(SoState* state);
   
    // Check projection
    void checkProjection(SoAction *action);

    void resetProjection(SoAction *action);

    bool projectionActive;

    // stored projection node
    SoProjection *m_lastProjection;

    // Bounding box cache
    int bBoxCacheCounter;
    float xMin, yMin, zMin;
    float xMax, yMax, zMax;

    static RenderTemplate renderTable[];
    static void getViewDirection(McVec3f& viewDir);
    static McThreadLocalStorage<SoSurface::Settings> settingsTLS;

    // True when OIV transparency is set to DELAYED_SORTED_LAYERS_BLEND or 
    // SORTED_LAYERS_BLEND (after having call updateOivCorrectTransparencyFlag method).
    // If true, depth sorting is disabled and, 
    // inherited classes *must not* manage transparency (with OGL calls) by themselves.
    bool m_isOivCorrectTransparency;

  public:
    /// Static version of member field value for the static functions.
    static void initTex(Settings* s);
    static void finishTex(Settings* s);
    static void initAlphaTable(Settings* s);
};

inline void glColor1ui(const unsigned int& value)
{
#ifdef HX_LITTLE_ENDIAN
    const unsigned char* c = (const unsigned char*) &value;
    glColor4ub( c[3],c[2],c[1],c[0] );
#else
    glColor4ubv( (const unsigned char*) &(value) );
#endif
}

inline void glMaterial1ui(const GLenum& face, const unsigned int& color)
{
    const unsigned char* src = (const unsigned char*) &color;
    float dst[4];
#ifdef HX_LITTLE_ENDIAN
    dst[0] = src[3]/255.;
    dst[1] = src[2]/255.;
    dst[2] = src[1]/255.;
    dst[3] = src[0]/255.;
#else
    dst[0] = src[0]/255.;
    dst[1] = src[1]/255.;
    dst[2] = src[2]/255.;
    dst[3] = src[3]/255.;
#endif
    ::glMaterialfv(face, GL_AMBIENT_AND_DIFFUSE, dst);
}

#pragma warning(pop)

#endif

/// @}
