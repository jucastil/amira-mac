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
#ifndef ARGPARSE
#define ARGPARSE

#include <mclib/McDArray.h>
#include <hxcore/HxAmiraWinDLLApi.h>

/** A simple parser for command line options and arguments.
    This class is designed to make command line parsing easier.
    A command line usually consists of single options, options with
    additional arguments, and arguments to the command itself. Options
    may be specified in two ways, via a single like @c -v or via a full
    string like @c --verbose.

    To use this class you first have to define the possible options
    and arguments like in the following example:

    @code
    ArgParse::Opt opts[] = {
        ArgParse::Opt('v', "-verbose", "be noisy", &isVerbose ),
        ArgParse::Opt('f', "-outfile", "filename", "redirect output", &fn ),
        ArgParse::Opt("infile", "input file", &fout, ArgParse::Required )
    };
    @endcode

    The actual parser class is initialized with this option list:

    @code
    ArgParse parser(argc, argv, 3, opts, "what the command is used for");
    @endcode

    To parse the command line, call the @c parse() method of the parser.
    After the commad line has been successfully parsed, the corresponding
    parameters are stored at the locations specified with a particular
    option. Use the @c found() method to enquire if an option was
    encountered alltogether at the command line.

    In case of an parse error, the @c parse() method will return
    @c ArgParse::ERROR. In this case @c errorMsg() will return a description
    of the error. You can also use @c error() to find out, if an error
    has occured.

    Instaed of using @c parse(), arguments and options may also be
    processed step by step using @c next(). */
class HXCORE_API ArgParse {
  public:

    /// return type of @c parse() and @c next()
    enum Result { DONE=-1, PARSE_ERROR=-2 };

    /// specifies if an option or argument is required or not
    enum Type { OPTIONAL_ARG=0, REQUIRED_ARG=1 };

    /// specifies how a particular option or argument looks like
    class HXCORE_API Opt {

      public:
        ///
        Opt() {}
        /// simple command option, no result is written
        Opt(char c, char* opt, char* help, Type r=OPTIONAL_ARG);

        /// simple command option
        Opt(char c, char* opt, char* help, int* val, Type r=OPTIONAL_ARG);

        /// command option with integer argument
        Opt(char c, char* opt, char* arg, char* help, int* val,
            Type r=OPTIONAL_ARG);

        /// command option with float argument
        Opt(char c, char* opt, char* arg, char* help, float* val,
            Type r=OPTIONAL_ARG);

        /// command option with string argument
        Opt(char c, char* opt, char* arg, char* help, char** val,
            Type r=OPTIONAL_ARG);

        /// command option with multiple float arguments
        Opt(char c, char* opt, char* arg, char* help, McDArray<float>* val,
            int nArgs, Type r=OPTIONAL_ARG);
        /// command option with multiple float arguments
        Opt(char c, char* opt, char* arg, char* help, McDArray<int>* val,
            int nArgs, Type r=OPTIONAL_ARG);

        /// command argument of type string, use @c getVal()
        Opt(char* arg, char* help, Type r=OPTIONAL_ARG);

        /// command argument of type string
        Opt(char* arg, char* help, char** val, Type r=OPTIONAL_ARG);

        /// multiple command arguments of type string
        Opt(char* arg, char* help, McDArray<char*>* val, Type r=OPTIONAL_ARG);

        /// indicates if this option was encountered during parse
        int wasFound() { return found; }

        /// if no result is written, returns pointer to argument
        char* getArg() { return (resType==EXPLICIT) ? found=0,res.argPtr:0; }

      protected:
        char        letter;
        char*       optionName;
        char*       argumentName;
        char*       helpText;
        Type        isRequired;
        int         found;
        int nArgs;
        enum ResultType { INT, FLOAT, STRING, MULTSTR, MULTIFLOAT, MULTIINT,
                          EXPLICIT } resType;

        union {
            int*        intVal;
            float*      floatVal;
            char**      strVal;
            McDArray<char*>* strList;
            McDArray<int>* intList;
            McDArray<float>* floatList;
            char*       argPtr;
        } res;

        friend class ArgParse;
    };

    /// instantiates a parser with given option list
    ArgParse(int argc, char* argv[], int nOpt, Opt opts[], char* help=0);

    /// destructor
    ~ArgParse();

    /// parses the whole command line
    int         parse();

    /// returns number of next option found or DONE or ERROR
    int         next();

    /// returns a usage string for the command
    char*       usage();

    /// returns true if a parse error has been detected
    int         error() { return err; }

    /// in case of an error, returns an error message
    char*       errorMsg() { return text; }

  protected:
    int         n;
    int         argc;
    int         nOpt;
    char**      argv;
    Opt         *opts;
    int         err;
    char*       text;
    int         textLen;
    int         textSize;
    char*       cmdHelp;
    int         scanOptions;

    void set(char *str);
    void append(char* str);
};

#endif

/// @}
