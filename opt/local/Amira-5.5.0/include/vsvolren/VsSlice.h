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
#ifndef _VS_SLICE_H_
#define _VS_SLICE_H_

#include "Vs.h"

#include "VsNode.h"

#include <mclib/McColor.h>
#include <mclib/McPlane.h>
#include <mclib/McVec3f.h>

#include <float.h>

class VsCropRegion;
class VsData;
class VsVolume;
class VsColorMap;


class VSVOLREN_API VsSliceSelector : public VsHandable {
public:
    virtual void select(VsSlice* slice) = 0;
};

template<typename T> class McDArray;

// VS_RELAY_CLASS VsSlice VsNodeRelay


/** Displays orthogonal and oblique slices through a data volume. 
*/
class VSVOLREN_API VsSlice : public VsNode
{
    VS_DECL_INTERFACE        ( VsSlice )
    VS_DECL_INTERFACE_IMPL   ( VsSlice )
    VS_DECL_INTERFACE_FACTORY( VsSlice )
    VS_DECL_INTERFACE_RELAY  ( VsSlice )

public:

    /// Notifications flags. See VsObject::TouchFlag for details.
    enum TouchFlag
    {
        /// Set if the primary volume has changed, a new input volume was set or the input volume was changed.
        NEW_DATA        = 1<<1,
        /// Set if a new volume level was selected via setLevel().
        NEW_LEVEL       = 1<<2,
        /// Set if a new transfer function was set via setTransferFunction().
        NEW_COLORMAP    = 1<<3,
        /// Set if a new data window was set via setDataWindow() or setInverseTF().
        NEW_DATAWINDOW  = 1<<4,
        /// Set if a new plane was set, the plane thickness has changed, or the thick slice compositing has changed.
        NEW_PLANE       = 1<<5,
        /// Set if a new crop region was set or the crop region was changed.
        NEW_CROPREGION  = 1<<6,
        /// Set if a new render mode was set via setRenderMode().
        NEW_RENDERMODE  = 1<<7,
        /// Set if a new decoration was specified via setDecoration().
        NEW_DECORATION  = 1<<8,
        /// Set if a new fusion weight was specified (see setFusionWeight()).
        NEW_FUSION_WEIGHT = 1<<9,
        /// Set if a new label field was specified or the current one has changed
        NEW_LABELS        = 1<<10,
        /// Set if the label colors have changed
        NEW_LABEL_COLORS  = 1<<11,
        /// Set if a label clip flag was changed via setLabelClipped().
        NEW_CLIP          = 1<<12,
        /// Set if the slice image was modified from outside
        NEW_SLICE_IMAGE   = 1<<13,
        /// Set if the label slice image was modified from outside
        NEW_LABEL_IMAGE   = 1<<14,
        /// Set if scout lines were changed (added, removed, repositioned, color change via setFrameColor())
        NEW_SCOUT_LINES   = 1<<15,
#ifndef HIDDEN_FROM_DOC
        /// Set if a new sampling geometry was specified in curved-slice-mode
        NEW_CURVED_SLICE_SAMPLE_MESH = 1<<16,
        /// Set if a new render geometry was specified in curved-slice-mode
        NEW_CURVED_SLICE_RENDER_MESH = 1<<17,
#endif
        /// Set if the registration transformation has changed (see setRegistrationTransform())
        NEW_REGISTRATION_TRANSFORM   = 1<<18,
        /// Set if the activity of label clipping has changed (see setLabelClippingEnabled())
        NEW_LABEL_CLIPPING           = 1<<19,
        /// Set if the texture filtering (nearest or bilinear) has changed
        NEW_FILTER                   = 1<<20
    };

    /// Plane orientation flags.
    enum Orientation 
    {
        /// Plane is positioned arbitrary.
        OBLIQUE         = -1,
        /// Plane normal is parallel to the x-axis
        SLICE_YZ        =  0,
        /// Plane normal is parallel to the y-axis
        SLICE_XZ        =  1,
        /// Plane normal is parallel to the z-axis
        SLICE_XY        =  2,
#ifndef HIDDEN_FROM_DOC
        /// Slice is curved
        SLICE_CURVED    =  3
#endif
    };

    /// Flag that determines the method of data sampling for displaying a pixel.
    enum Filter
    {
        /// Sample data along the current plane snapping to the nearest voxel.
        NEAREST         = 0,
        /// Sample data along the current plane interpolating linearly between the adjacent eight voxels.
        LINEAR          = 1
    };

    /// The compositing mode used during thick MPR reconstruction
    enum MipMode
    {
        /// No MPR reconstruction - VsSlice::thickness() is ignored
        MM_NONE         = 0,
        /// Maximum intensity value of all projected slices
        MM_MAX_IP       = 1,
        /// Minimum intensity value of all projected slices
        MM_MIN_IP       = 2,
        /// Average intensity value of all projected slices
        MM_AVERAGE      = 3
    };

    /** Render modes used in setRenderMode(). */
    enum RenderMode
    {
        /// Density mapped to gray scale values
        RENDER_DENSITY          = 0,
        /// Density mapped to colors via a color table
        RENDER_DENSITY_COLOR    = 1,
        /// Fusion of two data sets (e.g. PET and CT) with the colors multiplied
        RENDER_FUSION_MULTIPLY  = 2,
        /// Same as RENDER_FUSION_MULTIPLY but using a color map for the primary volume
        RENDER_FUSION_COLOR_MULTIPLY = 3,
        /// Fusion of two data sets with each data set's contribution defined by fusionWeight()
        RENDER_FUSION_CROSSFADE = 4,
#ifndef HIDDEN_FROM_DOC
        /** Fusion of two data sets with each data set's contribution defined by fusionWeight() 
            and enhanced by the intensity value. For PET/CT rendering this will lead to brighter images.
        */
        RENDER_FUSION_CROSSFADE_BRIGHT = 5,
#endif
        /// Fusion of two data sets with the second data set alpha blended on the first data set.
        RENDER_FUSION_BLEND     = 6,
        /// Fusion of two data sets with the color of both data sets added
        RENDER_FUSION_ADD       = 7,
        /// Fusion of two data sets with the color of both data sets subtracted
        RENDER_FUSION_SUB       = 8,
        /// Don't render textured polygon e.g. render only frame, scoutlines etc.
        RENDER_WIRE_FRAME       = 9
    };

    /** Decoration used for rendering - each one can be switched on or off 
        individually by setDecoration() */
    enum Decoration
    {
        /// No decoration
        DE_NONE              = 0,
        /// Labeled regions indicated by contour lines
        DE_CONTOURS          = 1<<0,
        /// Regions highlighted with label colors
        DE_REGIONS           = 1<<1,
        /// Selection of temporary segmentation
        DE_SELECTION         = 1<<2,
        /// Boundary of the slice in the primary volume
        DE_BOUNDARY_VOLUME0  = 1<<3,
        /// Boundary of the slice in the secondary volume
        DE_BOUNDARY_VOLUME1  = 1<<4,
        /// Scout lines (see addScoutLine() )
        DE_SCOUT_LINES       = 1<<5,
        /// Crop region lines
        DE_CROP_REGION_LINES = 1<<6,
        /// Thresholded highlight 
        DE_HIGHLIGHT         = 1<<7,
        /// All available decorations
        DE_ALL               = 0xFFFFFFFF
    };

    ////////////////////////////////////////
    // overloaded methods from VsObject
    ////////////////////////////////////////

    virtual VSRESULT setOptioni( int inOption, int inValue ); // VS_RELAY
    virtual VSRESULT optioni( int inOption, int & outValue ) const; // LOCAL_GET
    virtual VSRESULT setOptiond( int inOption, double inValue ); // VS_RELAY
    virtual VSRESULT optiond( int inOption, double & outValue ) const; // LOCAL_GET


    ////////////////////////////////////////
    // virtuals from VsNode
    ////////////////////////////////////////

    /** Returns the bounding box of the slice. The box encloses all vertices
        actually rendered by the slice. It is defined in object space coordinates.
        \param  outBox
                The current bounding box gets stored in the box object 
                referenced by this parameter.             
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT boundingBox( McBox3f & outBox ) const; // LOCAL_GET

    /** Renders the object
        \return 
                See VsRenderResult.
    */
    virtual VsRenderResult render();

    /** Frees all OpenGL recources allocated for the slice during rendering.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT cleanup();

    /** Overloaded method (sets internal plane-changed flag).
        \param  inMask 
                Bitwise combination of touch flags. 
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT touch(unsigned int inMask=NEW_UNSPECIFIED);

    ////////////////////////////////////////
    // new methods
    ////////////////////////////////////////

    /** Check if the node has attached data.
        \return 
                \c True if node has data, else \c False.
    */
    bool hasData() const; // LOCAL_GET

    /** Sets the primary/master volume - for non fusion rendering modes
        only the primary volume will be rendered. For fusion rendering
        modes the primary volume will determine the shape of the slice
        that is beeing rendered.
        \param  inIndex
                Index of the new primary volume, valid indices are 0 and 1.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT setPrimaryVolume(int inIndex = 0); // VS_RELAY

    /** Returns the index of the primary volume.
        \return 
                The primary volume index.
    */
    int primaryVolume() const; // LOCAL_GET

    /** Sets the image volume to be rendered.
        \param  inVolume
                Volume to be rendered. This volume may contain multiple
                versions of the image data to be rendered at different 
                resolution levels. If zero, the slice is going to have
                no attached data anymore.
        \param  inIndex
                Index of the volume to be attached - currently at most
                two volumes may be attached, meaning that valid indices are 
                0 and 1.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT setVolume( VsVolume * inVolume, int inIndex = 0 ); // VS_RELAY

    /** Get current volume.
        \param  inIndex
                Index of the volume object that should be returned.
                Currently valid indices are 0 and 1.
        \return 
                Pointer to the current volume data. If zero, there is no current volume.
    */
    VsVolume * volume( int inIndex = 0 ) const; // LOCAL_GET

    /** Convenience method for passing in a data volume directly from a VsData
        object. Automatically creates a VsVolume instance with
        a low-resolution version of the input data. 
        \param  inData
                Pointer to the new data. If zero, the slice is going to have
                no attached data anymore.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT setData( VsData * inData ); // VS_RELAY

    /** Sets the resolution level for rendering. Level 0 denotes the
        original high-resolution data. Level 1 denotes a down-sampled
        version of the data.
        \param  inLevel
                Level index to be rendered. Use -1 for automatic level selection. Coarser data resolutions might be used to improve interactivity.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT setLevel( int inLevel ); // VS_RELAY

    /** Returns the current resolution level. 
        \return 
                Index of the currend level selected for sampling.
                Default value is -1, denoting automatic level selection.
    */
    int level() const; // LOCAL_GET

    /** Sets the render mode. 
        \param  inMode
                See VsSlice::RenderMode for valid values.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT setRenderMode( VsSlice::RenderMode inMode ); // VS_RELAY

    /** Returns the current render mode.
        \return 
                The current rendering mode.
                See VsSlice::RenderMode for valid values.
    */
    VsSlice::RenderMode renderMode() const; // LOCAL_GET

    /** Enables decoration specified by inMask. The method accepts any
        bitwise OR of bits specified in VsSlice::Decoration.
        \param  inMask
                See VsSlice::Decoration for valid bit values.
        \return                 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT setDecoration( unsigned int inMask ); // VS_RELAY

    /** Returns the current decoration mask.
        \return 
                The current decoration mask.
                See VsSlice::Decoration for valid values.
    */
    unsigned int decoration() const; // LOCAL_GET
    
    /** Sets the color of the selection (highest bit of label field byte)
        \param inColor the color
    */
    void setSelectionColor(const McColor &inColor); // VS_RELAY

    /** Gets the selection color (highest bit of label field byte)
        \return  current set selection color
    */
    McColor selectionColor() const; // LOCAL_GET

    /** Set a transfer function.
        The transfer function determines how the intensity of a voxel
        is mapped to color and opacity. The data window of the colormap
        isn't used. Instead, the window can be set via setDataWindow().
        For rendering of multiple volumes, in particular cross fade
        fusion rendering, a separate transfer function can be set for 
        each volume.

        \param  inMap
                If non-zero, pointer to the transfer function.
                If zero, the transfer function gets set to the internal 
                default transfer function.
        \param  inVolumeIndex
                Index of the volume the transfer function is set for.
                Valid indices currently are 0 and 1.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT setTransferFunction( VsColorMap * inMap, int inVolumeIndex = 0 ); // VS_RELAY

    /** Returns a transfer function.
        \param  inVolumeIndex
                Index of the volume the transfer function is retrieved from.
        \return 
                If non-zero, pointer to the transfer function.
                Zero on error. To get extended error information, call Vs::lastError().
    */
    VsColorMap * transferFunction( unsigned int inVolumeIndex = 0 ) const; // LOCAL_GET


    /** Set a data window. 
        \param  inMin
                Value that is mapped to the first transfer function entry.
        \param  inMax
                Value that is mapped to the last transfer function entry.
        \param  inIndex
                index of the data window to set - each volume may use an
                individual data window so valid indices are 0 or 1
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT setDataWindow( float inMin, float inMax, int inIndex = 0 ); // VS_RELAY

    /** Get data value which is mapped to the first transfer function entry. 
        \param  inIndex
                index of the volume for which the minimum data value is to
                be retrieved.
        \return 
                Minimum data value of interest.
    */
    float dataWindowMin( int inIndex = 0 ) const; // LOCAL_GET

    /** Get data value which is mapped to the last transfer function entry.
        \param  inIndex
                index of the volume for which the maximum data value is to
                be retrieved.
        \return 
                Maximum data value of interest.
    */
    float dataWindowMax( int inIndex = 0 ) const; // LOCAL_GET

    /** Set a highlight data window.
        /param inMin First density value highlighted 

        /param inMax Last density value highlighted

        /param inIndex Volume index 0 or 1
    */
    VSRESULT setDataWindowHighlight( float inMin = FLT_MIN, float inMax = FLT_MAX, int inIndex=0 ); // VS_RELAY

    /** Get lower highlight data window bound
       /param inIndex Volume index 0 or 1 
    */
    float dataWindowHighlightMin( int inIndex = 0 ) const; // LOCAL_GET
    
    /** Get upper highlight data window bound
       /param inIndex Volume index 0 or 1 
    */
    float dataWindowHighlightMax( int inIndex = 0 ) const; // LOCAL_GET

    /** Toggle extraction / rendering of voxels tagged with specific labels 
        on or off. If the input volume provides label data 
        (see VsVolume::setLabelData()) this method allows to easily hide all
        voxels assigned to certain labels. In order to hide voxels corresponding
        to a specific label, you must set the clipping status for that label
        using VsVolren::setLabelClipped.
        \param  inOn 
                If \c True, label clipping is to be turned on, otherwise turned
                off.
        \param  inIndex
                The index of the volume for which the label clipping should be
                turned on/off. Use -1 for both volumes.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT setLabelClippingEnabled( bool inOn, int inIndex = -1 ); // VS_RELAY

    /** Returns whether label specific extraction/rendering is turned on or
        off. If on, all voxels tagged with labels that are defined to be clipped
        away are ignored during slice extraction and rendering.
        \param  inIndex
                The index of the volume for which the label clipping status
                should be obtained.
        \return 
                The method returns \c True if voxels tagged with labels, that 
                are defined as 'to-be-clipped' (see. setLabelClipped()) are ignored
                during slice extraction/rendering.
    */
    virtual bool labelClippingEnabled(int inIndex = 0) const; // LOCAL_GET

    /** Set the visibility/clipping status (for extraction/rendering) for 
        voxels corresponding to a specific label. If the input volume provides
        label data and label specific clipping is enabled 
        (see VsSlice::setLabelClippingEnabled) all voxels tagged with a certain
        label can be toggled on or off using this method.
        \param  inLabelIndex
                Label that should be turned on or off.
                If negative, all labels are affected.
        \param  inDoClip
                If \c True, the voxels of the specified labels are turned off,
                i.e. they are fully transparent and do not contribute to thick
                slice extraction. If \c False, the voxels of the specified label
                are drawn with their current transfer function and data window.
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
                Label for which the clip state should be returned.
        \param  inVolumeIndex
                Index of the volume.
        \return 
                If voxels of the specified label are rendered with their corresponding
                transfer function, the method returns \c True. \c False indicates that
                the voxels are rendered transparent.
    */
    virtual bool labelClipped( int inLabelIndex, int inVolumeIndex = 0 ) const; // LOCAL_GET

    /** Enable/disable color map inversion
        \param  inEnable
                flag indicating whether the color map should be applied inverted 
                or non inverted
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT setInverseTF(bool inEnable); // VS_RELAY

    /** Get the color map inversion mode
        \return
                true if color map inversion is enabled, else false.
    */
    bool inverseTF() const; // LOCAL_GET

    /** Set an axis aligned orthogonal plane.
        \param  inSliceOffset
                This offset is in volume index space.
                Internally this value gets clamped to the interval from 0 
                to max-dimension for the current axis minus one.
                It is possible to specify non-integer values.
                This makes sense for out-of-core data objects with more slices available
                than indicated by the current dimension.
        \param  inOrientation
                Orientation of the slice plane. For valid values see VsSlice::Orientation.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT setPlane( float inSliceOffset, VsSlice::Orientation inOrientation ); // VS_RELAY

    /** Sets an oblique plane. If the plane is nearly perpendicular to one
        of the major axes, the best matching orthogonal plane is extracted.
        The focus is set to the center of the bounding box of the slice.
        \param  inPlane
                New plane.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT setPlane( const McPlane & inPlane ); // VS_RELAY

    /** Get the current slice number or offset. The value is undefined for
        oblique planes. Therefore you should check orientation() before
        calling this method. Note that we use float for the slice number.
        Integer values refer to slices representing the
        base level (level 0). Non-integer values might refer to a higher
        resolution out-of-core version of the data set (currently not
        implemented). 
        \return 
                Current slice offset for the current orthogonal direction.
    */
    float sliceNumber() const; // LOCAL_GET

    /** Get the index increment between two slices. Note that we use
        float "indices". Integer values refer to slices representing the
        base level (level 0). Non-integer values might refer to a higher
        resolution out-of-core version of the data set (currently not
        implemented). 
        \return 
                Slice increment.
    */
    float sliceIncrement() const; // LOCAL_GET
    
    /** Returns the number of available slices. The number of slices
        depends on the current orientation. It is only defined for
        orthogonal orientations. numSlices() always refers to the level
        0 data set, not to a down-sampled version of the data.
        \return 
                Number of slices for the current orthogonal direction.
    */
    int numSlices() const; // LOCAL_GET

    /** Get the current orientation of the slice. For orthogonal planes
        this can be SLICE_YZ, SLICE_XZ, or SLICE_XY. For oblique planes
        OBLIQUE is returned. 
        \return 
                Current orientation. See VsSlice::Orientation for valid values.
    */
    VsSlice::Orientation orientation() const; // LOCAL_GET

    /** Get the current orientation of the slice with respect to the
        primary or overlay volume.
        \param  inIndex
                Index of the volume object for which the orientation should
                be returned. Currently valid indices are 0 and 1.
        \return 
                Current orientation. See VsSlice::Orientation for valid values.
    */
    VsSlice::Orientation orientation(int inIndex) const; // LOCAL_GET

    /** Get the current plane in object space.
        \return 
                The current plane.
    */
    McPlane plane() const; // LOCAL_GET

    /** Returns true if the current plane intersects the volume. If this
        is false, nothing will be rendered. */
    bool planeValid() const; // LOCAL_GET

    /** Get the coordinate swizzle for the current plane orientation.
        When a slice plane image is extracted, outSwizzle[0] and outSwizzle[1]
        denote the axes in the local volume coordinate system that refer
        to the x and y slice image coordinates, e.g., for SLICE_XY outSwizzle[0] 
        and outSwizzle[1] would be 0 and 1, for SLICE_YZ outSwizzle[0] and 
        outSwizzle[1] would be 1 and 2 etc. For oblique slices outSwizzle[2]
        points to the most perpendicular volume axis and outSwizzle[0]/outSwizzle[1]
        to any of the remaining coordinate axes.
        \param  outSwizzle
                Output array, where the swizzle parameters are returned.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT swizzle( int outSwizzle[3] ) const; // LOCAL_GET

    /** Set the weighting factor for fusion of two data sets on a single slice
        \param  inWeight
                New fusion weight. Valid values 0.0 ... 1.0.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT setFusionWeight( float inWeight ); // VS_RELAY

    /** Get current fusion weight.
        \return
                Current fusion weight
    */
    float fusionWeight() const; // LOCAL_GET

    /** Set the color of the slices border lines.
        \param  inColor
                New color.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT setFrameColor( const McColor & inColor ); // VS_RELAY

    /** Get current border lines color.
        \return 
                Current color.
    */
    McColor frameColor() const; // LOCAL_GET

    /** A value of \c inThickness > 0 enables thick-MPR mode. In this case multiple
        slices are reconstructed and composed as defined by setThickMIPMode(). The
        thickness value is specified in object coordinates, i.e., in the same
        coordinates the bounding box is defined in. The thick-MPR region
        will be centered around the actual plane specified by
        setPlane(). If \c inThickness is 0, just a standard slice will be taken. 
        \param  inThickness
                If non-zero, MPR is turned on extracting a slice of that thickness.
                If zero, MPR is turned off.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT setThickness( float inThickness ); // VS_RELAY

    /** Get the current thickness.
        \return 
                Current thickness.
    */
    float thickness() const; // LOCAL_GET

    /** Register another slice node. When the slice is drawn, an additional line is drawn
        for each registered slice with the frame color of this slice.
        This so called scout line is drawn at the intersection line between the planes.
        These scout lines indicate the region where the user can pick to drag
        the other slice.
        \param  inSlice
                Slice to register.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT addScoutLine( VsSlice * inSlice ); // VS_RELAY

    /** Get number of registered slice nodes.
        \return 
                number of slice nodes registered with addScoutLine().
    */
    int numScoutLines() const; // LOCAL_GET

    /** Gets the scout line at a specific index
        \param  index
                index of the scout line.
        \return 
                the scout line at the index position.
    */
    VsSlice * scoutLine(int index) const; // LOCAL_GET

    /** Un-register a specific slice node.
        \param  inSlice
                Slice to un-register.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT removeScoutLine( VsSlice * inSlice ); // VS_RELAY

    /** Un-register all slice nodes.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT clearScoutLines(); // VS_RELAY

    /** Sets a new crop region. If a crop region is active the
        parts of the slice outside the crop region will be
        drawn darkened. 
        Additionally the outline of the crop region is drawn on the slice.
        In order to disable cropping you should call this
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
    VSRESULT setCropRegion( VsCropRegion * inCropRegion, int idx = 0 ); // VS_RELAY

    /** Get the current crop region object. 
        \return 
                Current crop region or zero if cropping is disabled.
    */
    VsCropRegion * cropRegion() const; // LOCAL_GET

    /** Set texture lookup filter.
        The default value is VsSlice::NEAREST.
        \param  inFilter
                See VsSlice::Filter for valid values.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT setFilter( VsSlice::Filter inFilter ); // VS_RELAY

    /** Get current texture lookup filter.
        \return 
                See VsSlice::Filter for valid values.
    */
    VsSlice::Filter filter() const; // LOCAL_GET

    /** Sets the pick line for retrieving density values at a the position
        where the line hits the current plane.
        \param  inLine
                Line in object space.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT setPickLine( const McLine& inLine ); // VS_RELAY

    /** Get the hit point of the current pick line with the current 
        plane. The method returns #VS_FAILED if no intersection exists, i.e. 
        the current pick line is parallel to the current plane. 
        \param  outPoint
                The intersection point in object space of primary volume.
        \param  inIndex
                Index of the volume for which the picking should be
                performed. If -1 is specified, the method returns true
                if either the primary or the overlay volume was picked.
        \return 
                If there is an intersection, the return value is #VS_OK,
                else it is set to #VS_FAILED.
    */
    VSRESULT pickPoint( McVec3f & outPoint, int inIndex = 0 ) const; // LOCAL_GET

    /** Picks the density value at the hit point of the current pick line 
        and the current plane. Returns #VS_OK if line hits the data area. 
        \param  outDensity
                The density value at the intersection position is returned in this parameter.
        \param  inIndex
                Index of the volume for which the density is to be retrieved.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT pickValue( float & outDensity, int inIndex = 0 ) const; // VS_SYNC_CALL

    /** Picks the label data at the hit point of the current pick line 
        and the current plane. Returns #VS_OK if line hits the data area. 
        \param  outLabel
                The label at the intersection position is returned in this parameter.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT pickLabel( int& outLabel ) const; // VS_SYNC_CALL

    /** Picks the density value of several pick lines at once. 
        Returns #VS_OK even if some or all lines do not hit the data area!
        The density at those hit points is set to 0. 
        \param  inLineStrip
                Array of pick lines in object space.
        \param  inNumberOfResults
                Number of results. This must match inLineStrip.size().
        \param  outResults
                The density values at the intersection positions is returned in this parameter.
        \param  inIndex
                Index of the volume for which the density is to be retrieved.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT pickValueLine( const McDArray<McLine>& inLineStrip, int inNumberOfResults, float * outResults, int inIndex = 0 ) const; // VS_SYNC_CALL

    /** Get the current slice image. The application might change the intensity values
        in the slice image. However, in order to make modifications effective a
        touch (NEW_SLICE_IMAGE) is required. Note that modifications are temporary
        and will be lost next time the slice image is re-extracted.
        \param  inIndex
                Index of the volume for which the slice image is to be retrieved.
        \param extractSliceIfNecessary
                If true the slice will be extracted (resampled) if necessary, i.e.,
                if any parameters like plane position or thickness have changed.
                If false simply the last extracted slice will be return. Usually
                this will be the slice shown the last time the node was rendered.
        \return 
                Pointer to the currently extracted slice or NULL if there is no
                volume with index \c inIndex or the slice has not yet been rendered
                with the current volume.
    */
    VsData * sliceImage( int inIndex = 0, bool extractSliceIfNecessary = false ) const; // VS_SYNC_CALL

    /** Get the current image of extracted material labels. The application might 
        change the material labels in the slice image. However, in order to make 
        modifications effective a touch (NEW_LABEL_IMAGE) is required. Note that 
        modifications are temporary and will be lost next time the label slice 
        image is re-extracted. Also recall that label values larger than 128 have
        a special meaning since the most significant bit of the label value marks
        "selected" voxels/pixels, e.g. a voxel with label 67 "belongs" to material
        67, the same is true for a voxel with label 195 but the latter is considered
        "selected".
        \param  inIndex
                Index of the volume for which the label slice image is to be retrieved.
        \return 
                Reference to the currently label slice or NULL if there is no volume
                with index \c inIndex or if the volume has no label data.
    */
    VsData * labelImage( int inIndex = 0 ) const; // VS_SYNC_CALL ??

    /** Use this function to set the compositing mode for thick-MPR. For supported 
        modes see VsSlice::MipMode. In case of MM_MAX_IP multiple slices are
        reconstructed and the MIP (maximum intensity projection) is computed. 
        For MM_MIN_IP, the minimum intensity projection is computed. For MM_AVERAGE,
        the average of all projected slices is computed. The thick-MPR region
        will be centered symmetrically around the actual plane specified by
        setPlane(). VsSlice::setThickness is used to specify the thickness for
        MPR reconstruction in object space. VsSlice::MM_NONE will completely turn
        of MPR reconstruction regardless of the value of thickness().
        \param  inMode
                The new reconstruction mode.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT setThickMIPMode( VsSlice::MipMode inMode ); // VS_RELAY

    /** Get the current reconstruction mode for thick-MPR.
        \return
                The current reconstruction mode.
    */
    VsSlice::MipMode thickMIPMode() const; // LOCAL_GET

    /** Set the color that is used for highlighting the volumetric region
        marked with a specific label. There are two ways to show the label
        information depending on the decoration mask defined 
        (See VsSlice::setDecoration). If VsSlice::DE_REGOINS is set, texels 
        of the slice are rendered with a colored overlay, where the color is
        specified by the material id in the corresponding label data field. 
        If VsSlice::DE_CONTOURS is set a contour line is drawn around all 
        voxels sharing the same material id. This function is used to define
        the color that corresponds to a specific material label.

        Note that label values larger than 128 have a special meaning: 
        The most significant bit of the label value marks "selected" voxels/pixels.
        As an effect, e.g., voxels with labels 67 and 195 will share the same 
        color, the color of label 67.
        \param  inLabel
                The material label for which the color should be specified.
        \param  inNumberOfColor
                The number of the color channels. The number must be by the
                value 4.
        \param  inColor
                The new RGBA color value.
        \return
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT setLabelColor(int inLabel, int inNumberOfColor, unsigned char * inColor); // VS_RELAY

    /** Get the color associated with a specific material label.
        \param  inLabel
                The material label for which the color should be determined.
        \param  outColor
                An array of four unsigned char values. The RGBA-color value
                for the specified label will be returned there.
        \return
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    VSRESULT labelColor(int inLabel, unsigned char outColor[4]) const; // LOCAL_GET

    /** Get the area that is associated with one voxel/pixel shown on the
        slice plane. The function is useful for performing measurements, e.g.,
        determining the size of a highlighted area. Note that the return 
        value is not fix but depends on the current orientation of the slice
        since voxels of the volume project differently onto the slice plane.
        \return
                The area associated with a pixel of the slice plane. If
                the bounding box is specified in mm, the returned values
                is in mm x mm.
    */
    float voxelArea() const; // LOCAL_GET

    // ////////////////////////////////////////
    //  curved slicing
    // ////////////////////////////////////////

    /** Set the sampling geometry for a curved slice. Beside from the sampling
        of a volume data set on an axis aligned or oblique plane, an arbitrary
        polygonal surface may be defined inside the volume bounding box. The
        volume data is then resampled along this surface and presented as texture
        mapped onto a so called render geometry. In the easiest case the render
        geometry may be a simple rectangle.
        This functionality is useful, e.g., for showing the intestinal wall
        unfolded as a 'colonal map'.

        The polygonal surface is defined as a quad mesh consisting of m x n
        vertices.

        Note that the array of vertices is NOT copied by the VsSlice object,
        this allows to easily update the geometry when the slice is moved.

        \param  inM  Number of vertices (first index)
        \param  inN  Number of vertices (second index)
        \param  inVertices
                List of the vertices of the quad mesh. The vertices are assumed
                to be organized as 2D array, i.e.,
                Vertex[i][j] is stored at index k = j * m + i
        \return
                If the method succeeds, the return value is #VS_OK. To get
                extended error information, call Vs::lastError().
    */
    VSRESULT setSampleGeometry(int inM, int inN, const McVec3f* inVertices); // relay

    // This function is the same as setSampleGeometry. It only has a parameter addionally for roc.
    VSRESULT setSampleGeometry(int inM, int inN, int inNumberOfVertices, const McVec3f* inVertices); // VS_RELAY

    /** Set the rendering geometry for the curved slice. As a default the volume
        data that is sampled on a curved slice (arbitrary polygonal surface) is
        presented on the same geometry that is used for sampling, i.e., the
        quad mesh specified by setCurvedSlice(...). This method can be used to
        define an alternative geometry (a quad mesh) on which the sampled data
        is presented.

        For simplicity, currently, the sampling geometry and the rendering
        geometry have to share the same topology - meaning that the numbers of
        vertices in the rendering geometry have to be the same as for the sampling
        geometry.

        Note that the array of vertices is NOT copied by the VsSlice object,
        this allows to easily update the geometry when the slice is moved.

        \param  inM  Number of vertices (first index)
        \param  inN  Number of vertices (second index)
        \param  inVertices
                List of the vertices of the quad mesh. The vertices are assumed
                to be organized as 2D array, i.e.,
                Vertex[i][j] is stored at index k = j * m + i
        \return
                If the method succeeds, the return value is #VS_OK. To get
                extended error information, call Vs::lastError().
    */
    VSRESULT setRenderGeometry(int inM, int inN, const McVec3f* inVertices); // relay

    // This function is the same as setRenderGeometry. It only has a parameter addionally for roc.
    VSRESULT setRenderGeometry(int inM, int inN, int inNumberOfVertices, const McVec3f* inVertices); // VS_RELAY

    /** Conveniance method for setting up curved slices. The method sets the
        sampling geometry AND the rendering geometry of the slice to the same
        polygonal surface defined as a quad mesh consisting of m x n vertices.
    
        Note that the array of vertices is NOT copied by the VsSlice object,
        this allows to easily update the geometry when the slice is moved.

        \param  inM  Number of vertices (first index)
        \param  inN  Number of vertices (second index)
        \param  inVertices
                List of the vertices of the quad mesh. The vertices are assumed
                to be organized as 2D array, i.e.,
                Vertex[i][j] is stored at index k = j * m + i
        \return
                If the method succeeds, the return value is #VS_OK. To get
                extended error information, call Vs::lastError().
    */
    VSRESULT setCurvedSlice(int inM, int inN, const McVec3f* inVertices); // has always internaly relayed function

    // ////////////////////////////////////////
    //  transformation matrix
    // ////////////////////////////////////////

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

protected:

    /**
    */
    virtual VSRESULT observedObjectTouched( VsObject * inObject, unsigned int inMask );

public:
    /// Generic interface for extended functionality
    virtual void * extension( int, void * );
};


#endif


/// @}
