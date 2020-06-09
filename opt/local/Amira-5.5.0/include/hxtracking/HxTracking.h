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

/// @addtogroup hxtracking hxtracking
/// @{
#ifndef HX_TRACKING_H
#define HX_TRACKING_H

#include <mclib/McFilename.h>

#include <hxcore/HxSettingsModule.h>
#include <hxcore/HxPortButtonMenu.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortGeneric.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortFloatSlider.h>

#include <Inventor/SbLinear.h>

#include <hxtracking/hxtrackingAPI.h>

class SoScreenAmiraVR;
class Hx3DWand;
class HxVREvent;
class HxTrackingPrivate;
class HxVREventHandler;

/** AmiraVR control module managing head-tracking and interaction.
    This is the basic AmiraVR control module. Whenever an AmiraVR
    configuration is activated, a global instance of this class
    will be created. In order to access this instance from other
    modules the global pointer @c theTracking might be used. Note,
    that this pointer is null if no valid license for AmiraVR is
    found. 

    This class provides information about the current VR configuration,
    which is represented by a set of screens (as defined in the
    AmiraVR config file). You can ask for the number of screens
    and get a pointer to each screen in of a configuration. You
    may also get or set the current scene transformation matrix.
    In order to support new interaction schemes, so-called event
    handlers (HxVREventHandler) can be registered and activated.
*/
class HXTRACKING_API HxTracking : public HxSettingsModule {

  HX_HEADER(HxTracking);

  public:
    /// Returns pointer to global instance of the tracking class.
    static HxTracking* getGlobalInstance(bool create=true);

    /// Compute method.
    virtual void compute();

    /// Update method, enables or disables ports.
    virtual void update();

    /// Option menu listing the config files under 'share/config/vr'
    HxPortButtonMenu portConfig;

    enum { CONFIG_RELOAD=0, CONFIG_WRITE=1 };

    /// Text field holding the name of the tracking driver
    HxPortText portTracker;

    /// Action: 0=connect to tracker, 1=calibrate all, 2=pick wand
    HxPortButtonList portAction;

    enum { ACTION_CONNECT=0, ACTION_CALIBRATE=1, ACTION_PICK_WAND=2 };

    /// Mode: 0=navigate, 1=fly mode, 2=mouse control
    HxPortMultiMenu portMode;

    enum { NAVIGATE_MODE=0, FLY_MODE=1, MOUSE_MODE=2 };

    /// Options: 0=show environment, 1=print values, 2=menu, 3=enable wand highlighting
    HxPortToggleList portOptions;
    
    enum { OPT_ENVIRONMENT=0, OPT_VALUES=1, OPT_MENU=2, OPT_HIGHLIGHT=3 };

    /// Virtual-to-real-world scaling factor for the scene.
    HxPortGeneric portScale;
    
    enum { SCALE_MODE=0, SCALE_FACTOR=1 };

    /// Stereo on/off, head tracking on/off
    HxPortToggleList portStereo;

    enum { TOGGLE_STEREO=0, TOGGLE_HEAD_TRACKING=1 };

    /// Position of the left eye with respect to the head tracker, only used in immersive stereo viewing
    HxPortFloatTextN portLeftEyeOffset;
    
    /// Position of the right eye with respect to the head tracker, only used in immersive stereo viewing
    HxPortFloatTextN portRightEyeOffset;

    /// Sets the stereo balance (position of the zero parallax plane), only used in flat stereo viewing
    HxPortFloatSlider portZeroParallaxBalance;

    /// Sets the offset between each view, only used in flat stereo viewing
    HxPortFloatSlider portCameraOffset;

    /// Tcl command interface.
    int parse(Tcl_Interp* t, int argc, char **argv);

    /** Loads a configuration. @c config must be the name of a configuration
        file in either AMIRA_LOCAL/share/config/vr or AMIRA_ROOT/share/config/vr.
        It may also be an absolute file path of an arbitrary AmiraVR config
        file. If config is null, the standard configuration will be loaded.
        The method returns true if the configuration could be sucessfully
        loaded. Otherwise it returns false. */
    static bool loadConfig(const char* config,const char* hostname);

    /** Restores the standard configuration. This method is static. It can
        be called even if no tracking module has yet been created. In this
        case it simply restores the layout and the geometry of the Amira
        main viewer. */
    static void loadStandardConfig();

    /** Writes current configuration into a file. All information including
        the calibration data of the tracking system will be exported. If no
        filename is specified, the file dialog is popped up so that the user
        can interactively choose a filename. The method returns true if the
        config file was successfully written. */
    bool writeConfig(const char* filename);

    /** Returns true if current configuration is a planar one. A planar
        configuration represents a single flat viewer distributed across
        multiple screens. Tracking is not available for planar configurations.
        If a planar configuration is loaded, many ports related to tracking
        will be hidden. */
    bool isPlanarConfig() const;

    /** Returns the SoScreen object currently being rendered. This method
        can be called during rendering to find out which screen is currently
        being rendered. If an ordinary viewer is rendered, e.g., if no
        AmiraVR configuration is active, NULL is returned. */
    static SoScreenAmiraVR* getCurrentScreen();

    /** Returns the SoScreen object of master main viewer. 
        NULL is returned if it is not found in config file*/
    SoScreenAmiraVR* getMasterScreen();

    /** Returns the number of screens of the current VR configuration. If
        the amira standard configuration is active, 0 is returned. */
    int getNumScreens() const;

    /** Returns a pointer to a screen object. For each SoScreen section in
        an amiraVR config file a corresponding object is created. You can
        access these objects via this function, for example, to query the
        physical width or height of a screen. */
    const SoScreenAmiraVR* getScreen(int which) const;

    /** Returns a pointer to the global VR separator node. By default, any
        geometry made visible in a module by calling showGeom() will be
        defined in scene coordinates. Objects defined in scene coordinates
        stay not fixed but are transformed when navigating in 3D. In contrast,
        any geometry inserted into this global VR separator will be defined
        in device coordinates, i.e., in the same coordinate system used in
        the amiraVR config file. Objects defined in device coordinates are
        not transformed when navigating in 3D. Examples are the amiraVR wand
        geometry or the 3D menus. */
    SoSeparator* getVRRoot() const;
    
    /** Returns the value of the near clipping plane in VR coordinates. The
        default value is approximately 1 cm, but scales with the average width
        of all screens in the config file. */
    float getNearPlane() const;

    /// Sets the near clipping plane in VR coordinates.
    void setNearPlane(float value);

    /** Returns the value of the far clipping plane in VR coordinates. The
        default value is approximately 15 m, but scales with the average width
        of all screens in the config file. */
    float getFarPlane() const;

    /// Sets the far clipping plane in VR coordinates.
    void setFarPlane(float value);

    /** Returns the current position of the head sensor. If head tracking is
        disabled the default camera position specified in the config file is
        returned. */
    const SbVec3f& getHeadPosition() const;

    /** Returns the current orientation of the head sensor. If head tracking is
        disabled an identity rotation is returned. */
    const SbRotation& getHeadOrientation() const;

    /// Returns the default object position as specified in the config file.
    const SbVec3f& getDefaultObjectPosition() const;

    /// Returns the left eye offset as specified in the config file.
    const SbVec3f& getLeftEyeOffset() const;

    /// Returns the right eye offset as specified in the config file.
    const SbVec3f& getRightEyeOffset() const;

    /** Matrix which transforms scene coordinates into VR coordinates. Scene
        coordinates are the standard coordinates used in the Amira scene graph.
        VR coordinates are the coordinates used in the AmiraVR config file, i.e.,
        the coordinates the screens of the display system are defined in. This
        matrix changes when the camera of the viewer is changed or when the user
        navigates through the scene. */
    const SbMatrix& getSceneToVRTransform() const;

    /** Matrix which transforms VR coordinates into scene coordinates. This
        matrix changes when the camera of the viewer is changed or when the user
        navigates through the scene. */
    const SbMatrix& getVRToSceneTransform() const;

    /** Sets the matrix which transforms scene coordinates into VR coordinates,
        This method can be called from an event handler class to implement a new
        navigation method. */
    void setSceneToVRTransform(const SbMatrix&);

    /** Sets the menu size in VR coordinates. Size is approximately equal to the
        with of the main 3d menu. */
    void setMenuSize(float size);

    /** Returns the menu size in VR coordinates. */
    float getMenuSize() const;

    /** Makes the 3d wand visible. */
    void showWand();

    /** Hide the 3d wand. */
    void hideWand();

    /** Returns a pointer to the 3d wand. */
    Hx3DWand* getWand();
    
    /** Returns the id of the head tracker specified in the config file. If no
        head tracker was specified, -1 is returned. */
    int getHeadTrackerId() const;

    /** Returns the id of the wand tracker specified in the config file. */
    int getWandTrackerId() const;

    /** Returns true if head tracking is enabled. */
    bool isHeadTrackingEnabled() const;

    /** Enables or disables the 2d mouse mode. In this mode the 2d mouse can
        controlled with the 3d wand. */
    void enableMouseMode(bool onOff);

    /** Checks if the 2d mouse mode is enabled or not. */
    bool isMouseModeEnabled() const;

    /** Activates a registered event handler via its name. If no name is
        specified the default event handler ("pick") will be activated. This
        event handler lets you interact with the 3d menus or with objects in
        the scene graph. If the specified event handler could not be found,
        false is returned, */
    bool setEventHandler(const char* name=NULL); 

    /** Activates the specified event handler. The event handler object must
        not be deleted by the caller after activating it. Amira simply uses
        the event handler but is does not delete it when another handler is
        activated. */
    void setEventHandler(HxVREventHandler* eventHandler);

    /** Registers a new event handler. The event handler object must
        not be deleted by the caller after registering it. After an event
        handler has been registered it can be activated via its name using
        the Tcl interface or using the setEventHandler() method. */
    void registerEventHandler(HxVREventHandler* eventHandler);

    /** Returns a pointer to the current event handler object. */
    HxVREventHandler* getEventHandler() const;

    /** Stops properly a slave */
    void stopSlave(const char* host);

    /** Stop properly all the slave */
    void stopAllSlaves();
    /// Synchronizes the VR configuration files list port with QxTrackingNotifier
    void updateConfigList();

	/** Creates snapshots of each VR Screen and saves each screen to a single file.

		If FileNameBase is given as '/tmp/snapshot.jpg' the resulting files will be

		- '/tmp/snapshot_VR00.jpg'
		- '/tmp/snapshot_VR01.jpg'
		- ...
		- '/tmp/snapshot_VRnn.jpg'

		@returns true if everything went ok.
	*/
	bool snapshotVRScreens(McFilename FileNameBase);

  protected:
    /// Constructor is protected because this is a singleton.
    HxTracking();

    /// Destructor is protected because unref() should be used.
    ~HxTracking();
    
    HxTrackingPrivate* d;

    static void eventCallback(void *userData, HxVREvent* event);

    private:

        /** Returns true if @c host is in the slaves list, otherwise returns false. */
        bool isInSlavesList(const char* host);
};

#define theTracking HxTracking::getGlobalInstance()

#endif

/// @}
