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
#ifndef HXIMFORMATZEISSZVI_H
#define HXIMFORMATZEISSZVI_H

#include <amiramesh/HxParamBundle.h>
#include <mclib/McBox3f.h>

//for sizes of the data types see VTE_Read func
enum VAR_TYPES_ENUM
{
    VTE_EMPTY   = 0,        //nothing
    VTE_NULL    = 1,        //nothing
    VTE_I2  = 2,            //short
    VTE_I4  = 3,            //int
    VTE_R4  = 4,            //float
    VTE_R8  = 5,            //double
    VTE_CY  = 6,            //currency value
    VTE_DATE    = 7,        //date value
    VTE_BSTR    = 8,        //bstring (unsigned long len_in_bytes, wchar_t[len/2])
    VTE_DISPATCH    = 9,
    VTE_ERROR   = 10,
    VTE_BOOL    = 11,
    VTE_VARIANT = 12,
    VTE_UNKNOWN = 13,       //16 byte big
    VTE_DECIMAL = 14,
    VTE_I1  = 16,           //signed char
    VTE_UI1 = 17,           //unsigned char
    VTE_UI2 = 18,           //unsigned short
    VTE_UI4 = 19,           //unsigned long
    VTE_I8  = 20,           //64bit
    VTE_UI8 = 21,           //unsigned 64bit
    VTE_INT = 22,
    VTE_UINT    = 23,       //unsigned int
    VTE_VOID    = 24,
    VTE_HRESULT = 25,
    VTE_PTR = 26,
    VTE_SAFEARRAY   = 27,
    VTE_CARRAY  = 28,
    VTE_USERDEFINED = 29,
    VTE_LPSTR   = 30,
    VTE_LPWSTR  = 31,
    VTE_RECORD  = 36,
    VTE_FILETIME    = 64,
    VTE_BLOB    = 65,       //see ZVI_BLOB struct aboth
    VTE_STREAM  = 66,
    VTE_STORAGE = 67,
    VTE_STREAMED_OBJECT = 68,
    VTE_STORED_OBJECT   = 69,   //wchar_t identifying a Storage name
    VTE_BLOB_OBJECT = 70,
    VTE_CF  = 71,
    VTE_CLSID   = 72,
    VTE_BSTR_BLOB   = 0xfff,
    VTE_VECTOR  = 0x1000,
    VTE_ARRAY   = 0x2000,
    VTE_BYREF   = 0x4000,
    VTE_RESERVED    = 0x8000,
    VTE_ILLEGAL = 0xffff,
    VTE_ILLEGALMASKED   = 0xfff,
    VTE_TYPEMASK    = 0xfff
};

struct ZVI_BITMAPFILEHEADER
{
    unsigned short  bfType;         //"BM"
    unsigned long   bfSize;
    unsigned short  bfReserved1;
    unsigned short  bfReserved2;
    unsigned long   bfOffBits;
};

struct ZVI_BITMAPINFOHEADER
{
    unsigned long   biSize;             //size of struct
    long            biWidth;            //width of image
    long            biHeight;           //height
    unsigned short  biPlanes;
    unsigned short  biBitCount;         //bpp of image
    unsigned long   biCompression;      //compression type (we only use uncompressed)
    unsigned long   biSizeImage;        //size of complete image in bytes
    long            biXPelsPerMeter;    //rest goes unused
    long            biYPelsPerMeter;
    unsigned long   biClrUsed;
    unsigned long   biClrImportant;
};

//blob contains binary data
struct ZVI_BLOB
{
    unsigned long cbSize;       //size of binary block
    unsigned char *pBlobData;   //actual data
};

//pallete info... unused as we only use RGB images
struct ZVI_RGBQUAD
{
    unsigned char    rgbBlue;
    unsigned char    rgbGreen;
    unsigned char    rgbRed;
    unsigned char    rgbReserved;
};

struct ZVI_BITMAPINFO
{
    ZVI_BITMAPINFOHEADER    bmiHeader;
    ZVI_RGBQUAD             bmiColors[1];
};

struct ZVI_GUID
{
    unsigned char d1[4];
    unsigned char d2[2];
    unsigned char d3[2];
    unsigned char d4[2];
    unsigned char d5[6];
};

//normal 4 pointers to AddRef/QueryInterface and so on...
struct ZVI_IUnknown
{
    wchar_t* name;          //in case that we loaded a VTE_STORED_OBJECT
                            // this member contains the name of the substorage
    unsigned long ptr[3];
};

struct ZVI_Variant
{
    void* Value;                //pointer to item of type Value_Type
    VAR_TYPES_ENUM Value_Type;  //type id of the value behind 'Value'
};

//my stuff
//linked list to save pointer to allocated mem in...
struct MemList
{
    void* item;
    MemList* next;
};

//zeiss stuff
//format of the data in 'tagImageHeaderOthers' (see below)
struct image_header_other
{
    long m_IndexX;      //x offset for position list image
    long m_IndexY;      //y offset for pos. list offset
    long m_IndexZ;      //zdimension for zstack images
    long m_IndexC;      //channel (0-x) for multichannel images
    long m_IndexT;      //time-dimension (0-x) for time laps images..
    long m_IndexS;      //always zero
    long m_Orientation; //always zero
};

enum ZvImagePixelFormat
{
    zvImagePixelFormatAny       = 0,
    zvImagePixelFormatBGR24     = 1, // = RGBA with fixed A --- supported
    zvImagePixelFormatBGRA      = 2, // = RGBA -- supported
    zvImagePixelFormatByte      = 3, // = uint8 -- supported
    zvImagePixelFormatShort     = 4, // = int16 -- supported ?? (signed or unsigned, not sure)
    zvImagePixelFormatLong      = 5, // ?= right now using int32 -- supported
    zvImagePixelFormatFloat     = 6, // = mcfloat -- supported
    zvImagePixelFormatDouble    = 7, // = mcdouble -- supported
    zvImagePixelFormatBGR48     = 8  // currently not supported
};

struct  SZVBITMAPHEADER
{
    long Width;
    long Height;
    long Depth;
    long PixelWidth;                //how many bytes per pixel are stored?? (validbitsperpixel
                                    // indicates how many bits of these are actually used)
    ZvImagePixelFormat PixelFormat;
    long ValidBitsPerPixel;
    long LineWidth;                 //unused
};

enum ZvTagAttribute
{
    zvTagAttributeKeep  = -1,
    zvTagAttributeNone  = 0,
    zvTagAttributeFixed = 0x1,
    zvTagAttributeGlobal    = 0x2,
    zvTagAttributeShared    = 0x4,
    zvTagAttributeLocal = 0x8,
    zvTagAttributeReadOnly  = 0x10,
    zvTagAttributeInternal  = 0x20,
    zvTagAttributeNotPersistent = 0x40,
    zvTagAttributeUIDefaultVisible  = 0x1000,
    zvTagAttributeUINeverVisible    = 0x2000
};

enum ZvTagId
{   zvTagIdInvalid  = -1,
    zvTagIdRoot = 0,
    zvTagIdNamedField   = 1,
    zvTagIdDisplayGroup = 0x100,
    zvTagIdOutputTable  = 1 + zvTagIdDisplayGroup,
    zvTagIdDataMappingLow   = 2 + zvTagIdDisplayGroup, // BlackValue
    zvTagIdDataMappingHigh  = 3 + zvTagIdDisplayGroup, // WhiteValue
    zvTagIdDataMappingAutoRange = 4 + zvTagIdDisplayGroup, // ImageDataMappingAutoRange
    zvTagIdThumbnail    = 5 + zvTagIdDisplayGroup, // Thumbnail
    zvTagIdDataMappingGamma = 6 + zvTagIdDisplayGroup, //GammaValue
    zvTagIdImageOverExposure = 264, // ImageOverExposure
    zvTagIdImageRelativeTime1 = 265, // ImageRelativeTime1
    zvTagIdImageRelativeTime2 = 266, // ImageRelativeTime2
    zvTagIdImageRelativeTime3 = 267, // ImageRelativeTime3
    zvTagIdImageRelativeTime4 = 268, // ImageRelativeTime4
    zvTagIdSizeGroup    = 0x200,
    zvTagIdType = 1 + zvTagIdSizeGroup, // ObjectType
    zvTagIdTypeDescription  = 2 + zvTagIdSizeGroup,
    zvTagIdWidth    = 3 + zvTagIdSizeGroup, // ImageWidth
    zvTagIdHeight   = 4 + zvTagIdSizeGroup, // ImageHeight
    zvTagIdDepth    = 5 + zvTagIdSizeGroup, // Number Raw Count
    zvTagIdPixelFormat  = 6 + zvTagIdSizeGroup, // PixelType
    zvTagIdCount    = 7 + zvTagIdSizeGroup, // NumberOfRawImages
    zvTagIdSize = 8 + zvTagIdSizeGroup, // ImageSize
    zvTagIdCompressionFactorForSave = 9 + zvTagIdSizeGroup,
    zvTagIdSaveFlags    = 10 + zvTagIdSizeGroup,
    zvTagIdFileExtensionForItems    = 11 + zvTagIdSizeGroup, // Acquisition pause annotation
    zvTagIdScalingGroup = 0x300,
    zvTagIdScaleFactorForWidth  = 1 + zvTagIdScalingGroup, // Scale Factor for X
    zvTagIdScaleTypeForWidth    = 2 + zvTagIdScalingGroup, // Scale Unit for X
    zvTagIdScaleWidth   = 3 + zvTagIdScalingGroup, // Scale Width
    zvTagIdScaleFactorForHeight = 4 + zvTagIdScalingGroup, // Scale Factor for Y
    zvTagIdScaleTypeForHeight   = 5 + zvTagIdScalingGroup, // Scale Unit for Y
    zvTagIdScaleHeight  = 6 + zvTagIdScalingGroup, // Scale Height
    zvTagIdScaleFactorForDepth  = 7 + zvTagIdScalingGroup, // Scale Factor for Z
    zvTagIdScaleTypeForDepth    = 8 + zvTagIdScalingGroup, // Scale Unit for Z
    zvTagIdScaleDepth   = 9 + zvTagIdScalingGroup, // Scale Depth
    zvTagIdScalePositionX   = 10 + zvTagIdScalingGroup,
    zvTagIdScalePositionY   = 11 + zvTagIdScalingGroup,
    zvTagIdScalePositionZ   = 12 + zvTagIdScalingGroup,
    zvTagIdAcquisitionGroup = 0x400,
    zvTagIdAcquisitionTime  = 1 + zvTagIdAcquisitionGroup, // Acquisition Date
    zvTagIdScaleTypeForExposureTime = 2 + zvTagIdAcquisitionGroup, // 8-bit acquisition
    zvTagIdExposureTime = 4 + zvTagIdAcquisitionGroup,
    zvTagIdMonoReferenceLow = 5 + zvTagIdAcquisitionGroup, // MonoReferenceLow
    zvTagIdMonoReferenceHigh    = 6 + zvTagIdAcquisitionGroup, // MonoReferenceHigh
    zvTagIdRedReferenceLow  = 7 + zvTagIdAcquisitionGroup, // RedReferenceLow
    zvTagIdRedReferenceHigh = 8 + zvTagIdAcquisitionGroup, // RedReferenceHigh
    zvTagIdGreenReferenceLow    = 9 + zvTagIdAcquisitionGroup, // GreenReferenceLow
    zvTagIdGreenReferenceHigh   = 10 + zvTagIdAcquisitionGroup, // GreenReferenceHigh
    zvTagIdBlueReferenceLow = 11 + zvTagIdAcquisitionGroup, // BlueReferenceLow
    zvTagIdBlueReferenceHigh    = 12 + zvTagIdAcquisitionGroup, // BlueReferenceHigh
    zvTagIdHue  = 13 + zvTagIdAcquisitionGroup,
    zvTagIdSaturation   = 14 + zvTagIdAcquisitionGroup,
    zvTagIdIntegrationMode  = 15 + zvTagIdAcquisitionGroup,
    zvTagIdIntegrationCount = 16 + zvTagIdAcquisitionGroup,
    zvTagIdGrabberName  = 17 + zvTagIdAcquisitionGroup, // FrameGrabber Name
    zvTagIdCameraName   = 18 + zvTagIdAcquisitionGroup, // Camera
    zvTagIdIntegrationEnable    = 19 + zvTagIdAcquisitionGroup,
    zvTagIdTriggerMode  = 20 + zvTagIdAcquisitionGroup, // CameraTriggerSignalType
    zvTagIdTriggerEnable    = 21 + zvTagIdAcquisitionGroup,
    zvTagIdGrabberTimeout   = 22 + zvTagIdAcquisitionGroup,
    zvTagIdAcquisitionDuration  = 23 + zvTagIdAcquisitionGroup,
    zvTagIdMultiChannelDisplayGroup = 0x500,
    zvTagIdMultiChannelEnabled  = 1 + zvTagIdMultiChannelDisplayGroup,
    zvTagIdMultiChannelColor    = 2 + zvTagIdMultiChannelDisplayGroup,
    zvTagIdMultiChannelWeight   = 3 + zvTagIdMultiChannelDisplayGroup,
    zvTagIdMultiChannelName = 4 + zvTagIdMultiChannelDisplayGroup,
    zvTagIdMultiChannelAttribute    = 5 + zvTagIdMultiChannelDisplayGroup,
    zvTagIdDocumentInformationGroup = 0x600,
    zvTagIdTitle    = 1 + zvTagIdDocumentInformationGroup,
    zvTagIdAuthor   = 2 + zvTagIdDocumentInformationGroup,
    zvTagIdKeywords = 3 + zvTagIdDocumentInformationGroup,
    zvTagIdComments = 4 + zvTagIdDocumentInformationGroup,
    zvTagIdSampleID = 5 + zvTagIdDocumentInformationGroup,
    zvTagIdSubject  = 6 + zvTagIdDocumentInformationGroup,
    zvTagIdRevisionNumber   = 7 + zvTagIdDocumentInformationGroup,
    zvTagIdFileLink = 9 + zvTagIdDocumentInformationGroup,
    zvTagIdDocumentType = 10 + zvTagIdDocumentInformationGroup,
    zvTagIdFileMedium   = 11 + zvTagIdDocumentInformationGroup,
    zvTagIdFileID   = 12 + zvTagIdDocumentInformationGroup,
    zvTagIdFileName = 13 + zvTagIdDocumentInformationGroup,
    zvTagIdFileDate = 14 + zvTagIdDocumentInformationGroup,
    zvTagIdFileSize = 15 + zvTagIdDocumentInformationGroup,
    zvTagIdDocumentStatus   = 16 + zvTagIdDocumentInformationGroup,
    zvTagIdName = 17 + zvTagIdDocumentInformationGroup,
    zvTagIdProjectGroup = 0x700,
    zvTagIdDate = 1 + zvTagIdProjectGroup,
    zvTagIdLastSavedBy  = 2 + zvTagIdProjectGroup,
    zvTagIdCompany  = 3 + zvTagIdProjectGroup,
    zvTagIdCompanyLogo  = 4 + zvTagIdProjectGroup,
    zvTagIdImage    = 5 + zvTagIdProjectGroup,
    zvTagIdUserId   = 8 + zvTagIdProjectGroup,
    zvTagIdUserName = 9 + zvTagIdProjectGroup,
    zvTagIdCity = 10 + zvTagIdProjectGroup,
    zvTagIdAddress  = 11 + zvTagIdProjectGroup,
    zvTagIdState    = 12 + zvTagIdProjectGroup,
    zvTagIdPhone    = 13 + zvTagIdProjectGroup,
    zvTagIdFax  = 14 + zvTagIdProjectGroup,
    zvTagIdMicroscopeGroup  = 0x800,
    zvTagIdObjective    = 1 + zvTagIdMicroscopeGroup,
    zvTagIdOptovar  = 2 + zvTagIdMicroscopeGroup,
    zvTagIdReflector    = 3 + zvTagIdMicroscopeGroup,
    zvTagIdCondensorContrast    = 4 + zvTagIdMicroscopeGroup,
    zvTagIdFilterWheel1 = 5 + zvTagIdMicroscopeGroup,
    zvTagIdFilterWheel2 = 6 + zvTagIdMicroscopeGroup,
    zvTagIdShutterRefLight  = 7 + zvTagIdMicroscopeGroup,
    zvTagIdCondensorFrontlens   = 8 + zvTagIdMicroscopeGroup,
    zvTagIdExcitationFilter = 9 + zvTagIdMicroscopeGroup,
    zvTagIdBarrierFilter    = 10 + zvTagIdMicroscopeGroup,
    zvTagIdLampMirror   = 11 + zvTagIdMicroscopeGroup,
    zvTagIdFieldStop    = 12 + zvTagIdMicroscopeGroup,
    zvTagIdApertureReflect  = 13 + zvTagIdMicroscopeGroup,
    zvTagIdCondensorAperture    = 14 + zvTagIdMicroscopeGroup,
    zvTagIdLightPath    = 15 + zvTagIdMicroscopeGroup,
    zvTagIdHalogenLampOn    = 16 + zvTagIdMicroscopeGroup,
    zvTagIdHalogenLampOperationMode = 17 + zvTagIdMicroscopeGroup,
    zvTagIdHalogenLampVoltage   = 18 + zvTagIdMicroscopeGroup,
    zvTagIdMercuryLampOn    = 19 + zvTagIdMicroscopeGroup,
    zvTagIdMercuryLampOperationMode = 20 + zvTagIdMicroscopeGroup,
    zvTagIdMercuryLampVoltage   = 21 + zvTagIdMicroscopeGroup,
    zvTagIdLightManagerEnabled  = 22 + zvTagIdMicroscopeGroup,
    zvTagIdLightManagerComponents   = 23 + zvTagIdMicroscopeGroup,
    zvTagIdFocusPosition    = 24 + zvTagIdMicroscopeGroup,
    zvTagIdStagePositionX   = 25 + zvTagIdMicroscopeGroup,
    zvTagIdStagePositionY   = 26 + zvTagIdMicroscopeGroup,
    zvTagIdMicroscopeName   = 27 + zvTagIdMicroscopeGroup,
    zvTagIdObjectiveMagnification   = 28 + zvTagIdMicroscopeGroup,
    zvTagIdNumericalAperture    = 29 + zvTagIdMicroscopeGroup,
    zvTagIdIlluminationType = 30 + zvTagIdMicroscopeGroup,
    zvTagIdExtraShutter1    = 31 + zvTagIdMicroscopeGroup,
    zvTagIdExtraShutter2    = 32 + zvTagIdMicroscopeGroup,
    zvTagIdExtraShutter3    = 33 + zvTagIdMicroscopeGroup,
    zvTagIdExtraFilterWheel1    = 34 + zvTagIdMicroscopeGroup,
    zvTagIdExtraFilterWheel2    = 35 + zvTagIdMicroscopeGroup,
    zvTagIdParfCorrection   = 36 + zvTagIdMicroscopeGroup,
    zvTagIdAutofocusRun = 37 + zvTagIdMicroscopeGroup,
    zvTagIdExtraShutter4    = 38 + zvTagIdMicroscopeGroup,
    zvTagIdExtraShutter5    = 39 + zvTagIdMicroscopeGroup,
    zvTagIdExtraShutter6    = 40 + zvTagIdMicroscopeGroup,
    zvTagIdExtraFilterWheel3    = 41 + zvTagIdMicroscopeGroup,
    zvTagIdExtraFilterWheel4    = 42 + zvTagIdMicroscopeGroup,
    zvTagIdGrabberDriverGroup   = 0x900,
    zvTagIdGrabberDriverName    = 1 + zvTagIdGrabberDriverGroup,
    zvTagIdGrabberDriverDescription = 2 + zvTagIdGrabberDriverGroup,
    zvTagIdFrameLeft    = 3 + zvTagIdGrabberDriverGroup,
    zvTagIdFrameTop = 4 + zvTagIdGrabberDriverGroup,
    zvTagIdFrameWidth   = 5 + zvTagIdGrabberDriverGroup,
    zvTagIdFrameHeight  = 6 + zvTagIdGrabberDriverGroup,
    zvTagIdFrameBinning = 7 + zvTagIdGrabberDriverGroup,
    zvTagIdFrameFull    = 8 + zvTagIdGrabberDriverGroup,
    zvTagIdDataFormatType   = 9 + zvTagIdGrabberDriverGroup,
    zvTagIdDataFormatBitDepth   = 10 + zvTagIdGrabberDriverGroup,
    zvTagIdDataFormatRGBChannelOrder    = 11 + zvTagIdGrabberDriverGroup,
    zvTagIdDataFormatGrayChannelSelection   = 12 + zvTagIdGrabberDriverGroup,
    zvTagIdDataFormatScaleMode  = 13 + zvTagIdGrabberDriverGroup,
    zvTagIdDataFormatUseScaling = 14 + zvTagIdGrabberDriverGroup,
    zvTagIdDataFormatTransformation = 15 + zvTagIdGrabberDriverGroup,
    zvTagIdVideoMonochromeSignalType    = 16 + zvTagIdGrabberDriverGroup,
    zvTagIdVideoColorSignalType = 17 + zvTagIdGrabberDriverGroup,
    zvTagIdVideoInputChannel    = 18 + zvTagIdGrabberDriverGroup,
    zvTagIdVideoSyncChannel = 19 + zvTagIdGrabberDriverGroup,
    zvTagIdWhiteBalanceEnabled  = 20 + zvTagIdGrabberDriverGroup,
    zvTagIdWhiteBalanceWhiteRed = 21 + zvTagIdGrabberDriverGroup,
    zvTagIdWhiteBalanceWhiteGreen   = 22 + zvTagIdGrabberDriverGroup,
    zvTagIdWhiteBalanceWhiteBlue    = 23 + zvTagIdGrabberDriverGroup,
    zvTagIdACamResolution   = 24 + zvTagIdGrabberDriverGroup,
    zvTagIdShadingEnabled   = 25 + zvTagIdGrabberDriverGroup,
    zvTagIdShadingImage = 26 + zvTagIdGrabberDriverGroup,
    zvTagIdFrameScaleFactor = 27 + zvTagIdGrabberDriverGroup,
    zvTagIdGrabberCameraGroup   = 0xa00,
    zvTagIdGrabberCameraName    = 1 + zvTagIdGrabberCameraGroup,
    zvTagIdCameraType   = 2 + zvTagIdGrabberCameraGroup,
    zvTagIdExposureType = 3 + zvTagIdGrabberCameraGroup,
    zvTagIdExposureValue    = 4 + zvTagIdGrabberCameraGroup,
    zvTagIdExposureValueRed = 5 + zvTagIdGrabberCameraGroup,
    zvTagIdExposureValueGreen   = 6 + zvTagIdGrabberCameraGroup,
    zvTagIdExposureValueBlue    = 7 + zvTagIdGrabberCameraGroup,
    zvTagIdExposureAutomatic    = 8 + zvTagIdGrabberCameraGroup,
    zvTagIdGainValue    = 9 + zvTagIdGrabberCameraGroup,
    zvTagIdGainOffsetValue  = 10 + zvTagIdGrabberCameraGroup,
    zvTagIdGainAutomatic    = 11 + zvTagIdGrabberCameraGroup,
    zvTagIdAdjustHue    = 12 + zvTagIdGrabberCameraGroup,
    zvTagIdAdjustSaturation = 13 + zvTagIdGrabberCameraGroup,
    zvTagIdAdjustRedLow = 14 + zvTagIdGrabberCameraGroup,
    zvTagIdAdjustGreenLow   = 15 + zvTagIdGrabberCameraGroup,
    zvTagIdAdjustBlueLow    = 16 + zvTagIdGrabberCameraGroup,
    zvTagIdAdjustRedHigh    = 17 + zvTagIdGrabberCameraGroup,
    zvTagIdAdjustGreenHigh  = 18 + zvTagIdGrabberCameraGroup,
    zvTagIdAdjustBlueHigh   = 19 + zvTagIdGrabberCameraGroup,
    zvTagIdAdjustValueLow   = 20 + zvTagIdGrabberCameraGroup,
    zvTagIdAdjustValueHigh  = 21 + zvTagIdGrabberCameraGroup,
    zvTagIdIndexGroup   = 0xb00,
    zvTagIdIndexX   = 0xb01,
    zvTagIdIndexY   = 0xb02,
    zvTagIdIndexZ   = 0xb03, // Image Index Z
    zvTagIdIndexC   = 0xb04, // Image Channel Index
    zvTagIdIndexChannel = 0xb04, // Image Channel Index
    zvTagIdIndexT   = 0xb05, // Image Index T
    zvTagIdIndexTime    = 0xb05, // Image Index T
    zvTagIdPositionX    = 0xb06,
    zvTagIdPositionY    = 0xb07,
    zvTagIdPositionZ    = 0xb08,
    zvTagIdPositionC    = 0xb09,
    zvTagIdChannel  = 0xb09,
    zvTagIdPositionT    = 0xb0a,
    zvTagIdTime = 0xb0a,
    zvTagIdIndexA   = 0xb0b,
    zvTagIdIndexS   = 0xb0b,
    zvTagIdRawIndex = 0xb0c,
    zvTagIdPositionA    = 0xb0c,
    zvTagIdScene    = 0xb0c,
    zvTagIdAcquisitionDeltaT    = 0xb0d,
    zvTagIdCountX   = 0xb0e,
    zvTagIdCountY   = 0xb0f,
    zvTagIdCountZ   = 0xb10,
    zvTagIdCountC   = 0xb11,
    zvTagIdCountT   = 0xb12,
    zvTagIdCountA   = 0xb13,
    zvTagIdRawCount = 0xb14,
    zvTagIdMaskC    = 0xb15,
    zvTagIdMenuAndToolbarGroup  = 0xc00,
    zvTagIdSmallImageIndex  = 0xc01,
    zvTagIdLargeImageIndex  = 0xc02,
    zvTagIdIsLarge  = 0xc03,
    zvTagIdIsVisible    = 0xc04,
    zvTagIdCommandText  = 0xc05,
    zvTagIdCommandFlags = 0xc06,
    zvTagIdDisplayTextId    = 0xc07,
    zvTagIdMediumImageIndex = 0xc08,
    zvTagIdIsMedium = 0xc09,
    zvTagIdUserDefined  = 0xc0a,
    zvTagIdTooltipTextId    = 0xc0b,
    zvTagIdHelpId   = 0xc0c,
    zvTagIdCommandId    = 0xc0d,
    zvTagIdJobGroup = 0xd00,
    zvTagIdJobName  = 0xd01,
    zvTagIdJobInfo  = 0xd02,
    zvTagIdJobProgress  = 0xd03,
    zvTagIdJobStatus    = 0xd04,
    zvTagIdJobId    = 0xd05,
    zvTagIdUserGroup    = 0xe00,
    zvTagIdUser1    = 0xe01,
    zvTagIdUser2    = 0xe02,
    zvTagIdUser3    = 0xe03,
    zvTagIdUser4    = 0xe04,
    zvTagIdUser5    = 0xe05,
    zvTagIdUser6    = 0xe06,
    zvTagIdUser7    = 0xe07,
    zvTagIdUser8    = 0xe08,
    zvTagIdUser9    = 0xe09,
    zvTagIdUser10   = 0xe0a,
    zvTagIdComplexGroup = 0x1000000,
    zvTagIdComplexDisplayMode   = 1 + zvTagIdComplexGroup,
    zvTagIdComplexScaleMode = 2 + zvTagIdComplexGroup,
    zvTagIdRefWidth = 3 + zvTagIdComplexGroup,
    zvTagIdRefHeight    = 4 + zvTagIdComplexGroup,
    zvTagIdRefDepth = 5 + zvTagIdComplexGroup,
    zvTagIdRefPixelFormat   = 6 + zvTagIdComplexGroup,
    zvTagIdRefImageType = 7 + zvTagIdComplexGroup,
    zvTagIdRefZvFFTType = 8 + zvTagIdComplexGroup,
    zvTagIdRefZvFFTWindow   = 9 + zvTagIdComplexGroup,
    zvTagIdRefZvFFTWrapMode = 10 + zvTagIdComplexGroup,
    zvTagIdRefZvFFTDimension    = 11 + zvTagIdComplexGroup,
    zvTagIdPSFGroup = 0x1000100,
    zvTagIdPSFDisplayMode   = 1 + zvTagIdPSFGroup,
    zvTagIdPSFSource    = 2 + zvTagIdPSFGroup,
    zvTagIdPSFTestObjectGeometry    = 3 + zvTagIdPSFGroup,
    zvTagIdPSFTestObjectSize    = 4 + zvTagIdPSFGroup,
    zvTagIdPSFType  = 5 + zvTagIdPSFGroup,
    zvTagIdPSFDimensionality    = 6 + zvTagIdPSFGroup,
    zvTagIdPSFInstrument    = 7 + zvTagIdPSFGroup,
    zvTagIdPSFPupilGeometry = 8 + zvTagIdPSFGroup,
    zvTagIdPSFImageFormation    = 9 + zvTagIdPSFGroup,
    zvTagIdPSFDefocus   = 10 + zvTagIdPSFGroup,
    zvTagIdPSFIllumination  = 11 + zvTagIdPSFGroup,
    zvTagIdPSFPinholeGeometry   = 12 + zvTagIdPSFGroup,
    zvTagIdPSFPinholeSize   = 13 + zvTagIdPSFGroup,
    zvTagIdPSFNAObjective   = 14 + zvTagIdPSFGroup,
    zvTagIdPSFNACondensor   = 15 + zvTagIdPSFGroup,
    zvTagIdPSFExcitationWavelength  = 16 + zvTagIdPSFGroup,
    zvTagIdPSFEmissionWavelength    = 17 + zvTagIdPSFGroup,
    zvTagIdPSFDesignImmersionIndex  = 18 + zvTagIdPSFGroup,
    zvTagIdPSFOptovar   = 19 + zvTagIdPSFGroup,
    zvTagIdPSFLateralMagnification  = 20 + zvTagIdPSFGroup,
    zvTagIdPSFUsedImmersionIndex    = 21 + zvTagIdPSFGroup,
    zvTagIdPSFSampleIndex   = 22 + zvTagIdPSFGroup,
    zvTagIdPSFDesignCoverglassIndex = 23 + zvTagIdPSFGroup,
    zvTagIdPSFUsedCoverglassIndex   = 24 + zvTagIdPSFGroup,
    zvTagIdPSFDesignCoverglassThickness = 25 + zvTagIdPSFGroup,
    zvTagIdPSFUsedCoverglassThickness   = 26 + zvTagIdPSFGroup,
    zvTagIdPSFWorkingDistance   = 27 + zvTagIdPSFGroup,
    zvTagIdPSFSampleThickness   = 28 + zvTagIdPSFGroup,
    zvTagIdPSFDesignTubeLength  = 29 + zvTagIdPSFGroup,
    zvTagIdPSFUsedTubeLength    = 30 + zvTagIdPSFGroup,
    zvTagIdPSFTransverseResolution  = 31 + zvTagIdPSFGroup,
    zvTagIdPSFAxialResolution   = 32 + zvTagIdPSFGroup,
    zvTagIdPSFPrepareMode   = 33 + zvTagIdPSFGroup,
    zvTagIdPhotoGroup   = 0x1000,
    zvTagIdPhotoMagnification   = 1 + zvTagIdPhotoGroup,
    zvTagIdCameraSelection  = 2 + zvTagIdPhotoGroup,
    zvTagIdFilmRegistrationName = 3 + zvTagIdPhotoGroup,
    zvTagIdPhotoLightpath   = 4 + zvTagIdPhotoGroup,
    zvTagIdFilmName = 5 + zvTagIdPhotoGroup,
    zvTagIdFilmSpeed    = 6 + zvTagIdPhotoGroup,
    zvTagIdFilmReciprocity  = 7 + zvTagIdPhotoGroup,
    zvTagIdFilmCount    = 8 + zvTagIdPhotoGroup,
    zvTagIdExposureMode = 9 + zvTagIdPhotoGroup,
    zvTagIdExposureMethod   = 10 + zvTagIdPhotoGroup,
    zvTagIdExposureCorrection   = 11 + zvTagIdPhotoGroup,
    zvTagIdMultiExposure    = 12 + zvTagIdPhotoGroup,
    zvTagIdUserCountDescription = 13 + zvTagIdPhotoGroup,
    zvTagIdUserCount    = 14 + zvTagIdPhotoGroup,
    zvTagIdDatabackOn   = 15 + zvTagIdPhotoGroup,
    zvTagIdDatabackPicture  = 16 + zvTagIdPhotoGroup,
    zvTagIdDatabackBridge   = 17 + zvTagIdPhotoGroup,
    zvTagIdMC200Sensor  = 18 + zvTagIdPhotoGroup,
    zvTagIdPhotoLabel1  = 19 + zvTagIdPhotoGroup,
    zvTagIdPhotoLabel2  = 20 + zvTagIdPhotoGroup,
    zvTagIdPhotoLabel3  = 21 + zvTagIdPhotoGroup,
    zvTagIdPhotoLabel4  = 22 + zvTagIdPhotoGroup,
    zvTagIdPhotoLabel5  = 23 + zvTagIdPhotoGroup,
    zvTagIdPhotoLabel6  = 24 + zvTagIdPhotoGroup
};

struct CZvTag
{
    ZVI_Variant Value;
    ZvTagId      ID;
    ZvTagAttribute Attribute;
};

//return values of Read_Stream
#define RS_OK           1
#define RS_STRUCT_FULL  2
#define RS_READ_ERROR   3
#define RS_UNKNOWN_TYPE 4
#define RS_READ_IMAGE_FAILED    5

//carl zeiss vision's constant (ID) for image streams
#define STREAM_VERSIONID 0x10002000

//available image versions...
#define ZVIM_205VERSION             0x30001001      //old image ver
#define ZVIM_300VERSION             0x30001003      //actual image ver

//struct tree similar to the image file format
struct _Image_Scaling_Contents
{
    long version;
    wchar_t* scaling;   //'Scaling%d'
    long category;

    double factor[3];
    long type[3];
    wchar_t* unit[3];
    double origin[3];
    double angle[3];

    double matrix[16];

    //ver >= 0x20001001
    ZVI_IUnknown tag;      //'Tags'
};

struct _Image_Tags_Contents
{
    long version;
    long count;
    CZvTag *tags;
};

struct _Image_Tags
{
    _Image_Tags_Contents* Contents;
};

struct _Image_Scaling
{
    _Image_Scaling_Contents* Contents;
    _Image_Tags* Tags;
};

struct _IMG_DATA
{
    SZVBITMAPHEADER bmp_header;
    unsigned char* data;
};

struct _Image;

struct _Image_Contents
{
    long version;
    long type;
    wchar_t* typedescribtion;
    wchar_t* filename;
    long width,height,depth,pixelformat,count,validbitsperpixel;
    ZVI_BLOB plugin_CLSID;
    ZVI_BLOB img_other_header;
    image_header_other* img_head_other;

    ZVI_IUnknown Storage_Layer;
    ZVI_IUnknown Storage_Tags;
    ZVI_IUnknown Storage_Scaling;

    ZVI_IUnknown Storage_RootFolder;   //only ZVIM_300VERSION
    ZVI_IUnknown Storage_DisplayItem;  //only ZVIM_300VERSION

    _IMG_DATA* image;
    wchar_t** items;
    _Image** item_data;
};

struct _Image
{
    _Image_Tags* Tags;
    _Image_Contents* Contents;
    _Image_Scaling* Scaling;
};

//root image structs

struct _Thumbnail
{
    ZVI_BITMAPFILEHEADER bmp_header;
    ZVI_BITMAPINFO bmp_info;
    unsigned char* data;
};

struct _ISummaryInformation
{
    char* title;
    char* subject;
    char* author;
    char* comments;
    char* keywords;
};

struct _ZVI
{
    _Thumbnail* Thumbnail;
    _Image* Image;
    _ISummaryInformation* ISummaryInformation;
};

class QxZVIDialog;

class HxImFormatZeissZVI
{
public:
    HxImFormatZeissZVI();
    ~HxImFormatZeissZVI();

    bool read(const char * filename, int idx);
    void loadImage(_ZVI* zvi);

private:
    McBox3f getBoundingBox(int* dims, double *factor, double* origin, wchar_t** unit);
    HxParamBundle * getDisplayGroup(_Image_Tags_Contents *tagContents);
    HxParamBundle * getSizeGroup(_Image_Tags_Contents *tagContents);
    HxParamBundle * getScalingGroup(_Image_Tags_Contents *tagContents);
    HxParamBundle * getAcquisitionGroup(_Image_Tags_Contents *tagContents);
    HxParamBundle * getDocumentInformationGroup(_Image_Tags_Contents *tagContents);
    HxParamBundle * getProjectGroup(_Image_Tags_Contents *tagContents);


    _ZVI mZvi; //struct to hold our images
    MemList mAllocList; //here we keep list of allocations... so we can free them later
    QxZVIDialog * mDialog;
};

#endif // HXIMFORMATZEISSZVI_H

/// @}
