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
#ifndef HXIMTIFFFORMAT_H
#define HXIMTIFFFORMAT_H

#include "memio.h"

#include "HxImFormatInterface.h"
#include "HxImPsiaFormat.h"
#include "HxImFluoviewFormat.h"
#include "HxImCzLsmFormat.h"
#include "HxImStkFormat.h"
#include "HxImTinyTiff.h"
#include "HxImFormatUtils.h"

#ifndef NULL
#define NULL 0
#endif

#ifndef XMD_H
#define XMD_H // Shut JPEGlib up.
#endif

#include <exlibtiff/tiffio.h>
#include <exlibtiff/tif_dir.h>

typedef enum {
    tstGeneric  = 0,
    tstStk      = 1,
    tstPsia     = 2,
    tstFluoview = 3,
    tstCzLsm    = 4
} DIM_TiffSubType;

typedef struct TDimTiffParams
{
    TIFF  *dimTiff;
    DIM_TiffSubType subType;
    TDimImageInfo info;
    TDimTiffIFDs ifds;
    TDimStkInfo stkInfo;
    psiaInfoHeader psiaInfo;
    TDimFluoviewInfo fluoviewInfo;
    TDimLsmInfo lsmInfo;
} TDimTiffParams;


// DLL EXPORT FUNCTION
extern "C" {
    TDimFormatHeader* dimTiffGetFormatHeader(void);
}


long stkGetNumPlanes(TIFF *tif);
void init_image_palette( TIFF *tif, TDimImageInfo *info );
void fluoviewInitPalette( TDimTiffParams *tiffParams, TDimImageInfo *info );
bool stkIsTiffValid(TDimTiffParams *tiffParams);
int stkGetInfo ( TDimTiffParams *tiffParams );
bool psiaIsTiffValid(TDimTiffParams *tiffParams);
int psiaGetInfo (TDimTiffParams *tiffParams);
bool fluoviewIsTiffValid(TDimTiffParams *tiffParams);
int fluoviewGetInfo (TDimTiffParams *tiffParams);
bool lsmIsTiffValid(TDimTiffParams *tiffParams);
int lsmGetInfo (TDimTiffParams *tiffParams);
void stkClearInfo ( TDimTiffParams *tiffParams );
void stkInitInfo( TDimStkInfo *stkInfo );
DIM_UINT read_tiff_metadata (TDimFormatHandle *fmtHndl, TDimTiffParams *tifParams, int group, int tag, int type);
char* read_text_tiff_metadata ( TDimFormatHandle *fmtHndl, TDimTiffParams *tifParams );
int read_tiff_image(TDimFormatHandle *fmtHndl, TDimTiffParams *tifParams);
int write_tiff_image(TDimFormatHandle *fmtHndl, TDimTiffParams *tifParams);
void getCurrentPageInfo(TDimTiffParams *tiffParams);
void getImageInfo(TDimTiffParams *tiffParams);
TDimImageInfo initTDimImageInfo();
void* DimMalloc(DIM_ULONG size);
void* DimFree(void *p);
long getImgSizeInBytes(TDimImageBitmap *img);
DIM_UINT stkReadMetaMeta (TDimFormatHandle *fmtHndl, int group, int tag, int type);
void stkWriteTextMeta(TDimTiffParams *tiffParams, MemIOBuf *outIOBuf);
void lsmWriteTextMeta(TDimTiffParams *tiffParams, MemIOBuf *outIOBuf);
void fluoviewWriteTextMeta(TDimTiffParams *tiffParams, MemIOBuf *outIOBuf);
void psiaWriteTextMeta(TDimTiffParams *tiffParams, MemIOBuf *outIOBuf);
DIM_UINT  stkReadPlane(TDimTiffParams *tiffParams, int plane, TDimImageBitmap *img, TDimFormatHandle *fmtHndl);
DIM_UINT fluoviewReadPlane( TDimFormatHandle *fmtHndl, TDimTiffParams *tiffParams, int plane );
DIM_UINT psiaReadPlane(TDimFormatHandle *fmtHndl, TDimTiffParams *tiffParams, int plane, TDimImageBitmap *img);

// INTERNAL FUNCTIONS
DIM_INT dimTiffValidateFormatProc (DIM_MAGIC_STREAM *magic, DIM_UINT length);

TDimFormatHandle dimTiffAquireFormatProc( void );
void dimTiffReleaseFormatProc (TDimFormatHandle *fmtHndl);

DIM_UINT dimTiffOpenImageProc  (TDimFormatHandle *fmtHndl, DIM_ImageIOModes io_mode);
DIM_UINT dimTiffFOpenImageProc (TDimFormatHandle *fmtHndl, char* fileName, DIM_ImageIOModes io_mode);
DIM_UINT dimTiffIOpenImageProc (TDimFormatHandle *fmtHndl, char* fileName,
                                DIM_IMAGE_CLASS *image, DIM_ImageIOModes io_mode);

void dimTiffCloseImageProc     (TDimFormatHandle *fmtHndl);

DIM_UINT dimTiffGetNumPagesProc       ( TDimFormatHandle *fmtHndl );
TDimImageInfo dimTiffGetImageInfoProc ( TDimFormatHandle *fmtHndl, DIM_UINT page_num );

DIM_UINT dimTiffReadImageProc  (TDimFormatHandle *fmtHndl, DIM_UINT page);
DIM_UINT dimTiffWriteImageProc (TDimFormatHandle *fmtHndl);

DIM_UINT dimTiffReadImagePreviewProc (TDimFormatHandle *fmtHndl, DIM_UINT w, DIM_UINT h);

DIM_UINT dimTiffReadMetaDataProc (TDimFormatHandle *fmtHndl, DIM_UINT page, int group, int tag, int type);
char* dimTiffReadMetaDataAsTextProc ( TDimFormatHandle *fmtHndl );

#endif // HXIMTIFFFORMAT_H

/// @}
