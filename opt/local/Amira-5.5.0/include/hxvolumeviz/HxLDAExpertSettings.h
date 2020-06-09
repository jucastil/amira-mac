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

/// @addtogroup hxvolumeviz hxvolumeviz
/// @{
#ifndef HX_LDA_EXPERT_SETTINGS_H
#define HX_LDA_EXPERT_SETTINGS_H

#include <hxcore/HxSettingsModule.h>
#include <hxcore/HxPortSeparator.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortGeneric.h>

#include "HxVolumeData.h"
#include "HxVolumeVizAPI.h"

class QxLDAExpertSettingsNotifier;

#define theLDAExpertSettings HxLDAExpertSettings::getInstance()

class HXVOLUMEVIZ_API HxLDAExpertSettings : public HxSettingsModule
{
    HX_HEADER(HxLDAExpertSettings);

public:
    /// Returns pointer to global instance of the tracking class.
    static HxLDAExpertSettings* getInstance();

    HxPortSeparator  portSepVisualFeedback;

    enum { M_DRAW_TILES=0, M_SLICE_TEXTURES,M_FAKE_DATA, M_LOAD_UNLOAD_TILES};
    HxPortToggleList portVisualFeedback1;

    enum { M_TEXTURE_FRONT_OUTLINE=0, M_DATA_FRONT_OUTLINE, M_VALUATION_OUTLINE};
    HxPortToggleList portVisualFeedback2;

    HxPortSeparator  portSepOptions;

    enum { M_VIEW_CULLING=0, M_VIEWPOINT_REFINEMENT, M_SCREEN_RESOLUTION_CULLING};
    HxPortToggleList portOptions1;

    enum { M_SLICE_EQUAL_RESOLUTION = 0, M_MOVE_LOW_RESOLUTION, M_IGNORE_FULLY_TRANSPARENT_TILES};
    HxPortToggleList portOptions2;

    HxPortIntSlider  portNumLoadingThreads;

    enum { M_NO_INTERACTION=0, M_ALWAYS, M_NEVER};
    HxPortMultiMenu  portOptionsLoadingPolicy;

    HxPortToggleList portOptionFixedResMode;
    HxPortGeneric    portOptionRequestRes;

    HxPortSeparator  portSepMainMemory;
    HxPortIntSlider  portMainMemoryAmount;
    HxPortIntSlider  portMainMemoryNotificationRate;

    HxPortSeparator  portSepVolumeMemory;
    HxPortIntSlider  portVolumeMemoryAmount;
    HxPortIntSlider  portVolumeMemoryTextureLoadRate;

    HxPortSeparator  portSepSliceMemory;
    HxPortIntSlider  portSliceMemoryNumTextures;
    HxPortIntSlider  portSliceMemoryTextureLoadRate;

    /// Compute method.
    virtual void compute();

    void readPreferences();

    /// Update all volume data setting.
    void updateAllVolumes();

    /// Apply current settings to volume data.
    void applySettings(HxVolumeData * volumeData);

    /// Parse the interpreter commandline and execute commands
    virtual int parse (Tcl_Interp *interpreter, int argc, char **argv);

    // Query volume display policy
    bool waitTillVolumeIsLoaded();

public:
    /** Connection point for Qt signals and slots.
      */
    QxLDAExpertSettingsNotifier* const mNotifier;

    /**
     *  This method has been reimplemented in case of LDA preferences has
     *  been modified from the QxPreferenceDialog.
     */
    virtual void preferencesChanged(const HxPreferences& oldPreferences, const HxPreferences& newPreferences);

private:

    /// Constructor is protected because this is a singleton.
    HxLDAExpertSettings();

    /// Destructor is protected because unref() should be used.
    virtual ~HxLDAExpertSettings();

    bool mDrawTiles;
    bool mSliceTextures;
    bool mFakeData;
    bool mLoadUnloadTiles;
    bool mTextureFrontOutline;
    bool mDataFrontOutline;
    bool mValuationOutline;
    bool mViewCulling;
    bool mScreenResolutionCulling;
    bool mViewpointRefinement;
    bool mSliceEqualResolution;
    bool mMoveLowResolution;
    bool mIgnoreFullyTransparentTiles;
    int  mNumLoadingThreads;
    int  mLoadingPolicy;
    bool mFixedResolutionMode;
    int  mRequestedResolution;
    int  mMainMemoryAmount;
    int  mMainMemoryNotificationRate;
    int  mVolumeMemoryAmount;
    int  mVolumeMemoryTextureLoadRate;
    int  mSliceMemoryNumTextures;
    int  mSliceMemoryTextureLoadRate;
    bool mWaitTillVolumeIsLoaded;
};

#endif

/// @}
