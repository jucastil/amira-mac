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
#ifndef HX_PERFLOGGING_H
#define HX_PERFLOGGING_H

#define HX_PERF_LOGGING_COMPRESS

#include "hxcore/HxAmiraWinDLLApi.h"
#include "hxcore/HxObject.h"
#include "hxcore/HxResource.h"
#include "hxfield/HxLattice3.h"
#include "mclib/McDArray.h"

#ifdef HX_PERF_LOGGING_COMPRESS
#include <zlib/zlib.h>
#endif

#include <time.h>

#include <QFile>
#include <QNetworkReply>
#include <QObject>
#include <QString>
#include <QStringList>

// Somewhere "exception" is defined. This leads to problems with boost, 
// so undef it now.
#undef exception
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

// # comment
// ac: activate
// ap: application
// co: compute
// ca: crash
// cr: create object
// ce: create editor
// dc: data create
// di: data init
// dr: data crop
// ec: exception
// ex: exit
// in: init
// fr: file read
// fw: file write
// gd: graphics driver version
// gl: graphics open gl version
// gr: graphics renderer
// gv: graphics board vendor
// os: operating system
// nc: number of cores
// pe: preferences
// pr: printf
// ra: ram
// ts: timestamp
// up: update
// ve: version

class SendPerfMeasureData : public QObject
{
    Q_OBJECT
public:
    SendPerfMeasureData();
    void send(const QStringList &filenames);
protected slots:
    void error(QNetworkReply::NetworkError errorCode);
    void finished(QNetworkReply *reply);
protected:
    void send(const QString &filename);

    QStringList mFilenames;
    QFile mFile;
    QNetworkAccessManager mNetworkManager;
    QNetworkRequest mRequest;
    QNetworkReply* mReply;

    bool mErrorOccured;
};

// 
class HXCORE_API HxPerfLogging
{
protected:
    HxPerfLogging();
    ~HxPerfLogging();
public:
    enum LogType {Activate, Application, Compute, Crash, CreateObject, CreateEditor, DataCreate,
        DataCrop, DataInit, Exception, Exit, Init, FileRead, FileWrite, GraphicsBoardDriverVersion,
        GraphicsBoardOpenGLVersion, GraphicsRenderer, GraphicsBoardVendor,
        OperatingSystem, NumberOfCores, Preferences, Printf, RAM, Timestamp, Update, Version};

    void init();
    void startLogging();
    void deinit();
    static inline HxPerfLogging* getThePerfLogging();
    inline void startMeasure(const HxObject* obj, LogType logType);
    inline void stopAndLogMeasure(const HxObject* obj, LogType logType);
    inline void logDims(const HxLattice3* obj, LogType logType, const mculong dims[3],
        McPrimType pType, int dataVars);
    inline void logData(QString const& str, HxPerfLogging::LogType logType);
    inline void startIOMeasure(const HxObject* obj, LogType logType);
    inline void stopAndLogIO(const char *label, const char *funcName, LogType logType);
    inline void logCreation(const HxBase *base, LogType logType);
    inline void logActivation(HxSubApplicationInfo *info, LogType logType);
    inline void printf(const char *format, ...);
    inline void logCrash(const char *text);
    inline void logException(const char *text);
    QStringList collectLogFiles();
    void send(bool autoSend=false, bool forceSend=false);
    void setEnabled(bool enabled);
    QString const& getPathName() const;
protected:
    void logLine(const char *format, ...);
    void printSystemInformation();
    inline boost::posix_time::ptime getTimeStamp();

    McDArray<boost::posix_time::ptime> mComputeStartTimes;
    McDArray<boost::posix_time::ptime> mIOStartTimes;
    bool mEnabled;
#ifdef HX_PERF_LOGGING_COMPRESS
    gzFile file;
#else
    FILE *file;
#endif
    QString mFileName;
    QString mPathName;
    QString mFileExt;
    static const char cTypeIDs[26][3];
    boost::posix_time::ptime mLastFlushTime;
    time_t mSendInterval;
    const boost::posix_time::time_duration cFlushPeriod;
    const qint64 cMinSendSize;
};

HxPerfLogging* HxPerfLogging::getThePerfLogging()
{
    static HxPerfLogging instance; 
    return &instance;
}

boost::posix_time::ptime HxPerfLogging::getTimeStamp() 
{
    return boost::posix_time::microsec_clock::local_time();
}

void HxPerfLogging::startMeasure(const HxObject* obj, LogType logType)
{
    if (!mEnabled)
        return;
    mComputeStartTimes.push(getTimeStamp());
}

void HxPerfLogging::startIOMeasure(const HxObject* obj, LogType logType)
{
    if (!mEnabled)
        return;
    mIOStartTimes.push(getTimeStamp());
}

void HxPerfLogging::stopAndLogMeasure(const HxObject* obj, LogType logType)
{
    if (!mEnabled)
        return;
    boost::posix_time::ptime startTime;
    long delta;
    boost::posix_time::ptime stopTime = getTimeStamp();
    mComputeStartTimes.pop(startTime);
    delta = (stopTime-startTime).total_milliseconds();
    if (logType==Update && delta == 0) // log only time consuming updates
        return;
    int depth = mComputeStartTimes.size();
    const char *objName;
    if (obj)
        objName = obj->getTypeId()->getName();
    else
        objName = "<unknown>";
    logLine("%s: %i, %s, %li", cTypeIDs[logType], depth, objName, delta);
}

void HxPerfLogging::logDims(const HxLattice3* obj, LogType logType, const mculong dims[3],
                            McPrimType pType, int dataVars)
{
    if (!mEnabled)
        return;
    const char *objName;
    if (obj)
        objName = obj->getTypeId()->getName();
    else
        objName = "<unknown>";
    logLine("%s: %s, %s, %d, %lu, %lu, %lu", cTypeIDs[logType], objName, pType.getName(), dataVars, dims[0], dims[1], dims[2]);
}

void HxPerfLogging::logData(QString const& str, HxPerfLogging::LogType logType)
{
    if (!mEnabled)
        return;

    logLine("%s, %s", cTypeIDs[logType], qPrintable(str));
}

void HxPerfLogging::stopAndLogIO(const char *label, const char *funcName, LogType logType)
{
    if (!mEnabled)
        return;
    boost::posix_time::ptime startTime;
    long delta;
    boost::posix_time::ptime stopTime = getTimeStamp();
    mIOStartTimes.pop(startTime);
    delta = (stopTime-startTime).total_milliseconds();
    int depth = mIOStartTimes.size();
    if (!label)
        label = "";
    if (!funcName)
        funcName = "";
    logLine("%s: %d, %s, %s, %li", cTypeIDs[logType], depth, label, funcName, delta);
}

void HxPerfLogging::logCreation(const HxBase *base, LogType logType) 
{
    if (!mEnabled)
        return;
    const char *objName;
    if (base)
        objName = base->getTypeId()->getName();
    else
        objName = "<unknown>";
    logLine("%s: %s", cTypeIDs[logType], objName);
}

void HxPerfLogging::logActivation(HxSubApplicationInfo *info, LogType logType)
{
    if (!mEnabled)
        return;
    const char *str;
    if (info && info->className)
        str = info->className;
    else if (info && info->name)
        str = info->name;
    else
        str = "<unknown subapp>";
    logLine("%s: %s", cTypeIDs[logType], str);
}

void HxPerfLogging::printf(const char *format, ...)
{
    char str[1024];
    va_list args;
    va_start(args, format);
    vsprintf(str, format, args);
    va_end(args);
    logLine("%s: %s", cTypeIDs[Printf], str);
}

void HxPerfLogging::logCrash(const char *text)
{
    if (!mEnabled)
        return;
    logLine("%s: %s", cTypeIDs[Crash], text);
}

void HxPerfLogging::logException(const char *text)
{
    if (!mEnabled)
        return;
    logLine("%s: %s", cTypeIDs[Exception], text);
}

#endif //HX_PERFLOGGING_H

/// @}
