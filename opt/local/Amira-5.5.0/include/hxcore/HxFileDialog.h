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
#ifndef HX_FILEDIALOG_H
#define HX_FILEDIALOG_H

#include <mclib/McDArray.h>
#include <mclib/McString.h>
#include <mclib/McFilename.h>
#include <mclib/McHandle.h>
#include <mclib/McHandable.h>

#include <hxcore/HxFileFormat.h>
#include <hxcore/HxAmiraWinDLLApi.h>

class QxFileDialog;
class QStringList;
class HxFileFormat;
struct HxFileDialogPrivate;

/** The Amira file browser. The file browser can be used to select a single
    file or multiple files for loading. In addition, there is a save mode
    allowing to select the name of the file to be saved as well as its file
    type/format. Instead of creating your instance of the file browser you
    may use the global instance pointed to by theFileDialog. This
    saves memory and allows the user to select directories previously being
    entered from the history list. 
    
    The file browser always returns absolute path names. Directories will
    be separated by a single slash '/' on both UNIX and Windows.
    See the  @htmlonly <a href= ../usersguide/HxFilDialog.html> usersguide </A> @endhtmlonly 
    for a detailed view of the dialog's GUI.
    */
    
class HXCORE_API HxFileDialog 
{
  public:
    /// Modes in which the file dialog can run.
    enum Usage {
	/// Load a single file
	LoadFile,
	/// Load multiple files
	LoadFileList,
	/// Select single file for saving.
	SaveFile,
	/// Same as SaveFile but Ok-button is labeled "Ok" instead of "Save"
	AnyFile,
    // Load a directory
    LoadDirectory,
    // Save a directory
    SaveDirectory,
  /// Save a network (same as SaveFile except that the selected script file format is saved).
  SaveNetwork
    };

    /// Constructor.
    HxFileDialog();

    /// Destructor.
    ~HxFileDialog();
    
    /// Sets current path, may include a filename part.
    void setPath(const char* path);

    /// Configures file dialog for loading or saving, sets title to "Amira".
    void setDialogUsage(Usage usage);

    /// Returns the dialog usage.
    Usage getDialogUsage() {return usage;}

    /// Sets the window title to user-defined string.
    void setTitle(const char* title);

    /** Returns the number of selected Directory. This will be always one. */
    int getDirectoryCount(void) {return 1;}

    /** Returns absolute path name of the directory. */
    const char* getDirectoryName();

    /** Returns the number of selected files. This will be one unless usage
        has been set to <tt>Usage::LoadFileList</tt> and multiple files have been
        selected. In order to select multiple files, click the first one
        and shift-click the last one. Individual files may also be toggled
        by ctrl-clicking them. */
    int getFileCount(void);

    /** Returns absolute path name of i-th file. In order to load multiple
        files first get the number of files using getFileCount. Then
        access each file name using this method. */
    const char* getFileName(int i=0);

    /** Returns format descriptor of i-th file, or 0 if format is unknown.
        This method can be used to query the format of a file if usage has
        been set to <tt>Usage::LoadFile</tt> or <tt>Usage::LoadFileList</tt>. The
        file browser tries to detect the format of a file automatically and
        returns a pointer to a corresponding HxFileFormat structure.
        All formats registered in the Amira .rc-files will be considered.
        Note, that the user can override the format of any file by choosing
        the <em> Format</em> item from the file browser's popup menu. */
    HxFileFormat* getFileFormat(int i=0);

    /** Register save format option. If usage has been set to
        <tt>Usage::SaveFile</tt> or <tt>Usage::AnyFile</tt> an additional combo
        box will be displayed in the lower part of the file dialog. This
        box allows the user to select different file types/formats. Before
        adding new file types the method first should be called without any
        argument. This causes all previously registered file types to be
        deleted.

        Suffix should indicate the default extension for the file type, for
        example <tt> "tif"</tt> in case of the TIFF-format. When selecting a
        new file type the extension of the current file name displayed in
        the file browser's file name field will be updated automatically.
        Finally, if @c multiSave is set hashmark characters will be inserted
        automatically into the file name. This is useful if multiple files
        have to be written, e.g. if each slice of a 3D image stack should
        be written into a separate file. In order to replace the hashmark
        characters by an actual number, the static method
        HxFileFormat::enumerate of class HxFileFormat can be
        used. */ 
    void registerFileType(const char* name=NULL, const char* suffix=NULL,
        int multiSave=0);

    /** Returns file format selected for saving a file. For details about
        the file type see registerFileType(). Currently, only the name
        of the file type can be returned by the file dialog, not the index.
        Therefore, type names should be unique. */
    const char* getFileType();

    /** Sets the file format used for saving a file. @c name should be the
        name of a format registered with registerFileType(). This format will
        be the default format, i.e., it is selected when the file dialog is
        opened the first time. The method should be called after
        registerFileType(). Otherwise the format will be reset to the first
        registered format. Returns false, if the specified name was not
        set using registerFileType(). */
    bool setFileType(const char* name);

    /** Add path to history menu. Paths added by this method will always be
        listed in the history menu. In addition, the last 10 or so paths
        will be listed. */
    void addHistory(const char* path);

    /** Executes the dialog, returns 0 if everything was ok. The file
        dialog is a modal dialog. After returning from this method, the
        number and the name of the selected files can be queried by means
        of getFileCount and getFileName(). */
    int postAndWait();

    /** Enables/disables to open only Amira networks 
        file.
      */
    void openOnlyNetworks(bool flag) ;

    /** Append a new extension that will be filtered by the qdialog      
      */
    void appendFilter(const char* name, const char* extension);

    /** Deleting any previous extension in the qdialog
      */
    void resetFilters(void);

    /** Receive the list of extension filtered by the qdialog      
      */
    QStringList* getFilters(void);

    /// select one filter in the qdialog
    void setSelectedFilter(const McString& name, const McString& extension);

    /// Return the current filter selected in the qdialog
    void getSelectedFilter(McString& name, McString& extension) const;

    /// Save directory list to registry (windows only).
    void savePathList();
    
    static HxFileDialog* _getTheFileDialog();

    static int exists() { return (_theFileDialog!=0); }

    /** 
     * To register the script file formats.
     */
    void registerScriptFileFormats();

    /** 
     * To know if the current script file format is "pack & go".
     */
    bool isCurrentScriptFileFormatPackAndGo() const;

    /** 
     * To get the current script file format header.
     */
    McString getCurrentScriptFileFormatHeader() const;

  protected:
    Usage usage;
    QxFileDialog* qdialog;
    HxFileDialogPrivate* priv;
    
    static HxFileDialog *_theFileDialog;

  private:

    /** 
     * To add the available script file formats to the list.
     */
    void initScriptFileFormats();

    /** 
     * To store a script file format information.
     */
    struct ScriptFileFormatInfo
    {
      McString name;
      McString header;
      bool isPackAndGo;
    };

    /** 
     * To store all script file formats info.
     */
    McDArray< ScriptFileFormatInfo > m_scriptFileFormats;

    /** 
     * Index of the current script file format to use when saving networks.
     */
    int m_currentScriptFileFormatIdx;
};

// Global instance of the file dialog
#define theFileDialog (HxFileDialog::_getTheFileDialog())

#endif

/// @}
