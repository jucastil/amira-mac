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
#ifndef SO_TRI_SURFACE_H 
#define SO_TRI_SURFACE_H

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoMFUInt32.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFVec3i32.h>

#include <hxsurface/SoSurface.h>
#include <hxsurface/Surface.h>

#include <mclib/McVec3f.h>
#include <mclib/McDArray.h>
#include <mclib/McSmallArray.h>


#include <hxsurface/SurfaceVBO.h>
#include <hxsurface/SurfaceShaders.h>

class SoGLRenderAction;


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

class HXSURFACE_API SoTriSurface : public SoSurface {

    SO_NODE_HEADER(SoTriSurface);

  public:
    
    /** Deprecated */
    enum WireframeRenderMode {
        WIREFRAME_LINES,    // Render as Line sets
        WIREFRAME_TRIANGLES // Render as outlined triangles (Default)
    };

      /// Vertex indices of triangles (required).
    SoMFVec3i32 triangles;
    
    /// Constructor.
    SoTriSurface();

    /// Returns the number of elements (triangles or quads).
    virtual int getNumElements() const;

    /// Generate triangle normals.
    void computeTriangleNormals();

    /// Generate vertex normals.
    void computeVertexNormals();

    /// Generate direct normals.
    void computeDirectNormals(float creaseAngle=0.5);
    
    /// Resort triangles (called automatically when number of triangles changed).
    void sortTriangles();

    /// Change selection bit of triangle i (allocates bitfield if necessary).
    void selectTriangle(int i, int mode = SET_BIT) { selectElement(i,mode); }
    
    /// Change selection bits according to selectedTriangles bitfield (allocates bitfield if necessary).
    void selectTriangles(const McBitfield &selectedTriangles) { selectElements(selectedTriangles); }

    /// Change selection bit of all triangles (allocates bitfield if necessary).
    void selectAllTriangles(int mode = SET_BIT) { selectAllElements(mode); }

    /// Change highlight bit of triangle i (allocates bitfield if necessary).
    void highlightTriangle(int i, int mode = SET_BIT) { highlightElement(i,mode); }
    
     /// Change selection bits according to selectedTriangles bitfield(allocates bitfield if necessary).
    void highlightTriangles(const McBitfield &highlightedTriangles) { highlightElements(highlightedTriangles); }

    /// Change highlight bit of all triangles (allocates bitfield if necessary).
    void highlightAllTriangles(int mode = SET_BIT) { highlightAllElements(mode); }

    /// Deprecated
    void setWireFrameRenderMode(WireframeRenderMode mode);
    
    /** Set user-supplied coordinate access callback. This callback is
	used in order to determine the bounding box of visible triangles,
	for the outline and for the highlight render passes, as well as for
	picking (@c generatePrimitives() )..  */
    void setCoordsCB(void (*cb)(int, const float* [3], void*), void* userData);

  SoEXTENDER public:
    // Implements actions
    virtual void GLRender(SoGLRenderAction *action);
    void GLRenderVBO(SoGLRenderAction *action);

  SoINTERNAL public:
    static void	initClass();

    static void useGLMaterial(bool value);

    static bool isGLMaterialUsed();

    virtual void  startNotify();

  protected:
    virtual ~SoTriSurface();

    // Generates triangles representing faces
    virtual void generatePrimitives(SoAction *action);

    // Handles bounding box computation
    virtual void computeBBox(SoAction*, SbBox3f &box, SbVec3f &center);

    void (*getCoords)(int i, const float* coords[3], void* userData);

  private:
    static RenderTemplate renderTable[];
    static RenderTemplate renderEdgeTable[];
    McDArray<int> sortedIdx[3];
    int numSortedPoints;

    void checkNormals();
    void mainLoopSorted(Settings* s);
    void mainLoopUnsorted(Settings* s);
    void mainLoopSortedVBO(Settings* s, unsigned int context);
    void mainLoopUnsortedVBO(Settings* s, unsigned int context);
    
    int getWireframeRenderIndex();

    /// Deprecated
    WireframeRenderMode wireframeRenderMode;

    // User-defined callbacks and render template.
    static void renderDepthUser(Settings* s);
    static void renderDepth(Settings* s);
    static void getCoordsDefault(int i, const float* coords[3], void* userData);

public:
    SurfaceVBO     mSurfaceVBO;
    SurfaceShaders mSurfaceShaders;
    bool mEnableVBO;
    bool mSecondaryColor;
    bool mRequiredGLFeaturesAvailable;
    bool mSurfaceCreationSuccess;

};

#endif

/// @}
