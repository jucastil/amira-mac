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
#ifndef HX_FILE_FORMAT_H
#define HX_FILE_FORMAT_H

#include <sys/types.h>
#ifndef _WIN32
#include <regex.h>
#endif

#include <mclib/McInterface.h>
#include <mclib/McDArray.h>
#include <mclib/McTypedObject.h>
#include <mclib/McTypedObject.h>
#include <mclibthreaded/McMutex.h>
#include <hxcore/HxDSO.h>
#include <hxcore/HxAmiraWinDLLApi.h>
#include <hxcore/HxData.h>
#include <hxcore/ProgressSenderIface.h>

#include <QThread>

class HxObject;
class QRegExp;
class McString;
class HxFileFormat;

class LoadThread : public QThread, public McInterface
{
    Q_OBJECT
    MC_HEADER(LoadThread);
public:
    LoadThread() : mProgressSenderIface(this) {}
    LoadThread(HxFileFormat *fileFormat, LoadFunction loadFunction, LoadFunction2 loadFunction2);
    virtual ~LoadThread();
    void setProgressModule(HxObject *obj);
    void setFilenames(int n, const char* const* files);
    void setMultiLoad(int multiLoad);
    int getResult();
    // Cancel all threads which are queued for loading
    static void abortThreads(HxFileFormat *format);
    // Wait until all canceled threads are finished
    static void waitUntilThreadsFinished(HxFileFormat *format);

public slots:
    void deleteProgressModule();
protected:
    // Insert thread into list of threads to process
    void registerThread();
    // Remove thread from list
    void unregisterThread();
    virtual void run();

    char **mFilenames;
    int mNumFiles;
    HxFileFormat *mFileFormat;
    LoadFunction mLoadFunction;
    LoadFunction2 mLoadFunction2;
    int mMultiLoad;
    HxObject *mProgressModule;
    int mRes;
    LoadThread *mPrev;
    LoadThread *mNext;
    static McMutex mThreadListLock;

private:
    ProgressSenderIfaceGenImpl mProgressSenderIface;
};

/** This class provides an interface to user-defined file formats. File
    formats are registered by means of an Amira Tcl-command. Both, loading
    and saving of Amira objects is supported. 

    In order to register a file format use something like this:

    @code
    dataFile -name GIF-option gif \
        -ext .gif -load readGIF \
        -type HxRGBImage -save saveGIF \
        -dso libimio.so
    @endcode

    See the  @htmlonly <a href= ../usersguide/AmiraIndexFileFormat.html> usersguide </A> @endhtmlonly 
    for a list of @c Fileformats already supported by Amira.
*/ 

class HXCORE_API HxFileFormat {

  public:
    /// Constructor, but usually class instances are created by parse().
    HxFileFormat();

    /// This constructor is used for compiled-in formats.
    HxFileFormat(const char* label);

    /// Destructor.
    virtual ~HxFileFormat();

    /// The label is used in menus to identify the format.
    const char* getLabel() const { return label; }

    /** Tcl commands use the option string to specify the format, for
        example "load -iv filename". The option string does not contain a
        leading dash, i.e. "iv" is returned instead of "-iv". */
    const char* getOption() const { return option; }

    /** Return true if the file format supports options on the "save" command. In this case, all options
     *  given to the "save" command will be passed to the write function of the corresponding writer.
     *  Using this option, avoid to modify all writers so they can handle error message when not supporting 
     *  arguments.
     */
    bool hasWriteParameters() const { return m_hasWriteParameters; }

    /// Returns standard extension of file format.
    const char* getSuffix() const { return suffices.size()?suffices[0]:0; }

    const char* getSharedObjectName() const { return sharedObjectName; }

    /// Returns the C++ name of the load function.
    const char* getLoadFunctionName() const { return loadFunctionName; }

    /// Returns the C++ name of the save function.
    const char* getSaveFunctionName() const { return saveFunctionName; }

    const McDArray<char*>& getTypes() const { return saveTypes; }

    /// Returns 1 if argument matches format's headerRegEx.
    int checkHeader(const char* header);

    /// Returns 1 if argument matches format's filename pattern or reg ex.
    int checkFilename(const char* filename);

    /** Try to load given files. The files are loaded synchronously if either
        loadAsync is set to false or a network is currently loading. 
        Otherwise all files are loaded asynchronously.
        When loading synchronously the number of successfully read files is 
        returned, otherwise the number of scheduled files.
        If a file could not be read the method returns without
        trying to load further files. */
    int load(int n, const char* const* files, bool loadAsync=true);

    /// Returns 1 if the format implements a load method.
    int isLoad() const { return (loadFunctionName || loadFunction); }

    /// Returns 1 if the format implements a save method.
    int isSave() const { return (saveFunctionName || saveFunction); }

    /** Returns 1 if the format implements a multisave method. A multisave
        method generates multiple files for one data object. These files
        should be enumerated properly, e.g. using @c enumerate(). */
    int isMultiSave() const { return isSave() && multiSave; }

    /// Returns 1 if objects of given type can be saved.
    int canSave(const HxObject* object) const;

    /// Saves object using given filename.
    int save(HxObject* object, const char* filename);

    /** Parses arguments and returns a new instance of HxFormat.
        The following options are interpreted:

            @li @c -label Label
            @li @c -option Option
            @li @c -header HeaderRegEx
            @li @c -file FilenameRegEx
            @li @c -ext Suffix1[,Suffix2,...]
            @li @c -load ReadMethod
            @li @c -type SaveType1[,SaveType2,...]
            @li @c -save SaveMethod
            @li @c -check Tcl-expression
            @li @c -multisave SaveMethod
            @li @c -dso SharedObjectName
            @li @c -loadInOwnThread <false|true|multi>
	
        Note, that argv[0] should already point to the first option.
    */
    static HxFileFormat* parse(int n, char **argv);

    /** Explicitly set the load function. This is necessary if a file
        format should be directly compiled into the code and not loaded
        dynamically from an DSO. */
    void setLoadFunction(LoadFunction load) { loadFunction = load; }
    /** Explicitly set the load function. This is necessary if a file
        format should be directly compiled into the code and not loaded
        dynamically from an DSO. This version is for load routines which
        support McProgressInterface. */
    void setLoadFunction2(LoadFunction2 load) { loadFunction2 = load; }

    /// Explicitly set the save function.
    void setSaveFunction(SaveFunction save) { saveFunction = save; }

    /// Set option string.
    void setOption(const char* option);

    /// Set header reg ex.
    void setHeaderRegEx(const char* headerRegEx);

    /// Set filename reg ex.
    void setFilenameRegEx(const char* filenameRegEx);

    /// Append file extension.
    void appendSuffix(const char* suffix);

    /// Checks if two formats are equal (used to redefine a format).
    int operator==(const HxFileFormat& other);

    /// Returns the capability to be converted into the LDA format.
    const bool isLDAConvertible() const {return LDAConvertible;};

    /// Sets the capability to be converted into the LDA format.
    void setLDAConvertible(bool value) {LDAConvertible = value;};

    /// Returns the capability to be converted into the LDA format.
    const bool isEnabled() const {return enabled;};

    /// Disable the capability to be used to load any file of this format.
    /// The parameter is the name of the license that has not been found
    /// to allow the use of this file format. It is used to show which 
    /// license is needed when loading file fails because license is missing.
    void disable(const char *licenseName = NULL);

    /** Generate an enumerated file name. @c pattern is searched for a
        sequence of \#-characters. If such a sequence is found it is
        replaced by the number @c n printed with leading zeros. If no
        such pattern is found the number is inserted before the filename
        suffix using at least four digits. If no suffix exists it is
        appended to the filename. */
    static void enumerate(McString& result, const char* pattern, int n);

    static HxFileFormat * getFileFormatByLabel(const char * label);

    /** 
     * To know if the file format generate data provider interface.
     */
    bool isDataProviderCompatible() const { return m_dataProviderCompatible; }

    /** Returns the priority of the fileformat.
        Among two matching file formats, the highest priority one is choosen.
    */
    int getPriority() const { return m_priority; }

    /// Returns a list of all suffixes this file format may have.
    McDArray<char*> const& getSuffixes() const {return suffices;}
    
    enum LoadMode {MainThread, OwnThreadExclusive, OwnThreadMultiple};
    /** 
     * Should loading processed in the main thread, in a worker thread 
     * but exclusive (OwnThreadExclusive), or can multiple loadings be
     * processed in parallel (OwnThreadMultiple)?
     */
    void setLoadMode(LoadMode loadMode);
    virtual LoadMode getLoadMode() const;
    /**
     * Pointer to the LoadThread which currently uses the load routine managed
     * by this HxFileFormat object.
     */
    void setCurrentLoadThread(LoadThread *loadThread);
    LoadThread* getCurrentLoadThread() const;
  protected:
    

    char* label;		// Name to be displayed in file browser
    char* option;		// Option of the load command

    QRegExp* headerRegEx;	// Compiled regular expression for file header
    QRegExp* filenameRegEx;	// Compiled regular expression for file suffix

    McDArray<char*> suffices;	// List of suffices which identify format 

    unsigned int multiLoad:1;	// True is load func takes multiple files
    unsigned int multiLoad2:1;	// True if load func 2 takes multiple files
    unsigned int multiSave:1;	// True is save func write multiple files
    char* loadFunctionName;	// C++ name of load function (will be mangled)
    LoadFunction loadFunction;		// Pointer to load function
    LoadFunction2 loadFunction2;    // Pointer to load function with McProgressInterface

    McDArray<char*> saveTypes;	// Type info of objects which can be saved
    char* saveFunctionName;	// C++ name of save function (will be mangled)
    SaveFunction saveFunction;		// Pointer to save function
    char* check;                // Tcl-check

    HxDSO handle;
    char* sharedObjectName;
    
    bool LDAConvertible;

    bool m_dataProviderCompatible;

    int m_priority;

    /** Set to true if the file format supports parameters on the "save" command */
    bool m_hasWriteParameters;

  private:
    bool enabled;
    char* licenseLabel;

    LoadMode mLoadMode;             // See setLoadMode()
    LoadThread *mCurrentLoadThread; // See setCurrentLoadThread()
};

#endif

/// @}
