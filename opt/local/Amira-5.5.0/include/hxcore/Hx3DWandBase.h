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
#ifndef HX_3D_WAND_BASE_H
#define HX_3D_WAND_BASE_H

#include <Inventor/SbLinear.h>
#include <mclib/McHandle.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoSeparator.h>
#include <hxcore/HxAmiraWinDLLApi.h>

#define GET_WAND(e) \
    dynamic_cast<Hx3DWandBase*>((Hx3DWandBase*)(e)->trackerInfo().getData())

#pragma warning(push)

// 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
#pragma warning(disable:4251)

/** Base class representing a 3D wand in AmiraVR. If you are writing
    an event callback which reacts on VR events in Amira, i.e., on
    SoTrackerEvent or SoControllerButtonEvent, you can access the wand
    in the following way:

    SoTrackerEvent* e = (SoTrackerEvent*) action->getEvent();
    Hx3DWandBase* wand = GET_WAND(e);

    or

    SoControllerButtonEvent* e = (SoControllerButtonEvent*) action->getEvent();
    Hx3DWandBase* wand = GET_WAND(e);

    You can then ask the wand for its current position or
    orientation. You can also highlight it in order to give some
    visual feedback.

    In addition, the class provides the two static methods sceneXform()
    and sceneXformInverse(). You can use these methods to convert between
    the physical coordinates used in an AmiraVR config file and the scene
    coordinates, e.g., the coordinates a data set is defined in. */
class HXCORE_API Hx3DWandBase
{
  public:
    /** Sets the inventor geometry used to display the wand
        in normal state, as well as the top of the wand. The origin
        is assumed to be at (0,0,0). This can also be specified in a
        permanent way in the AmiraVR config file. */
    void setGeometry(SoNode* wand, const SbVec3f& hotSpot);

    /** Sets the inventor geometry used to display the wand
        in highlighted state. This can also be specified in a
        permanent way in the AmiraVR config file. */
    void setHighlightGeometry(SoNode* wand);

    /** Sets scale factor applied to the wand geometry. The wand
        geometry will be scaled by this factor. The factor allows
        you to adjust the size of the wand so that it matches the
        VR coordinates used in the current AmiraVR config file. For
        example, if your screen width is 200 (cm) and you are
        using a wand geometry with the hot spot at (0,0,-1), a
        wand scale factor of 100 makes the wand half as long as
        your screen. */
    void setWandScale(float scaleFactor);

    /** Returns the scale factor of the wand. The scale factor can
        be defined in the AmiraVR config file. If it is not specified
        there, a default factor will be used which 0.16 times the
        length of the first screen in defined in the config file. */
    float getWandScale() const { return wandScale; }

    /** Highlights the wand. Can be used in custom nodes to give
        some visual feedback. For example, if the top of the wand
        is inside some box this method could be called so that the
        user knows that he can move the box. */
    virtual void setHighlight(bool value);

    /// Returns the current state of a button of the VR input device.
    bool getButton(unsigned int which);

    /// Returns the current state of all buttons of the VR input device.
    int getButtonStatus() { return buttonStatus; }

    /** Returns true if the specified button was pressed since the
        scene graph was traversed the last time by the handle event
        action. */
    bool wasButtonPressed(unsigned int which);

    /** Returns true if the specified button was released since the
        scene graph was traversed the last time by the handle event
        action. */
    bool wasButtonReleased(unsigned int which);

    /** Returns the origin of the 3D wand. If @c scene is true the
        origin is reported in scene coordinates, i.e., the value
        depends on the current viewing transformation. Otherwise the
        origin is reported in VR coordinates, i.e., in the same
        coordinate system used in the amiraVR config file. */
    const SbVec3f& origin(bool scene=true) const { return scene ? _sceneOrigin : _vrOrigin; }

    /** Returns the top of the 3D wand. If @c scene is true the
        top is reported in scene coordinates, i.e., the value
        depends on the current viewing transformation. Otherwise the
        top is reported in VR coordinates, i.e., in the same
        coordinate system used in the amiraVR config file. */
    const SbVec3f& top(bool scene=true) const { return scene ? _sceneTop : _vrTop; }

    /** Returns the current orientation of the wand. If @c scene is
        true the orientation is reported relative to the scene
        cordinate system. Otherwise it is reported relative to the VR
        coordinate system, i.e., the coordinate system used in the
        amiraVR config file. This method can be used to pick and move
        an object with the wand. In order to do so you need to remember
        the current wand top poistion and the current orientation at
        the time the interaction starts, i.e., when a wand button is
        pressed:

        \code
        refRotInverse = wand->orientation().inverse();
        refPos = wand->origin();
        \endcode

        Then, when the wand position and orientation changes you can
        compute a transformation matrix as follows:

        \code
        SbMatrix T1; T1.setTranslate(-refPos);
        SbMatrix R; R.setRotate(refRotInverse*wand->orientation());
        SbMatrix T2; T2.setTranslate(wand->origin());
        SbMatrix deltaXform = T1*R*T2;
        \endcode

        For a concrete example see the module MyVRDemo in the AmiraDev
        demo package. */
    const SbRotation& orientation(bool scene=true) const { return scene ? _sceneOrientation : _vrOrientation; }

    /** Returns the length of the wand. If @c scene is true the length is
        reported in scene coordinates. Otherwise it is reported in VR
        coordinates. The length is the distance between the wand origin
        and the top of the wand. */
    float length(bool scene=true) const { return scene ? _sceneLength : _vrLength; }

    /** Returns the matrix which transforms between scene coordinates
        and VR coordinates, i.e., the coordinates used in the amiraVR
        config file. For example, in order to get the top position of
        the wand in this physical coordinate system use

        \code
        SbVec3f topInDeviceCoords;
        wand->sceneXform().multVecMatrix(wand->top(),topInDeviceCoords);
        \endcode */
    const SbMatrix& sceneXform() const { return *sceneToVRTransform; }

    /** The inverse of sceneXform(). This matrix transforms from device
        coordinates as defined in the amiraVR config file to scene
        coordinates. */
    const SbMatrix& sceneXformInverse() const { return *vrToSceneTransform; }

    /// Updates the 3D wand position (called by HxTracking).
    virtual void update(const SbVec3f& pos, const SbRotation& rot, unsigned int b);

    const SbVec3f& getHotSpot() { return hotSpot; }

    static SoSeparator* getDefaultWandGeometry();
    
protected:
    // Constructor (protected because this is a base class).
    Hx3DWandBase();

    // Destructor (protected because this is a base class).
    virtual ~Hx3DWandBase();

    static SoSeparator* createDefaultWand(unsigned int highlight);

    SbVec3f hotSpot;
    float wandScale;
    McHandle<SoNode> geometry;
    McHandle<SoNode> highlightGeometry;

    float _sceneLength;
    SbVec3f _sceneTop;
    SbVec3f _sceneOrigin;
    SbRotation _sceneOrientation;

    float _vrLength;
    SbVec3f _vrTop;
    SbVec3f _vrOrigin;
    SbRotation _vrOrientation;

    const SbMatrix* sceneToVRTransform;
    const SbMatrix* vrToSceneTransform;

    unsigned int buttonStatus;
    unsigned int lastButtonStatus;
};

#pragma warning(pop)

#endif

/// @}
