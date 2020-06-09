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

/// @addtogroup dsstreamer dsstreamer
/// @{
class CFrameStream;

#include"ifstream.h"


//------------------------------------------------------------------------------
// Class CStreamer
//
// This is the main class for the streamer filter. It inherits from
// CSource, the DirectShow base class for source filters.
//------------------------------------------------------------------------------
class CStreamer : public CSource,IFrameStreamer
{
 public:
  
  DECLARE_IUNKNOWN;
  
  // The only allowed way to create CStreamers!
  static CUnknown * WINAPI CreateInstance(LPUNKNOWN lpunk, HRESULT *phr);
  
  STDMETHODIMP NonDelegatingQueryInterface(REFIID riid, void **ppv)
    {
      if( riid == IID_IFrameStreamer )
        {
	  return GetInterface((IFrameStreamer*)this, ppv);
        }
      return CSource::NonDelegatingQueryInterface(riid, ppv);
    }

  // called to put one frame  
  STDMETHODIMP PutFrame(BYTE* pData,long pDataLen, REFERENCE_TIME *pTimeStart,
			REFERENCE_TIME *pTimeEnd);
  
  STDMETHODIMP GetCurrentMediaType(AM_MEDIA_TYPE *pmt);
  
  STDMETHODIMP SetFormat(AM_MEDIA_TYPE *pmt);
  
  STDMETHODIMP setFormat(int w,int h,int bpp);
  
 private:
  
  // It is only allowed to to create these objects with CreateInstance
  CStreamer(LPUNKNOWN lpunk, HRESULT *phr);
  CFrameStream * mBStream;
  
}; // CStreamer


//------------------------------------------------------------------------------
// Class CFrameStream
//
// This class implements the stream which is used to output the 
// data from the source filter. It inherits from DirectShows's base
// CSourceStream class.
//------------------------------------------------------------------------------
class CFrameStream : public CSourceStream
{

public:

    CFrameStream(HRESULT *phr, CStreamer *pParent, LPCWSTR pPinName);
    ~CFrameStream();

    // should put data into the supplied video frame: not used because
    // this is done by the caller of putFrame()
    HRESULT FillBuffer(IMediaSample *pms);

    // Ask for buffers of the size appropriate to the agreed media type
    HRESULT DecideBufferSize(IMemAllocator *pIMemAlloc,
                             ALLOCATOR_PROPERTIES *pProperties);

    // Set the agreed media type, and set up the necessary ball parameters
    HRESULT SetMediaType(const CMediaType *pMediaType);

    // Because we calculate the ball there is no reason why we
    // can't calculate it in any one of a set of formats...
    HRESULT CheckMediaType(const CMediaType *pMediaType);
    HRESULT GetMediaType(int iPosition, CMediaType *pmt);

    // Resets the stream time to zero
    HRESULT OnThreadCreate(void);

    // Quality control notifications sent to us
    STDMETHODIMP Notify(IBaseFilter * pSender, Quality q);
    
    // puts a frame
    STDMETHODIMP PutFrame(BYTE* pData,long lDataLen, REFERENCE_TIME *pTimeStart,
			  REFERENCE_TIME *pTimeEnd);
    
    STDMETHODIMP GetCurrentMediaType(AM_MEDIA_TYPE *pmt);
    
    STDMETHODIMP SetFormat(AM_MEDIA_TYPE *pmt);
    
    STDMETHODIMP setFormat(int w,int h, int bpp);

protected:

    // we have overridden this menhod to synchronize with user calls of PutFrame() 
    virtual HRESULT DoBufferProcessingLoop(void);    // the loop executed whilst running

    // waits for frames
    bool FrameWaiting();
    
 private:
    
    int m_iImageHeight;	                // The current image height
    int m_iImageWidth;	                // And current image width
    int m_iImageDepth;	                // And current image depth
    int m_iRepeatTime;                  // Time in msec between frames
    const int m_iDefaultRepeatTime;     // Initial m_iRepeatTime
    BYTE m_BallPixel[4];	        // Represents one coloured ball
    int	m_iPixelSize;	                // The pixel size in bytes
    PALETTEENTRY m_Palette[256];	// The optimal palette for the image
    CCritSec m_cSharedState;	        // Lock on m_rtSampleTime and m_Ball
    BOOL m_bZeroMemory;                 // Do we need to clear the buffer
    CRefTime m_rtSampleTime;	        // The time stamp for each sample
    
    IMediaSample *pSample;
    HRESULT hrFillBuffer;
    HANDLE hEvent, hFreeEvent,hFillEvent,hCompleteEvent;
    CCritSec m_cBusy,m_cRepeat;
    bool busy,prevIn;
    int count;

}; // CFrameStream
	

/// @}
