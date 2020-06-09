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
#ifndef DS_IMAGECAPTURER_H
#define DS_IMAGECAPTURER_H

typedef _TCHAR *PTCHAR;

#include <dxsdk/streams.h>

#include <mmreg.h>
#include <msacm.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <commdlg.h>

#include <hxcore/HxPortGeneric.h>

#include "streamer/ifstream.h"
#include "HxMovieMakerWinDLLApi.h"
#include "ImageStreamer.h"

#include <mclib/McFilename.h>

#define ABS(x) (((x) > 0) ? (x) : -(x))

class QWidget;
class HxPortMultiMenu;

/**
   Class that encapsulates DirectShow image streaming, used to author video files frame-by-frame.
   This is the Amira-tuned version 
 */

class HXMOVIEMAKER_API DSImageStreamer : public ImageStreamer {
 public:

  // <host> : can be null, if no preview wanted (mostly the case)
  // <menu> : the Amira port containing the video compressors
  DSImageStreamer(QWidget* host,HxPortGenericComboBox* menu);

  virtual ~DSImageStreamer();

  // deals with preview
  BOOL BuildGraph();
  BOOL StartStream();
  BOOL StopStream();
  BOOL PauseStream();

  // builds the DShow graph that writes in <filename>, eventually preallocated
  bool openStream(const char * filename, int preAllocMB=-1);
  // starts the graph
  bool startStream();
  // stops the graph
  bool stopStream();

  // sends one frame
  bool putFrame(const QImage& image);
  // Send one frame
  bool putFrame( int inSize[3], unsigned char * inData );

  // sends one frame using real time - DOESN'T WORK FOR AVI !
  bool putFrameRealTime(void* pD,long lD);

  bool hasFixedFrameRates(){return false;};
  void getFixedFrameRatesCodes(int& ncodes, char**& codes){
          ncodes = 0;
          codes = 0;
        };

  bool setFrameRate(int fps){ mFrameDelay = 1000.0/fps;return true;};
  bool setFixedFrameRate(int code){return false;};

  // get/set the streamer video format
  bool getFormat(int& w,int &h, int& bpp );
  bool setFormat(int w,int h, int bpp);


  // the same, works directly with the more detailed DirectShow format
  // set is not implemented yet
  bool getDShowFormat(AM_MEDIA_TYPE* pmt);
  bool setDShowFormat(AM_MEDIA_TYPE* pmt);

  // ready to stream ?
  bool canStartStream(){return canC;};
  
  // everythig's OK with the streaming capabilities ?
  bool canStream(){return capfOK;};


  // sets the currently used compressor
  bool SetVideoCompressor(int format,bool& canQuality, double& defQuality);
  
  // sets the compression quality on thye current compressor, if supported
  bool setQuality(double cq);

  bool canQuality(){return mCanQ;};

  double currentQuality(){return mCurrQ;}; 

  // Ask for codec property page
  bool hasPropertiesDialog();
  // Show codec property page
  void showCodecProperties();

 protected:
  
  // automatically called by constructor
  void initialize();

  // automatically called by destructor
  void terminate();
  
  void NukeDownstream(IBaseFilter *pf);
  BOOL InitCapFilters();
  BOOL MakeBuilder();
  BOOL MakeGraph();
  void AddVideoCompressors();
  
  void TearDownGraph();
  void FreeCapFilters();

     
struct _capstuff {
    ICaptureGraphBuilder2 *pBuilder;
    IVideoWindow *pVW;
    IMediaEventEx *pME;
    IAMDroppedFrames *pDF;
    IAMVideoCompression *pVC;
    IAMVfwCaptureDialogs *pDlg;
    IAMStreamConfig *pASC;      // for audio cap
    IAMStreamConfig *pVSC;      // for video cap
    IBaseFilter *pRender;
 
    IBaseFilter *pStream,*pVCap, *pACap, *pFileSrc,*pVComp;
        IFrameStreamer * pStreamer;
    IGraphBuilder *pFg;
    IFileSinkFilter *pSink;
    IConfigAviMux *pConfigAviMux;
    IConfigInterleaving *pConfigAviInter;
    IMediaSeeking *pMS;

    TCHAR szCaptureFile[_MAX_PATH];
    WORD wCapFileSize;  // size in Meg

    int  iMasterStream;
    BOOL fCaptureGraphBuilt;
    BOOL fPreviewGraphBuilt;
    BOOL fCapturing;
    BOOL fPreviewing;
    BOOL fCapAudio;
    BOOL fCapCC;
    BOOL fCCAvail;
    BOOL fCapAudioIsRelevant;
    bool fDeviceMenuPopulated;
    IMoniker *rgpmCompressorMenu[30];
    IMoniker *pmCompressor;
    int  iCompressor;
    double FrameRate;
    BOOL fWantPreview;
    long lCapStartTime;
    long lCapStopTime;
    WCHAR wachFriendlyName[120];
    WCHAR wFileName[220];
    BOOL fUseTimeLimit;
    BOOL fUseFrameRate;
    DWORD dwTimeLimit;
    int iFormatDialogPos;
    int iSourceDialogPos;
    int iDisplayDialogPos;
    int iVCapDialogPos;
    int iVCrossbarDialogPos;
    int iTVTunerDialogPos;
    int iACapDialogPos;
    int iACrossbarDialogPos;
    int iTVAudioDialogPos;
    int iVCapCapturePinDialogPos;
    int iVCapPreviewPinDialogPos;
    int iACapCapturePinDialogPos;
    long lDroppedBase;
    long lNotBase;
    BOOL fPreviewFaked;
  
    int iVideoInputMenuPos;
    LONG NumberOfVideoInputs;
   
    int iNumCompressors;  
   
} gcap;
HWND ghwndApp;


    QWidget * mHost;
    bool canC,capfOK,mCanQ;
    double mCurrQ;
    long mFrameDelay;
    CRefTime m_Time;
        DWORD m_sTime;
    HxPortGenericComboBox *mCompMenu;
};

#endif // DS_IMAGECAPTURER_H

/// @}
