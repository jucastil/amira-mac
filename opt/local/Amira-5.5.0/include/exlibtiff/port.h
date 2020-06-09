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

/// @addtogroup exlibtiff exlibtiff
/// @{
#ifndef TIFF_PORT_H
#define TIFF_PORT_H 1

#define TIFF_PREFIX(x) ex_##x

#define LogL10fromY		TIFF_PREFIX(LogL10fromY)
#define LogL10toY		TIFF_PREFIX(LogL10toY)
#define LogL16fromY		TIFF_PREFIX(LogL16fromY)
#define LogL16toY		TIFF_PREFIX(LogL16toY)
#define LogLuv24fromXYZ		TIFF_PREFIX(LogLuv24fromXYZ)
#define LogLuv24toXYZ		TIFF_PREFIX(LogLuv24toXYZ)
#define LogLuv32fromXYZ		TIFF_PREFIX(LogLuv32fromXYZ)
#define LogLuv32toXYZ		TIFF_PREFIX(LogLuv32toXYZ)
#define TIFFAccessTagMethods	TIFF_PREFIX(TIFFAccessTagMethods)
#define TIFFCheckTile		TIFF_PREFIX(TIFFCheckTile)
#define TIFFClientOpen		TIFF_PREFIX(TIFFClientOpen)
#define TIFFClose		TIFF_PREFIX(TIFFClose)
#define TIFFComputeStrip	TIFF_PREFIX(TIFFComputeStrip)
#define TIFFComputeTile		TIFF_PREFIX(TIFFComputeTile)
#define TIFFCreateDirectory	TIFF_PREFIX(TIFFCreateDirectory)
#define TIFFLastDirectory TIFF_PREFIX(TIFFLastDirectory)
#define TIFFCurrentDirectory	TIFF_PREFIX(TIFFCurrentDirectory)
#define TIFFCurrentRow		TIFF_PREFIX(TIFFCurrentRow)
#define TIFFCurrentStrip	TIFF_PREFIX(TIFFCurrentStrip)
#define TIFFCurrentTile		TIFF_PREFIX(TIFFCurrentTile)
#define TIFFDefaultDirectory	TIFF_PREFIX(TIFFDefaultDirectory)
#define TIFFDefaultStripSize	TIFF_PREFIX(TIFFDefaultStripSize)
#define TIFFDefaultTileSize	TIFF_PREFIX(TIFFDefaultTileSize)
#define _TIFFError		TIFF_PREFIX(_TIFFError)
#define TIFFFaxBlackCodes	TIFF_PREFIX(TIFFFaxBlackCodes)
#define TIFFFaxBlackTable	TIFF_PREFIX(TIFFFaxBlackTable)
#define TIFFFaxMainTable	TIFF_PREFIX(TIFFFaxMainTable)
#define TIFFFaxWhiteCodes	TIFF_PREFIX(TIFFFaxWhiteCodes)
#define TIFFFaxWhiteTable	TIFF_PREFIX(TIFFFaxWhiteTable)
#define TIFFFdOpen		TIFF_PREFIX(TIFFFdOpen)
#define TIFFFileName		TIFF_PREFIX(TIFFFileName)
#define TIFFFindCODEC		TIFF_PREFIX(TIFFFindCODEC)
#define TIFFFlush		TIFF_PREFIX(TIFFFlush)
#define TIFFFlushData		TIFF_PREFIX(TIFFFlushData)
#define TIFFFlushData1		TIFF_PREFIX(TIFFFlushData1)
#define TIFFFreeDirectory	TIFF_PREFIX(TIFFFreeDirectory)
#define TIFFGetBitRevTable	TIFF_PREFIX(TIFFGetBitRevTable)
#define TIFFGetClientInfo	TIFF_PREFIX(TIFFGetClientInfo)
#define TIFFGetField		TIFF_PREFIX(TIFFGetField)
#define TIFFGetFieldDefaulted	TIFF_PREFIX(TIFFGetFieldDefaulted)
#define TIFFGetMode		TIFF_PREFIX(TIFFGetMode)
#define TIFFGetTagListCount	TIFF_PREFIX(TIFFGetTagListCount)
#define TIFFGetTagListEntry	TIFF_PREFIX(TIFFGetTagListEntry)
#define TIFFGetVersion		TIFF_PREFIX(TIFFGetVersion)
#define TIFFInitCCITTFax3	TIFF_PREFIX(TIFFInitCCITTFax3)
#define TIFFInitCCITTFax4	TIFF_PREFIX(TIFFInitCCITTFax4)
#define TIFFInitCCITTRLE	TIFF_PREFIX(TIFFInitCCITTRLE)
#define TIFFInitCCITTRLEW	TIFF_PREFIX(TIFFInitCCITTRLEW)
#define TIFFInitDumpMode	TIFF_PREFIX(TIFFInitDumpMode)
#define TIFFInitLZW		TIFF_PREFIX(TIFFInitLZW)
#define TIFFInitNeXT		TIFF_PREFIX(TIFFInitNeXT)
#define TIFFInitPackBits	TIFF_PREFIX(TIFFInitPackBits)
#define TIFFInitSGILog		TIFF_PREFIX(TIFFInitSGILog)
#define TIFFInitZIP		TIFF_PREFIX(TIFFInitZIP)
#define TIFFIsByteSwapped	TIFF_PREFIX(TIFFIsByteSwapped)
#define TIFFIsMSB2LSB		TIFF_PREFIX(TIFFIsMSB2LSB)
#define TIFFIsTiled		TIFF_PREFIX(TIFFIsTiled)
#define TIFFIsUpSampled		TIFF_PREFIX(TIFFIsUpSampled)
#define TIFFNumberOfStrips	TIFF_PREFIX(TIFFNumberOfStrips)
#define TIFFNumberOfTiles	TIFF_PREFIX(TIFFNumberOfTiles)
#define TIFFOpen		TIFF_PREFIX(TIFFOpen)
#define TIFFPredictorInit	TIFF_PREFIX(TIFFPredictorInit)
#define TIFFPrintDirectory	TIFF_PREFIX(TIFFPrintDirectory)
#define TIFFRGBAImageBegin	TIFF_PREFIX(TIFFRGBAImageBegin)
#define TIFFRGBAImageEnd	TIFF_PREFIX(TIFFRGBAImageEnd)
#define TIFFRGBAImageGet	TIFF_PREFIX(TIFFRGBAImageGet)
#define TIFFRGBAImageOK		TIFF_PREFIX(TIFFRGBAImageOK)
#define TIFFRasterScanlineSize	TIFF_PREFIX(TIFFRasterScanlineSize)
#define TIFFReadBufferSetup	TIFF_PREFIX(TIFFReadBufferSetup)
#define TIFFReadDirectory	TIFF_PREFIX(TIFFReadDirectory)
#define TIFFReadEncodedStrip	TIFF_PREFIX(TIFFReadEncodedStrip)
#define TIFFReadEncodedTile	TIFF_PREFIX(TIFFReadEncodedTile)
#define TIFFReadRGBAImage	TIFF_PREFIX(TIFFReadRGBAImage)
#define TIFFReadRGBAStrip	TIFF_PREFIX(TIFFReadRGBAStrip)
#define TIFFReadRGBATile	TIFF_PREFIX(TIFFReadRGBATile)
#define TIFFReadRawStrip	TIFF_PREFIX(TIFFReadRawStrip)
#define TIFFReadRawTile		TIFF_PREFIX(TIFFReadRawTile)
#define TIFFReadScanline	TIFF_PREFIX(TIFFReadScanline)
#define TIFFReadTile		TIFF_PREFIX(TIFFReadTile)
#define TIFFReassignTagToIgnore	TIFF_PREFIX(TIFFReassignTagToIgnore)
#define TIFFReverseBits		TIFF_PREFIX(TIFFReverseBits)
#define TIFFRewriteDirectory	TIFF_PREFIX(TIFFRewriteDirectory)
#define TIFFScanlineSize	TIFF_PREFIX(TIFFScanlineSize)
#define TIFFSetClientInfo 	TIFF_PREFIX(TIFFSetClientInfo)
#define TIFFSetCompressionScheme TIFF_PREFIX(TIFFSetCompressionScheme)
#define TIFFSetDirectory	TIFF_PREFIX(TIFFSetDirectory)
#define TIFFSetErrorHandler	TIFF_PREFIX(TIFFSetErrorHandler)
#define TIFFSetField		TIFF_PREFIX(TIFFSetField)
#define TIFFSetTagExtender	TIFF_PREFIX(TIFFSetTagExtender)
#define TIFFSetWarningHandler	TIFF_PREFIX(TIFFSetWarningHandler)
#define TIFFSetWriteOffset	TIFF_PREFIX(TIFFSetWriteOffset)
#define TIFFStripSize		TIFF_PREFIX(TIFFStripSize)
#define TIFFSwabArrayOfDouble	TIFF_PREFIX(TIFFSwabArrayOfDouble)
#define TIFFSwabArrayOfLong	TIFF_PREFIX(TIFFSwabArrayOfLong)
#define TIFFSwabArrayOfShort	TIFF_PREFIX(TIFFSwabArrayOfShort)
#define TIFFSwabDouble		TIFF_PREFIX(TIFFSwabDouble)
#define TIFFSwabLong		TIFF_PREFIX(TIFFSwabLong)
#define TIFFSwabShort		TIFF_PREFIX(TIFFSwabShort)
#define TIFFTileRowSize		TIFF_PREFIX(TIFFTileRowSize)
#define TIFFTileSize		TIFF_PREFIX(TIFFTileSize)
#define TIFFVGetField		TIFF_PREFIX(TIFFVGetField)
#define TIFFVGetFieldDefaulted	TIFF_PREFIX(TIFFVGetFieldDefaulted)
#define TIFFVSetField		TIFF_PREFIX(TIFFVSetField)
#define TIFFVStripSize		TIFF_PREFIX(TIFFVStripSize)
#define TIFFVTileSize		TIFF_PREFIX(TIFFVTileSize)
#define _TIFFWarning		TIFF_PREFIX(_TIFFWarning)
#define TIFFWriteBufferSetup	TIFF_PREFIX(TIFFWriteBufferSetup)
#define TIFFWriteCheck		TIFF_PREFIX(TIFFWriteCheck)
#define TIFFWriteDirectory	TIFF_PREFIX(TIFFWriteDirectory)
#define TIFFWriteEncodedStrip	TIFF_PREFIX(TIFFWriteEncodedStrip)
#define TIFFWriteEncodedTile	TIFF_PREFIX(TIFFWriteEncodedTile)
#define TIFFWriteRawStrip	TIFF_PREFIX(TIFFWriteRawStrip)
#define TIFFWriteRawTile	TIFF_PREFIX(TIFFWriteRawTile)
#define TIFFWriteScanline	TIFF_PREFIX(TIFFWriteScanline)
#define TIFFWriteTile		TIFF_PREFIX(TIFFWriteTile)
#define XYZtoRGB24		TIFF_PREFIX(XYZtoRGB24)
#define _TIFFBuiltinCODECS	TIFF_PREFIX(_TIFFBuiltinCODECS)
#define _TIFFDefaultStripSize	TIFF_PREFIX(_TIFFDefaultStripSize)
#define _TIFFDefaultTileSize	TIFF_PREFIX(_TIFFDefaultTileSize)
#define _TIFFFax3fillruns	TIFF_PREFIX(_TIFFFax3fillruns)
#define TIFFFieldWithTag	TIFF_PREFIX(TIFFFieldWithTag)
#define TIFFFindFieldInfo	TIFF_PREFIX(TIFFFindFieldInfo)
#define TIFFMergeFieldInfo	TIFF_PREFIX(TIFFMergeFieldInfo)
#define _TIFFNoPostDecode	TIFF_PREFIX(_TIFFNoPostDecode)
#define _TIFFNoPreCode		TIFF_PREFIX(_TIFFNoPreCode)
#define _TIFFNoRowDecode	TIFF_PREFIX(_TIFFNoRowDecode)
#define _TIFFNoRowEncode	TIFF_PREFIX(_TIFFNoRowEncode)
#define _TIFFNoSeek		TIFF_PREFIX(_TIFFNoSeek)
#define _TIFFNoStripDecode	TIFF_PREFIX(_TIFFNoStripDecode)
#define _TIFFNoStripEncode	TIFF_PREFIX(_TIFFNoStripEncode)
#define _TIFFNoTileDecode	TIFF_PREFIX(_TIFFNoTileDecode)
#define _TIFFNoTileEncode	TIFF_PREFIX(_TIFFNoTileEncode)
#define _TIFFPrintFieldInfo	TIFF_PREFIX(_TIFFPrintFieldInfo)
#define _TIFFSampleToTagType	TIFF_PREFIX(_TIFFSampleToTagType)

/* Note: function name shortened to facilitate porting */
#define _TIFFSetDefaultCompressionState	TIFF_PREFIX(_TIFFSetDefaultCompStat)
#define _TIFFSetupFieldInfo	TIFF_PREFIX(_TIFFSetupFieldInfo)
#define _TIFFSwab16BitData	TIFF_PREFIX(_TIFFSwab16BitData)
#define _TIFFSwab32BitData	TIFF_PREFIX(_TIFFSwab32BitData)
#define _TIFFSwab64BitData	TIFF_PREFIX(_TIFFSwab64BitData)
#define _TIFFerrorHandler	TIFF_PREFIX(_TIFFerrorHandler)
#define _TIFFfree		TIFF_PREFIX(_TIFFfree)
#define _TIFFgetMode		TIFF_PREFIX(_TIFFgetMode)
#define _TIFFmalloc		TIFF_PREFIX(_TIFFmalloc)
#define _TIFFmemcmp		TIFF_PREFIX(_TIFFmemcmp)
#define _TIFFmemcpy		TIFF_PREFIX(_TIFFmemcpy)
#define _TIFFmemset		TIFF_PREFIX(_TIFFmemset)
#define _TIFFprintAscii		TIFF_PREFIX(_TIFFprintAscii)
#define _TIFFprintAsciiTag	TIFF_PREFIX(_TIFFprintAsciiTag)
#define _TIFFrealloc		TIFF_PREFIX(_TIFFrealloc)
#define _TIFFsetByteArray	TIFF_PREFIX(_TIFFsetByteArray)
#define _TIFFsetDoubleArray	TIFF_PREFIX(_TIFFsetDoubleArray)
#define _TIFFsetFloatArray	TIFF_PREFIX(_TIFFsetFloatArray)
#define _TIFFsetLongArray	TIFF_PREFIX(_TIFFsetLongArray)
#define _TIFFsetNString		TIFF_PREFIX(_TIFFsetNString)
#define _TIFFsetShortArray	TIFF_PREFIX(_TIFFsetShortArray)
#define _TIFFsetString		TIFF_PREFIX(_TIFFsetString)
#define _TIFFwarningHandler	TIFF_PREFIX(_TIFFwarningHandler)
#define tiffDataWidth		TIFF_PREFIX(tiffDataWidth)
#define uv_decode		TIFF_PREFIX(uv_decode)
#define uv_encode		TIFF_PREFIX(uv_encode)

#define TIFFIsCODECConfigured	TIFF_PREFIX(TIFFIsCODECConfigured)
#define TIFFCIELabToRGBInit	TIFF_PREFIX(TIFFCIELabToRGBInit)
#define TIFFCIELabToXYZ		TIFF_PREFIX(TIFFCIELabToXYZ)
#define TIFFXYZToRGB		TIFF_PREFIX(TIFFXYZToRGB)
#define TIFFYCbCrtoRGB		TIFF_PREFIX(TIFFYCbCrtoRGB)
#define TIFFYCbCrToRGBInit	TIFF_PREFIX(TIFFYCbCrToRGBInit)
#define _TIFFCreateAnonFieldInfo TIFF_PREFIX(_TIFFCreateAnonFieldInfo)
#define TIFFDataWidth		TIFF_PREFIX(TIFFDataWidth)
/* Note: function name shortened to facilitate porting */
#define _TIFFFindOrRegisterFieldInfo TIFF_PREFIX(_TIFFFindOrRegisterFieldIn)
#define display_sRGB		TIFF_PREFIX(display_sRGB)
#define TIFFReadRGBAImageOriented TIFF_PREFIX(TIFFReadRGBAImageOriented)
#define TIFFInitJPEG		TIFF_PREFIX(TIFFInitJPEG)
#define TIFFInitOJPEG		TIFF_PREFIX(TIFFInitOJPEG)
#define TIFFFillStrip		TIFF_PREFIX(TIFFFillStrip)
#define TIFFFillTile		TIFF_PREFIX(TIFFFillTile)
#define TIFFRawStripSize	TIFF_PREFIX(TIFFRawStripSize)

#define _TIFFCheckMalloc 	TIFF_PREFIX(_TIFFCheckMalloc)
#define TIFFCleanup 		TIFF_PREFIX(TIFFCleanup)
#define TIFFGetConfiguredCODECs TIFF_PREFIX(TIFFGetConfiguredCODECs)
#define _TIFFDataSize 		TIFF_PREFIX(_TIFFDataSize)
#define TIFFFieldWithName 	TIFF_PREFIX(TIFFFieldWithName)
#define TIFFFindFieldInfoByName TIFF_PREFIX(TIFFFindFieldInfoByName)
#define TIFFCheckpointDirectory TIFF_PREFIX(TIFFCheckpointDirectory)
#define TIFFClientdata 		TIFF_PREFIX(TIFFClientdata)
#define TIFFFileno 		TIFF_PREFIX(TIFFFileno)
#define TIFFGetCloseProc 	TIFF_PREFIX(TIFFGetCloseProc)
#define TIFFGetMapFileProc 	TIFF_PREFIX(TIFFGetMapFileProc)
#define TIFFGetReadProc 	TIFF_PREFIX(TIFFGetReadProc)
#define TIFFGetSeekProc 	TIFF_PREFIX(TIFFGetSeekProc)
#define TIFFGetSizeProc 	TIFF_PREFIX(TIFFGetSizeProc)
#define TIFFGetUnmapFileProc 	TIFF_PREFIX(TIFFGetUnmapFileProc)
#define TIFFGetWriteProc 	TIFF_PREFIX(TIFFGetWriteProc)
#define TIFFIsBigEndian		TIFF_PREFIX(TIFFIsBigEndian)
#define TIFFSetClientdata	TIFF_PREFIX(TIFFSetClientdata)
#define TIFFSetFileName		TIFF_PREFIX(TIFFSetFileName)
#define TIFFSetFileno		TIFF_PREFIX(TIFFSetFileno)
#define TIFFSetMode		TIFF_PREFIX(TIFFSetMode)
#define _TIFFSwab24BitData	TIFF_PREFIX(_TIFFSwab24BitData)
#define TIFFSwabArrayOfTriples	TIFF_PREFIX(TIFFSwabArrayOfTriples)
#define TIFFSetupStrips		TIFF_PREFIX(TIFFSetupStrips)

#endif

/// @}
