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

/// @addtogroup hxplot hxplot
/// @{
#ifndef PZ_MESSAGE_H
#define PZ_MESSAGE_H

#include <stdio.h>
#include <stdarg.h>
#ifdef NEWSTYLE_IOSTREAM
#include <iostream>
using std::ostream;
#include <streambuf>
using std::streambuf;
#else
#include <iostream.h>
#endif

#include <mclib/McString.h>

#include <hxplot/PzPlotWinDLLApi.h>

class QzMessageWindow;
//class QTextEdit;
class PzPlot;

/** This class is used to display messages in the stand alone amira plot
    console window.
    Other objects may use the global pointer @c theMsg in order to
    display messages in the console window.

    In addition to a C-style printf method also a C++ output stream
    is provided in order to support the << operator. The class also provides
    some static methods which can be used to pop up simple modal dialogs
    (e.g. error, warning, info, file overwrite, question).
*/

class HXPLOT_API PzMessage
{ 
  public:
    /** Constructor. The console window is put in the lower right corner of
        the screen. All messages printed in the console window will be
        logged in the file denoted by @c logfile, unless this parameter is
        null. Logging can be activated by starting Amira with the command
        line option <tt> -log <filename></tt>. */
    PzMessage(PzPlot* plotwin, const char* logfile=NULL);

    /// Clears the content of the message window.
    void clear();
    
    /** C-style printf method. Other objects may use this method in order to
        print arbitrary messages in the console window. If not already
        present, a new line character will be added automatically to every
        message. */
    void printf(const char* format, ...);

    /** Prints an IO error message. The message consists of two lines. The
        first line will be <em> IO error on <filename>:</em>. The second line
        indicates the error reason. This line will be the compiled format
        string (printf syntax).  If no such string is specified <em>
        strerror()</em> is evaluated on both UNIX and Windows. In this way
        common errors like non-existing files or permission mismatches are
        indicated automatically. */
    void ioError(const char* filename, const char* format=0, ...);

    /** Prints a memory allocation error message. If a non-zero argument is
        specified the message is "Error: could not allocate <num> bytes". If
        no argument is specified the message is "Error: could not allocate
        enough memory". */
    void memError(int numBytes);

    /** Prints a message describing the last system error. On UNIX the
        error message is obtained using <em> strerror()</em>. On Windows
        <em> GetLastError()</em> is evaluated. The format string (printf syntax)
        can be used to define a text message which is printed prior to the
        system error message. If no format string is specified only the system
        error message will be printed. */
    void sysError(const char* format=0, ...);

    /** Error dialog. Pops up a modal dialog displaying a user-defined error
        message. Up to three different buttons can be displayed. The return
        value indicates which button has been pressed by the user. If
        @c button0Text is null, Close will be displayed. @c defaultButtonNumber
        (0-2) is the index of the default button. Pressing Return or Enter is
        the same as clicking the default button. @c escapeButtonNumber is the
        index of the escape button. Pressing Escape is the same as clicking
        the escape button. On default, both button numbers are set to -1,
        indicating that pressing the corresponding key has no effect.

        In order to format a message text using C-style printf syntax you may
        use the McString utility class:
        @code
        int btn = PzMessage::error(McString().printf
            ("Error in line %d", lineNumber), "More Info", "Close");
        if (btn==0)
            provideMoreInfo();
        @endcode
    */
    static int error(const char* message, const char* button0Text=0,
        const char* button1Text=0, const char* button2Text=0,
        int defaultButtonNumber=-1, int escapeButtonNumber=-1);

    /// Warning dialog, usage same as error.
    static int warning(const char* message, const char* button0Text=0,
        const char* button1Text=0, const char* button2Text=0,
        int defaultButtonNumber=-1, int escapeButtonNumber=-1);

    /// Question dialog, usage same as error.
    static int question(const char* message, const char* button0Text,
        const char* button1Text, const char* button2Text=0,
        int defaultButtonNumber=-1, int escapeButtonNumber=-1);

    /** Info dialog. In contrast to the error, warning, and question
        dialogs the info dialog always has exactly one button labeled <em>
        Close</em>. No additional strings have to defined and the last argument
        is not required to be zero. */
    static int Info(const char* format, ...);

    /** Ask user whether to overwrite the specified file. A modal dialog will
        be popped up saying that the specified file already exists. The user
        may choose <em> Overwrite</em> or <em> Cancel</em>. If overwrite is chosen
        the method returns 1. Otherwise, it returns 0. It is not checked
        whether the specified file really already exists. To perform such a
        check the utility class McFilename can be used. */
    static int Overwrite(const char* filename);

    /** Returns an output stream connected to the Amira console. The
        output stream can be used to print messages via the C++ output
        operator <<. */
    ostream & stream();

    static PzMessage*& getTheMsg();

    ///
    void raise();

    ///
    void lower();

    /// Parse method associated with @c theMsg command.
    int parse(Tcl_Interp* t, int argc, char** argv);

    /** This is an extention to the original HxMessage class in order to
        be able to set and get the window geometry and position in a
        stand-alone application */
    void setSize(int width, int height);

    void getSize(int &width, int &height);

    void setPosition(int x, int y);

    void getPosition(int &x, int &y);

  protected:
    QzMessageWindow* text;
    // QTextEdit* text;

    void outputString(const char* string, int skipInput);
  
  private:
    // Local class representing a streambuf that prints to the Amira console.
    class msgstreambuf : public streambuf {
      protected:
        virtual int overflow(int c = EOF);
        virtual int underflow();
        virtual int sync();
      private:
        McString strm;
        int writeBlock(char *c,int n);
    };

    msgstreambuf theMsgStreamBuf;
    ostream* theMsgStream;
    FILE* log;
    PzPlot* thePlot;

    friend class msgstreambuf;
};

#define theAmplMsg (PzMessage::getTheMsg()) 

#endif

/// @}
