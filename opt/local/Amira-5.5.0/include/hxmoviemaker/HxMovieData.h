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
#ifndef _HX_MOVIE
#define _HX_MOVIE

#include <mclib/McString.h>
#include <mclib/McList.h>
#include <mclib/McDArray.h>
#include <mclib/McHandle.h>
#include <mclib/McWatch.h>
#include <mclib/McFilename.h>

#include <hxcore/HxData.h>
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
class HxMovieStream;


class HXMOVIEMAKER_API HxMovieData : public HxData, public McLink
{
    HX_HEADER( HxMovieData );

public:         HxMovieData( const char * inFileName = 0 );
               ~HxMovieData();

    void        bunchReadUI();
    void        bunchWriteUI();

    void        bunchNew();
    void        bunchLoad( char * inPath );
    void        bunchSave( char * inPath );
    void        bunchSourceToAbsolute();
    void        bunchSourceToRelative();

    const McString & fileName();
    void             fileNameSet( const McString & inFileName );

    void        init( HxMoviePlayer * inPlayer=0, int inWriteable=0, int inAppend=0 );
    int         isInit();
    void        end();

    virtual void update();
    virtual void compute();
    virtual void info();

    HxMoviePlayer * player(){ return _player; }
    void            playerSet( HxMoviePlayer * p = 0 );

    HxMoviePlayer         * _player;

    // ports
    HxPortMultiMenu         _port_numStreams;
    HxPortFilename          _port_stream0;
    HxPortFilename          _port_stream1;
    HxPortFilename          _port_stream2;
    HxPortFilename          _port_stream3;
    HxPortFilename        * _port_stream[4];
    HxPortMultiMenu         _port_type;

    HxPortRadioBox          _port_method;
    HxPortFloatTextN        _port_aspect;
    HxPortToggleList        _port_swapLR;
    HxPortToggleList        _port_flip;
    HxPortIntTextN          _port_maxFps;
    HxPortIntTextN          _port_maxThreads;

    HxPortIntTextN          _port_segments_per_frame;

    // parameters
    McFilename              _infoFileName;
    HxBunch                 _bunch;


    mculong                 _numStreams;
    // number of segments per frame
    int                     _numSegPerFrame;

    mculong                 _forceBytesPerChunk;
    int                     _forcePixelFormat;
    int                     _forcePostCompression;

    // in/out streams
    McList<HxMovieStream>   _streams;
};

HXMOVIEMAKER_API int HxMovieWrite( HxMovieData * inMovie, const char * inFileName );
HXMOVIEMAKER_API int HxMovieRead( const char * filename );


#endif

/// @}
