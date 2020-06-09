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

/// @addtogroup vssegmentation vssegmentation
/// @{
#ifndef VS_LABEL_TOOLS_H
#define VS_LABEL_TOOLS_H

#include "VsSegmentationAPI.h"
#include <vsvolren/Vs.h>
#include <vsvolren/VsInterface.h>

#include <mclib/McDArray.h>
#include <mclib/McPrimType.h>

class McBitfield;
class McBox3i;
class McFilename;
class VsData;
class VsVolume;

// VS_RELAY_CLASS VsLabelTools VsRelay

/** This class provides a set of helper functions operating on label fields.
    In particular, materials can be written to file and read back. There is
    the notion of a "material cache", i.e. a directory containing files with
    single material label fields. These files can be read and merged into an
    existing label field. The material cache is located in the directory
    "<volume-file-basename>.seg/precomputed".
*/
class VSSEGMENTATION_API VsLabelTools : public VsInterface
{
    VS_DECL_INTERFACE        ( VsLabelTools )
    VS_DECL_INTERFACE_FACTORY( VsLabelTools )
    VS_DECL_INTERFACE_RELAY  ( VsLabelTools )

public:

    VsLabelTools( VsMeta * inMeta = 0 );
    ~VsLabelTools();

    /** Insertion policy to be applied in insertBitfield(). */
    enum InsertionPolicy
    {
        /** If bit is set a voxel will be assigned to the specified
            material regardless of the actual assignment of that voxel. */
        INSERT,
        /** If bit is set a voxel will be assigned to the specified material
            unless the voxel is already assigned to some other material. */
        INSERT_PRESERVE_OTHERS,
        /** If bit is set a voxel will be assigned to the specified
            material regardless of the actual assignment of that voxel;
            if bit is unset and the voxel is already assigned to the
            specified material the voxel will be unset (assigned to 0). */
        REPLACE,
        /** If bit is set a voxel will be assigned to the specified material
            unless the voxel is already assigned to some other material;
            if bit is unset and the voxel is already assigned to the
            specified material the voxel will be unset (assigned to 0). */
        REPLACE_PRESERVE_OTHERS,
        /** If bit is set a voxel will be assigned 0 material
            regardless of the actual assignment of that voxel.
            This is an alias to INSERT with materialIdx equal to 0.
            
            label bitfield result
            X     0        X
            X     1        0
            */
        CLEAR,
        /** If bit is set a voxel will be assigned 0 material
            unless the voxel is already assigned to some material
            other than materialIdx.
            
            label bitfield result
            X     0        X
            idx   1        0
            !=idx 1        !=idx
            */
        CLEAR_PRESERVE_OTHERS
    };

    /** Constructs a bitfield from a label field. The bitfield will be resized
        so that the number of bits matches the number of voxels in the input
        label field. A bit is set if the corresponding voxel in the label field
        is assigned to the specified material. Currently only contiguous label
        fields are supported.

        \param[in] labelData Label field (one byte per voxel).
        \param[out] bitfield Bitfield to be computed.
        \param[in] materialIdx Index of material to be extracted.
        \param[in] ignoreSelection if true the selection bits (highest bit) are not taken into account,
                                   thus the range of materials is from 0 to 255 and otherwise from 0 to 127
        \return VS_OK on success, VS_FAILED otherwise.
            To get extended error information, call Vs::lastError().
    */
    static VSRESULT extractBitfield(VsData* labelData, McBitfield& bitfield, int materialIdx, bool ignoreSelection = true);

    /** Inserts a bitfield into an existing label field. The number of bits
        in the bitfield must match the number of voxels in the label field.
        A voxel in the label field will be assigned to the specified material
        if the corresponding bit in the bitfield is set (insertion policy
        VsLabelTools::INSERT). If existing assignments should be preserved or
        already assigned voxels should also be unset, different insertion
        policies might be specified, see InsertionPolicy. Currently only
        contiguous label fields are supported.

        \param[in,out] labelData    Label field to be modified.
        \param[in] bitfield         Bitfield representing a segmentation result.
        \param[in] policy           Insertion policy, see InsertionPolicy.
        \param[in] lockVector       a array of bools which contains a list of all currently available materials
                                    and their lock status, where true is locked and 0 is unlocked
        \param[in] lockVectorLength length of the lock vector array
        \param[in] ignoreSelection  if true the selection bits (highest bit) are not taken into account,
                                    thus the range of materials is from 0 to 255 and otherwise from 0 to 127
        \return VS_OK on success, VS_FAILED otherwise.
            To get extended error information, call Vs::lastError().
    */
    static VSRESULT insertBitfield(VsData* labelData, McBitfield& bitfield,
        int materialIdx, InsertionPolicy policy, bool *lockVector = 0, int lockVectorlength = 0, bool ignoreSelection = true);
    

    /** Reads a material file and inserts it into an existing label field.
        The labels at level 1 will be updated automatically. */
    static VSRESULT readMaterialFromFile(VsVolume* volume, const char* material,
        InsertionPolicy policy, const char* user, const char* filename, bool ignoreSelection = true); // VS_FORBIDDEN_ON_CLIENT

    /** Writes a material from a label field into a material file. If
        filename is 0 the default material filename will be used.

        \param[in] volume Volume containg label field to be exported.
        \param[in] materialIdx Index of material to be exported.
        \param[in] user User name.
        \param[in] filename Name of material file to be written. If this
            is 0, getMaterialFilename() will be used instead.
        \return VS_OK if file was successfully written, VS_FAILED otherwise.
                To get extended error information, call Vs::lastError(). The
                method might fail e.g. if the input volume does not contain
                label data or if the specified material does not exist.
    */
    static VSRESULT writeMaterialToFile(VsVolume* volume, int materialIdx, const char* user, const char* filename); // VS_FORBIDDEN_ON_CLIENT

    /** Writes the specified bitfield into a material file. The size of the
        bitfield must match the dimensions of the level 0 label data of the
        volume. If the name of the material file is 0, the default file
        name for the specified material will be used.

        \param[in] volume       Volume object to be segmented.
        \param[in] bitfield     Bitfield representing the segmentation to be
                                written into a file.
        \param[in] user         User name.
        \param[in] material     Material name.
        \param[in] filename     Name of material file to be written. If this
                                is 0, getMaterialFilename() will be used instead.
        \return VS_OK if file was successfully written, VS_FAILED otherwise.
                To get extended error information, call Vs::lastError().
    */
    static VSRESULT writeMaterialToFile(VsVolume* volume, const McBitfield& bitfield, const char* material, const char* user, const char* filename); // VS_FORBIDDEN_ON_CLIENT

    /** Returns the default name of a material file. The file will be called
        "<volume-file-basename>.seg/precomputed/<material>.bit" where
        <volume-file-basename> is the name of the volume file without extension
        and <material> is the name of the material.

        If user is specified, a filename is a user-specific material directory
        is returned (additional subdirectory users/<user> under precomputed).

        \param[in] volume       Volume object to be segmented.
        \param[in] material     Material name.
        \param[in] user         User name, might be 0.
        \param[out] filename    Absolute path of material file.
        \return VS_OK if filename was set, VS_FAILED otherwise (e.g. if
            volume was not read from disk but was created dynamically).
    */
    static VSRESULT getMaterialFilename(VsVolume* volume, const char* material, const char* user, McFilename& filename);

    /** Checks if there is a precomputed/saved file. The file will be called
        "<volume-file-basename>.seg/precomputed/<material>.bit" where
        <volume-file-basename> is the name of the volume file without extension
        and <material> is the name of the material.

        If user is specified, a filename is a user-specific material directory
        is returned (additional subdirectory users/<user> under precomputed).

        \param[in] volume       Volume object to be segmented.
        \param[in] material     Material name.
        \param[in] user         User name, might be 0.
        \return VS_OK if the file does exists, VS_FAILED otherwise.
    */
    VSRESULT doesSavedFileExists( VsVolume* volume, const char* material, const char* user); // VS_SYNC_CALL

    /** Creates the material directory for specified volume. If the material
        directory already exists, the method does nothing. The name of the
        material directory is "<volume-file-basename>.seg/precomputed" where
        <volume-file-basename> is the name of the volume file without extension.

        If user is specified, a user-specific material directory is created
        (additional subdirectory users/<user> under precomputed).

        \param[in] volume       Volume object to be segmented.
        \param[in] user         Optional user name.
        \return VS_OK if material directory already existed or was successfully
            created, VS_FAILED otherwise (e.g. if volume was not read from disk).
    */
    static VSRESULT createMaterialDirectory(VsVolume* volume, const char* user);


    VSRESULT relabelMaterial(VsVolume* volume, int materialIdx, int newMaterialIdx, const McBox3i* inBox = 0, bool ignoreSelection = true); // VS_SYNC_CALL
    
    /** Replaces labels with inLabelIndex with 0. Currently does not care about
        the selection bit, but treats this bit as part of the label index
        (probably additional parameter is required to specify this?)
        If inBBox is not provided, this operation is done in the whole label field,
        otherwise only in the provided bounding box. 
    */
    VSRESULT replaceWith0(VsData* inLabelData, int materialIndex, const McBox3i* inBBox = 0, bool ignoreSelection = true); // VS_SYNC_CALL

    /** Counts the number of voxels assigned to each material in the given label data */
    VSRESULT countMaterialVoxels(
        VsData*            inLabelData,
        McDArray<mcint64>& outVoxelCount,   // output of the function. array will contain 256 elements
        bool ignoreSelection = true         // ignore selction bit (highest bit)
     ); // VS_SYNC_CALL

    /** Sets the highest bit for every byte of the label field, 
        foreach "set" bit of the selection bitfield.   

        \param labelData        Label data to assigne to
        \param selectionBf      Selection bitfield to be assigned
        \param bbox             Selection bounding box
        \param lockVector       a list of all defined materials and their coresponding lock status
                                if null all materials are considered as unlocked
        \param lockVectorLength number of materials
        \return                 VS_OK if selection was set successfully otherwise VS_FAILED (e.g.
                                the dims of the labelfield and the selection bitfield are not equal ...)
    */
    static VSRESULT assignToSelection(VsData* labelData, const McBitfield& selectionBf, const McBox3i &bbox, bool *lockVector = 0, int lockVectorLength = 0);


    /** Removes the highest bit for every byte of the label field, 
        where a bit of the selection bitfield and the highest bit of the label field byte is set.   

        \param labelData        Label data from where to remove 
        \param selectionBf      Selection bitfield to be removed
        \param bbox             Selection bounding box
        \return                 VS_OK if selection was set successfully otherwise VS_FAILED (e.g.
                                the dims of the labelfield and the selection bitfield are not equal ...)
    */
    static VSRESULT removeFromSelection(VsData* labelData, const McBitfield& selectionBf);//, const McBox3i &bbox);

    /** Constructs a bitfield from a label field. The bitfield will be resized
        so that the number of bits matches the number of voxels in the input
        label field. A bit is set if the corresponding voxel in the label field
        is selected. Currently only contiguous label fields are supported.

        \param[in] labelData Label field (one byte per voxel).
        \param[out] bitfield Bitfield to be computed.
        \return VS_OK on success, VS_FAILED otherwise.
            To get extended error information, call Vs::lastError().
    */
    static VSRESULT extractSelection(VsData* labelData, McBitfield& bitfield);
    
    /** Resets a selection. 
        
        Unsets the highest bit of every byte of the label field if it is set.

        \param labelData Label data to reset
    */
    VSRESULT clearSelection(VsData* labelData); // VS_SYNC_CALL

    
    /** Adds the current selection to a specified material. Only non looked materials will be 
        overwritten. 
        
        \param labelData
        \param matIdx material to which selection should be added 
      
        \return        
    */
    VSRESULT addSelectionToMaterial(VsVolume *inVol, int matIdx); // VS_SYNC_CALL
    
    /** Removes the current selection from a specified material, respectively sets it to the exterior 
        material.

        \param labelData 
        \param matIdx material from which selection should be removed
        \return
    */
    VSRESULT removeSelectionFromMaterial(VsVolume *inVol, int matIdx); // VS_SYNC_CALL

    /** Returns a list of all currently available materiels and their lock status,
        where 1 is locked and 0 is unlocked

        \param  densityData 
        \param  materialLockStatus a list containing all materiel lock status information 
        \return 
    */
    static VSRESULT getMaterialLockStatus(VsData * densityData, McDArray<bool> &materialLockStatus);
    
    /// TODO: merge this helper functions to McBitfield,  because this is not the right place
    static mculong lastSetBit(McBitfield& bitfield);
    static mculong firstSetBit(McBitfield& bitfield);
};

#endif

/// @}
