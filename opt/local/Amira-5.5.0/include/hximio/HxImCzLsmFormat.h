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

/// @addtogroup hximio hximio
/// @{
#ifndef HXIMCZLSMFORMAT_H
#define HXIMCZLSMFORMAT_H

#include <amiramesh/HxParamBundle.h>

#include "HxImFormatInterface.h"
#include "HxImTiffFormat.h"

//----------------------------------------------------------------------------
// Internal LSM Structures
//----------------------------------------------------------------------------
#define UINT16 DIM_UINT16
#define UINT32 DIM_UINT32
#define SINT32 DIM_INT32
#define FLOAT64 DIM_FLOAT64


#pragma pack(push, 1)
typedef struct CZ_LSMINFO {
    UINT32   u32MagicNumber;
    SINT32   s32StructureSize;
    SINT32   s32DimensionX;
    SINT32   s32DimensionY;
    SINT32   s32DimensionZ;
    SINT32   s32DimensionChannels;
    SINT32   s32DimensionTime;
    SINT32   s32DataType;
    SINT32   s32ThumbnailX;
    SINT32   s32ThumbnailY;
    FLOAT64  f64VoxelSizeX;
    FLOAT64  f64VoxelSizeY;
    FLOAT64  f64VoxelSizeZ;
    FLOAT64  f64OriginX;
    FLOAT64  f64OriginY;
    FLOAT64  f64OriginZ;
    UINT16   u16ScanType;
    UINT16   u16SpectralScan;
    UINT32   u32DataType;
    UINT32   u32OffsetVectorOverlay;
    UINT32   u32OffsetInputLut;
    UINT32   u32OffsetOutputLut;
    UINT32   u32OffsetChannelColors;
    FLOAT64  f64TimeIntervall;
    UINT32   u32OffsetChannelDataTypes;
    UINT32   u32OffsetScanInformation;
    UINT32   u32OffsetKsData;
    UINT32   u32OffsetTimeStamps;
    UINT32   u32OffsetEventList;
    UINT32   u32OffsetRoi;
    UINT32   u32OffsetBleachRoi;
    UINT32   u32OffsetNextRecording;
    FLOAT64  f64DisplayAspectX;
    FLOAT64  f64DisplayAspectY;
    FLOAT64  f64DisplayAspectZ;
    FLOAT64  f64DisplayAspectTime;
    UINT32   u32MeanOfRoisOverlayOffset;
    UINT32   u32TopoIsolineOverlayOffset;
    UINT32   u32TopoProfileOverlayOffset;
    UINT32   u32LinescanOverlayOffset;
    UINT32   u32ToolbarFlags;
    UINT32   u32Reserved [ 90 ];
} CZ_LSMINFO;

typedef struct CZ_LSMSCANINFO
{
    UINT32 entry;
    UINT32 blockType;
    UINT32 dataSize;
} CZ_LSMSCANINFO;

typedef struct CZ_LSMCHANNELINFO
{
    SINT32 s32BlockSize;
    SINT32 s32NumberColors;
    SINT32 s32NumberNames;
    SINT32 s32ColorsOffset;
    SINT32 s32NamesOffset;
    SINT32 s32Mono;
} CZ_LSMCHANNELINFO;

#pragma pack(pop)

#pragma pack(push, 1)
typedef struct CZ_ChannelColors {
    SINT32 s32BlockSize;    // Size of the structure in bytes including the name strings and colors.
    SINT32 s32NumberColors; // Number of colors in the color array; should be the same as the number of channels.
    SINT32 s32NumberNames;  // Number of character strings for the channel names; should be the same as the number of channels.
    SINT32 s32ColorsOffset; // Offset relative ti the start of the structure to the UINT32 array of channel colors.
    // Each array entry contains a color with intensity values in the range 0..255 for the three color components
    SINT32 s32NamesOffset;  // Offset relative ti the start of the structure to the list of channel names. The list of channel names is a series of \0-terminated ANSI character strings.
    SINT32 s32Mono;         // If unequal zero the Mono button in the LSM-imagefenster  window was peressed
} CZ_ChannelColors;
#pragma pack(pop)

//----------------------------------------------------------------------------
// TIFF Codec-wise Fluoview Structure
//----------------------------------------------------------------------------
typedef struct TDimLsmInfo
{
    int ch;        // number of channels in each image of the sequence
    int z_slices;  // number of Z slices for each time instance
    int t_frames;  // number of time frames in the sequence
    int pages;     // the value of consequtive images generated by driver
    double res[4]; // pixel resolution for XYZT
    CZ_LSMINFO lsm_info; // actual header structure retreived form the image
    CZ_ChannelColors lsm_colors;

    //internal
    int pages_tiff;
} TDimLsmInfo;

/** Data types. */
enum CZ_DataTypes
{
    TYPE_SUBBLOCK = 0,
    TYPE_ASCII = 2,
    TYPE_LONG = 4,
    TYPE_RATIONAL = 5
};
/** Subblock types. */
enum CZ_SubblockTypes
{
    SUBBLOCK_RECORDING = 0x10000000,
    SUBBLOCK_LASERS = 0x30000000,
    SUBBLOCK_LASER = 0x50000000,
    SUBBLOCK_TRACKS = 0x20000000,
    SUBBLOCK_TRACK = 0x40000000,
    SUBBLOCK_DETECTION_CHANNELS = 0x60000000,
    SUBBLOCK_DETECTION_CHANNEL = 0x70000000,
    SUBBLOCK_ILLUMINATION_CHANNELS = 0x80000000,
    SUBBLOCK_ILLUMINATION_CHANNEL = 0x90000000,
    SUBBLOCK_BEAM_SPLITTERS = 0xa0000000,
    SUBBLOCK_BEAM_SPLITTER = 0xb0000000,
    SUBBLOCK_DATA_CHANNELS = 0xc0000000,
    SUBBLOCK_DATA_CHANNEL = 0xd0000000,
    SUBBLOCK_TIMERS = 0x11000000,
    SUBBLOCK_TIMER = 0x12000000,
    SUBBLOCK_MARKERS = 0x13000000,
    SUBBLOCK_MARKER = 0x14000000,
    SUBBLOCK_END = (int) 0xffffffff
};
/*
private static final int SUBBLOCK_GAMMA = 1;
private static final int SUBBLOCK_BRIGHTNESS = 2;
private static final int SUBBLOCK_CONTRAST = 3;
private static final int SUBBLOCK_RAMP = 4;
private static final int SUBBLOCK_KNOTS = 5;
private static final int SUBBLOCK_PALETTE = 6;
*/
/** Sub Data types. */
enum CZ_SubblockEntry
{
    RECORDING_ENTRY_NAME = 0x10000001,
    RECORDING_ENTRY_DESCRIPTION = 0x10000002,
    RECORDING_ENTRY_NOTES = 0x10000003,
    RECORDING_ENTRY_OBJECTIVE = 0x10000004,
    RECORDING_ENTRY_PROCESSING_SUMMARY =  0x10000005,
    RECORDING_ENTRY_SPECIAL_SCAN_MODE  =  0x10000006,
    RECORDING_ENTRY_SCAN_TYPE =  0x10000007,
    OLEDB_RECORDING_ENTRY_SCAN_MODE =  0x10000008,
    RECORDING_ENTRY_NUMBER_OF_STACKS =  0x10000009,
    RECORDING_ENTRY_LINES_PER_PLANE =  0x1000000A,
    RECORDING_ENTRY_SAMPLES_PER_LINE =  0x1000000B,
    RECORDING_ENTRY_PLANES_PER_VOLUME =  0x1000000C,
    RECORDING_ENTRY_IMAGES_WIDTH =  0x1000000D,
    RECORDING_ENTRY_IMAGES_HEIGHT =  0x1000000E,

    RECORDING_ENTRY_IMAGES_NUMBER_PLANES = 0x1000000F,
    RECORDING_ENTRY_IMAGES_NUMBER_STACKS = 0x10000010,
    RECORDING_ENTRY_IMAGES_NUMBER_CHANNELS = 0x10000011,

    RECORDING_ENTRY_LINSCAN_XY_SIZE = 0x10000012,
    RECORDING_ENTRY_SCAN_DIRECTION = 0x10000013,
    RECORDING_ENTRY_TIME_SERIES = 0x10000014,
    RECORDING_ENTRY_ORIGINAL_SCAN_DATA = 0x10000015,
    RECORDING_ENTRY_ZOOM_X= 0x10000016,
    RECORDING_ENTRY_ZOOM_Y = 0x10000017,
    RECORDING_ENTRY_ZOOM_Z = 0x10000018,
    RECORDING_ENTRY_SAMPLE_0X = 0x10000019,
    RECORDING_ENTRY_SAMPLE_0Y = 0x1000001A,
    RECORDING_ENTRY_SAMPLE_0Z = 0x1000001B,
    RECORDING_ENTRY_SAMPLE_SPACING = 0x1000001C,
    RECORDING_ENTRY_LINE_SPACING = 0x1000001D,
    RECORDING_ENTRY_PLANE_SPACING = 0x1000001E,
    RECORDING_ENTRY_PLANE_WIDTH = 0x1000001F,
    RECORDING_ENTRY_PLANE_HEIGHT = 0x10000020,
    RECORDING_ENTRY_VOLUME_DEPTH = 0x10000021,
    RECORDING_ENTRY_ROTATION = 0x10000034,
    RECORDING_ENTRY_NUTATION = 0x10000023,
    RECORDING_ENTRY_PRECESSION = 0x10000035,
    RECORDING_ENTRY_SAMPLE_0TIME = 0x10000036,
    RECORDING_ENTRY_START_SCAN_TRIGGER_IN = 0x10000037,
    RECORDING_ENTRY_START_SCAN_TRIGGER_OUT = 0x10000038,
    RECORDING_ENTRY_START_SCAN_EVENT = 0x10000039,
    RECORDING_ENTRY_START_SCAN_TIME = 0x10000040,
    RECORDING_ENTRY_STOP_SCAN_TRIGGER_IN = 0x10000041,
    RECORDING_ENTRY_STOP_SCAN_TRIGGER_OUT = 0x10000042,
    RECORDING_ENTRY_STOP_SCAN_EVENT = 0x10000043,
    RECORDING_ENTRY_STOP_SCAN_TIME = 0x10000044,
    RECORDING_ENTRY_USE_ROIS = 0x10000045,


    TRACK_ENTRY_MULTIPLEX_TYPE = 0x40000001,
    TRACK_ENTRY_MULTIPLEX_ORDER  = 0x40000002,
    TRACK_ENTRY_SAMPLING_MODE = 0x40000003,
    TRACK_ENTRY_SAMPLING_METHOD = 0x40000004,
    TRACK_ENTRY_SAMPLING_NUMBER = 0x40000005,
    TRACK_ENTRY_ACQUIRE = 0x40000006,
    TRACK_ENTRY_SAMPLE_OBSERVATION_TIME = 0x40000007,
    TRACK_ENTRY_TIME_BETWEEN_STACKS = 0x4000000B,
    TRACK_ENTRY_NAME = 0x4000000C,
    TRACK_ENTRY_COLLIMATOR1_NAME = 0x4000000D,
    TRACK_ENTRY_COLLIMATOR1_POSITION = 0x4000000E,
    TRACK_ENTRY_COLLIMATOR2_NAME = 0x4000000F,
    TRACK_ENTRY_COLLIMATOR2_POSITION = 0x40000010,
    TRACK_ENTRY_IS_BLEACH_TRACK = 0x40000011,
    TRACK_ENTRY_IS_BLEACH_AFTER_SCAN_NUMBER = 0x40000012,
    TRACK_ENTRY_BLEACH_SCAN_NUMBER = 0x40000013,
    TRACK_ENTRY_TRIGGER_IN = 0x40000014,
    TRACK_ENTRY_TRIGGER_OUT = 0x40000015,
    TRACK_ENTRY_IS_RATIO_TRACK = 0x40000016,
    TRACK_ENTRY_BLEACH_COUNT = 0x40000017,


    LASER_ENTRY_NAME = 0x50000001,
    LASER_ENTRY_ACQUIRE = 0x50000002,
    LASER_ENTRY_POWER = 0x50000003,

    CHANNEL_ENTRY_INTEGRATION_MODE = 0x70000001,
    CHANNEL_ENTRY_SPECIAL_MODE = 0x70000002,
    CHANNEL_ENTRY_DETECTOR_GAIN = 0x70000003,
    CHANNEL_ENTRY_DETECTOR_GAIN_LAST = 0x70000004,
    CHANNEL_ENTRY_AMPLIFIER_GAIN_FIRST = 0x70000005,
    CHANNEL_ENTRY_AMPLIFIER_GAIN_LAST = 0x70000006,
    CHANNEL_ENTRY_AMPLIFIER_OFFS_FIRST = 0x70000007,
    CHANNEL_ENTRY_AMPLIFIER_OFFS_LAST = 0x70000008,
    CHANNEL_ENTRY_PINHOLE_DIAMETER = 0x70000009,

    CHANNEL_ENTRY_COUNTING_TRIGGER = 0x7000000A,
    CHANNEL_ENTRY_ACQUIRE = 0x7000000B,
    CHANNEL_POINT_DETECTOR_NAME = 0x7000000C,
    CHANNEL_AMPLIFIER_NAME = 0x7000000D,
    CHANNEL_PINHOLE_NAME = 0x7000000E,
    CHANNEL_FILTER_SET_NAME = 0x7000000F,
    CHANNEL_FILTER_NAME = 0x70000010,
    CHANNEL_INTEGRATOR_NAME = 0x70000013,
    CHANNEL_DETECTION_CHANNEL_NAME = 0x70000014,

    CHANNEL_ENTRY_SPI_WAVELENGTH_START = 0x70000022,
    CHANNEL_ENTRY_SPI_WAVELENGTH_END = 0x70000023,

    ILLUMCHANNEL_ENTRY_NAME = 0x90000001,
    ILLUMCHANNEL_ENTRY_POWER = 0x90000002,
    ILLUMCHANNEL_ENTRY_WAVELENGTH = 0x90000003,
    ILLUMCHANNEL_ENTRY_ACQUIRE = 0x90000004,
    ILLUMCHANNEL_DETCHANNEL_NAME = 0x90000005,

    BEAMSPLITTER_ENTRY_FILTER_SET = 0x0B0000001,
    BEAMSPLITTER_ENTRY_FILTER = 0xB0000002,
    BEAMSPLITTER_ENTRY_NAME = 0xB0000003,


    START_TIME = 0x10000036,

    DATACHANNEL_ENTRY_NAME = 0xD0000001,
    DATACHANNEL_ENTRY_COLOR = 0xD0000004,
    DATACHANNEL_ENTRY_SAMPLETYPE = 0xD0000005,
    DATACHANNEL_ENTRY_BITSPERSAMPLE = 0xD0000006,
    DATACHANNEL_ENTRY_RATIO_TYPE = 0xD0000007,
    DATACHANNEL_ENTRY_RATIO_TRACK1 = 0xD0000008,
    DATACHANNEL_ENTRY_RATIO_CHANNEL1 = 0xD000000A,
    DATACHANNEL_ENTRY_RATIO_TRACK2 = 0xD0000009,
    DATACHANNEL_ENTRY_RATIO_CHANNEL2 = 0xD000000B,
    DATACHANNEL_ENTRY_RATIO_CONST1  = 0xD000000C,
    DATACHANNEL_ENTRY_RATIO_CONST2  = 0xD000000D,
    DATACHANNEL_ENTRY_RATIO_CONST3  = 0xD000000E,
    DATACHANNEL_ENTRY_RATIO_CONST4  = 0xD000000F,

    TIMER_ENTRY_NAME = 0x12000001,
    TIMER_ENTRY_DESCRIPTION = 0x12000002,
    TIMER_ENTRY_INTERVAL = 0x12000003,
    TIMER_ENTRY_TRIGGER_IN = 0x12000004,
    TIMER_ENTRY_TRIGGER_OUT = 0x12000005,
    TIMER_ENTRY_ACTIVATION_TIME = 0x12000006,
    TIMER_ENTRY_ACTIVATION_NUMBER = 0x12000007,

    MARKER_ENTRY_NAME = 0x14000001,
    MARKER_ENTRY_DESCRIPTION = 0x14000002,
    MARKER_ENTRY_TRIGGER_IN = 0x14000003,
    MARKER_ENTRY_TRIGGER_OUT = 0x14000004
};

#undef UINT32
#undef SINT32
#undef FLOAT64

struct TDimTiffParams;

HxParamBundle * lsmReadScanInfo(TDimTiffParams*);
void lsmInfo(TDimTiffParams* tiffpar, HxParamBundle* param);

#endif // HXIMCZLSMFORMAT_H

/// @}
