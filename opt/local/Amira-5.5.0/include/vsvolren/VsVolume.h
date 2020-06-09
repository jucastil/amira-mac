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
#ifndef _VS_VOLUME_H
#define _VS_VOLUME_H

#include "Vs.h"
#include "VsRelay.h"
#include "VsObject.h"
#include "VsVoxelDescriptor.h"

class HxParamBundle;
class AmiraMesh;
class VsData;
class VsJobControl;

class McBox3f;
class McBox3i;
class McColor;
class McPlane;
class McString;
class McVec3i;


// VS_RELAY_CLASS VsVolume VsObjectRelay


/** Multi-resolution representation of a data volume.

    This class stores multiple versions of a data volume at different
    resolutions. These versions are the so called levels.
    Usually, in addition to the original high-resolution
    level a downsampled level is provided. The downsampled
    level is used, for example, for interactive volume rendering.
    By convention data with the higher resolution is stored in
    a level with a lower index. Level 0 holds the data with the highest resolution.

    A level may contain multiple data objects of different semantics.
    The most common semantic is the density. Additionally a level can
    contain label data.

    Currently all data objects of a single level have to have the same
    resolution. This may change in future.

    VsVolume objects may be created manually by computing two or more
    VsData objects, one for each level, and registering them in VsVolume
    by calling setData(). Alternatively, a VsVolume object may be created
    automatically, for example, by a VsVolren node. This occurs when the
    VsVolren node is initialized with a VsData object instead of a VsVolume
    object. The resulting VsVolume object can then be obtained via
    VsVolren::volume() and stored in an AmiraMesh file by calling
    writeAmiraMesh(). If the AmiraMesh file is read again, first the downsampled
    level is read. The high-resolution data is read afterwards asynchronously
    in a background thread.
*/
class VSVOLREN_API VsVolume : public VsObject
{
    VS_DECL_INTERFACE        ( VsVolume )
    VS_DECL_INTERFACE_IMPL   ( VsVolume )
    VS_DECL_INTERFACE_FACTORY( VsVolume )
    VS_DECL_INTERFACE_RELAY  ( VsVolume )

public:

    /// Additional flags to be used in touch().
    enum TouchFlag
    {
        /** Set if the volumes data base has enlarged. This flag is used,
            e.g., when the asynchronous reader finishes his work. */
        NEW_DATA        = 1<<1
		/// Used in vsbase/ExLoadManager to indicate the termination of a read job.
    ,   NEW_DATA_LOADED = 1<<2
        /// Crop region has changed
    ,   NEW_CROPREGION  = 1<<3
    };


    ////////////////////////////////////////
    // overloaded methods from VsObject
    ////////////////////////////////////////

    virtual VSRESULT setOptioni( int inOption, int    inValue ); // VS_RELAY
    virtual VSRESULT setOptiond( int inOption, double inValue ); // VS_RELAY
    virtual VSRESULT optioni( int inOption, int & outValue ) const; // LOCAL_GET
    virtual VSRESULT optiond( int inOption, double & outValue ) const; // LOCAL_GET
    virtual void *   extension( int inEnum, void * userData ); // ???

protected:

    virtual VSRESULT observedObjectTouched( VsObject * inObject, unsigned int inMask );


    ////////////////////////////////////////
    // own methods
    ////////////////////////////////////////

public:

    /** Returns the bounding box of the volume.
        \param  outBox
                The current bounding box gets stored in the box object
                referenced by this parameter.
        \return
                If the method succeeds, the return value is #VS_OK. To get
                extended error information, call Vs::lastError().
    */
    VSRESULT boundingBox( McBox3f & outBox ) const; // LOCAL_GET

    /** Set density data for the specified level. Any previous density data set for that level is released.
        If \c inData is zero, the level has no data after this method call.
        \param  inLevel
                Level the density data is set for.
        \param  inData
                If non-zero, pointer to the density data to associate with the level.
                If zero, any previous associated data is released.
        \return
                If the method succeeds, the return value is #VS_OK. To get
                extended error information, call Vs::lastError().
    */
    VSRESULT setData( unsigned int inLevel, VsData * inData ); // VS_RELAY

    /** Set label data for the specified level. Any previous label data set for that
        level is released. If \c inData is zero, the level has no label data after this method call.
        This method can only be called if the specified volume already has a volume
        data set. The size of the label data set must match the size of the volume
        data set.
        \param  inLevel
                Level the label data is set for.
        \param  inData
                If non-zero, pointer to the label data to associate with the level.
                If zero, any previous associated label data is released.
        \return
                If the method succeeds, the return value is #VS_OK. To get
                extended error information, call Vs::lastError().
    */
    VSRESULT setLabelData( unsigned int inLevel, VsData * inData ); // VS_RELAY

    /** Convenience method to set the density data for level 0.
        \param  inLevel0Data
                If non-zero, pointer to the density data to associate with level 0.
                If zero, any previous associated density data is released.
        \return
                If the method succeeds, the return value is #VS_OK. To get
                extended error information, call Vs::lastError().
    */
    VSRESULT setData( VsData * inLevel0Data ); // calls setData(level,data)

    /*  Add more data to the already set data for a specific level.
        \param  inLevel
                Affected Level
        \param  inData
                Data to be added
        \param  inDesc
                Format and semantics of the data
        \return
                If the method succeeds, the return value is #VS_OK. To get
                extended error information, call Vs::lastError().
    */
    VSRESULT addData( unsigned int inLevel, VsData * inData, VsVoxelDescriptor::VoxelDescriptor inDesc ); // VS_RELAY

    /** Release data objects of the specified level. This includes density and label data.
        \param  inLevel
                Level the data is released from.
        \return
                If the method succeeds, the return value is #VS_OK. To get
                extended error information, call Vs::lastError().
    */
    VSRESULT removeData( unsigned int inLevel ); // VS_RELAY

    /** Is used to inform the volume about changes in the data object, e.g., changes
        in the voxel data. The volume will then, in case, trigger a NEW_DATA touch.
        \param  inData
                The changed data object.
        \return
                If the method succeeds, the return value is #VS_OK. To get
                extended error information, call Vs::lastError().
    */
    VSRESULT setDataModified( VsData * inData ); // VS_RELAY

    /** Returns the density data object of the specified level.
        \param  inLevel
                Level the density data is read from.
        \return
                Pointer to the density data of the specified level or zero if level has no density data.
    */
    VsData * densityData( unsigned int inLevel ) const; // LOCAL_GET

    /** Returns the density data object of the specified level.
        \param  inLevel
                Level the density data is read from.
        \return
                Pointer to the density data of the specified level or zero if level has no density data.
    */
    VsData * data( unsigned int inLevel ) const; // LOCAL_GET

    /** Returns the primary data object of the specified level.
        The primary data is the data with the highest priority.
        First comes DENSITY then COLOR then LABEL.
        \param  inLevel
                Level the primary data is read from.
        \return
                Pointer to the data of the specified level or zero if level has no data.
    */
    VsData * primaryData( unsigned int inLevel ) const; // LOCAL_GET

    /** Returns the label data object of the specified level.
        \param  inLevel
                Level the label data is read from.
        \return
                Pointer to the label data of the specified level or zero if level has no label data.
    */
    VsData * labelData( unsigned int inLevel ) const; // LOCAL_GET

    /** Convenience method to retrieve the level 0 density data.
        \return
                Pointer to the density data of the level 0 or zero if level 0 has no density data.
    */
    VsData * densityData() const; // LOCAL_GET

    /** Convenience method to retrieve the level 0 density data.
        \return
                Pointer to the density data of the level 0 or zero if level 0 has no density data.
    */
    VsData * data() const; // LOCAL_GET

    /** Returns the primary data object of level 0.
        The primary data is the data with the highest priority.
        First comes DENSITY then COLOR then LABEL.
        \param  inLevel
                Level the density data is read from.
        \return
                Pointer to the density data of the specified level or zero if level has no density data.
    */
    VsData * primaryData() const; // LOCAL_GET

    /** Set color data for the specified level. Any previous color data set for that
        level is released. If \c inData is zero, the level has no color data after this method call.
        If that level already has density data, that data gets released.
        \param  inLevel
                Level the color data is set for.
        \param  inData
                If non-zero, pointer to the color data to associate with the level.
                If zero, any previous associated color data is released.
        \return
                If the method succeeds, the return value is #VS_OK. To get
                extended error information, call Vs::lastError().
    */
    VSRESULT setColorData( unsigned int inLevel, VsData * inData ); // VS_RELAY

    /** Returns the color data object of the specified level.
        \param  inLevel
                Level the color data is read from.
        \return
                Pointer to the color data of the specified level or zero if level has no color data.
    */
    VsData * colorData( unsigned int inLevel ) const; // LOCAL_GET


    /** Returns the number of levels. This also includes levels without any data objects.
        This number is library dependent and may change in the future. It is guaranteed
        to be at least 8.
        \return
                Number of levels.
    */
    int numLevels() const; // LOCAL_GET

    /** Computes a low-resolution version of the data set.
        If the level 1 not already contains a data set, the method computes
        a down-sampled version of the data set at level 0 and stores it as
        level 1 data.  If level 0 also contains label data, a down-sampled
        version of the label data is computed as well. The method may fail if
        not enough memory is available for down-sampling.
        \param  inJC Pointer to an optional VsJobControl object. With such
                an object it is possible to interrupt the down-sampling
                operation and to get progress information about it.
        \return
                If the method succeeds, the return value is #VS_OK. To get
                extended error information, call Vs::lastError().
    */
    VSRESULT computeLevels(VsJobControl * inJC = 0); // VS_SYNC_CALL // RELAY later

    /** Recomputes the image data in level 1 inside the region of interest \c inROI from level 0.
        \param  inROI An optional region-of-interest in level 0 index space.
                If set, the image data will only be updated inside this
                region-of-interest.
    */
    void updateLevel1(const McBox3i* inROI=0); // VS_RELAY

    /** Recomputes the labels in level 1 inside the region of interest \c inROI from level 0.
        \param  inROI An optional region-of-interest in level 0 index space.
                If set, the labels will only be updated inside this
                region-of-interest.
    */
    void updateLevel1Labels(const McBox3i* inROI=0); // VS_RELAY

    /** Creates labels if these do not already exist. Labels are used for
        segmentation and clipping. For each voxel an 8-bit label is stored.
        All labels are initialized with 0.
        \return If the method succeeds, the return value is #VS_OK. To get
                extended error information, call Vs::lastError().
    */
    VSRESULT createLabels(); // VS_SYNC_CALL

    /** Returns the number of materials stored in the volume's material
        list. The first material is associated with label 0, the second
        with label 0, and so on. The first material (index 0) usually
        represents unsegmented or outside regions. If the volume does
        not contain label data, the number of materials is 0. If it has
        empty label data, the number of materials is 1.

        \return Number of materials
    */
    int numMaterials(); // LOCAL_GET

    /** Returns the index of a material. The index is used in a label field
        in order to express that a voxel is assigned to that material.

        \param[in] inMaterialName The name of the material to be looked-up.
        \param[in] inCreate If true, a new entry in the volumes material
            list will be allocated if the specified material does not yet exist.
        \param[in] inReturnVoidMaterial If true, also the index of an existing
            material marked as void (unused) will be returned. Otherwise, in this
            case -1 will be returned unless inCreate is true. If inCreate is true
            and the material exists but is marked as void then the void tag
            will be removed and the actual index of the material will be returned.
        \return Index of the specified material, or -1 if the material can
            not be found in the material list of the volume.
    */
    int materialIdx(const char* inMaterialName, bool inCreate=false, bool inReturnVoidMaterial=false); // VS_RELAY

    /** Returns the index of a material. This method essentially behaves as
        the method above. If it does not already exist, the requested
        material is created and the color of the material is set the 
        specified value.

        \param[in] inMaterialName The name of the material to be looked-up.
        \param[in] inDefaultColor Material color. The color will be set if
            the material is created. If the material already exists the
            material color will not be overwritten.
        \return Index of the specified material.
    */
    int materialIdx(const char* inMaterialName, const McColor& inDefaultColor); // VS_RELAY

    /** Returns the parameter bundle for the specified material. The material
        bundle may contain additional information such as the color of the
        material.

        \param[in] inMaterialIdx Index of the material to be retrieved.
        \return Pointer to parameter bundle or 0 if the material with the
            specified index does not exist.
    */
    const HxParamBundle* material(int materialIdx); // LOCAL_GET

    // The function "materials" is now removed. This was necessary for realizing
    // the client - server - communication.
    // The function "materials" is spitted in to function "getMaterials" and
    // "copyMaterials". 
    // Be careful with the function "getMaterials". You have to be sure, there
    // exist Material before you call the function. Use "hasMaterial" about
    // this information. (Date: 6.6.1007. Author: Jan")

    /** Returns the material bundle of the volume. The material
        bundle contains sub-bundles for all labels defined for this volume.

        \param[in] inCreateIfNecessary If true, material bundle is created if
            it does not already exit.
        \return Pointer to material bundle.
    */
    //HxParamBundle* materials(bool inCreateIfNecessary=true); // ??? LOCAL_GET or VS_RELAY

    /** Returns true if there are any the material in the bundle of the volume.

        \return true / false.
    */
    bool hasMaterials(); // LOCAL_GET

    /** Returns the material bundle of the volume. The material
        bundle contains sub-bundles for all labels defined for this volume.

        \return Pointer to material bundle.
    */
    HxParamBundle & getMaterials(); // LOCAL_GET

    /** Copys all information in the provided material bundle to the material
        bundle in the volume. The bundle should contain sub-bundles for all 
        labels defined for this volume.

        \param[in] inBundle a bundle of material information, which should
                   be stored in the volume.
        \param[in] inClearBundle
                   if this is \c true the new material information completely
                   replaces the old (deleting attributes not present in \c 
                   inBundle). If \c false the material information of \c inBundle
                   is just added (overwriting but not deleting attributes missing
                   in \c inBundle).
    */
    void copyMaterials( HxParamBundle & inBundle, bool inClearBundle = false ); // VS_RELAY

    /** Store volume into a file.
        \param  inFileName
                Filename of the destination volume file.
        \return
                If the method succeeds, the return value is #VS_OK. To get
                extended error information, call Vs::lastError().
    */
    VSRESULT writeAmiraMesh( const char * inFileName ); // VS_SYNC_CALL

    /** Reads a volume from the AmiraMesh handle \c inMesh. The AmiraMesh handle
        can be obtained by calling AmiraMesh::read(). It is possible to defer
        the import of the actual voxel data by setting AmiraMesh::recordFilePosition
        to 1 before calling AmiraMesh::read(). This method will then read the data
        by itself. The level 0 version of the data will be read asynchronously.
        If \c inROI is nonzero, it specifies a subregion of the voxel
        volume in index space. Instead of the complete volume only the subregion
        will be read and only memory for the subregion will be allocated. This is
        useful for multi-GPU rendering. The index values in \c inROI refer to level
        0.
        \param  inMesh
                Amira mesh handle.
        \param  inFileName
                Filename of the source volume file.
        \param  inMoveParameters
                If set to \c True, the methode will move the parameter bundle from the
                amira mesh file to the volume object. (Performance optimization that
                consumes the bundle in inMesh.
        \param  inROI
                Pointer to the region of interest. If zero the whole volume is read in.
        \param  inDownsamplingFactor
                Factors in x, y, z indicating to downsample the high resolution data
                in each direction. If 0, no downsampling is performed. Currently
                cannot be combined with the inROI parameter.
        \param  inJC
                Pointer to VsJobControl object. By specifying a VsJobControl object it
                is possible to interrupt asynchronous reading of the level 0 data.
        \param  inAutoStartReader
                The parameter allows to defer starting the asynchronous reader.
                If set to \c False the reader will not be started automatically.
                Default is \c True.
        \return
                Pointer to the newly created volume object. Zero means that an error
                occoured. To get extended error information, call Vs::lastError().
    */
    static VsVolume * readAmiraMesh( AmiraMesh * inMesh, const char * inFileName, bool inMoveParameters, const McBox3i * inROI=0, const McVec3i * inDownsamplingFactor=0, bool inAutoStartReader=true , VsJobControl* inJC=0 );

    /** Reads a volume from an AmiraMesh file. The level 0 version of the data will
        be read asynchronously, i.e., the method returns before the data has been
        completely read. The volume can already be rendered when the method returns.
        However, initially only a low-resolution version of the data set might be
        displayed.
        \param  inFileName
                Filename of the source volume file.
        \param  inROI
                Pointer to the region of interest. If zero the whole volume is read in.
        \param  inDownsamplingFactor
                Factors in x, y, z indicating to downsample the high resolution data
                in each direction. If 0, no downsampling is performed. Currently
                cannot be combined with the inROI parameter.
        \param  inAutoStartReader
                The parameter allows to defer starting the asynchronous reader.
                If set to \c False the reader will not be started automatically.
                Default is \c True.
        \param  inJC
                Pointer to VsJobControl object. By specifying a VsJobControl object it
                is possible to interrupt asynchronous reading of the level 0 data.
        \return
                Pointer to the newly created volume object. Zero means that an error
                occoured. To get extended error information, call Vs::lastError().
    */
    static VsVolume * readAmiraMesh( const char * inFileName, const McBox3i * inROI=0, const McVec3i * inDownsamplingFactor=0, bool inAutoStartReader=true, VsJobControl* inJC=0 );

    /** Reads label data from an AmiraMesh file. Any previous label data set for that
        volume will be released. Usually labels are loaded/saved in the same file
        as density data by means of writeAmiraMesh() and readAmiraMesh(). However, this
        method allows for loading a seperate data field as label data from a seperate
        AmiraMesh file (see writeLabelsAmiraMesh() for creating such a file).
        The file must contain an 8-bit label value for each voxel of the density
        data field contained in this volume object. This particularly means that
        the resolution of the label field has to match the resolution of the
        level 0 density data. The label file only needs to define level 0 data
        for level 1 label data will automatically be computed by downsampling if
        required.
        Note that asynchronous reading is not supported for label data.
        \param  inMesh
                Amira mesh handle.
        \param  inFileName
                Filename of the source label file.
        \return
                If the method succeeds, the return value is #VS_OK. To get
                extended error information, call Vs::lastError().
    */
    VSRESULT readLabelsAmiraMesh(AmiraMesh* inMesh, const char* inFileName);

    /** Reads label data from an AmiraMesh file. Any previous label data set for that
        volume will be released. Usually labels are loaded/saved in the same file
        as density data by means of writeAmiraMesh() and readAmiraMesh(). However, this
        method allows for loading a seperate data field as label data from a seperate
        AmiraMesh file (see writeLabelsAmiraMesh() for creating such a file).
        The file must contain an 8-bit label value for each voxel of the density
        data field contained in this volume object. This particularly means that
        the resolution of the label field has to match the resolution of the
        level 0 density data. The label file only needs to define level 0 data
        for level 1 label data will automatically be computed by downsampling if
        required.
        Note that asynchronous reading is not supported for label data.
        \param  inFileName
                Filename of the source label file. The filename is needed
                because the file might need to be reopened again by the
                asynchronous reader.
        \return
                If the method succeeds, the return value is #VS_OK. To get
                extended error information, call Vs::lastError().
    */
    VSRESULT readLabelsAmiraMesh( const char* inFileName); // VS_SYNC_CALL

    /** Writes label data defined within the volume object into a separate
        AmiraMesh file. (see readLabelsAmiraMesh() for loading such a file)
        Note that this does not remove the label data from the volume object.
        Thus, a call to writeAmiraMesh() will still save the volume object
        with density data AND label data.
        \param  inFileName
                Filename where label data should be stored.
        \param  inDescription
                An optional description - more user friendly name - that is
                stored within the AmiraMesh parameter bundle. Methods for
                file browsing may show the description instead of a
                (potentially cryptic) file name. Also the character set
                used within the description is not restricted by any operating
                system limitations.
        \param  inCodec
                Specifies the codec to be used to compress the data. Possible
                values are "HxByteRLE" (run-length encoding), "HxRLEZ" (run-length
                encoding followed by zlib compression), and 0 (no compression).
        \return
                If the method succeeds, the return value is #VS_OK. To get
                extended error information, call Vs::lastError().
    */
    VSRESULT writeLabelsAmiraMesh( const char* inFileName, const char* inDescription = 0, const char* inCodec = 0 ); // VS_SYNC_CALL

    /** Waits for an asynchronous reader to finish.
        The method waits until the associated asynchronous reader thread
        terminates or until the specified number of milliseconds have elapsed.
        The method returns \c True if there was a running reader thread that has
        terminated within the given time limit. If there is no asynchronous
        reader running or the specified milliseconds have elapsed without reader
        terminatation \c False is returned.
        \param  inTime
                Number of milliseconds to wait for an asynchronous reader.
                (-1 means wait for ever)
        \return
                \c True if there was a reader that terminated within the given
                time frame.
    */
    bool waitReading(unsigned long inTime=-1); // VS_SYNC_CALL

#ifndef HIDDEN_FROM_DOC
    /** Sets a pointer to an external label field. Usually each volume has
        its own set of label data. However, for time series it can be reasonable
        to share the very same label data for each time step. In this case, the
        volume needs to know that its label data is actually shared with other
        volumes so that modifications to the label data can be synced between
        all volumes of a time series. Call this function to set a label field
        that is shared with the \c inVolume.
        \param  inVolume
                Pointer to the volume that serves as a master for label data.
                (0 means, break label sharing).
         \return
                If the method succeeds, the return value is #VS_OK. To get
                extended error information, call Vs::lastError().
    */
    VSRESULT setLabelMaster(VsVolume * inVolume); // VS_RELAY

    /** In case of label data shared between multiple volumes, e.g. time steps
        of a time series, this function returns the pointer to the volume mastering
        the label data. (\sa setLabelMaster). If no label sharing is established
        the method will return 0.
         \return
                In case of shared label data the pointer to the volume mastering
                the label data is returned, or 0 otherwhise.
    */
    const VsVolume * labelMaster(); // VS_LOCAL_CALL
#endif // HIDDEN_FROM_DOC

    /** Set pointer to an external parameter bundle. On default the volume
        uses the parameter bundle of the first VsData object in level 0.
        This method allows you to specify an arbitrary HxParamBundle object.
        You must make sure that the HxParamBundle object exists as long as
        the volume object does. The volume object does not delete the
        external HxParamBundle when it is deleted.
        \param inBundle
            HxParamBundle object used in parameters().
    */
    void setParameters( HxParamBundle * inBundle );

    enum ParamType {
        P_PRIVATE,
        P_SHARED
    };

    /**
    */
    void setParameters( VsVolume::ParamType type, const char * inPath, const char * inName, const char*  inValue, int inParse=0); // VS_RELAY
    void setParameters( VsVolume::ParamType type, const char * inPath, const char * inName, const int    inValue); // VS_RELAY
    void setParameters( VsVolume::ParamType type, const char * inPath, const char * inName, const double inValue); // VS_RELAY
    void setParameters( VsVolume::ParamType type, const char * inPath, const char * inName, const int inNumberOfValues, const int*    inValues); // VS_RELAY
    void setParameters( VsVolume::ParamType type, const char * inPath, const char * inName, const int inNumberOfValues, const float*  inValues); // VS_RELAY
    void setParameters( VsVolume::ParamType type, const char * inPath, const char * inName, const int inNumberOfValues, const double* inValues); // VS_RELAY
    void removeParameters( VsVolume::ParamType type, const char * inPath, const char * inName); // VS_RELAY

    /** A read-only reference to the volume parameter bundle that contains
        additional, application defined informations about the volume.
        While you hold the reference, ensure by using appropriate locking
        mechanisms that the parameter bundle is not modified by other threads.
        \return
                Read-only reference to the volume's parameter bundle.
    */
    const HxParamBundle & parameters(VsVolume::ParamType type=VsVolume::P_SHARED) const;

    /** A writeable reference to the volume parameter bundle that contains
        additional, application defined informations about the volume.
        While you hold the reference, ensure by using appropriate locking
        mechanisms that the parameter bundle is not modified by other threads.
        \return
                Reference to the volume's parameter bundle.
    */
    HxParamBundle & parameters(VsVolume::ParamType type=VsVolume::P_SHARED); // LOCAL_GET




    /** Add a plane that clips away parts of the volume during rendering.
        \param  inPlane
                Plane that gets added. The plane is copied internally.
        \return
                If the method succeeds, the return value is #VS_OK. To get
                extended error information, call Vs::lastError().
    */
    VSRESULT addClipPlane( const McPlane & inPlane ); // VS_RELAY

    /** Remove all clip planes.
        \return
                If the method succeeds, the return value is #VS_OK. To get
                extended error information, call Vs::lastError().
    */
    VSRESULT deleteClipPlanes(); // VS_RELAY




    /** Sets a new crop region. If a crop region is active only the
        parts of the volume inside the crop region will be
        rendered. In order to disable cropping you should call this
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


    /** Retrieve number of clip planes.
        \return
                Number of clip planes.
    */
    unsigned int numClipPlanes() const; // LOCAL_GET

    /** Retrieve a clip plane.
        \param  inPlaneIndex
                Index of the requested clip plane.
        \param  outPlane
                Output plane.
        \return
                If the method succeeds, the return value is #VS_OK. To get
                extended error information, call Vs::lastError().
    */
    VSRESULT clipPlane( unsigned int inPlaneIndex, McPlane & outPlane ) const; // LOCAL_GET

    /** Returns the scaling factor used to map raw data values to
        physical values. The raw data values of the volume can be mapped
        to physical values (e.g. Hounsfield values) by applying the
        following formula:
        \code
        value = data * rescaleSlope() + rescaleIntercept()
        \endcode
        In the graphical user-interface of an application typically
        only mapped physical values are displayed.
        \sa rescaleIntercept(), rescale()
        \return
                 Current scaling factor.
    */
    float rescaleSlope() const; // LOCAL_GET

    /** Sets the scaling factor used to map raw data values to
        physical values. Usually this method will be called when
        creating or initializing a data volume, e.g. in a reader.
        \sa rescaleSlope()
        \param  inValue
                New scaling factor.
    */
    void setRescaleSlope(float inValue); // VS_RELAY

    /** Returns the offset used to map raw data values to
        physical values. The raw data values of the volume can be mapped
        to physical values (e.g. Hounsfield values) by applying the
        following formula:
        \code
        value = data * rescaleSlope() + rescaleIntercept()
        \endcode
        In the graphical user-interface of an application typically
        only mapped physical values are displayed.
        \sa rescaleSlope(), rescale()
        \return
                 Current offset for data mapping.
    */
    float rescaleIntercept() const; // LOCAL_GET

    /** Sets the offset used to map raw data values to
        physical values. Usually this method will be called when
        creating or initializing a data volume, e.g. in a reader.
        \sa rescaleIntercept()
        \param  inValue
                New offset for data mapping.
    */
    void setRescaleIntercept(float inValue); // VS_RELAY

    /** Maps a raw data value to a physical value.
        \sa rescaleSlope(), rescaleIntercept()
        \param  inValue
                Raw data value to be mapped.
        \return Mapped physical value.
    */
    float rescale(float inValue) const { return inValue*rescaleSlope() + rescaleIntercept(); }

    /** Maps a physical value to a raw data value.
        \sa rescaleSlope(), rescaleIntercept()
        \param  inValue
                Pysical value to be mapped.
        \return Mapped raw data value.
    */
    float scale(float inValue) const { return (inValue-rescaleIntercept())/rescaleSlope(); }

    /** Returns the name of the file the volume has been read from.
        If the volume has not been read from a file the method returns
        false and \c outFilename is not modified.

        \param  outFilename
                Name of file the volume has been read from.
        \return True if filename was set, false otherwise.
    */
    bool getFilename(McString& outFilename); // LOCAL_GET




    /** Synchronize the parameters with the remote side.
    */
    void syncParameters(VsVolume::ParamType type);

    // This function is only for internal use (for syncParameters())
    void syncParameters(VsVolume::ParamType type, HxParamBundle & inBundle, bool workerside = false); // VS_RELAY

    //void copyParameters(HxParamBundle& inBundle); // VS_RELAY
    void setDataWindow(float vmin, float vmax); // VS_RELAY
    void recomputeBoundingBoxAllLevels(); // VS_RELAY

    void doneReading(bool success); // VS_RELAY

#ifndef HIDDEN_FROM_DOC
    ////////////////////////////////////////
    // verification methods for WAN
    ////////////////////////////////////////
    bool verify_parameters(const VsMsg & inValue, bool workerSide=false, VsVolume::ParamType type=VsVolume::P_SHARED) const; // VS_SYNC_CALL
    bool verify_getMaterials(const VsMsg & inValue, bool workerSide=false) const; // VS_SYNC_CALL
#endif
};


#endif

/// @}
