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
#ifndef HX_RESOURCE_H
#define HX_RESOURCE_H

#include <tcl.h>
#include <mclib/McHandle.h>
#include <mclib/McDArray.h>
#include <mclib/McFilename.h>
#include <Inventor/SbBasic.h>
#include <hxcore/HxAmiraWinDLLApi.h>

#if defined(TGS_VERSION) && TGS_VERSION>=3000
    #define AMIRA_MULTITHREAD
    #include <Inventor/threads/SbThread.h>
#endif

template<class Key, class Value> class McHashTable;
class HxTclWrapper;
class McTypeInfo;

class McTypedObject;
class McException;
class HxFileFormat;
class HxDSO;
class HxEditor;
class HxObject;
class QImage;
class QPixmap;
class QCursor;
class SoType;
class SbThreadRWMutex;
class HxTViewInfo;


enum HxProductDir {
  HX_ROOT_DIR=0x01,
  HX_LOCAL_DIR=0x02,
  HX_ALL_DIRS=0x03
} ;

/** Internal struct representing registered Amira objects. For each
    data class or module registered in an Amira .rc file a HxObjectInfo
    struct is created. A list of these structs can be obtained using the
    method HxResource::matchingObjects(). */
struct HXCORE_API HxObjectInfo : McHandable {
    char*  label;
    int    nPrim;
    char** primary;
    int    color;
    char*  initProc;
    char*  checkSource;
    char*  className;
    char*  sharedObjectName;
    HxDSO* handle;
    char** category;
    int    nCategories;
    int    tmpIdx; //  needed temporarily
    char*  cCheckSource;
    char*  cCheckUserData;
    char*  cCheckSharedObjectName;
    HxDSO* cCheckDSO;
    int    priority;
    char*  language;

    HxObjectInfo(const char* label,
        const char* primary,
        const char* color,
        const char* initProc,
        const char* check,
        const char* className,
        const char* sharedObjectName,
        const char* category,
        const char* ccheck,
        const char* ccheckdat,
        const char* ccheckdso,
        const char* priority,
        const char* language);

    ~HxObjectInfo();

    void clearCCheck();
    int getIconColor();
};

/** Internal struct representing registered Amira editors. For each
    editor registered in an Amira .rc file a HxEditorInfo struct is
    created. These structs are stored in HxResource::editors. */
struct HxEditorInfo {

    char*       label;
    char*       dataType;
    char*       checkSource;
    char*       className;
    char*       iconName;
    QPixmap*    icon;
    char*       sharedObjectName;
    HxDSO*      handle;
    int         supportRemoteSync;

    HxEditorInfo();
    ~HxEditorInfo();
    int isValid();
    void dupValues();
};

/** 
    Struct representing shader info
*/
struct HxShaderInfo
{
    McString shaderName;
    McString shaderFilename;
    McString package;

    HxShaderInfo(const char*   shaderName
                 , const char* shaderFilename
                 , const char* packageName)
        : shaderName(shaderName)
        , shaderFilename(shaderFilename)
        , package(packageName)
    {}
};

/**
    Struct representing unit tests.
*/
struct HxTestInfo {
    HxTestInfo(const char* className, const char* package, const char* category)
            : className(className), package(package), category(category)
    {}

    McString className;
    McString package;
    McString category;
};

class HxInterfaceFactory;
/** Internal struct representing registered amira interfaces. For each interface
    factory registered in an Amira .rc file a HxInterfaceFactoryInfo struct is
    created. These structs are stored in HxResource::mInterfaceFactories. */
struct HxInterfaceFactoryInfo
{
    int                 nExtendsType;
    char**              extendsType;
    char*               checkSource;
    char*               className;
    char*               sharedObjectName;
    HxDSO*              handle;
    HxInterfaceFactory* factory;

    HxInterfaceFactoryInfo(
        const char* extendsType,
        const char* check,
        const char* className,
        const char* sharedObjectName = NULL);

    ~HxInterfaceFactoryInfo();
};

class HxSubApplication;
/** Internal struct representing registered amira sub-applications. Each
    sub-application is represented by a separate button near the console
    window. Sub-applications are registered in a .rc file. */
struct HXCORE_API HxSubApplicationInfo
{
    char*               name;
    char*               iconName;
    char*               className;
    char*               sharedObjectName;
    HxDSO*              handle;
    HxSubApplication*   subApplication;

    HxSubApplicationInfo(
        const char* name,
        const char* iconName,
        const char* className,
        const char* sharedObjectName = NULL);

    ~HxSubApplicationInfo();
};

/** Internal struct representing macro button actions. For each macro
    button defined in an Amira .rc file a HxMacroButtonInfo struct
    is created. These structs are stored in HxResource::mMacroButtons. */
struct HxMacroButtonInfo
{
    char*  label;       // Label of the macro button action
    char*  proc;        // Tcl procedure to be executed if the macro button is clicked
    unsigned int color; // Background color of macro button (R+(G<<8)+(B<<16))

    HxMacroButtonInfo(const char* label,
                      const char* proc,
                      const char* color);

    ~HxMacroButtonInfo();
};

/// @if EXCLUDETHIS
struct HxHostInfo {

    char* name;
    char* path;
    char  addr[4];
    int   sock;

    HxHostInfo();
    ~HxHostInfo();

    void dupValues();
    int isValid();
    HxHostInfo *getHostListEntry();
};

struct HxUserInfo {
    char* name;
    char* home;

    HxUserInfo();
    ~HxUserInfo();

    void dupValues();
    int isValid();
};

class HXCORE_API HxPathTranslator {
    public:
        virtual ~HxPathTranslator();

        virtual bool onSave( McString& hint, McDArray<McString>& files ) = 0;

        virtual bool onLoad( const char* hint,  McDArray<char*>& files ) = 0;
};
/// @endif

/** Utility class providing static methods for different purposes. */
class HXCORE_API HxResource
{
public:
    /// Returns Amira version string, e.g. "4.0.0".
    static const char* getVersion();

    /** This method returns 1 if Amira has been started with the -no_gui
        command line option. The option is useful for executing scripts
        in batch mode. No windows or dialogs are popped up. */
    static int noGui() { return noGuiFlag; }

    /** This method returns 1 if Amira has been started with the -no_border
        command line option. The option is interpreted by HxViewerPanel.
        If set, borderless windows will be created for all 3D viewers. This
        is useful e.g. for holobench applications. */
    static int noBorder() { return noBorderFlag; }

    /// Sets the no border flag when Amira has already been started.
    static void setNoBorder(int f) { noBorderFlag=f; }

    /** Returns the Amira root directory. The Amira root directory is the
        directory where Amira is installed in. Usually it is determined
        automatically, but it can also be defined by setting the
        environment variable AMIRA_ROOT. The directory name is returned
        without a trailing '/' character. */
    static const char* getRootDir();

    /** Returns local Amira directory. The local directory is an
        additional directory with the same structure as the Amira
        root directory. It can be used to add custom modules and
        other components to Amira. On UNIX systems the local Amira
        directory must be defined by the environment variable
        AMIRA_LOCAL. On Windows the directory can be specified via
        the development wizard. If no local Amira directory exists
        the name of the root directory is returned. */
    static const char* getLocalDir();

    /** Returns Amira's main data directory. This is the first directory
        defined in the environment variable AMIRA_DATA. If this environment
        variable is not defined at all, $AMIRA_ROOT/data is returned. */
    static const char* getDataDir();

    /** Returns Amira's demo directory. The demo directory is defined by
        the environment variable AMIRA_DEMOS. If this variable is not
        defined, a null pointer is returned. */
    static const char* getDemoDir();

    /** Returns Amira's network drive directory, i.e. the root dir of
        a network drive.  This directory is defined by the environment
        variable AMIRA_NETWORKDRIVE_DIR.  If this variable is not
        defined, a null pointer is returned.  This variable is
        particular useful if you are working on different platforms
        which have the same network drive mounted under different
        names, e.g. 'k:/' on Windows and '/vis/data/' on Linux. */
    static const char* getNetworkDriveDir();

    /** Returns path of amira executable. On Unix the absolute path name
        of the Amira start script is returned. On Windows the absolute path
        name of amiramain.exe is returned. */
    static const char* getExecPath();

    /// Returns the architecture string, e.g. "arch-Linux-Optimize".
    static const char* getArchString();

    /// Returns a string describing the instruction set architecture, e.g. i386, x64, ppc, or ia64.
    static const char* getISA();

    /** Returns name of the X11 display (Unix only). The display must
        either be specified using the -display command line option or
        using the DISPLAY environment variable. On Windows, a null
        pointer is returned. */
    static const char* getDisplayName() { return displayName; }

    /// Returns the host name of the computer.
    static const char* localHost();

    /// Returns the host id of the computer as used for license checking.
    static const char* getHostId();

    /** Search for a file in AMIRA_LOCAL and AMIRA_ROOT. For example, you
        can set @c filename to "share/resources/hxmolecule.rc", The method
        returns 1 if this file exists in either AMIRA_LOCAL or AMIRA_ROOT.
        On return, @c filename is substituted by the absolute path of the
        found file. AMIRA_LOCAL is searched first. If the file could not
        be located 0 is returned and @c filename remains unchanged. */
    static int locateFile(McFilename& filename, HxProductDir whereToFind=HX_ALL_DIRS);

    /**@name Methods for loading data objects. */
    //@{

    /// Try to load a file (format detected automatically).
    static int loadData(const char* filename, bool loadAsync=false);

    /// Try to load a file (format determined by @c format).
    static int loadData(const char* filename, const char* format, bool loadAsync=false);

    /// Try to load a series of files (format detected automatically).
    static int loadData(int n, const char* const* files, bool loadAsync=false);

    /// Try to load a series of files (format determined by @c format).
    static int loadData(int n, const char* const* files, const char* format, bool loadAsync=false);

    /// Automatic file format detection.
    static HxFileFormat* queryDataFormat(const char* file);

    /// Automatic file format detection.
    static HxFileFormat* queryDataFormat(int n, const char* const* files);

    //@}

    /**@name Methods for 2D image IO */
    //@{

    /** Read an image from file, memory must be freed by user.
        Parameter size contains the entries image size in x, image size in y
        and number of colour values */
    static int readImage(const char* filename, int size[3], unsigned char*& data);

    /// Read a Qt image from file.
    static int readQImage(const char* filename, QImage& image);

    /// Returns list of supported image output formats.
    static const char** imageOutputFormats(int& n);

    /// Determines image format from file name suffix.
    static const char* queryImageFormat(const char* filename);

    /** Writes raster image to file.
        Parameter size contains the entries image size in x, image size in y
        and number of colour values */
    static int writeImage(const char* filename, const int size[3],
        const unsigned char* data, const char* format=0);

    /// Write Qt image to file.
    static int writeQImage(const char* filename, const QImage& image,
        const char* format=0);

    /// Find and read the specified icon. If the file does not exist or is of an unknown format, the pixmap becomes a null pixmap.
    static QPixmap readIcon(const char * icon_name);

    /// Find and read the specified cursor. bitmap and mask make up the bitmap. hotX and hotY define the cursor's hot spot.
    static QCursor readCursor(const char * bitmap, const char * mask, int hotx = -1, int hoty = -1);
    //@}

    /**@name Methods for creation of objects and editors. */
    //@{

    /** Create object from info structure (DLL loaded automatically).
        Source indicates the object the popup menu belongs to the new
        object was selected from. If this argument is not null it is
        used to define the Tcl variable 'source' before the Tcl init
        procedure associated with the new object is executed. */
    static HxObject* createObject(HxObjectInfo* info, HxObject* source=0);

    /// Create object from ASCII class name.
    static HxObject* createObject(const char* className);

    ///
    static void disableObject(const char* className);

    /// Function type of object factories.
    typedef HxObject* ObjectFactory_t(const HxObjectInfo*);

    /** Register a factory that can create objects implemented in the specified language.
      */
    static void registerObjectFactory(const char* language, ObjectFactory_t* factory);

    /** Lookup factory for language.
      */
    static ObjectFactory_t* getObjectFactory(const char* language);

    /** Get McTypeInfo for ASCII class name.

        Different from McTypeInfo::fromName() the shared library containing
        the class is linked if required.
      */
    static const McTypeInfo* getTypeId(const char* className);

    /** Find object info from ASCII class name. The method also finds
        Tcl-only objects. In this case className is interpreted as the
        objects label. */
    static HxObjectInfo* findObject(const char* className);

    /// Create editor from info structure (DLL loaded automatically)
    static HxEditor* createEditor(HxEditorInfo* info);

    /// Create editor from ASCII class name.
    static HxEditor* createEditor(const char* className);

    /// Dynamically link a shared library or DLL.
    static HxDSO* linkDSO(const char* sharedObjectName);

    /// Disable all classes of package and unlink its shared library.
    static void unloadPackage(const char* package);
    //@}
  private:
    static void disableObjectsOfDSO(const McString& sharedObjectName);

    static void disableSimpleClassesOfDSO(const McString& sharedObjectName);

  public:

    /** Returns a list of all objects which can be connected to @c source.
        The resulting objects info list is sorted alphabetically by labels.
        In addition, duplicate entries are removed. Objects which can be
        connected to any interface of @c source are listed as well. */
    static void allMatchingObjects(HxObject* source, McDArray<HxObjectInfo*>&);

    /** Returns a list of objects which can be connected to @c source. In
        contrast to the result returned by allMatchingObjects() the
        list is not sorted and it may contain duplicate entries. Also,
        if @c source is an HxObject, the interfaces of @c source are not
        considered. If @c source is null, all object info entries defined
        in all Amira .rc files are returned. */
    static void matchingObjects(McTypedObject* source, McDArray<HxObjectInfo*>&);

    /**
        Appends all the objects that can be connected to an object of type @c t to the
        @result. If @t is 0, no objects will be appended.
    */
    static void matchingObjectsByType(const McTypeInfo* t, McDArray<HxObjectInfo*>& result);

    /** Returns a list of objects which don't appear in the popup menu of
        any other object. In Amira these objects are listed in the Create
        menu of the main window. The resulting list is not sorted and it may
        even contain entries with identical names. */
    static int noPrimaryObjects(McDArray<HxObjectInfo*>& result);

    /// Register file formats for Amira.
    static void registerFormat(HxFileFormat* info);

    static McDArray<HxFileFormat*> getFileFormatsByType(const McTypeInfo*);

    /// Register objects for Amira, i.e. data types and modules.
    static void registerObject(HxObjectInfo* info);

    static int writeObjectTable(ClientData data, Tcl_Interp* t, int argc, char** argv);

    /// Register file editors for Amira.
    static void registerEditor(HxEditorInfo* info);

    /// Register interfaces for Amira.
    static void registerInterfaceFactory(HxInterfaceFactoryInfo* info);

    /// Register interfaces for Amira.
    static bool registerSubApplication(HxSubApplicationInfo* info);

    ///
    static void registerSimpleClass (const char* className, const char* sharedObjectName);

    ///
    static void enableSimpleClass (const char* className);

    ///
    static void disableSimpleClass(const char* className);

    ///
    static void registerTclWrapper (const char* className, const char* wrapsType);

    ///
    static HxTclWrapper* getTclWrapper (const McTypeInfo* typeToWrap);

    static void registerTest(const HxTestInfo* testInfo);

    /// Register a new gpu shader.
    static void registerShader(const HxShaderInfo* shaderInfo);

    static McTypedObject* createTestObject(const HxTestInfo* testInfo);

    private:
    ///
    static McHashTable<McString, McString>& getSimpleClassTable ();

    ///
    static McHashTable<McString, McString>& getTclWrapperClassNameTable ();

    ///
    static McHashTable<McString, ObjectFactory_t*>& getObjectFactoryTable();

    ///
    static McHashTable<McTypeInfo*, HxTclWrapper*>& getTclWrapperTypeIdTable ();

    static McDArray<const HxTestInfo*>& registeredTestsArray();

    static McDArray<const HxShaderInfo*>& registeredShadersArray();

    public:
    /// Register macro buttons for Amira.
    static void registerMacroButton(HxMacroButtonInfo* info);

    /// Register the tree view information (basic or default directories...)
    static void registerTViewInfo(HxTViewInfo* info);

    /// To get the registered tree view basic information.
    static void getRegisteredTViewInfos(McDArray<HxTViewInfo*>& allInfos);

    /** Returns a list of all registered objects in @c result. */
    static void getRegisteredObjects(McDArray<HxObjectInfo*>& result);

    static const McDArray<const HxTestInfo*>& getRegisteredTests();

    static const McDArray<const HxShaderInfo*>& getRegisteredShaders();

    /// To get the HxEditorInfo structure from an editor class name.
    static const HxEditorInfo* getEditorInfoFromClassName(const McString& editorClassName);

    static McDArray<HxFileFormat*> formats;
    static McDArray<HxEditorInfo*> editors;
    static McDArray<HxInterfaceFactoryInfo*> mInterfaceFactories;
    static McDArray<HxSubApplicationInfo*> mSubApplications;
    static McDArray<HxMacroButtonInfo*> mMacroButtons;
    static McDArray<HxHostInfo*> hosts;
    static McDArray<HxUserInfo*> users;

    /** Manages a global time which is incremented on every call.
        Used by HxData::touch() or HxComputationalModule::setResult() */
    static int getTouchTime();

    /** Create path relative to some directory. The method is used when
        saving Amira network scripts. The Amira root directory is replaced
        by @c ${AMIRA_ROOT}. The Amira local directory is replaced by
        @c ${AMIRA_LOCAL}. The directory @c dir is replaced by @c ${SCRIPTDIR}.
        Not more than two leading up dirs (..) are allowed. Otherwise, an
        absolute path name is generated. */
    static void makeRelativePath(const char* path,
        const char* dir, McString& result);

    /** Decompress file to a temporary file and return its file name in
        result. The caller is responsible for deleting the file.
        On success 0 is returned, */
    static int gunzipFile(const char* infile, McFilename& result);

    /** React to an exception by showing an error dialog. If clearBusy
        is set (default), all busy states will be popped from theWorkArea.*/
    static void handleException(McException& e, int clearBusy=1);

    static SbThreadId_t getMainThreadId() { return mainThreadId; }

    /** Try to allocate numBlocks of the specified size in MB and then immediately
        free the blocks again.
        Return true if the memory was available.*/
    static bool checkMemory(int numBlocks, int blockSizeMB);

    /** Check if the class is locked by a specific license. 
        If yes, check if license exists.
        If license isn't defined prompt a message.
    */
    static bool checkIfClassIsLicenseLocked(const char* className);

  private:
    // Content of display name string
    static const char* displayName;
    // If this is set local modules are taken from debug branch
    static unsigned int localDebugMode;
    // This is set if the -no_gui command line option was specified
    static unsigned int noGuiFlag;
    // This is set if the -no_border command line option was specified
    static unsigned int noBorderFlag;
    // Hostname reported by HxResource::localHost()
    static const char* hostname;

  public:
    static bool isDevVersion();
    static int mainWindowNoShowFlag;

  private:
    /// Initializes resource management
    static void init();

    /** Create path relative to some directory.  The method is used
        when saving Amira network scripts.  If @c envPath exists in 
        @c inStr it will be replaced by @c replaceString.  The result
        will be written to result.  This function is called from
        within the public function makeRelativePath(...), hence it is
        private.  If @c envPath was successfully replaced in @c inStr, 
        the function returns true, otherwise false is returned.
    */
    static bool makeRelativePath(const char * inStr,
                                 const char * envPath,
                                 const char * replaceString,
                                 McString   & result);

    /// Find and read Amira.rc from appropriate directory.
    static void readRCFiles();
    /// Set the internal main thread pointer to the currently running thread.
    static void setMainThreadPtr();

    static McString version;
    static Tcl_HashTable matchingTable;
    static Tcl_HashTable objectTable;

    /// To store the tree view information.
    static Tcl_HashTable tViewInfoTable;

    static SbThreadId_t mainThreadId;
    static int touchTime;

    /** attach interfaces using HxInterfaceFactory.
        MUST be called only once per object.
        Use HxObject::attachInterfacesOnce instead
        of calling this method.
     */
    static void createInterfaces (HxObject* source);

    friend class HxMain;
    friend class HxObject;

  public:
    static void setPathTranslator( HxPathTranslator* t) {
        mPathTranslator = t;
    }

    static HxPathTranslator* getPathTranslator() {
        return mPathTranslator;
    }

  private:
    static HxPathTranslator* mPathTranslator;
};

// Duplicates a string if non-zero.
char* dup(const char* str);

// Duplicates all words of a string separately.
void splitCopy(const char* src, int& n, char**& dst);

#endif

/// @}
