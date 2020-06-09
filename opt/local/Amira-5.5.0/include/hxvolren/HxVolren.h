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

/// @addtogroup hxvolren hxvolren
/// @{
#ifndef HX_VOLREN_H
#define HX_VOLREN_H

#include <QCursor>
#include <QDataStream>

#include "hxvolrenAPI.h"
#include "SxVolren.h"
#include "QxCleanupTimer.h"
#include "HxPortGenericMaterial.h"

#include <mcgl/mcgl.h>

#include <mclib/McHandle.h>
#include <mclib/McHashTable.h>
#include <mclib/McMat4f.h>
#include <mclib/McVec2f.h>

#include <hxcore/HxBase.h>
#include <hxcore/HxModule.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortGeneric.h>
#include <hxcore/HxPortSeparator.h>
#include <hxcore/HxPortTabBar.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcolor/HistogramProviderModuleIface.h>

#include <hxcolor/HxPortColormap.h>

#include <hxfield/HxRegColorField3.h>
#include <hxfield/HxUniformScalarField3.h>

#include <hxfield/HxMultiChannelField3.h>
#include <hxfield/HxPortMultiChannel.h>

#include <vsvolren/VsColorTable.h>
#include <vsvolren/VsVolume.h>
#include <vsvolren/VsVolren.h>
#include <vsvolren/VsCropRegion.h>
#include <vsvolren/VsCornerCut.h>
#include <vsvolren/VsMemoryData.h>
#include <vsvolren/McVec3l.h>

class SxVolren;

class HXVOLREN_API HxVolren
:   public HxModule
{
    HX_HEADER( HxVolren );

    class HistogramProvider : public HistogramProviderModuleIface {
      public:
        HistogramProvider(HxVolren* o);

        virtual McHandle<McHistogram> getHistogram(unsigned int numBins, HxPortColormap* const colormap);
        virtual McHandle<McHistogram> getHistogramAsync(unsigned int numBins, HxPortColormap* const portColormap);
      private:
        HxVolren* mVolren;
    };

    int               sCallDepth;
    HistogramProvider mHistogramProvider;
public:

    enum Mode
    {
        RM_VRT = 0
    ,   RM_DRR
    ,   RM_MIP   
    ,   RM_NUM
    };

    enum ModePort
    {
        COMMON_MODE_RADIO_GROUP = 0
    ,   COMMON_MODE_CHECKBOX
    };

    enum PhongFactors
    {
        PF_AMBIENT = 0
    ,   PF_DIFFUSE
    ,   PF_SPECULAR
    ,   PF_NUM
    };

    enum PhongPresets
    {
        PP_VRT = 0
    ,   PP_DIFF
    ,   PP_SVRT
    ,   PP_USER
    ,   PP_NUM
    };

    enum LightPresets
    {
        LP_TOP_LEFT = 0
    ,   LP_BOTTOM_LEFT
    ,   LP_BOTTOM_RIGHT
    ,   LP_TOP_RIGHT
    ,   LP_USER
    ,   LP_NUM
    };

    enum CommonOption
    {
        COPT_LORES_ONLY = 0
    ,   COPT_NUM
    };

    enum Tabs
    {
        TAB_COMMON = 0
    ,   TAB_TRANSFUNCS
    ,   TAB_MATERIALS
    };


    /// Conctructor.
    HxVolren();

    /// Destructor
   ~HxVolren();

    void updateUI();


    ////////////////////////////////////////
    // overload HxModule
    ////////////////////////////////////////

    /// Ports are shown or hidden here.
    void update();

    /// Compute method.
    void compute();

    /// Parse the interpreter commandline and execute commands
    int parse( Tcl_Interp * inTCL, int inArgc, char ** inArgv );

    /// Overloaded method, restores number of transfer function ports.
    int saveCreation(FILE* fp, const char* dataDir, int saveFlags);


    ////////////////////////////////////////
    // static ports
    ////////////////////////////////////////

    /// Input for optional label data.
    HxConnection        mPortLabel;

    /// Connection to ROI interface.
    HxConnection        mPortROI;
    HxConnection        mPortROICornerCut;


    ////////////////////////////////////////
    
    HxPortTabBar        *mPortTab;


    ////////////////////////////////////////
    // common
    ////////////////////////////////////////

  /// Render modes
    HxPortGeneric      *mPortCommonMode;

    ///
    HxPortToggleList    *mPortCommonOptions;


    HxPortFloatSlider   *mPortCommonDRRGamma;

 //   HxPortSeparator     mPortCommonSeparator;


    ////////////////////////////////////////
    // shading
    ////////////////////////////////////////

    /// shading parameters presets
    HxPortRadioBox      *mPortShadingParameterPreset;

    /// phong factors, light color
    HxPortGeneric       *mPortShadingParameter;

    /// light direction presets: top left, bottom left, head light, ...
    HxPortRadioBox      *mPortShadingLightAnglePreset;

    /// light direction
    HxPortFloatSlider   *mPortShadingLightAngleYaw;
    HxPortFloatSlider   *mPortShadingLightAnglePitch;

    /// sampling distance for slice-based VR
    HxPortFloatSlider    *mPortSliceDistance;

    /// Recompute and load OpenGL texture.
    //HxPortDoIt          portAction;

    bool portActionWasHit;

    bool movieMode;

    bool isMovieModeEnabled();
    void setMovieModeEnabled(bool);




    ////////////////////////////////////////
    // transfer functions
    ////////////////////////////////////////

    class TransFunc
    {
    public:

        TransFunc( HxVolren * inVolren, int inId );
       ~TransFunc();

        HxVolren          * mVolren;
        int                 mId;
        bool                mDeleteMe;

        HxPortGeneric       mPortOptions;
        int                 mPortOptionsIdxDel;
        int                 mPortOptionsIdxDefaultLabel;

        /// Colormap defines transfer function.
        HxPortColormap      mPortColormap;

        /// Alpha scale
        HxPortFloatSlider   mPortAlphaScale;

        ///
        HxPortSeparator     mPortSeparator;

        void defaultColorMap();

        bool isFirstUpdate();

    private:
        bool mIsFirstUpdate;
    };


    McHashTable< int, TransFunc* >  mTransFuncs;

    int                     mTransFuncIdNext;
    
    HxPortButtonList        mTransFuncNew;

    void transFuncNewButtonUpdate();
    void transFuncNew();
    void initTransferFunctionPorts(const McDArray<int>& ids);
    

    ////////////////////////////////////////
    // materials
    ////////////////////////////////////////

    static const int MaterialDefault = 256;

    class Material
    {
    public:

        Material( HxVolren * inVolren, int inIndex, char * inName );
       ~Material();

        HxVolren          * mVolren;

        int                 mId;
        McString            mName;

        bool                mTmpDelete;

        ///
        HxPortGenericMaterial       mPortOptions;

        int                 mPortOptionsIdxColor;
        int                 mPortOptionsIdxHide;
        int                 mPortOptionsIdxDefault;
        int                 mPortOptionsIdxUseColor;
        int                 mPortOptionsIdxTransFunc;

        HxPortSeparator   * mPortSeparator;

        void setName( char const * inName );

        void setTransFuncId( int inTransFuncId );
        int  transFuncId();
    };

    McHashTable< int, Material* >  mMaterials;

    void materialsUpdate();
    void materialsUpdateUI();

    // shows all available transfer functions registered in HxVolren
    // return TRUE if setting was changed, FALSE if unchanged
    bool materialSelectTransferFunction( HxVolren::Material * ioMat );


    ////////////////////////////////////////
    // colormap
    ////////////////////////////////////////

    // Foreach HxColormap a temporary VsColorMap needs to be computed.
    class ColorMap
    {
    public:

        ColorMap() : mUseId( -1 ), mDefaultColor(1.f, 1.f, 1.f), mHxColorMap(0)
        {
        }

       ~ColorMap()
        {
        }

        int                     mUseId;
        SbColor                 mDefaultColor;
        HxColormap*             mHxColorMap;
        McHandle<VsColorMap>    mVsColorMap;
    };

    McDArray< ColorMap* >  mColorMaps;

    ColorMap* findColorMap( HxPortColormap& portColorMap, bool create );

    void createColorMap( HxVolren::ColorMap * inMap, McHandle<VsColorMap> & outMap );

    void setMultiChannelFieldColor();
    void checkColorField();
    void checkLowResOnly();


    ////////////////////////////////////////
    // level data
    ////////////////////////////////////////

    class LevelData
    {
    public:

        LevelData();
       ~LevelData();

        void scan( HxVolren & inVolren );
        void prepare( LevelData * inLevel0 = 0 );

        bool needRePrepare( LevelData & inOther );
        bool needReRender ( LevelData & inOther );

        void convertMultiChannelToRGBA( 
            HxMultiChannelField3    & inField
        ,   McDArray<HxLattice3*>   & inLatticesToUse
        ,   McHandle<VsMemoryData>  & outData
        );


        // needs to be set manually before instance is used
        int                       mLevel;

#define USEAMIRADATA 0

#if USEAMIRADATA
        // amira objects
        HxUniformScalarField3   * mDensiUSF;
        HxRegColorField3        * mDensiUCF;
        HxMultiChannelField3    * mDensiMCF;
        HxUniformScalarField3   * mLabelUSF;

        // lattice arrays sorted by pointer
        McDArray<HxLattice3*>     mDensiLattices;
        McDArray<HxLattice3*>     mLabelLattices;
#endif

        // data containers
        McHandle<VsData>          mDensiVsData;
        McHandle<VsData>          mLabelVsData;

        // some properties
        McVec3l                   mDensiDims;
        McVec3l                   mLabelDims;
        McPrimType                mDensiPrimType;
        McPrimType                mLabelPrimType;
        McMat4f                   mDensiObject2World;
        McBox3f                   mDensiBoundingBox;
    };

    LevelData               mLevels[2];

    ////////////////////////////////////////


    unsigned short          mId;
    static unsigned short   sIdNext;

    McHandle<VsVolume>      mVsVolume;


    ////////////////////////////////////////
    // render data
    ////////////////////////////////////////

    McHandle<SxVolren>      mSxVolren;

    McMat4f                 mMatrixModelView;
    McMat4f                 mMatrixModelViewI;
    McMat4f                 mMatrixProjection;

    uint32_t                mFrameIDLastStateScan;
    uint32_t                mFrameIDLastRender;

    McDArray<McPlane>       mClipPlanes;
    McHandle<VsCropRegion>  mVsCropRegion;

    
    ////////////////////////////////////////
    // render data
    ////////////////////////////////////////

    QxCleanupTimer          mCleanupTimer;


    
    bool                    mVsCornerCutActive;
    McHandle<VsCornerCut>   mVsCornerCut;
    McMat4f                 mVsCornerCutO2W;

    McBox3f                 mCropBox;
    McMat4f                 mCropBoxO2W;

    void cleanup();
};

extern void check();

#endif

/// @}
