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
#ifndef SO_SCREEN_H
#define SO_SCREEN_H

#include <hxcore/HxAmiraWinDLLApi.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFRotation.h>

class HxRenderArea;

/** Describes a single screen of multi-wall display system. This class
    represents an SoScreen section as occuring in an AmiraVR config file in
    memory. For a detailed documentation of the meaning of the different
    fields please refer to AmiraVR config file reference documentation. */

class HXCORE_API SoScreenAmiraVR : public SoNode {

    SO_NODE_HEADER(SoScreenAmiraVR);

  public:
    /// Camera modes
    enum CameraMode {
        /// Monoscopic view
        MONOSCOPIC=0,
        /// Left eye view (passive stereo)
        LEFT_VIEW=1,
        /// Right eye view (passive stereo)
        RIGHT_VIEW=2,
        /// OpenGL active stereo view
        ACTIVE_STEREO=3,
        UNDEFINED=4
    };

    /// Modes modifying the standard background settings.
    enum BackgroundMode {
        /// Don't modify the standard background.
        BG_AS_IS=0,
        /// Use a uniform background with lower color.
        BG_LOWER=1,
        /// Use a uniform background with upper color.
        BG_UPPER=2,
        /// Use a gradient background with reversed colors.
        BG_REVERSE=3
    };

    /// Constructor.
    SoScreenAmiraVR();

    /// Name of the screen.
    SoSFString name;

    /// Name of the X11 display (not used on Windows).
    SoSFString display;

    /// Name of the render host (Amira cluster version only)
    SoSFString hostname;

    /// Origin of the graphics window on the desktop.
    SoSFVec2f channelOrigin;

    /// Size of the graphics window on the desktop.
    SoSFVec2f channelSize;

    /// Soft-edge overlaps for the four sides.
    SoMFFloat softEdgeOverlap;

    /// Soft-edge gamma correction factors for the four sides.
    SoMFFloat softEdgeGamma;

    /// Background modification mode.
    SoSFEnum backgroundMode;

    /// Camera mode.
    SoSFEnum cameraMode;

    /// Thread group the screen should belong to.
    SoSFInt32 threadGroup;

    /// Physical coordinates of the lower left corner of the screen.
    SoSFVec3f lowerLeft;

    /// Physical coordinates of the lower right corner of the screen.
    SoSFVec3f lowerRight;

    /// Physical coordinates of the upper left corner of the screen.
    SoSFVec3f upperLeft;

    /// Physical coordinates of the upper right corner of the screen.
    SoSFVec3f upperRight;

    SoSFFloat borderLeft;
    SoSFFloat borderRight;
    SoSFFloat borderBottom;
    SoSFFloat borderTop;

    /// Origin of screen in a virtual graphics window (planar configs only).
    SoSFVec2f tileOrigin;

    /// Size of screen in a virtual graphics window (planar configs only).
    SoSFVec2f tileSize;

    /// Returns true if screen should be rendered on a remote host (cluster version).
    bool isRemoteHost() const;

    /// Returns true if screen describes a planar setup (no corner coords).
    bool isPlanar() const { return planarFlag; }

    /// Returns the physical width of the screen.
    float getScreenWidth() const { return screenWidth; }

    /// Returns the physical height of the screen.
    float getScreenHeight() const { return screenHeight; }

    /// Returns true if screen has a non-default orientation.
    bool hasScreenTransform() const { return hasScreenXform; }

    /** Returns a matrix which transforms the screen into its default orientation.
        Default orientation means, that the lower left corner is positioned
        at the origin (0,0,0) and the the lower right corner is at (w,0,0). */
    const SbMatrix& getScreenTransform() const { return screenXform; }

    /// Returns the inverse of the screen transformation matrix.
    const SbMatrix& getScreenTransformInv() const { return screenXformInv; }

    /// Maps a point defined in physical coords to rotated coordinates.
    void map(const SbVec3f& vrCoords, SbVec3f& rotatedCoords) const;

    /// Returns the position and size of the graphics window on the desktop.
    const SbBox2s& getWindowGeometry() const { return windowGeometry; }

    /** Returns a pointer to the render area associated with this screen.
        If a screen should be rendered on a remote host in a cluster
        configuration then there is no render area associated with the
        screen and a null pointer is returned. */
    HxRenderArea* getRenderArea() const { return renderArea; }

    /// Sets the render area (internal use only).
    void setRenderArea(HxRenderArea*);
    
  SoINTERNAL public:
    static void	initClass();
    
	SbBox3f computeViewVolume(SoGLRenderAction* renderAction, int , int , int w, int h, const SbVec2f &masterViewSize);
	SbVec2i32 convertToPixelUp(const SbVec2f &value, const int w, const int h) const;
	SbVec2i32 convertToPixel(const SbVec2f &value, const int w, const int h) const;

  protected:
    virtual ~SoScreenAmiraVR();
    void computeWindowGeometry();

    HxRenderArea* renderArea;
    SbBox2s windowGeometry;
    float screenWidth;
    float screenHeight;
    SbMatrix screenXform;
    SbMatrix screenXformInv;
    unsigned int planarFlag:1;
    unsigned int hasScreenXform:1;
};

#endif


/// @}
