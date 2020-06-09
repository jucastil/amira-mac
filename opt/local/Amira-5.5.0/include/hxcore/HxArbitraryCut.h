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
#ifndef HX_ARBITRARY_CUT_H
#define HX_ARBITRARY_CUT_H

#include <hxcore/HxPlanarMod.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortFloatTextN.h> 

#include <mclib/McVec3f.h>
#include <mclib/McDArray.h>

class HxData;
class HxViewer;

class SoSeparator;
class SoCoordinate3;
class SoLineSet;
class SoFaceSet;
class SoQuadMesh;
class SoTransform;
class SoDragger;
class SoEvent;
class SoMatrixTransform;
class SoTranslate1Dragger;
class SoTrackballDragger;
class SoQtViewer;
class SoEventCallback;
class SoSwitch;
class SoMFVec2f;
class SoPickStyle;

class HxRoiInterface;

/** Base class for all arbitrarily orientable cutting plane modules. This
    class provides an Open Inventor trackball dragger which allows the
    user to adjust the orientation of the plane in an intuitive way. The
    plane can also be picked and translated in normal direction. In order
    to work correctly HxModule::portData must be connected to some
    input object of type HxSpatialData. */
    
class HXCORE_API HxArbitraryCut : public HxPlanarMod {

  HX_HEADER(HxArbitraryCut);
  
  public:
    /** Constructor. If @c frameLevel is 0 the orange frame indicating the
        cutting plane is put into the background of the SoDecal node
        of HxPlanarMod. If a derived module provides a background
        itself (e.g. a textured face set) @c frameLevel should be 1. If the
        parameter @c interaction is set to 0 interaction mode (i.e. the 3D
        trackball interface) cannot be activated. This is useful if
        computation of the slice takes very long. */
    HxArbitraryCut(int frameLevel=0, int interaction=1);

    /** Constructor used by derived classes. HxModule::portData is
        configured so that it only can be connected to data objects of the
        type specified by @c ti. The meaning of the two other parameters
        is the same as in the default constructor. */
    HxArbitraryCut(const McTypeInfo* ti, int frameLevel=0, int interaction=1);

    /** Compute method. This method should be called right at the beginning
        of the compute method of a derived module. It handles any changes
        of the ports of this base class. On return, the plane vectors
        HxPlanarMod::origin, HxPlanarMod::uVec, and
        HxPlanarMod::vVec already reflect the new state after the
        orientation has been reset or the plane has been translated. */
    virtual void compute();

    /// Update method.
    virtual void update();

    /// Reset orientation: 0=axial, 1=frontal, 2=sagittal.
    HxPortButtonList portReset;

    /** Options: 0=adjust view, 1=rotate, 2=immediate, 4=fit into points. 
        The rotate toggle shows or hides a trackball dragger which can be
        used to change the orientation of the plane. The third toggle 
        (immediate mode) will only show up if the @c interaction parameter
        of the constructor was set to 1. */
    HxPortToggleList portOptions;

    /** 
     *  Translate slider providing a relative scale between 0..100.
     *  You can change this range by calling @c setTranslateRange.
     */
    HxPortFloatSlider portTranslate;

    // connection port for additional vertex set to change the plane
    HxConnection portVertexSet;

    /// Tcl command interface.
    virtual int parse(Tcl_Interp*, int argc, char** argv);

    /// Saves the state.
    virtual void savePorts(FILE* fp);

    /** Sets a new plane. @c pointOnPlane specifies a point on the plane.
        The rotate dragger will be centered around this point. @c normal
        specifies the plane normal. No check is performed to ensure that
        the plane intersects the bounding box of the data set this module
        is connected to. Suitable uVec() and vVec() vectors lying within
        the plane will be computed automatically. This method updates the
        internal plane representation but does not fire the module or calls
        it compute method. Usually you will explicitely call fire() after
        calling this method.
        The parameter @c absoluteOrientation may be used to specify that the
        defined orientation/position is absolute. If the orientation isn't absolute,
        it will be a local orientation/position.
        */
    void setPlane(const SbVec3f& pointOnPlane, const SbVec3f& normal, bool absoluteOrientation=false);

    /** Sets a new plane. This method is similar to the above method, but
        instead of a normal vector two vectors within the plane need to be
        specified. Some derived modules may interprete the length of these
        vectors.
        The parameter @c absoluteOrientation may be used to specify that the
        defined orientation/position is absolute. If the orientation isn't absolute,
        it will be a local orientation/position.
        */
    void setPlane(const SbVec3f& pointOnPlane, const SbVec3f& u, const SbVec3f& v, bool absoluteOrientation=false);

    /** Shows or hides the orange wireframe around the cutting plane. On
        default the wireframe is drawn as a foreground geometry. It can 
        be deactivated by calling this method with the argument false. */
    void setFrame(bool value);

    /** Returns true if the wireframe is enabled. See setFrame() for more
        details. */
    bool hasFrame() const;

    /** Returns true while the plane is manipulated interactively. This method
        can be called in the compute() method of a derived module. It allows
        you to activate some sort of accelerated low-resolution rendering
        method while the plane is translated or rotated interactively vis its
        Open Inventor dragger. */
    bool isInteractive() const;

    /**
        Returns the bounding box of the Slice volume.
    */
    virtual McBox3f boundingBox();

    /**
        Select a region of interest for the slicing plane.
    */
    HxConnection portRoi;

    /**
     *  Set the absolute range of the @c portTranslate.
     *  It will automatically update the @c portTranslate 
     *  min value to 0 and max value to @c range-1.
    */
    void setTranslateRange(int range);

    /**
     *  Return the absolute translate range.
    */
    int getTranslateRange() {return (int) m_translateRange;}

    /**
     *  Set the minimum Plane point.
     *  The parameter @c isAbsolutePointCoord may be used to specify that the
     *  specified @c point coordinate is absolute. If the point isn't absolute,
     *  it will be a local position. Otherwise, the matrix applied to the input
     *  data will be take in count.
     */
    void setMinPlanePoint(const SbVec3f& point, bool isAbsolutePointCoord=false);

    /**
     *  Set the maximum Plane point
     *  The parameter @c isAbsolutePointCoord may be used to specify that the
     *  specified @c point coordinate is absolute. If the point isn't absolute,
     *  it will be a local position. Otherwise, the matrix applied to the input
     *  data will be take in count.
     */
    void setMaxPlanePoint(const SbVec3f& point, bool isAbsolutePointCoord=false);

    /**
     *  Get the min plane point value.
     */
    inline const SbVec3f& getMinPlanePoint() const {return m_minPlanePoint;}

    /**
     *  Get the max plane point value.
     */
    inline const SbVec3f& getMaxPlanePoint() const {return m_maxPlanePoint;}
    
    /**
    *  Unset the minimum Plane point
    */
    void unsetMinPlanePoint();
    
    /**
    *  Unset the maximum Plane point
    */
    void unsetMaxPlanePoint();

    /**
     *  Compute a point on the plane parallel to the current
     *  arbitrary plane like if the portTranslate value was
     *  @ translate.
     */
    void getPointOnPlane(float translate, SbVec3f& pointOnPlane);

    /**
     *  Save absolute coordinates. If @c saveAbsoluteCoordinates is true, the saved coordinates
     *  which defines this arbitrary cut (the cutting plane plus the min/max plane point)
     *  will be absolute ones. On reload, if coordinates are saved absolutely,
     *  the resulting coordinates will be absolute ones and will take care of the
     *  data transformation so that visually the arbitrary cut is still at the same position.
     *  False by default.
     */
    inline void saveAbsoluteCoordinates(bool saveAbsoluteCoordinates) {m_saveAbsoluteCoordinates = saveAbsoluteCoordinates;}

    /**
     * Return plane length into the plane coordinate system.
     * Optionally, you can also retrieve uMin and vMin coordinates (according to the plane origin).
     */
    virtual void getPlaneLength(float& uLength, float& vLength, float* uMin=0, float* vMin=0);

    /**
     * Show or hide interaction buttons (rotate toggle and fit to points)
     */
    void setInteractionButtonsVisibles(bool onOrOff);

    /**
        Computes sampling parameters. If data sampling is needed under that
        arbitrary cut, use this method to get sampling vectors, sampling origin
        and optionally texture coordinates according to a requested resolution,
        the scale applied to the data and the current plane orientation.
    
        The returned parameters allows to perform an isotrop sampling.  If a
        scale is applied to data, the isotropy parameters are computed
        according to the scale to get a "visual" isotropy.
    
        Texture coordinate are computed in order to be applied on the @c
        frameCoords points.  It means that the @c texCoords input array will be
        resized to fit the @c frameCoords points.
    
        If a projection is applied to this module, this method will
        automatically call getNonIsotropSamplingParameters method and return.
    
        By default isotropic sampling is computed. You can deactivated this
        feature with @c doIsotropSampling.  Furthermore, when doIsotropSampling
        is false, the scale isn't take in account during the computation.
    */
    void getSamplingParameters(const SbVec2i32& sampleRes, SbVec3f& sampleOrigin, 
                               SbVec3f& sampleUVec, SbVec3f& sampleVVec,
                               SoMFVec2f* texCoords = 0, const SbVec2i32* texRes = 0,
                               bool doIsotropSampling = true);

    /**
     *  Return the "portTranslate".
     */
    virtual HxPort* getTranslationPort() {return &portTranslate;}

    /**
     *  Return the "portReset".
     */
    virtual HxPort* getResetToOrthoPlanePort() {return &portReset;}

    /**
     *  Reset the representation to one of the 3 major axes.
     */
    virtual void resetRepToOrthoPlane(OrthoPlane orthoPlane);

   /**
    * Update plane from normal and origin ports
    */
    virtual void updatePlaneFromPorts();


  protected:

    /**
    * Update plane properties (normal, u & v vectors)
    */
    void internalUpdatePlane( bool dontSetTranslateValue );

    struct SortVertex {
        SortVertex(SbVec3f& co) { c = co; }
        float phi;
        SbVec3f c;
        int operator<(const SortVertex& o) const {
            return (phi < o.phi);
        }
        SortVertex& operator=(const SortVertex& o) {
            phi = o.phi;
            c=o.c;
            return *this;
        }
    };

    /// Destructor.
    virtual ~HxArbitraryCut();

    /** This method is derived for internal reasons. If the plane's
        orientation has been reset, i.e., if portReset is new, and if
        the adjust view option of portOption is enabled the camera
        orientation of the main viewer is adjusted in this method after
        calling compute(). */
    virtual int callCompute();

    /// point on minimum bounding plane (normal vector is pNorm)
    SbVec3f             m_minPlanePoint;

    /// point on maximum bounding plane (normal vector is pNorm)
    SbVec3f             m_maxPlanePoint;

    // create a refined shape from vertices
    void createRefinedShape( McDArray<SortVertex> &vertices );

    // Set value of frame width
    bool setFrameWidth(int value);

    // Set value of frame color
    bool setFrameColor(McColor c);

    SoPickStyle         *m_backgroundPickStyle;
    SoSeparator*	    frame;
    SoCoordinate3*	    frameCoords;
    SoFaceSet*	    	frameShape;

    SoSeparator*	    active;
    SoCoordinate3*	    activeCoords;
    SoFaceSet*	    	    activeShape;

    SoSeparator*	        trans;
    SoTransform*	        transXform;
    SoTranslate1Dragger*  transDragger;
    SoSwitch*             transDraggerSwitch;

    SoSeparator*	    orient;
    SoTransform*	    orientXform;
    SoTrackballDragger*     orientDragger;

    SbMatrix          m_dataTransformMtx;
    SbVec3f           m_dataScale;

    SoTransform*      m_resetDataXform;

    float        maxTrans, minTrans, transScale;

    bool applyButtonWasHit;

  private:
    float        m_translateRange;

  protected:
    float	 xMin, xMax, yMin, yMax, zMin, zMax;
    SbVec3f      center;
    unsigned int doUpdate:1;	    // Call compute() in interactive mode ?
    unsigned int interactiveFlag:1; // Indicates interactive manipulation
    unsigned int hasImmediateToggle:1; // Indicates interactive manipulation
    int		 frameLevel;	    // 0=Background, 1=Foreground
    int		 doNotResetPlane;

    // whether Refinement or not (use quadMesh)
    // refinement is used with projections
    bool m_refine;

    void createQuadMesh( McDArray<SortVertex > &vertices , bool doubleQuad = false);

    SoQuadMesh* m_quadMesh;

    McDArray<McVec3f>  pointsInPlane;
    bool         pickModeActivated;
    int          pickEventRegistered;
    void         pointDefinition(SoEventCallback *);

    // Returns 1 if bbox has changed, 0 otherwise
    int newData(HxSpatialData* data, HxRoiInterface* roi);

    bool m_saveAbsoluteCoordinates;
    void	commonInit();
    void	transValueChanged();
    void	transFinish();
    void	orientValueChanged();
    void computePlanePropertiesFromDraggerMatrix(const SbMatrix& draggerMatrix, 
                                                 SbVec3f& normal, SbVec3f& u, SbVec3f& v);
    void computePlaneUAndVFromNormal(SbVec3f& normal, SbVec3f& u, SbVec3f& v);
    void computeRotationMatrixFromPlaneNormal(const SbVec3f& normal, SbMatrix& matrix);
    void	orientFinish();
    void	insertVertex(SbVec3f*, float*, int, const SbVec3f&);
    void 	newOrientation(bool setDraggerRotation = true,bool dontSetTranslateValue = false);
    void	computeFrame(SoCoordinate3*, SoFaceSet*, float offset=0);
    void	updateFrame(); // copy activeShape into frameShape
    void	showFrame();
    void	hideFrame();
    void	setUpDragger(SoTrackballDragger* dragger);
    void  updatePlaneProperties();
    virtual void updateDraggingActiveState();

    /*
     * Get non isotropy sampling parameters. It guarantees that you will have sampleRes[0] in U direction
     * and sampleRes[1] in V direction samples.
     */
    void getNonIsotropSamplingParameters(const SbVec2i32& sampleRes, SbVec3f& sampleOrigin, 
                                         SbVec3f& sampleUVec, SbVec3f& sampleVVec,
                                         SoMFVec2f* texCoords = 0, const SbVec2i32* texRes = 0);

    void computeTexCoords_FirstStep(const SbVec3f& sampleOrigin, 
                                    const SbVec3f& sampleUVec, SbVec3f& sampleVVec, 
                                    SoMFVec2f* texCoords);
    /*
     * @c optionalMaxLength is used only for non isotrop sampling
     */
    void computeTexCoords_SecondStep(SoMFVec2f* texCoords, const SbVec2i32* texRes, 
                                     float xMin, float yMin, float uLength, float vLength);

    void computeBBoxIntersections(const SbLine& line, SbVec3f& firstPoint, SbVec3f& secondPoint, bool useScaledBBox);
    //Parameter dir must be normalized
    bool getBBoxIntersectionWithRayFromInside(const float* box, const SbVec3f& orig, const SbVec3f& dir,
                                              SbVec3f& firstInterPoint, SbVec3f& secondInterPoint) const;

    // static stuff
    static void transStartCB(void*, SoDragger*);
    static void transValueChangedCB(void*, SoDragger*);
    static void transFinishCB(void*, SoDragger*);
    static void orientStartCB(void*, SoDragger*);
    static void orientValueChangedCB(void*, SoDragger*);
    static void orientFinishCB(void*, SoDragger*);
    static SbBool orientToggleCB(const SoEvent*, HxViewer*, void*);
    static void trackerEventCB(void* userData, SoEventCallback*);
    static void controllerEventCB(void* userData, SoEventCallback*);
    static void pointDefCB(void* userData, SoEventCallback*);

    static void getMaxGLClipPlanes(void* userData, SoAction* action);

    
    /**
     * Override this method to hide plane interaction toggles when a projection is activated.
    */
    virtual void projectionActivated();

    /**
    * Override this method to show plane interaction toggles when a projection is activated.
    */
    virtual void projectionDeactivated();

    /**
     *  Here, we re-define this method in order to also hide/show
     *  the "rotate", "immediate" and "fit to points"
     *  check boxes options.
     */
    virtual void setPlaneControllerPortsVisible(bool areVisibles);

    // Number of created ClippingPlane modules. This variable is used to test if
    // number of ClippingPlane modules exceed the maximum number of OpenGL clip plane.
    static int numClippingPlaneModules;

    static int maxGLClipPlanes;
    SoSeparator* maxCPSeparator;
};

#endif

/// @}
