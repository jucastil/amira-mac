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

/// @addtogroup dicom dicom
/// @{
#ifndef DICOM_DICOM_H
#define DICOM_DICOM_H

#include <stdio.h>
#include <dicom/DicomWinDLLApi.h>


/* often used DICOM groups with elements */
/* see DICOM part 6: Data Dictionary     */
#define DE_GROUP_LENGTH              0x0000
/* ------------------------------------- */
#define DG_FILE_META          0x0002
#define DE_META_INFORMATION_VERSION      0x0001
#define DE_META_STORAGE_SOP_CLASS_UID    0x0002
#define DE_META_STORAGE_SOP_INSTANCE_UID 0x0003
#define DE_META_TRANSFER_SYNTAX          0x0010
#define DE_META_IMPLEMENTATION_CLASS     0x0012
#define DE_META_IMPLEMENTATION_VER_NAME  0x0013
#define DE_META_SOURCE_APP_ENTITY_TITLE  0x0016
#define DE_META_PRIVATE_INFO_CREATOR_UID 0x0100
#define DE_META_PRIVATE_INFO             0x0102
/* ------------------------------------- */
#define DG_FILE_SET           0x0004
#define DE_FILE_SET_ID               0x1130
#define DE_FILE_SET_DESCRIPTOR       0x1141
#define DE_FILE_CHARACTER_SET        0x1142
#define DE_FILE_FIRST_RECORD_OFFSET  0x1200
#define DE_FILE_LAST_RECORD_OFFSET   0x1202
#define DE_FILE_SET_CONSISTENCY_FLAG 0x1212
#define DE_FILE_DIR_RECORD_SEQUENCE  0x1220
#define DE_FILE_NEXT_RECORD_OFFSET   0x1400
#define DE_FILE_RECORD_IN_USE_FLAG   0x1410
#define DE_FILE_DIR_RECORD_TYPE      0x1430
#define DE_FILE_PRIVATE_RECORD_UID   0x1432
#define DE_FILE_REFERENCED_FILE_ID   0x1500
#define DE_FILE_DIR_RECORD_OFFSET    0x1504
#define DE_FILE_REFERENCED_SOP_CLASS 0x1510
#define DE_FILE_REFERENCED_SOP_INST  0x1511
#define DE_FILE_REF_TRANSFER_SYNTAX  0x1512
#define DE_FILE_NUMBER_OF_REFERENCES 0x1600
/* ------------------------------------- */
#define DG_IDENTIFY           0x0008
#define DE_ID_LENGTH_TO_END          0x0001
#define DE_ID_SPEC_CHARACTER_SET     0x0005
#define DE_ID_IMAGE_TYPE             0x0008
#define DE_ID_INST_CREATION_DATE     0x0012
#define DE_ID_INST_CREATION_TIME     0x0013
#define DE_ID_INST_CREATOR_UID       0x0014
#define DE_ID_SOP_CLASS_UID          0x0016
#define DE_ID_SOP_INSTANCE_UID       0x0018
#define DE_ID_STUDY_DATE             0x0020
#define DE_ID_SERIES_DATE            0x0021
#define DE_ID_ACQUISITION_DATE       0x0022
#define DE_ID_IMAGE_DATE             0x0023
#define DE_ID_OVERLAY_DATE           0x0024
#define DE_ID_CURVE_DATE             0x0025
#define DE_ID_STUDY_TIME             0x0030
#define DE_ID_SERIES_TIME            0x0031
#define DE_ID_ACQUISITION_TIME       0x0032
#define DE_ID_IMAGE_TIME             0x0033
#define DE_ID_ACCESSION_NUMBER       0x0050
#define DE_ID_MODALITY               0x0060
#define DE_ID_CONVERSION_TYPE        0x0064
#define DE_ID_MANUFACTURER           0x0070
#define DE_ID_INSTITUTION_NAME       0x0080
#define DE_ID_INSTITUTION_ADDRESS    0x0081
#define DE_ID_INSTITUTION_CODE       0x0082
#define DE_ID_REFERRING_PHYS_NAME    0x0090
#define DE_ID_REFERRING_PHYS_ADDR    0x0092
#define DE_ID_REFERRING_PHYS_TEL     0x0094
#define DE_ID_STATION_NAME           0x1010
#define DE_ID_STUDY_DESCRIPTION      0x1030
#define DE_ID_SERIES_DESCRIPTION     0x103E
#define DE_ID_PERFORMING_PHYS_NAME   0x1050
#define DE_ID_OPERATORS_NAME         0x1070
#define DE_ID_MANUFACTURER_MODEL     0x1090
#define DE_ID_RECOM_FRAME_RATE       0x2144
#define DE_ID_TRANSDUCER_POSITION    0x2200
#define DE_ID_TRANSDUCER_ORIENTATION 0x2204
#define DE_ID_ANATOMIC_STRUCTURE     0x2208
/* ------------------------------------- */
#define DG_PATIENT            0x0010
#define DE_PAT_NAME                  0x0010
#define DE_PAT_ID                    0x0020
#define DE_PAT_ISSUER_OF_ID          0x0021
#define DE_PAT_BIRTH_DATE            0x0030
#define DE_PAT_BIRTH_TIME            0x0032
#define DE_PAT_SEX                   0x0040
#define DE_PAT_INSURANCE_PLAN_CS     0x0050
#define DE_PAT_OTHER_PAT_ID          0x1000
#define DE_PAT_OTHER_PAT_NAMES       0x1001
#define DE_PAT_BIRTH_NAME            0x1005
#define DE_PAT_AGE                   0x1010
#define DE_PAT_SIZE                  0x1020
#define DE_PAT_WEIGHT                0x1030
#define DE_PAT_ADDRESS               0x1040
#define DE_PAT_INSURANCE_PLAN_ID     0x1050
#define DE_PAT_MOTHERS_BIRTH_NAME    0x1060
#define DE_PAT_MILITARY_RANK         0x1080
#define DE_PAT_BRANCH_OF_SERVICE     0x1081
#define DE_PAT_MEDICAL_RECORD_LOC    0x1090
#define DE_PAT_MEDICAL_ALERTS        0x2000
#define DE_PAT_CONTRAST_ALLERGIES    0x2110
#define DE_PAT_COUNTRY_OF_RESIDENCE  0x2150
#define DE_PAT_REGION_OF_RESIDENCE   0x2152
#define DE_PAT_TELEPHONE             0x2154
#define DE_PAT_ETHNIC_GROUP          0x2160
#define DE_PAT_OCCUPATION            0x2180
#define DE_PAT_SMOKING_STATUS        0x21A0
#define DE_PAT_ADDITIONAL_HISTORY    0x21B0
#define DE_PAT_PREGNANCY_STATUS      0x21C0
#define DE_PAT_LAST_MENSTRUAL_DATE   0x21D0
#define DE_PAT_RELIGIOUS_PREF        0x21F0
#define DE_PAT_COMMENTS              0x4000
/* ------------------------------------- */
#define DG_ACQUISITION        0x0018
#define DE_ACQ_CONTRAST_BOLUS_AGENT  0x0010
#define DE_ACQ_BODY_PART_EXAMINED    0x0015
#define DE_ACQ_SCANNING_SEQUENCE     0x0020
#define DE_ACQ_SCAN_OPTIONS          0x0022
#define DE_ACQ_MR_ACQ_TYPE           0x0023
#define DE_ACQ_SEQUENCE_NAME         0x0024
#define DE_ACQ_SLICE_THICKNESS       0x0050
#define DE_ACQ_KVP                   0x0060
#define DE_ACQ_COUNTS_ACCUMULATED    0x0070
#define DE_ACQ_REPETITION_TIME       0x0080
#define DE_ACQ_ECHO_TIME             0x0081
#define DE_ACQ_INVERSION_TIME        0x0082
#define DE_ACQ_MAG_FIELD_STRENGTH    0x0087
#define DE_ACQ_SLICE_SPACING         0x0088
#define DE_ACQ_PROTOCOL_NAME         0x1030
#define DE_ACQ_SPATIAL_RESOLUTION    0x1050
#define DE_ACQ_RECONSTR_DIAMETER     0x1100
#define DE_ACQ_DIST_SOURCE_DETECTOR  0x1110
#define DE_ACQ_DIST_SOURCE_PATIENT   0x1111
#define DE_ACQ_GANTRY_TILT           0x1120
#define DE_ACQ_TABLE_TRAVERSE        0x1131
#define DE_ACQ_ROTATION_DIRECTION    0x1140
#define DE_ACQ_ANGULAR_POSITION      0x1141
#define DE_ACQ_RADIAL_POSITION       0x1142
#define DE_ACQ_SCAN_ARC              0x1143
#define DE_ACQ_ANGULAR_STEP          0x1144
#define DE_ACQ_FOV_SHAPE             0x1147
#define DE_ACQ_FOV_DIMENSIONS        0x1149
#define DE_ACQ_EXPOSURE_TIME         0x1150
#define DE_ACQ_X_RAY_TUBE_CURRENT    0x1151
#define DE_ACQ_EXPOSURE              0x1152
#define DE_ACQ_RADIATION_SETTING     0x1155
#define DE_ACQ_FILTER_TYPE           0x1160
#define DE_ACQ_INTENSIFIER_SIZE      0x1162
#define DE_ACQ_CONVOLUTION_KERNEL    0x1210
#define DE_ACQ_SCAN_VELOCITY         0x1300
#define DE_ACQ_WHOLE_BODY_TECHNIQUE  0x1301
#define DE_ACQ_SCAN_LENGTH           0x1302
#define DE_ACQ_SAR                   0x1316
#define DE_ACQ_POSITIONER_MOTION     0x1500
#define DE_ACQ_POSIT_PRIMARY_ANGLE   0x1510
#define DE_ACQ_POSIT_SECONDARY_ANGLE 0x1511
#define DE_ACQ_COMMENTS              0x4000
#define DE_ACQ_PATIENT_POSITION      0x5100
#define DE_ACQ_VIEW_POSITION         0x5101
#define DE_ACQ_DIFF_B_VALUE          0x9087
#define DE_ACQ_DIFF_GRAD_ORIENTATION 0x9089
/* ------------------------------------- */
#define DG_RELATION           0x0020
#define DE_REL_STUDY_INSTANCE_UID    0x000D
#define DE_REL_SERIES_INSTANCE_UID   0x000E
#define DE_REL_STUDY_ID              0x0010
#define DE_REL_SERIES_NUMBER         0x0011
#define DE_REL_ACQUISITION_NUMBER    0x0012
#define DE_REL_IMAGE_NUMBER          0x0013
#define DE_REL_PATIENT_ORIENTATION   0x0020
#define DE_REL_IMAGE_POSITION_RET    0x0030 /* RETIRED IN DICOM 3.0 */
#define DE_REL_IMAGE_POSITION        0x0032
#define DE_REL_IMAGE_ORIENTATION_RET 0x0035 /* RETIRED IN DICOM 3.0 */
#define DE_REL_IMAGE_ORIENTATION     0x0037
#define DE_REL_LOCATION              0x0050 /* RETIRED IN DICOM 3.0 */
#define DE_REL_FRAME_OF_REFERENCE    0x0052
#define DE_REL_LATERALITY            0x0060
#define DE_REL_SERIES_IN_STUDY       0x1000
#define DE_REL_ACQUIS_IN_SERIES      0x1001 /* RETIRED IN DICOM 3.0 */
#define DE_REL_IMAGES_IN_ACQUISITION 0x1002
#define DE_REL_IMAGES_IN_SERIES      0x1003
#define DE_REL_ACQUIS_IN_STUDY       0x1004
#define DE_REL_IMAGES_IN_STUDY       0x1005
#define DE_REL_REFERENCE             0x1020 /* RETIRED IN DICOM 3.0 */
#define DE_REL_POSITION_REFERENCE    0x1040
#define DE_REL_SLICE_LOCATION        0x1041
#define DE_REL_COMMENTS              0x4000
/* ------------------------------------- */
#define DG_IMAGE              0x0028
#define DE_IMG_SAMPLES_PER_PIXEL     0x0002
#define DE_IMG_PHOTOMETRIC_INTERPRET 0x0004
#define DE_IMG_PLANAR_CONFIGURATION  0x0006
#define DE_IMG_NUMBER_OF_FRAMES      0x0008
#define DE_IMG_FRAME_INCR_POINTER    0x0009
#define DE_IMG_ROWS                  0x0010
#define DE_IMG_COLUMNS               0x0011
#define DE_IMG_PIXEL_SPACING         0x0030
#define DE_IMG_ZOOM_FACTOR           0x0031
#define DE_IMG_ZOOM_CENTER           0x0032
#define DE_IMG_PIXEL_ASPECT_RATIO    0x0034
#define DE_IMG_BITS_ALLOCATED        0x0100
#define DE_IMG_BITS_STORED           0x0101
#define DE_IMG_HIGH_BIT              0x0102
#define DE_IMG_PIXEL_REPRESENTATION  0x0103
#define DE_IMG_SMALLEST_VALID_PIXEL  0x0104 /* RETIRED IN DICOM 3.0 */
#define DE_IMG_LARGEST_VALID_PIXEL   0x0105 /* RETIRED IN DICOM 3.0 */
#define DE_IMG_SMALLEST_PIXEL_VALUE  0x0108
#define DE_IMG_LARGEST_PIXEL_VALUE   0x0109
#define DE_IMG_PIXEL_PADDING_BIT     0x0120

#define DE_IMG_WINDOW_CENTER         0x1050
#define DE_IMG_WINDOW_WIDTH          0x1051
#define DE_IMG_RESCALE_INTERCEPT     0x1052
#define DE_IMG_RESCALE_SLOPE         0x1053
#define DE_IMG_RESCALE_TYPE          0x1054
#define DE_IMG_LOSSY_COMPRESSION     0x2110
#define DE_IMG_COMMENTS              0x4000
/* ------------------------------------- */
#define DG_STUDY              0x0032
#define DE_STUDY_COMMENTS            0x4000
/* ------------------------------------- */
#define DG_VISIT              0x0038
#define DE_VISIT_COMMENTS            0x4000
/* ------------------------------------- */
#define DG_PIXEL              0x7FE0
#define DE_PXL_DATA                  0x0010
/* ------------------------------------- */

#define DG_NONE   -1
#define DE_NONE   -1


#ifndef __cplusplus
#define inline __inline__
#endif

namespace dicom {

 /* data type definitions */
 /* --------------------- */
    typedef   signed char     s8bit;
    typedef unsigned char     u8bit;
    typedef   signed short    s16bit;
    typedef unsigned short    u16bit;
    typedef   signed int      s32bit;
    typedef unsigned int      u32bit;
#ifdef _WIN32
    typedef unsigned __int64   u64bit;
#else
    typedef unsigned long long u64bit;
#endif


 /* architecture definition (little vs. big endian) */
 /* ----------------------------------------------- */
    typedef enum {ARCH_LITTLE_ENDIAN = 0, ARCH_BIG_ENDIAN = 1} enArchitecture;

 /* value representations (see DICOM part 5: 6.2) */
 /* --------------------------------------------- */
    typedef enum {AE, AS, AT, CS, DA, DS, DT, FL, FD, IS, LO, LT,
                  PN, SH, SL, SS, ST, TM, UI, UL, US, OB, OW, SQ, UN, UT} valRep;


 /* explicit transfer syntax specification */
 /* -------------------------------------- */
    typedef enum {NONE = 0,           /* not specified */
                  IMVR_LITTLE_ENDIAN, /* implicit value repr., little endian */
                  EXVR_LITTLE_ENDIAN, /* explicit value repr., little endian */
                  EXVR_BIG_ENDIAN,    /* explicit value repr., big endian */
                  JPEG_14_LOSSLESS,   /* lossl., hierar., 1. order pred, 14 */
                  COMPR_RLE_LOSSLESS, /* lossless run length encoding */
                  COMPR_JPEG_BASELINE,/* baseline encoding (jpeg 8bit lossy), process 1.*/
                  NOT_SUPPORTED} enCoding;

    typedef struct {
        char      *uid;
        enCoding   encoding;
        char      *description;
    } transferSyntax;


 /* DICOM Data Element Structure */
 /* ---------------------------- */
    typedef struct {
        u16bit group;
        u16bit element;
        s32bit valueLen; /* u32bit is not valid, len=-1 can occur */
        u8bit  valueRep[2];
        u8bit *value;
    } dicomDataElement;


 /* a DICOM dictionary entry */
 /* ------------------------ */
    typedef  struct {
        u16bit    group;
        u16bit    element;
        valRep    dataType;
        char     *name;
    } dicomDictEntry;


    enum {PHOTOMETRIC_DEFAULT=0, PHOTOMETRIC_YBR_FULL=1};

 /* complete DICOM header including pointer to the image data */
 /* --------------------------------------------------------- */
    typedef struct {
        u8bit              preamble[128];
        u8bit              prefix[4];
        dicomDataElement  *dde;
        u16bit             numElements;
        void              *image;
        u16bit             littleEndian;
        u16bit             part10;
        u16bit             explicitVR;
        u16bit             dicomDir;
        enCoding           transferSyntax;
        u32bit             imageSize;
        u16bit             imageWidth;
        u16bit             imageHeight;
        u8bit              bytesPerPixel;
        u8bit              samplesPerPixel;
        enArchitecture     architecture;
        u16bit             numFrames;
        int                photometricInterp;
        u16bit             bitsAllocated;
        u16bit             bitsStored;
        size_t             imageSeekPosition;
    } dicomStruct;


#ifdef __cplusplus
// extern "C" {
#endif

    DICOM_API dicomStruct   * dicomReadFile (FILE *, int omitPixelData);
    DICOM_API void          * dicomReadImageData (dicomStruct *, FILE *, void *);
    DICOM_API u8bit         * dicomMapTo8 (dicomStruct *);
    DICOM_API const char    * dicomGetById (dicomStruct *, u16bit, u16bit);
    DICOM_API const char    * dicomGetByName (dicomStruct *, const char *);
    DICOM_API void            dicomFree (dicomStruct *);
    DICOM_API const char    * dicomDictionaryName (u16bit, u16bit);
    DICOM_API int             dicomDictionaryContains (u16bit, u16bit);

    DICOM_API u16bit  dicomRead16bit (u8bit *, u16bit);
    DICOM_API u32bit  dicomRead32bit (u8bit *, u16bit);
    DICOM_API u32bit  dicomAdjustLength (u8bit *, dicomDataElement *, dicomStruct *);

    DICOM_API valRep  dicomDictionaryType (u16bit, u16bit);
    DICOM_API u16bit  dicomConvert16bit (u8bit *, u16bit);
    DICOM_API u32bit  dicomConvert32bit (u8bit *, u16bit);
    DICOM_API u64bit  dicomConvert64bit (u8bit *, u16bit);

#ifdef __cplusplus
// }
#endif

} // end namespace dicom

#endif



/// @}