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

/// @addtogroup hxvisageviewer hxvisageviewer
/// @{
#ifndef  EX_ROTATETOOL_H
#define  EX_ROTATETOOL_H

#include "ExModal.h"
#include <mclib/McDArray.h>
#include <mclib/McHandle.h>
#include <vsvolren/McViewVolume.h>
#include "McSphereSheetProjector.h"

#include "VisageViewerWinDLLApi.h"
#include "VsRotationCenterRenderer.h"

class VsSlice;
class McRotation;
class RotRecord;


/** TODO document class
*/
class HXVISAGEVIEWER_API ExRotateTool : public ExModal
{
    /** TODO document struct
    */
    class RotRecord
    {   
    public:
        RotRecord() {}
        RotRecord(ExBaseViewer* viewer, McVec3f & rotCenter);
        ExBaseViewer * mViewer;
        VsSlice *      mSlice; // REVIEW-RK-20060619 better use a HcHandle
        McPlane        mPlane;
        McVec3f        mRotateCenter;
        McVec3f        mCamPos;
        McVec3f        mCamFocus;
        McVec3f        mCamUp;
        McVec3f        mCamViewDir;
        McVec3f        mCamRightDir;
        float          mRotateRadians;
        
    };


public:

    /** constructor
    \param  activeState
            The button state that has to be present that the tool gets into rotation mode.
    */
    ExRotateTool(int /* Vs::ButtonState */ activeState = Vs::BS_LeftButton);
    
    /** Rotate around a custom defined rotation center */
    void enableCustomRotationCenter(bool inFlag) { mCustomRotationCenterEnabled = inFlag; }
    bool isCustomRotationCenterEnabled() { return mCustomRotationCenterEnabled; }
    void setCustomRotationCenter(McVec3f center) { mCustomRotationCenter = center; }
    
    /** Call to begin rotation process.
    \param  viewer
            viewer where the tool is applied to
    \param  x
            current horizontal mouse position
    \param  y
            current vertical mouse position
    */
    void startRotating(ExBaseViewer* viewer, int x, int y);
    void startRotatingVD(ExBaseViewer* viewer, int x, int y);

    /** call to stop rotation process
    */
    void stopRotating(ExBaseViewer* viewer);

    /** rotate camera around a volume.
    \param  viewer
            viewer where the tool is applied to
    \param  x
            current horizontal mouse position
    \param  y
            current vertical mouse position
    \return 
            If the method succeeds, the return value is VS_OK.
    */
    VSRESULT rotateCameraForVolume(ExBaseViewer* viewer, int x, int y);

    /** rotate camera around a slice.
    \param  viewer
            viewer where the tool is applied to
    \param  x
            current horizontal mouse position
    \param  y
            current vertical mouse position
    \return 
            If the method succeeds, the return value is VS_OK.
    */
    VSRESULT rotateCameraForSlice(ExBaseViewer* viewer, int x, int y);

    // REVIEW-RK-20060616 never used
    VSRESULT rotateCameraForSliceOld(ExBaseViewer* viewer, int x, int y);

    VSRESULT rotateCameraVD(ExBaseViewer* viewer, int x, int y);


    ////////////////////////////////////////
    // virtual override methods of ExTool
    ////////////////////////////////////////
    
    virtual bool supports(Ex::ViewerType) const;
    virtual bool isStandard() const;
    virtual const McString identifier() const;


    ////////////////////////////////////////
    // virtual override methods of ExModal
    ////////////////////////////////////////
    
    virtual bool processMouseEvent(ExBaseViewer* viewer, Vs::MouseEvent inEvent, int inX, int inY, Vs::ButtonState inState, Ex::CursorShape& outCursor);
    virtual bool processKeyEvent(ExBaseViewer* viewer, Vs::KeyEvent inEvent, Vs::Key inKey, Vs::ButtonState inState);
    virtual bool processWheelEvent(ExBaseViewer* viewer, int inX, int inY, int inDelta);

    void setRenderRotationCenterMarkerOnMousePress(bool render);

private:

    void rotateSlice( ExBaseViewer* viewer, const McVec2f& delta );
    void rotateSlice( ExBaseViewer* viewer, const McRotation& rot );
    void rotateCurvedSlice( ExBaseViewer* viewer, int x, int y );

    RotRecord * findRotateRecord( ExBaseViewer* viewer );

    void showRotationCenterMarker(ExBaseViewer* viewer, bool show);
    
    enum Mode {
        M_NONE,
        M_ROTATE,
        M_ROTATE_VD
    };

    /// true as long rotation is performed
    Mode                    mMode;

    /// current mouse position in the moment when rotation started
    int                     mLocator[2];

    ///
    McSphereSheetProjector  mSphereSheet;

    ///
    McVec3f                 mRotateCenter;

    ///
    McDArray<RotRecord>     mRotRecords;

    McHandle<VsRotationCenterRenderer> mRotationCenterRenderer;
    bool                    mRenderRotationCenterMarkerOnMousePress;

    ///
    bool                    mIsKeyPressed;

    McVec3f                 mPickedPoint3D;
    McViewVolume            mViewVolume;
    McRotation              mCameraOrientation;
    
    /// 
    McVec3f                 mCustomRotationCenter;
    bool                    mCustomRotationCenterEnabled;
};

#endif // EX_ROTATETOOL_H

/// @}
