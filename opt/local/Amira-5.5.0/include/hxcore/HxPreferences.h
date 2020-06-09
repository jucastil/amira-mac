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
#ifndef HX_PREFERENCES_H
#define HX_PREFERENCES_H

#include "HxAmiraWinDLLApi.h"

#include <mclib/McString.h>
#include <mclib/McColor.h>

class HXCORE_API HxPreferences {

public:
    HxPreferences();

    /**
     *  If true, execution of an object's compute method is indicated
     *  graphically. The rectangular connection area of the object's
     *  icon is drawn in red during execution.
     */
    bool drawComputeIndicator;  

    /**
     *  If true, new modules are selected automatically after they have
     *  been created via an object's popup menu.
     */
    bool autoSelectNewModules;

    /**
     *  If true, and if autoSelectNewModules is set selected objects are
     *  deselected before a new object is selected.
     */
    bool deselectPreviouslySelectedModules;

    /**
     *  If true, the object's viewer toggles are drawn on the icon. If not
     *  set, the viewer toggles are only drawn on the object's header bar.
     *  In this case the object must be selected in order to modify the
     *  viewer mask.
     */
    bool drawViewerTogglesOnIcons;

    /**
     *  If true, a 2-pass firing mechanism is used. This mechanism
     *  ensures that in complex networks downstream modules will only be
     *  fired once.
     */
    bool twoPassFiring;

    /**
     *  If true, all objects including hidden once are saved in networks.
     *  Otherwise hidden data objects with no down stream objects attached
     *  to them (such as colormaps) will not be saved. Default is off.
     */
    bool includeUnusedDataObjects;

    /**
     *  If true, old files are overwritten during auto save. This applies to
     *  data objects which need to be saved to file before a network script
    /// can be generated.
     */
    bool overwriteInAutoSave;

    bool doNotShowAnyNews;

    /**
     *  If true, the size and the position of Amira viewer windows will be
     *  included in network files. This results in scripts which are not
     *  fully portable because the screen resolution as well as the size of
     *  the window borders is not the same of all systems. On default, this
     *  option is off.
     */
    bool includeWindowSizeAndPosition;

    /**
     *  If true, Amira checks if there are unsaved data objects before quiting.
     *  If so a message box listing these data objects is displayed. The
     *  user then can save the objects, quit Amira anyway, or cancel the
     *  dialog and return to Amira.
     */
    bool onExitCheckDataSave;

    /**
     *  If true, Amira checks if the network needs to be saved before quitting,
     *  The conditions indicating that the network need to be saved can be
     *  controlled in more detail using the flags below.
     */
    bool onExitCheckNetworkSave;

    /**
     *  If true, the network is marked as dirty when objects are added to or
     *  removed from the object pool.
     */
    bool networkDirtyAddRemove;

    /**
     *  If true, the network is marked as dirty when the transformation of a
     *  spatial data object is changed.
     */
    bool networkDirtyXform;

    /**
     *  If true, the network is marked as dirty when the label of an object
     *  is changed.
     */
    bool networkDirtyLabels;

    /**
     *  If true, the network is marked as dirty when the value of any port is
     *  changed.
     */
    bool networkDirtyPorts;

    /**
     *  If true, axes are labeled axial, coronal, sagittal instead ox xy, xz,
     *  and yz. The medical naming is the default.
     */
    bool axisNamingIsMedical;

    /**
     *  If true, the viewer panel is displayed in a separate top-level
     *  window as in Amira 3.1 and previous versions.
     */
    bool topLevelPanel;

    /**
     *  If true, the console is displayed in a separate top-level window
     *  as in Amira 3.1 and previous versions.
     */
    bool topLevelConsole;

    /**
     *  If true, the help is displayed in a separate top-level window
     *  as in Amira 3.1 and previous versions.
     */
    bool topLevelHelp;

    /**
     *  If true, no macro or module buttons will be displayed in the object
     *  pool in Amira 4.0.
     */
    bool noMacroButtons;

    /**
     *  If true, the DoIt buttons will be displayed in the properties area
     *  in Amira 4.0.
     */
    bool showDoItButtons;

    /**
     *  If true, save GUI layout on exit.
     */
    bool onExitSaveLayout;

    /** Viewer Settings */
    int     viewerBackgroundMode;
    McColor viewerBackgroundColor1;
    McColor viewerBackgroundColor2;


    /**@name Viewer Gadgets. */
    //@{
    /// If true, show the camera trackball.
    bool showCameraTrackball;
    /// The camera trackball position.
    unsigned int cameraTrackballPosition;
    /// If true, auto hide the camera trackball when the mouse leave
    /// the camera trackball viewport.
    bool autoHideCameraTrackball;
    /// If true, show the compass.
    bool showCompass;
    /// The compass position.
    unsigned int compassPosition;
    /// The compass name.
    McString compassName;
    /// If true, auto hide the compass when the mouse leave
    /// the compass trackball viewport.
    bool autoHideCompass;
    //@}

    /**
     *  To show connections as ports in the Properties Area.
     */
    bool showConnectionsAsPortsInGraphView;

    /**@name Shadowing. */
    //@{
    /// 
    unsigned int shadowDefaultStyle;
    ///
    int shadowIntensity;
    ///
    int shadowQuality;
    //@}

    /**
     *  To be in duplicate mode or not.
     */
    bool duplicateMode;

    /**
     *  To activate auto adjust range of colormaps.
     */
    bool autoAdjustRangeOfColormaps;

    /**
     *  If true, the main viewer will be displayed on the left-hand side
     *  as in Amira 4.0 and earlier versions. In Amira 5.0 and later the
     *  default is to display the viewer on the right-hand side.
     */
    bool viewerOnLeftHandSide;

    /**
     *  If true, will enable viewers spin animation by default
     *  as in Amira 4.0 and earlier versions. In Amira 5.0 and later the
     *  default is to disable viewers spin animation.
     */
    bool viewerSpinAnimation;

    /**@name Molecules Preferences. */
    //@{
    ///
    bool molCpkColor;
    ///
    bool molRasmolAaColor;

    ///
    bool molIdCaseSensitive;

    ///
    bool molInfoMolName;
    ///
    bool molInfoGroupName;
    ///
    bool molInfoGroupAtts;
    ///
    bool molInfoExplicitAtts;
    ///
    McString molExplicitAttributes;
    //@}

    /**
     *  The out of core memory (MB) limit.
     */
    unsigned int outOfCoreMemoryLimitMB;

    /**@name LDA Preferences. */
    //@{
    /// Compression type.
    McString ldaCompressionType;
    /// Sampling type.
    int ldaSamplingType;
    /// Tile size in voxels.
    int ldaTileSize;
    /// Border size in voxels.
    int ldaBorderSize;
    /// Viewpoint refinement.
    bool ldaViewpointRefinement;
    /// Move low resolution.
    bool ldaMoveLowRes;
    /// View culling.
    bool ldaViewCulling;
    /// Loading policy
    int ldaLoadingPolicy;
    /// Max main memory
    int ldaMainMemory;
    /// Max video memory
    int ldaVideoMemory;
    /// How volume loading is priorties over slice loading
    float ldaVolumeLoadingPriority;
    /// Volume loading priority handling enabled
    bool ldaVolumeLoadingPriorityEnabled;
    //@}

    /**
     *  The pool view type (tree view, pool, both).
     */
    unsigned int poolView;
    bool         extendedTreeView;

    /**
     *  If true, optimize graphics performance.
     *  If false, reduce memory consumption.
     */
    bool optimSurfaceRendering;

    /**
     *  If false, use shaders and Vector Buffer Objects.
     *  If true, use standard pipeline.
     */
    bool useLegacyRendering;

    /**
     *  If flase, two passes rendering is used.
     *  If true, one pass rendering is used enables front and back faces check in the shader.
     */
    bool useTwoPassRendering;

    /**
     *  If true, a dialog will appear if the surface is too big.
     *  If false, no dialog will appear.
     */
    bool surfaceTooBigWarning;

    /**@name Segmentation Preferences. */
    //@{
    /// 3D draw style.
    McString seg3dDrawStyle;
    /// Selection draw style.
    int segSelectionDrawStyleType;
    /// Selection draw style.
    int segSelectionDrawStyleOpacity;
    /// Last used magic wand settings (lower and upper values, 3dMode, absoluteValues, sameMaterialOnly, fillInterior and seedValue).
    McString segMagicWandSettings;
    /// Last viewer 0 orientation and data flip values (X, Y an Z)
    McString segOrientationAndFlip;
    //@}

    /**
     *  The preset name of the application.
     */
    McString preset;

    /**
     *  The materials database filename.
     */
    McString matDataBase;

    /**
     *  The product mode (Default, Seismic,...)
     */
    McString productMode;

    /**
     *  To show colormap module in the pool.
     */
    bool showColormaps;

    /**
     *  To show the alpha channel editor in the colormap editor.
     */
    bool showColormapAlphaEditor;

    /**@name DICOM Preferences. */
    //@{
    /// Units.
    float dicomUnits;
    /// To anonymize.
    bool dicomAnonymize;
    /// Custom load options.
    McString dicomLoadOptions;
    //@}

    /**@name Seismic Preferences. */
    //@{
    /// Fault sticks Format.
    McString seismicLastFaultSticksFormat;
    /// Fault fault surface Format.
    McString seismicLastFaultSurfaceFormat;
    /// Fault horizon Format.
    McString seismicLastHorizonFormat;
    //@}

    /**@name TeamWork Preferences. */
    //@{
    /// last server name.
    McString teamWorkLastServer;
    /// Last server port.
    int teamWorkLastServerPort;
    /// Last session name.
    McString teamWorkLastSessionName;
    /// Last alias.
    McString teamWorkLastAlias;
    //@}

    /// To set the AmiraVR configurations path
    McString vrConfigsPath;

    /// To set the custom modules directory.
    McString localDir;

    /// To set the demo directory.
    McString demoDir;

    /// To set custom preferences (For modules developed via XPand)
    McString customPreference;

    /**@name Recent documents preferences. */
    //@{
    /// Max number of recent files
    unsigned int maxNbOfRecentFiles;
    /// Max number of recent networks
    unsigned int maxNbOfRecentNetworks;
    //@}

    /**
     *  Show or not projection button.
     *  Actually, this preference just prevents
     *  from using projection by hiding the projection button.
     *  The product will still be able to load networks containing
     *  projection.
     */
    bool showProjectionButtons;


    /**
     * Provenance
     *
     * Store a standard directory for the provenance workspace that
     * is automatically loaded on Amira start if autoLoad is enabled.
     */
    McString provenanceStandardDir;

    /**
     * Enable or disable the automatic loading of the standard provenance workspace.
     */
    bool provenanceAutoLoad;


    /**
     * Disable or enable projection support. If projection is not
     * enabled, networks containing projections can not be loaded.
     * This flag determines if the objects have projection ports
     * or not.
     */
    bool isProjectionEnabled;


    /**
    * Maximum number of threads to be used by compute modules
    * which could make use of multi threading. Later we also 
    * might have maxNumberOfIOThreads etc.
    */
    unsigned int maxNumberOfComputeThreads;

    /**
     * Enable or disable automatic detection of the maximum number of threads
     * to be used by compute modules.
     */
    bool autoDetectNumberOfComputeThreads;

    /**@name Logging Preferences. */
    //@{
    /// Has the user logging allowed?
    bool logEnable;
    /// Shall we ask before sending a log?
    bool logAskBeforeSending;
    /// Has the user seen the initial logging dialog?
    bool logShowInitialDialog;
    /// Time the logs were sent lastly
    time_t logLastSentTime;
    /// Send how often?
    time_t logSendFrequency;
    /// Number of consecutive send failures
    int logNumSendFailures;
    //@}

    /**
     *  Modify preferences to match EarthEdition edition defaults.
     */
    void setEarthEditionDefaults();

    /**
     *  Modify preferences to match EarthEdition edition defaults.
     */
    void setWindEditionDefaults();

    /**
     *  Modify preferences to match EarthEdition edition defaults.
     */
    void setGreenEditionDefaults();

    /**
     *  Check for equality.
     */
    inline bool operator == (const HxPreferences& other) const
    {
        return isEqual(other);
    }

    /**
     *  Check for inequality.
     */
    inline bool operator != (const HxPreferences& other) const
    {
        return !isEqual(other);
    }

protected:

    bool isEqual(const HxPreferences& other) const;
};

#endif

/// @}
