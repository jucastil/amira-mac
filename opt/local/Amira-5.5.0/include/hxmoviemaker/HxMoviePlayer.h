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
#ifndef _HX_MOVIE_PLAYER
#define _HX_MOVIE_PLAYER

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
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortSeparator.h>
#include <hxcore/HxPortFilename.h>
#include <hxcore/HxPortButtonList.h>

#include <hxcore/HxBunch.h>

#include <hxmoviemaker/HxMovieMakerWinDLLApi.h>
#include <hxmoviemaker/HxPortPlayer.h>

#include <Inventor/SbLinear.h>
#include <Inventor/nodes/SoCallback.h>

#include <hxcore/hxgl.h>


#define HXSMP_DO_DEBUG          0
#define HXSMP_USE_IJL           0  // use Intels IPP based JPEG-Lib
#define HXSMP_FRAME_MARK_LOW    15
#define HXSMP_FRAME_MARK_HIGH   25
#define HXSMP_TILE_WIDTH        128
#define HXSMP_TILE_HEIGHT       128
#define HXSMP_PAGESIZE          2048

#define EXTAMOVINFO "amov"
#define EXTAMOVBIG  "amovstream"
#define EXTAMOVIDX  "amovindex"


#ifndef APIENTRY
#define APIENTRY
#endif
// OpenGL - texture compression
typedef void (APIENTRY * PFNGLCOMPRESSEDTEXIMAGE3DARBPROC)    (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRY * PFNGLCOMPRESSEDTEXIMAGE2DARBPROC)    (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRY * PFNGLCOMPRESSEDTEXIMAGE1DARBPROC)    (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRY * PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRY * PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRY * PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRY * PFNGLGETCOMPRESSEDTEXIMAGEARBPROC)   (GLenum target, GLint level, void *img);

#define GL_COMPRESSED_ALPHA_ARB                 0x84E9
#define GL_COMPRESSED_LUMINANCE_ARB             0x84EA
#define GL_COMPRESSED_LUMINANCE_ALPHA_ARB       0x84EB
#define GL_COMPRESSED_INTENSITY_ARB             0x84EC
#define GL_COMPRESSED_RGB_ARB                   0x84ED
#define GL_COMPRESSED_RGBA_ARB                  0x84EE
#define GL_TEXTURE_COMPRESSION_HINT_ARB         0x84EF
#define GL_TEXTURE_IMAGE_SIZE_ARB               0x86A0
#define GL_TEXTURE_COMPRESSED_ARB               0x86A1
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS_ARB   0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS_ARB       0x86A3

// OpenGL - color table
typedef void (APIENTRY * PFNGLCOLORTABLESGIPROC)               (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *table);
typedef void (APIENTRY * PFNGLCOLORTABLEPARAMETERFVSGIPROC)    (GLenum target, GLenum pname, const GLfloat *params);
typedef void (APIENTRY * PFNGLCOLORTABLEPARAMETERIVSGIPROC)    (GLenum target, GLenum pname, const GLint *params);
typedef void (APIENTRY * PFNGLCOPYCOLORTABLESGIPROC)           (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
typedef void (APIENTRY * PFNGLGETCOLORTABLESGIPROC)            (GLenum target, GLenum format, GLenum type, GLvoid *table);
typedef void (APIENTRY * PFNGLGETCOLORTABLEPARAMETERFVSGIPROC) (GLenum target, GLenum pname, GLfloat *params);
typedef void (APIENTRY * PFNGLGETCOLORTABLEPARAMETERIVSGIPROC) (GLenum target, GLenum pname, GLint *params);

#define GL_GENERATE_MIPMAP_SGIS           0x8191
#define GL_GENERATE_MIPMAP_HINT_SGIS      0x8192

#define GL_COLOR_TABLE_SGI                0x80D0
#ifndef GL_TEXTURE_COLOR_TABLE_SGI
#  define GL_TEXTURE_COLOR_TABLE_SGI      0x80BC
#endif


class HxMovieSegment;
class HxMovieStream;
class HxMovieData;


class HXMOVIEMAKER_API HxMoviePlayer : public HxCompModule
{
    HX_HEADER( HxMoviePlayer );

public:

    class MyThread;
    class MyContext;


////////////////////////////////////////////////////////////////////////////////
// MyThread
// objects of this class perform the parallel retrieval of segment data
////////////////////////////////////////////////////////////////////////////////
    class MyThread : public HxThread, public McLink
    {
    private:    MyThread(){};
    public:     MyThread( HxMoviePlayer * inPlayer );
               ~MyThread();

        virtual void  run(); // abstract from base class

        // my player object
        HxMoviePlayer * _player;
    };

////////////////////////////////////////////////////////////////////////////////
// MyContext
// one for each GL-context this player has to render to
////////////////////////////////////////////////////////////////////////////////
    class MyContext : public McLink
    {
    public:
                            MyContext();
                           ~MyContext();

            void            texFree();

    static  MyContext     * get( unsigned int contextId );

            // context ID
            unsigned int            _id;
            // big texture stuff
            GLuint            _texId;
            GLuint            _pboTexId;
            int                     _texFormat;
            int                     _texWidth;
            int                     _texHeight;

    static  int                     _instCount;
    static  unsigned char         * _texData;
    static  int                     _texDataLen;
    static  McList<MyContext>       _contexts;
    };

////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////
    // UI ports
    ////////////////////////////////////////

    HxPortButtonList        _port_NewResult;
    HxPortMultiMenu         _port_Src;
    HxPortIntSlider         _port_Pos;
    HxPortPlayer            _port_Player;

    HxPortRadioBox          _port_pixelFormat;
    HxPortToggleList        _port_postCompress;
    HxPortIntTextN          _port_bytesPerChunk;

    ////////////////////////////////////////
    // thread stuff
    ////////////////////////////////////////

    // list of the read treads
    McList<MyThread>        _threads;
    int                     _threadsIsSingleThreaded;

    // idling read treads wait with this for work - lock for accessing _isPlaying
    static HxMutex          _threadWorkMutex;
    static HxWaitCondition  _threadWorkWait;

    // main thread waits with this for new data from read threads
    HxMutex                 _forDataMutex;
    HxWaitCondition         _forDataWait;

    ////////////////////////////////////////
    // content stuff
    ////////////////////////////////////////

    // lock this while accessing segment stuff that could be touched by a read thread
    HxMutex                 _segmentMutex;
    // segment recycle bin
    McList<HxMovieSegment>  _segmentsBin;
    // sorted list of actual loading segments
    McList<HxMovieSegment>  _segmentsLoad;
    int                     _segmentsLoadAheadCount;

    // actual visible segents
    McList<HxMovieSegment>  _segmentsCurr;
    // number of the next segment to load
    int                     _segNumNext;

    HxMovieData           * _movieSrc; // current source movie
    HxMovieData           * _movieDst; // current destination movie


    ////////////////////////////////////////
    // play state
    ////////////////////////////////////////
    // if that flag is zero, the read threads exit
    int                     _playPlaying;
    int                     _playBackward;
    int                     _playPaused; // if paused, _playPlaying may be still true

    //
    McWatch                 _frameTimer;
    float                   _frameTimeNext;
    float                   _frameTimeFrameDist;
    float                   _frameTimeFrameDistMin;
    float                   _frameTimeFactor;

    ////////////////////////////////////////
    // render stuff
    ////////////////////////////////////////

    McHandle<SoCallback>    _callback;
    int                     _doPreprocessing;

    McWatch                 _fpsTimer;
    float                   _fpsTimeLast;
    float                   _fpsTimeCurr;
    float                   _fpsTimeStart;
    float                   _fpsTimeStop;
    int                     _fpsFrameCount;
    #define                 _fpsFrameNum 10
    float                   _fpsFrames[_fpsFrameNum];
    int                     _fpsFrameCurr;

    ////////////////////////////////////////
    // memory stuff
    ////////////////////////////////////////
    static HxMutex          _fastMemMutex;
    static mculong          _fastMemAllocated;


    ////////////////////////////////////////
    // OpenGL stuff
    ////////////////////////////////////////
    static PFNGLCOMPRESSEDTEXIMAGE2DARBPROC    _glCompressedTexImage2DARB ;
    static PFNGLGETCOMPRESSEDTEXIMAGEARBPROC   _glGetCompressedTexImageARB ;
    static PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC _glCompressedTexSubImage2DARB ;

    static PFNGLCOLORTABLESGIPROC              _glColorTableSGI ;
    static PFNGLCOLORTABLEPARAMETERIVSGIPROC   _glColorTableParameterivSGI ;
    static PFNGLCOLORTABLEPARAMETERFVSGIPROC   _glColorTableParameterfvSGI ;


////////////////////////////////////////////////////////////////////////////////

public:
    enum SeekMode { S_END, S_START, S_CURR };

     HxMoviePlayer();
    ~HxMoviePlayer();


    virtual void  update ();
    virtual void  compute();


    static void   renderCallback( void * userData, SoAction * action );
    void          render ( SoGLRenderAction * renderAction );
    void          timeout();
    void          readImageJpeg( HxMovieSegment & dst, const char* fn, int size[3] );


    static void * fastMemAlloc( int pages );
    static void   fastMemFree( void * mem, int pages );
    static void   myMessage( const char* format, ... );
    static void   myHtonl( mculong * arr, int count );
    static void   myNtohl( mculong * arr, int count );
    static int    calcPages( int len );
    static int    getNumberOfProcessors();

    void          actionError();
    void          actionInit( int inIsInteractive=0 );
    void          actionPlay( int inBackward=0, int inIsInteractive=0 );
    void          actionPause();
    void          actionResume();
    void          actionStop( int inResetButtons=1 );
    void          actionSeek( mclong inFrame, SeekMode inMode );

    /// Tcl command interface.
    int           parse(Tcl_Interp* t, int argc, char **argv);


private:

    int           frameGetTimeToNext();
    void          frameFetchNext();
    void          frameSchedule();
    int           frameGetNumAvailable();

    void          segmentRecycle( HxMovieSegment & ioSeg );
    void          segmentsRecycle( McList<HxMovieSegment> & ioSegs );

    void          startThreads();
    void          stopThreads ();

    mclong        positionDetermineMax();
};


#endif

/// @}
