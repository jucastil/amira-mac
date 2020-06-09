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
#ifndef _HX_OBJECT_POOL_H
#define _HX_OBJECT_POOL_H

#include <mclib/McDArray.h>
#include <mclib/McVec2i.h>

#include <hxcore/HxObject.h>
#include <hxcore/HxAmiraWinDLLApi.h>

class QWidget;
class HxObjectPoolGUI;
class HxConnection;
class QxObjectPoolContainer ;
struct HxObjectInfo;
class QxObjectPoolNotifier;

/** This class stores all Amira data objects and modules. Typically,
    the objects are represented by a small icon in the network area of
    Amira's user interface. However, note that some icons may also be
    hidden.

    The object pool can be accessed via the global pointer
    @c theObjectPool. For example, this pointer may be used in a
    compute module in order to add new data objects to the object
    pool. Another application is to search the object pool and to
    access objects which are not directly connected to a module's
    input port.
*/

class HXCORE_API HxObjectPool {

  public:
    /// Constructor.
    HxObjectPool(QWidget* parent) ;

    /// Destructor.
    virtual ~HxObjectPool();

    /** Add an object to the pool. The reference counter of the object
        is increased by one. */
    void addObject(HxObject* object);

    /** Remove an object from the pool. The reference counter of the object
        is decreased by one. */
    void removeObject(HxObject* object);

    /**
     * Replace an object into the pool by another.
     * New object will be automatically added to the pool at the same
     * graphical position than the old one which will be removed from the pool.
     * If objects have the same type and the same number of ports and connections,
     * some actions will be performed:
     *      - new object connections will be copied from old object.
     *        If keepExistingUpstreamConnections parameter is set, effective connection
     *        of new object will be kept and only the empty ones will be copied.
     *      - new object ports values will be copied from old ones if copyPortsValues
     *        paramter is set.
     *      - all downstream connections of old object will be re-connected to the new one.
     * The method will return 1 if these action have been performed, 0 otherwise.
     */
    int replaceObject(HxObject* oldObj, HxObject* newObj, bool keepExistingUpstreamConnections = false, bool copyPortsValues = false);

    /// Duplicate all selected objects, called from the edit menu.
    void duplicateSelectedObjects();

    /// Hide all selected objects, called from the edit menu.
    void hideSelectedObjects();

    /// Remove all selected objects, called from the edit menu.
    void removeSelectedObjects();

    /** Remove all or all visible objects. If @c onlyVisible is true hidden
        objects, i.e., objects whose icons are not displayed in the object
        pool, will not be removed. This is the behavior when called from
        the edit menu. */
    void removeAll(bool force = false);

    /// Select all objects.
    void selectAll(bool onlyVisible = true);

    /// Deselect all objects.
    void deselectAll();

    /// Show all hidden objects.
    void showAll();

    /// Returns the first selected module if any, otherwise @c NULL.
    HxObject* getSelected();

    /// Look for an object with the given label.
    HxObject* findObject(const char* label) const;

    /** Look for an object at position @c x @c y. This method is used
        internally in order to select objects. The first object whose
        icon covers position @c x @c y is returned or @c NULL if no such
	object is found. */
    HxObject* findObject(int x, int y);

    /** Look for a connection at position @c x @c y. The method is used
        internally in order to pick connection lines. The nearest line with a
        distance less than 3 pixels from point @c x @c y stored in @c result.
        If the endpoint of a connection line is picked, all downstream
        connections of the corresponding object are stored in @c result. The
        method returns the number of found connections. */
    int findConnection(int x, int y, McDArray<HxConnection*>& result);

    /** Find an useful position for the given object. Data objects are put
        on the left part of the object pool. Modules are put on the right
        part just beside the primary data object they are connected to. */
    void position(HxObject* object);

    /** These flags control how a network is saved. Before saveState() is
        called from the file menu (in HxMain.cpp) an appropriate bit mask is
        generated. The flags OVERWRITE_EXISTING and INCLUDE_INVISIBLE are
        initialized using the global variables overwriteInAutoSave and
        includeUnusedDataObjects. These variables can be modified by
        the user via the preference dialog. The flag SAVE_LOADABLE is true
        if the option <em> Amira script and data files (pack & go)</em> is chosen
        in the file dialogs format menu. */
    enum SaveFlags {
        /// Save data objects even if they could be loaded from an existing file.
        SAVE_LOADABLE = HxObject::SAVE_LOADABLE,
        /// Reuse filenames and overwrite old versions during auto save
        OVERWRITE_EXISTING = HxObject::OVERWRITE_EXISTING,
        /// Include hidden unreferenced data objects in network sript
        INCLUDE_INVISIBLE = HxObject::INCLUDE_INVISIBLE,
        /// Force auto save if necessary
        FORCE_AUTO_SAVE = HxObject::FORCE_AUTO_SAVE
    };
 
    /** Get the number of objects to be saved */
    int getObjectsToBeSaved(int saveFlags=0);

    /** Iterate through the list of objects and adapt their suffixes to the file formats
     *  they would be saved as in case of storing them. */
    bool adaptObjectSuffixes(McDArray<HxObject*> const &list, unsigned char* isSaved);

    /** Creates a script which, when executed, restores the current network.
        @c file denotes the file name of the script. If the object pool contains
        data objects which need to be saved in order to be able to restore the
        network a question dialog pops up asking the user whether these
        objects should be saved automatically. If the user accepts the objects
        are stored in the directory denoted by @c dir. */
    void saveState(const char* file, const char* dir, int saveFlags=0);

    // Returns pointer to the QWidget GUI class.
    HxObjectPoolGUI* getGUI() { return gui; }

    QxObjectPoolContainer* getGUIContainer() { return guiContainer; }

    // This calls gui->redraw() if gui exists.
    void redraw();

    /* Enables or disables viewer toggles on icons. This method sets the
       value of the flag @c viewerTogglesOnIcons, recomputes the size of all
       icons, and finally redraw the object pool. */
    void setViewerTogglesOnIcons(bool value);

    /* Update the viewer toggles of all icons. This method is called
       when the viewer layout is changed (see HxViewerPanel::setLayout())
       or when a viewer is explicitly shown or hidden. */
    void updateViewerToggles();

    /** Creates object specified by @c info and connect it to @c primary.
        This method is called when selecting an entry from a object's
        popup menu. In previous versions of Amira it was protected, but
        we need it in AmiraVR to create objects in 3D. */
    void createObjectFromPopup(HxObjectInfo*, HxObject* source);

    /** Adds an object to the pool. This method performs the same
        type of initialization which is performed when an object is
        selected from a popup menu. In particular, it auto-connects
        the object to the specified source object, sets the correct
        viewer maks, selects the object unless auto-selection is
        deactivated in the preference dialog, and finally fires the
        new object. */
    void addObject(HxObject* object, HxObject* source);

    /** Marks the network as dirty. This allows us to check if the network
        need to be saved before terminating Amira. */
    void touch() { networkIsDirty=1; }

    void checkRemoteMode();

    void updateMacroButtons(bool all=false);

	/// To delete the module buttons displayed in the macrobuttons widget.
	void deleteModuleButtons();

	/// To execute duplicate commands.
	int executeDuplicationCommands(McTypedObject * typedObject, const char * duplicatedObjectName);

	/// For copy-paste functionnality.
	void cutObjects();
	void copyObjects();
	void pasteObjects();

	/// To know if copy-cut/paste functionality can be achieved.
	inline bool copyCutPasteEnabled() {return m_copyCutPasteEnabled;};

	/// To set the m_copyCutPasteEnabled flag.
	inline void setCopyCutPasteEnabled(bool enable = true) {m_copyCutPasteEnabled = enable;};

    /**	Emit a Qt signal to notify that a new connection has been done. 
        In case of @c connection was already connected to an object, this object can be retrieved thanks to @c oldSrc.
        Internal use.*/
    void notifyConnection(HxConnection* connection, HxObject* oldSrc);

    /** Emit a Qt signal to notify that a disconnection has been done.
        When this signal is emitted, the connection still contains the source from which it is being disconnected.
        The parameter @c isDisconnectedDuringConnection tell if this signal is emitted during a connection which implies first a disconnection of the original source.
        The parameter @c oldConnectedObject refers to the previous connected object.
        Internal use.*/
    void notifyDisconnection(HxConnection* connection, bool isDisconnectedDuringConnection, HxObject* oldConnectedObject);

    /**	Emit a Qt signal to notify that an object has been selected. 
    *  Internal use.
    */
    void notifySelection(HxObject* selectedObj);

    /**	Emit a Qt signal to notify that an object has been deselected. 
    *  Internal use.
    */
    void notifyDeselection(HxObject* deselectedObj);

    /**	Emit a Qt signal to notify that a fire has been done on the object. 
    *  Internal use.
    */
    void notifyFireOnObject(HxObject* firedObject);

  /** 
   * To get the offset.
   */
  const McVec2i& getOffset() const;

    /** 
     * Called to remove the connections from the visible list
     * when their visibility state is changed.
     */
    void removeUndisplayedPinnedConnectionsFromVisibleList();

    /** Connection point for Qt signals and slots.
      */
    QxObjectPoolNotifier* const mNotifier;

    /**
     *  Clip all objects within the pool by the clipper @c pMod.
     *  By default, object are clipped within a viewer only if they are visible
     *  within the viewer.
     *  Optionally, you can specify a viewerClippingMask which will indicate
     *  if an object must never be clipped within specific viewers by using @c viewerClipMask.
     */
    void clipObjects(HxPlanarMod* pMod, int viewerClipMask=0xffff);

    /**
     *  Unset objects clipping for @c pMod.
     */
    void unclipObjects(HxPlanarMod* pMod);

    // This calls gui->adjustScrollBars() if gui exists.
    void adjustScrollBars();

  protected:
    // GUI stuff is implemented in a separate class.
    HxObjectPoolGUI* gui;
    QxObjectPoolContainer* guiContainer;

    // Scroll bar offset, better should be a member of HxObjectPoolGUI ?
    McVec2i offset;

    // Helper function for the saving method
    void verifyNodesForSaving(unsigned char* isSaved,McDArray<HxObject*> &list, int saveFlags);

    /**
     *  Update objects clipping state.
     *  Note that @c viewerClipMask isn't used when @c clippingIsActivated is false.
     */
    void updateObjectsClippedState(bool clippingIsActivated, HxPlanarMod* pMod, int viewerClipMask=0xffff);

  public:
    /**
     *  To be notified that preferences changed.
     */
    virtual void preferencesChanged(const HxPreferences& oldPreferences, const HxPreferences& newPreferences);

    static HxObjectPool*& getTheObjectPool();

    /** If set the object pool's redraw method returns immediately.
        This is useful in order to speed up batch processing of complex
        networks. Also used internally e.g. when removing multiple objects
        from the object pool. This must be an int because the flag is
        frequently increased and decreased by one. */
    int redrawInhibit;

    /** If set objects added via addObject remain hidden. This flag
        can be accessed from a script via the linked Tcl variable
        @c hideNewModules. For example, in the Amira start script
        @c Amira.init this variable is set to true just before the default
        colormaps are loaded. Afterwards it is set to false again. */
    int hideNewModules;

    /** This flag indicates that the current network has been modified and need
        to be saved. The flag is set at various places depending on the values
        of the above dirty flags. It is reset in saveNetwork. */
    int networkIsDirty;

    /// Cached value of HxPreferences::m_drawViewerTogglesOnIcons preference bit.
    bool viewerTogglesOnIcons;
    
    /** Contains all objects. This member should only be used to
        search for certain objects. In order to add or remove objects
        use addObject or removeObject. */
    McDArray<HxObject*> nodeList;

    // Contains all selected objects.
    McDArray<HxObject*> selectionList;

    // Contains all visible objects (selected and/or pinned)
    McDArray<HxObject*> visibleList;

	/// Contains all copied objects.
	McDArray<HxObject*> copyList;

	/// Contains all the Tcl commands used for re-create cut objects.
	McDArray< McDArray<string> > cutObjectsSavedCommands;

	/// To know if objects are cut.
	int cutInProgress;

	/// To know if copy-cut/paste functionality can be achieved.
	bool m_copyCutPasteEnabled;

    friend class HxObjectPoolGUI;
};

// ------------------------------ INLINE methods. ------------------------------
inline const McVec2i&
HxObjectPool::getOffset() const
{
  return offset;
}

// Global instance of the object pool.
#define theObjectPool (HxObjectPool::getTheObjectPool())

#endif

/// @}
