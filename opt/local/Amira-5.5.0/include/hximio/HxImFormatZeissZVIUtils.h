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
#ifndef HX_IMFORMATZEISSZVIUTILS_H
#define HX_IMFORMATZEISSZVIUTILS_H

#ifdef HX_OS_WIN

// Needed for various Windows data structures.
#include <windows.h>

#include "HxImFormatZeissZVI.h"

//allocate some mem and add it to our allocation list
void* AllocateList(unsigned long size, MemList* ml);

//convert normal string into wide character for IStorage object
wchar_t* CreateWideChar(const char* str);

//open a storage file (like .zvi)
IStorage* OpenFile(const char* file_name);

//open a stream in a folder
IStream* OpenStream(IStorage* parent,char* stream_name);

//open a subfolder folder in an open storage object
IStorage* OpenFolder(IStorage* parent,char* folder_name);

//this func reads in the image header and the image itself
long ReadImage(IStream* stream, unsigned char* b_out, unsigned long* b_read, long* size,
               bool fill_struct, MemList* ml);

//look up the VAR ID found (in vte) and read the corresponding size of mem from stream into b_out
long VTE_Read(unsigned short vte, IStream* stream, unsigned char* b_out,
              unsigned long* b_read, bool fill_struct, bool Alloc, MemList* ml);

//read from stream into Val using type
bool ReadValue(void* Val, IStream* stream, unsigned short type, MemList* ml);

//read from stream into Val using type
bool AllocValue(ZVI_Variant* Val, IStream* stream, MemList* ml);

bool ReadZVIScaling(IStream *pContents, _Image_Scaling_Contents* zvi, MemList* ml);

//open a subfolder folder in an open storage object
IStorage* OpenFolderWCHAR(IStorage* parent, wchar_t* folder_name);

bool ReadZVITags(IStream *pContents, _Image_Tags_Contents* zvi, MemList* ml);

bool ReadZVI(IStorage* pSubStorageImage, IStream *pImageContents, _Image* zvi, MemList* ml);

//reads a Thumbnail of the pic stored in the .zvi...
bool ReadThumbnail(IStream* pThumb, _Thumbnail* zvi, MemList* ml);

//find closest DWORD border
unsigned long DWBorder(unsigned long size);

//this func is a hack... it's a M$ specific format which is not documented...
//searching for ID 0x00000013 worked for all files I know... but it may fail for others
//this stream only contains the additional file information used by win9x/2k/NT
//there is another stream called DocumentSummaryInformation which contains other useless info
//so I didn't add it here
bool ReadISummaryInformation(IStream* pInfo, _ISummaryInformation* zvi, MemList* ml);

#endif // HX_OS_WIN

#endif // HX_IMFORMATEZISSZVIUTILS_H

/// @}
