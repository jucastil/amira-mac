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
#ifndef HXXTIFFIO_H
#define HXXTIFFIO_H

#ifndef NULL
#define NULL 0
#endif

#include <exlibtiff/tiffio.h>
#include <exlibtiff/tiffiop.h>

// Define public Tag names and values here

// STK TAGS
#define TIFFTAG_STK_UIC1     33628
#define TIFFTAG_STK_UIC2     33629
#define TIFFTAG_STK_UIC3     33630
#define TIFFTAG_STK_UIC4     33631

// PSIA TAGS
#define TIFFTAG_PSIA_MAGIC_NUMBER        50432
#define TIFFTAG_PSIA_VERSION             50433
#define TIFFTAG_PSIA_DATA                50434
#define TIFFTAG_PSIA_HEADER              50435
#define TIFFTAG_PSIA_COMMENTS            50436
#define TIFFTAG_PSIA_LINE_PROFILE_HEADER 50437

// EXIF
#define TIFFTAG_EXIF_IFD 34665

// FLUOVIEW TAGS
#define TIFFTAG_FLUO_MMHEADER    34361
#define TIFFTAG_FLUO_MMSTAMP     34362
#define TIFFTAG_FLUO_MMUSERBLOCK 34386

// CARL ZEISS LSM
#define TIFFTAG_CZ_LSMINFO       34412

// GEOTIFF TAGS
// tags 33550 is a private tag registered to SoftDesk, Inc
#define TIFFTAG_GEOPIXELSCALE       33550
// tags 33920-33921 are private tags registered to Intergraph, Inc
#define TIFFTAG_INTERGRAPH_MATRIX    33920   // $use TIFFTAG_GEOTRANSMATRIX !
#define TIFFTAG_GEOTIEPOINTS         33922
// tags 34263-34264 are private tags registered to NASA-JPL Carto Group
#ifdef JPL_TAG_SUPPORT
#define TIFFTAG_JPL_CARTO_IFD        34263    // $use GeoProjectionInfo !
#endif
#define TIFFTAG_GEOTRANSMATRIX       34264    // New Matrix Tag replaces 33920
// tags 34735-3438 are private tags registered to SPOT Image, Inc
#define TIFFTAG_GEOKEYDIRECTORY      34735
#define TIFFTAG_GEODOUBLEPARAMS      34736
#define TIFFTAG_GEOASCIIPARAMS       34737

/*
*  Define Printing method flags. These
*  flags may be passed in to TIFFPrintDirectory() to
*  indicate that those particular field values should
*  be printed out in full, rather than just an indicator
*  of whether they are present or not.
*/
#define TIFFPRINT_GEOKEYDIRECTORY   0x80000000
#define TIFFPRINT_GEOKEYPARAMS      0x40000000



/**********************************************************************
*    Nothing below this line should need to be changed by the user.
**********************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

    extern TIFF* XtiffOpen(const char* name, const char* mode);
    extern TIFF* XtiffdOpen(int fd, const char* name, const char* mode);
    extern void XtiffClose(TIFF *tif);

    extern TIFF* XtiffClientOpen(const char* name, const char* mode, 
        thandle_t thehandle,
        TIFFReadWriteProc, TIFFReadWriteProc,
        TIFFSeekProc, TIFFCloseProc,
        TIFFSizeProc,
        TIFFMapFileProc, TIFFUnmapFileProc);
#if defined(__cplusplus)
}
#endif

#endif // HXXTIFFIO_H

/// @}
