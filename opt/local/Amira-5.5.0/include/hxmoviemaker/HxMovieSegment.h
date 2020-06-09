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
#ifndef _HX_MOVIE_SEGMENT
#define _HX_MOVIE_SEGMENT

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
class HxMovieStream;


class HXMOVIEMAKER_API HxMovieSegment : public McLink
{
public:

    class MyHeader;

////////////////////////////////////////////////////////////////////////////////
// MyHeader
// structure which leads every segment in an amovie files
////////////////////////////////////////////////////////////////////////////////
    class MyHeader
    {
    public:
        void    init();

        enum { h_version=2 }; // e1
        enum { f_none=0, f_native, f_indexed, f_glcompressed }; // e2
        enum { c_none=0, c_zip };   // e3
        enum { l_mono=0, l_stereoUD, l_stereoLR, l_stereoInterlaced }; // e4

        mculong             _version;       // header version (e1)
        mculong             _width;         // pixel width of the whole segment
        mculong             _height;        // pixel height of the whole segment
        mculong             _bytesPerPixel; // bytes per pixel
        mculong             _hasAlpha;      // zero if pixels have no alpha compunent
        mculong             _format;        // this is the pixel format (e2)
        mculong             _internalFormat;// OpenGls format identifier if GL-compression is used
        mculong             _tileNumHorz;   // number of tiles in x direction
        mculong             _tileNumVert;   // number of tiles in y direction
        mculong             _tileWidth;     // pixel width of a single tile
        mculong             _tileHeight;    // pixel height of a single tile
        mculong             _bodyMemLen;    // len of allocated memory for storing the imagedata ; is a multiple of HXSMP_PAGESIZE
        mculong             _userDataLen;   // len of the memory part used for non-compressed image data
        mculong             _userDataLenCompressed; // len of the same data if compressed
        mculong             _userDataCompression;   // compress method (e3)
        mculong             _layout;        // type of the image data (e4)
    };


private:    HxMovieSegment(){};
public:     HxMovieSegment( HxMoviePlayer & inPlayer );
           ~HxMovieSegment();

    void    load();

    void    retrieveFaked();
    void    retrieveExternal();
    void    retrieveStreamed();
    void    readImageJpeg();

    void    storeStreamed();

    void    compressGL();
    void    compressZIP();
    void    tileize();


    int                     _loadMe; // set to 0 by the thread which grabs this segment for loading
    int                     _isLoaded;
    int                     _segNum; // index in the whole movie

    HxMoviePlayer         * _player;
    HxMovieStream         * _streamIn;
    McString                _file;

    // image data stuff
    unsigned char         * _tiles;
    mculong                 _tilesLen;
    MyHeader              * _header;
    mculong                 _headerLen;

    mculong               * _tilesLenPerTile;

    unsigned char         * _palette;

    //
    McLink                * _waitPtr;
};


#endif

/// @}
