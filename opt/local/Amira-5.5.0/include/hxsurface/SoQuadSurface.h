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
#ifndef SO_QUAD_SURFACE_H 
#define SO_QUAD_SURFACE_H

#include <hxcore/hxgl.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFUInt32.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFVec4i32.h>

#include <mclib/McVec3f.h>
#include <mclib/McDArray.h>
#include <hxsurface/SoSurface.h>

#include <hxsurface/HxSurfaceWinDLLApi.h>

class SoGLRenderAction;

/** All-in-one surface node. This Inventor node can be used to display an
    arbitrary set of indexed quads, i.e., quads defined by three
    indices into an array of vertices. In contrast to an ordinary
    SoIndexedFaceSet this class provides the following features:

    

    @li data like vertex coordinates, normals, vertex indices, or colors
	need not to be copied but can be referenced from an existing
	memory location by means of RefField template classes, which
	are derived from Inventor's original SoMField classes

    @li quad outlines can be drawn accurately using OpenGL's polygon
	offset extension

    @li a subset of all quads can be rendered easily by providing a
	bitfield indicating which quads are currently selected

    @li quads can also be highlighted, i.e., drawn in red outlines,
	by providing a second bitfield

    @li either back-face culling or front-face culling can be enabled,
	or culling can be disabled completely

    @li a number of different color modes are supported, e.g. constant
	overall color, different colors for front and back faces,
	per-quads colors, per-vertex color, and direct colors (i.e.,
	three independent colors per quad, one for each vertex)

    @li the surface may be colorized using a 1d-texture map (useful
	for high-quality pseudo-color displays: function values are
	interpolated inside a quad, not colors)

    @li a simple but efficient depth-sorting strategy is provided for
	more accurate display of transparent quads

    @li more realistic display of transparent surface using a fancy alpha
	mode, causing the transparency of a single quad to be adjusted
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

class HXSURFACE_API SoQuadSurface : public SoSurface {

    SO_NODE_HEADER(SoQuadSurface);

  public:
    /// Vertex indices of quads (required).
    SoMFVec4i32 quads;

    /// Constructor.
    SoQuadSurface();

    /// Returns the number of elements (triangles or quads).
    virtual int getNumElements() const;

    /// Generate quad normals.
    void computeQuadNormals();

    /// Generate vertex normals.
    void computeVertexNormals();

    /// Generate direct normals.
    void computeDirectNormals(float creaseAngle=0.5);

    /// Resort quads (called automatically when number of quads changed).
    void sortQuads();

    /// Change selection bit of quad i (allocates bitfield if necessary).
    void selectQuad(int i, int mode = SET_BIT) { selectElement(i, mode); }

    /// Change selection bit of all quads (allocates bitfield if necessary).
    void selectAllQuads(int mode = SET_BIT) { selectAllElements(mode); }

    /// Change highlight bit of quad i (allocates bitfield if necessary).
    void highlightQuad(int i, int mode = SET_BIT) { highlightElement(i, mode); }
    
    /// Change highlight bit of all quads (allocates bitfield if necessary).
    void highlightAllQuads(int mode = SET_BIT) { highlightAllElements(mode); }

    // callbacks
    /** Set user-supplied coordinate access callback. This callback is
	used in order to determine the bounding box of visible quads,
	for the outline and for the highlight render passes, as well as for
	picking (@c generatePrimitives() )..
    */
    void setCoordsCB(void (*cb)(int, const float* [4], void*), void* userData);

  SoEXTENDER public:
    // Implements actions
    virtual void GLRender(SoGLRenderAction *action);

  SoINTERNAL public:
    static void	initClass();

  protected:
    ~SoQuadSurface();

    // Generates quads representing faces
    virtual void generatePrimitives(SoAction *action);

    // Handles bounding box computation
    virtual void computeBBox(SoAction*, SbBox3f &box, SbVec3f &center);

    void (*getCoords)(int i, const float* coords[4], void* userData);

  private:
    static RenderTemplate renderTable[];
    McDArray<int> sortedIdx[3];

    void checkNormals();
    void mainLoopSorted(Settings* s);
    void mainLoopUnsorted(Settings* s);

    // User-defined callbacks and render template.
    static void renderDepthUser(Settings* s);
    static void renderDepth(Settings* s);
    static void getCoordsDefault(int i, const float* coords[4], void* userData);
};


#endif

/// @}
