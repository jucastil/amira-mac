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
#ifndef _VS_SCENE_MANAGER_IMPL_H
#define _VS_SCENE_MANAGER_IMPL_H

#include "VsSceneManager.h"

#include "VsViewManagerImpl.h"
#include "VsCropRegion.h"

#include <mclib/McPlane.h>
#include <mclib/McVec3f.h>
#include <mclib/McBox3f.h>


class VsSlice;
class VsOverlay;
class VsVolren;
class VsSceneManager;

////////////////////////////////////////////////////////////////////////////////
class VsSceneManagerImpl : public VsViewManagerImpl
{
    VS_IMPLEMENTATION( VsSceneManagerImpl, VsViewManagerImpl, VsSceneManager )
    
public:

    enum PickObject {
        PO_NONE,
        PO_SCOUT_LINE,
        PO_CROP_REGION,
        PO_MEASURE,
        PO_ANNOTATION
    };

    struct PickInfo {
        PickInfo() : type(PO_NONE), info(-1), distance(9999), shape(VsInteractionManager::ArrowCursor) { }

        PickObject                        type;     // the type of object that was picked
        int                               info;     // which object was picked. meaning depends on object type
        float                             distance; // distance in pixels to picked element
        VsInteractionManager::CursorShape shape;    // cursor shape if something was hit
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

    enum CrosshairMode
    {
        CM_ORTHO,
        CM_OBLIQUE
    };

    VsSceneManager::InteractionMode mInteractionMode;
    VsSceneManager::InteractionMode mLastInteractionMode;
    McHandle<VsSlice>               mSlice;
    McHandle<VsOverlay>             mMeasure;
    McHandle<VsOverlay>             mAnnotate;
    McHandle<VsOverlay>             mLastOverlay;
    McHandle<VsVolren>              mVolren;

    float                           mRefSlice;
    McPlane                         mRefPlane;
    VsSceneManager                * mCompanions[4];
    unsigned int                    mSharedCoords[4];
    int                             mConstrainedScout;
    CrosshairMode                   mCrosshairMode;
    McVec3f                         mRotateCenter;
    float                           mRefDataWindowCenter;
    float                           mRefDataWindowWidth;
    McBox3f                         mRefCropBox;
    McVec3f                         mRefPickedPoint;
    int                             mRefPickInfo;
    McHandle<VsCropRegion>          mCropRegion;
    bool                            mLowResSliceInteraction;


public:
    

public:
    ////////////////////////////////////////
    // non-virtual interface methods
    ////////////////////////////////////////
    void setSlice( VsSlice * slice );
    VsSlice * slice() const;
    void setVolren( VsVolren * volren );
    VsVolren * volren() const;
    void setMeasure( VsOverlay * measure );
    VsOverlay * measure() const;
    void setAnnotate( VsOverlay * annotate );
    VsOverlay * annotate() const;
    void setCompanion( VsSceneManager *, int k, unsigned int sharedCoords );
    VsSceneManager * companion( int k ) const;
    VsSceneManager::InteractionMode interactionMode() const;
    void setCropRegion( VsCropRegion * cropRegion );
    VsCropRegion * cropRegion() const;
    void resetOrthoSlicing();
    void setLowResSliceInteraction(bool value);
    bool lowResSliceInteraction() const;
    void panCompanionCameras();
    void changeSlice( int y );
    void crossHair( int x, int y );
    void setSlicePos( int x, int y, int companion = 0);
    bool computeRotateCenter();
    void setCompanionCursorShape( VsInteractionManager::CursorShape shape );
    void updateCursorShape(int x, int y);   
    bool moveCutPlane(int x, int y, int pickInfo);
    bool moveCropSlab(int x, int y, int pickInfo);
    void updateContrast(int x, int y);
    void volumePick(int x, int y);
    void changeSlice3D( float );
    void updatePickingInfoHUD(int x, int y, bool enable);
    void constrainCamera();
    void modifyCropRegion(int x, int y);
    float distanceFromLineSegment(const McVec3f& pw0, const McVec3f& pw1, int x, int y);
    float distanceFromPoint(const McVec3f& p1, int x, int y);
    float distanceOnScreen(const McVec3f& pw0, const McVec3f& pw1);

    static void setCompanionGroup( VsSceneManager *, VsSceneManager *, VsSceneManager *, VsSceneManager * vm3D=NULL );

    // Revised methods
    bool pickedPoint(int x, int y, McVec3f& pWorld);
    bool screenPoint(const McVec3f& pWorld, McVec2f& pScreen);
    VsInteractionManager::CursorShape cursorDependingOnLineSlope(const McVec3f& pworld1, const McVec3f& pworld2);

    bool cutPlanePicked(const McVec3f& pos, int x, int y, PickInfo& pickInfo);
    bool cropSlabPicked(const McVec3f& pos, int x, int y, PickInfo& pickInfo);
    bool cropBoxPicked(const McVec3f& pos, int x, int y, PickInfo& pickInfo);
    bool cornerCutPicked(const McVec3f& pos, int x, int y, PickInfo& pickInfo);
    bool cropRegionPicked(int x, int y, PickInfo& pickInfo);
    bool scoutLinePicked(int x, int y, PickInfo& pickInfo);
    bool annotationPicked(int x, int y, PickInfo& pickInfo);
    bool measurePicked(int x, int y, PickInfo& pickInfo);

private:
    ////////////////////////////////////////
    // virtual interface methods
    ////////////////////////////////////////
    void vimpl_setInteractionMode( VsSceneManager::InteractionMode, bool setCompanionsToo=true );
    bool vimpl_processMouseEvent( Vs::MouseEvent t, int x, int y, Vs::ButtonState state );
    bool vimpl_processKeyEvent( Vs::KeyEvent t, Vs::Key k, Vs::ButtonState state );
    bool vimpl_processWheelEvent( int x, int y, int delta, Vs::ButtonState state );
    bool vimpl_notifySliceWindowChange (float& vmin, float& vmax);
    bool vimpl_notifyVolrenWindowChange(float& vmin, float& vmax);
    bool vimpl_notifyVolrenWindowChange(float& threshold);
    void vimpl_switchMouseMode( int mode, int x, int y );

    ////////////////////////////////////////
    // helper methods
    ////////////////////////////////////////
    void sliceChanged() const;
};

#endif


/// @}
