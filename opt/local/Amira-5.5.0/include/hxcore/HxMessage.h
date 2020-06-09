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
#ifndef HX_MESSAGE_H
#define HX_MESSAGE_H

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

#include <tcl.h>
#include <hxcore/HxAmiraWinDLLApi.h>

class QSize;
class QPoint;
class QWidget;
class QxMessageWindow;

#ifndef NDEBUG
    #define DBG_PRINTF(args) theMsg->dbgPrintf args
#else
    #define DBG_PRINTF(args)
#endif

/** This class is used to display messages in Amira's console window.
    Other objects may use the global pointer @c theMsg in order to
    display messages in the console window.

    In addition to a C-style printf method also a C++ output stream
    is provided in order to support the << operator. The class also provides
    some static methods which can be used to pop up simple modal dialogs
    (e.g. error, warning, info, file overwrite, question).
*/

class HXCORE_API HxMessage
{
  public:
    /** Constructor. The console window is put in the lower right corner of
        the screen. All messages printed in the console window will be
        logged in the file denoted by @c logfile, unless this parameter is
        null. Logging can be activated by starting Amira with the command
        line option <tt> -log <filename></tt>. */
    HxMessage(QWidget* parent, const char* logfile=0);

    /// Clears the content of the message window.
    void clear();

    /// Prevents from displaying message in the console window.
    void setSilentMode(bool silent)
    { m_isSilentMode = silent ; }

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
    void memError(size_t numBytes);

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
        use the McString ultility class:
        @code
        int btn = HxMessage::error(McString().printf
            ("Error in line %d", lineNumber), "More Info", "Close");
        if (btn==0)
            provideMoreInfo();
        @endcode
    */
    static int error(const char* message, const char* button0Text=0,
        const char* button1Text=0, const char* button2Text=0,
        int defaultButtonNumber=-1, int escapeButtonNumber=-1);

    /// Warning dialog, usage same as error().
    static int warning(const char* message, const char* button0Text=0,
        const char* button1Text=0, const char* button2Text=0,
        int defaultButtonNumber=-1, int escapeButtonNumber=-1);

    /// Question dialog, usage same as error().
    static int question(const char* message, const char* button0Text,
        const char* button1Text, const char* button2Text=0,
        int defaultButtonNumber=-1, int escapeButtonNumber=-1);

    /** Info dialog. In contrast to the error, warning, and question
        dialogs the info dialog always has exactly one button labeled <em>
        Close</em>. No additional strings have to defined. */
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

    /// Wraps the message window's resize() method.
    void resize(const QSize& s);

    /// Wraps the message window's move() method.
    void move(const QPoint& p);

    /// Wraps the message window's size() method.
    QSize size() const;

    /// Wraps the message window's pos() method.
    QPoint pos() const;

    /// Wraps the message window's raise() method.
    void raise();

    /// Wraps the message window's lower() method.
    void lower();

    /// Wraps the message window's setVisible(bool) method.
    void setVisible(bool visible);

    /// Wraps the message window's show() method.
    void show();

    /// Wraps the message window's hide() method.
    void hide();

    /// Wraps the message window's isVisible() method.
    bool isVisible() const;

    void dbgPrintf(const char* format, ...);

    void setDebugLogging(bool onOff);

    /** Pops up the help browser. If a command is specified it is
        checked if help is available for this command. If so the, help
        browser is opened with the appropriate page. Otherwise, it is
        opened with the online help main page. */
    void help(const char* cmd=0);

    /// Parse method associated with @c theMsg command.
    int parse(Tcl_Interp* t, int argc, char** argv);

    /// Returns the console widget associated with this object.
    QWidget* getWidget() const { return (QWidget*) text; }

    /// Returns pointer to global message object (theMsg).
    static HxMessage*& getTheMsg();

    /// Allows you to override the caption of message windows
    static void setWindowName(const char* win);

    /// Returns the current caption of message windows
    static const char* getWindowName();

    static void setMessageBoxParent(QWidget* parent);

    static QWidget* getMessageBoxParent();

    /* Position in global pixel coordinates at which a HxMessage opens.
       This method is useful for multi-monitor setups, especially if
       "horizontal-span mode" is used. In this case dialogs are often
       shown half-and-half on two monitors. By adding one or more center
       default positions this can be avoided. */
    static void addWindowPosCenterDefault(int x, int y);

    // Moves the widget to the the nearest default center position
    static void moveToWindowPosCenterDefault(QWidget* widget);

  protected:
    void msghelp();

    static int openMessageBox(int severity, const char* message,
        const char* button0Text, const char* button1Text, const char* button2Text,
        int defaultButtonNumber, int escapeButtonNumber);


    QxMessageWindow* text;
    void outputString(const char* string);
    static McString mWindowName;
    bool m_isSilentMode ;

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
};

#define theMsg (HxMessage::getTheMsg())

#endif

/// @}
