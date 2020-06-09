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
#ifndef HX_DATA_H
#define HX_DATA_H

#include <stdarg.h>
#include <hxcore/HxObject.h>
#include <hxcore/HxMasterConnection.h>
#include <amiramesh/HxParamBundle.h>

class HxData;
class HxCoordSystem;
class HxCoordSystemListener;
class HxFileFormat;
class ProgressSenderIface;
class QStringList;

typedef int (*LoadFunction)(const char* filename);
typedef int (*LoadFunction2) (const char* filename, ProgressSenderIface *progress);
typedef int (*SaveFunction)(void* object, const char* filename);

typedef int (*LoadSeriesFunction)(int n, const char* const* files);
typedef int (*LoadSeriesFunction2)(int n, const char* const* files, ProgressSenderIface *progress);
typedef int (HxData::*SaveMethod)(const char* filename);

/** Base class for all Amira data objects. This class add the following
    features to ordinary objects of type HxObject:

    @li Possibility to mark data objects as new by calling touch.
          A special bit mask can be used to indicate that only certain
          parts like transformation or parameters have changed. Downstream
          modules will only be fired if a data object has changed, i.e., if
          it is marked as new (see isNew()). In addition, a module may
          save redundant computations by querying which of the touch flags
          are set.
    @li Possibility to define arbitrary parameters, even in a
          hierarchical way. Parameters are stored in the public member
          parameters of type HxParamBundle. They may be edited
          interactively via the parameter editor.
    @li Possibility to define save methods and load functions. */
class HXCORE_API HxData : public HxObject {

  HX_ABSTRACT_HEADER(HxData);

  public:
    /// Local structure used to register save methods, i.e., member methods.
    struct SaveInfo {
        /// The name of the save file format.
        const char* name;
        /// The preferred file name extension of the format.
        const char* suffix;
        /** Pointer to save member method. @c SaveMethod is defined in the
            following way:
            @code
            typedef int (HxData::*SaveMethod)(const char* filename);
            @endcode
            The save method takes the name of the file the data object
            should be saved to. It should return true on success, or false
            if some error occurred. */
        SaveMethod method;
    };

    /** Pointer to array of @c SaveInfo structures. Note, that it is
        recommended to use global save functions (which are registered in
        the Amira .rc-files) instead of save methods (which are registered
        via the saveInfo pointer). Save functions provide more
        flexibility. For example, they can not only be configured for
        objects but also for interfaces (compare HxInterface).
        Another advantage is that they support the multi-save option (file
        browser displays file name with hashmark pattern, see
        HxFileFormat).

        In order to register save methods the saveInfo pointer should be
        initialized with the address of a static array of SaveInfo
        structutes. The last entry of the array should contain a
        SaveInfo structure with a null name. Example:
        @code
        static HxData::SaveInfo si [] = {
            { "Inventor", ".iv", (SaveMethod) &HxIvData::write },
            { 0, 0, 0 }
        };

        HxIvData::HxIvData() {
            saveInfo = si;
            ...
        }
        @endcode
        Note, that if you want to add a new save method in a derived class
        you must set saveInfo to a new array containing the
        SaveInfo pointers of all base classes as well. */
    SaveInfo* saveInfo;

    /** Returns name of file from which data has been read. The file name
        will be stored as a parameter of the data object when calling
        registerData. */
    const char* getFilename() const;

    /** Returns the default file format of the data object. The default file
        format is used when the object's save() method is called without
        a format string and no SaveInfo parameter has been set (see
        setSaveInfoParam()). This happens for example, when a new data
        objects needs to be stored in oder to create a network script. The
        default file format will also be used in order to initialize the
        file format combo box of the file dialog when choosing "Save Data
        As..." from the main menu. */
    const char* getDefaultFileFormat() const;

    /** Sets the default file format for this data object. Usually the default
        file format is set in the data object's contructor, and there is no
        need to change it later. However, custom compute modules or read
        routines may do so if they know that some custom format is better
        suited to represent the object. For most native Amira data object
        the default file format is the AmiraMesh format. The format itself
        should be specified by the format name (same name as shown in the
        file type combo box of the file dialog). */
    void setDefaultFileFormat(const char* format);

    /** Returns the preferred file format for saving the data object.
        This format is used in order to initialize the file type combo box
        in the "Save Data As..." file dialog. The format is determined
        as follows:

        \arg Use file format specified in "SaveInfo" parameter
        \arg Use default file format as returned by getDefaultFileFormat()
        \arg Determine file format from extension of given file name
        \arg Return first format available for the data object

        If no format is registered and the object can't be saved at all
        a null string is returned. */
    const char* getPreferredFileFormat(const char* filename=0) const;

    /// These flags specify what part of a data object has changed.
    enum {
        /// The transformation of a spatial data object changed.
        NEW_TRANSFORMATION = 1 ,
        /// The coordinates or the bounding box changed.
        NEW_COORDINATES = 2,
        /// The data values changed.
        NEW_DATA = 4,
        /// The name of a data object changed.
        NEW_LABEL = 8,
        /// The range changed.
        NEW_RANGE = 16,
        /// The input (source) of a connection port changed.
        NEW_SOURCE = 32,
        /// The parameters have changed.
        NEW_PARAMETERS = 64,
        /// The color or transparency values changed.
        NEW_COLOR = 128,
        /// Indicates that local range flag was toggled.
        NEW_RANGE_STATE = 256
    };

    /** Set content description. The content description will be stored in
        a parameter @c Content. In future versions of Amira the content
        description may be displayed in the file browser. However,
        currently it is simply ignored. */
    void setContentInfo(const char* format, ...);

    /** Sets new flag and touches all downstream connections. This
        method should always be called when a data object is modified.  The
        bit mask allows you to specify in more detail which parts of the
        object have changed. Derived classes can define more specific new
        flags. This method also sets the corresponding bits in the modified
        mask. */
    virtual void touch(unsigned int mask=0xffffffff);

    /** Returns true if data has been changed. The bit mask allows you to get
        more detailed information about which parts of the object have been
        changed. The new flag returned by this method will be reset to zero
        at the end of the fire() method. */
    int isNew(unsigned int mask=0xffffffff) const { return newFlag&mask; }

    /** Returns true if data has been modified. The bit mask allows you to
        get more detailed information about which parts of the object have
        been modified. In contrast to the new flag returned by isNew
        the modified flag is not reset until the object is written to file. */
    int isModified(unsigned int mask=0xffffffff) const { return modifiedFlag&mask; }

    /** Set the modified state. Typically used in save methods to
        set the modified state to 0. */
    virtual void setModified(unsigned int mask);

    /** Returns the time of the last call of touch. The touch time is
        a simple global counter which is increased each time touch() is
        called. It is used by compute modules (see HxCompModule) in
        order to decide whether a result object can be recomputed with the
        current port settings or not. If a result object can be recomputed
        the object need not to be saved itself when writing a network
        script. */
    int getTouchTime();

    /** Force computation of this and all downstream objects. Downstream
        objects will only be fired if the new flag is non-zero, i.e., if
        touch has been called by an upstream compute module or by the
        data object's compute method itself. At the end of the fire method
        the new flag is cleared. */
    virtual void fire(int shouldCompute=1);

    /// Tcl command interface of the data object
    virtual int parse(Tcl_Interp* interpreter, int argc, char **argv);

    /// Connection to compute module or data editor.
    HxMasterConnection portMaster;

    /// Contains data specific parameters.
    HxParamBundle parameters;

    /// Duplicates the current object (returns NULL if not implemented)
    virtual HxData* duplicate() const;

    /// Kind of assignment operator, used by duplicate.
    void copyData(const HxData& other);

    /// Calls HxObject::setViewerMask() with master==mask.
    virtual void setViewerMask(int mask, int master=0xffff);

    /// Data objects are mediumaquamarine.
    virtual McColor getIconColor();

    /// Inherited from HxObject.
    virtual bool acceptConnect(HxConnection* connection);

    /// To know if the data is savable.
    void getSavingFlags(bool& isSavable, bool& isSavableAs) const;

    /// Determines the most suitable save format for the given format string.
    bool determineSaveFormat(char const *format, HxFileFormat *&saveFormat, int &saveMethod);

    /** Generic preprocess function, which will be called after the data has 
        been registered within the ObjectPool. 
        
        Overwrite this function in a derived data class
        in order to implement a custom preprocessing routine. 
    */
    virtual void preProcess() {}
    
    /** Generic function, which will be called whenever it's necessary 
        to cancel data preprocessing.

        Usually the data preprocessing @see preProcess() will be implemented 
        asynchronously, running in a separat worker thread.
        
        Overwrite this function in a derived data class
        in order to terminate/cancel the worker thread in a propper way.
    */
    virtual void cancelPreProcess() {}

    /** Generic function to create information about a certain object
        which should be used for logging.

        Overwrite in derived data classes in order to get logging
        information.
    */
    virtual McString getLoggingInfo() {return McString();}

  protected:
    // Indicates if data is new.
    unsigned int newFlag;

    /// Time returned by getTouchTime.
    int touchTime;

    // Constructor is protected - this is an abstract class
    HxData(McInterfaceOwner* owner = 0);

    // Virtual destructor
    virtual ~HxData();

    // Prints class name.
    virtual void info();

    /// Special creation syntax for data objects.
    int saveCreation(FILE* fp, const char* dataDir, int savingFlags);

    /// Calls HxObject::callCompute() and returns the newFlag.
    virtual int callCompute();

  public:
    /** Saves data object in a given format. @c format may either be the name
        of a save method, i.e., a member method of the data class
        registered via saveInfo, or it may be the name of a save
        format, i.e., a save function registered in one of the Amira
        .rc-files (see HxFileFormat). The method returns true on
        success or false if some error occured. In this case an error
        message is printed in the console window by the particular save
        routine itself. */
    int save(const char* format, const char* fileName);

     /** 
      * @copydoc HxData::save(const char* format,const char* fileName) 
      * writeParameters will be appended to fileName string before being send to 
      * the save method of the file writer. It allows to give custom parameters to
      * a file writer. Quoted parameters (with ") are appended to the filename so filename has this form:
      // \"filename\" \"space separated parameters\"
      */
    int save(const char* format, const char* fileName, const QStringList& writeParameters);

    /** Reader methods use this to register new data class instances.
        The method set the name of @c newData to @c filename (leading
        directories are removed) and adds the data object to the object
        pool. In addition the default load command for the data object
        (parameter <em> LoadCmd</em> is set to <em> load <filename></em>. When the
        file format cannot be detected automatically or if multiple data
        objects are created from a single file more sophisticated load
        commands must be set afterwards using setLoadCmd(). The
        parameter @c ext is obsolete. */
    static void registerData(HxData* newData, const char* filename,
                             const char* ext=NULL);

    /** Sets the load command for the data object. The load command is
        stored as a special parameter called <em> LoadCmd</em>. This parameter
        contains a Tcl-command which, when executed, loads or creates the
        data object. By default the load command is simply set to <em>
        load <filename></em>. Filename is always protected by quotes (").

        If you want to define a more sophisticated load commands, set
        @c verbatim to true. Then @c filename is interpreted as a load
        command string without any further modifications. For example,
        set filename to <tt>load -dicom slice01.dcm slice02.dcm slice03.dcm</tt>
        if you want to write a reader for multiple 2D images in DICOM
        format. Note, that in verbatim mode you are responsible for
        quoting file names containing white spaces. */
    void setLoadCmd(const char *filename, int verbatim=0);

    /** Sets the <em> SaveInfo</em> parameter of a data object. If present, the <em>
        SaveInfo</em> parameter should indicate the default file format used by
        the <em> Save</em> option of the <em> File</em> menu. If no parameter <em>
        SaveInfo</em> or no parameter <em> Filename</em> exists the <em> Save</em>
        option will be insensitive and <em> Save As</em> must be used. This
        method should be called in read and save methods. */
    void setSaveInfoParam(const char *format);

    virtual void checkRemoteMode();

    // set the data coordinates system and notify listeners of the change
    void setCoordSystem(const HxCoordSystem* cs);

    // retrieve the data coordinates system
    const HxCoordSystem* getCoordSystem() const;
    
    // Indicates if the given editor can be attached to this data
    virtual bool isEditable(const HxEditorInfo* info) const;

    /** Attaches an editor to the data object. In Amira 4 and before editors always
        had to be connected to the data object's master connection (portMaster).
        In Amira 5 the parameter editor no longer uses the master connection,
        but is attached separately. This allows it to open the parameter editor
        without disconnecting the data object from an up-stream compute module
        or a multi-channel field. This method is the preferred way to attach an
        editor to a data object. */
    void setEditor(HxEditor* editor);

    /** Returns the editor currently connected to the data object. */
    HxEditor* getEditor() const;

  private:
    /*  Indicates if data was modified or not. In order to modify this flag
        the method setModified() has to be used. This method updates the visual
        representation of the data object's icon if necessary (modified data
        objects have an asterisk appended to their name). */
    unsigned int modifiedFlag;

    unsigned int wasComputeCalled;

    // coordinates system used by the listeners in their gui and/or 3D representation.
    const HxCoordSystem* m_coordSystem;

    // Stores default file format, see getDefaultFileFormat() for details.
    McString mDefaultFileFormat;

    // Pointer to a "read-only" editor (currently only used for parameter editor).
    McHandle<HxEditor> mReadOnlyEditor;
};

#define HX_DATA_HEADER(className) \
    MC_ABSTRACT_HEADER(className)

#define HX_DATA_INIT(className,parentClass) \
    MC_INIT_ABSTRACT_CLASS(className,parentClass)

#endif

/// @}
