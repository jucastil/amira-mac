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

/// @addtogroup hxcore hxcore
/// @{
#ifndef QX_NETRESOURCE_H
#define QX_NETRESOURCE_H

#include <QObject>
#include <QUrl>
#include <QFile>
#include <QDir>
#include <QHttp>
#include <QFtp>

#include <mclib/McDArray.h>
#include <mclib/McString.h>

class QxNetResource;

typedef void QxNetResourceFinishCB(QxNetResource* res, int state,
                                   void* userdata);

typedef void QxNetResourceProgressCB(QxNetResource* res, int bytesDone,
                                     int bytesTotal, void* userdata);

typedef void QxNetResourceStateCB(QxNetResource* res, char* state,
                                  void* userdata);

/* Utility class providing methods for accessing resources from the net.
    Resources from the net means: files residing on a ftp resp. http server.
*/
class QxNetResource : public QObject {

    Q_OBJECT

  public:

    QxNetResource(int idx = 0);

    ~QxNetResource();

    int loadData(const QUrl & url);

    void setLocalPath(const char* path);

    QUrl getRemoteUrl() { return theRemoteOp; }

    QUrl getLocalPath() { return theLocalOp; }

    const char* getErrorMsg() { return errorMsg.getString(); }

    const char* getStateMsg() { return stateMsg.getString(); }

    void getProgress(int& bytesDone, int& bytesTotal);

    // sets the callback to be invoked when remote access is finished
    void setFinishCallback(QxNetResourceFinishCB* clientFunc, void* clientData);

    // unsets the callback above
    void unsetFinishCallback() { finishCallback = NULL; }

    // sets the callback to handle the progress while data is loaded
    void setProgressCallback(QxNetResourceProgressCB* clientFunc,
                             void* clientData);

    // unsets the callback above
    void unsetProgressCallback() { progressCallback = NULL; }

    // sets the callback to handle state changes (e.g. connected, loading, ...
    void setStateCallback(QxNetResourceStateCB* clientFunc, void* clientData);

    // unsets the callback above
    void unsetStateCallback() { stateCallback = NULL; }

    // interrupts the remote data access
    void interrupt();

    // returns index number given at construction
    int getIndex() { return myIdx; }

  protected:

    int transferStarted;

  private slots:

    void dataReadProgress(int done, int total);
    void httpResponseHeaderReceived(const QHttpResponseHeader &resp);

    void ftpCommandFinished(int, bool);
    void dataTransferProgress(qint64 done, qint64 total);
    void done(bool error);

  private:

    QUrl theRemoteOp;
    QUrl theLocalOp;

    QFtp  m_ftp;
    QHttp m_http;
    QFile m_localFile;

    McString errorMsg;
    McString stateMsg;

    int myIdx;
    int numReadBytes;
    int numTotalBytes;
    
    QxNetResourceFinishCB* finishCallback;
    void*                  finishUserdata;

    QxNetResourceProgressCB* progressCallback;
    void*                    progressUserdata;

    QxNetResourceStateCB* stateCallback;
    void*                 stateUserdata;

}; // QxNetResource

#endif

/// @}
