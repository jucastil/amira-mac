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
#ifndef HXIMTINYTIFF_H
#define HXIMTINYTIFF_H

#ifndef NULL
#define NULL 0
#endif

#ifndef XMD_H
#define XMD_H // Shut JPEGlib up.
#endif

#include <exlibtiff/tiffio.h>
#include <exlibtiff/tif_dir.h>
#include <exlibtiff/tiffiop.h>

#ifndef uchar
#define uchar unsigned char
#endif

static int tag_size_bytes[13] = { 1, 1, 1, 2, 4, 8, 1, 1, 2, 4, 8, 4, 8 };

static int one = 1;
static int bigendian = (*(char *)&one == 0);
static int swabflag = 0; // we can only set this one opening file,
// it depends on internal endian

typedef struct
{
    uint16 tiff_magic;
    uint16 tiff_version;
    uint32 tiff_diroff;
} TDimTiffHeader;

typedef struct TDimTiffIFDEntry
{
    uint16 tag;
    uint16 type;
    uint32 count;
    uint32 offset;
} TDimTiffIFDEntry;

typedef struct TDimTiffIFD
{
    uint16 count;
    TDimTiffIFDEntry *entries;
    uint32 next;
} TDimTiffIFD;

typedef struct TDimTiffIFDs
{
    uint16 count;
    TDimTiffIFD *ifds;
} TDimTiffIFDs;

TDimTiffIFDs initTDimTiffIFDs ();
void clearTiffIFD (TDimTiffIFD *ifd);

bool isTagPresentInIFD ( TDimTiffIFD *ifd, uint32 tag );
bool isTagPresentInFirstIFD ( TDimTiffIFDs *ifds, uint32 tag );
int getTagPositionInIFD ( TDimTiffIFD *ifd, uint32 tag );


//  TDimTiffIFD readFirstTiffIFD (FILE *stream, int offset);
//  void readTiffTag (TDimTiffIFD *ifd, FILE *stream, uint32 tag, uint32 &size, void **buf);

//#ifdef _TIFF_

void clearTiffIFDs (TDimTiffIFDs *ifds);

TDimTiffIFD readFirstTiffIFD (TIFF *tif);
TDimTiffIFDs readAllTiffIFDs (TIFF *tif);
void freeTiffTagBuf( uchar **buf );

int32 getTiffTagOffset(TIFF *tif, TDimTiffIFD *ifd, uint32 tag);
int32 getTiffTagCount(TIFF *tif, TDimTiffIFD *ifd, uint32 tag);


// reads to buffer data of size in bytes from determant offset and do necessary convertion
void readTiffBuf (TIFF *tif, uint32 offset, uint32 size, uint32 type, uchar **buf);
int readTiffBufNoAlloc (TIFF *tif, uint32 offset, uint32 size, uint32 type, uchar *buf);
void readTiffTag (TIFF *tif, TDimTiffIFD *ifd, uint32 tag, uint32 &size, uint32 &type, uchar **buf);
// this function reads tif tag using provided size and type instead of IFD values
void readTiffCustomTag (TIFF *tif, TDimTiffIFD *ifd, uint32 tag, uint32 size, uint32 type, uchar **buf);

//#endif

#endif //HXIMTINYTIFF_H

/// @}
