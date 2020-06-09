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

/// @addtogroup vsvolren vsvolren
/// @{
#ifndef _VS_SCENE_MANAGER_H_
#define _VS_SCENE_MANAGER_H_

#include "Vs.h"

#include "VsViewManager.h"

#include <mclib/McVec2f.h>


class VsSlice;
class VsVolren;
class VsOverlay;
class VsCropRegion;


/** Standard interaction class for slicing and volume rendering.

    In addition to VsViewManager this class implements interaction
    with three slicing modules. Only one of the slicing modules is
    displayed in this viewer. The two other slices are displayed
    in two companion viewers, which have to be set via the method
    setCompanion(). If the user picks a scout line representing an
    orthogonal slice this slice is updated and the companion viewer
    is touched. */
class VSVOLREN_API VsSceneManager : public VsViewManager
{
    VS_DECL_INTERFACE        ( VsSceneManager )
    VS_DECL_INTERFACE_IMPL   ( VsSceneManager )
    // VS_DECL_INTERFACE_FACTORY( VsSceneManager )
    
public:

    /** Interaction modes beginning with IM_ are permanently active. 
        They can be interupted by an interaction tool, which begin with IT_.
        When the action of the interaction tool has been terminated, the
        former interaction mode will be reactivated. 
    */
    enum InteractionMode 
    {
        /** Standard mouse mode. Allows for picking all pickable elements (scout lines, 
            crop lines, annorations and measurements) with left mouse button. */
        IM_STANDARD,
        /** Window level mouse mode. Allows for setting the window level (contrast and brightness)
            with the left mouse button. Picking elements is not possible. */
        IM_WINDOW_LEVEL,
        /** Volume picking mouse mode. Allows for setting the crosshair by clicking 
            into the 3D viewer. In 2D viewers, this mode behaves as the standard mouse mode. */
        IM_VOLUME_PICK,
        /// adds an annotation
        IT_ANNOTATE,
        /// adds a measurement
        IT_MEASURE,
        /// takes a snapshot
        IT_SNAPSHOT
    };

    enum MouseMode 
    {
        MM_SLICE            = 4,
        MM_CROSSHAIR        = 5,
        MM_CONTRAST_CONTROL = 6,
        MM_CROP_EDIT        = 7,
        MM_MEASURE          = 8,
        MM_ANNOTATION       = 9,
        MM_VOLUME_PICK      = 10
    };


public:

    void setSlice( VsSlice * slice );

    VsSlice * slice() const;

    void setVolren( VsVolren * volren );

    VsVolren * volren() const;

    /** Sets the VsOverlay used for measurements. Allowed to be 0. */
    void setMeasure( VsOverlay * measure );

    /** The VsOverlay that displays and allows interaction with 
        measures in the scene. If no measure is set, 
        or if the measure is not visible(), interaction with
        the measure does not occur, and, for example, mouse cursors
        and key events with respects to the measure overlay elements
        are ignored. */
    VsOverlay * measure() const;

    /** Sets the VsOverlay used for text annotations. Allowed to be 0. */
    void setAnnotate( VsOverlay * annotate );

    /** The VsOverlay that displays and allows interaction with 
        text annotations in the scene.  If no annotation is set, 
        or if the annotation is not visible(), interaction with
        the annotation does not occur, and, for example, mouse cursors
        and key events with respects to the annotation overlay elements
        are ignored. */
    VsOverlay * annotate() const;

    void setCompanion( VsSceneManager *, int k, unsigned int sharedCoords );

    VsSceneManager * companion( int k ) const;

    static void setCompanionGroup( VsSceneManager *, VsSceneManager *, VsSceneManager *, VsSceneManager * vm3D=NULL );

    virtual void setInteractionMode( InteractionMode, bool setCompanionsToo=true );

    InteractionMode interactionMode() const;

    void setCropRegion( VsCropRegion * cropRegion );

    VsCropRegion * cropRegion() const;

    void resetOrthoSlicing();

    virtual bool processMouseEvent( Vs::MouseEvent t, int x, int y, Vs::ButtonState state );

    virtual bool processKeyEvent( Vs::KeyEvent t, Vs::Key k, Vs::ButtonState state );

    virtual bool processWheelEvent( int x, int y, int delta, Vs::ButtonState state );

    void setLowResSliceInteraction(bool value);

    bool lowResSliceInteraction() const;

    float distanceFromLineSegment(const McVec3f& pw0, const McVec3f& pw1, int x, int y);

    float distanceFromPoint(const McVec3f& p1, int x, int y);

    bool screenPoint(const McVec3f& pWorld, McVec2f& pScreen);


protected:

    friend class VsVolpickImpl; // to use pickedPoint();

    void panCompanionCameras();
    void changeSlice( int y );
    void crossHair( int x, int y );
    /// 0 = all companions, 1 only companion 1, 2 only companion 2
    void setSlicePos( int x, int y, int companion = 0);
    bool computeRotateCenter();
    void updateCursorShape(int x, int y);
    bool pickedPoint(int x, int y, McVec3f& pos);
    bool moveCutPlane(int x, int y, int pickInfo);
    bool moveCropSlab(int x, int y, int pickInfo);
    void updateContrast(int x, int y);
    void volumePick(int x, int y);
    void changeSlice3D( float );
    void updatePickingInfoHUD(int x, int y, bool enable);
    void constrainCamera();

    void modifyCropRegion(int x, int y);

    virtual void switchMouseMode( int mode, int x, int y );

public:

    virtual bool notifySliceWindowChange (float& vmin, float& vmax);
    virtual bool notifyVolrenWindowChange(float& vmin, float& vmax);
    virtual bool notifyVolrenWindowChange(float& threshold);
};

#endif

/// @}
