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

/// @addtogroup vsvolren vsvolren
/// @{
#ifndef _VSLOG_H_
#define _VSLOG_H_

#include "VsVolrenAPI.h"

#include <mclib/McString.h>

#ifndef VSLOG_MODULE
#define VSLOG_MODULE "UNDEFINED_MODULE"
#endif

// Abstract interface for logging within the volren library

class VSVOLREN_API VsLog {

public:
    enum LogLevel
    {
        LOG_LOG = 0,
        LOG_FATAL,
        LOG_WARNING,
        LOG_NOTICE,
        LOG_INFO,
        LOG_DEBUG
    };

    void setLogLevel(const char * module, int level);

    void doLog(const char * format, ...);
    void setup(const char * module, int level);
    
    static VsLog & theLog();
    VsLog();

private:
    McString mTmpModule;
    int      mTmpLevel;

    /** The currently active log level, only messages with 
        level <= \c mLogLevel will be posted */
    int      mLogLevel; 
};

#ifdef NDEBUG

  #define VS_FLOG(f) do {} while(0);
  #define VS_FFATAL(f) do {} while(0);
  #define VS_FWARNING(f) do {} while(0);
  #define VS_FNOTICE(f) do {} while(0);
  #define VS_FINFO(f) do {} while(0);
  #define VS_FDEBUG(f) do {} while(0);

#else

  #define VS_FLOG(f) do { \
    VsLog::theLog().setup(VSLOG_MODULE, VsLog::LOG_LOG); \
    VsLog::theLog().doLog f; \
  } while(0);

  #define VS_FFATAL(f) do { \
    VsLog::theLog().setup(VSLOG_MODULE, VsLog::LOG_WFATAL); \
    VsLog::theLog().doLog f; \
  } while(0);

  #define VS_FWARNING(f) do { \
    VsLog::theLog().setup(VSLOG_MODULE, VsLog::LOG_WARNING); \
    VsLog::theLog().doLog f; \
  } while(0);

  #define VS_FNOTICE(f) do { \
    VsLog::theLog().setup(VSLOG_MODULE, VsLog::LOG_NOTICE); \
    VsLog::theLog().doLog f; \
  } while(0);

  #define VS_FINFO(f) do { \
    VsLog::theLog().setup(VSLOG_MODULE, VsLog::LOG_INFO); \
    VsLog::theLog().doLog f; \
  } while(0);

  #define VS_FDEBUG(f) do { \
    VsLog::theLog().setup(VSLOG_MODULE, VsLog::LOG_DEBUG); \
    VsLog::theLog().doLog f; \
  } while(0);

#endif // NDEBUG

#endif // _VSLOG_H_


/// @}
