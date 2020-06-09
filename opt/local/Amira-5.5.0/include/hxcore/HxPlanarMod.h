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
#ifndef _HX_PLANAR_MOD_
#define _HX_PLANAR_MOD_

#include <stdlib.h>
#include <limits.h>
#include <Inventor/SbLinear.h>
#include <hxcore/SoAutoClipPlane.h>
#include <Inventor/nodes/SoSeparator.h>
#include <hxcore/SoDecal.h>
#include <hxcore/HxModule.h>
#include <hxcore/HxPort3DPointList.h>
#include <hxcore/HxPortGeneric.h>

#include<mclib/McBox3f.h>
#include<mclib/McDArray.h>

class HxMultiVolumeBase;

// PORTING but useless #include <hxcore/HxPortPlaneOrientation.h>

/// Base class for all cutting plane modules.
class HXCORE_API HxPlanarMod : public HxModule {
    HX_ABSTRACT_HEADER(HxPlanarMod);

  public:

    /// Returns point on plane (lower left corner or center ?)
    SbVec3f origin() { return portOrigin->getValue(); }

    /// Returns base vector in u direction.
    const SbVec3f& uVec() { return puVec; }

    /// Returns base vector in v direction.
    const SbVec3f& vVec() { return pvVec; }

    /// Returns plane normal.
    SbVec3f normal() { return portNormal->getValue(); }

    /// Returns normal of clipping plane
    SbVec3f clippingNormal();

    /// Returns the bounding box of the underlying data set. Is empty if bounding the box is not given.
    virtual McBox3f boundingBox();

    /// Enables Inventor's DELAY mechanism or binary ALPHATEST.
    void setAlphaPolicy(SoDecal::AlphaPolicy policy);

    /// Add some overlay geometry.
    void addOverlay (SoNode* node);

    /// Add some background geometry.
    void addBackground (SoNode* node);

    /// Remove overlay child.
    void removeOverlay (SoNode* node);

    /// Remove background child.
    void removeBackground (SoNode* node);

    /// Show plane.
    void showDecal();

    /// Hide plane.
    void hideDecal();

    /// This may be used by derived modules to check if plane has changed.
    int planeIsNew() const { return changed; }

    /// A dragger may call this to indicate a plane change.
    void planeTouch() { changed = 1; }

    /// Unset plane touched flag.
    void planeUntouch() { changed = 0; }

    /// Inverts the clipping plane.
    void invertClippingPlane();

    /** Returns true if clipping plane is inverted. If the clipping plane
        is inverted all geometry below the plane is clipped. Otherwise
        all geometry above the plane is clipped. */
    bool isClippingPlaneInverted() const { return invert; }

    /**
     *  Returns true if clipping plane is in autoClipping mode, false otherwise
     */
    bool isAutoClippingPlane() const;

    /// Returns true if some other module is clipped by this plane.
    int isClipping() const { return clippedModules.size(); }

    /**
     *  Check if clip plane is already created.
     *  If not, create it
     */
    void createClipPlane();

    /**
     *  Sets the clip plane autoClipping mode.
     *  If auto mode is set, the clipping plane is adjusted to clip the front of the plane related to the camera position,
     *  otherwise the clipping plane uses the HxPlanarMod normal.
     */
    void setAutoClippingPlane( bool autoState );

    /** Reset viewers (not plane) to one of the major axes.
        Set @c orientation to 0,1, or 2 for X, Y, or Z direction.
    */
    void adjustView(int orientation);

    /** This method computes the coordinates of the polygon which is
        the intersection of the bounding box with the current plane.
        The coordinates will be sorted such that when connecting
        consecutive coords the resulting polyhedral line will form the
        polygon boundary.  The offset can be used to compute the
        polygon where the current plane is offset by the @c offset
        value. */
    void computeFrame(   McDArray< SbVec3f > & frameCoords
                       , const float           offset = 0.f );

    /// Planar modules are lightsalmon.
    virtual McColor getIconColor();

    /// Parse method.
    virtual int parse(Tcl_Interp*, int argc, char** argv);

    /** Calls planeUntouch() if necessary. When the plane position
        or orientation is modified by calling one of the planeSet()
        methods below, a flag is set and planeIsNew() returns true.
        This flag is reset in this overloaded method after the
        object's update and compute method have been called and
        after all downstream objects are fired. */
    void fire(int shouldCompute=1);

    /** If set to true an SoPolygonOffset node is inserted into
        the scene graph before all other nodes of the palnar module.
        This allows other modules to draw wireframe graphics into
        the same plane as this module without causing z-buffer
        fighting. On default, polygon offset is disabled because it
        introduces artifacts when enabling clipping planes. */
    void setPolygonOffsetEnabled(bool value);

    /** Checks if the module's geometry is rendered with polygon
        offset enabled or not. */
    bool getPolygonOffsetEnabled() const;

    /**
    * Return plane length into the plane coordinate system ( untransformed and without bounding box care).
    * Optionally, you can also retrieve uMin and vMin coordinates (according to the plane origin).
    * uMin and vMin are the lowest distances of the plane points from origin. 
    */
    virtual void getPlaneLength(float& uLength, float& vLength, float* uMin=0, float* vMin=0)
    {uLength = vLength = 0;}

    /**
     *  Disable or Enable translation mouse dragging.
     *  This method may have no effect in case inherited
     *  classes doesn't have the possibility to drag 
     *  the plane defined by this class.
     *  Default is enabled.
     */
    void enableDragging(bool enableIt);

    /**
     *  Update method. Mostly check if input represents a 2D data.
     *  If yes, it calls virtual methods which will update the module
     *  GUI and graphical representations.
     */
    virtual void update();

    /**
     *  Connect or disconnect to other planarMod by interconnecting portOrigin & portNormal
     *  depending on state flag.
     */
    void connectPlane( HxPlanarMod* planarMod, bool state );

    typedef enum
    {
        XY = 0, // axial/transversal
        XZ = 1, // coronal/frontal
        YZ = 2  // sagital
    } OrthoPlane;

    /**
     *  This method allows this plane and graphical representations
     *  displayed by inherited class over this plane to reset them
     *  to one of the 3 major orthogonal planes.
     */
    virtual void resetRepToOrthoPlane(OrthoPlane orthoPlane) = 0;

    /**
    * Update plane properties from normal & origin
    */
    virtual void updatePlaneFromPorts();

    /**
    *  Port defining plane origin.
    *  This port is a pointer on purpose. See @c HxPort3DPointList for more information.
    */
    HxPort3DPointList* portOrigin;

    /**
    *  Port defining plane normal.
    *  This port is a pointer on purpose. See @c HxPort3DPointList for more information.
    */ 
    HxPort3DPointList* portNormal;

    /// Show or hide frame, set frame width, set frame color.
    HxPortGeneric portFrame;

  protected:
    HxPlanarMod(const McTypeInfo* dataType);
    virtual ~HxPlanarMod();

    /** Sets clipping plane. */
    void planeSet(const SbVec3f& orig, const SbVec3f& uVec,
                  const SbVec3f& vVec, const SbVec3f& norm);

    /** Sets clipping plane. Sets the plane to be parallel to the XY plane
        and have the given origin.*/
    void planeSetXY(const SbVec3f& origin,float u=1,float v=1);
    /** Sets clipping plane. Sets the plane to be parallel to the ZX plane
        and have the given origin.*/
    void planeSetZX(const SbVec3f& origin,float u=1,float v=1);
    /** Sets clipping plane. Sets the plane to be parallel to the ZY plane
        and have the given origin.*/
    void planeSetYZ(const SbVec3f& origin,float u=1,float v=1);
    /// Sets the origin of the clipping plane.
    void planeSetOrig(const SbVec3f& origin);
    /// Initializes the clipping plane to be the XY plane.
    void planeInit() { planeSetXY(SbVec3f(0,0,0)); }
    /// Transforms the clipping plane using the given transformation matrix.
    void transform(const SbMatrix& mat);

    /// Returns true if there are no planar modules in object pool yet.
    int isFirst();

    /// Updates clipping plane considering controlling data
    virtual void updateClipPlane();

    /**
     *  Must be implemented by inherited classes in order to activate
     *  or deactivate plane dragging.
     */
    virtual void updateDraggingActiveState() = 0;

    /**
     *  If the connected data represents a 2D data set,
     *  automatically reset graphical representations to the 
     *  plane defined by the 2D data.
     *  Internally call @c resetRepToOrthoPlane(OrthoPlane orthoPlane).
     */
    virtual void resetRepToOrthoPlane();

    /**
     *  Check if input represents a 2D data.
     */
    virtual bool is2DData();

    /**
     *  Find the 2D plane connected to the portData.
     *  Return false if 2D plane hasn't been found.
     */
    bool find2DPlane();

    /**
     *  Helper method to set visibility of all ports which control 
     *  the plane definition (translation and orientation).
     */
    virtual void setPlaneControllerPortsVisible(bool areVisibles);

    /**
     *  Inherited classes will have to return the port which will
     *  control the plane translation.
     *  Return 0 if such a controller doesn't exist.
     */
    virtual HxPort* getTranslationPort() = 0;

    /**
     *  Inherited classes will have to return the port which will
     *  be in charge of aligning the plane to a XY, XZ or YZ plane.
     *  Return 0 if such a controller doesn't exist.
     */
    virtual HxPort* getResetToOrthoPlanePort() = 0;

    SbVec3f             puVec;
    SbVec3f             pvVec;
    
    unsigned int        changed:1;
    unsigned int        invert:1;
    SoDecal*            decal;
    SoAutoClipPlane*    clipPlane;
    McDArray<HxBase*>   clippedModules;

    McHandle<SoSeparator> m_separator;

    ///To know if we allow plane dragging.
    bool                m_isDraggingEnabled;
    ///To know if the connected is a kind of image
    bool                m_is2DData;

    friend class HxBase;
};

#endif

/// @}
