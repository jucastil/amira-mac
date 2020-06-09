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
#ifndef HX_OBJECT_H
#define HX_OBJECT_H

#include <mclib/McBox2i.h>
#include <mclib/McDArray.h>
#include <mclib/McColor.h>
#include <hxcore/HxBase.h>
#include <hxcore/HxPort.h>

#include <string>
using namespace std;

class HxPort;
class HxInterface;
class HxObjectPool;
class HxConnection;
class HxObjectGUI;
class HxTightConnection;
struct HxEditorInfo;
class McFilename;
class HxRemoteSessionController;
class HxInterconnection;
class QxInfoTag;

/** Base class for modules and data objects. Instances of this class can
    be added to theObjectPool, where they will be represented
    by a little icon. Icons of different objects may be grouped together
    using addChild and removeChild.
    The class provides many more features common to modules and data objects,
    e.g. storage of down-stream connections,
    pinning of ports, an autoconnect facility,
    automatic creation of standart documentation files, etc. 
*/
class HXCORE_API HxObject : public HxBase
{
    HX_ABSTRACT_HEADER(HxObject);

  public:
    /** This method sets a new label. The label is checked and perhaps
	modified so that it is unique. The size of the object's icon is
	recomputed. If the icon is visible it is redrawn. If the title
	bar of the object is visible, i.e., if the object is selected or
	if one of the ports is pinned, it will also be updated. */
    virtual void setLabel(const char* label);

    /** Updates the user interface of an object. This method is called
	whenever an object is selected or whenever a port of the object has
	changed. On default, the method does nothing. Derived classes may
	overload it in order to show or hide some of their ports. On default,
	all ports of an object are visible. If some ports should not be
	visible the HxPort::hide method of the port must be called
	each time the update method is called. A common mistake is to call
	HxPort::hide only if some other port is new. */
    virtual void update();

    /** Computes something in response to a parameter change. This method
	is called whenever a port of the object has changed. On default, the
	method does nothing. Derived classes should overload it in order to
	compute the things that should be computed by the object. */
    virtual void compute();

    // Destroy this and all downstream objects.
    virtual void destroy();

    /// Derived objects may override empty default method.
    virtual int autoConnect(HxObject* primary);

    /// Tcl command interface of the object.
    virtual int parse(Tcl_Interp* interpreter, int argc, char **argv);

	static int parseAllInterfaces(Tcl_Interp* t, int argc, char** argv, McInterface* iface);

    /// Displays icon in object pool.
    void showIcon();

    /// Makes icon invisible.
    void hideIcon();

    /// Hides icons of all down-stream objects.
    void collapseChilds();

    /// Shows icons of all down-stream objects.
    void expandChilds();

    /// Check if icon is being displayed in object pool.
    int iconVisible() const { return visible; }

    /// Move icon within the object pool.
    void moveIcon(int x, int y);

    /// Returns icon color.
    virtual McColor getIconColor();

    /// Updates the object's info ports.
    void updateInfo();

    /** The interface widget contains the header bar displaying the
        object's name as well as a number of additional buttons (e.g.
	viewer and editor buttons). */
    QWidget* interfaceWidget(int create=1);

    /// Configures the header controls (stop, edit, clip, viewer)
    void headerConfig();

    /** Select object (ports will be displayed in work area). The argument
        @c index specifies at which position the object will be shown in the
        work area. If index is negative the object will be appended at the
        end of the list of selected objects.  The argument @c updateGUI 
        indicates whether the object pool should be visually updated to
        reflect the selection. This can be set to false when speeding up
        the selection, i.e. when closing the application, is necessary. */
    virtual void select(int index=-1, bool updateGUI=true);

    /// Deselect object (ports will be hidden).
    virtual void deselect();

    /// Check if object is selected in object pool.
    int isSelected() const { return selected; }

    /// Make this and all up-stream objects read-only.
    void setReadOnly(int onOff);

    /// If true, some down-stream object is still working.
    int isReadOnly() const { return (readOnly>0); }

    /// Make this and all down-stream objects invalid.
    int setLock(int onOff);

    /// If true, this or some up-stream object is being edited.
    int isLocked() const { return (locked>0); }

    /// Check if object has an geometry.
    int hasGeometry();

    /** Checks if the specified data object can be created by this module.
        If so, it fills @c createCmd with the appropriate Tcl-commands. */
    virtual int canCreateData(HxData*, McString &createCmd);
    
    /// Pops up the help browser and displays object documentation.
    void help();

    /// callback to allow derived class to override the default filename
    virtual void getHelpFilename (McFilename& name);

    /**
     *  Helper method which computes the help filename @c path 
     *  thanks to a @c typedObject object.
     */
    static bool getHelpFilename(McTypedObject* typedObject, McFilename& path);
    /** Checks if a hint text is embedded in the object's documentation.
        If so, returns the text.  Otherwise, returns an empty string.
      */
    McString getHelpHint();


    /**
     *  Helper method which computes the help filename @c path
     *  thanks to a @c typeInfo class type.
     */
    static bool getHelpFilename(const McTypeInfo* typeInfo, McFilename& path);

    /** Force computation of this and all downstream objects. This method
        is called whenever a port of the object is modified. It should NOT
        be called from inside an update or compute method. It implements a
        2-pass firing algorithm which avoids multiple computations in case
        of complex networks. In the first pass a counter is incremented for
        each downstream module. In the second pass the counter is
        decremented again. If the counter reaches 0 again the object's
        update and compute methods are called. Note, that it is allowed to
        delete or reconnect objects in the compute method. The firing
        algorithm can handle this. */
    void fire2();

    /** Implements the second pass of the firing algorithm. The method
        decrements the fire counter and then possibly invokes update
        and compute. Afterwards, all downstream objects will be fired
        and all ports will be untouched. If the argument is zero, the
        fire counter will just be decremented without invoking update
        and compute. The flag is used for data objects which aren't new
        and thus don't require firing of downstream object.
        
        This method can also be called directly, possibly causing compute()
        to be invoked multiple times for downstream objects. This ensures
        backward compatibility with Amira 2.2. */
    virtual void fire(int shouldCompute=1);

    /** Reimplemented for internal reasons. The method calls setViewerMask()
        for all downstream objects not derived from HxData. Afterwards, it
        calls HxBase::setViewerMask(). */
    virtual void setViewerMask(int mask, int master=0xffff);

    /** Used HxResource::createInterfaces to attach
        interfaces if this was not already done. 
     */
    void attachInterfacesOnce();

    /** Sets the label width of all ports. */
    void setPortsLabelWidth(int size) ;

	/// To connect an object to another.
	virtual int connect(HxObject * source);

	/// To duplicate an object.
	/** This is a virtual function provided for convenience.
		It allows to duplicate both data and modules.
		Originally, only data could be duplicated. */
	virtual HxObject * duplicate() const;

	/// To duplicate an object with its DSCs.
	virtual HxObject * duplicateWithDSC() const;

	/// Save the object into a virtual file and return the list of the Tcl commands.
	virtual void virtualSave(McDArray<string>& saveCommandsList);

    /// Connection ports (all ports together stored in HxBase::allPorts).
    McDArray<HxConnection*> connectionPorts;

    /// List of all down stream connections
    McDArray<HxConnection*> downStreamConnections;

    /** Returns the corresponding GUI object.
        @return Returns the GUI object or Null if not called from the main thread.
    */
    virtual HxObjectGUI* getGUI();

    ///  Recompute size and position of object's icon group
    void recomputeSize();
    ///  Add an object to icon group
    void addChild(HxObject* child);
    ///  Remove an object from icon group
    void removeChild(HxObject* child);

    void setRemoveDownstreamWhenDeleted(bool set){removeDownstreamWhenDeleted = set;}

    virtual void checkRemoteMode();

    virtual void removingFromPool() {}

    bool acceptSave() const { return noSave==0; }
    void setNoSave(bool b) { noSave=b; }
  
    HxRemoteSessionController* getAllowedRemoteController() const {return m_allowedRemoteCtrl;}

    /// To know if the object is collapsed.
    bool isCollapsed() const;

    /**
     * To get the port which value is displayed in the tree view.
     */
    HxPort* getTreeViewAccessiblePort() const;

    /**
     * To register a port as accessible in the tree view.
     */
    void setTreeViewAccessiblePort(HxPort* port);

    /**
     * To set the noRemove flag.
     */
    void setNoRemove(bool noRemoveFlag);

    /**
     * To set the noRemoveAll flag.
     */
    void setNoRemoveAll(bool noRemoveAllFlag);

    /** 
     * To know if the flag noRemove is set.
     */
    bool isNoRemove() const;

    /**
     * To know if the flag noRemoveAll is set.
     */
    bool isNoRemoveAll() const;

    /**
     * To know if the object has viewer toggles.
     */
    bool hasViewerTogglesVisible() const;

    /**
     * To know if the object is being destroyed.
     */
    bool isBeingDestroyed() const;

  /** 
   * To know if the object is pinned.
   */
  bool isPinned() const;

  /** 
   * To pin/unpin the object.
   */
  void pin(bool pinned = true);

  /**
   * To know if the object is invisible.
   */
  bool isInvisible() const;

  /**
   * To know if the object can be clipped by another one.
   */
  bool isClippable() const;

  /**  
   * To get the package the object belongs to.
   */
  McString getPackage() const;

  /**
   * To prevent the object from untouching its ports
   * when compute is done.
   * Useful when portAction has not been hit.
   * This is a one time action. It needs to be call
   * when one wants to disable compute untouch effect
   * and keep all new information for real compute call.
   */
  void preserveTouchOnce();

  bool isVisibleIfUncollapsed() const { return visibleIfUncollapsed; }

  /**
   * To know if an object is connected to another.
   * Used by theObjectPool->saveState for instance.
   */
  bool isConnected() const;

    // Return interconnection 
    HxInterconnection* getInterconnection( HxPort* port, bool create = true );
    
    //Delete interconnection related to port
    void deleteInterconnection( HxPort* port );

    //Spread fire method to interconnected modules
    void spreadFireToConnected();

    virtual void setCaption(McString const &caption);
    virtual McString const& getCaption() const;

protected:

    /// Constructor is protected - this is an abstract class.
    HxObject(McInterfaceOwner* owner = 0);

    /// Destructor is virtual.
    virtual ~HxObject();

    /// This method displays some information about the object.
    virtual void info();

    /// Derived info() methods should use this for printing.
    void infoTag(const char* label, const char* format, ...);

    void appendInfoTag(QxInfoTag* infoTag);

    /** These flags control how a network is saved. For details refer to
        HxObjectPool::SaveFlags. The flag INCLUDE_INVISIBLE already
        will be interpreted in HxObjectPool::saveState. The two other
        flags will be interpreted in the overloaded method
        HxData::saveCreation. */
    enum SaveFlags {
        /// Save data objects even if they could be loaded from an existing file.
        SAVE_LOADABLE = 0x01,
        /// Reuse filenames and overwrite old versions during auto save
        OVERWRITE_EXISTING = 0x02,
        /// Include hidden unreferenced data objects in network sript
        INCLUDE_INVISIBLE = 0x04,
        /// Force auto save if necessary
        FORCE_AUTO_SAVE = 0x08
    };

    /** This method writes a command sequence to @c fp which, when executed,
        creates this object and sets its ports. The default implementation 
        simply calls the following methods saveCreation, savePorts... */
    virtual void saveState(FILE* fp, const char* dataDir, int saveFlags);

    /** This method writes a command sequence to @c fp which, when executed,
        creates this object. For modules this is usually just a simple <em>
        create</em> command. For data objects this is more likely a <em> load</em>
        command. If a data object has not yet been saved into a file, this
        is done automatically. Actually, the method is called twice when
        saving a network. In a first pass with @c fp==0 it is merely checked
        if data objects would be automatically written to file. If this
        happens the routine should return a non-zero integer. In a second
        pass with @c fp!=0 the actual save operation should be performed. */
    virtual int saveCreation(FILE* fp, const char* dataDir, int saveFlags);

    /// Writes a command sequence preparing the port initialization to fp.
    virtual void savePortPreparation(FILE* fp);

    /// Writes a command sequence initializing the ports to fp.
    virtual void savePorts(FILE* fp);

    /// Writes a command sequence finishing the object initialization to fp.
    virtual void saveUpdate(FILE* fp);

    /// Implements the first pass of the firing algorithm.
    void firePass1();

    /** Calls update and compute. This method is used in the implementation
        of the second pass fire method above. It calls update, shows
        and hides the object's ports as necessary, calls compute,
        shows and hides the object's ports again, and finally calls
        updateInfo in orde to refresh any info tags. The return value
        of this method is a newFlag which is used to touch the connection
        ports of all downstream objects. If this flag is null, compute
        isn't called for downstream objects. On default, 0xffffffff is
        returned. The method is overloaded in HxData in order to return the
        newFlag of the data object. It is also overloaded in HxBatchModule
        and in HxArbitraryCut. */
    virtual int callCompute();

    /** This method is called after a downstream object is connected to the
        object. The method is overloaded for example in HxMultiChannelField3,
        where among other things the tightness flag of the connection port
        is set. */
    virtual void notifyConnect(HxConnection* downStreamConnection);

    /** This method is called after a downstream object is disconnected.
        When the method is called the connection already has been removed
        from downStreamConnections. The method is overloaded for
        example in HxMultiChannelField3, where among other things the
        tightness flag of the connection is unset. */
    virtual void notifyDisconnect(HxConnection* downStreamConnection);

    /** Decides whether downstream objects can connect or not. The method is
        called before a connection to an upstream object is established. The
        upstream object may overload the method and return 0 in order to deny
        the connection. The method is also called when a connection is changed
        interactively in order to give a visual feedback (yellow highlight).
        The default method simply returns 1, therby accepting any connection. */
    virtual bool acceptConnect(HxConnection* downStreamConnection);

    void setAllowedRemoteController(HxRemoteSessionController* ctrl);

    HxObjectGUI* gui; // GUI class implements Qt specific stuff
    McDArray<HxEditorInfo*> editorInfo; // Editors which can operate on object
    HxObject* parent; // Parent object of icon group
    McDArray<HxObject*>	children; // Childs of icon group
    McBox2i iconRect; // Icon box (used in findObject() and elsewhere)
    
    bool removeDownstreamWhenDeleted;

    // Object's icon is shown in object pool.
    unsigned int visible:1;
	// Object's icon is never shown in object pool.
	unsigned int invisible:1;
    // Object is selected
    unsigned int selected:1;
    // Object is marked as readonly (not used).
    unsigned int readOnly:1;
    // Object is locked (not used).
    unsigned int locked:1;
    // Used in mouseMoveEvent.
    unsigned int work:1;
    // Object should not be deleted (except when remove -All is called).
    unsigned int noRemoveAll:1;
	// Object should never be deleted (except at the end of amira).
	unsigned int noRemove:1;
    // Object should not be clipped by other modules.
    unsigned int noClip:1;
    // Used by the 2-pass firing algorithm.
    unsigned int shouldComputeAtAll:1;
    // If set viewer toggles will always be shown.
    unsigned int hasViewerToggles:1;
    // Set if an asteriks is appended to name.
    unsigned int hasAsterisk:1;
    // Prevent compute() being called recursively
    unsigned int computeLock:1;
    // This is set as soon as destroy() is called.
    unsigned int beingDestroyed;
    // Rember if interfaces already created
    unsigned int interfacesAreAttached:1;
    // Object GUI should have a help button though it's not of type HxModule
    unsigned int withExtraHelpButton:1;
    // Set if icon would be visible if it is not collapsed.
    unsigned int visibleIfUncollapsed:1;
    // Object should not be saved.
    unsigned int noSave:1;

    // Fire counter
    unsigned int fireCount;

    // The port which value is displayed in the tree view.
    HxPort* m_treeViewAccessiblePort;

    /** This generates some @c template documentation files for this module.
	If @c snapsOnly is 1 only snapshots of all visible ports are made
	and saved to @c classname_portname.png, respectively.
	If @c snapsOnly is 0 a @c classname.doc file is also created
	containing a standard documentation which should be
	completed manually. */
    void createDocFiles(int snapsOnly);

    HxRemoteSessionController* m_allowedRemoteCtrl;

    // should we untouch module's port when compute is done
    bool m_untouchPorts;

  /**
   * The pin counter.
   */
  int m_pinCounter;

    //Interconnection managers (one per connected port)
    McDArray<HxInterconnection*> m_interconnections;

    // Caption for GUI representation of this object
    McString m_caption;

    friend class HxMain;
    friend class HxConnection;
    friend class HxObjectGUI;
    friend class QxProgressModule;
    friend class HxObjectPool;
    friend class HxObjectPoolGUI;
};

// ------------------------------ INLINE methods. ------------------------------
inline HxPort*
HxObject::getTreeViewAccessiblePort() const
{
  return m_treeViewAccessiblePort;
}

inline void
HxObject::setNoRemove(bool noRemoveFlag)
{
  noRemove = noRemoveFlag;
}

inline void
HxObject::setNoRemoveAll(bool noRemoveAllFlag)
{
  noRemoveAll = noRemoveAllFlag;
}

inline bool
HxObject::isNoRemove() const
{
  return noRemove;
}

inline bool
HxObject::isNoRemoveAll() const
{
  return noRemoveAll;
}

inline bool 
HxObject::hasViewerTogglesVisible() const
{
  return hasViewerToggles;
}

inline bool 
HxObject::isBeingDestroyed() const
{
  return beingDestroyed;
}

inline bool 
HxObject::isInvisible() const
{
  return invisible;
}

inline bool 
HxObject::isClippable() const
{
    return !noClip;
}

#endif 


/// @}
