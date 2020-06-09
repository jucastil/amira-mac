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
#ifndef HXIMFORMATUTILS_H
#define HXIMFORMATUTILS_H

#include "HxImFormatInterface.h"

#include <string>

//------------------------------------------------------------------------------
// Safe calls for memory/io prototypes, if they are not supplied then
// standard functions are used
//------------------------------------------------------------------------------

void* dimMalloc ( TDimFormatHandle *fmtHndl, DIM_ULONG size );
void* dimFree   ( TDimFormatHandle *fmtHndl, void *p );
// overload of dimin free to make a safe delete
inline void dimFree( void **p ) {
  if ( *p == NULL ) return;
  delete (unsigned char *) *p;  
  *p = NULL;
}

// the stream is specified by TDimFormatHandle
DIM_ULONG dimRead  ( TDimFormatHandle *fmtHndl, void *buffer, DIM_ULONG size, DIM_ULONG count );
DIM_ULONG dimWrite ( TDimFormatHandle *fmtHndl, void *buffer, DIM_ULONG size, DIM_ULONG count );
DIM_INT   dimFlush ( TDimFormatHandle *fmtHndl );
DIM_INT   dimSeek  ( TDimFormatHandle *fmtHndl, DIM_LONG offset, DIM_INT origin );
DIM_ULONG dimSize  ( TDimFormatHandle *fmtHndl );
DIM_ULONG dimTell  ( TDimFormatHandle *fmtHndl );
DIM_INT   dimEof   ( TDimFormatHandle *fmtHndl );
DIM_INT   dimClose ( TDimFormatHandle *fmtHndl );
   
//------------------------------------------------------------------------------
// tests for provided callbacks
//------------------------------------------------------------------------------
bool isCustomReading ( TDimFormatHandle *fmtHndl );
bool isCustomWriting ( TDimFormatHandle *fmtHndl );

//------------------------------------------------------------------------------------------------
// misc
//------------------------------------------------------------------------------------------------

DIM_UCHAR iTrimUC (int num);
TDimFormatHandle initTDimFormatHandle();
TDimImageInfo initTDimImageInfo();

//------------------------------------------------------------------------------------------------
// swap
//------------------------------------------------------------------------------------------------

void dimSwapShort(DIM_UINT16* wp);
void dimSwapLong(DIM_UINT32* lp);
void dimSwapArrayOfShort(DIM_UINT16* wp, register DIM_ULONG n);
void dimSwapArrayOfLong(register DIM_UINT32* lp, register DIM_ULONG n);
void dimSwapDouble(double *dp);
void dimSwapArrayOfDouble(double* dp, register DIM_ULONG n);
void dimSwapData(int type, long size, void* data);

//------------------------------------------------------------------------------------------------
// TDimImageBitmap
//------------------------------------------------------------------------------------------------

// you must call this function once declared image var
void initImagePlanes(TDimImageBitmap *bmp);

int allocImg( TDimImageBitmap *img, DIM_UINT w, DIM_UINT h, DIM_UINT samples, DIM_UINT depth);
// alloc image using w,h,s,d
int allocImg( TDimFormatHandle *fmtHndl, TDimImageBitmap *img, DIM_UINT w, DIM_UINT h, DIM_UINT samples, DIM_UINT depth);
// alloc image using info
int allocImg( TDimFormatHandle *fmtHndl, TDimImageInfo *info, TDimImageBitmap *img);
// alloc handle image using info
int allocImg( TDimFormatHandle *fmtHndl, TDimImageInfo *info );

void deleteImg( TDimImageBitmap *img);
void deleteImg( TDimFormatHandle *fmtHndl, TDimImageBitmap *img);

long getLineSizeInBytes(TDimImageBitmap *img);
long getImgSizeInBytes(TDimImageBitmap *img);
long getImgNumColors(TDimImageBitmap *img);

int getSampleHistogram(TDimImageBitmap *img, long *hist, int sample);
int normalizeImg(TDimImageBitmap *img, TDimImageBitmap *img8);
int resizeImgNearNeighbor( TDimImageBitmap *img, unsigned int newWidth, unsigned int newHeight);
int retreiveImgROI( TDimImageBitmap *img, DIM_ULONG x, DIM_ULONG y, DIM_ULONG w, DIM_ULONG h );

std::string getImageInfoText( TDimImageBitmap *img );

//------------------------------------------------------------------------------------------------
// metadata
//------------------------------------------------------------------------------------------------

void clearMetaTag(TDimTagItem *tagItem);
void clearMetaTags(TDimTagList *tagList);
//bool isTagPresent(TDimTagList *tagList, int tag);
bool isTagPresent(TDimTagList *tagList, int group, int tag);
//int tagPos(TDimTagList *tagList, int tag);
int tagPos(TDimTagList *tagList, int group, int tag);

int addMetaTag(TDimTagList *tagList, TDimTagItem item);

#endif //HXIMFORMATUTILS_H



/// @}
