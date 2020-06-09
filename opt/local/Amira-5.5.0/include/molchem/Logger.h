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

/// @addtogroup molchem molchem
/// @{
#ifndef MOLCHEM_LOGGER_H
#define MOLCHEM_LOGGER_H

#include "MolChemWinDLLApi.h"

#ifdef NEWSTYLE_IOSTREAM
#include <iostream>
using std::ostream;
using namespace std;
#else
#include <iostream.h>
#endif

#include <mclib/McDArray.h>
#include <mclib/McHandable.h>
#include <mclib/McHandle.h>
#include <mclib/McString.h>

#ifdef _DEBUG
#define DEBUG_OUTPUT
#endif

namespace molchem {

    class Logger;
    class LogNode;
    class LogStream;

    /** \brief LoggingHandler is a singleton class which contains all loggers.
        
        A Logger automatically registers in the LoggingHandler upon construction and
        deregisters upon destruction.

        The LoggingHandler also allows to assign LogStreams or Levels to a pattern match of
        Loggers.

        Example:
        Logger("amira.amiraMol.molchem.Molecule");
        theLogginHandler->setStream("amira.*",logStreamAmiraMessage,LoggingHandler::INFO);
        theLogginHandler->setStream("amira.amiraMol.molchem.*",logStreamStdout,LoggingHandler::ALL);

    */
    class MOLCHEM_API LoggingHandler {
        friend class Logger;
        friend class LogStream;
    public:
        enum OutputLevel {
            LOG_ALL   =    0,
            LOG_DEBUG = 1001,
            LOG_INFO  = 2001,
            LOG_WARN  = 3001,
            LOG_ERROR = 4001,
            LOG_FATAL = 5001,
            LOG_NONE  = 6001
        };
        /** 
        */
        static LoggingHandler* getLoggingHandler();
        /** 
        */
        void setLevel(const char * pattern, int level );
        /** 
        */
        void setStream(const char* pattern,LogStream*);
        /** 
        */
        void setStream(const char* pattern,LogStream*,int level);
        /** 
        */
        void removeLoggers(const char* pattern);

    private:
        void getMatchInfo(const char* name1, const char* name2,int& depth1,int& depth2,int& matchDepth);
        void addLogger(LogNode* l);
        void removeLogger(Logger* l);
        void removeStream(LogStream* s);
        LoggingHandler();
        static LoggingHandler* instance;
        McDArray<McHandle<LogNode> > loggers;
    };

    /** \brief LogNode is a node in the tree of loggers which is managed by the LoggingHandler.

        A LogNode contains streams and their corresponding levels. This may either be used
        by the subclass Logger to decide what to write and where to write. Or a LogNode can be
        used as a placeholder in the tree to default streams and levels for all loggers
        below that tree level. I.e. the Loggers 'amiraMol.bla' and 'amiraMol.blu' would both
        inherit their streams and levels from a LogNode 'amiraMol'
    */
    class MOLCHEM_API LogNode : public McHandable {
        friend class LoggingHandler;
    public:
        /** 
        */
        const char* getName() { return name;}
        /**
        */
        void removeStream(LogStream* stream);
        /**
        */
        void setLevel(int level);
        /**
        */
        void setStream(LogStream* s);
        /**
        */
        void setStream(LogStream* s,int level);

        bool matchesName(const char* name);

    protected:
        McDArray<McHandle<LogStream> > stream;
        McDArray<int> streamLevel;
        const char* name;
        LogNode(const char* name);
        virtual ~LogNode();
    };   

    /** Logger is a class allowing to easily write logs. 

        A Logger will inherit streams and levels from parent LogNodes. 
        It automatically registers and deregisters in the LoggingHandler.

        A logger should usually be used as a static member of a class, because this allows to
        use the macros (e.g. MCLOGGER_DEBUG). 

        Example:
        class bla {
            static Logger* l
            void doIt();
        }
        Logger* bla::l = new Logger("amiraMol.bla");
        void doIt(); {
            MCLOGGER_DEBUG("doIt called!");
        }
    */
    class MOLCHEM_API Logger : public LogNode {
    public:
        /** 
        */
        Logger(const char* name);
        /** 
        */
        virtual ~Logger();
        /** 
        */
        void debug(const char* txt);
        /** 
        */
        void info(const char* txt);
        /** 
        */
        void warn(const char* txt);
        /** 
        */
        void error(const char* txt);
        /** 
        */
        void fatal(const char* txt);
        /** 
        */
        void write(const char* txt,int level);
    };

    /**
    Formatting:
    #> more indent (open table in html)
    #< less indent (close table in html)
    */
    class MOLCHEM_API LogStream : public McHandable {
    public:
        LogStream();
        /** */
        virtual ~LogStream();
        /** */
        void write(const char* txt);
        /** Returns whether stream reckognizes special formatting strings. */
        bool getFormating() { return formating;}
        /** Sets whether stream reckognizes special formating strings*/
        void setFormating(bool f) {formating = f;}
    protected:
        virtual void writeInternal(const char* txt) = 0;
        bool formating;
    };

    /**
    */
    class MOLCHEM_API LogStreamStream : public LogStream {
    public:
        /** */
        LogStreamStream(ostream* stream);
    private:
        virtual void writeInternal(const char* txt);
        ostream* str;
    };

    /**
    */
    class MOLCHEM_API LogStreamFile : public LogStream {
    public:
        /** */
        LogStreamFile(const char* name);
        /** */
        ~LogStreamFile();
    private:
        virtual void writeInternal(const char* txt);
        FILE* f;
    };

    /** 
        Static log stream, which writes to stdout
    */
    extern MOLCHEM_API LogStreamStream* logStreamStdout;
    /**
        Static log stream, which writes to stream Resouce::message
        which (if build with Amira) is 
        theMessage->stream() (found in <Amira/HxMessage.h>)
    */
    extern MOLCHEM_API LogStreamStream* logStreamMessage;
}

/** Concenience macro to return the loggin-handler instance */
#define theLoggingHandler molchem::LoggingHandler::getLoggingHandler()

#ifdef DEBUG_OUTPUT
    #define MCLOGGER_DEBUG(txt) \
    {McString _x_str; _x_str.stream() << txt;\
    logger->debug(_x_str.getString());}
    #define MCLOGGER_DEBUG2(pat,txt) \
    {McString _x_str; _x_str.printf(pat,txt);\
    logger->debug(_x_str.getString());}
#else
    #define MCLOGGER_DEBUG(txt)
    #define MCLOGGER_DEBUG2(pat,txt)
#endif
#define MCLOGGER_INFO(txt) \
    {McString _x_str; _x_str.stream() << txt;\
    logger->info(_x_str.getString());}
#define MCLOGGER_INFO2(pat,txt) \
    {McString _x_str; _x_str.printf(pat,txt);\
    logger->info(_x_str.getString());}
#define MCLOGGER_ERROR(txt) \
    {McString _x_str; _x_str.stream() << txt;\
    logger->error(_x_str.getString());}
#define MCLOGGER_ERROR2(pat,txt) \
    {McString _x_str; _x_str.printf(pat,txt);\
    logger->error(_x_str.getString());}
#define MCLOGGER_WARN(txt) \
    {McString _x_str; _x_str.stream() << txt;\
    logger->warn(_x_str.getString());}
#define MCLOGGER_WARN2(pat,txt) \
    {McString _x_str; _x_str.printf(pat,txt);\
    logger->warn(_x_str.getString());}
#define MCLOGGER_FATAL(txt) \
    {McString _x_str; _x_str.stream() << txt;\
    logger->fatal(_x_str.getString());}
#define MCLOGGER_FATAL2(pat,txt) \
    {McString _x_str; _x_str.printf(pat,txt);\
    logger->fatal(_x_str.getString());}

#endif


/// @}
