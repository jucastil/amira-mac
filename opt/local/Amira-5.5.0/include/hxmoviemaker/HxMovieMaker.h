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

/// @addtogroup hxmoviemaker hxmoviemaker
/// @{
#ifndef _AMIRA_HxMovieMaker_H_
#define _AMIRA_HxMovieMaker_H_

#include <QObject>

#include <qpixmap.h>
#include <qwidget.h>

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortFilename.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortGeneric.h>
#include <hxcore/HxViewer.h>

#include <hxtime/HxPortTime.h>
#include <hxmoviemaker/HxMovieMakerWinDLLApi.h>

#if defined(USE_WIN_STREAMER)
#include "DSImageStreamer.h"
#endif
#include "MPEGImageStreamer.h"


/**
   Windows/DirectShow module for movie generation.
 */
class HXMOVIEMAKER_API HxMovieMaker : public HxCompModule
{
    HX_HEADER( HxMovieMaker );

public:
    enum Type
    {
        T_UNDEFINED   = -1, // undefined
        T_MONO        =  0, // monoscopic
        T_STEREO_SIDE =  1, // stereo side by side
        T_STEREO_R_C  =  2, // stereo red/cyan
        T_STEREO_B_Y  =  3, // stereo blue/yellow
        T_STEREO_G_M  =  4, // stereo green/magenta
    };

protected:
    ///Saves informations about the state of a viewer prior to shooting.
    struct TViewerResetInfo
    {
        TViewerResetInfo()
            :pViewer(NULL)
        {}

        HxViewer* pViewer;
        int AntiAliasingNPasses;
        SbBool AntiAliasingIsSmoothing;
        bool bInsideOut;
        Type stereoMode;
    };

    ///Mode of shooting
    enum EMovieMakerShootMode
    {
        EMMSM_SingleViewer,
        EMMSM_Panel,
        EMMSM_VRRenderAreas
    };

public:
    /// Constructor
    HxMovieMaker();

    /// Amira virtual compute function
    void compute();

    // Amira virtual update function
    void update();

protected:

    // The destructor should be hidden.
    virtual ~HxMovieMaker();

    /// Tcl-command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

public:
    HxPortMultiMenu         mPortViewer;

    HxPortMultiMenu         mPortMovieFormat;

    HxPortFilename          mPortMovieFilename;
    HxPortIntSlider         mPortFrameNumber;
    HxPortIntSlider         mPortFrameRate;
    HxPortMultiMenu         mPortFixedFrameRate;

    #if defined(USE_WIN_STREAMER)
    HxPortGeneric           mPortCodec;
    #endif

    HxPortFloatSlider       mPortCompQuality;
    HxPortMultiMenu         mPortType;
    HxPortRadioBox          mPortFormat;
    HxPortIntTextN          mPortTiles;
    HxPortRadioBox          mPortSizeFlags;
    HxPortIntTextN          mPortResolution;
    HxPortDoIt              mPortCreateIt;

private:

    #if defined(USE_WIN_STREAMER)
    DSImageStreamer   * mDSStr;
    #endif
    ImageStreamer     * mStreamers[3];

    int                 mCurrentStr;
    int                 mStreamerDepth;
    int                 mStreamerW;
    int                 mStreamerH;
    int                 mCurrentViewer;

    bool                mCanQ;

//    QWidget             mwi;


private:
    ///Returns the currently in our UI selected viewer. May be NULL.
    HxViewer* getSelectedViewer(EMovieMakerShootMode& shootMode);

    ///Sets some viewer attributes thereby saving their original values.
    TViewerResetInfo prepareViewer(HxViewer* pViewer, const Type stereoMode, const int antiAliasing, const bool bUseInsideOut);

    ///Resets viewer attributes to their original values.
    void resetViewers(const McDArray< TViewerResetInfo >& Infos);

    ///Shoots the image content of the given viewer and sends this frame to the current stream.
    bool shootSingleViewer(HxViewer* viewer);

    ///Shoots the image content of the panel and sends this frame to the current stream.
    bool shootPanel();

    ///Shoots the image content of the VR screens and saves each render area in a separate file.
    bool shootVRRenderAreas(const int nFrames, HxPortTime& data, const float subMin, const float subMax, const McFilename& FileNameTemplate);

protected:
    void info();
};

#endif /* __AMIRA_HxMovieMaker_H_ */

/// @}
