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
#ifndef _VS_VOLREN_IMPL_H
#define _VS_VOLREN_IMPL_H

#include "VsVolren.h"

#include "VsNodeImpl.h"
#include "VsVolumeImpl.h"
#include "VsColorMapImpl.h"
#include "VsCropRegionImpl.h"

#include <mclib/McHandle.h>
#include <mclib/McColor.h>
#include <mclib/McVec3f.h>
#include <mclib/McList.h>


////////////////////////////////////////////////////////////////////////////////
class VSVOLREN_API VsVolrenImpl : public VsNodeImpl
{
    VS_IMPLEMENTATION( VsVolrenImpl, VsNodeImpl, VsVolren )
    
public:
    
    class VsVolumeParams;

    ////////////////////////////////////////
    // color maps can be referenced by multiple materials
    ////////////////////////////////////////
    class VsColorContainer
    :   public VsHandable
    ,   public McLink
    {
    public:
        VsVolrenImpl          * mVolrenI;
        
        McHandle< VsColorMap >  mColorMap;

        int                     mLastState;
        
        int                     mFrameIdUsed;
        int                     mFrameIdChanged;

        unsigned short        * mTransFunc0; // raw transfer function


        float                   mtmp0[2]; // internal use only

        VsColorContainer( VsVolrenImpl * I, VsColorMap * M );
       ~VsColorContainer();
    };

    McList  < VsColorContainer > mColorContainers;
    McHandle< VsColorContainer > mColorContainerEmpty;

    ////////////////////////////////////////
    // single material
    ////////////////////////////////////////
    class VsMaterial
    {
    public:

        VsVolrenImpl          * mVolrenI;
        VsVolumeParams        * mParams;


        bool                            mUseDefault;
        bool                            mClip;
        McColor                         mColor;
        bool                            mUseColor;


        McHandle< VsColorContainer >    mColorContainer;
        float                           mDataWindow[2];
        float                           mAlphaScale;


        int                     mTransFunc1UpdateFrameId;   // set to -1 to force update of transFunc1
        
        unsigned short        * mTransFunc1; // transfer functions scaled and biased according data windows
        unsigned short        * mTransFunc2; // transfer functions scaled and biased according data windows + alpha corrected


        VsMaterial( VsVolrenImpl * I, VsVolumeParams * P );
       ~VsMaterial();

        void setCM( VsColorMap * cm );
        void setDW( float a, float b );
        void setAS( float scale );
    };


    ////////////////////////////////////////
    // all data needed for rendering a volume
    ////////////////////////////////////////
    class VsVolumeParams
    {
    public:

        VsVolumeParams( VsVolrenImpl * I ); 
       ~VsVolumeParams();

        VsVolrenImpl                      * mVolrenI;

        VsMaterial                        * mMaterials[ VsVolren::MaterialMaxNum + 1 ];

        int                                 mNumTrueClip;
        int                                 mNumTrueUseColor;

        VsVolren::RenderMode                mRenderMode;

        McHandle< VsVolume >                mVolume;

        bool                                mVisible;

        // specular light color
        McColor                             mLightColor;
        
        // light direction
        McVec3f                             mLightDirection;

        float                               mLightingParameters[4];


        // DRR exposure
        float                               mExposure;
    };

    McDArray<VsVolumeParams*>               mParameters;


    ////////////////////////////////////////
    //
    ////////////////////////////////////////


    int                             mLevel;


    float                           mIsoThreshold;
    McColor                         mIsoColor;

    McMat4f                         mRegistrationTransform;

    float                           mFusionWeight;

    McColor                         mSelectionColor;
    bool                            mSelectionHighlightEnabled;

    McHandle<VsCropRegion>          mCropRegion;



public:
    ////////////////////////////////////////
    // non-virtual interface methods
    ////////////////////////////////////////
    VsVolume * volume(int inVolumeIndex) const;
    VSRESULT setData( VsData * data,  int inVolumeIndex );
    VsData * data( int inVolumeIndex ) const;
    int level() const;
    VsVolren::RenderMode renderMode(int inVolumeIndex) const;
    float dataWindowMin(unsigned int inTableIndex,int inVolumeIndex);
    float dataWindowMax(unsigned int inTableIndex,int inVolumeIndex);
    float isoThreshold() const;
    VSRESULT setLightDirection( VsVolren::LightDirection dir, int inVolumeIndex );
    McVec3f lightDirection( int inVolumeIndex) const;
    McColor lightColor(int inVolumeIndex) const;
    McColor isoColor() const;
    float lightingParameter( VsVolren::LightingParameter param, int inVolumeIndex ) const;
    VsCropRegion * cropRegion() const;
    VSRESULT setRegistrationTransform( const McMat4f & inMatrix );
    VSRESULT registrationTransform( McMat4f & outMatrix ) const;
    float exposure( int inVolumeIndex ) const;
    VsVolumeParams & parameters( int inVolumeIndex ) const;
    VSRESULT setVolumeVisible( bool inFlag, int inVolumeIndex );
    bool volumeVisible( int inVolumeIndex );
    bool isMultiMaterial( int inVolumeIndex );
    bool volpick( 
            VsVolren * volren
        ,   const McVec3f & inPos
        ,   const McVec3f & inDir
        ,   const bool & inVolume0
        ,   const bool & inVolume1
        ,   McVec3f & outResult
        );
    void setFusionWeight( float inWeight );
    float fusionWeight() const;

    bool selectionHighlightEnabled();
    McColor selectionHighlightColor();
    

private:
    ////////////////////////////////////////
    // virtual interface methods
    ////////////////////////////////////////
    VSRESULT vimpl_observedObjectTouched( VsObject * inObject, unsigned int inMask );
    VSRESULT vimpl_boundingBox( McBox3f & box ) const;
    VSRESULT vimpl_setCropRegion( VsCropRegion * cropRegion );
    VSRESULT vimpl_setLightingParameter( VsVolren::LightingParameter param, float value, int inVolumeIndex );
    VSRESULT vimpl_setIsoColor( const McColor& color );
    VSRESULT vimpl_setLightColor( const McColor& color, int inVolumeIndex );
    VSRESULT vimpl_setLightDirection( const McVec3f & dir, int inVolumeIndex );
    VSRESULT vimpl_setIsoThreshold( float value );
    VSRESULT vimpl_setDataWindow( float min, float max, int inTableIndex, int inVolumeIndex );
    VsColorMap * vimpl_transferFunction(unsigned int inTableIndex, int inVolumeIndex) const;
    VSRESULT vimpl_setTransferFunction( VsColorMap * map, int inTableIndex, int inVolumeIndex );
    VSRESULT vimpl_setRenderMode( VsVolren::RenderMode mode, int inVolumeIndex );
    VSRESULT vimpl_setLevel( int level );
    VSRESULT vimpl_setExposure( float inValue, int inVolumeIndex );
    VSRESULT vimpl_setAlphaScale( float inAlpha, int inLabelIndex, int inVolumeIndex );
    float    vimpl_alphaScale( unsigned int inLabelIndex, int inVolumeIndex );
    VSRESULT vimpl_setSelectionHighlightEnabled( bool inFlag );
    VSRESULT vimpl_setSelectionHighlightColor( McColor & inColor );
    VSRESULT vimpl_setLabelClipped( int inLabel, bool inDoClip, int inVolumeIndex );
    bool     vimpl_labelClipped( int inLabelIndex, int inVolumeIndex ) const;
    VSRESULT vimpl_setUseDefaultMaterial( int inLabel, bool inUseDefault, int inVolumeIndex );
    bool     vimpl_useDefaultMaterial( int inLabelIndex, int inVolumeIndex ) const;
    VSRESULT vimpl_setLabelColor( int inLabelIndex, McColor inColor, int inVolumeIndex );
    McColor  vimpl_labelColor( int inLabelIndex, int inVolumeIndex ) const;
    VSRESULT vimpl_setUseLabelColor( int inLabelIndex, bool inUseColor, int inVolumeIndex );
    bool     vimpl_useLabelColor( int inLabelIndex, int inVolumeIndex ) const;


protected:

    virtual VSRESULT    vimpl_setOptioni( int inOption, int inValue );
    virtual VSRESULT    vimpl_setOptiond( int inOption, double inValue );
    virtual VSRESULT    vimpl_optioni( int inOption, int & outValue ) const;
    virtual VSRESULT    vimpl_optiond( int inOption, double & outValue ) const;
    virtual VsRenderResult vimpl_render();
    virtual VSRESULT    vimpl_touch( unsigned int mask );
    virtual VSRESULT    vimpl_cleanup();

protected:

    virtual bool        vimpl_supported() const;
    virtual VSRESULT    vimpl_setVolume( VsVolume * volume, int inVolumeIndex );

private:
    void computeRegistrationTransform();
    void setVolumesInFusionMode( const bool & inVolume0, const bool & inVolume1 );
    bool mVolume0InFusionMode;
    bool mVolume1InFusionMode;
};

#endif


/// @}
