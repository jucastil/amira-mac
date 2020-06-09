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
#ifndef HX_PORT_FILENAME_H
#define HX_PORT_FILENAME_H

#include <hxcore/HxPort.h>
#include <hxcore/HxModule.h>

class QxLineEdit;
class QPushButton;
class QxFilenameListDialog;

/** This port can be used to define a filename. In addition to a
    simple text field the port provides a button which activates
    the file browser.

    There are two possible modes of this module, one useful for saving a
    file (@c AnyFile) and one for loading a file (@c ExistingFile), that 
    correspond to the HxFileDialog's modes @c AnyFile and @c LoadFile.

    See the  @htmlonly <a href= ../usersguide/HxPortFilename.html> usersguide </A> @endhtmlonly 
    for a detailed view of the port's GUI.
*/
class HXCORE_API HxPortFilename : public HxPort {

  MC_ABSTRACT_HEADER(HxPortFilename);

  public:
    /// Modes for the file dialog.
    enum Mode {
        /// Useful for saving a file.
        AnyFile=0,
        /// Useful for loading a file.
        ExistingFile=1,
        /// Useful for selecting multiple files
        MultiFile=2,
        /// Load a directory
        LoadDirectory=3,
        /// Save a directory
        SaveDirectory=4,
        /// after last
        MODE_END=5
    };

    /// Constructor for objects.
    HxPortFilename(HxObject* object, const char* name, Mode=AnyFile);

    /// Constructor for editors.
    HxPortFilename(HxEditor* editor, const char* name, Mode=AnyFile);

    /// Destructor.
    ~HxPortFilename();

    /// Only useful in mode MultiFile 
    int getFileCount () const { return names.size (); }

    /// Returns the filename.
    const char* getFilename (int i=0) const { return (i<names.size())?names[i]:""; }

    /// Returns the filetype.
    const char* getFileType (int i=0) const { return (i<formats.size())?formats[i]:"unknown"; }

    /// Sets a new filename, don't use in mode MultiFile.
    void setFilename(const char* name, const char* format = 0);

    /// Use in mode MultiFile.
    void setFilenames (int n, const char* names[], const char* formats[] = 0);

    /// Synonym for getFilename().
    const char* getValue() const { return getFilename(); }

    /// Synonym for setFilename().
    void setValue(const char* name) { setFilename(name); }

    /// Sets the file browser mode (AnyFile or ExistingFile).
    void setMode(Mode mode);

    /// Returns the file browser mode.
    Mode getMode() const { return mode; }

    /** File types displayed if the browser is in mode @c AnyFile.
	See HxFileDialog::HxFileDialog::registerFileType for detailed
	description how to register file types. */
    void registerFileType(const char* name=0, const char* suffix=0, int multiSave=0);

    /** Clear all registered file types. */
    void clearFileTypes();

    /** Pops up file dialog forcing the user to choose a file. Mainly
        useful for script programmers. The method is blocking. It waits
        until the dialog was closed. Returns 0 if dialog was cancelled. */
    int exec();

    /// Parse method.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Save state method.
    virtual void saveState(FILE* fp);

    /// Returns current state in ascii string.
    virtual void getState(McString& state);

    /// Restores current state from ascii string.
    virtual int setState(const McString& state);

    McString findFileExt(McString const &fileType);

  protected:
    void internalSetFilename(const char* name, const char* format);

    QxGuardedPtr<QxLineEdit> lineEdit;
    QxGuardedPtr<QPushButton> button;
    QxFilenameListDialog* dialog;

    struct FileType {
	      McString name;
	      McString ext;
        int multiSave;
    };

    Mode mode;
    McString fn;
    McString ft;
    McDArray<FileType> fileTypes;

    McDArray<const char*> names;
    McDArray<const char*> formats;

    virtual void guiCallback();
    virtual void createWidget(QWidget* parent);

    virtual int cmd_setFilenames(Tcl_Interp* t, int argc, char **argv);
    virtual int cmd_setFilename(Tcl_Interp* t, int argc, char **argv);
};

#endif

/// @}
