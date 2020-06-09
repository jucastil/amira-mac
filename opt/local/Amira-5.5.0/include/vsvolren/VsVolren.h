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
#ifndef _VS_VOLREN_H
#define _VS_VOLREN_H

#include "Vs.h"
#include "VsNode.h"
#include "VsRelay.h"

#include <mclib/McColor.h>
#include <mclib/McVec3f.h>

class VsCropRegion;
class VsColorMap;
class VsVolume;
class VsData;


// VS_RELAY_CLASS VsVolren VsNodeRelay

/** Implements hardware-accelerated direct volume rendering of 3D image
    volumes.

    This class provides a volume rendering interface.
    In order to render a 3D image volume you need to create an
    instance of VsVolren, pass in your data via setData() or setVolume(),
    and set parameters such as the render mode via setRenderMode(), the
    transfer function via setTransferFunction(),
    or an optional crop region via setCropRegion(). Afterwards you may
    directly call the \link VsNode::render() render() \endlink method with
    an existing OpenGL context, or you may create a renderer derived from
    VsRenderer and pass in the VsVolren node as part of a scene-graph.

    Details on how to provide 3D data volumes are discussed in section
    \link vsvolren_datamanagement Data Management \endlink.
    Possible ways of how to integrate volume rendering into existing 
    applications are described in section 
    \link vsvolren_integration Using the Library\endlink.
    The different render modes supported by VsVolren are discussed in
    section \link vsvolren_rendermodes Volume Rendering Modes\endlink.
*/
class VSVOLREN_API VsVolren : public VsNode
{   
    VS_DECL_INTERFACE        ( VsVolren )
    VS_DECL_INTERFACE_IMPL   ( VsVolren )
    VS_DECL_INTERFACE_FACTORY( VsVolren )
    VS_DECL_INTERFACE_RELAY  ( VsVolren )

public:
    
    /// Notifications flags. See VsObject::TouchFlag for details.
    enum TouchFlag
    {
        /// Set if a new input volume was set or the input volume was changed.
        NEW_DATA        = 1<<1
        /// Set if a new volume level was selected via setLevel().
    ,   NEW_LEVEL       = 1<<2
        /// Set if a new transfer function was set via setTransferFunction().
    ,   NEW_COLORMAP    = 1<<3
        /// Set if a new data window was set via setDataWindow().
    ,   NEW_DATAWINDOW  = 1<<4
        /// Set if a new iso threshold was set via setIsoThreshold().
    ,   NEW_THRESHOLD   = 1<<5
        /// Set if a new crop region was set or the crop region was changed.
    ,   NEW_CROPREGION  = 1<<6
        /// Set if a new render mode was set via setRenderMode().
    ,   NEW_RENDERMODE  = 1<<7
        /// Set if a label clip flag was changed via setLabelClipped().
    ,   NEW_CLIP        = 1<<8
        /// Set if the transformation of a volume has changed
    ,   NEW_TRANSFORM   = 1<<9
        /// Set if the visibility of a volume has changed
    ,   NEW_VISIBILITY  = 1<<10
#ifndef HIDDEN_FROM_DOC
        /// Set if a new alpha scale was set via setAlphaScale().
    ,   NEW_ALPHASCALE  = 1<<11
#endif
        /// Set if the registration transformation has changed
    ,   NEW_REGISTRATION_TRANSFORM = 1<<12
        /// Set if the materials have changed
    ,   NEW_MATERIAL    = 1<<13
    };

    /** Render modes used in setRenderMode().
        Details about these modes are described in a
        \link vsvolren_rendermodes separate section \endlink. */
    enum RenderMode 
    {
        /// Maximum intensity
        RENDER_MIP      = 0
        /// Emission-absorption
    ,   RENDER_VRT      = 1
        /// Shaded volume rendering
    ,   RENDER_SVRT     = 2
        /// Surface shaded display (isosurface)
    ,   RENDER_SSD      = 3
        /// Digitally reconstructed radiographs
    ,   RENDER_DRR      = 4
        /// Maximum intensity inverted
    ,   RENDER_MIPI     = 5
    };

    /// Lighting parameters used in setLightingParameter().
    enum LightingParameter 
    {
        /// Identifier for ambient color
        K_AMBIENT       = 0
        /// Identifier  for diffuse color
    ,   K_DIFFUSE       = 1
        /// Identifier for specular color
    ,   K_SPECULAR      = 2
        /// Identifier for shininess
    ,   SHININESS       = 3
    };

    /// Predefined light directions used in setLightDirection().
    enum LightDirection
    {
        /// light comes from top left
        LIGHT_TOP_LEFT      = 0
        /// light comes from bottom left
    ,   LIGHT_BOTTOM_LEFT   = 1
        /// light comes from the camera
    ,   LIGHT_HEAD          = 2
        /// light comes from bottom right
    ,   LIGHT_BOTTOM_RIGHT  = 3
        /// light comes from top right
    ,   LIGHT_TOP_RIGHT     = 4
    };


    /// Number of supported labels.
    static const int MaterialMaxNum  = 256;

    /// When specifying label indicies, use this value to affect the default material.
    static const int MaterialDefault = 256;
    
    /// When specifying label indicies, use this value to affect all materials including the default material.
    static const int MaterialAll     =  -1;


    ////////////////////////////////////////
    // overloaded methods from VsObject
    ////////////////////////////////////////

public:

    virtual VSRESULT setOptioni( int inOption, int inValue ); // VS_RELAY
    virtual VSRESULT setOptiond( int inOption, double inValue ); // VS_RELAY
    virtual VSRESULT optioni( int inOption, int & outValue ) const; // LOCAL_GET
    virtual VSRESULT optiond( int inOption, double & outValue ) const; // LOCAL_GET

protected:

    virtual VSRESULT observedObjectTouched( VsObject * inObject, unsigned int inMask );

    ////////////////////////////////////////
    // overloaded methods from VsNode
    ////////////////////////////////////////

public:

    virtual VsRenderResult render();
    virtual VSRESULT touch(unsigned int inMask=NEW_UNSPECIFIED);
    virtual VSRESULT cleanup();
    virtual VSRESULT boundingBox( McBox3f & outBox ) const; // LOCAL_GET


    ////////////////////////////////////////
    // own methods
    ////////////////////////////////////////
public:

    /** Sets the image volume to be rendered. \c inVolume should contain
        a downsampled version of the data set to be used for interactive
        rendering. 
        \sa \link vsvolren_datamanagement data management \endlink
        \param  inVolume
                Volume to be rendered.
        \param  inVolumeIndex
                Index of the volume.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT setVolume( VsVolume * inVolume, int inVolumeIndex = 0 ); // VS_RELAY

    /** Returns the current image volume.
        \param  inVolumeIndex
                Index of the volume.
        \return 
                Current volume. Null if there is none.
    */
    VsVolume * volume( int inVolumeIndex = 0 ) const; // VS_LOCAL_GET

    /** Sets the image volume to be rendered. This method automatically
        creates a VsVolume object and computes a downsampled version of
        \c inData for interactive display, if necessary. Depending on the
        size of the data set this may take a few seconds.
        \sa \link vsvolren_datamanagement data management \endlink
        \param  inData
                3D data to be rendered.
        \param  inVolumeIndex
                Index of the volume.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT setData( VsData * inData, int inVolumeIndex = 0 ); // VS_SYNC_CALL since internally VsVolume is created. Maybe remove from interface?

    /** Returns a pointer to the original (high-resolution) data set. 
        \param  inVolumeIndex
                Index of the volume.
        \return 
                Pointer to current data set. Null if there is none.
    */
    VsData * data( int inVolumeIndex = 0 ) const; // LOCAL_GET

    /** Sets the resolution level for rendering. Level 0 denotes the
        original (high-resolution) data. Level 1 denotes the
        downsampled (low-resolution) data set stored in the current
        volume().
        \param  inLevel
                The level index. 
                0 high resolution level. 1 low resulution level.
                -1 level auto selection. The default value is -1.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT setLevel( int inLevel ); // VS_RELAY

    /** Returns the current resolution level. 
        \return 
                The current index of the level currently chosen for rendering.
    */
    int level() const; // LOCAL_GET

    /** Sets the render mode. 
        \param  inMode
                See VsVolren::RenderMode for valid values.
        \param  inVolumeIndex
                Index of the volume.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT setRenderMode( VsVolren::RenderMode inMode, int inVolumeIndex = 0 ); // VS_RELAY

    /** Returns the current render mode.
        \param  inVolumeIndex
                Index of the volume.
        \return 
                See VsVolren::RenderMode for valid values.
    */
    VsVolren::RenderMode renderMode( int inVolumeIndex = 0 ) const; // LOCAL_GET


    /** Show or hide a volume.
        With this method one can enable or disable rendering of a volume in this Volren node.
        \param  inFlag
                Set to \c True to enable rendering for the volume indexed by the parameter 
                \c inVolumeIndex.
        \param  inVolumeIndex
                Index of the volume the flag is set for.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT setVolumeVisible( bool inFlag, int inVolumeIndex = 0 ); // VS_RELAY

    /** Get visibility status of a volume.
        With this method one can query if rendering of a volume is enabled.
        \param  inVolumeIndex
                Index of the volume the flag queried from.
        \return 
                \c True if volume is visible, else \c False.
    */
    bool volumeVisible( int inVolumeIndex = 0 ); // LOCAL_GET

    /** 
        \if UNDOCUMENTED
        Set a transfer function.
        The transfer function determines how the intensity of a voxel
        is mapped to color and opacity. This function is additionally
        affected by the alpha scale (see below). The data window of the 
        provided colormap isn't used. Instead, the window can be set 
        via setDataWindow(). For volume rendering of segmented volumes 
        a separate transfer function can be set for each material label.
        \else
        Set a transfer function.
        The transfer function determines how the intensity of a voxel
        is mapped to color and opacity. The data window of the
        provided colormap isn't used. Instead, the window can be set
        via setDataWindow(). For volume rendering of segmented volumes
        a separate transfer function can be set for each material label.
        \endif
        \param  inMap
                If non-zero, pointer to the transfer function.
                If zero, the transfer function gets set to the internal 
                default transfer function.
        \param  inLabelIndex
                When in range from 0 to MaterialMaxNum-1 :
                    Affects the material of a single label.
                MaterialAll :
                    Affects the material of each label.
                MaterialDefault :
                    Affects the default material.
        \param  inVolumeIndex
                Index of the volume.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT setTransferFunction( VsColorMap * inMap, int inLabelIndex = -1, int inVolumeIndex = 0 ); // VS_RELAY

    /** Returns a transfer function.
        \param  inLabelIndex
                When in range from 0 to MaterialMaxNum-1 :
                    Returns the value of a single label material.
                MaterialDefault :
                    Returns the value of the default material.
        \param  inVolumeIndex
                Index of the volume.
        \return 
                If non-zero, pointer to the transfer function.
                Zero on error. To get extended error information, call Vs::lastError().
    */
    virtual VsColorMap * transferFunction( unsigned int inLabelIndex = 0, int inVolumeIndex = 0 ) const; // LOCAL_GET

#ifndef HIDDEN_FROM_DOC
    /** Sets the alpha scale.
        The alpha scale is multiplied to the values of the transfer
        function, and hence controls the opacity of a displayed
        volume. The default value is 1.0 which leaves the transfer function unchanged.
        When this method is called with a negative inLabelIndex also the default alpha scale value
        for new materials is changed to the value of inAlpha.
        For volume rendering of segmented volumes a separate alpha scale can can be set for 
        each material label.
        \param  inAlpha
                Contains the new alpha scale. Negative values are clamped to zero.
        \param  inLabelIndex
                When in range from 0 to MaterialMaxNum-1 :
                    Affects the material of a single label.
                MaterialAll :
                    Affects the material of each label.
                MaterialDefault :
                    Affects the default material.
        \param  inVolumeIndex
                Index of the volume.
    */
    virtual VSRESULT setAlphaScale( float inAlpha, int inLabelIndex = -1, int inVolumeIndex = 0 ); // VS_RELAY

    /** Returns the alpha scale.
        \param  inLabelIndex
                When in range from 0 to MaterialMaxNum-1 :
                    Returns the value of a single label material.
                MaterialDefault :
                    Returns the value of the default material.
        \param  inVolumeIndex
                Index of the volume.
        \return 
                Alpha scale.
    */
    virtual float alphaScale( unsigned int inLabelIndex = 0, int inVolumeIndex = 0 ) const; // LOCAL_GET

    /* Used for fixing #1752. When disabling fusion display, we need a place to store
       the original fusion weight, because we must be able to restore it when we later
       enable fusion again.
       - The alpha scale will be set to one (to fix #1752), hence we cannot use that.
       - ExVolren seems another place which could be potentially used, but it seems
         to serve another purpose that is probably conflicting.
       - A hashtable in ExFusionTool would be ugly and we could forget to reset it
       So we just use a local attribute here, even though is redundant
       to the alpha scale.
       The setter is *not relayed*, we don't need the value for rendering on the server!
    */

    // RK: this is non-functional, do not use this
    // the recommented way is to use setAlphaScale(..)
    void setFusionWeight( float inWeight );
    float fusionWeight() const;

#endif

    /** Set data window of a specific transfer function. 
        \param  inMin
                Data value that gets mapped to the first value of the transfer function.
        \param  inMax
                Data value that gets mapped to the last value of the transfer function.
        \param  inLabelIndex
                When in range from 0 to MaterialMaxNum-1 :
                    Affects the material of a single label.
                MaterialAll :
                    Affects the material of each label.
                MaterialDefault :
                    Affects the default material.
        \param  inVolumeIndex
                Index of the volume.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT setDataWindow( float inMin, float inMax, int inLabelIndex = -1, int inVolumeIndex = 0 ); // VS_RELAY

    /** Return data value which is mapped to first transfer function entry. 
        \param  inLabelIndex
                When in range from 0 to MaterialMaxNum-1 :
                    Returns the value of a single label material.
                MaterialDefault :
                    Returns the value of the default material.
        \param  inVolumeIndex
                Index of the volume.
        \return 
                Data value that gets mapped to the first value of the transfer function.
    */
    float dataWindowMin( unsigned int inLabelIndex = 0, int inVolumeIndex = 0 ) const; // LOCAL_GET

    /** Return data value which is mapped to last transfer function entry. 
        \param  inLabelIndex
                When in range from 0 to MaterialMaxNum-1 :
                    Returns the value of a single label material.
                MaterialDefault :
                    Returns the value of the default material.
        \param  inVolumeIndex
                Index of the volume.
        \return 
                Data value that gets mapped to the last value of the transfer function.
    */
    float dataWindowMax( unsigned int inLabelIndex = 0, int inVolumeIndex = 0 ) const; // LOCAL_GET

    /** Toggle rendering of voxels tagged with a specific label on or off.
        If the input volume provides label data (see VsVolume::setLabelData())
        this method allows to easily hide all voxels assigned to a given
        label. The same result could be obtained by setting a completely
        transparent transfer function for that label.
        \param  inLabelIndex
                When in range from 0 to MaterialMaxNum-1 :
                    Affects the material of a single label.
                MaterialAll :
                    Affects the material of each label.
        \param  inDoClip
                If \c True, the voxels of the specified labels are turned off,
                i.e. they are fully transparent. If \c False, the voxels
                of the specified label are drawn with their current transfer function
                and data window.
        \param  inVolumeIndex
                Index of the volume.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT setLabelClipped( int inLabelIndex, bool inDoClip, int inVolumeIndex = 0 ); // VS_RELAY

    /** Returns whether tagged voxels of a specific label are currently displayed
        or invisible.
        \param  inLabelIndex
                When in range from 0 to MaterialMaxNum-1 :
                    Returns the value of a single label material.
                MaterialDefault :
                    Returns the value of the default material.
        \param  inVolumeIndex
                Index of the volume.
        \return 
                If voxels of the specified label are rendered with their corresponding
                transfer function, the method returns \c True. \c False indicates that
                the voxels are rendered transparent.
    */
    virtual bool labelClipped( int inLabelIndex, int inVolumeIndex = 0 ) const; // LOCAL_GET



    virtual VSRESULT setLabelColor( int inLabelIndex, McColor inColor, int inVolumeIndex = 0 ); // VS_RELAY
    virtual McColor labelColor( int inLabelIndex, int inVolumeIndex = 0 ) const; // LOCAL_GET

    virtual VSRESULT setUseLabelColor( int inLabelIndex, bool inUseColor, int inVolumeIndex = 0 ); // VS_RELAY
    virtual bool useLabelColor( int inLabelIndex, int inVolumeIndex = 0 ) const; // LOCAL_GET



    /** Toggle between application of the default material and the label specific material.
        \param  inLabelIndex
                When in range from 0 to MaterialMaxNum-1 :
                    Affects a single label.
                MaterialAll :
                    Affects each label.
        \param  inUseDefault
                If \c True, the voxels of the specified labels are rendered using the default material.
                If \c False, the voxels of the specified labels are rendered using the label specific material.
        \param  inVolumeIndex
                Index of the volume.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT setUseDefaultMaterial( int inLabelIndex, bool inUseDefault, int inVolumeIndex = 0 ); // VS_RELAY

    /** Returns whether tagged voxels of a specific label are currently displayed
        or invisible.
        \param  inLabelIndex
                Needs to be in range from 0 to MaterialMaxNum-1 :
                    Returns the value for a single label.
        \param  inVolumeIndex
                Index of the volume.
        \return 
                If voxels of the specified label are rendered with their corresponding
                transfer function, the method returns \c True. \c False indicates that
                the voxels are rendered transparent.
    */
    virtual bool useDefaultMaterial( int inLabelIndex, int inVolumeIndex = 0 ) const; // LOCAL_GET


    /** Set threshold for isosurface rendering. 
        \param  inValue
                Threshold value of all data on the ISO-surface.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT setIsoThreshold( float inValue ); // VS_RELAY

    /** Returns threshold for isosurface rendering. 
        \return 
                Threshold value of all data on the ISO-surface.
    */
    float isoThreshold() const; // LOCAL_GET

    /** Set density scaling for DRR mode (synthetic X-ray images).
        \param  inValue
                Exposure value. Must be greater than 0.0. Larger 
                values generate brighter images. 
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT setExposure( float inValue, int inVolumeIndex = 0 ); // VS_RELAY

    /** Returns density scaling for DRR mode. 
        \return 
                Exposure value.
    */
    float exposure( int inVolumeIndex = 0) const; // LOCAL_GET

    /** Set light direction in world space. 
        \param  inDir
                Light direction in camera space.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT setLightDirection( const McVec3f & inDir, int inVolumeIndex = -1 ); // VS_RELAY

    /** Convenience method that calls the above method. Sets a predefined light direction.
        \param  inDir
                See VsVolren::LightDirection for valid values.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT setLightDirection( VsVolren::LightDirection inDir, int inVolumeIndex = -1 );

    /** Returns the current light direction. 
        \return 
                The current light direction in camera space.
    */
    McVec3f lightDirection( int inVolumeIndex = 0 ) const; // LOCAL_GET

    /** Sets the light color for RENDER_SVRT and RENDER_SSD modes. 
        \param  inColor
                Light color.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */ 
    virtual VSRESULT setLightColor( const McColor & inColor, int inVolumeIndex = -1 ); // VS_RELAY

    /** Returns the current light color. 
        \return 
                Current light color.
    */
    McColor lightColor( int inVolumeIndex = 0 ) const; // LOCAL_GET

    /** Sets the surface color for RENDER_SSD mode. 
        \param  inColor
                Surface color.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT setIsoColor(const McColor & inColor ); // VS_RELAY

    /** Returns the current surface color. 
        \return 
                Current surface color..
    */
    McColor isoColor() const; // LOCAL_GET

    /** Sets the lighting parameters for RENDER_SVRT and RENDER_SSD modes.

        This method allows for setting coefficients for the ambient,
        diffuse, and specular lighting terms. The coeffients should be
        in the range 0..1. They are used to multiply the corresponding
        color contributions. The ambient and diffuse colors themselves
        are taken from the transfer function in case of RENDER_SVRT,
        or they are defined by the surface color set via setIsoColor()
        in case of RENDER_SSD. The specular color can be defined by
        setLightColor(). 
        \param  inParam
                See LightingParameter for valid values.
        \param  inValue
                New value for the specified parameter.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT setLightingParameter( VsVolren::LightingParameter inParam, float inValue, int inVolumeIndex = -1 ); // VS_RELAY

    /** Returns the current value of a lighting parameter. 
        \param  inParam
                See LightingParameter for valid values.
        \return 
                Current value of the requested parameter.
    */
    float lightingParameter( VsVolren::LightingParameter inParam, int inVolumeIndex = 0 ) const; // LOCAL_GET

    /** Sets a new crop region. If a crop region is active only the
        parts of the image volume inside the crop region will be
        shown. In order to disable cropping you should call this
        method with a zero pointer. The crop region object will not
        be copied but a handle to the object will be stored. When
        the crop region is modified, this object will be automatically
        touched. 
        \param  inCropRegion
                New crop region. If zero, cropping is disabled.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT setCropRegion( VsCropRegion * inCropRegion ); // VS_RELAY

    /** Returns the current crop region object. 
        \return 
                Current crop region or zero if cropping is disabled.
    */
    VsCropRegion * cropRegion() const; // LOCAL_GET

    /** Set the registration transform for the secondary volume. 
        Note that the transformation matrix is specified as relative
        transformation of the secondary volume with respect to the first
        volume.
        \param  inMatrix
                The transformation matrix.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setRegistrationTransform( const McMat4f & inMatrix ); // VS_RELAY

    /** Get the registration transformation matrix for the secondary volume.
        \param  outMatrix
                Receives the current registration transformation matrix.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT registrationTransform( McMat4f & outMatrix ) const; // LOCAL_GET

    /** Checks if volume rendering is supported on the current hardware.
        This function requires to be called with a valid rendering context active.
        \return 
                \c True if supported.
    */
    virtual bool supported() const; // VS_SYNC_CALL // result could be cached on client then

    /** Implements the actual volume picking algorithm: sends a ray through the
        volume and returns the position you see in the rendering along that ray. 
        Returns false if no point can be found.
        \param  inPos
                The position of the ray on the volume
        \param  inDir
                The direction of the ray through the volume
        \param  inVolume0
                Should be set true if the first volume is in fusion mode
        \param  inVolume1
                Should be set true if the second volume is in fusion mode
        \param  outResult
                returns the final position in the volume
    */
    virtual bool volpick( 
            const McVec3f & inPos
        ,   const McVec3f & inDir
        ,   const bool & inVolume0
        ,   const bool & inVolume1
        ,   McVec3f & outResult ); // VS_SYNC_CALL


    /*
    */
    bool selectionHighlightEnabled();
    virtual VSRESULT setSelectionHighlightEnabled( bool inFlag ); // VS_RELAY

    McColor selectionHighlightColor();
    virtual VSRESULT setSelectionHighlightColor( McColor & inColor ); // VS_RELAY
};


#endif


/// @}
