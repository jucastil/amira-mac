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
#ifndef _HX_OVERLAY_MODULE
#define _HX_OVERLAY_MODULE

#include <hxcore/HxModule.h>
#include <hxcore/HxPlanarMod.h>
#include <hxcore/HxTightConnection.h>
#include <hxcore/HxPlanarMod.h>

/** Base class for modules referencing a HxPlanarMod module. This class
    merely provides an additional connection port which can be connected to
    a HxPlanarMod module. Usually overlay modules are registered to appear
    in the popup menu of both the actual data object as well as a
    HxPlanarMod module. If an overlay module is created directly for a data
    object, Amira automatically creates a empty plane module too (see
    HxArbitraryCut) and connects it to portModule. */

class HXCORE_API HxOverlayModule : public HxModule {

  HX_HEADER(HxOverlayModule);

  public:

    /**
     *  Define the way how the graphical representation of this module is managed.
     *  See the constructor documentation for more details.
     */
    typedef enum
    {
        MANAGED_BY_BACKGROUND_MOD = 0,  //The graphical representation is managed by the background module.
        MANAGED_BY_VIEWER               //The graphical representation is managed by viewer.
    } GraphicalRepMgtType;

    /**
     *  Constructor.
     *
     *  The optional parameter @c graphicalRepMgtType defines how the graphical
     *  representation is managed by this class.
     *  If the graphical representation is managed as an overlay
     *  (@graphicalRepMgtType = MANAGED_BY_BACKGROUND_MOD) of another module,
     *  the following behavior will be activated :
     *      - The visibility of this module is linked to the visibility of the
     *        background module (see @c m_background).
     *      - The graphical representation is added to the SoDecal node contained
     *        within the background module. It allows to correctly handle polygon offset.
     *
     *  If this module isn't managed as an overlay it means that:
     *      - This module has a viewer toggle
     *        (and so, the visibility isn't linked to the visibility of its background module).
     *      - There is no polygon offset management.
     */
    HxOverlayModule(const McTypeInfo* type, GraphicalRepMgtType graphicalRepMgtType = MANAGED_BY_BACKGROUND_MOD);

    /// Connection to planar module
    HxTightConnection portModule;

    /// Returns portModule as primary port
    virtual int autoConnect(HxObject* primary);

    /// Compute method. It is used to updated bounding box and diagonal of the input data.
    virtual void compute();

  protected:
    virtual ~HxOverlayModule();

    SbVec3f m_dataScale;

    float		m_dataDiagonal;
    float		m_scaledDataDiagonal;

    float   m_inputBBox[6];

    // Pointer to background module defining the plane.
    McHandle<HxPlanarMod> m_background;

    /**
     *  Tell if the graphical representation of this module is managed 
     *  as an overlay of a background module.
     *
     *  Default is MANAGED_BY_BACKGROUND_MOD.
     */
    GraphicalRepMgtType m_graphicalRepMgtType;

    /**
     *  Depending if the graphical representation of this module is managed
     *  by a background module (see @c m_graphicalRepMgtType),
     *  this method will add the graphical representation as an overlay of the background or,
     *  as a node of viewers.
     */
    virtual void showGeom(SoNode *node);

    /**
     *  Depending if the graphical representation management type(see @c m_graphicalRepMgtType),
     *  the graphical representation will be removed from the background module or,
     *  from viewers.
     */
    virtual void hideGeom(SoNode *node);

    /**
     *  Force to show the graphical representation @c node as an overlay of a background node
     *  or, as a standard graphical representation of viewers depending on @c graphicalRepMgtType.
     */
    virtual void showGeom(SoNode *node, GraphicalRepMgtType graphicalRepMgtType);

    /**
     *  Force to hide the graphical representation @c node from a background node
     *  or, from viewers depending on @c graphicalRepMgtType.
     */
    virtual void hideGeom(SoNode *node, GraphicalRepMgtType graphicalRepMgtType);


    /**
        Called when the current background module (m_background) will be destroyed.
        Subclasses that add themselves as overlay to the background must overwrite
        this method to correctly remove themselves again when the background plane
        is changed.
    */
    virtual void removeOverlay() {};

    virtual void computeInputBBox();

    /**
    Get sampling parameter. If you have to sample data under that HxPlanarMod,
    use this method to get sampling vectors, sampling origin according to a 
    requested resolution, the scale applied to the data and the current plane orientation.
    The returned parameters allows to perform an isotrop sampling. 
    If a scale is applied to data, the isotropy parameters are computed
    according to the scale to get a "visual" isotropy.
    If a projection is applied to this module, this method will automatically call 
    getNonIsotropSamplingParameters method and return.
    */
    void getIsotropSamplingParameters(const SbVec2i32& sampleRes, SbVec3f& sampleOrigin, 
                                      SbVec3f& sampleUVec, SbVec3f& sampleVVec);

    /*
     * Get non isotropy sampling parameters. It guarantees that you will have sampleRes[0] in U direction
     * and sampleRes[1] in V direction samples.
     */
    void getNonIsotropSamplingParameters(const SbVec2i32& sampleRes, SbVec3f& sampleOrigin, 
                                         SbVec3f& sampleUVec, SbVec3f& sampleVVec);

    //Compute the length of the BBox diagonal by taking care of current transformation
    void computeDiagonal(const McBox3f& bBox);

    void computeBBoxIntersections(const SbLine& line, SbVec3f& firstPoint, SbVec3f& secondPoint, bool useScaledBBox);
    //Parameter dir must be normalized
    bool getBBoxIntersectionWithRayFromInside(const float* box, const SbVec3f& orig, const SbVec3f& dir,
                                              SbVec3f& firstInterPoint, SbVec3f& secondInterPoint) const;

    /**
    * Override this method to hide plane interaction toggles when a projection is activated.
    */
    virtual void projectionActivated();

    /**
    * Override this method to show plane interaction toggles when a projection is activated.
    */
    virtual void projectionDeactivated();
};

#endif /* _HX_OVERLAY_GRID_ */

/// @}
