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

/// @addtogroup hxmoviemaker hxmoviemaker
/// @{
#ifndef _HX_MOVIE_STREAM
#define _HX_MOVIE_STREAM

#include <mclib/McString.h>
#include <mclib/McList.h>
#include <mclib/McDArray.h>
#include <mclib/McHandle.h>
#include <mclib/McWatch.h>
#include <mclib/McFilename.h>

#include <hxcore/HxThread.h>
#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortSeparator.h>
#include <hxcore/HxPortFilename.h>
#include <hxcore/HxBunch.h>

#include <hxmoviemaker/HxMovieMakerWinDLLApi.h>
#include <hxmoviemaker/HxPortPlayer.h>

#include <Inventor/SbLinear.h>
#include <Inventor/nodes/SoCallback.h>


class HxMoviePlayer;
class HxMovieData;
class HxMovieSegment;


class HXMOVIEMAKER_API HxMovieStream : public McLink
{
private:    HxMovieStream(){};
public:     HxMovieStream( HxMovieData & inMovie );
           ~HxMovieStream();

    void    open( mclong inChunkNum, mcint64 inOffset=0, int inDontAlter=0 );
    void    close();
    void    read(  mclong  inByteCount, void * inDst, mclong inSegIdx=-1 );
    void    seek(  mcint64 inByteCount );
    void    write( mclong  inByteCount, void * inSrc, mclong inSegIdx=-1 );

    void    segmentRead( mclong inSegNum, HxMovieSegment * ioSeg=0  );
    void    segmentWrite( HxMovieSegment & outSeg );

    void    storeStreamed();
    int     enterIO( McLink * inWaitPtr=0 );
    void    leaveIO();

    void    idxClear( int inSetComplete=0 );
    void    idxSet( mclong inSegNum, mclong   inChunkNum, mcint64   inByteOffset );
    void    idxGet( mclong inSegNum, mclong &outChunkNum, mcint64 &outByteOffset );
    void    idxRemoveLast();
    mclong  idxLength();
    void    idxScan();
    void    idxFileRead();
    void    idxFileWrite();
    void    idxFileDelete();

    mclong  idxMovieToStream( mclong inIdx );
    mclong  idxStreamToMovie( mclong inIdx );

    McLink* waitAdd();
    void    waitDel( McLink * & ioPtr );
    int     waitIsTop( McLink * inPtr );

    enum { t_none=0, t_bigfile, t_singlefiles };

    HxMovieData       * _movie;

    int                 _type;
    int                 _forceDirect;
    int                 _forceWriteable;
    int                 _doAppend;

    // only used on t_bigfile
    McString            _fileTemplate;
    McFilename          _fileCurr;

    // segment alignment
    int                 _segOffset;
    int                 _segStride;
    int                 _segCount;

    // current state
    int                 _isOpen;

    // sync when multiple readers/writers work on the same big file
    HxMutex             _mutex;
    HxWaitCondition     _wait;

    // file descriptor
    void              * _descriptor;
    int                 _descriptorIsFILE;
#ifdef _WINDOWS
    OVERLAPPED          _overlapped;
#endif

    // chunk info
    mclong              _chunkNumCurr; // number of the current data chunk; 0-based; -1 if none
    mcint64             _chunkByteOff;
    mcint64             _chunkBytesMax;

    // index (only on big-files)
    HxMutex             _idxMutex;
    int                 _idxIsComplete;
    int                 _idxForceWrite;
    McDArray<mclong>    _idxSegToChunkNum;
    McDArray<mcint64>   _idxSegToByteOffset;
    HxBunch             _idxSegToFileName; // only valid if _type==t_singlefiles

    // waiters queue
    McList<McLink>      _waitList;
    HxMutex             _waitListMutex;
};


#endif

/// @}
