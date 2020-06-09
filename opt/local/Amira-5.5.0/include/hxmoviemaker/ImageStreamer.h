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
#ifndef IMAGE_STREAMER_H
#define IMAGE_STREAMER_H

#define FT_SERIES 0
#define FT_MPEG 1
#define FT_AVI 2

#include <mclib/McString.h>
#include <hxmoviemaker/HxMovieMakerWinDLLApi.h>

class QImage;

/** Class that encapsulates image streaming, used to author video files frame-by-frame.
    This base class writes a single file for each frame. The filename is assumed
    to be contain a hashmark sequence, name.####.jpg. The haskmarks are replaced by
    the actual frame number. Derived classes implement actual movie formats, i.e.,
    MPEG or AVI via Direct Show. */

class HXMOVIEMAKER_API ImageStreamer
{
  public:
    /// Constructor.
    ImageStreamer();

    /// Destructor.
    virtual ~ImageStreamer();

    /// Prepares streaming into <fileame>, possibly preallocated
    virtual bool openStream(const char * filename, int preAllocMB=-1);

    /// Start streaming
    virtual bool startStream();

    /// Stop streaming
    virtual bool stopStream();

    // Send one frame
    virtual bool putFrame(const QImage& image);
    // Send one frame
    virtual bool putFrame( int inSize[3], unsigned char * inData );

    // Get the streamer video format
    virtual bool getFormat(int& w,int &h, int& bpp);

    /// Set the streamer video format.
    virtual bool setFormat(int w,int h, int bpp);

    /// Returns true if only fixed frame rates are supported.
    virtual bool hasFixedFrameRates();

    /// Returns number of frame rate codes.
    virtual void getFixedFrameRatesCodes(int& ncodes, char**& codes);

    virtual float getFrameRate(int code);

    virtual bool setFrameRate(int fps);

    virtual bool setFixedFrameRate(int code);

    // ready to stream ?
    virtual bool canStartStream();

    // everythig's OK with the streaming capabilities ?
    virtual bool canStream();

    virtual bool canQuality();

    virtual bool setQuality(double q);

    virtual double currentQuality();

  protected:
    McString filename;
    int frameNumber;
    int size[3];
};

#endif

/// @}
