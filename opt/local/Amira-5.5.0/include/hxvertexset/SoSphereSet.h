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
#ifndef SO_SPHERE_SET_H
#define SO_SPHERE_SET_H

#include <Inventor/fields/SoMFColor.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFUInt32.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/sensors/SoNodeSensor.h>

#include <mclib/McHandle.h>
#include <hxcore/SoMFBit.h>
#include <hxvertexset/HxVertexsetWinDLLApi.h>

class SoSphereSetRenderer;

/** Open Inventor node for displaying a set of spheres.
	
    This Open Inventor node represents a set of spheres. In order to
    allow quick display of a large number of spheres (up to hundreds
    of thousands) a special rendering technique called {\em plates}
    rendering is provided. Instead of a triangulated polygonal model
    a simple billboard texture with the image a sphere will be rendered.
    While this rendering technique is very fast, there are two drawbacks.
    First, the spheres have a constant depth buffer value. Thus, if
    two spheres intersect each other the image will not be correct.
    Second, since fixed resolution billboard textures are used sampling
    artifacts can be observed when zooming very close to a sphere. To
    avoid these drawbacks at least partially a second rendering technique
    is provided making use of {\em tesselated} spheres. In this case the
    billboard textures are not mapped onto a flat polygon but onto a
    (coarse) polygonal model of a sphere. However, although more precise
    {\em tesselated} rendering is significantly slower than {\em plates}
    rendering.
*/

class HXVERTEXSET_API SoSphereSet : public SoShape {
    
    SO_NODE_HEADER(SoSphereSet);
    
  public:
    
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

    /** Several render functions: PLATES, 
        TESSELATED (spheres with phong shading), 
        POINTS. */
    enum RenderFunction{PLATES, TESSELATED, POINTS};
    
    /// Defines which render function is used.
    SoSFEnum renderFunction;

    /// Coordinates of spheres (required).
    SoMFVec3f coords;
    
    /// radii of spheres.
    SoMFFloat radii;

    /// colors of spheres.
    SoMFColor colors;

    /// Selection state (1 bit per sphere, not required).
    SoMFBit selected;

    /// Highlight state (1 bit per sphere, not required).
    SoMFBit highlighted;

    /// Set highlight color (default exists).
    SoSFColor highlightColor;

    /** Set complexity (default exists) (needs to be followed by
        an update()-call. */
    SoSFFloat complexity;

    /// Set transparency (default is non-transparent).
    SoSFFloat transparency;

    /// point size.
    SoSFFloat pointSize;

    /// line width for highlighting
    SoSFInt32 highlightWidth;

    /// Enable/disable antialiasing of sphere textures.
    SoSFBool antiAlias;

    /// Enable/disable linear texture interpolation.
    SoSFBool linearTextureInterpolation;

    /// Constructor.
    SoSphereSet(); 

    /// Convenience method for initializing multifields (equal length, default values). 
    void setNumSpheres(int num);

    /// Convenience method for setting radii for an interval of spheres.
    void setRadii(float radius, int start=0, int num=-1);

    /// Convenience method for setting same color to an interval of spheres. 
    void setColors(SbColor color, int start=0, int num=-1); 

    /// Convenience method for mapping a color field on spheres. 
    void setColors(const SbColor* colors, int size); 

    /// Convenience method for setting color of highlighted spheres.
    void setColorHighlighted(SbColor color);

    /// Convenience method for selecting all spheres with given indices.
    void selectSpheres(bool mode, int start=0, int num=-1);

    /// Convenience method for (un)highlighting spheres with given indices.
    void highlightSpheres(bool mode, int start=0, int num=-1);
    
  SoEXTENDER public:

    virtual void GLRender(SoGLRenderAction *action);

    // Compute bounding box.
    virtual void computeBBox(SoAction*, SbBox3f &box, SbVec3f &center);

  SoINTERNAL public:
    static void initClass();
    
  protected:
    ~SoSphereSet();
    
    virtual void generatePrimitives(SoAction *action);

    // Enables selecting spheres. 
    virtual SoDetail* createTriangleDetail(SoRayPickAction *action,
                                           const SoPrimitiveVertex *v1,
                                           const SoPrimitiveVertex *v2,
                                           const SoPrimitiveVertex *v3,
                                           SoPickedPoint *pp);
    // Enables selecting points.
    virtual SoDetail* createPointDetail(SoRayPickAction *action,
                                        const SoPrimitiveVertex *v1,
                                        SoPickedPoint *pp);

  private:

    static void fieldSensorCB(void*, SoSensor* sensor);
    void fieldChanged();

    SoSphereSetRenderer* renderer;
    SoNodeSensor sensor;

    friend class SoSphereSetRenderer;
};

#endif // SO_SPHERE_SET_H

/// @}
